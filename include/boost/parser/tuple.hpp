// Copyright (C) 2020 T. Zachary Laine
// Copyright Louis Dionne 2013-2017
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_PARSER_TUPLE_HPP
#define BOOST_PARSER_TUPLE_HPP

#include <boost/parser/config.hpp>

#if BOOST_PARSER_USE_STD_TUPLE

#include <tuple>

#else

// Silence very verbose warnings about std::is_pod being deprecated.  TODO:
// Remove this if/when Hana accepts releases the fix for this (already on
// develop).
#if defined(__GNUC__) || defined(__clang__)
#    pragma GCC diagnostic push
#    pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#    pragma GCC diagnostic ignored "-Wunused-value"
#endif
#include <boost/hana.hpp>
#if defined(__GNUC__) || defined(__clang__)
#    pragma GCC diagnostic pop
#endif

#endif


namespace boost { namespace parser {

    namespace detail {
        // to_int() and parse_llong() taken from boost/hana/bool.hpp.
        constexpr int to_int(char c)
        {
            int result = 0;

            if (c >= 'A' && c <= 'F') {
                result = static_cast<int>(c) - static_cast<int>('A') + 10;
            } else if (c >= 'a' && c <= 'f') {
                result = static_cast<int>(c) - static_cast<int>('a') + 10;
            } else {
                result = static_cast<int>(c) - static_cast<int>('0');
            }

            return result;
        }

        template<std::size_t N>
        constexpr long long parse_llong(const char (&arr)[N])
        {
            long long base = 10;
            std::size_t offset = 0;

            if constexpr (N > 2) {
                bool starts_with_zero = arr[0] == '0';
                bool is_hex = starts_with_zero && arr[1] == 'x';
                bool is_binary = starts_with_zero && arr[1] == 'b';

                if (is_hex) {
                    // 0xDEADBEEF (hexadecimal)
                    base = 16;
                    offset = 2;
                } else if (is_binary) {
                    // 0b101011101 (binary)
                    base = 2;
                    offset = 2;
                } else if (starts_with_zero) {
                    // 012345 (octal)
                    base = 8;
                    offset = 1;
                }
            }

            long long number = 0;
            long long multiplier = 1;

            for (std::size_t i = 0; i < N - offset; ++i) {
                char c = arr[N - 1 - i];
                if (c != '\'') { // skip digit separators
                    number += to_int(c) * multiplier;
                    multiplier *= base;
                }
            }

            return number;
        }
    }

    /** The tuple template alias used within Boost.Parser.  This will be
        `std::tuple` when either `BOOST_PARSER_STANDALONE` or
        `BOOST_PARSER_USE_STD_TUPLE` is defined, and `boost::hana::tuple`
        otherwise*/
#if BOOST_PARSER_USE_STD_TUPLE
    template<typename... Args>
    using tuple = std::tuple<Args...>;
#else
    template<typename... Args>
    using tuple = hana::tuple<Args...>;
#endif

    /** A template alias that is `std::integral_constant<T, I>` when either
        `BOOST_PARSER_STANDALONE` or `BOOST_PARSER_USE_STD_TUPLE` is defined,
        and `boost::hana::integral_constant<T, I>` otherwise. */
#if BOOST_PARSER_USE_STD_TUPLE
    template<typename T, T I>
    using integral_constant = std::integral_constant<T, I>;
#else
    template<typename T, T I>
    using integral_constant = hana::integral_constant<T, I>;
#endif

    /** A template alias that is `std::integral_constant<long long, I>` when
        either `BOOST_PARSER_STANDALONE` or `BOOST_PARSER_USE_STD_TUPLE` is
        defined, and `boost::hana::llong<I>` otherwise. */
    template<long long I>
    using llong = integral_constant<long long, I>;

    namespace literals {
        /** A literal that can be used to concisely name `parser::llong`
            integral constants. */
        template<char... chars>
        constexpr auto operator"" _c()
        {
            constexpr long long n =
                detail::parse_llong<sizeof...(chars)>({chars...});
            return llong<n>{};
        }
    }

    /** A tuple accessor that returns a reference to the `I`-th element. */
    template<typename T, T I, typename... Args>
    constexpr decltype(auto)
    get(tuple<Args...> const & t, integral_constant<T, I>)
    {
#if BOOST_PARSER_USE_STD_TUPLE
        return std::get<I>(t);
#else
        return hana::at_c<I>(t);
#endif
    }

    /** A tuple accessor that returns a reference to the `I`-th element. */
    template<typename T, T I, typename... Args>
    constexpr decltype(auto) get(tuple<Args...> & t, integral_constant<T, I>)
    {
#if BOOST_PARSER_USE_STD_TUPLE
        return std::get<I>(t);
#else
        return hana::at_c<I>(t);
#endif
    }

    /** A tuple accessor that returns a reference to the `I`-th element. */
    template<typename T, T I, typename... Args>
    constexpr decltype(auto) get(tuple<Args...> && t, integral_constant<T, I>)
    {
#if BOOST_PARSER_USE_STD_TUPLE
        return std::move(std::get<I>(t));
#else
        return std::move(hana::at_c<I>(t));
#endif
    }

}}

#endif
