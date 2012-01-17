/**
 *   Copyright (C) 2010, 2011 Object Modeling Designs
 *   Copyright (c) 2010 Joel de Guzman
 */

#if !defined(OMD_COMMON_SCALAR_DEF_HPP)
#define OMD_COMMON_SCALAR_DEF_HPP

#include "scalar.hpp"

#include <boost/cstdint.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_container.hpp>
#include <boost/spirit/include/phoenix_statement.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/regex/pending/unicode_iterator.hpp>

namespace omd { namespace parser
{
    namespace detail
    {
        struct push_utf8
        {
            template <typename S, typename C>
            struct result { typedef void type; };

            void operator()(std::string& utf8, uchar code_point) const
            {
                typedef std::back_insert_iterator<std::string> insert_iter;
                insert_iter out_iter(utf8);
                boost::utf8_output_iterator<insert_iter> utf8_iter(out_iter);
                *utf8_iter++ = code_point;
            }
        };

        struct push_esc
        {
            template <typename S, typename C>
            struct result { typedef void type; };

            void operator()(std::string& utf8, uchar c) const
            {
                switch (c)
                {
                    case ' ': utf8 += ' ';          break;
                    case '\t': utf8 += '\t';        break;
                    case '0': utf8 += char(0);      break;
                    case 'a': utf8 += 0x7;          break;
                    case 'b': utf8 += 0x8;          break;
                    case 't': utf8 += 0x9;          break;
                    case 'n': utf8 += 0xA;          break;
                    case 'v': utf8 += 0xB;          break;
                    case 'f': utf8 += 0xC;          break;
                    case 'r': utf8 += 0xD;          break;
                    case 'e': utf8 += 0x1B;         break;
                    case '"': utf8 += '"';          break;
                    case '/': utf8 += '/';          break;
                    case '\\': utf8 += '\\';        break;

                    case '_': push_utf8()(utf8, 0xA0);  break;
                    case 'N': push_utf8()(utf8, 0x85);  break;
                    case 'L': push_utf8()(utf8, 0x2028);  break;
                    case 'P': push_utf8()(utf8, 0x2029);  break;
                }
            }
        };

        template <typename T>
        struct yaml_real_policies : qi::real_policies<T>
        {
            static bool const expect_dot = true;

            template <typename Iterator, typename Attribute>
            static bool
            parse_nan(Iterator& first, Iterator const& last, Attribute& attr)
            {
                using boost::spirit::unused;

                if (first == last)
                    return false;   // end of input reached

                // .nan ?
                if (qi::detail::string_parse(".nan", ".NAN", first, last, unused))
                {
                    attr = std::numeric_limits<T>::quiet_NaN();
                    return true;
                }
                return false;
            }

            template <typename Iterator, typename Attribute>
            static bool
            parse_inf(Iterator& first, Iterator const& last, Attribute& attr)
            {
                using boost::spirit::unused;

                if (first == last)
                    return false;   // end of input reached

                // -.inf
                if (qi::detail::string_parse("-.inf", "-.INF", first, last, unused))
                {
                    attr = -std::numeric_limits<T>::infinity();
                    return true;
                }
                // .inf
                if (qi::detail::string_parse(".inf", ".INF", first, last, unused))
                {
                    attr = std::numeric_limits<T>::infinity();
                    return true;
                }
                return false;
            }
        };
    }

    template <typename Iterator>
    unicode_string<Iterator>::unicode_string(int& indent)
      : unicode_string::base_type(unicode_start),
        indent(indent)
    {
        qi::char_type char_;
        qi::_val_type _val;
        qi::_r1_type _r1;
        qi::_1_type _1;
        qi::_2_type _2;
        qi::lit_type lit;
        qi::blank_type blank;
        qi::eol_type eol;
        qi::repeat_type repeat;
        qi::inf_type inf;
        qi::hex_type hex;

        using boost::spirit::qi::uint_parser;
        using boost::phoenix::function;
        using boost::phoenix::ref;

        uint_parser<uchar, 16, 4, 4> hex4;
        uint_parser<uchar, 16, 8, 8> hex8;
        function<detail::push_utf8> push_utf8;
        function<detail::push_esc> push_esc;

        escape =
                  ('x' > hex)                     [push_utf8(_r1, _1)]
              |   ('u' > hex4)                    [push_utf8(_r1, _1)]
              |   ('U' > hex8)                    [push_utf8(_r1, _1)]
              |   char_("0abtnvfre\"/\\N_LP \t")  [push_esc(_r1, _1)]
              |   eol                             // continue to next line
            ;

        char_esc =
            '\\' > escape(_r1)
            ;

        double_quoted =
              '"'
            > *(char_esc(_val) | (~char_('"'))    [_val += _1])
            > '"'
            ;

        single_quoted =
              '\''
            > *(
                  lit("''")                       [_val += '\'']
              |   (~char_('\''))                  [_val += _1]
              )
            > '\''
            ;

        auto space = blank | (eol >> repeat(ref(indent), inf)[blank]);

        // These are not allowed as first plain-style character
        auto unsafe_first = char_(" \n\r\t,[]{}#&*!|>\\\"%@`");

        // These are not allowed as non-first plain-style character
        auto unsafe_plain = char_(" \n\r\t,[]{}:#");

        unquoted =
                (~unsafe_first)                   [_val = _1]
            >>  *(
                        (+space >> ~unsafe_plain) [_val += ' ', _val += _2]
                    |   (~unsafe_plain)           [_val += _1]
                )
            ;

        unicode_start =
                double_quoted
            |   single_quoted
            |   unquoted
            ;

        BOOST_SPIRIT_DEBUG_NODES(
            (escape)
            (char_esc)
            (single_quoted)
            (double_quoted)
            (unquoted)
            (unicode_start)
        );
    }

    template <typename Iterator>
    scalar<Iterator>::scalar(int& indent)
      : scalar::base_type(scalar_value),
        string_value(indent)
    {
        qi::lit_type lit;
        qi::char_type char_;
        qi::hex_type hex;
        qi::oct_type oct;
        qi::no_case_type no_case;
        qi::int_type int_;
        qi::attr_type attr;
        qi::blank_type blank;
        qi::omit_type omit;

        qi::real_parser<double, detail::yaml_real_policies<double> > double_value;

        scalar_value =
                alias
            |   anchored_value
            |   double_value
            |   integer_value
            |   no_case[bool_value]
            |   no_case[null_value]
            |   string_value
            ;

        integer_value =
                (no_case["0x"] > hex)
            |   (no_case["0o"] > oct)
            |   ('0' >> oct)
            |   int_
            ;

        bool_value.add
            ("true", true)
            ("false", false)
            ("on", true)
            ("off", false)
            ("yes", true)
            ("no", false)
            ;

        null_value =
              (lit("null") | '~')
            >> attr(ast::null_t())
            ;

        alias =
            '*' >> +~char_(" \n\r\t,{}[]") >> attr((ast::value_t*)0)
            ;

        anchored_value =
            '&' >> +~char_(" \n\r\t,{}[]") >> omit[+blank] >> scalar_value
            ;

        BOOST_SPIRIT_DEBUG_NODES(
            (scalar_value)
            (integer_value)
            (null_value)
            (alias)
            (anchored_value)
        );
    }
}}

#endif
