/**
 *   Copyright (C) 2024 T. Zachary Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See
 *   accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt)
 */

#include <boost/parser/parser.hpp>
#include <boost/parser/transcode_view.hpp>

#include <gtest/gtest.h>


namespace bp = boost::parser;

TEST(quoted_string, basic)
{
    constexpr auto parser = bp::quoted_string;

    {
        auto result = bp::parse("", parser, bp::ws);
        EXPECT_FALSE(result);
    }

    {
        auto result = bp::parse(R"("foo")", parser, bp::ws);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "foo");
    }

    {
        auto result = bp::parse(R"("foo\\")", parser, bp::ws);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "foo\\");
    }

    {
        auto result = bp::parse(R"("\"foo\"")", parser, bp::ws);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "\"foo\"");
    }
}

TEST(quoted_string, different_char)
{
    constexpr auto parser = bp::quoted_string('\'');

    {
        auto result = bp::parse("", parser, bp::ws);
        EXPECT_FALSE(result);
    }

    {
        auto result = bp::parse(R"('foo')", parser, bp::ws);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "foo");
    }

    {
        auto result = bp::parse(R"('foo\\')", parser, bp::ws);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "foo\\");
    }

    {
        auto result = bp::parse(R"('\'foo\'')", parser, bp::ws);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "'foo'");
    }
}

#if 0
TEST(quoted_string, char_set)
{
    constexpr auto parser = bp::quoted_string("'\"");

    {
        auto result = bp::parse("", parser, bp::ws);
        EXPECT_FALSE(result);
    }

    {
        EXPECT_FALSE(bp::parse(R"('foo")", parser, bp::ws));
        EXPECT_FALSE(bp::parse(R"("foo')", parser, bp::ws));
    }

    {
        auto result = bp::parse(R"('foo')", parser, bp::ws);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "foo");
    }
    {
        auto result = bp::parse(R"("foo")", parser, bp::ws);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "foo");
    }

    {
        auto result = bp::parse(R"('foo\\')", parser, bp::ws);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "foo\\");
    }
    {
        auto result = bp::parse(R"("foo\\")", parser, bp::ws);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "foo\\");
    }

    {
        auto result = bp::parse(R"('\'foo\'')", parser, bp::ws);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "'foo'");
    }
    {
        auto result = bp::parse(R"("\"foo\"")", parser, bp::ws);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "'foo'");
    }

    {
        // Can't escape arbitrary characters, only backslash and the quote
        // character.
        EXPECT_FALSE(bp::parse(R"("\'foo")", parser, bp::ws));
    }
}
#endif
