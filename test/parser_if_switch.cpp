/**
 *   Copyright (C) 2018 T. Zachary Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See
 *   accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt)
 */

#include <boost/parser/parser.hpp>

#include <gtest/gtest.h>


using namespace boost::parser;


auto true_ = [](auto & context) { return true; };
auto false_ = [](auto & context) { return false; };

auto three = [](auto & context) { return 3; };


TEST(parser, if_)
{
    {
        std::string str = "a";
        auto result = parse(str, if_(true_)[char_]);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 'a');
        EXPECT_FALSE(parse(str, if_(false_)[char_]));
    }
    {
        std::string str = "a";
        auto result = parse(str, if_(true_)[char_]);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 'a');
        EXPECT_FALSE(parse(str, if_(false_)[char_]));
        EXPECT_FALSE(parse(str, if_(true_)[char_('b')]));
    }
}

TEST(parser, switch_)
{
    {
        std::string str = "a";
        auto result = parse(str, switch_(true_)(true, char_));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 'a');
    }
    {
        std::string str = "a";
        auto result = parse(str, switch_(true)(true_, char_));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 'a');
    }
    {
        std::string str = "a";
        auto result = parse(str, switch_(true)(true, char_));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 'a');
    }
    {
        std::string str = "a";
        auto result = parse(str, switch_(true_)(true_, char_));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 'a');
    }

    {
        std::string str = "a";
        auto result = parse(str, switch_(true_)(false, char_));
        EXPECT_FALSE(result);
    }
    {
        std::string str = "a";
        auto result = parse(str, switch_(true)(false_, char_));
        EXPECT_FALSE(result);
    }
    {
        std::string str = "a";
        auto result = parse(str, switch_(true)(false, char_));
        EXPECT_FALSE(result);
    }
    {
        std::string str = "a";
        auto result = parse(str, switch_(true_)(false_, char_));
        EXPECT_FALSE(result);
    }

    {
        std::string str = "a";
        auto result =
            parse(str, switch_(three)(1, char_('b'))(three, char_('a')));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 'a');
    }
    {
        std::string str = "a";
        auto result = parse(str, switch_(3)(1, char_('b'))(three, char_('a')));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 'a');
    }
    {
        std::string str = "a";
        auto result = parse(str, switch_(3)(1, char_('b'))(3, char_('a')));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 'a');
    }
    {
        std::string str = "a";
        auto result = parse(str, switch_(three)(1, char_('b'))(3, char_('a')));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 'a');
    }

    {
        std::string str = "a";
        auto result =
            parse(str, switch_(three)(1, char_('a'))(three, char_('b')));
        EXPECT_FALSE(result);
    }
    {
        std::string str = "a";
        auto result = parse(str, switch_(3)(1, char_('a'))(three, char_('b')));
        EXPECT_FALSE(result);
    }
    {
        std::string str = "a";
        auto result = parse(str, switch_(3)(1, char_('a'))(3, char_('b')));
        EXPECT_FALSE(result);
    }
    {
        std::string str = "a";
        auto result = parse(str, switch_(three)(1, char_('a'))(3, char_('b')));
        EXPECT_FALSE(result);
    }
}
