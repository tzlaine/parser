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
{P0, P1, P2, P3, eps, *P0, -P0, (P0 |/>> P2), -(P0 |/>> P1), (-P0 |/>> P1)}

P0 = bp::string("foo");
P1 = bp::string("bar");
P2 = bp::int_;
P3 = bp::char_('c');
*/

using namespace std::literals;

TEST(attributes, or_parser_permutations_1)
{
    [[maybe_unused]] int dummy = 0; // for clang-format(!)

    // P0
    {
        auto result = bp::parse("foo", bp::string("foo") | bp::string("foo"));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "foo"s);
    }
    {
        auto result = bp::parse("bar", bp::string("foo") | bp::string("bar"));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "bar"s);
    }
    {
        auto result = bp::parse("42", bp::string("foo") | bp::int_);
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 1u);
        EXPECT_EQ(std::get<int>(*result), 42);
    }
    {
        auto result = bp::parse("c", bp::string("foo") | bp::char_('c'));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 1u);
        EXPECT_EQ(std::get<char>(*result), 'c');
    }
    {
        auto result = bp::parse("foo", bp::string("foo") | bp::eps);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, std::optional("foo"s));
    }
    {
        auto result = bp::parse("foo", bp::string("foo") | *bp::string("foo"));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(std::get<std::string>(*result), "foo"s);
    }
    {
        auto result = bp::parse("", bp::string("foo") | -bp::string("foo"));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 1u);
        EXPECT_EQ(std::get<std::optional<std::string>>(*result), std::nullopt);
    }
    {
        auto result = bp::parse(
            "foo", bp::string("foo") | (bp::string("foo") | bp::int_));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(std::get<std::string>(*result), "foo"s);
    }
    {
        auto result = bp::parse(
            "bar",
            bp::string("foo") | -(bp::string("foo") | bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 1);
        EXPECT_EQ(std::get<std::optional<std::string>>(*result), "bar"s);
    }
    {
        auto result = bp::parse(
            "", bp::string("foo") | (-bp::string("foo") | bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 1);
        EXPECT_EQ(std::get<std::optional<std::string>>(*result), std::nullopt);
    }
    {
        auto result = bp::parse(
            "foo", bp::string("foo") | (bp::string("foo") >> bp::int_));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(std::get<std::string>(*result), "foo"s);
    }
    {
        auto result = bp::parse(
            "", bp::string("foo") | -(bp::string("foo") >> bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 1u);
        EXPECT_EQ(
            (std::get<std::optional<bp::tuple<std::string, std::string>>>(
                *result)),
            std::nullopt);
    }
    {
        auto result = bp::parse(
            "bar",
            bp::string("foo") | (-bp::string("foo") >> bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 1u);
        EXPECT_EQ(
            (std::get<bp::tuple<std::optional<std::string>, std::string>>(
                *result)),
            (make::tuple(std::optional<std::string>{}, "bar"s)));
    }

    // -P0
    {
        auto result = bp::parse("foo", -bp::string("foo") | bp::string("foo"));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(
            std::get<std::optional<std::string>>(*result),
            std::optional("foo"s));
    }
    {
        auto result = bp::parse("", -bp::string("foo") | bp::string("bar"));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(std::get<std::optional<std::string>>(*result), std::nullopt);
    }
    {
        auto result = bp::parse("", -bp::string("foo") | bp::int_);
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(std::get<std::optional<std::string>>(*result), std::nullopt);
    }
    {
        auto result = bp::parse("", -bp::string("foo") | bp::char_('c'));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(std::get<std::optional<std::string>>(*result), std::nullopt);
    }
    {
        auto result = bp::parse("foo", -bp::string("foo") | bp::eps);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "foo"s);
    }
    {
        auto result = bp::parse("foo", -bp::string("foo") | *bp::string("foo"));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(std::get<std::optional<std::string>>(*result), "foo"s);
    }
    {
        auto result = bp::parse("foo", -bp::string("foo") | -bp::string("foo"));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "foo"s);
    }
    {
        auto result =
            bp::parse("", -bp::string("foo") | (bp::string("foo") | bp::int_));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(std::get<std::optional<std::string>>(*result), std::nullopt);
    }
    {
        auto result = bp::parse(
            "foo",
            -bp::string("foo") | -(bp::string("foo") | bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "foo"s);
    }
    {
        auto result = bp::parse(
            "", -bp::string("foo") | (-bp::string("foo") | bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(std::get<std::optional<std::string>>(*result), std::nullopt);
    }
    {
        auto result = bp::parse(
            "foo", -bp::string("foo") | (bp::string("foo") >> bp::int_));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(std::get<std::optional<std::string>>(*result), "foo"s);
    }
    {
        auto result = bp::parse(
            "foo",
            -bp::string("foo") | -(bp::string("foo") >> bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(std::get<std::optional<std::string>>(*result), "foo"s);
    }
    {
        auto result = bp::parse(
            "foo",
            -bp::string("foo") | (-bp::string("foo") >> bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(std::get<std::optional<std::string>>(*result), "foo"s);
    }

    // *P0
    {
        auto result = bp::parse(
            "foo", bp::lexeme[*bp::string("foo")] | bp::string("foo"));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(
            std::get<std::vector<std::string>>(*result), std::vector({"foo"s}));
    }
    {
        auto result =
            bp::parse("foofoo", *bp::string("foo") | bp::string("bar"));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(
            std::get<std::vector<std::string>>(*result),
            std::vector({"foo"s, "foo"s}));
    }
    {
        auto result = bp::parse("", *bp::string("foo") | bp::int_);
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(
            std::get<std::vector<std::string>>(*result),
            std::vector<std::string>{});
    }
    {
        auto result = bp::parse("", *bp::string("foo") | bp::char_('c'));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(
            std::get<std::vector<std::string>>(*result),
            std::vector<std::string>{});
    }
    {
        auto result = bp::parse("foofoo", *bp::string("foo") | bp::eps);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, std::optional(std::vector({"foo"s, "foo"s})));
    }
    {
        auto result = bp::parse(
            "foofoo", bp::lexeme[*bp::string("foo")] | *bp::string("foo"));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, std::vector({"foo"s, "foo"s}));
    }
    {
        auto result =
            bp::parse("foofoo", *bp::string("foo") | -bp::string("foo"));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(
            std::get<std::vector<std::string>>(*result),
            std::vector({"foo"s, "foo"s}));
    }
    {
        auto result = bp::parse(
            "foofoo",
            bp::lexeme[*bp::string("foo")] | (bp::string("foo") | bp::int_));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(
            std::get<std::vector<std::string>>(*result),
            std::vector({"foo"s, "foo"s}));
    }
    {
        auto result = bp::parse(
            "foofoo",
            bp::lexeme[*bp::string("foo")] |
                -(bp::string("foo") | bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(
            std::get<std::vector<std::string>>(*result),
            std::vector({"foo"s, "foo"s}));
    }
    {
        auto result = bp::parse(
            "foofoo",
            bp::lexeme[*bp::string("foo")] |
                (-bp::string("foo") | bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(
            std::get<std::vector<std::string>>(*result),
            std::vector({"foo"s, "foo"s}));
    }
    {
        auto result = bp::parse(
            "foofoo",
            bp::lexeme[*bp::string("foo")] | (bp::string("foo") >> bp::int_));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(
            std::get<std::vector<std::string>>(*result),
            std::vector({"foo"s, "foo"s}));
    }
    {
        auto result = bp::parse(
            "foofoo",
            bp::lexeme[*bp::string("foo")] |
                -(bp::string("foo") >> bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(
            std::get<std::vector<std::string>>(*result),
            std::vector({"foo"s, "foo"s}));
    }
    {
        auto result = bp::parse(
            "foofoo",
            bp::lexeme[*bp::string("foo")] |
                (-bp::string("foo") >> bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(result->index(), 0);
        EXPECT_EQ(
            std::get<std::vector<std::string>>(*result),
            std::vector({"foo"s, "foo"s}));
    }
}
