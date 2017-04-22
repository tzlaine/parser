/**
 *   Copyright (C) 2010, 2011, 2012 Object Modeling Designs
 *   consultomd.com
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if !defined(OMD_PARSER_FLOW_DEF_HPP)
#define OMD_PARSER_FLOW_DEF_HPP

#include <yaml/parser/flow.hpp>

#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/phoenix/object/construct.hpp>
#include <boost/spirit/include/phoenix_container.hpp>
#include <boost/spirit/include/phoenix_statement.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

namespace omd { namespace yaml { namespace parser
{
    template <typename Iterator>
    white_space<Iterator>::white_space()
      : white_space::base_type(start)
    {
        qi::char_type char_;
        qi::eol_type eol;
        qi::space_type space;

        start =
                space                           // tab/space/cr/lf
            |   '#' >> *(char_ - eol) >> eol    // comments
            ;
    }

    template <typename Iterator>
    flow<Iterator>::flow(
        int& indent,
        qi::symbols<char>& anchors,
        std::string const& source_file)
      : flow::base_type(flow_start),
        scalar_value(indent, anchors),
        error_handler(error_handler_t(source_file))
    {
        qi::_1_type _1;
        qi::_2_type _2;
        qi::_3_type _3;
        qi::_4_type _4;
        qi::_a_type _a;
        qi::_b_type _b;
        qi::_val_type _val;
        qi::char_type char_;
        qi::lit_type lit;
        qi::eps_type eps;
        qi::omit_type omit;
        qi::no_skip_type no_skip;
        using qi::as;

        namespace phx = boost::phoenix;
        auto ins = phx::insert(_val, _1);
        phx::function<qi::symbols<char>::adder> add_anchor(anchors.add);
        using boost::phoenix::construct;

        auto & separate = scalar_value.string_value.separate;
        auto & plain_safe = scalar_value.string_value.plain_safe;
        auto & plain = scalar_value.string_value.unquoted;
        auto & single_quoted = scalar_value.string_value.single_quoted;
        auto & double_quoted = scalar_value.string_value.double_quoted;

        flow_start =
                top_anchored_value
            |   ("!!map" > flow_mapping)
            |   ("!!seq" > flow_sequence)
            |   flow_mapping
            |   flow_sequence
            ;

        top_anchored_value %=
                '&'
            >>  (+~char_(" \n\r\t,{}[]")) [ add_anchor(_1) ]
            >>  flow_start
            ;

        flow_value =
                anchored_value
            |   scalar_value
            |   flow_mapping
            |   flow_sequence
            ;

        anchored_value %=
                '&'
            >>  (+~char_(" \n\r\t,{}[]")) [ add_anchor(_1) ]
            >>  flow_value
            ;

        // 7.4.1 Flow Sequences

        // [137]
        flow_sequence =
            '[' >> -flow_seq_entries >> ']'
            ;

        // [138]
        flow_seq_entries =
            flow_seq_entry % ',' >> -omit[char_(",")]
            ;

        // [139]
        flow_seq_entry =
                as<ast::value_t>()[flow_pair]
            |   flow_value//TODO flow_node
            ;

        // 7.4.2 Flow Mappings

        // [140]
        flow_mapping =
            '{' >> -flow_map_entries >> '}'
            ;

        // [141]
        flow_map_entries =
            flow_map_entry[ins] % ',' >> -omit[char_(",")]
            ;

        // [142]
        flow_map_entry %=
                '?' >> flow_map_explicit_entry
            |   flow_map_implicit_entry
            ;

        // [143]
        flow_map_explicit_entry =
                flow_map_implicit_entry[_val = _1]
            |   eps[_val = ast::object_element_t()]
            ;

        // [144]
        flow_map_implicit_entry %=
                flow_map_yaml_key_entry
            |   flow_map_empty_key_entry
            |   flow_map_json_key_entry
            ;

        // [145]
        flow_map_yaml_key_entry = (
                flow_value/*TODO flow_yaml_node*/[_a = _1]
            >>  -flow_map_separate_value[_b = _1]
            )
            [_val = construct<ast::object_element_t>(_a, _b)]
            ;

        // [146]
        flow_map_empty_key_entry =
            flow_map_separate_value
            [_val = construct<ast::object_element_t>(ast::null_t(), _1)]
            ;

        // [147]
        flow_map_separate_value =
                ':' >> !no_skip[plain_safe]
            >>  -flow_value/*TODO flow_node*/[_val = _1]
            ;

        // [148]
        flow_map_json_key_entry = (
                flow_value/*TODO flow_json_node*/[_a = _1]
            >>  -flow_map_adjacent_value[_b = _1]
            )
            [_val = construct<ast::object_element_t>(_a, _b)]
            ;

        // [149]
        flow_map_adjacent_value =
            ':' >> -flow_value/*TODO flow_node*/[_val = _1]
            ;

        // [150]
        flow_pair =
                '?' >> flow_map_explicit_entry[ins]
            |   flow_pair_entry[ins]
            ;

        // [151]
        flow_pair_entry =
                flow_pair_yaml_key_entry
            |   flow_map_empty_key_entry
            |   flow_pair_json_key_entry
            ;

        // [152]
        flow_pair_yaml_key_entry =
            (implicit_yaml_key[_a = _1] >> flow_map_separate_value[_b = _1])
            [_val = construct<ast::object_element_t>(_a, _b)]
            ;

        // [153]
        flow_pair_json_key_entry %=
            implicit_json_key >> flow_map_adjacent_value
            ;

        // [154]
        implicit_yaml_key =
            flow_value//TODO flow_yaml_node
            ;

        // [155]
        implicit_json_key =
            flow_value//TODO flow_json_node
            ;

        // 7.5 Flow Nodes

        // [156]
        flow_yaml_content =
            plain
            ;

        // [157]
        flow_json_content =
                flow_sequence
            |   flow_mapping
            |   single_quoted
            |   double_quoted
            ;

        // [158]
        flow_content =
                flow_yaml_content
            |   flow_json_content
            ;

#if 0 // TODO
        // [159]
        flow_yaml_node =
                alias_node
            |   flow_yaml_content
            |   omit[properties] >> (omit[separate] >> flow_yaml_content | eps)
            ;

        // [160]
        flow_json_node =
            -properties >> flow_json_content
            ;

        // [161]
        flow_node =
                alias_node
            |   flow_content
            |   omit[properties] >> (omit[separate] >> flow_content | eps)
            ;            
#endif

        BOOST_SPIRIT_DEBUG_NODES(
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
        );

        BOOST_SPIRIT_DEBUG_NODES(
            (flow_start)
            (flow_value)
            (anchored_value)
            (top_anchored_value)
        );

        qi::on_error<qi::fail>(flow_start, error_handler(_1, _2, _3, _4));
    }
}}}

#endif
