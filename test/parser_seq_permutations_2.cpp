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

TEST(attributes, seq_parser_permutations_2)
{
    [[maybe_unused]] int dummy = 0; // for clang-format(!)

    // P1
    {
        auto result =
            bp::parse("barfoo", bp::string("bar") >> bp::string("foo"));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, (make::tuple("bar"s, "foo"s)));
    }
    {
        auto result =
            bp::parse("barbar", bp::string("bar") >> bp::string("bar"));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, (make::tuple("bar"s, "bar"s)));
    }
    {
        auto result = bp::parse("bar42", bp::string("bar") >> bp::int_);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, (make::tuple("bar"s, 42)));
    }
    {
        auto result = bp::parse("barc", bp::string("bar") >> bp::char_('c'));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "barc"s);
    }
    {
        auto result = bp::parse("bar", bp::string("bar") >> bp::eps);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "bar"s);
    }
    {
        auto result =
            bp::parse("barfoofoo", bp::string("bar") >> *bp::string("foo"));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, std::vector({"bar"s, "foo"s, "foo"s}));
    }
    {
        auto result =
            bp::parse("barfoo", bp::string("bar") >> -bp::string("foo"));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, (make::tuple("bar"s, std::optional("foo"s))));
    }
    {
        auto result = bp::parse(
            "barfoo42", bp::string("bar") >> (bp::string("foo") >> bp::int_));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, (make::tuple("bar"s, "foo"s, 42)));
    }
    {
        auto result = bp::parse(
            "barfoobar",
            bp::string("bar") >> -(bp::string("foo") >> bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(
            *result,
            (make::tuple("bar"s, std::optional(make::tuple("foo"s, "bar"s)))));
    }
    {
        auto result = bp::parse(
            "barfoobar",
            bp::string("bar") >> (-bp::string("foo") >> bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(
            *result, (make::tuple("bar"s, std::optional("foo"s), "bar"s)));
    }
    {
        auto result = bp::parse(
            "bar42", bp::string("bar") >> (bp::string("foo") | bp::int_));
        EXPECT_TRUE(result);
        EXPECT_EQ(
            *result, (make::tuple("bar"s, std::variant<std::string, int>(42))));
    }
    {
        auto result = bp::parse(
            "bar",
            bp::string("bar") >> -(bp::string("foo") | bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, (make::tuple("bar"s, std::optional<std::string>{})));
    }
    {
        auto result = bp::parse(
            "bar",
            bp::string("bar") >> (-bp::string("foo") | bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(
            *result,
            make::tuple(
                "bar"s,
                std::variant<std::optional<std::string>, std::string>(
                    std::nullopt)));
    }

    // P2
    {
        auto result = bp::parse("42foo", bp::int_ >> bp::string("foo"));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, (make::tuple(42, "foo"s)));
    }
    {
        auto result = bp::parse("42bar", bp::int_ >> bp::string("bar"));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, (make::tuple(42, "bar"s)));
    }
    {
        auto result = bp::parse("42 42", bp::int_ >> bp::int_, bp::ws);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, (make::tuple(42, 42)));
    }
    {
        auto result = bp::parse("42c", bp::int_ >> bp::char_('c'));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, (make::tuple(42, 'c')));
    }
    {
        auto result = bp::parse("42", bp::int_ >> bp::eps);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 42);
    }
    {
        auto result = bp::parse("42foofoo", bp::int_ >> *bp::string("foo"));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, (make::tuple(42, std::vector({"foo"s, "foo"s}))));
    }
    {
        auto result = bp::parse("42foo", bp::int_ >> -bp::string("foo"));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, (make::tuple(42, std::optional("foo"s))));
    }
    {
        auto result =
            bp::parse("42foo42", bp::int_ >> (bp::string("foo") >> bp::int_));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, (make::tuple(42, "foo"s, 42)));
    }
    {
        auto result = bp::parse(
            "42foobar", bp::int_ >> -(bp::string("foo") >> bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(
            *result,
            (make::tuple(42, std::optional(make::tuple("foo"s, "bar"s)))));
    }
    {
        auto result = bp::parse(
            "42foobar", bp::int_ >> (-bp::string("foo") >> bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, (make::tuple(42, std::optional("foo"s), "bar"s)));
    }
    {
        auto result = bp::parse(
            "42 42", bp::int_ >> (bp::string("foo") | bp::int_), bp::ws);
        EXPECT_TRUE(result);
        EXPECT_EQ(
            *result, (make::tuple(42, std::variant<std::string, int>(42))));
    }
    {
        auto result = bp::parse(
            "42", bp::int_ >> -(bp::string("foo") | bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, (make::tuple(42, std::optional<std::string>{})));
    }
    {
        auto result = bp::parse(
            "42", bp::int_ >> (-bp::string("foo") | bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(
            *result,
            make::tuple(
                42,
                std::variant<std::optional<std::string>, std::string>(
                    std::nullopt)));
    }

    // P3
    {
        auto result = bp::parse("cfoo", bp::char_('c') >> bp::string("foo"));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "cfoo"s);
    }
    {
        auto result = bp::parse("cbar", bp::char_('c') >> bp::string("bar"));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "cbar"s);
    }
    {
        auto result = bp::parse("c42", bp::char_('c') >> bp::int_);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, (make::tuple('c', 42)));
    }
    {
        auto result = bp::parse("cc", bp::char_('c') >> bp::char_('c'));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "cc"s);
    }
    {
        auto result = bp::parse("c", bp::char_('c') >> bp::eps);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 'c');
    }
    {
        auto result =
            bp::parse("cfoofoo", bp::char_('c') >> *bp::string("foo"));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, (make::tuple('c', std::vector({"foo"s, "foo"s}))));
    }
    {
        auto result = bp::parse("cfoo", bp::char_('c') >> -bp::string("foo"));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, (make::tuple('c', std::optional("foo"s))));
    }
    {
        auto result = bp::parse(
            "cfoo42", bp::char_('c') >> (bp::string("foo") >> bp::int_));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, (make::tuple("cfoo"s, 42)));
    }
    {
        auto result = bp::parse(
            "cfoobar",
            bp::char_('c') >> -(bp::string("foo") >> bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(
            *result,
            (make::tuple('c', std::optional(make::tuple("foo"s, "bar"s)))));
    }
    {
        auto result = bp::parse(
            "cfoobar",
            bp::char_('c') >> (-bp::string("foo") >> bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, (make::tuple('c', std::optional("foo"s), "bar"s)));
    }
    {
        auto result =
            bp::parse("c42", bp::char_('c') >> (bp::string("foo") | bp::int_));
        EXPECT_TRUE(result);
        EXPECT_EQ(
            *result, (make::tuple('c', std::variant<std::string, int>(42))));
    }
    {
        auto result = bp::parse(
            "c", bp::char_('c') >> -(bp::string("foo") | bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, (make::tuple('c', std::optional<std::string>{})));
    }
    {
        auto result = bp::parse(
            "c", bp::char_('c') >> (-bp::string("foo") | bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(
            *result,
            (make::tuple(
                'c',
                std::variant<std::optional<std::string>, std::string>(
                    std::nullopt))));
    }

    // eps
    {
        auto result = bp::parse("foo", bp::eps >> bp::string("foo"));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "foo"s);
    }
    {
        auto result = bp::parse("bar", bp::eps >> bp::string("bar"));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "bar"s);
    }
    {
        auto result = bp::parse("42", bp::eps >> bp::int_);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 42);
    }
    {
        auto result = bp::parse("c", bp::eps >> bp::char_('c'));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 'c');
    }
    {
        auto result = bp::parse("", bp::eps >> bp::eps);
        EXPECT_TRUE(result);
    }
    {
        auto result = bp::parse("foofoo", bp::eps >> *bp::string("foo"));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, std::vector({"foo"s, "foo"s}));
    }
    {
        auto result = bp::parse("foo", bp::eps >> -bp::string("foo"));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, std::optional("foo"s));
    }
    {
        auto result =
            bp::parse("foo42", bp::eps >> (bp::string("foo") >> bp::int_));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, (make::tuple("foo"s, 42)));
    }
    {
        auto result = bp::parse(
            "foobar", bp::eps >> -(bp::string("foo") >> bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, std::optional((make::tuple("foo"s, "bar"s))));
    }
    {
        auto result = bp::parse(
            "foobar", bp::eps >> (-bp::string("foo") >> bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, (make::tuple(std::optional("foo"s), "bar"s)));
    }
    {
        auto result =
            bp::parse("42", bp::eps >> (bp::string("foo") | bp::int_));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, (std::variant<std::string, int>(42)));
    }
    {
        auto result =
            bp::parse("", bp::eps >> -(bp::string("foo") | bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, std::optional<std::string>{});
    }
    {
        auto result =
            bp::parse("", bp::eps >> (-bp::string("foo") | bp::string("bar")));
        EXPECT_TRUE(result);
        EXPECT_EQ(
            *result,
            (std::variant<std::optional<std::string>, std::string>(
                std::nullopt)));
    }
}
