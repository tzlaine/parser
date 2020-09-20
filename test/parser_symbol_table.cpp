// Copyright (C) 2018 T. Zachary Laine
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#include <boost/parser/parser.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>

#include <gtest/gtest.h>


using namespace boost::parser;

TEST(parser, symbols_empty)
{
    symbols<int> roman_numerals;
    symbols<std::string> named_strings;

    std::string const str = "I";
    EXPECT_FALSE(parse(str, roman_numerals));
    EXPECT_FALSE(parse(str, named_strings));
}

TEST(parser, symbols_simple)
{
    symbols<int> const roman_numerals = {
        {"I", 1}, {"V", 5}, {"X", 10}, {"L", 50}, {"C", 100}};
    symbols<std::string> const named_strings = {
        {"I", "1"}, {"V", "5"}, {"X", "10"}, {"L", "50"}, {"C", "100"}};

    {
        auto const result = parse("I", roman_numerals);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 1);
    }
    {
        auto const result = parse("I", named_strings);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "1");
    }

    {
        auto const result = parse("L", roman_numerals);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 50);
    }
    {
        auto const result = parse("L", named_strings);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "50");
    }
}

TEST(parser, symbols_max_munch)
{
    symbols<int> const roman_numerals = {
        {"I", 1},
        {"II", 2},
        {"III", 3},
        {"IV", 4},
        {"V", 5},
        {"VI", 6},
        {"VII", 7},
        {"VIII", 8},
        {"IX", 9},

        {"X", 10},
        {"XX", 20},
        {"XXX", 30},
        {"XL", 40},
        {"L", 50},
        {"LX", 60},
        {"LXX", 70},
        {"LXXX", 80},
        {"XC", 90},

        {"C", 100},
        {"CC", 200},
        {"CCC", 300},
        {"CD", 400},
        {"D", 500},
        {"DC", 600},
        {"DCC", 700},
        {"DCCC", 800},
        {"CM", 900},

        {"M", 1000}};

    {
        auto const result = parse("I", roman_numerals);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 1);
    }
    {
        auto const result = parse("II", roman_numerals);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 2);
    }
    {
        auto const result = parse("III", roman_numerals);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 3);
    }
    {
        auto const result = parse("IV", roman_numerals);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 4);
    }
    {
        auto const result = parse("V", roman_numerals);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 5);
    }
    {
        auto const result = parse("VI", roman_numerals);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 6);
    }
    {
        auto const result = parse("VII", roman_numerals);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 7);
    }
    {
        auto const result = parse("VIII", roman_numerals);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 8);
    }
    {
        auto const result = parse("IX", roman_numerals);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 9);
    }
}

TEST(parser, symbols_mutating)
{
    symbols<int> roman_numerals;
    roman_numerals.add("I", 1)("V", 5)("X", 10);
    auto const add_numeral = [&roman_numerals](auto & context) {
        using namespace boost::parser::literals;
        char chars[2] = {get(_attr(context), 0_c), 0};
        roman_numerals.insert(context, chars, get(_attr(context), 1_c));
    };
    auto const numerals_parser = (char_ >> int_)[add_numeral] >> roman_numerals;

    {
        auto const result = parse("L50L", numerals_parser);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 50);
        EXPECT_FALSE(parse("L", roman_numerals));
    }
    {
        auto const result = parse("C100C", numerals_parser);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 100);
        EXPECT_FALSE(parse("C", roman_numerals));
    }
    {
        auto const result = parse("L50C", numerals_parser);
        EXPECT_FALSE(result);
    }
}
