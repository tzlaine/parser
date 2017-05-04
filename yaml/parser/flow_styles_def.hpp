/**
 *   Copyright (C) 2017 Zach Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef YAML_PARSER_FLOW_STYLES_DEF_HPP
#define YAML_PARSER_FLOW_STYLES_DEF_HPP

#include <yaml/parser/flow_styles.hpp>

#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_container.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/phoenix/object/construct.hpp>


namespace yaml { namespace parser {

    namespace detail {

        struct in_flow
        {
            template <typename, typename>
            struct result { using type = context_t; };

            context_t operator() (context_t c) const
            {
                switch (c) {
                case context_t::flow_out:
                case context_t::flow_in:
                    return context_t::flow_in;
                case context_t::block_key:
                case context_t::flow_key:
                    return context_t::flow_key;
                default:
                    BOOST_ASSERT(!"Invalid input passed to in_flow()");
                    return context_t::block_out;
                }
            }
        };

    }

    template <typename Iterator>
    flow_styles<Iterator>::flow_styles (boost::phoenix::function<error_handler_t> const & error_handler)
        : basic_structures_ (error_handler)
    {
        qi::attr_type attr;
        qi::omit_type omit;
        qi::hold_type hold;
        qi::char_type char_;
        qi::_val_type _val;
        qi::_1_type _1;
        qi::_a_type _a;
        qi::_r1_type _r1;
        qi::_r2_type _r2;
        qi::lit_type lit;
        qi::blank_type blank;
        qi::eol_type eol;
        qi::eps_type eps;

        namespace phx = boost::phoenix;
        using qi::as;
        using phx::function;
        using phx::construct;

        phx::function<detail::handle_properties> handle_properties;
        auto ins = phx::insert(_val, _1);

#ifdef BOOST_SPIRIT_DEBUG
        phx::function<detail::print_indent> print_indent;
#endif

        auto & esc_char = basic_structures_.characters_.esc_char;
        auto & nb_json = basic_structures_.characters_.nb_json;
        auto & ns_char = basic_structures_.characters_.ns_char;

        auto & flow_folded = basic_structures_.flow_folded;
        auto & l_empty = basic_structures_.l_empty;
        auto & line_prefix = basic_structures_.line_prefix;
        auto & separate = basic_structures_.separate;
        auto & separate_in_line = basic_structures_.separate_in_line;
        auto & properties = basic_structures_.properties;

        anchors.name("anchors");

        // 7.1 Alias Nodes

        // [104]
        alias_node =
                '*'
            >   anchors
            ;

        // 7.3 Flow Scalar Styles

        // 7.3.1 Double Quoted Style

        // [107]
        nb_double_char =
                esc_char
            |   nb_json - char_("\"\\")
            ;

        // [108]
        ns_double_char =
            nb_double_char - blank
            ;

        // [109]
        double_quoted =
            '"' >> double_text(_r1, _r2) >> '"'
            ;

        // [110]
        double_text =
                eps(_r2 == context_t::flow_out || _r2 == context_t::flow_in)
            >>  double_multi_line(_r1)
            |   eps(_r2 == context_t::block_key || _r2 == context_t::flow_key)
            >>  *nb_double_char                 // double-one-line [111]
            ;

        // [112]
        double_escaped = hold[
                *blank
            >> '\\'
            >> eol
            >> *l_empty(_r1, context_t::flow_in)
            >> line_prefix(_r1, context_t::flow_in)
            ]
            ;

        // [113]
        double_break =
            double_escaped(_r1) | flow_folded(_r1, false)
            ;

        // [114]
        double_in_line =
            *hold[*blank >> ns_double_char]
            ;

        // [115]
        double_next_line = hold[
            double_break(_r1)
            >>  -hold[
                    ns_double_char
                >>  double_in_line
                >>  (double_next_line(_r1) | *blank)
                ]
            ]
            ;

        // [116]
        double_multi_line =
            double_in_line >> (double_next_line(_r1) | *blank)
            ;

        // 7.3.2 Single Quoted Style

        // [118]
        nb_single_char =
            lit("''") >> attr('\'') | nb_json - '\''
            ;

        // [119]
        ns_single_char =
            nb_single_char - blank
            ;

        // [120]
        single_quoted =
            '\'' >> single_text(_r1, _r2) >> '\''
            ;

        // [121]
        single_text =
                eps(_r2 == context_t::flow_out || _r2 == context_t::flow_in)
            >>  single_multi_line(_r1)
            |   eps(_r2 == context_t::block_key || _r2 == context_t::flow_key)
            >>  *nb_single_char
            ;

        // [123]
        single_in_line =
            *hold[*blank >> ns_single_char]
            ;

        // [124]
        single_next_line = hold[
            flow_folded(_r1, false)
            >>  -hold[
                    ns_single_char
                >> single_in_line
                >>  (single_next_line(_r1) >> *blank)
                ]
            ]
            ;

        // [125]
        single_multi_line =
            single_in_line >> (single_next_line(_r1) | *blank)
            ;

        // 7.3.3 Plain Style

        // [22]
        auto indicator = char_("-?:,[]{}#&*!|>'\"%@`");

        // [126]
        plain_first =
                (ns_char - indicator)
            |   hold[char_("?:-") >> plain_safe(_r1)]
            ;

        // [127]
        plain_safe =
                eps(_r1 == context_t::flow_out || _r1 == context_t::block_key)
            >>  ns_char
            |   eps(_r1 == context_t::flow_in || _r1 == context_t::flow_key)
            >>  ns_char - char_(",[]{}")
            ;

        // [130]
        plain_char =
                plain_safe(_r1) - char_(":#")
            |   hold[ns_char >> char_('#')]
            |   hold[char_(':') >> plain_safe(_r1)]
            ;

        // [131]
        plain =
                eps(_r2 == context_t::flow_out || _r2 == context_t::flow_in)
            >>  plain_multi_line(_r1, _r2)
            |   eps(_r2 == context_t::block_key || _r2 == context_t::flow_key)
            >>  plain_one_line(_r2)
            ;

        // [132]
        plain_in_line =
            *hold[*blank >> plain_char(_r1)]
            ;

        // [133]
        plain_one_line =
            hold[plain_first(_r1) >> plain_in_line(_r1)]
            ;

        // [134]
        plain_next_line =
            YAML_PARSER_PRINT_INDENT
            // TODO: Apply hold[] everywhere appropriate.
            hold[flow_folded(_r1, true) >> plain_char(_r2) >> plain_in_line(_r2)]
            ;

        // [135]
        plain_multi_line =
            plain_one_line(_r2) >> *plain_next_line(_r1, _r2)
            ;

        // 7.4 Flow Collection Styles

        // [136]
        function<detail::in_flow> in_flow;

        // 7.4.1 Flow Sequences

        // [137]
        flow_sequence =
            '[' >> -separate(_r1, _r2) >> -flow_seq_entries(_r1, in_flow(_r2)) >> -separate(_r1, _r2) >> ']'
            ;

        // [138]
        flow_seq_entries =
                flow_seq_entry(_r1, _r2) % (-separate(_r1, _r2) >> ',' >> -separate(_r1, _r2))
            >>  -(-separate(_r1, _r2) >> ',')
            ;

        // [139]
        flow_seq_entry =
                as<ast::value_t>{}[flow_pair(_r1, _r2)]
            |   flow_node(_r1, _r2)
            ;

        // 7.4.2 Flow Mappings

        // [140]
        flow_mapping =
            '{' >> -separate(_r1, _r2) >> -flow_map_entries(_r1, in_flow(_r2)) >> -separate(_r1, _r2) >> '}'
            ;

        // [141]
        flow_map_entries =
                flow_map_entry(_r1, _r2) % (-separate(_r1, _r2) >> ',' >> -separate(_r1, _r2))
            >>  -(-separate(_r1, _r2) >> ',')
            ;

        // [142]
        flow_map_entry =
                '?' >> separate(_r1, _r2) >> flow_map_explicit_entry(_r1, _r2)
            |   flow_map_implicit_entry(_r1, _r2)
            ;

        // [143]
        flow_map_explicit_entry =
                flow_map_implicit_entry(_r1, _r2)
            |   attr(ast::map_element_t())
            ;

        // [144]
        flow_map_implicit_entry =
                flow_map_yaml_key_entry(_r1, _r2)
            |   flow_map_empty_key_entry(_r1, _r2)
            |   flow_map_json_key_entry(_r1, _r2)
            ;

        // [145]
        flow_map_yaml_key_entry =
                flow_yaml_node(_r1, _r2)
            >>  (
                    -separate(_r1, _r2) >> flow_map_separate_value(_r1, _r2)
                |   attr(ast::value_t())
                )
            ;

        // [146]
        flow_map_empty_key_entry =
            attr(ast::value_t()) >> flow_map_separate_value(_r1, _r2)
            ;

        // [147]
        flow_map_separate_value =
                ':'
            >>  !plain_safe(_r2)
            >>  (
                    separate(_r1, _r2) >> flow_node(_r1, _r2)
                |   attr(ast::value_t())
                )
            ;

        // [148]
        flow_map_json_key_entry =
                flow_json_node(_r1, _r2)
            >>  (
                    -separate(_r1, _r2) >> flow_map_adjacent_value(_r1, _r2)
                |   attr(ast::value_t())
                )
            ;

        // [149]
        flow_map_adjacent_value =
                ':'
            >>  (
                    -separate(_r1, _r2) >> flow_node(_r1, _r2)
                |   attr(ast::value_t())
                )
            ;

        // [150]
        flow_pair =
                '?' >> separate(_r1, _r2) >> flow_map_explicit_entry(_r1, _r2)[ins]
            |   flow_pair_entry(_r1, _r2)[ins]
            ;

        // [151]
        flow_pair_entry =
                flow_pair_yaml_key_entry(_r1, _r2)
            |   flow_map_empty_key_entry(_r1, _r2)
            |   flow_pair_json_key_entry(_r1, _r2)
            ;

        // [152]
        flow_pair_yaml_key_entry =
            implicit_yaml_key(_r2) >> flow_map_separate_value(_r1, _r2)
            ;

        // [153]
        flow_pair_json_key_entry =
            implicit_json_key(_r2) >> flow_map_adjacent_value(_r1, _r2)
            ;

        // [154]
        implicit_yaml_key =
            flow_yaml_node(0, _r1) >> -separate_in_line
            ;

        // [155]
        implicit_json_key =
            flow_json_node(0, _r1) >> -separate_in_line
            ;

        // 7.5 Flow Nodes

        // [156]
        flow_yaml_content =
            plain(_r1, _r2)
            ;

        // [157]
        flow_json_content =
                flow_sequence(_r1, _r2)
            |   flow_mapping(_r1, _r2)
            |   single_quoted(_r1, _r2)
            |   double_quoted(_r1, _r2)
            ;

        // [158]
        flow_content =
                flow_yaml_content(_r1, _r2)
            |   flow_json_content(_r1, _r2)
            ;

        // TODO: Use Niabelek trick to handle parse after properties.

        // [159]
        flow_yaml_node =
                as<ast::value_t>{}[alias_node][_val = _1]
            |   flow_yaml_content(_r1, _r2)[_val = _1]
            |   omit[properties(_r1, _r2)[_a = _1]]
            >>  (separate(_r1, _r2) >> flow_yaml_content(_r1, _r2) | attr(ast::value_t()))
                [_val = handle_properties(_a, _1, phx::ref(anchors))]
            ;

        // [160]
        flow_json_node =
                -(omit[properties(_r1, _r2)[_a = _1]] > separate(_r1, _r2))
            >>  flow_json_content(_r1, _r2)
                [_val = handle_properties(_a, _1, phx::ref(anchors))]
            ;

        // [161]
        flow_node = YAML_PARSER_PRINT_INDENT (
                as<ast::value_t>{}[alias_node][_val = _1]
            |   flow_content(_r1, _r2)[_val = _1]
            |   omit[properties(_r1, _r2)[_a = _1]]
            >>  (separate(_r1, _r2) >> flow_content(_r1, _r2) | attr(ast::value_t()))
                [_val = handle_properties(_a, _1, phx::ref(anchors))]
            )
            ;

        BOOST_SPIRIT_DEBUG_NODES(
            (alias_node)
            (nb_double_char)
            (ns_double_char)
            (double_quoted)
            (double_text)
            (double_escaped)
            (double_break)
            (double_in_line)
            (double_next_line)
            (double_multi_line)
            (nb_single_char)
            (ns_single_char)
            (single_quoted)
            (single_text)
            (single_in_line)
            (single_next_line)
            (single_multi_line)
            (plain_first)
            (plain_safe)
            (plain_char)
            (plain)
            (plain_in_line)
            (plain_one_line)
            (plain_next_line)
            (plain_multi_line)
            (flow_sequence)
            (flow_seq_entries)
            (flow_seq_entry)
            (flow_mapping)
            (flow_map_entries)
            (flow_map_entry)
            (flow_map_explicit_entry)
            (flow_map_implicit_entry)
            (flow_map_yaml_key_entry)
            (flow_map_empty_key_entry)
            (flow_map_separate_value)
            (flow_map_json_key_entry)
            (flow_map_adjacent_value)
            (flow_pair)
            (flow_pair_entry)
            (flow_pair_yaml_key_entry)
            (flow_pair_json_key_entry)
            (implicit_yaml_key)
            (implicit_json_key)
            (flow_yaml_content)
            (flow_json_content)
            (flow_content)
            (flow_yaml_node)
            (flow_json_node)
            (flow_node)
        );
    }

} }

#endif
