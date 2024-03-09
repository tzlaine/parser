/**
 *   Copyright (C) 2024 T. Zachary Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See
 *   accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt)
 */

#include <boost/parser/parser.hpp>

#include <gtest/gtest.h>


namespace bp = boost::parser;

namespace make {
    template<typename... Ts>
    auto tuple(Ts &&... xs)
    {
        return bp::tuple<Ts...>((Ts &&) xs...);
    }
}

/*
{P0, -P0, *P0, P1, P2, P3, eps}
<cartesian product>
{P0, P1, P2, P3, eps, *P0, -P0, (P0 >>/| P2), -(P0 >>/| P1), (-P0 >>/| P1)}

P0 = bp::string("foo");
P1 = bp::string("bar");
P2 = bp::int_;
P3 = bp::char_('c');
*/

using namespace std::literals;

TEST(attributes, or_parser_permutations_2)
{
    [[maybe_unused]] int dummy = 0; // for clang-format(!)

    // P1
    {
        auto result = bp::parse("foo", bp::string("bar") | bp::string("foo"));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "foo"s);
    }
    {
        auto result = bp::parse("bar", bp::string("bar") | bp::string("bar"));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "bar"s);
    }
    {
        auto result = bp::parse("42", bp::string("bar") | bp::int_);
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 1u);
        EXPECT_EQ(std::get<int>(*result), 42);
    }
    {
        auto result = bp::parse("bar", bp::string("bar") | bp::char_('c'));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(std::get<std::string>(*result), "bar"s);
    }
    {
        auto result = bp::parse("", bp::string("bar") | bp::eps);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, std::nullopt);
    }
    {
        auto result =
            bp::parse("foofoo", bp::string("bar") | *bp::string("foo"));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 1u);
        EXPECT_EQ(
            std::get<std::vector<std::string>>(*result),
            std::vector({"foo"s, "foo"s}));
    }
    {
        auto result = bp::parse("bar", bp::string("bar") | -bp::string("foo"));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(std::get<std::string>(*result), "bar"s);
    }
    {
        auto result =
            bp::parse("42", bp::string("bar") | (bp::string("foo") | bp::int_));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 1u);
        EXPECT_EQ(std::get<int>(*result), 42);
    }
    {
        auto result = bp::parse(
            "bar",
            bp::string("foo") | -(bp::string("foo") | bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 1u);
        EXPECT_EQ(std::get<std::optional<std::string>>(*result), "bar"s);
    }
    {
        auto result = bp::parse(
            "foo",
            bp::string("bar") | (-bp::string("foo") | bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 1u);
        EXPECT_EQ(std::get<std::optional<std::string>>(*result), "foo"s);
    }
    {
        auto result = bp::parse(
            "bar", bp::string("bar") | (bp::string("foo") >> bp::int_));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(std::get<std::string>(*result), "bar"s);
    }
    {
        auto result = bp::parse(
            "bar",
            bp::string("bar") | -(bp::string("foo") >> bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(std::get<std::string>(*result), "bar"s);
    }
    {
        auto result = bp::parse(
            "bar",
            bp::string("bar") | (-bp::string("foo") >> bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(std::get<std::string>(*result), "bar"s);
    }

    // P2
    {
        auto result = bp::parse("42", bp::int_ | bp::string("foo"));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(std::get<int>(*result), 42);
    }
    {
        auto result = bp::parse("bar", bp::int_ | bp::string("bar"));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 1u);
        EXPECT_EQ(std::get<std::string>(*result), "bar"s);
    }
    {
        auto result = bp::parse("42", bp::int_ | bp::int_, bp::ws);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 42);
    }
    {
        auto result = bp::parse("c", bp::int_ | bp::char_('c'));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 1u);
        EXPECT_EQ(std::get<char>(*result), 'c');
    }
    {
        auto result = bp::parse("", bp::int_ | bp::eps);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, std::nullopt);
    }
    {
        auto result = bp::parse("foofoo", bp::int_ | *bp::string("foo"));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 1u);
        EXPECT_EQ(
            std::get<std::vector<std::string>>(*result),
            std::vector({"foo"s, "foo"s}));
    }
    {
        auto result = bp::parse("42", bp::int_ | -bp::string("foo"));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(std::get<int>(*result), 42);
    }
    {
        auto result =
            bp::parse("42", bp::int_ | (bp::string("foo") | bp::int_));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(std::get<int>(*result), 42);
    }
    {
        auto result = bp::parse(
            "bar", bp::int_ | -(bp::string("foo") | bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 1u);
        EXPECT_EQ(
            std::get<std::optional<std::string>>(*result),
            std::optional("bar"s));
    }
    {
        auto result =
            bp::parse("", bp::int_ | (-bp::string("foo") | bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 1u);
        EXPECT_EQ(std::get<std::optional<std::string>>(*result), std::nullopt);
    }
    {
        auto result =
            bp::parse("42", bp::int_ | (bp::string("foo") >> bp::int_));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(std::get<int>(*result), 42);
    }
    {
        auto result = bp::parse(
            "42", bp::int_ | -(bp::string("foo") >> bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(std::get<int>(*result), 42);
    }
    {
        auto result = bp::parse(
            "42", bp::int_ | (-bp::string("foo") >> bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(std::get<int>(*result), 42);
    }

    // P3
    {
        auto result = bp::parse("c", bp::char_('c') | bp::string("foo"));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(std::get<char>(*result), 'c');
    }
    {
        auto result = bp::parse("bar", bp::char_('c') | bp::string("bar"));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 1u);
        EXPECT_EQ(std::get<std::string>(*result), "bar"s);
    }
    {
        auto result = bp::parse("42", bp::char_('c') | bp::int_);
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 1u);
        EXPECT_EQ(std::get<int>(*result), 42);
    }
    {
        auto result = bp::parse("c", bp::char_('c') | bp::char_('c'));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 'c');
    }
    {
        auto result = bp::parse("c", bp::char_('c') | bp::eps);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 'c');
    }
    {
        auto result = bp::parse("foofoo", bp::char_('c') | *bp::string("foo"));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 1u);
        EXPECT_EQ(
            std::get<std::vector<std::string>>(*result),
            std::vector({"foo"s, "foo"s}));
    }
    {
        auto result = bp::parse("c", bp::char_('c') | -bp::string("foo"));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(std::get<char>(*result), 'c');
    }
    {
        auto result =
            bp::parse("42", bp::char_('c') | (bp::string("foo") | bp::int_));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 2u);
        EXPECT_EQ(std::get<int>(*result), 42);
    }
    {
        auto result = bp::parse(
            "bar", bp::char_('c') | -(bp::string("foo") | bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 1u);
        EXPECT_EQ(
            std::get<std::optional<std::string>>(*result),
            std::optional("bar"s));
    }
    {
        auto result = bp::parse(
            "foo", bp::char_('c') | (-bp::string("foo") | bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 1u);
        EXPECT_EQ(
            std::get<std::optional<std::string>>(*result),
            std::optional("foo"s));
    }
    {
        auto result = bp::parse(
            "foo42", bp::char_('c') | (bp::string("foo") >> bp::int_));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 1u);
        EXPECT_EQ(
            (std::get<bp::tuple<std::string, int>>(*result)),
            (make::tuple("foo"s, 42)));
    }
    {
        auto result = bp::parse(
            "c", bp::char_('c') | -(bp::string("foo") >> bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(std::get<char>(*result), 'c');
    }
    {
        auto result = bp::parse(
            "c", bp::char_('c') | (-bp::string("foo") >> bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(std::get<char>(*result), 'c');
    }

    // eps | ... prohibited.
}
