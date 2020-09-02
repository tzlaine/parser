// Copyright (C) 2020 T. Zachary Laine
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_PARSER_CONCEPTS_HPP
#define BOOST_PARSER_CONCEPTS_HPP

#include <boost/parser/config.hpp>
#include <boost/parser/parser_fwd.hpp>
#include <boost/text/transcode_view.hpp>

// Silence very verbose warnings about std::is_pod being deprecated.  TODO:
// Remove this if/when Hana accepts https://github.com/boostorg/hana/pull/471.
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
#include <boost/hana.hpp>
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif

#if defined(BOOST_PARSER_DOXYGEN) || BOOST_PARSER_USE_CONCEPTS

#include <ranges>


namespace boost { namespace parser {

    //[ all_concepts
    template<typename T>
    concept utf8_code_unit = std::integral<T> && sizeof(T) == 1;

    template<typename T>
    concept utf32_code_unit = std::integral<T> && sizeof(T) == 4;

    template<typename T>
    concept utf8_pointer =
        std::is_pointer_v<T> && utf8_code_unit<std::iter_value_t<T>>;

    template<typename T>
    concept utf8_range = std::ranges::forward_range<T> &&
        utf8_code_unit<std::ranges::range_value_t<T>>;

    template<typename T>
    concept utf8_range_like = utf8_range<T> || utf8_pointer<T>;

    template<typename T>
    concept char8_pointer =
        utf8_pointer<T> && std::is_same_v<std::iter_value_t<T>, char8_t>;

    template<typename T>
    concept char8_iter = std::forward_iterator<T> &&
        std::is_same_v<std::iter_value_t<T>, char8_t>;

    template<typename T>
    concept char8_range =
        utf8_range<T> && std::is_same_v<std::ranges::range_value_t<T>, char8_t>;

    template<typename T>
    concept parsable_iter = std::forward_iterator<T> &&
        std::is_integral<std::iter_value_t<T>>::value;

    template<typename T>
    concept code_point_iter = parsable_iter<T> &&
                              sizeof(std::iter_value_t<T>) == 4u;

    template<typename T>
    concept code_point_range = parsable_range<T> &&
                               sizeof(std::ranges::range_value_t<T>) == 4u;

    //[ parsable_range_like_concept
    template<typename T>
    concept parsable_range = std::ranges::forward_range<T> &&
        std::is_integral<std::ranges::range_value_t<T>>::value;

    template<typename T>
    concept parsable_pointer = std::is_pointer<std::decay_t<T>>::value &&
        std::is_integral<std::remove_pointer_t<std::decay_t<T>>>::value;

    template<typename T>
    concept parsable_range_like = parsable_range<T> || parsable_pointer<T>;
    //]

    template<
        typename I,
        typename S,
        typename ErrorHandler,
        typename GlobalState>
    using minimal_parse_context = decltype(detail::make_context(
        std::declval<I>(),
        std::declval<S>(),
        std::declval<bool &>(),
        std::declval<int &>(),
        std::declval<ErrorHandler const &>(),
        std::declval<detail::nope &>(),
        std::declval<detail::symbol_table_tries_t &>()));

    template<typename T, typename I, typename S, typename GlobalState>
    concept error_handler =
        requires (
            T const & t,
            I first,
            S last,
            parse_error<I> const & e,
            diagnostic_kind kind,
            std::string_view message,
            minimal_parse_context<
                I, S, T, GlobalState> const & context) {
            { t(first, last, e) } -> std::same_as<error_handler_result>;
            t.diagnose(kind, message, context, first);
            t.diagnose(kind, message, context);
        };

    //[ container_concept
    template<typename T>
    concept container = std::ranges::common_range<T> && requires(T t) {
        { t.insert(t.begin(), *t.begin()) }
            -> std::same_as<std::ranges::iterator_t<T>>;
        { t.insert(t.begin(), t.begin(), t.end()) }
            -> std::same_as<std::ranges::iterator_t<T>>;
    };
    //]

    //]

    namespace detail {

        template<typename T, typename U>
        concept container_and_value_type =
            container<T> && std::is_same_v<std::ranges::range_value_t<T>, U>;

    }

}}

#endif

#endif
