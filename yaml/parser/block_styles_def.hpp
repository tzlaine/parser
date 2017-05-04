/**
 *   Copyright (C) 2017 Zach Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef YAML_PARSER_BLOCK_STYLES_DEF_HPP
#define YAML_PARSER_BLOCK_STYLES_DEF_HPP

#include <yaml/parser/block_styles.hpp>

#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_container.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/phoenix/object/construct.hpp>


namespace yaml { namespace parser {

    namespace detail {

        struct chomping
        {
            template <typename>
            struct result { using type = chomping_t; };

            chomping_t operator() (block_header_t block_header) const
            { return block_header.chomping_; }
        };

        struct indentation
        {
            template <typename>
            struct result { using type = int; };

            int operator() (block_header_t block_header) const
            { return block_header.indentation_; }
        };

        struct seq_spaces
        {
            template <typename, typename>
            struct result { using type = int; };

            int operator() (int n, context_t c) const
            { return c == context_t::block_out ? n - 1 : n; }
        };

    }

    template <typename Iterator>
    block_styles<Iterator>::block_styles (boost::phoenix::function<error_handler_t> const & error_handler)
        : flow_styles_ (error_handler)
    {
        qi::attr_type attr;
        qi::omit_type omit;
        qi::_val_type _val;
        qi::_1_type _1;
        qi::_r1_type _r1;
        qi::_r2_type _r2;
        qi::_a_type _a;
        qi::_b_type _b;
        qi::_c_type _c;
        qi::lit_type lit;
        qi::blank_type blank;
        qi::digit_type digit;
        qi::eol_type eol;
        qi::eoi_type eoi;
        qi::eps_type eps;

        namespace phx = boost::phoenix;
        using phx::function;
        using phx::construct;

        phx::function<detail::handle_properties> handle_properties;
        phx::function<detail::chomping> chomping;
        phx::function<detail::indentation> indentation;
        phx::function<detail::seq_spaces> seq_spaces; // [201]
        auto ins = phx::insert(_val, _1);
        auto pb = phx::push_back(_val, _1);

#ifdef BOOST_SPIRIT_DEBUG
        phx::function<detail::print_indent> print_indent;
#endif

        auto & nb_char = flow_styles_.basic_structures_.characters_.nb_char;
        auto & ns_char = flow_styles_.basic_structures_.characters_.ns_char;

        auto & b_l_folded = flow_styles_.basic_structures_.b_l_folded;
        auto & indent = flow_styles_.basic_structures_.indent;
        auto & indent_le = flow_styles_.basic_structures_.indent_le;
        auto & indent_lt = flow_styles_.basic_structures_.indent_lt;
        auto & l_comment = flow_styles_.basic_structures_.l_comment;
        auto & l_empty = flow_styles_.basic_structures_.l_empty;
        auto & s_b_comment = flow_styles_.basic_structures_.s_b_comment;
        auto & s_l_comments = flow_styles_.basic_structures_.s_l_comments;
        auto & separate = flow_styles_.basic_structures_.separate;
        auto & properties = flow_styles_.basic_structures_.properties;

        auto & anchors = flow_styles_.anchors;
        auto & flow_node = flow_styles_.flow_node;
        auto & implicit_yaml_key = flow_styles_.implicit_yaml_key;
        auto & implicit_json_key = flow_styles_.implicit_json_key;

        // 8.1 Block Scalar Styles

        // [162]
        block_header = (
                indentation_indicator[_a = _1] >> chomping_indicator[_b = _1]
            |   chomping_indicator[_b = _1] >> indentation_indicator[_a = _1]
            )
            >>  s_b_comment(_c = eoi_state_t::not_at_end)
            [_val = construct<block_header_t>(_a, _b)]
            ;

        // [163]
        // TODO: For round-tripping, a number like this must sometimes be
        // placed in the output (as in, when a scalar has leading spaces)
        indentation_indicator =
                digit[_val = _1 - 0x30]   // c-indentation-indicator [163]
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
            >>  '#' >> *nb_char >> (eol | eoi)
            >>  *l_comment(_a = eoi_state_t::not_at_end)
            ;

        // 8.1.2. Literal Style

        // [170]
        literal =
                '|'
            >>  block_header[_a = _r1 + indentation(_1), _b = chomping(_1)]
            >>  literal_content(_a, _b)[_val = _1]
            ;

        // [171]
        literal_text =
            *l_empty(_r1, context_t::block_in) >> indent(_r1) >> +nb_char
            ;

        // [172]
        literal_next =
            eol >> literal_text(_r1)
            ;

        // [173]
        literal_content =
                -(literal_text(_r1) >> *literal_next(_r1) >> (eol | eoi))
            >>  chomped_empty(_r1, _r2)
            ;

        // 8.1.3. Folded Style

        // [174]
        folded =
                '>'
            >>  omit[block_header[_a = _r1 + indentation(_1), _b = chomping(_1)]]
            >>  folded_content(_a, _b)
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
                -(diff_lines(_r1) >> (eol | eoi))
            >>  chomped_empty(_r1, _r2)
            ;

        // 8.2.1. Block Sequences

        auto_detect_indent =
            eps[_val = 0] >> &(*lit(' ')[++_val])
#ifdef BOOST_SPIRIT_DEBUG
            >> eps[phx::ref(std::cerr) << "m=" << _val << " ----------------------------------------\n"]
#endif
            ;

        // [183]
        block_sequence =
                auto_detect_indent[_a = _1]
            >>  +(indent(_a) >> block_seq_entry(_a)[pb])
            ;

        // [184]
        block_seq_entry =
                '-'
            >>  !ns_char
            >>  block_indented(_r1, context_t::block_in)
            ;

        // [185]
        block_indented =
                auto_detect_indent[_a = _1]
            >>  indent(_a)
            >>  (
                    compact_sequence(_r1 + 1 + _a)[_val = _1]
                |   compact_mapping(_r1 + 1 + _a)[_val = _1]
                )
            |   block_node(_r1, _r2)[_val = _1]
            |   attr(ast::value_t()) >> s_l_comments(_b = eoi_state_t::not_at_end)
            ;

        // [186]
        compact_sequence =
            block_seq_entry(_r1) % indent(_r1)
            ;

        // 8.2.1. Block Mappings

        // [187]
        block_mapping =
                auto_detect_indent[_a = _1]
            >>  +(indent(_a) >> block_map_entry(_a)[ins]) // TODO: Report duplicate keys when found.
            ;

        // [188]
        block_map_entry =
            block_map_explicit_entry(_r1) | block_map_implicit_entry(_r1)
            ;

        // [189]
        block_map_explicit_entry =
                block_map_explicit_key(_r1)
            >>  (block_map_explicit_value(_r1) | attr(ast::value_t()))
            ;

        // [190]
        block_map_explicit_key =
            '?' >> block_indented(_r1, context_t::block_out)
            ;

        // [191]
        block_map_explicit_value =
            indent(_r1) >> ':' >> block_indented(_r1, context_t::block_out)
            ;

        // [192]
        block_map_implicit_entry =
                (block_map_implicit_key | attr(ast::value_t()))
            >>  block_map_implicit_value(_r1)
            ;

        // [193]
        block_map_implicit_key =
            implicit_json_key(context_t::block_key) | implicit_yaml_key(context_t::block_key)
            ;

        // [194]
        block_map_implicit_value =
                ':'
            >>  (
                    block_node(_r1, context_t::block_out)
                |   attr(ast::value_t()) >> s_l_comments(_a = eoi_state_t::not_at_end)
                )
            ;

        // [195]
        compact_mapping =
            block_map_entry(_r1)[ins] % indent(_r1)
            ;

        // 8.2.3. Block Nodes

        // [196]
        block_node = YAML_PARSER_PRINT_INDENT (
            block_in_block(_r1, _r2) | flow_in_block(_r1)
            )
            ;

        // [197]
        flow_in_block =
                separate(_r1 + 1, context_t::flow_out)
            >>  flow_node(_r1 + 1, context_t::flow_out)
            >>  s_l_comments(_a = eoi_state_t::not_at_end)
            ;

        // [198]
        block_in_block =
            block_scalar(_r1, _r2) | block_collection(_r1, _r2)
            ;

        // [199]
        block_scalar =
                separate(_r1 + 1, _r2)
            >>  -omit[properties(_r1 + 1, _r2)[_a = _1] >> separate(_r1 + 1, _r2)]
            >>  (literal(_r1) | folded(_r1))
                [_val = handle_properties(_a, _1, phx::ref(anchors))]
            ;

        // [200]
        block_collection =
                s_l_comments(_b = eoi_state_t::not_at_end)
            >>  (
                    block_sequence(seq_spaces(_r1, _r2))[_val = _1]
                |   block_mapping(_r1)[_val = _1]
                )
            |   omit[separate(_r1 + 1, _r2) >> properties(_r1 + 1, _r2)[_a = _1]]
            >>  s_l_comments(_b = eoi_state_t::not_at_end)
            >>  (
                    block_sequence(seq_spaces(_r1, _r2))
                    [_val = handle_properties(_a, _1, phx::ref(anchors))]
                |   block_mapping(_r1)
                    [_val = handle_properties(_a, _1, phx::ref(anchors))]
                )
            ;

        BOOST_SPIRIT_DEBUG_NODES(
            (auto_detect_indent)

            (block_header)
            (indentation_indicator)
            (chomping_indicator)
            (chomped_empty)
            (strip_empty)
            (keep_empty)
            (trail_comments)
            (literal)
            (literal_text)
            (literal_text)
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
            (block_sequence)
            (block_seq_entry)
            (block_indented)
            (compact_sequence)
            (block_mapping)
            (block_map_entry)
            (block_map_explicit_entry)
            (block_map_explicit_key)
            (block_map_explicit_value)
            (block_map_implicit_entry)
            (block_map_implicit_key)
            (block_map_implicit_value)
            (compact_mapping)
            (block_node)
            (flow_in_block)
            (block_in_block)
            (block_scalar)
            (block_collection)
        );
    }

} }

#endif
