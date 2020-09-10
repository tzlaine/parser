/*=============================================================================
    Copyright (c) 2001-2014 Joel de Guzman
    Copyright (c) 2001-2011 Hartmut Kaiser
    Copyright (c) 2011 Jan Frederick Eick
    Copyright (c) 2011 Christopher Jefferson
    Copyright (c) 2006 Stephen Nutt
    Copyright (c) 2019 T. Zachary Laine

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PARSER_DETAIL_NUMERIC_HPP
#define BOOST_PARSER_DETAIL_NUMERIC_HPP

#include <boost/spirit/home/x3/support/numeric_utils/detail/extract_int.hpp>
#include <boost/spirit/home/x3/support/numeric_utils/extract_real.hpp>


namespace boost { namespace parser { namespace detail_spirit_x3 {

    // Copied from
    // boost/spirit/home/x3/support/numeric_utils/detail/extract_int.hpp
    // (Boost 1.67),and modified for use with iterator, sentinel pairs:

    ///////////////////////////////////////////////////////////////////////////
    //  extract_int_impl: main code for extracting integers
    ///////////////////////////////////////////////////////////////////////////
#define BOOST_PARSER_NUMERIC_INNER_LOOP(z, x, data)                             \
        if (!spirit::x3::detail::check_max_digits<MaxDigits>::call(count + leading_zeros) \
            || it == last)                                                      \
            break;                                                              \
        ch = *it;                                                               \
        if (!radix_check::is_valid(ch) || !extractor::call(ch, count, val))     \
            break;                                                              \
        ++it;                                                                   \
        ++count;                                                                \
    /**/

    template <
        typename T, unsigned Radix, unsigned MinDigits, int MaxDigits
      , typename Accumulator = spirit::x3::detail::positive_accumulator<Radix>
      , bool Accumulate = false
    >
    struct extract_int_impl
    {
#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
# pragma warning(push)
# pragma warning(disable: 4127)   // conditional expression is constant
#endif
        template <typename Iterator, typename Sentinel, typename Attribute>
        inline static bool
        parse_main(
            Iterator& first
          , Sentinel last
          , Attribute& attr)
        {
            typedef spirit::x3::detail::radix_traits<Radix> radix_check;
            typedef spirit::x3::detail::int_extractor<Radix, Accumulator, MaxDigits> extractor;
            typedef
                typename std::iterator_traits<Iterator>::value_type char_type;

            Iterator it = first;
            std::size_t leading_zeros = 0;
            if (!Accumulate)
            {
                // skip leading zeros
                while (it != last && *it == '0' && leading_zeros < MaxDigits)
                {
                    ++it;
                    ++leading_zeros;
                }
            }

            typedef typename
                spirit::x3::traits::attribute_type<Attribute>::type
            attribute_type;

            attribute_type val = Accumulate ? attr : attribute_type(0);
            std::size_t count = 0;
            char_type ch;

            while (true)
            {
                BOOST_PP_REPEAT(
                    3
                  , BOOST_PARSER_NUMERIC_INNER_LOOP, _)
            }

            if (count + leading_zeros >= MinDigits)
            {
                spirit::x3::traits::move_to(val, attr);
                first = it;
                return true;
            }
            return false;
        }
#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
# pragma warning(pop)
#endif

        template <typename Iterator, typename Sentinel>
        inline static bool
        parse(
            Iterator& first
          , Sentinel last
          , spirit::x3::unused_type)
        {
            T n = 0; // must calculate value to detect over/underflow
            return parse_main(first, last, n);
        }

        template <typename Iterator, typename Sentinel, typename Attribute>
        inline static bool
        parse(
            Iterator& first
          , Sentinel last
          , Attribute& attr)
        {
            return parse_main(first, last, attr);
        }
    };
#undef BOOST_PARSER_NUMERIC_INNER_LOOP

    ///////////////////////////////////////////////////////////////////////////
    //  extract_int_impl: main code for extracting integers
    //  common case where MinDigits == 1 and MaxDigits = -1
    ///////////////////////////////////////////////////////////////////////////
