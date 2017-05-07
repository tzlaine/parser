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

    namespace detail {

        struct handle_properties
        {
            template <typename, typename, typename>
            struct result { using type = ast::value_t; };

            template <typename T>
            ast::value_t operator() (
                ast::properties_t const & properties,
                T const & x,
                qi::symbols<char, ast::alias_t> & anchors
            ) const {
                if (properties.anchor_ != "") {
                    std::shared_ptr<ast::value_t> anchor_ptr(new ast::value_t(x));
                    // TODO: Emit a warning when an anchor is redefined.
                    anchors.remove(properties.anchor_);
                    anchors.add(
                        properties.anchor_,
                        ast::alias_t(properties.anchor_, anchor_ptr)
                    );
                }
                if (properties)
                    return ast::value_t(ast::properties_node_t(properties, ast::value_t(x)));
                return ast::value_t(x);
            }
        };

    }

    template <typename CharIter>
    struct flow_styles_t
    {
        using iterator_t = pos_iterator<CharIter>;

        explicit flow_styles_t (boost::phoenix::function<error_handler_t> const & error_handler);

        basic_structures_t<CharIter> basic_structures_;

        qi::symbols<char, ast::alias_t> anchors;

        qi::rule<iterator_t, ast::alias_t()> alias_node;

        qi::rule<iterator_t, std::string()> nb_double_char;
        qi::rule<iterator_t, std::string()> ns_double_char;
        qi::rule<iterator_t, std::string(int, context_t)> double_quoted;
        qi::rule<iterator_t, std::string(int, context_t)> double_text;
        qi::rule<iterator_t, std::string(int)> double_escaped;
        qi::rule<iterator_t, std::string(int)> double_break;
        qi::rule<iterator_t, std::string()> double_in_line;
        qi::rule<iterator_t, std::string(int)> double_next_line;
        qi::rule<iterator_t, std::string(int)> double_multi_line;

        qi::rule<iterator_t, char()> nb_single_char;
        qi::rule<iterator_t, char()> ns_single_char;
        qi::rule<iterator_t, std::string(int, context_t)> single_quoted;
        qi::rule<iterator_t, std::string(int, context_t)> single_text;
        qi::rule<iterator_t, std::string()> single_in_line;
        qi::rule<iterator_t, std::string(int)> single_next_line;
        qi::rule<iterator_t, std::string(int)> single_multi_line;

        qi::rule<iterator_t, char(context_t)> plain_first;
        qi::rule<iterator_t, char(context_t)> plain_safe;
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
        qi::rule<iterator_t, ast::map_t(int, context_t)> flow_pair;
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
            qi::locals<ast::properties_t>
        > flow_yaml_node;

        qi::rule<
            iterator_t,
            ast::value_t(int, context_t),
            qi::locals<ast::properties_t>
        > flow_json_node;

        qi::rule<
            iterator_t,
            ast::value_t(int, context_t),
            qi::locals<ast::properties_t>
        > flow_node;
    };

} }

#endif
