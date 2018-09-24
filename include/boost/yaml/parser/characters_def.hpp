/**
 *   Copyright (C) 2010, 2011, 2012 Object Modeling Designs : consultomd.com
 *   Copyright (c) 2010 Joel de Guzman
 *   Copyright (C) 2017 Zach Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_YAML_PARSER_CHARACTERS_DEF_HPP
#define BOOST_YAML_PARSER_CHARACTERS_DEF_HPP

#include <boost/yaml/parser/characters.hpp>

#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/regex/pending/unicode_iterator.hpp>
#include <boost/phoenix/object/construct.hpp>


namespace boost { namespace yaml { namespace parser {

    namespace detail {

        struct push_esc
        {
            template <typename, typename>
            struct result { using type = void; };

            void operator() (parsed_uchar_t & to, uchar_t from) const
            {
                switch (from)
                {
                    case ' ':  to.value_ = ' ';     break;
                    case '\t': to.value_ = '\t';    break;
                    case '0':  to.value_ = '\0';    break;
                    case 'a':  to.value_ = 0x7;     break;
                    case 'b':  to.value_ = 0x8;     break;
                    case 't':  to.value_ = '\t';    break;
                    case 'n':  to.value_ = 0xa;     break;
                    case 'v':  to.value_ = '\v';    break;
                    case 'f':  to.value_ = '\f';    break;
                    case 'r':  to.value_ = '\r';    break;
                    case 'e':  to.value_ = 0x1b;    break;
                    case '"':  to.value_ = '"';     break;
                    case '/':  to.value_ = '/';     break;
                    case '\\': to.value_ = '\\';    break;
                    case '_':  to.value_ = 0xa0;    break;
                    case 'N':  to.value_ = 0x85;    break;
                    case 'L':  to.value_ = 0x2028;  break;
                    case 'P':  to.value_ = 0x2029;  break;
                }
            }
        };

    }

    BOOST_YAML_HEADER_ONLY_INLINE
    characters_t::characters_t (bool verbose)
    {
        qi::unicode::char_type char_;
        qi::_val_type _val;
        qi::_1_type _1;
        qi::blank_type blank;
        qi::eol_type eol;
        qi::unicode::alnum_type alnum;
        qi::hex_type hex;
        qi::eps_type eps;

        namespace phx = boost::phoenix;
        using qi::copy;
        using qi::uint_parser;
        using phx::construct;
        using phx::function;
        using phx::ref;

        uint_parser<uchar_t, 16, 4, 4> hex4;
        uint_parser<uchar_t, 16, 8, 8> hex8;
        function<detail::push_esc> push_esc;

        // 5.2. Character Encodings

        // [1]
        printable =
                char_("\t\n\f") | char_(U'\x20', U'\x7e')                                // 8 bit
            |   char_(U'\x85') | char_(U'\xa0', U'\ud7ff') | char_(U'\ue000', U'\ufffd') // 16 bit
            |   char_(U'\U00010000', U'\U0010ffff')                                      // 32 bit
            ;

        // [2]
        nb_json =
            char_(U'\t') | char_(U'\x20', U'\U0010ffff')
            ;

        // [3]
        bom =
            char_(0xfeff)
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
        auto word_char = copy(alnum | char_('-'));

        // [39]
        uri_char =
                char_('%') >> hex
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
                    ('x' > hex)                     [_val = construct<parsed_uchar_t>(_1)]
                |   ('u' > hex4)                    [_val = construct<parsed_uchar_t>(_1)]
                |   ('U' > hex8)                    [_val = construct<parsed_uchar_t>(_1)]
                |   char_("0abtnvfre\"/\\N_LP\t ")  [push_esc(_val, _1)]
                )
            ;

        // TODO: Separate out the naming of these things from debugging
        // them; give them user-friendly names.
        if (verbose) {
            BOOST_SPIRIT_DEBUG_NODES(
                (printable)
                (nb_json)
                (bom)
                (nb_char)
                (ns_char)
                (uri_char)
                (tag_char)
                (esc_char)
            );
        }
    }

}}}

#endif
