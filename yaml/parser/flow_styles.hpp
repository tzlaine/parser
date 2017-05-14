/**
 *   Copyright (C) 2017 Zach Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef YAML_PARSER_FLOW_STYLES_HPP
#define YAML_PARSER_FLOW_STYLES_HPP

#include <yaml/parser/parser_fwd.hpp>
#include <yaml/parser/basic_structures.hpp>


namespace yaml { namespace parser {

    struct flow_styles_t
    {
        explicit flow_styles_t (
            boost::phoenix::function<error_handler_t> & error_handler,
            bool verbose
        );

        basic_structures_t basic_structures_;

        qi::symbols<char, anchor_t> anchors;

        qi::rule<iterator_t, ast::alias_t()> alias_node;

        qi::rule<iterator_t, parsed_uchar_t()> nb_double_char;
        qi::rule<iterator_t, parsed_uchar_t()> ns_double_char;
        qi::rule<iterator_t, std::string(int, context_t)> double_quoted;
        qi::rule<iterator_t, std::string(int, context_t)> double_text;
        qi::rule<iterator_t, std::string(int)> double_escaped;
        qi::rule<iterator_t, std::string(int)> double_break;
        qi::rule<iterator_t, std::string(), qi::locals<std::string>> double_in_line;
        qi::rule<iterator_t, std::string(int), qi::locals<std::string>> double_next_line;
        qi::rule<iterator_t, std::string(int)> double_multi_line;

        qi::rule<iterator_t, parsed_uchar_t()> nb_single_char;
        qi::rule<iterator_t, parsed_uchar_t()> ns_single_char;
        qi::rule<iterator_t, std::string(int, context_t)> single_quoted;
        qi::rule<iterator_t, std::string(int, context_t)> single_text;
        qi::rule<iterator_t, std::string(), qi::locals<std::string>> single_in_line;
        qi::rule<iterator_t, std::string(int), qi::locals<std::string>> single_next_line;
        qi::rule<iterator_t, std::string(int)> single_multi_line;

        qi::rule<iterator_t, std::string(context_t)> plain_first;
        qi::rule<iterator_t, parsed_uchar_t(context_t)> plain_safe;
        qi::rule<iterator_t, std::string(context_t)> plain_char;
        qi::rule<iterator_t, std::string(int, context_t)> plain;
        qi::rule<iterator_t, std::string(context_t)> plain_in_line;
        qi::rule<iterator_t, std::string(context_t)> plain_one_line;
        qi::rule<iterator_t, std::string(int, context_t)> plain_next_line;
        qi::rule<iterator_t, std::string(int, context_t)> plain_multi_line;

        qi::rule<iterator_t, ast::seq_t(int, context_t)> flow_sequence;
        qi::rule<iterator_t, ast::seq_t(int, context_t)> flow_seq_entries;
        qi::rule<iterator_t, ast::value_t(int, context_t)> flow_seq_entry;

        qi::rule<iterator_t, ast::map_t(int, context_t)> flow_mapping;
        qi::rule<iterator_t, ast::map_t(int, context_t)> flow_map_entries;
        qi::rule<iterator_t, ast::map_element_t(int, context_t)> flow_map_entry;
        qi::rule<iterator_t, ast::map_element_t(int, context_t)> flow_map_explicit_entry;
        qi::rule<iterator_t, ast::map_element_t(int, context_t)> flow_map_implicit_entry;

        qi::rule<iterator_t, ast::map_element_t(int, context_t)> flow_map_yaml_key_entry;
        qi::rule<iterator_t, ast::map_element_t(int, context_t)> flow_map_empty_key_entry;
        qi::rule<iterator_t, ast::value_t(int, context_t)> flow_map_separate_value;
        qi::rule<iterator_t, ast::map_element_t(int, context_t)> flow_map_json_key_entry;
        qi::rule<iterator_t, ast::value_t(int, context_t)> flow_map_adjacent_value;
        qi::rule<iterator_t, ast::map_t(int, context_t), qi::locals<iterator_range_t, iterator_range_t>> flow_pair;
        qi::rule<iterator_t, ast::map_element_t(int, context_t)> flow_pair_entry;
        qi::rule<iterator_t, ast::map_element_t(int, context_t)> flow_pair_yaml_key_entry;
        qi::rule<iterator_t, ast::map_element_t(int, context_t)> flow_pair_json_key_entry;
        qi::rule<iterator_t, ast::value_t(context_t)> implicit_yaml_key;
        qi::rule<iterator_t, ast::value_t(context_t)> implicit_json_key;

        qi::rule<iterator_t, ast::value_t(int, context_t)> flow_yaml_content;
        qi::rule<iterator_t, ast::value_t(int, context_t)> flow_json_content;
        qi::rule<iterator_t, ast::value_t(int, context_t)> flow_content;

        qi::rule<
            iterator_t,
            ast::value_t(int, context_t),
            qi::locals<parser_properties_t>
        > flow_yaml_node;

        qi::rule<
            iterator_t,
            ast::value_t(int, context_t),
            qi::locals<parser_properties_t>
        > flow_json_node;

        qi::rule<
            iterator_t,
            ast::value_t(int, context_t),
            qi::locals<parser_properties_t>
        > flow_node;
    };

} }

#if YAML_HEADER_ONLY
#include <yaml/parser/flow_styles_def.hpp>
#endif

#endif
