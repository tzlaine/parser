/**
 *   Copyright (C) 2010, 2011, 2012 Object Modeling Designs
 *   consultomd.com
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if !defined(OMD_PARSER_FLOW_HPP)
#define OMD_PARSER_FLOW_HPP

#define BOOST_SPIRIT_NO_PREDEFINED_TERMINALS

#include <string>
#include <yaml/parser/scalar.hpp>

namespace omd { namespace yaml { namespace parser
{
    template <typename Iterator>
    struct white_space : qi::grammar<Iterator>
    {
        white_space();
        qi::rule<Iterator> start;
    };

    template <typename Iterator>
    struct flow : qi::grammar<Iterator, ast::value_t(), white_space<Iterator> >
    {
        flow(
            int& indent,
            qi::symbols<char>& anchors,
            std::string const& source_file = "");

        using white_space_t = white_space<Iterator>;

        using object_element_rule_locals_t = qi::rule<
            Iterator,
            ast::object_element_t(),
            qi::locals<ast::value_t, ast::value_t>,
            white_space_t
        >;

        qi::rule<Iterator, ast::array_t(), white_space_t> flow_sequence;
        qi::rule<Iterator, ast::array_t(), white_space_t> flow_seq_entries;
        qi::rule<Iterator, ast::value_t(), white_space_t> flow_seq_entry;
        qi::rule<Iterator, ast::object_t(), white_space_t> flow_mapping;
        qi::rule<Iterator, ast::object_t(), white_space_t> flow_map_entries;
        qi::rule<Iterator, ast::object_element_t(), white_space_t> flow_map_entry;
        qi::rule<Iterator, ast::object_element_t(), white_space_t> flow_map_explicit_entry;
        qi::rule<Iterator, ast::object_element_t(), white_space_t> flow_map_implicit_entry;
        object_element_rule_locals_t flow_map_yaml_key_entry;
        qi::rule<Iterator, ast::object_element_t(), white_space_t> flow_map_empty_key_entry;
        qi::rule<Iterator, ast::value_t(), white_space_t> flow_map_separate_value;
        object_element_rule_locals_t flow_map_json_key_entry;
        qi::rule<Iterator, ast::value_t(), white_space_t> flow_map_adjacent_value;
        qi::rule<Iterator, ast::object_t(), white_space_t> flow_pair;
        qi::rule<Iterator, ast::object_element_t(), white_space_t> flow_pair_entry;
        object_element_rule_locals_t flow_pair_yaml_key_entry;
        qi::rule<Iterator, ast::object_element_t(), white_space_t> flow_pair_json_key_entry;
        qi::rule<Iterator, ast::value_t(), white_space_t> implicit_yaml_key;
        qi::rule<Iterator, ast::value_t(), white_space_t> implicit_json_key;
        qi::rule<Iterator, ast::value_t(), white_space_t> flow_yaml_content;
        qi::rule<Iterator, ast::value_t(), white_space_t> flow_json_content;
        qi::rule<Iterator, ast::value_t(), white_space_t> flow_content;
        qi::rule<Iterator, ast::value_t(), white_space_t> flow_yaml_node;
        qi::rule<Iterator, ast::value_t(), white_space_t> flow_json_node;
        qi::rule<Iterator, ast::value_t(), white_space_t> flow_node;

        scalar<Iterator> scalar_value;

        typedef omd::yaml::parser::error_handler<Iterator> error_handler_t;
        boost::phoenix::function<error_handler_t> const error_handler;
    };
}}}

#endif
