/**
 *   Copyright (C) 2010, 2011, 2012 Object Modeling Designs : consultomd.com
 *   Copyright (c) 2010 Joel de Guzman
 *   Copyright (C) 2017 Zach Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef YAML_PARSER_CHARACTERS_DEF_HPP
#define YAML_PARSER_CHARACTERS_DEF_HPP

#include <yaml/parser/characters.hpp>

#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/regex/pending/unicode_iterator.hpp>


namespace yaml { namespace parser {

    namespace detail {

        struct push_utf8
        {
            template <typename S, typename C>
            struct result { using type = void; };

            void operator() (std::string & utf8, uchar_t code_point) const
            {
                using insert_iter = std::back_insert_iterator<std::string>;
                insert_iter out_iter(utf8);
                boost::utf8_output_iterator<insert_iter> utf8_iter(out_iter);
                *utf8_iter++ = code_point;
            }
        };

        struct push_esc
        {
            template <typename S, typename C>
            struct result { using type = void; };

            void operator() (std::string & utf8, uchar_t c) const
            {
                switch (c)
                {
                    case ' ':  utf8 += ' ';                break;
                    case '\t': utf8 += '\t';               break;
                    case '0':  utf8 += '\0';               break;
                    case 'a':  utf8 += 0x7;                break;
                    case 'b':  utf8 += 0x8;                break;
                    case 't':  utf8 += '\t';               break;
                    case 'n':  utf8 += 0xa;                break;
                    case 'v':  utf8 += '\v';               break;
                    case 'f':  utf8 += '\f';               break;
                    case 'r':  utf8 += '\r';               break;
                    case 'e':  utf8 += 0x1b;               break;
                    case '"':  utf8 += '"';                break;
                    case '/':  utf8 += '/';                break;
                    case '\\': utf8 += '\\';               break;

                    case '_':  push_utf8()(utf8, 0xa0);    break;
                    case 'N':  push_utf8()(utf8, 0x85);    break;
                    case 'L':  push_utf8()(utf8, 0x2028);  break;
                    case 'P':  push_utf8()(utf8, 0x2029);  break;
                }
            }
        };

    }

    template <typename Iterator>
    characters<Iterator>::characters ()
    {
        qi::byte_type byte_;
        qi::char_type char_;
        qi::_val_type _val;
        qi::_1_type _1;
        qi::lit_type lit;
        qi::blank_type blank;
        qi::eol_type eol;
        qi::alnum_type alnum;
        qi::hex_type hex;
        qi::eps_type eps;

        namespace phx = boost::phoenix;
        using qi::copy;
        using qi::uint_parser;
        using phx::function;
        using phx::ref;

        uint_parser<uchar_t, 16, 4, 4> hex4;
        uint_parser<uchar_t, 16, 8, 8> hex8;
        function<detail::push_utf8> push_utf8;
        function<detail::push_esc> push_esc;

        // 5.2. Character Encodings

        full_bom =
                byte_('\x00') >> byte_('\x00') >> byte_('\xfe') >> byte_('\xff') [_val = encoding_t::utf32_be]
            |   byte_('\x00') >> byte_('\x00') >> byte_('\x00') >> byte_ [_val = encoding_t::utf32_be]
            |   byte_('\xff') >> byte_('\xfe') >> byte_('\x00') >> byte_('\x00') [_val = encoding_t::utf32_le]
            |   byte_ >> byte_('\x00') >> byte_('\x00') >> byte_('\x00') [_val = encoding_t::utf32_le]
            |   byte_('\xfe') >> byte_('\xff') [_val = encoding_t::utf16_be]
            |   byte_('\x00') >> byte_ [_val = encoding_t::utf16_be]
            |   byte_('\xff') >> byte_('\xfe') [_val = encoding_t::utf16_le]
            |   byte_ >> byte_('\x00') [_val = encoding_t::utf16_le]
            |   byte_('\xef') >> byte_('\xbb') >> byte_('\xbf') [_val = encoding_t::utf8]
            ;

        // [1]
        printable =
            char_("\t\n\f\x20-\x7e") // TODO: This should properly have other chars in it once we can parse UTf8.
            ;

        // [2]
        nb_json =
            char_("\t\x20-\x7e") // TODO: This should properly be \t | anything >= \x20
            ;

        // [3]
        bom =
            byte_('\xfe') >> byte_('\xff')
            ;

        // 5.4. Line Break Characters

        // [27]
        nb_char =
            printable - eol - bom
            ;

        // 5.5. White Space Characters

        // [34]
        ns_char =
            printable - eol - bom - blank
            ;

        // 5.6. Miscellaneous Characters

        // [38]
        auto word_char = copy(alnum | char_("-"));

        // [39]
        uri_char =
                char_("%") >> hex[push_utf8(_val, _1)]
            |   word_char
            |   char_("#;/?:@&=+$,_.!~*'()[]")
            ;

        // [40]
        tag_char =
            uri_char - char_("!,[]{}") // '!' | flow_indicator [23]
            ;

        // 5.7. Escaped Characters

        // [62]
        esc_char =
                '\\'
            >>  (
                    ('x' > hex)                     [push_utf8(_val, _1)]
                |   ('u' > hex4)                    [push_utf8(_val, _1)]
                |   ('U' > hex8)                    [push_utf8(_val, _1)]
                |   char_("0abtnvfre\"/\\N_LP\t ")  [push_esc(_val, _1)]
                )
            ;

        BOOST_SPIRIT_DEBUG_NODES(
            (printable)
#if 1
            (nb_json)
#endif
            (bom)
            // TODO: Separate out the naming of these things from debugging
            // them; give them user-friendly names.
#if 0
            (nb_char)
            (ns_char)
#endif
            (uri_char)
            (tag_char)
            (esc_char)
        );
    }

} }

#endif
