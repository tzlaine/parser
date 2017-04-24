/**
 *   Copyright (C) 2010, 2011, 2012 Object Modeling Designs : consultomd.com
 *   Copyright (c) 2010 Joel de Guzman
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if !defined(OMD_COMMON_SCALAR_DEF_HPP)
#define OMD_COMMON_SCALAR_DEF_HPP

#include <yaml/parser/scalar.hpp>

#include <boost/cstdint.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_container.hpp>
#include <boost/spirit/include/phoenix_statement.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/regex/pending/unicode_iterator.hpp>
#include <boost/phoenix/object/construct.hpp>

namespace omd { namespace yaml { namespace parser
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
        struct yaml_strict_real_policies : qi::real_policies<T>
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

        template <typename T>
        struct yaml_real_policies : yaml_strict_real_policies<T>
        {
            static bool const expect_dot = false;
        };
    }

    template <typename Iterator>
    unicode_string<Iterator>::unicode_string(int& indent_)
      : unicode_string::base_type(unicode_start),
        indent(indent_)
    {
        qi::char_type char_;
        qi::_val_type _val;
        qi::_r1_type _r1;
        qi::_1_type _1;
        qi::_2_type _2;
        qi::lit_type lit;
        qi::blank_type blank;
        qi::print_type print;
        qi::eol_type eol;
        qi::repeat_type repeat;
        qi::inf_type inf;
        qi::alnum_type alnum;
        qi::hex_type hex;
        qi::omit_type omit;

        using boost::spirit::qi::uint_parser;
        using boost::phoenix::function;
        using boost::phoenix::ref;
        using boost::spirit::qi::copy;

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

        separate = copy(
                blank | (eol >> repeat(ref(indent), inf)[blank])
            );

        plain_safe = ~char_(" \n\r\t,[]{}#");

        // These are not allowed as first plain-style character
        auto unsafe_first = char_(" \n\r\t?:-,[]{}#&*!|>\\\"%@`");

        unquoted_char =
                plain_safe - char_(":#")
            |   ~char_(" \n\r\t") >> &char_("#")
            |   ':' >> plain_safe
            ;

        unquoted =
                (~unsafe_first | char_("?:-") >> &plain_safe) [_val = _1]
            >>  *(
                        (+separate >> unquoted_char)          [_val += ' ', _val += _2]
                    |   unquoted_char                         [_val += _1]
                )
            ;

        explicit_ =
                "!!str"
            >   omit[+blank]
            >   (   double_quoted
                |   single_quoted
                |   unquoted
                )
            ;

        unicode_start =
                explicit_
            |   double_quoted
            |   single_quoted
            |   unquoted
            ;

        // [34]
        ns_char =
            print - eol /* - bom */ - blank
            ;

        // [39]
        uri_char =
                char_("%") > hex > hex
            |   alnum | char_("-")               // word_char [38]
            |   char_("#;/?:@&=+$,_.!~*'()[]")
            ;

        // [40]
        tag_char =
            uri_char - char_("!,[]{}") // '!' | flow_indicator [23]
            ;

        // [102]
        anchor_char =
            ns_char - char_(",[]{}")
            ;

        BOOST_SPIRIT_DEBUG_NODES(
            (escape)
            (char_esc)
            (single_quoted)
            (double_quoted)
            (unquoted)
            (unicode_start)
            (explicit_)
        );
    }

    template <typename Iterator>
    scalar<Iterator>::scalar(int& indent, qi::symbols<char>& anchors)
      : scalar::base_type(scalar_value),
        string_value(indent)
    {
        qi::lit_type lit;
        qi::char_type char_;
        qi::alnum_type alnum;
        qi::hex_type hex;
        qi::oct_type oct;
        qi::no_case_type no_case;
        qi::int_type int_;
        qi::attr_type attr;
        qi::blank_type blank;
        qi::omit_type omit;
        qi::_a_type _a;
        qi::_b_type _b;
        qi::_1_type _1;
        qi::_val_type _val;
        qi::raw_type raw;
        qi::eoi_type eoi;

        namespace phx = boost::phoenix;
        using boost::spirit::qi::copy;
        using phx::construct;

        phx::function<qi::symbols<char>::adder> add_anchor(anchors.add);
        qi::real_parser<
            double, detail::yaml_strict_real_policies<double> >
        strict_double_value;
        qi::real_parser<
            double, detail::yaml_real_policies<double> >
        double_value;

        auto & uri_char = string_value.uri_char;
        auto & tag_char = string_value.tag_char;
        auto & anchor_char = string_value.anchor_char;
        auto & separate = string_value.separate;

        scalar_value =
                scalar_value_no_strings
            |   string_value
            ;

        auto delimeter = copy(char_(" \n\r\t,[]{}:#") | eoi);

        scalar_value_no_strings =
                alias_node
            |   anchored_value
            |   ("!!float" > omit[+blank] > float_value)
            |   ("!!bool" > omit[+blank] > bool_value)
            |   ("!!int" > omit[+blank] > int_value)
            |   ("!!null" > omit[+blank] > null_value)
            |   strict_float_value
            |   int_value
            |   bool_value
            |   null_value
            ;

        // this is a special form of scalar for use as map keys
        map_key =
                alias_node
            |   anchored_string
            |   string_value
            |   ("!!float" > omit[+blank] > float_value)
            |   ("!!bool" > omit[+blank] > bool_value)
            |   ("!!int" > omit[+blank] > int_value)
            |   ("!!null" > omit[+blank] > null_value)
            ;

        int_value =
            (       (no_case["0x"] > hex)
                |   (no_case["0o"] > oct)
                |   ('0' >> oct)
                |   int_
            )
            >>  &delimeter
            ;

        float_value =
                double_value
            >>  &delimeter
            ;

        strict_float_value =
                strict_double_value
            >>  &delimeter
            ;

        bool_value_.add
            ("true", true)
            ("false", false)
            ;

        bool_value =
                bool_value_
            >>  &delimeter
            ;

        null_value =
                (lit("null") | '~')
            >>  &delimeter
            >>  attr(ast::null_t())
            ;

        // [104]
        alias_node =
                '*'
            >   anchor_name
            >   attr((ast::value_t*)0)
            ;

        anchored_value %=
                '&'
            >>  (+~char_(" \n\r\t,{}[]")) [ add_anchor(_1) ]
            >>  omit[+blank]
            >>  scalar_value
            ;

        anchored_string %=
                '&'
            >>  (+~char_(" \n\r\t,{}[]")) [ add_anchor(_1) ]
            >>  omit[+blank]
            >>  string_value
            ;

        // [89]
        tag_handle %=
                // "alnum..." below is  word_char [38]
                '!' >> +(alnum | char_("-")) >> '!' // named_tag_handle [92] (must match existing TAG-defined prefix)
            |   "!!"                                // secondary_tag_handle [91]
            |   '!'                                 // primary_tag_handle [90]
            ; // TODO: Check that nonempty handle matches existing TAG prefix (or better yet, use a symbol table)

        // [96]
        properties = (
                tag_property[_a = _1] >> -(separate >> anchor_property[_b = _1])
            |   anchor_property[_b = _1] >> -(separate >> tag_property[_a = _1])
            )
            [_val = construct<ast::properties_t>(_a, _b)]
            ;

        // [97]
        tag_property %=
                lit('!') >> "<" > +uri_char > ">"   // verbatim_tag [98]
            |   tag_handle >> +tag_char             // shorthand_tag [99]
            |   '!'                                 // non_specific_tag [100]
            ;

        // [101]
        anchor_property %=
            '&' >> +anchor_char
            ;

        // [103]
        anchor_name %=
            +anchor_char
            ;

        BOOST_SPIRIT_DEBUG_NODES(
            (scalar_value)
            (int_value)
            (float_value)
            (strict_float_value)
            (null_value)
            (alias_node)
            (anchor_name)
            (anchored_value)
        );
    }
}}}

#endif
