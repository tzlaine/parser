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
using namespace std::literals;

TEST(permutation_parser, basic)
{
    {
        constexpr auto parser = bp::int_ || bp::string("foo");

        {
            auto result = bp::parse("42 foo", parser, bp::ws);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, (bp::tuple<int, std::string>(42, "foo"s)));
        }
        {
            auto result = bp::parse("42foo", parser, bp::ws);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, (bp::tuple<int, std::string>(42, "foo"s)));
        }
        {
            auto result = bp::parse("foo 42", parser, bp::ws);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, (bp::tuple<int, std::string>(42, "foo"s)));
        }
        {
            auto result = bp::parse("foo42", parser, bp::ws);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, (bp::tuple<int, std::string>(42, "foo"s)));
        }
    }

    {
        constexpr auto parser = bp::int_ || bp::string("foo") || bp::char_('g');

        {
            auto result = bp::parse("42 foo g", parser, bp::ws);
            EXPECT_TRUE(result);
            EXPECT_EQ(
                *result,
                (bp::tuple<int, std::string, double>(42, "foo"s, 'g')));
        }
        {
            auto result = bp::parse("42 g foo", parser, bp::ws);
            EXPECT_TRUE(result);
            EXPECT_EQ(
                *result,
                (bp::tuple<int, std::string, double>(42, "foo"s, 'g')));
        }
        {
            auto result = bp::parse("foo 42 g", parser, bp::ws);
            EXPECT_TRUE(result);
            EXPECT_EQ(
                *result,
                (bp::tuple<int, std::string, double>(42, "foo"s, 'g')));
        }
        {
            auto result = bp::parse("foo g 42", parser, bp::ws);
            EXPECT_TRUE(result);
            EXPECT_EQ(
                *result,
                (bp::tuple<int, std::string, double>(42, "foo"s, 'g')));
        }
        {
            auto result = bp::parse("g foo 42", parser, bp::ws);
            EXPECT_TRUE(result);
            EXPECT_EQ(
                *result,
                (bp::tuple<int, std::string, double>(42, "foo"s, 'g')));
        }
        {
            auto result = bp::parse("g 42 foo", parser, bp::ws);
            EXPECT_TRUE(result);
            EXPECT_EQ(
                *result,
                (bp::tuple<int, std::string, double>(42, "foo"s, 'g')));
        }
    }
}
