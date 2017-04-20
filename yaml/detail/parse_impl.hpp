/**
 *   Copyright (C) 2017 Zach Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if !defined(OMD_DETAIL_PARSE_IMPL_HPP)
#define OMD_DETAIL_PARSE_IMPL_HPP

#include <boost/spirit/include/classic_position_iterator.hpp>

#define PARSE_YAML_IMPLEMENTATION()                                     \
namespace omd { namespace yaml { namespace parser {                     \
                                                                        \
    bool parse_yaml(std::istream& is, ast::value_t& result, std::string const& source_file) \
    {                                                                   \
        std::string file;                                               \
        std::getline(is, file, '\0');                                   \
                                                                        \
        typedef std::string::const_iterator base_iterator_type;         \
        base_iterator_type sfirst(file.begin());                        \
        base_iterator_type slast(file.end());                           \
                                                                        \
        typedef boost::spirit::classic::position_iterator<base_iterator_type> \
            iterator_type;                                              \
        iterator_type first(sfirst, slast);                             \
        iterator_type last;                                             \
        first.set_tabchars(1);                                          \
                                                                        \
        omd::yaml::parser::yaml<iterator_type> p(source_file);          \
                                                                        \
        bool const retval =                                             \
            boost::spirit::qi::parse(first, last, p, result);           \
        if (retval)                                                     \
            ast::link_yaml(result);                                     \
        return retval;                                                  \
    }                                                                   \
                                                                        \
} } }

#if YAML_HEADER_ONLY
PARSE_YAML_IMPLEMENTATION()
#endif

#endif
