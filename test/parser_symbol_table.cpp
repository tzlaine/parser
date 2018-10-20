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

TEST(parser, symbols_mutating)
{
    symbols<int> roman_numerals;
    roman_numerals.add("I", 1)("V", 5)("X", 10);
    auto const add_numeral = [&roman_numerals](auto & context) {
        using namespace boost::hana::literals;
        char chars[1] = {_attr(context)[0_c]};
        roman_numerals.insert(context, chars, _attr(context)[1_c]);
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
