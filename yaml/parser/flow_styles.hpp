/**
 *   Copyright (C) 2017 Zach Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef YAML_PARSER_FLOW_STYLES_HPP
#define YAML_PARSER_FLOW_STYLES_HPP

#include <yaml/parser/basic_structures.hpp>


namespace yaml { namespace parser {

    template <typename Iterator>
    struct flow_styles
    {
        flow_styles ();

        basic_structures<Iterator> basic_structures_;

        qi::rule<Iterator, ast::alias_t()> alias_node;

        qi::rule<Iterator, std::string()> nb_double_char;
        qi::rule<Iterator, std::string()> ns_double_char;
        qi::rule<Iterator, std::string(int, context_t)> double_quoted;
        qi::rule<Iterator, std::string(int, context_t)> double_text;
        qi::rule<Iterator, std::string(int)> double_escaped;
        qi::rule<Iterator, std::string(int)> double_break;
        qi::rule<Iterator, std::string()> double_in_line;
        qi::rule<Iterator, std::string(int)> double_next_line;
        qi::rule<Iterator, std::string(int)> double_multi_line;

        qi::rule<Iterator, char()> nb_single_char;
        qi::rule<Iterator, char()> ns_single_char;
        qi::rule<Iterator, std::string(int, context_t)> single_quoted;
        qi::rule<Iterator, std::string(int, context_t)> single_text;
        qi::rule<Iterator, std::string()> single_in_line;
        qi::rule<Iterator, std::string(int)> single_next_line;
        qi::rule<Iterator, std::string(int)> single_multi_line;

        qi::rule<Iterator, char(context_t)> plain_first;
        qi::rule<Iterator, char(context_t)> plain_safe;
        qi::rule<Iterator, std::string(context_t)> plain_char;
        qi::rule<Iterator, std::string(int, context_t)> plain;
        qi::rule<Iterator, std::string(context_t)> plain_in_line;
        qi::rule<Iterator, std::string(context_t)> plain_one_line;
        qi::rule<Iterator, std::string(int, context_t)> plain_next_line;
        qi::rule<Iterator, std::string(int, context_t)> plain_multi_line;

        qi::rule<Iterator, ast::seq_t(int, context_t)> flow_sequence;
        qi::rule<Iterator, ast::seq_t(int, context_t)> flow_seq_entries;
        qi::rule<Iterator, ast::value_t(int, context_t)> flow_seq_entry;

        qi::rule<Iterator, ast::map_t(int, context_t)> flow_mapping;
        qi::rule<Iterator, ast::map_t(int, context_t)> flow_map_entries;
        qi::rule<Iterator, ast::map_element_t(int, context_t)> flow_map_entry;
        qi::rule<Iterator, ast::map_element_t(int, context_t)> flow_map_explicit_entry;
        qi::rule<Iterator, ast::map_element_t(int, context_t)> flow_map_implicit_entry;

        qi::rule<Iterator, ast::map_element_t(int, context_t)> flow_map_yaml_key_entry;
        qi::rule<Iterator, ast::map_element_t(int, context_t)> flow_map_empty_key_entry;
        qi::rule<Iterator, ast::value_t(int, context_t)> flow_map_separate_value;
        qi::rule<Iterator, ast::map_element_t(int, context_t)> flow_map_json_key_entry;
        qi::rule<Iterator, ast::value_t(int, context_t)> flow_map_adjacent_value;
        qi::rule<Iterator, ast::map_t(int, context_t)> flow_pair;
        qi::rule<Iterator, ast::map_element_t(int, context_t)> flow_pair_entry;
        qi::rule<Iterator, ast::map_element_t(int, context_t)> flow_pair_yaml_key_entry;
        qi::rule<Iterator, ast::map_element_t(int, context_t)> flow_pair_json_key_entry;
        qi::rule<Iterator, ast::value_t(context_t)> implicit_yaml_key;
        qi::rule<Iterator, ast::value_t(context_t)> implicit_json_key;

        qi::rule<Iterator, ast::value_t(int, context_t)> flow_yaml_content;
        qi::rule<Iterator, ast::value_t(int, context_t)> flow_json_content;
        qi::rule<Iterator, ast::value_t(int, context_t)> flow_content;
        qi::rule<Iterator, ast::value_t(int, context_t)> flow_yaml_node;
        qi::rule<Iterator, ast::value_t(int, context_t)> flow_json_node;
        qi::rule<Iterator, ast::value_t(int, context_t)> flow_node;
    };

} }

#endif