#define BOOST_PARSER_NUMERIC_INNER_LOOP(z, x, data)                             \
        if (it == last)                                                         \
            break;                                                              \
        ch = *it;                                                               \
        if (!radix_check::is_valid(ch))                                         \
            break;                                                              \
        if (!extractor::call(ch, count, val))                                   \
            return false;                                                       \
        ++it;                                                                   \
        ++count;                                                                \
    /**/

    template <typename T, unsigned Radix, typename Accumulator, bool Accumulate>
    struct extract_int_impl<T, Radix, 1, -1, Accumulator, Accumulate>
    {
#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
# pragma warning(push)
# pragma warning(disable: 4127)   // conditional expression is constant
#endif
        template <typename Iterator, typename Sentinel, typename Attribute>
        inline static bool
        parse_main(
            Iterator& first
          , Sentinel last
          , Attribute& attr)
        {
            typedef spirit::x3::detail::radix_traits<Radix> radix_check;
            typedef spirit::x3::detail::int_extractor<Radix, Accumulator, -1> extractor;
            typedef
                typename std::iterator_traits<Iterator>::value_type char_type;

            Iterator it = first;
            std::size_t count = 0;
            if (!Accumulate)
            {
                // skip leading zeros
                while (it != last && *it == '0')
                {
                    ++it;
                    ++count;
                }

                if (it == last)
                {
                    if (count == 0) // must have at least one digit
                        return false;
                    attr = 0;
                    first = it;
                    return true;
                }
            }

            typedef typename
                spirit::x3::traits::attribute_type<Attribute>::type
            attribute_type;

            attribute_type val = Accumulate ? attr : attribute_type(0);
            char_type ch = *it;

            if (!radix_check::is_valid(ch) || !extractor::call(ch, 0, val))
            {
                if (count == 0) // must have at least one digit
                    return false;
                spirit::x3::traits::move_to(val, attr);
                first = it;
                return true;
            }

            count = 0;
            ++it;
            while (true)
            {
                BOOST_PP_REPEAT(
                    3
                  , BOOST_PARSER_NUMERIC_INNER_LOOP, _)
            }

            spirit::x3::traits::move_to(val, attr);
            first = it;
            return true;
        }
#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
# pragma warning(pop)
#endif

        template <typename Iterator, typename Sentinel>
        inline static bool
        parse(
            Iterator& first
          , Sentinel last
          , spirit::x3::unused_type)
        {
            T n = 0; // must calculate value to detect over/underflow
            return parse_main(first, last, n);
        }

        template <typename Iterator, typename Sentinel, typename Attribute>
        inline static bool
        parse(
            Iterator& first
          , Sentinel last
          , Attribute& attr)
        {
            return parse_main(first, last, attr);
        }
    };

