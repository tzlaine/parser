/**
 *   Copyright (C) 2017 Zach Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef YAML_DETAIL_PARSE_IMPL_HPP
#define YAML_DETAIL_PARSE_IMPL_HPP

#include <boost/spirit/include/classic_position_iterator.hpp>


#define PARSE_YAML_IMPLEMENTATION()                                     \
namespace yaml { namespace parser {                                     \
                                                                        \
    boost::optional<std::vector<ast::value_t>> parse_yaml(              \
        std::istream & is,                                              \
        std::string const & source_file,                                \
        reporting_fn_t const & errors_callback,                         \
        reporting_fn_t const & warnings_callback                        \
    ) {                                                                 \
        std::string file;                                               \
        std::getline(is, file, '\0');                                   \
                                                                        \
        using base_iterator_type = std::string::const_iterator;         \
        base_iterator_type sfirst(file.begin());                        \
        base_iterator_type slast(file.end());                           \
                                                                        \
        using iterator_type = boost::spirit::classic::position_iterator< \
            base_iterator_type                                          \
        >;                                                              \
        iterator_type first(sfirst, slast);                             \
        iterator_type last;                                             \
        first.set_tabchars(1);                                          \
                                                                        \
        stream<iterator_type> p(                                        \
            source_file,                                                \
            errors_callback,                                            \
            warnings_callback                                           \
        );                                                              \
                                                                        \
        std::vector<ast::value_t> documents;                            \
        bool const success = boost::spirit::qi::parse(                  \
            first,                                                      \
            last,                                                       \
            p.yaml_stream,                                              \
            documents                                                   \
        );                                                              \
                                                                        \
        if (success) {                                                  \
            return boost::optional<std::vector<ast::value_t>>(          \
                std::move(documents)                                    \
            );                                                          \
        } else {                                                        \
            return boost::optional<std::vector<ast::value_t>>{};        \
        }                                                               \
    }                                                                   \
                                                                        \
} }

#if YAML_HEADER_ONLY
PARSE_YAML_IMPLEMENTATION()
#endif

#endif
