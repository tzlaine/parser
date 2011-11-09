/**
 *   Copyright (C) 2010, 2011 Object Modeling Designs
 *   Copyright (c) 2010 Joel de Guzman
 */

#if !defined(OMD_PARSER_SCALAR_HPP)
#define OMD_PARSER_SCALAR_HPP

#define BOOST_SPIRIT_NO_PREDEFINED_TERMINALS

#include <string>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_function.hpp>

#include "../ast.hpp"         // our AST
#include "error_handler.hpp"  // Our Error Handler

namespace omd { namespace parser
{
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;

    typedef boost::uint32_t uchar; // a unicode code point

    // The indicators
    char const* indicators = "-?:,[]{}#&*!|>\\\"%@`";

    // These are not allowed as first plain-style character
    char const* unsafe_first = ",[]{}#&*!|>\\\"%@`";

    template <typename Iterator>
    struct unicode_string : qi::grammar<Iterator, std::string()>
    {
        unicode_string();

        qi::rule<Iterator, void(std::string&)> char_esc;
        qi::rule<Iterator, std::string()> char_lit;
        qi::rule<Iterator, std::string()> double_quoted;
        qi::rule<Iterator, std::string()> single_quoted;
        qi::rule<Iterator, std::string()> unquoted;
        qi::rule<Iterator, std::string()> start;
    };

    template <typename Iterator>
    struct scalar : qi::grammar<Iterator, ast::value_t()>
    {
        scalar();

        qi::rule<Iterator, ast::value_t()> value;
        unicode_string<Iterator> string_value;
        qi::rule<Iterator, int()> integer_value;
        qi::symbols<char, bool> bool_value;
        qi::rule<Iterator, ast::null_t() > null_value;
    };
}}

#endif
