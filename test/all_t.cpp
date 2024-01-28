/**
 *   Copyright (C) 2024 T. Zachary Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See
 *   accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt)
 */

#include <boost/parser/config.hpp>
#include <boost/parser/detail/text/detail/all_t.hpp>

#include <gtest/gtest.h>


using namespace boost::parser::detail::text;

TEST(all_t, basic)
{
    std::string str;
    std::string const const_str;

    {
        auto && result = detail::all(
            BOOST_PARSER_SUBRANGE(const_str.begin(), const_str.end()));
        static_assert(std::is_same_v<
                      decltype(result),
                      BOOST_PARSER_SUBRANGE<decltype(const_str.begin())> &&>);
    }
    {
        auto && result = detail::all(str);
        static_assert(
            std::is_same_v<decltype(result), detail::ref_view<std::string> &&>);
    }
    {
        auto && result = detail::all(const_str);
        static_assert(std::is_same_v<
                      decltype(result),
                      detail::ref_view<std::string const> &&>);
    }
    {
        auto && result = detail::all(std::string{});
        static_assert(std::is_same_v<
                      decltype(result),
                      detail::owning_view<std::string> &&>);
    }

    static_assert(
        std::is_same_v<
            detail::all_t<BOOST_PARSER_SUBRANGE<decltype(const_str.begin())>>,
            BOOST_PARSER_SUBRANGE<decltype(const_str.begin())>>);

    static_assert(std::is_same_v<
                  detail::all_t<std::string &>,
                  detail::ref_view<std::string>>);

    static_assert(std::is_same_v<
                  detail::all_t<std::string const &>,
                  detail::ref_view<std::string const>>);

    static_assert(std::is_same_v<
                  detail::all_t<std::string &&>,
                  detail::owning_view<std::string>>);
}

TEST(all_t, array)
{
    char str[] = "text";
    char const const_str[] = "text";

    static_assert(detail::range_<char[5]>);
    static_assert(std::is_object_v<char[5]>);
    detail::ref_view<char[5]> ref_view_(str);
    {
        auto && result = detail::all(
            BOOST_PARSER_SUBRANGE(std::begin(const_str), std::end(const_str)));
        static_assert(std::is_same_v<
                      decltype(result),
                      BOOST_PARSER_SUBRANGE<decltype(std::begin(const_str))> &&>);
    }
    {
        auto && result = detail::all(str);
        static_assert(
            std::is_same_v<decltype(result), detail::ref_view<char[5]> &&>);
    }
    {
        auto && result = detail::all(const_str);
        static_assert(std::is_same_v<
                      decltype(result),
                      detail::ref_view<char const[5]> &&>);
    }

    static_assert(
        std::is_same_v<
            detail::all_t<BOOST_PARSER_SUBRANGE<decltype(std::begin(const_str))>>,
            BOOST_PARSER_SUBRANGE<decltype(std::begin(const_str))>>);

    static_assert(
        std::
            is_same_v<detail::all_t<char(&)[5]>, detail::ref_view<char[5]>>);

    static_assert(std::is_same_v<
                  detail::all_t<char const(&)[5]>,
                  detail::ref_view<char const[5]>>);
}
