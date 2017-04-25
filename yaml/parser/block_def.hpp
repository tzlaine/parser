/**
 *   Copyright (C) 2010, 2011 Object Modeling Designs
 *   Copyright (C) 2017 Zach Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if !defined(OMD_PARSER_BLOCK_DEF_HPP)
#define OMD_PARSER_BLOCK_DEF_HPP

#include <yaml/parser/block.hpp>

#include <boost/phoenix/object/construct.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_container.hpp>
#include <boost/spirit/include/phoenix_statement.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <algorithm>


// For debugging:
#if defined(BOOST_SPIRIT_DEBUG)
#define PRINT_INDENT \
[ std::cerr << phx::val("\n============================") << get_indent << std::endl ]
#else
#define PRINT_INDENT
#endif

namespace omd { namespace yaml { namespace parser {

    namespace detail {

        struct update_indent
        {
            template <typename, typename, typename>
            struct result { typedef void type; };

            template <typename Range, typename Pass>
            void operator()(
                Range const& rng,                   //  <-- where we are now
                int& current_indent,                //  <-- the current indent position
                Pass& pass                          //  <-- set to false to fail parsing
            ) const
            {
                int pos = rng.begin().get_position().column;
                if (pos >= current_indent)
                    current_indent = pos;
                else
                    pass = false;
            }
        };

        struct check_indent
        {
            template <typename, typename, typename>
            struct result { typedef void type; };

            template <typename Range, typename Pass>
            void operator()(
                Range const& rng,                   //  <-- where we are now
                int const& current_indent,          //  <-- the current indent position
                Pass& pass                          //  <-- set to false to fail parsing
            ) const
            {
                int pos = rng.begin().get_position().column;
                if (pos < current_indent)
                    pass = false;
            }
        };

        struct fold_line
        {
            template <typename, typename, typename, typename>
            struct result { typedef void type; };

            template <typename String, typename Range>
            void operator()(
                String& result_,
                Range const& rng,
                char indicator,
                bool different_indentation
            ) const
            {
                if (rng.empty())
                    return;

                typedef typename std::iterator_traits<typename Range::iterator>::difference_type distance_t;

                distance_t n = std::distance(rng.begin(), rng.end());

                // Don't fold the previous lines if the next line has a different indentation
                if ((indicator == '>') && different_indentation)
                {
                    for (distance_t i = 0; i != n; ++i)
                        result_ += '\n';
                    return;
                }

                if ((indicator == '>') && (n == 1))
                    result_ += ' ';
                else
                    result_ += '\n';
            }
        };

        struct chomp_string
        {
            template <typename, typename>
            struct result { typedef void type; };

            template <typename String>
            void operator()(String& result_, char indicator) const
            {
                if (indicator == '-' || indicator == 0)
                {
                    std::size_t pos = result_.size();
                    for (; pos != 0; --pos)
                    {
                        if (result_[pos-1] != '\n')
                            break;
                    }
                    if (pos < result_.size())
                    {
                        if (indicator == '-')
                            result_.erase(pos);
                        else
                            result_.erase(pos+1);
                    }
                }
            }
        };

        struct chomping
        {
            template <typename>
            struct result { typedef chomping_t type; };

            chomping_t operator() (block_header_t block_header) const
            { return block_header.chomping_; }
        };

        struct indentation
        {
            template <typename>
            struct result { typedef int type; };

            int operator() (block_header_t block_header) const
            { return block_header.indentation_; }
        };

        struct seq_spaces
        {
            template <typename, typename>
            struct result { typedef int type; };

            int operator() (int n, context_t c) const
            { return c == context_t::block_out ? n - 1 : n; }
        };

    }

    template <typename Iterator>
    block<Iterator>::block(std::string const& source_file)
      : block::base_type(start),
        flow_g(current_indent, anchors),
        current_indent(-1),
        n_(-1),
        error_handler(error_handler_t(source_file))
    {
        namespace phx = boost::phoenix;
        using boost::spirit::qi::copy;
        phx::function<detail::update_indent> update_indent;
        phx::function<detail::check_indent> check_indent;
        phx::function<detail::fold_line> fold_line;
        phx::function<detail::chomp_string> chomp_string;
        phx::function<qi::symbols<char>::adder> add_anchor(anchors.add);

        phx::function<detail::chomping> chomping;
        phx::function<detail::indentation> indentation;
        phx::function<detail::seq_spaces> seq_spaces; // [201]
        using phx::ref;

        using phx::construct;

        qi::skip_type skip;
        auto space = ws.start.alias();

        qi::_val_type _val;
        qi::_1_type _1;
        qi::_2_type _2;
        qi::_3_type _3;
        qi::_4_type _4;
        qi::_a_type _a;
        qi::_b_type _b;
        qi::_c_type _c;
        qi::_r1_type _r1;
        qi::_r2_type _r2;
        qi::char_type char_;
        qi::lit_type lit;

        qi::repeat_type repeat;
        qi::omit_type omit;
        qi::_pass_type _pass;
        qi::eps_type eps;
        qi::attr_type attr;
        qi::raw_type raw;

        qi::eol_type eol;
        qi::eoi_type eoi_;
        qi::blank_type blank;
        qi::digit_type digit;

        auto comment = copy('#' >> *(char_ - eol) >> eol);  // comments
        auto blank_eol = copy(*blank >> (comment | eol));   // empty until eol

        auto & nb_char = flow_g.scalar_value.string_value.nb_char;
        auto & ns_char = flow_g.scalar_value.string_value.ns_char;
        auto & separate = flow_g.scalar_value.string_value.separate;

        auto map_key = copy(
            skip(space)[flow_g.scalar_value.map_key]
            );

        // no-skip version without strings
        auto flow_scalar_ns =
            flow_g.scalar_value.scalar_value_no_strings.alias()
            ;

        // Only for strings
        auto& flow_string_ns =
            flow_g.scalar_value.string_value
            ;

        auto get_indent =
            ref(current_indent)
            ;

        auto save_indent = copy(
            eps[_a = get_indent] PRINT_INDENT
            );

        auto zero_indent = copy(
            eps[_a = get_indent, get_indent = 0] PRINT_INDENT
            );

        auto increase_indent = copy(
            eps[get_indent += 1] PRINT_INDENT
            );

        auto decrease_indent = copy(
            eps[get_indent -= 1] PRINT_INDENT
            );

        auto restore_indent = copy(
            eps[get_indent = _a] PRINT_INDENT
            );

        indent_ =
            *blank >> raw[eps] [update_indent(_1, get_indent, _pass)]
            ;

        skip_indent =
            *blank >> raw[eps] [check_indent(_1, get_indent, _pass)]
            ;

        auto skip_exact_indent = copy(
            repeat(get_indent-1)[blank]     // note: indent is one based!
            );

        skip_indent_child =
            *blank >> raw[eps] [check_indent(_1, get_indent + 1, _pass)]
            ;

        end_of_input =
            omit[
                -('#' >> *(char_ - eoi_))   //  allow comments at the very end
            >>  eoi_
            ];

        //  Allow newlines before scalars as long as they are properly indented.
        //  Make sure that the scalar doesn't span multiple lines by requiring
        //  the next line to be a higher level node (with lower indentation).
        //  We'll deal with strings and potentially multi-line strings separately.

        auto scalar_in_block = copy(
                omit[-(+blank_eol >> skip_indent_child)]
            >>  flow_scalar_ns
            >>  !(+blank_eol >> skip_indent_child)
            );

        //  Allow newlines before strings as long as they are properly indented
        auto string_in_block = copy(
                omit[-(+blank_eol >> skip_indent_child)]
            >>  flow_string_ns
            );

        // flow compound (arrays and maps) need no indentations. Set indent to
        // zero while parsing.
        flow_compound %=
                zero_indent
            >>  (skip(space)[flow_g.flow_node] | !restore_indent)
            >>  restore_indent
            ;

        block_node =
                compact_block
            |   indented_block
            |   flow_compound
            |   scalar_in_block
            |   string_in_block
            |   (omit[blank_eol | end_of_input]  //  If all else fails, then null_t
                  >> attr(ast::null_t()))
            ;

        anchored_block_node %=
                '&'
            >>  (+~char_(" \n\r\t,{}[]")) [ add_anchor(_1) ]
            >>  omit[blank | &eol]
            >>  block_node
            ;

        auto block_node_main = copy(
                anchored_block_node
            |   block_node
            );

        indented_block %=
                increase_indent
            >>  (blocks | !decrease_indent)
            >>  decrease_indent
            ;

        compact_block =
                !blank_eol
            >>  blocks
            ;

        auto block_main = copy(
                block_literal
            |   block_seq
            |   explicit_block_map
            |   implicit_block_map
            );

        blocks %=
                omit[*blank_eol]
            >>  save_indent
            >>  (block_main | !restore_indent)
            >>  restore_indent
            ;

        start %=
                blocks

                // YAML allows bare top-level scalars. Allow this, but set
                // the indent to 1 to require unquoted strings to be indented,
                // otherwise, unquoted strings will gobble up too much in
                // its path.
            |   eps[get_indent = 1] >> skip(space)[flow_g.scalar_value]
            ;

        auto start_indent = copy(
            omit[indent_] PRINT_INDENT
            );

        auto block_literal_first_line = copy(
                raw[*eol]           [ fold_line(_val, _1, _a, false) ]
            >>  start_indent                                //  Get first line indent
            >>  +(char_ - eol)      [ _val += _1 ]          //  Get the line
            );

        // This rule checks for blank lines and sets local _c to true or false
        // depending on whether the succeeding line has a different indentation or not
        auto block_literal_blank_lines = copy(
            raw[(*eol)
                >> &-(skip_exact_indent >> blank)     [ _c = true ]
                >> -(!skip_exact_indent)              [ _c = true ]
            ][ fold_line(_val, _1, _a, _c) ]
            );

        // This rule checks if the current line is indented or not and
        // sets local _c accordingly
        auto block_literal_indented_line = copy(
            &(blank[ _c = true ] | eps[ _c = false ])
            );

        auto block_literal_line = copy(
                block_literal_blank_lines
            >>  skip_exact_indent                           //  Indent get_indent spaces
            >>  block_literal_indented_line
            >>  +(char_ - eol)      [ _val += _1 ]          //  Get the line
            );

        block_literal =
                (*blank)            [ _c = false, _b = 0 ]  //  initialize locals
            >>  char_("|>")         [ _a = _1 ]             //  get indicator in local _a
            >>  -char_("+-")        [ _b = _1 ]             //  get the (optional) chomping indicator
            >>  *blank >> blank_eol
            >>  block_literal_first_line
            >>  *block_literal_line
            >>  eps                 [ chomp_string(_val, _b) ]
            ;

        auto block_seq_indicator = copy(                    //  Lookahead and see if we have a
            &(start_indent >> '-' >> (blank | eol))         //  sequence indicator.
            );

        block_seq =
                omit[block_seq_indicator]
            >>  +block_seq_entry                            //  Get the entries
            ;

        block_seq_entry =
                omit[*blank_eol]                            //  Ignore blank lines
            >>  omit[skip_indent]                           //  Indent get_indent spaces
            >>  omit['-' >> (blank | &eol)]                 //  Get the sequence indicator '-'
            >>  block_node_main                             //  Get the entry
            ;

        auto implicit_block_map_indicator = copy(           //  Lookahead and see if we have an
            &(  start_indent                                //  implicit map indicator.
            >>  map_key
            >>  skip(space)[':']
            ));

        implicit_block_map =
                omit[implicit_block_map_indicator]
            >>  +block_map_entry                            //  Get the entries
            ;

        auto explicit_block_map_indicator = copy(           //  Lookahead and see if we have an
            &(start_indent >> '?' >> (blank | eol))         //  explicit map indicator.
            );

        explicit_block_map =
                omit[explicit_block_map_indicator]
            >>  +block_map_entry                            //  Get the entries
            ;

        block_map_entry =
                explicit_block_map_entry
            |   implicit_block_map_entry
            ;

        implicit_block_map_entry =
                omit[*blank_eol]                            //  Ignore blank lines
            >>  omit[skip_indent]                           //  Indent get_indent spaces
            >>  map_key                                     //  Get the key
            >>  omit[skip(space)[':']]                      //  Get the map indicator ':'
            >>  omit[*blank]                                //  Ignore blank spaces
            >>  block_node_main                             //  Get the value
            ;

        explicit_block_map_entry =
                omit[*blank_eol]                            //  Ignore blank lines
            >>  omit[skip_indent]                           //  Indent get_indent spaces
            >>  omit['?' >> (blank | &eol)]                 //  Get the map-key indicator '?'
            >>  map_key                                     //  Get the key

            >>  omit[*blank_eol]                            //  Ignore blank lines
            >>  omit[skip_indent]                           //  Indent get_indent spaces
            >>  omit[':' >> (blank | &eol)]                 //  Get the map-value indicator ':'
            >>  block_node_main                             //  Get the value
            ;

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

        // [67]
        line_prefix =
                indent(_r1)
            >>  eps(_r2 == context_t::flow_in || _r2 == context_t::flow_out) >> -separate
            ;

        // [70]
        l_empty =
                (line_prefix(_r1, _r2) | indent_lt(_r1))
            >>  eol
            ;

        b_l_folded =
                eol >> +l_empty(_r1, _r2)   // b-l-trimmed [71]
            |   eol
            ;

        // 8.1 Block Scalar Styles

        // [162]
        block_header = (
                indentation_indicator[_a = _1] >> +blank >> chomping_indicator[_b = _1]
            |   chomping_indicator[_b = _1] >> +blank >> indentation_indicator[_a = _1]
            )
            >>  blank_eol
            [_val = construct<block_header_t>(_a, _b)]
            ;

        // [163]
        // TODO: For round-tripping, a number like this must sometimes be
        // placed in the output (as in, when a scalar has leading spaces)
        indentation_indicator =
                digit[_val = _1 - 0x30]
            |   eps[_val = 0]
            ;

        // [164]
        chomping_indicator =
                lit('-')[_val = chomping_t::strip]
            |   lit('+')[_val = chomping_t::keep]
            |   eps[_val = chomping_t::clip]
            ;

        // [166]
        chomped_empty =
                eps(_r2 == chomping_t::keep) >> keep_empty(_r1)
            |   strip_empty(_r1)
            ;

        // [167]
        strip_empty =
                *(indent_le(_r1) >> eol)
            >>  -trail_comments(_r1)
            ;

        // [168]
        keep_empty =
                *l_empty(_r1, context_t::block_in)
            >>  -trail_comments(_r1)
            ;

        // [169]
        trail_comments =
                indent_lt(_r1)
            >>  '#' >> *nb_char >> eol
            >>  *blank_eol
            ;

        // 8.1.2. Literal Style

        // [170] TODO: Get rid of these Phoenix functions -- just use
        // block_header _1 and _2!
        literal =
                '|'
            >>  block_header[_a = _r1 + indentation(_1), _b = chomping(_1)]
            >>  literal_content(_a, _b)[_val = _1]
            ;

        // [171]
        l_nb_literal_text =
            *l_empty(_r1, context_t::block_in) >> indent(_r1) >> +nb_char
            ;

        // [172]
        b_nb_literal_text =
            eol >> l_nb_literal_text(_r1)
            ;

        // [173]
        literal_content =
                -(l_nb_literal_text(_r1) >> *b_nb_literal_text(_r1) >> eol)
            >>  chomped_empty(_r1, _r2)
            ;

        // 8.1.3. Folded Style

        // [174]
        folded =
                '>'
            >>  block_header[_a = _r1 + indentation(_1), _b = chomping(_1)]
            >>  folded_content(_a, _b)[_val = _1]
            ;

        // [175]
        folded_text =
            indent(_r1) >> ns_char >> *nb_char
            ;

        // [176]
        folded_lines =
            folded_text(_r1) >> *(b_l_folded(_r1, context_t::block_in) >> folded_text(_r1))
            ;

        // [177]
        spaced_text =
            indent(_r1) >> blank >> *nb_char
            ;

        // [178]
        spaced =
            eol >> *l_empty(_r1, context_t::block_in)
            ;

        // [179]
        spaced_lines =
            spaced_text(_r1) >> *(spaced(_r1) >> spaced_text(_r1))
            ;

        // [180]
        same_lines =
                *l_empty(_r1, context_t::block_in)
            >>  (folded_lines(_r1) | spaced_lines(_r1))
            ;

        // [181]
        diff_lines =
            same_lines(_r1) >> *(eol >> same_lines(_r1))
            ;

        // [182]
        folded_content =
                -(diff_lines(_r1) >> eol)
            >>  chomped_empty(_r1, _r2)
            ;

#if 0
        // 8.2.1. Block Sequences

        auto_detect_indent =
            eps[_val = 0] >> &(*lit(' ')[++_val])
            ;

        // [183]
        block_sequence =
                auto_detect_indent[_a = _1]
            >>  +(indent(_a) >> block_seq_entry(_a))
            ;

        // [184]
        block_seq_entry =
                '-' >> !ns_char
            >>  block_indented(_r1, context_t::block_in)
            ;

        // [185]
        block_indented =
            indent
            ;
#endif

#if 0
        // 8.2.3. Block Nodes

        // [196]
        block_node =
            block_in_block(_r1, _r2) | flow_in_block(_r1)
            ;

        // [197]
        flow_in_block =
                separate(_r1 + 1, context_t::flow_out)
            >>  flow_node/*TODO (_r1 + 1, context_t::flow_out)*/
            >>  s_l_comments
            ;

        // [198]
        block_in_block =
            block_scalar(_r1, _r2) | block_collection(_r1, _r2)
            ;

        // [199]
        block_scalar =
                separate(_r1 + 1, _r2)
            >>  -(properties(_r1 + 1, _r2) >> separate(_r1 + 1, _r2))
            >>  (literal(_r1) | folded(_r1))
            ;

        // [200]
        block_collection =
                -(separate(_r1 + 1, _r2) >> properties(_r1 + 1, _r2))
            >>  s_l_comments
            >>  (block_sequence(seq_spaces(_r1, _r2)) | block_mapping(_r1))
            ;
#endif

        BOOST_SPIRIT_DEBUG_NODES(
            (indent)
            (indent_lt)
            (indent_le)
            (line_prefix)
            (l_empty)
            (b_l_folded)
            (block_header)
            (indentation_indicator)
            (chomping_indicator)
            (chomped_empty)
            (strip_empty)
            (keep_empty)
            (trail_comments)
            (literal)
            (l_nb_literal_text)
            (b_nb_literal_text)
            (literal_content)
            (folded)
            (folded_text)
            (folded_lines)
            (spaced_text)
            (spaced)
            (spaced_lines)
            (same_lines)
            (diff_lines)
            (folded_content)
        );

        BOOST_SPIRIT_DEBUG_NODES(
            (end_of_input)
            (block_node)
            (anchored_block_node)
            (indented_block)
            (compact_block)
            (blocks)
            (block_literal)
            (block_seq)
            (block_seq_entry)
            (implicit_block_map)
            (implicit_block_map_entry)
            (block_map_entry)
            (explicit_block_map)
            (explicit_block_map_entry)
            (indent)
        );

        qi::on_error<qi::fail>(blocks, error_handler(_1, _2, _3, _4));
    }

} } }

#endif
