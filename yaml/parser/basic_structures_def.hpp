/**
 *   Copyright (C) 2017 Zach Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef YAML_PARSER_BASIC_STRUCTURES_DEF_HPP
#define YAML_PARSER_BASIC_STRUCTURES_DEF_HPP

#include <yaml/parser/basic_structures.hpp>

#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/phoenix/object/construct.hpp>


namespace yaml { namespace parser {

    namespace detail {

        struct check_yaml_version
        {
            template <typename, typename>
            struct result { using type = void; };

            template <typename Pass>
            void operator() (
                unsigned int major,
                unsigned int minor,
                error_handler_t const & error_handler,
                Pass & pass
            ) const {
                if (major != 1) {
                    std::stringstream oss;
                    oss << "The current document has a %YAML "
                        << major << '.' << minor
                        << " directive.  This parser recognizes "
                           "YAML 1.2, and so cannot continue.\n";
                    error_handler.report_preformatted_error(oss.str());
                    pass = false;
                } else if (minor != 2) {
                    std::stringstream oss;
                    oss << "The current document has a %YAML "
                        << major << '.' << minor
                        << " directive.  This parser recognizes "
                           "YAML 1.2, and so might not work.  "
                           "Trying anyway...\n";
                    error_handler.report_warning(oss.str());
                }
            }
        };

        // HACK!  This is a dirty, dirty hack that bears explaining.  Many
        // productions in the YAML 1.2 spec include "newline | end-of-input"
        // (e.g. b-comment).  This poses a problem, since many of the uses of
        // this construct (say, using b-comment) are repeated via Kleene star.
        // Spirit consumes a character when parsing a newline (qi::eol), but
        // *not* when parsing end-of-input (qi::eoi).
        //
        // So, when a rule contains, say, *b-comment, infinite looping
        // results, since qi::eoi succeeds without advancing the parser's read
        // position.
        //
        // The natural inclination is to create a consuming version of eoi --
        // and since eoi is unique, that state can be shared across all rules
        // in the parser.  Sadly, this does not work, because some
        // (transitive) uses of eoi in this YAML parser may need to backtrack
        // back to before the eoi was seen and try some other productions.
        //
        // As a workaround, I've created a repetition-detecting eoi.  The
        // state is passed in, and the first time eoi is seen, the state
        // changes.  Subsequent eoi detections will fail.
        struct first_time_eoi
        {
            template <typename>
            struct result { using type = bool; };

            bool operator() (eoi_state_t & state) const
            {
                bool const retval = state == eoi_state_t::not_at_end;
                state = eoi_state_t::at_end;
                return retval;
            }
        };

        struct to_str
        {
            template <typename>
            struct result { using type = std::string; };

            std::string operator() (iterator_range_t range) const
            {
                using iterator_t = iterator_range_t::iterator;
                boost::u32_to_u8_iterator<iterator_t> first(range.begin());
                boost::u32_to_u8_iterator<iterator_t> last(range.end());
                return std::string(first, last);
            }
        };

    }

    YAML_HEADER_ONLY_INLINE
    basic_structures_t::basic_structures_t (
        boost::phoenix::function<error_handler_t> const & error_handler,
        bool verbose
    )
        : characters_ (verbose)
        , error_handler_ (error_handler)
    {
        qi::attr_type attr;
        qi::uint_type uint_;
        qi::unicode::char_type char_;
        qi::_val_type _val;
        qi::_1_type _1;
        qi::_r1_type _r1;
        qi::_r2_type _r2;
        qi::_r3_type _r3;
        qi::_a_type _a;
        qi::_b_type _b;
        qi::lit_type lit;
        qi::blank_type blank;
        qi::unicode::alnum_type alnum;
        qi::eol_type eol;
        qi::eoi_type eoi;
        qi::eps_type eps;
        qi::repeat_type repeat;
        qi::raw_type raw;
        qi::_pass_type _pass;

        namespace phx = boost::phoenix;
        using qi::copy;
        using phx::function;
        using phx::construct;

        auto & nb_char = characters_.nb_char;
        auto & ns_char = characters_.ns_char;
        auto & tag_char = characters_.tag_char;
        auto & uri_char = characters_.uri_char;

        function<detail::check_yaml_version> check_yaml_version;
        function<detail::check_start_of_line> check_start_of_line;
        function<detail::first_time_eoi> first_time_eoi;
        function<detail::to_str> to_str;

        // 6.1. Indentation Spaces

        // [63]
        indent =
            repeat(_r1)[lit(' ')]
            ;

        // [64]
        indent_lt =
            repeat(0, _r1 - 1)[lit(' ')]
            ;

        // [65]
        indent_le =
            repeat(0, _r1)[lit(' ')]
            ;

        // 6.2. Separation Spaces

        // [66]
        separate_in_line =
            (+blank | raw[eps][check_start_of_line(_1, _pass)])
            ;

        // 6.3. Line Prefixes

        // [67]
        line_prefix =
                eps(_r2 == context_t::block_in || _r2 == context_t::block_out) >> indent(_r1)
            |   eps(_r2 == context_t::flow_in || _r2 == context_t::flow_out) >> indent(_r1) >> -separate_in_line
            ;

        // 6.4 Empty Lines

        // [70]
        l_empty =
                (line_prefix(_r1, _r2) | indent_lt(_r1))
            >>  eol
            >>  attr('\n')
            ;

        // 6.5 Line Folding

        // [73]
        b_l_folded =
                eol
            >>  (eps(!_r3) | !(lit("...") | "---"))
            >>  (
                    +l_empty(_r1, _r2)   // b-l-trimmed [71]
                |    attr(" ")
                )
            ;

        // [74]
        flow_folded =
                -separate_in_line
            >>  b_l_folded(_r1, context_t::flow_in, _r2)
            >>  line_prefix(_r1, context_t::flow_in)
            ;

        // 6.6 Comments

        // [75]
        comment_text =
            '#' >> +nb_char
            ;

        // [77]
        s_b_comment =
                -(separate_in_line >> -comment_text)
            >>  (eol | eoi >> eps(first_time_eoi(_r1)))                  // b-comment [77]
            ;

        // [78]
        l_comment =
            separate_in_line >> -comment_text >> (eol | eoi >> eps(first_time_eoi(_r1)))
            ;

        // [79]
        s_l_comments =
                 (s_b_comment(_r1) | raw[eps][check_start_of_line(_1, _pass)])
            >>  *l_comment(_r1)
            ;

        // 6.7 Separation Lines

        // [80]
        separate =
                eps(_r2 == context_t::block_key || _r2 == context_t::flow_key)
            >>  separate_in_line
            |   eps(!(_r2 == context_t::block_key || _r2 == context_t::flow_key))
            >>  separate_lines(_r1)
            ;

        // [81]
        separate_lines =
                s_l_comments(_a = eoi_state_t::not_at_end)
            >>  indent(_r1) >> -separate_in_line   // flow-line-prefix [69]
            |   separate_in_line
            ;

        // 6.8 Directives

        // [82]
        directive =
                '%'
            >>  (yaml_directive | tag_directive | reserved_directive)
            >>  s_l_comments(_a = eoi_state_t::not_at_end)
            ;

        // [83]
        reserved_directive =
                +ns_char
            >>  *(+blank >> +ns_char)
            ;

        // [86]
        yaml_directive =
                "YAML"
            >>  +blank
            >>  uint_[_a = _1]
            >>  '.'
            >>  uint_[check_yaml_version(_a, _1, phx::cref(error_handler_.get().f), _pass)]
            ;

        // [88]
        tag_directive =
            "TAG" >> +blank >> tag_handle >> +blank >> tag_prefix
            // TODO [add tag to tag symbol table]
            ;

        // [89]
        tag_handle =
                // "alnum..." below is  word_char [38]
                '!' >> +(alnum | char_("-")) >> '!' // named_tag_handle [92] (must match existing TAG-defined prefix)
            |   "!!"                                // secondary_tag_handle [91]
            |   '!'                                 // primary_tag_handle [90]
            ; // TODO: Check that nonempty handle matches existing TAG prefix (or better yet, use a symbol table)

        // [93]
        tag_prefix =
                '!' >> *uri_char
            |   tag_char >> *uri_char
            ;

        // 6.9 Node Properties

        // [96]
        // TODO: Defer construction of an ast::properties_t until we know
        // we'll keep it.
        properties = (
                tag_property[_a = _1] >> -(separate(_r1, _r2) >> anchor_property[_b = *_1])
            |   anchor_property[_b = _1] >> -(separate(_r1, _r2) >> tag_property[_a = *_1])
            )
            [_val = construct<ast::properties_t>(to_str(_a), to_str(_b))]
            ;

        // [97]
        tag_property = raw[
                lit('!') >> "<" > +uri_char > ">"   // verbatim_tag [98]
            |   tag_handle >> +tag_char             // shorthand_tag [99]
            |   '!'                                 // non_specific_tag [100]
            ]
            ;

        // [22]
        auto indicator = char_("-?:,[]{}#&*!|>'\"%@`");

        // [101]
        // TODO: The spec says flow-indicator (",[]{}") here, not indicator.
        // Document this.  Reference test 2SXE.yml:
        // Before:
//&a : key: &a value
// foo:
//  *a:
        // After:
//&a: key: &a value
//foo:
//  *a:
        anchor_property =
            '&' >> raw[+(ns_char - indicator)]
            ;

        // [102]
        // auto anchor_char = ns_char - char_(",[]{}");

        // [103]
        anchor_name =
            raw[+(ns_char - char_(",[]{}"))]
            ;

        one_time_eoi =
            eoi >> eps(first_time_eoi(_r1))
            ;

        if (verbose) {
            BOOST_SPIRIT_DEBUG_NODES(
                (indent)
                (indent_lt)
                (indent_le)
                (separate_in_line)
                (line_prefix)
                (l_empty)
                (b_l_folded)
                (flow_folded)
                (comment_text)
                (s_b_comment)
                (l_comment)
                (s_l_comments)
                (separate)
                (separate_lines)
                (directive)
                (reserved_directive)
                (yaml_directive)
                (tag_directive)
                (tag_handle)
                (tag_prefix)
                (properties)
                (tag_property)
                (anchor_property)
                (anchor_name)
            );
        }
    }

} }

#endif
