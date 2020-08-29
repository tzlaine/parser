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

constexpr rule<struct abc_def_tag, std::string> abc_def = "abc or def";
constexpr auto abc_def_def = string("abc") | string("def");
BOOST_PARSER_DEFINE_RULES(abc_def);

auto const fail = [](auto & context) { _pass(context) = false; };
constexpr rule<struct fail_abc_pass_def_tag, std::string> fail_abc_pass_def =
    "abc";
constexpr auto fail_abc_pass_def_def = string("abc")[fail] | string("def");
BOOST_PARSER_DEFINE_RULES(fail_abc_pass_def);

auto const attr_to_val = [](auto & context) { _val(context) = _attr(context); };
constexpr rule<struct action_copy_abc_def_tag, std::string>
    action_copy_abc_def = "abc or def";
constexpr auto action_copy_abc_def_def =
    string("abc")[attr_to_val] | string("def")[attr_to_val];
BOOST_PARSER_DEFINE_RULES(action_copy_abc_def);

auto const abc_value = [](auto & context) { _val(context) = "abc"; };
auto const def_value = [](auto & context) { _val(context) = "def"; };
constexpr rule<struct rev_abc_def_tag, std::string> rev_abc_def = "abc or def";
constexpr auto rev_abc_def_def =
    string("abc")[def_value] | string("def")[abc_value];
BOOST_PARSER_DEFINE_RULES(rev_abc_def);

auto const append_attr = [](auto & context) {
    _locals(context) += _attr(context);
};
auto const locals_to_val = [](auto & context) {
    _val(context) = std::move(_locals(context));
};
rule<struct locals_abc_def_tag, std::string, std::string> const locals_abc_def =
    "abc or def";
auto locals_abc_def_def = -string("abc")[append_attr] >>
                          -string("def")[append_attr] >> eps[locals_to_val];
BOOST_PARSER_DEFINE_RULES(locals_abc_def);

TEST(parser, side_effects)
{
    int i = 0;
    auto increment_i = [&i](auto & context) { ++i; };

    using no_attribute_return = decltype(parse("xyz", char_('a')[increment_i]));
    BOOST_MPL_ASSERT((boost::is_same<no_attribute_return, bool>));

    {
        std::string const str = "xyz";
        EXPECT_FALSE(parse(str, char_('a')[increment_i]));
        EXPECT_EQ(i, 0);
        EXPECT_FALSE(parse(str, char_('x')[increment_i]));
        EXPECT_EQ(i, 1);
        auto first = str.c_str();
        EXPECT_TRUE(parse(
            first, boost::text::null_sentinel{}, char_('x')[increment_i]));
        EXPECT_EQ(i, 2);
        EXPECT_FALSE(parse(str, char_('a')[increment_i]));
        EXPECT_EQ(i, 2);
        EXPECT_FALSE(parse(str, char_('x')[increment_i]));
        EXPECT_EQ(i, 3);
        first = str.c_str();
        EXPECT_TRUE(parse(
            first, boost::text::null_sentinel{}, char_('x')[increment_i]));
        EXPECT_EQ(i, 4);
    }
}

TEST(parser, pass)
{
    {
        std::string const str = "xyz";
        auto const result = parse(str, abc_def);
        EXPECT_FALSE(result);
    }
    {
        std::string const str = "abc";
        auto const result = parse(str, abc_def);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "abc");
    }
    {
        std::string const str = "def";
        auto const result = parse(str, abc_def);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "def");
    }
    {
        std::string const str = "abc";
        auto const result = parse(str, fail_abc_pass_def);
        EXPECT_FALSE(result);
    }
    {
        std::string const str = "def";
        auto const result = parse(str, fail_abc_pass_def);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "def");
    }
}

TEST(parser, val_attr)
{
    {
        std::string const str = "abc";
        auto const result = parse(str, action_copy_abc_def);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "abc");
    }
    {
        std::string const str = "def";
        auto const result = parse(str, action_copy_abc_def);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "def");
    }
    {
        std::string const str = "abc";
        auto const result = parse(str, rev_abc_def);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "def");
    }
    {
        std::string const str = "def";
        auto const result = parse(str, rev_abc_def);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "abc");
    }
}

TEST(parser, locals)
{
    {
        std::string const str = "";
        auto const result = parse(str, locals_abc_def);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "");
    }
    {
        std::string const str = "abc";
        auto const result = parse(str, locals_abc_def);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "abc");
    }
    {
        std::string const str = "abcdef";
        auto const result = parse(str, locals_abc_def);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "abcdef");
    }
    {
        std::string const str = "def";
        auto const result = parse(str, locals_abc_def);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "def");
    }
}
