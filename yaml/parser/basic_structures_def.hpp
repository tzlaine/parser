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

        struct reserved_directive_warning
        {
            template <typename>
            struct result { using type = void; };

            void operator() (
                iterator_range_t const & range,
                error_handler_t const & error_handler
            ) const {
                if (!error_handler.impl().warning_fn_)
                    return;
                std::string const directive = range_to_string(range);
                std::ostringstream oss;
                oss << "All directives except %YAML and %TAG are "
                    << "reserved for future use.  The directive '%"
                    << directive << "' will be ignored";
                error_handler.impl().report_warning_at(range.begin(), oss.str());
            }
        };

        struct check_yaml_version
        {
            template <typename, typename, typename, typename, typename>
            struct result { using type = void; };

            template <typename Pass>
            void operator() (
                iterator_range_t const & range,
                unsigned int major,
                unsigned int minor,
                basic_structures_t & structures,
                Pass & pass
            ) const {
                error_handler_t const & error_handler = structures.error_handler_.f;
                if (structures.yaml_directive_seen_) {
                    scoped_multipart_error_t multipart(error_handler.impl());
                    error_handler.impl().report_error_at(
                        range.begin(),
                        "The current document has more than one %YAML "
                        "directive.  Only one is allowed.  The latest "
                        "one is here",
                        multipart
                    );
                    error_handler.impl().report_error_at(
                        structures.first_yaml_directive_it_,
                        "The first one was was here",
                        multipart
                    );
                    pass = false;
                } else {
                    structures.first_yaml_directive_it_ = range.begin();
                    if (major != 1) {
                        scoped_multipart_error_t multipart(error_handler.impl());
                        std::ostringstream oss;
                        oss << "The current document has a %YAML "
                            << major << '.' << minor
                            << " directive.  This parser recognizes "
                               "YAML 1.2, and so cannot continue";
                        error_handler.impl().report_error_at(range.begin(), oss.str(), multipart);
                        pass = false;
                    } else if (minor != 2 && error_handler.impl().warning_fn_) {
                        std::ostringstream oss;
                        oss << "The current document has a %YAML "
                            << major << '.' << minor
                            << " directive.  This parser recognizes "
                               "YAML 1.2, and so might not work.  "
                               "Trying anyway...";
                        error_handler.impl().report_warning_at(range.begin(), oss.str());
                    }
                }
                structures.yaml_directive_seen_ = true;
            }
        };

        struct record_tag_handle
        {
            template <typename, typename, typename, typename, typename>
            struct result { using type = void; };

            template <typename Pass>
            void operator() (
                iterator_range_t const & handle_range,
                iterator_range_t const & prefix_range,
                qi::symbols<char, basic_structures_t::tag_t> & tags,
                error_handler_t const & error_handler,
                Pass & pass
            ) const {
                std::string const handle = range_to_string(handle_range);

                auto existing_tag = tags.find(handle);
                if (existing_tag && existing_tag->default_) {
                    tags.remove(handle);
                    existing_tag = nullptr;
                }

                if (existing_tag) {
                    scoped_multipart_error_t multipart(error_handler.impl());
                    std::ostringstream oss;
                    oss << "The current document has more than one %TAG "
                        << "directive using the handle " << handle << ".  "
                        << "Only one is allowed.  The latest one is here";
                    error_handler.impl().report_error_at(
                        handle_range.begin(),
                        oss.str(),
                        multipart
                    );
                    error_handler.impl().report_error_at(
                        existing_tag->position_,
                        "The first one was was here",
                        multipart
                    );
                    pass = false;
                } else {
                    tags.add(
                        handle,
                        basic_structures_t::tag_t{
                            range_to_string(prefix_range),
                            handle_range.begin(),
                            false
                        }
                    );
                }
            }
        };

        struct prefix
        {
            template <typename>
            struct result { using type = std::string const &; };

            std::string const & operator() (basic_structures_t::tag_t const & tag) const
            { return tag.prefix_; }
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

    }

    YAML_HEADER_ONLY_INLINE
    basic_structures_t::basic_structures_t (
        boost::phoenix::function<error_handler_t> & error_handler,
        bool verbose
    )
        : characters_ (verbose)
        , error_handler_ (error_handler)
        , yaml_directive_seen_ (false)
    {
        qi::attr_type attr;
        qi::uint_type uint_;
        qi::unicode::char_type char_;
        qi::unicode::string_type string;
        qi::_val_type _val;
        qi::_1_type _1;
        qi::_2_type _2;
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

        function<detail::reserved_directive_warning> reserved_directive_warning;
        function<detail::check_yaml_version> check_yaml_version;
        function<detail::record_tag_handle> record_tag_handle;
        function<detail::prefix> prefix;
        function<detail::check_start_of_line> check_start_of_line;
        function<detail::first_time_eoi> first_time_eoi;
        function<detail::to_str> to_str;

        tags.name("a tag prefix defined in a TAG directive, \"!!\", or \"!\"");

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
            raw[+ns_char >> *(+blank >> +ns_char)]
            [reserved_directive_warning(_1, phx::cref(error_handler_.f))]
            ;

        // [86]
        yaml_directive =
                raw["YAML"][_a = _1]
            >>  +blank
            >>  uint_[_b = _1]
            >>  '.'
            >>  uint_[check_yaml_version(_a, _b, _1, phx::ref(*this), _pass)]
            ;

        // [88]
        tag_directive =
                "TAG"
            >>  +blank
            >>  raw[tag_handle][_a = _1]
            >>  +blank
            >>  raw[tag_prefix][record_tag_handle(_a, _1, phx::ref(tags), phx::cref(error_handler_.f), _pass)]
            ;

        // [89]
        tag_handle =
                // "alnum..." below is  word_char [38]
                '!' >> +(alnum | char_("-")) >> '!' // named_tag_handle [92]
            |   "!!"                                // secondary_tag_handle [91]
            |   '!'                                 // primary_tag_handle [90]
            ;

        // [93]
        tag_prefix =
                '!' >> *uri_char
            |   tag_char >> *uri_char
            ;

        // 6.9 Node Properties

        // [96]
        properties = (
                tag_property[_a = _1] >> -(separate(_r1, _r2) >> anchor_property[_b = *_1])
            |   anchor_property[_b = _1] >> -(separate(_r1, _r2) >> tag_property[_a = *_1])
            )
            [_val = construct<parser_properties_t>(_a, _b)]
            ;

        // [97]
        tag_property =
                raw["!<" > +uri_char > '>'][_val = to_str(_1)]            // verbatim_tag [98]
            |   (tags >> raw[+tag_char])[_val = prefix(_1) + to_str(_2)]  // shorthand_tag [99]
            |   lit('!')[_val = "!"]                                      // non_specific_tag [100]
            ;

        // [22]
        // auto indicator = char_("-?:,[]{}#&*!|>'\"%@`");

        // [101]
        anchor_property =
            '&' >> raw[+(ns_char - char_(",[]{}"))]
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
