/**
 *   Copyright (C) 2010, 2011, 2012 Object Modeling Designs : consultomd.com
 *   Copyright (c) 2010 Joel de Guzman
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if !defined(OMD_PARSER_SCALAR_HPP)
#define OMD_PARSER_SCALAR_HPP

#define BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
#define BOOST_SPIRIT_ACTIONS_ALLOW_ATTR_COMPAT

#include <string>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_copy.hpp>

#include <yaml/ast.hpp>                   // our AST
#include <yaml/parser/error_handler.hpp>  // Our Error Handler

namespace omd { namespace yaml { namespace parser
{
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;

    typedef boost::uint32_t uchar; // a unicode code point

    template <typename Iterator>
    struct unicode_string : qi::grammar<Iterator, std::string()>
    {
        int& indent;
        unicode_string(int& indent);

        qi::rule<Iterator, void(std::string&)> escape;
        qi::rule<Iterator, void(std::string&)> char_esc;
        qi::rule<Iterator, std::string()> char_lit;
        qi::rule<Iterator, std::string()> double_quoted;
        qi::rule<Iterator, std::string()> single_quoted;
        qi::rule<Iterator, std::string()> unquoted_char;
        qi::rule<Iterator, std::string()> unquoted;
        qi::rule<Iterator, std::string()> explicit_;
        qi::rule<Iterator, std::string()> unicode_start;
        qi::rule<Iterator, std::string()> separate;
        qi::rule<Iterator, std::string()> plain_safe;
        qi::rule<Iterator, std::string()> uri_char;
        qi::rule<Iterator, std::string()> tag_char;
        qi::rule<Iterator, std::string()> anchor_char;
    };

    template <typename Iterator>
    struct scalar : qi::grammar<Iterator, ast::value_t()>
    {
        scalar(int& indent, qi::symbols<char>& symbol_table);

        qi::rule<Iterator, ast::value_t()> scalar_value;
        qi::rule<Iterator, ast::value_t()> scalar_value_no_strings;
        qi::rule<Iterator, ast::value_t()> map_key;
        unicode_string<Iterator> string_value;
        qi::rule<Iterator, int()> int_value;
        qi::rule<Iterator, double()> strict_float_value;
        qi::rule<Iterator, double()> float_value;
        qi::symbols<char, bool> bool_value_;
        qi::rule<Iterator, bool()> bool_value;
        qi::rule<Iterator, ast::null_t() > null_value;
        qi::rule<Iterator, ast::alias_t() > alias_node;
        qi::rule<Iterator, std::string() > anchor_name;
        qi::rule<Iterator, ast::anchored_object_t() > anchored_value;
        qi::rule<Iterator, ast::anchored_object_t() > anchored_string;
        qi::rule<Iterator, std::string()> tag_handle;

        qi::rule<
            Iterator,
            ast::properties_t(),
            qi::locals<ast::string_t, ast::string_t>
        > properties;

        qi::rule<Iterator, std::string()> tag_property;
        qi::rule<Iterator, std::string()> anchor_property;
    };
}}}

#endif
