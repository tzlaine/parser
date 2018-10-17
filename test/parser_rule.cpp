// Copyright (C) 2018 T. Zachary Laine
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#include <boost/parser/parser.hpp>

#include <gtest/gtest.h>


using namespace boost::parser;

constexpr rule<struct flat_rule_tag> flat_rule = "flat_rule";
constexpr auto flat_rule_def = string("abc") | string("def");
BOOST_PARSER_DEFINE_RULES(flat_rule);

constexpr rule<struct recursive_rule_tag> recursive_rule = "recursive_rule";
constexpr auto recursive_rule_def = string("abc") >> -('a' >> recursive_rule);
BOOST_PARSER_DEFINE_RULES(recursive_rule);

TEST(parser, no_attribute_rules)
{
    {
        std::string const str = "xyz";
        EXPECT_FALSE(parse(str, flat_rule));
        EXPECT_FALSE(parse(str, recursive_rule));
    }
    {
        std::string const str = "def";
        bool const flat_result{parse(str, flat_rule)};
        EXPECT_TRUE(flat_result);
        EXPECT_FALSE(parse(str, recursive_rule));
    }
    {
        std::string const str = "abc";
        EXPECT_TRUE(parse(str, flat_rule));
        EXPECT_TRUE(parse(str, recursive_rule));
    }
    {
        std::string const str = "abcaabc";
        EXPECT_TRUE(parse(str, flat_rule));
        EXPECT_TRUE(parse(str, recursive_rule));
    }
}

constexpr rule<struct flat_string_rule_tag, std::string> flat_string_rule =
    "flat_string_rule";
constexpr auto flat_string_rule_def = string("abc") | string("def");
BOOST_PARSER_DEFINE_RULES(flat_string_rule);

constexpr rule<struct recursive_string_rule_tag, std::string>
    recursive_string_rule = "recursive_string_rule";
constexpr auto recursive_string_rule_def = string("abc") >>
                                           -('a' >> recursive_string_rule);
BOOST_PARSER_DEFINE_RULES(recursive_string_rule);

TEST(parser, string_attribute_rules)
{
    {
        std::string const str = "xyz";
        EXPECT_FALSE(parse(str, flat_string_rule));
        EXPECT_FALSE(parse(str, recursive_string_rule));
    }
    {
        std::string const str = "def";
        auto const flat_result = parse(str, flat_string_rule);
        EXPECT_TRUE(flat_result);
        EXPECT_EQ(*flat_result, "def");
        EXPECT_FALSE(parse(str, recursive_string_rule));
    }
    {
        std::string const str = "abc";
        EXPECT_EQ(*parse(str, flat_string_rule), "abc");
        EXPECT_EQ(*parse(str, recursive_string_rule), "abc");
    }
    {
        std::string const str = "abcaabc";
        EXPECT_EQ(*parse(str, flat_string_rule), "abc");
        EXPECT_EQ(*parse(str, recursive_string_rule), "abcabc");
    }
}

constexpr rule<struct flat_vector_rule_tag, std::vector<char>>
    flat_vector_rule = "flat_vector_rule";
constexpr auto flat_vector_rule_def = string("abc") | string("def");
BOOST_PARSER_DEFINE_RULES(flat_vector_rule);

TEST(parser, vector_attribute_rules)
{
    {
        std::string const str = "xyz";
        std::vector<char> chars;
        EXPECT_FALSE(parse(str, flat_vector_rule, chars));
    }
    {
        std::string const str = "def";
        std::vector<char> chars;
        EXPECT_TRUE(parse(str, flat_vector_rule, chars));
        EXPECT_EQ(chars, std::vector<char>({'d', 'e', 'f'}));
    }
    {
        std::string const str = "abc";
        EXPECT_EQ(
            *parse(str, flat_vector_rule), std::vector<char>({'a', 'b', 'c'}));
    }
    {
        std::string const str = "abcaabc";
        EXPECT_EQ(
            *parse(str, flat_vector_rule), std::vector<char>({'a', 'b', 'c'}));
    }
}
