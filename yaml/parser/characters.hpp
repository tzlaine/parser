/**
 *   Copyright (C) 2017 Zach Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef YAML_PARSER_CHARACTERS_HPP
#define YAML_PARSER_CHARACTERS_HPP

#define BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
#define BOOST_SPIRIT_ACTIONS_ALLOW_ATTR_COMPAT

#include <yaml/ast.hpp>
#include <yaml/parser/error_handler.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_copy.hpp>

#include <string>


#ifdef BOOST_SPIRIT_DEBUG
#define YAML_PARSER_PRINT_INDENT eps(print_indent(_r1)) >>
#else
#define YAML_PARSER_PRINT_INDENT
#endif


namespace yaml { namespace parser {

    namespace detail {

#ifdef BOOST_SPIRIT_DEBUG
        struct print_indent
        {
            template <typename>
            struct result { using type = bool; };

            bool operator() (int n) const
            {
                std::cerr << n << " ======================================== " << n << "\n";
                return true;
            }
        };
#endif

    }

    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;

    enum class context_t {
        block_in, block_out,
        flow_in, flow_out,
        block_key, flow_key
    };

#ifdef BOOST_SPIRIT_DEBUG
    inline std::ostream & operator<< (std::ostream & os, context_t c)
    {
        switch (c) {
#define CASE(x) case context_t::x: return os << #x
        CASE(block_in); CASE(block_out);
        CASE(flow_in); CASE(flow_out);
        CASE(block_key); CASE(flow_key);
#undef CASE
        }
        return os;
    }
#endif

    enum class encoding_t {
        utf32_be, utf32_le,
        utf16_be, utf16_le,
        utf8
    };

    inline std::ostream & operator<< (std::ostream & os, encoding_t c)
    {
        switch (c) {
        case encoding_t::utf32_be: return os << "UTF-32 big-endian";
        case encoding_t::utf32_le: return os << "UTF-32 little-endian";
        case encoding_t::utf16_be: return os << "UTF-16 big-endian";
        case encoding_t::utf16_le: return os << "UTF-16 little-endian";
        case encoding_t::utf8: return os << "UTF-8";
        }
        return os;
    }

    using uchar_t = boost::uint32_t; // Unicode code point

    template <typename Iterator>
    struct characters
    {
        characters ();

        qi::rule<Iterator, encoding_t()> full_bom;

        qi::rule<Iterator, char()> printable;
        qi::rule<Iterator> bom;
        qi::rule<Iterator, char()> nb_char;
        qi::rule<Iterator, char()> ns_char;
        qi::rule<Iterator, std::string()> uri_char;
        qi::rule<Iterator, std::string()> tag_char;
        qi::rule<Iterator, std::string()> esc_char;
    };

} }

#endif