#undef BOOST_PARSER_NUMERIC_INNER_LOOP


    // Copied from boost/spirit/home/x3/support/numeric_utils/extract_int.hpp
    // (Boost 1.67), and modified for use with iterator, sentinel pairs:

    ///////////////////////////////////////////////////////////////////////////
    //  Extract the prefix sign (- or +), return true if a '-' was found
    ///////////////////////////////////////////////////////////////////////////
    template<typename Iterator, typename Sentinel>
    inline bool extract_sign(Iterator & first, Sentinel last)
    {
        (void)last;                  // silence unused warnings
        BOOST_ASSERT(first != last); // precondition

        // Extract the sign
        bool neg = *first == '-';
        if (neg || (*first == '+'))
        {
            ++first;
            return neg;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////////
    // Low level unsigned integer parser
    ///////////////////////////////////////////////////////////////////////////
    template <typename T, unsigned Radix, unsigned MinDigits, int MaxDigits
      , bool Accumulate = false>
    struct extract_uint
    {
        // check template parameter 'Radix' for validity
        static_assert(
            (Radix >= 2 && Radix <= 36),
            "Error Unsupported Radix");

        template <typename Iterator, typename Sentinel>
        inline static bool call(Iterator& first, Sentinel last, T& attr)
        {
            if (first == last)
                return false;

            typedef extract_int_impl<
                T
              , Radix
              , MinDigits
              , MaxDigits
              , spirit::x3::detail::positive_accumulator<Radix>
              , Accumulate>
            extract_type;

            Iterator save = first;
            if (!extract_type::parse(first, last, attr))
            {
                first = save;
                return false;
            }
            return true;
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    // Low level signed integer parser
    ///////////////////////////////////////////////////////////////////////////
    template <typename T, unsigned Radix, unsigned MinDigits, int MaxDigits>
    struct extract_int
    {
        // check template parameter 'Radix' for validity
        static_assert(
            (Radix == 2 || Radix == 8 || Radix == 10 || Radix == 16),
            "Error Unsupported Radix");

        template <typename Iterator, typename Sentinel>
        inline static bool call(Iterator& first, Sentinel last, T& attr)
        {
            if (first == last)
                return false;

            typedef extract_int_impl<
                T, Radix, MinDigits, MaxDigits>
            extract_pos_type;

            typedef extract_int_impl<
                T, Radix, MinDigits, MaxDigits, spirit::x3::detail::negative_accumulator<Radix> >
            extract_neg_type;

            Iterator save = first;
            bool hit = detail_spirit_x3::extract_sign(first, last);
            if (hit)
                hit = extract_neg_type::parse(first, last, attr);
            else
                hit = extract_pos_type::parse(first, last, attr);

            if (!hit)
            {
                first = save;
                return false;
            }
            return true;
        }
    };

    // Copied from boost/spirit/home/x3/support/numeric_utils/extract_real.hpp
    // (Boost 1.71), and modified for use with iterator, sentinel pairs:

    template <typename T, typename RealPolicies>
    struct extract_real
    {
        template <typename Iterator, typename Sentinel, typename Attribute>
        static bool
        parse(Iterator& first, Sentinel last, Attribute& attr,
            RealPolicies const& p)
        {
            if (first == last)
                return false;
            Iterator save = first;

            // Start by parsing the sign. neg will be true if
            // we got a "-" sign, false otherwise.
            bool neg = p.parse_sign(first, last);

            // Now attempt to parse an integer
            T n = 0;
            bool got_a_number = p.parse_n(first, last, n);

            // If we did not get a number it might be a NaN, Inf or a leading
            // dot.
            if (!got_a_number)
            {
                // Check whether the number to parse is a NaN or Inf
                if (p.parse_nan(first, last, n) ||
                    p.parse_inf(first, last, n))
                {
                    // If we got a negative sign, negate the number
                    spirit::x3::traits::move_to(
                        spirit::x3::extension::negate(neg, n), attr);
                    return true;    // got a NaN or Inf, return early
                }

                // If we did not get a number and our policies do not
                // allow a leading dot, fail and return early (no-match)
                if (!p.allow_leading_dot)
                {
                    first = save;
                    return false;
                }
            }

            bool e_hit = false;
            Iterator e_pos;
            int frac_digits = 0;

            // Try to parse the dot ('.' decimal point)
            if (p.parse_dot(first, last))
            {
                // We got the decimal point. Now we will try to parse
                // the fraction if it is there. If not, it defaults
                // to zero (0) only if we already got a number.
                Iterator savef = first;
                if (p.parse_frac_n(first, last, n))
                {
                    // Optimization note: don't compute frac_digits if T is
                    // an unused_type. This should be optimized away by the compiler.
                    if (!is_same<T, spirit::x3::unused_type>::value)
                        frac_digits =
                            static_cast<int>(std::distance(savef, first));
                    BOOST_ASSERT(frac_digits >= 0);
                }
                else if (!got_a_number || !p.allow_trailing_dot)
                {
                    // We did not get a fraction. If we still haven't got a
                    // number and our policies do not allow a trailing dot,
                    // return no-match.
                    first = save;
                    return false;
                }

                // Now, let's see if we can parse the exponent prefix
                e_pos = first;
                e_hit = p.parse_exp(first, last);
            }
            else
            {
                // No dot and no number! Return no-match.
                if (!got_a_number)
                {
                    first = save;
                    return false;
                }

                // If we must expect a dot and we didn't see an exponent
                // prefix, return no-match.
                e_pos = first;
                e_hit = p.parse_exp(first, last);
                if (p.expect_dot && !e_hit)
                {
                    first = save;
                    return false;
                }
            }

            if (e_hit)
            {
                // We got the exponent prefix. Now we will try to parse the
                // actual exponent. It is an error if it is not there.
                int exp = 0;
                if (p.parse_exp_n(first, last, exp))
                {
                    // Got the exponent value. Scale the number by
                    // exp-frac_digits.
                    if (!spirit::x3::extension::scale(exp, frac_digits, n))
                        return false;
                }
                else
                {
                    // If there is no number, disregard the exponent altogether.
                    // by resetting 'first' prior to the exponent prefix (e|E)
                    first = e_pos;

                    // Scale the number by -frac_digits.
                    if (!spirit::x3::extension::scale(-frac_digits, n))
                        return false;
                }
            }
            else if (frac_digits)
            {
                // No exponent found. Scale the number by -frac_digits.
                if (!spirit::x3::extension::scale(-frac_digits, n))
                    return false;
            }

            // If we got a negative sign, negate the number
            spirit::x3::traits::move_to(
                spirit::x3::extension::negate(neg, n), attr);

            // Success!!!
            return true;
        }
    };

    // Copied from
    // boost/spirit/home/x3/string/detail/string_parse.hpp
    // (Boost 1.47),and modified for use with iterator, sentinel pairs:

    template <typename Char, typename Iterator, typename Sentinel, typename Attribute, typename CaseCompareFunc>
    inline bool string_parse(
        Char const* str
      , Iterator& first, Sentinel const& last, Attribute& attr, CaseCompareFunc const& compare) 
    {
        Iterator i = first;
        Char ch = *str;

        for (; !!ch; ++i)
        {
            if (i == last || (compare(ch, *i) != 0))
                return false;
            ch = *++str;
        }

        spirit::x3::traits::move_to(first, i, attr);
        first = i;
        return true;
    }

    template <typename String, typename Iterator, typename Sentinel, typename Attribute, typename CaseCompareFunc>
    inline bool string_parse(
        String const& str
      , Iterator& first, Sentinel const& last, Attribute& attr, CaseCompareFunc const& compare)
    {
        Iterator i = first;
        typename String::const_iterator stri = str.begin();
        typename String::const_iterator str_last = str.end();

        for (; stri != str_last; ++stri, ++i)
            if (i == last || (compare(*stri, *i) != 0))
                return false;
        spirit::x3::traits::move_to(first, i, attr);
        first = i;
        return true;
    }

    struct common_type_equal
    {
        template<typename T, typename U>
        bool operator()(T x, U y)
        {
            using common_t = std::common_type_t<decltype(x), decltype(y)>;
            return (common_t)x == (common_t)y;
        }
    };

    template <typename Char, typename Iterator, typename Sentinel, typename Attribute>
    inline bool string_parse(
        Char const* uc_i, Char const* lc_i
      , Iterator& first, Sentinel const& last, Attribute& attr)
    {
        Iterator i = first;

        common_type_equal eq;

        for (; *uc_i && *lc_i; ++uc_i, ++lc_i, ++i)
            if (i == last || (!eq(*uc_i, *i) && !eq(*lc_i, *i)))
                return false;
        spirit::x3::traits::move_to(first, i, attr);
        first = i;
        return true;
    }

    template <typename String, typename Iterator, typename Sentinel, typename Attribute>
    inline bool string_parse(
        String const& ucstr, String const& lcstr
      , Iterator& first, Sentinel const& last, Attribute& attr)
    {
        typename String::const_iterator uc_i = ucstr.begin();
        typename String::const_iterator uc_last = ucstr.end();
        typename String::const_iterator lc_i = lcstr.begin();
        Iterator i = first;

        for (; uc_i != uc_last; ++uc_i, ++lc_i, ++i)
            if (i == last || ((*uc_i != *i) && (*lc_i != *i)))
                return false;
        spirit::x3::traits::move_to(first, i, attr);
        first = i;
        return true;
    }

    // Copied from
    // boost/spirit/home/x3/numeric/real_policies.hpp
    // (Boost 1.47),and modified for use with iterator, sentinel pairs:

    ///////////////////////////////////////////////////////////////////////////
    //  Default (unsigned) real number policies
    ///////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct ureal_policies
    {
        // trailing dot policy suggested by Gustavo Guerra
        static bool const allow_leading_dot = true;
        static bool const allow_trailing_dot = true;
        static bool const expect_dot = false;

        template <typename Iterator, typename Sentinel>
        static bool
        parse_sign(Iterator& /*first*/, Iterator const& /*last*/)
        {
            return false;
        }

        template <typename Iterator, typename Sentinel, typename Attribute>
        static bool
        parse_n(Iterator& first, Sentinel const& last, Attribute& attr_)
        {
            return extract_uint<T, 10, 1, -1>::call(first, last, attr_);
        }

        template <typename Iterator, typename Sentinel>
        static bool
        parse_dot(Iterator& first, Sentinel const& last)
        {
            if (first == last || *first != '.')
                return false;
            ++first;
            return true;
        }

        template <typename Iterator, typename Sentinel, typename Attribute>
        static bool
        parse_frac_n(Iterator& first, Sentinel const& last, Attribute& attr_)
        {
            return extract_uint<T, 10, 1, -1, true>::call(first, last, attr_);
        }

        template <typename Iterator, typename Sentinel>
        static bool
        parse_exp(Iterator& first, Sentinel const& last)
        {
            if (first == last || (*first != 'e' && *first != 'E'))
                return false;
            ++first;
            return true;
        }

        template <typename Iterator, typename Sentinel>
        static bool
        parse_exp_n(Iterator& first, Sentinel const& last, int& attr_)
        {
            return extract_int<int, 10, 1, -1>::call(first, last, attr_);
        }

        ///////////////////////////////////////////////////////////////////////
        //  The parse_nan() and parse_inf() functions get called whenever
        //  a number to parse does not start with a digit (after having
        //  successfully parsed an optional sign).
        //
        //  The functions should return true if a Nan or Inf has been found. In
        //  this case the attr should be set to the matched value (NaN or
        //  Inf). The optional sign will be automatically applied afterwards.
        //
        //  The default implementation below recognizes representations of NaN
        //  and Inf as mandated by the C99 Standard and as proposed for
        //  inclusion into the C++0x Standard: nan, nan(...), inf and infinity
        //  (the matching is performed case-insensitively).
        ///////////////////////////////////////////////////////////////////////
        template <typename Iterator, typename Sentinel, typename Attribute>
        static bool
        parse_nan(Iterator& first, Sentinel const& last, Attribute& attr_)
        {
            if (first == last)
                return false;   // end of input reached

            if (*first != 'n' && *first != 'N')
                return false;   // not "nan"

            // nan[(...)] ?
            if (detail_spirit_x3::string_parse("nan", "NAN", first, last, spirit::x3::unused))
            {
                if (first != last && *first == '(')
                {
                    // skip trailing (...) part
                    Iterator i = first;

                    while (++i != last && *i != ')')
                        ;
                    if (i == last)
                        return false;     // no trailing ')' found, give up

                    first = ++i;
                }
                attr_ = std::numeric_limits<T>::quiet_NaN();
                return true;
            }
            return false;
        }

        template <typename Iterator, typename Sentinel, typename Attribute>
        static bool
        parse_inf(Iterator& first, Sentinel const& last, Attribute& attr_)
        {
            if (first == last)
                return false;   // end of input reached

            if (*first != 'i' && *first != 'I')
                return false;   // not "inf"

            // inf or infinity ?
            if (detail_spirit_x3::string_parse("inf", "INF", first, last, spirit::x3::unused))
            {
                // skip allowed 'inity' part of infinity
                detail_spirit_x3::string_parse("inity", "INITY", first, last, spirit::x3::unused);
                attr_ = std::numeric_limits<T>::infinity();
                return true;
            }
            return false;
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    //  Default (signed) real number policies
    ///////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct real_policies : ureal_policies<T>
    {
        template <typename Iterator, typename Sentinel>
        static bool
        parse_sign(Iterator& first, Sentinel const& last)
        {
            return extract_sign(first, last);
        }
    };

    template <typename T>
    struct strict_ureal_policies : ureal_policies<T>
    {
        static bool const expect_dot = true;
    };

    template <typename T>
    struct strict_real_policies : real_policies<T>
    {
        static bool const expect_dot = true;
    };

}}}

#endif
