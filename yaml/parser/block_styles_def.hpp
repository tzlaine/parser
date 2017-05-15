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

        struct update_max
        {
            template <typename, typename>
            struct result { using type = void; };

            void operator() (int & max_indent, int this_line_indent) const
            { max_indent = (std::max)(max_indent, this_line_indent); }
        };

        struct check_scalar_indentation
        {
            template <typename, typename, typename, typename, typename>
            struct result { using type = void; };

            template <typename Pass>
            void operator() (
                iterator_range_t range,
                int & max_indent,
                int this_line_indent,
                error_handler_t const & error_handler,
                Pass & pass
            ) const {
                if (max_indent <= this_line_indent) {
                    max_indent = this_line_indent;
                } else {
                    scoped_multipart_error_t multipart(error_handler.impl());
                    std::ostringstream oss;
                    oss << "The first non-space character of a block-scalar "
                        << "(text beginning with '|' or '>') must be at least "
                        << "as indented as all its leading empty lines.  "
                        << "This line is indented " << this_line_indent
                        << " spaces, but a previous line was indented "
                        << max_indent << " spaces:\n";
                    error_handler.impl().report_error_at(range.begin(), oss.str(), multipart);
                    pass = false;
                }
            }
        };

    }

    YAML_HEADER_ONLY_INLINE
    block_styles_t::block_styles_t (
        boost::phoenix::function<error_handler_t> & error_handler,
        bool verbose
    )
        : flow_styles_ (error_handler, verbose)
    {
        qi::attr_type attr;
        qi::omit_type omit;
        qi::hold_type hold;
        qi::raw_type raw;
        qi::_pass_type _pass;
        qi::_val_type _val;
        qi::_1_type _1;
        qi::_2_type _2;
        qi::_r1_type _r1;
        qi::_r2_type _r2;
        qi::_r3_type _r3;
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
        phx::function<detail::push_utf8> push_utf8;
        phx::function<detail::update_max> update_max;
        phx::function<detail::map_insert> map_insert;
        phx::function<detail::check_scalar_indentation> check_scalar_indentation;
        phx::function<detail::seq_spaces> seq_spaces; // [201]

        auto ins = map_insert(_val, _1, _b, phx::cref(error_handler.f));
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

        // [165]
        chomped_last =
                eps(_r1 == chomping_t::strip) >> (eol | eoi)
            |   eps(_r1 != chomping_t::strip) >> (eol[_val += "\n"] | eoi)
            ;

        // [166]
        chomped_empty =
                eps(_r2 == chomping_t::keep) >> keep_empty(_r1)[_r3 += _1]
            |   eps(_r2 != chomping_t::keep) >> strip_empty(_r1)
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
            >>  eps[_a = eoi_state_t::not_at_end] >> *l_comment(_a)
            ;

        // 8.1.2. Literal Style

        // [170]
        literal =
                '|'
            >>  block_header[_a = indentation(_1), _b = chomping(_1)]
            >>  (
                    eps(_a == 0)
                >>  scalar_auto_detect_indent[_a = _1]
                    // This parenthesized expression is a modified version of
                    // folded_content that only expects the optional portion
                    // if positive indentation is detected.
                >>  (
                        (eps(_r1 < _a) > literal_content_optional(_a, _b)[_val = _1] | eps)
                    >>  chomped_empty(_a, _b, _val)
                    )
                |   eps(_a != 0)
                >>  literal_content(_r1 + _a, _b)[_val = _1]
                )
            ;

        // [171]
        literal_text =
                *l_empty(_r1, context_t::block_in)[_a += _1]
            >>  indent(_r1)
            >>  nb_char[_val += _a, push_utf8(_val, _1)]
            >>  *nb_char[push_utf8(_val, _1)]
            ;

        // [172]
        literal_next =
            eol >> !(lit("...") | "---") >> literal_text(_r1)[_val += "\n", _val += _1]
            ;

        literal_content_optional =
            hold[literal_text(_r1) >> *literal_next(_r1) >> chomped_last(_r2)]
            ;

        // [173]
        literal_content =
                -literal_content_optional(_r1, _r2)
            >>  chomped_empty(_r1, _r2, _val)
            ;

        // 8.1.3. Folded Style

        // [174]
        folded =
                '>'
            >>  block_header[_a = indentation(_1), _b = chomping(_1)]
            >>  (
                    eps(_a == 0)
                >>  scalar_auto_detect_indent[_a = _1]
                    // This parenthesized expression is a modified version of
                    // folded_content that only expects the optional portion
                    // if positive indentation is detected.
                >>  (
                        (eps(_r1 < _a) > folded_content_optional(_a, _b)[_val = _1] | eps)
                    >>  chomped_empty(_a, _b, _val)
                    )
                |   eps(_a != 0)
                >>  folded_content(_r1 + _a, _b)[_val = _1]
                )
            ;

        // [175]
        folded_text =
            indent(_r1) >> ns_char[push_utf8(_val, _1)] >> *nb_char[push_utf8(_val, _1)]
            ;

        // [176]
        folded_lines =
                folded_text(_r1)[_val += _1]
            >>  *(b_l_folded(_r1, context_t::block_in, true) >> folded_text(_r1))[_val += _1, _val += _2]
            ;

        // [177]
        spaced_text =
            indent(_r1) >> blank[_val = _1] >> *nb_char[push_utf8(_val, _1)]
            ;

        // [178]
        spaced =
            eol[_val = "\n"] >> *l_empty(_r1, context_t::block_in)[_val += "\n"]
            ;

        // [179]
        spaced_lines =
                spaced_text(_r1)[_val += _1]
            >>  *(spaced(_r1) >> spaced_text(_r1))[_val += _1, _val += _2]
            ;

        // [180]
        same_lines =
                *l_empty(_r1, context_t::block_in)[_a += _1]
            >>  (folded_lines(_r1)[_val += _a, _val += _1] | spaced_lines(_r1)[_val += _a, _val += _1])
            ;

        // [181]
        diff_lines =
                same_lines(_r1)[_val += _1]
            >>  *(eol >> same_lines(_r1)[_val += "\n", _val += _1])
            ;

        folded_content_optional =
            hold[diff_lines(_r1) >> chomped_last(_r2)]
            ;

        // [182]
        folded_content =
                -folded_content_optional(_r1, _r2)
            >>  chomped_empty(_r1, _r2, _val)
            ;

        // 8.2.1. Block Sequences

        auto_detect_indent =
            eps[_val = 0] >> &(*lit(' ')[++_val])
            ;

        if (verbose) {
            auto_detect_indent =
                    eps[_val = 0] >> &(*lit(' ')[++_val])
                >>  eps[phx::ref(std::cerr) << "m=" << _val << " ----------------------------------------\n"]
                ;
        }

        scalar_auto_detect_indent =
                eps[_val = 0]
            >>  &(
                    *(eps[_a = 0] >> *lit(' ')[++_a] >> eol[update_max(_val, _a)])
                >>  eps[_a = 0] >> *lit(' ')[++_a]
                >>  raw[eps][check_scalar_indentation(_1, _val, _a, phx::cref(error_handler.f), _pass)]
            )
            ;


        if (verbose) {
            scalar_auto_detect_indent =
                    eps[_val = 0]
                >>  &(
                        *(
                            eps[_a = 0] >> *lit(' ')[++_a] >> eol[update_max(_val, _a)]
                        >>  eps[phx::ref(std::cerr) << "m=" << _a << " ----------------------------------------\n"]
                        )
                    >>  eps[_a = 0] >> *lit(' ')[++_a] >> eps(_val <= _a)[_val = _a]
                    >>  eps[phx::ref(std::cerr) << "m=" << _a << " ----------------------------------------\n"]
                    )
                >>  eps[phx::ref(std::cerr) << "m_final=" << _val << " ----------------------------------\n"]
                ;
        }

        // [183]
        block_sequence =
                auto_detect_indent[_a = _1] >> eps(_r1 < _a)
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
                auto_detect_indent[_a = _1] >> eps(_r1 < _a)
            >>  +(indent(_a) >> raw[eps][_b = _1] >> block_map_entry(_a)[ins])
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
                raw[eps][_b = _1]
            >>  block_map_entry(_r1)[ins] % indent(_r1)
            ;

        // 8.2.3. Block Nodes

        // [196]
        block_node =
            block_in_block(_r1, _r2) | flow_in_block(_r1)
            ;

        if (verbose) {
            block_node =
                YAML_PARSER_PRINT_INDENT
                (block_in_block(_r1, _r2) | flow_in_block(_r1))
                ;
        }

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
                [_val = handle_properties(_a, _1, phx::ref(anchors), phx::cref(error_handler.f))]
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
                    [_val = handle_properties(_a, _1, phx::ref(anchors), phx::cref(error_handler.f))]
                |   block_mapping(_r1)
                    [_val = handle_properties(_a, _1, phx::ref(anchors), phx::cref(error_handler.f))]
                )
            ;

        if (verbose) {
            BOOST_SPIRIT_DEBUG_NODES(
                (auto_detect_indent)
                (scalar_auto_detect_indent)

                (block_header)
                (indentation_indicator)
                (chomping_indicator)
                (chomped_empty)
                (strip_empty)
                (keep_empty)
                (trail_comments)
                (literal)
                (literal_text)
                (literal_next)
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
    }

} }

#endif
