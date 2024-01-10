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
BOOST_PARSER_DEFINE_RULE(flat_rule);

constexpr rule<struct recursive_rule_tag> recursive_rule = "recursive_rule";
constexpr auto recursive_rule_def = string("abc") >> -('a' >> recursive_rule);
BOOST_PARSER_DEFINE_RULE(recursive_rule);

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
        EXPECT_FALSE(parse(str, flat_rule));
        EXPECT_TRUE(parse(str, recursive_rule));
    }
    {
        std::string const str = "abcaabc";
        auto first = str.c_str();
        EXPECT_TRUE(prefix_parse(first, boost::parser::detail::text::null_sentinel, flat_rule));
        first = str.c_str();
        EXPECT_TRUE(prefix_parse(first, boost::parser::detail::text::null_sentinel, recursive_rule));
    }
}

constexpr rule<struct flat_string_rule_tag, std::string> flat_string_rule =
    "flat_string_rule";
constexpr auto flat_string_rule_def = string("abc") | string("def");
BOOST_PARSER_DEFINE_RULE(flat_string_rule);

constexpr callback_rule<struct recursive_string_rule_tag, std::string>
    recursive_string_rule = "recursive_string_rule";
auto append_string = [](auto & ctx) {
    auto & val = _val(ctx);
    auto & attr = _attr(ctx);
    val.insert(val.end(), attr.begin(), attr.end());
};
constexpr auto recursive_string_rule_def = string("abc")[append_string] >>
                                           -('a' >> recursive_string_rule);
BOOST_PARSER_DEFINE_RULE(recursive_string_rule);

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
        EXPECT_FALSE(parse(str, flat_string_rule));
        EXPECT_TRUE(parse(str, recursive_string_rule));
    }
    {
        std::string const str = "abcaabc";
        auto first = str.c_str();
        EXPECT_EQ(
            *prefix_parse(
                first,
                boost::parser::detail::text::null_sentinel,
                flat_string_rule),
            "abc");
        first = str.c_str();
        EXPECT_EQ(
            *prefix_parse(
                first,
                boost::parser::detail::text::null_sentinel,
                recursive_string_rule),
            "abcabc");
    }
}

constexpr rule<struct flat_vector_rule_tag, std::vector<char>>
    flat_vector_rule = "flat_vector_rule";
constexpr auto flat_vector_rule_def = string("abc") | string("def");
BOOST_PARSER_DEFINE_RULE(flat_vector_rule);

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
        EXPECT_FALSE(parse(str, flat_vector_rule));
    }
    {
        std::string const str = "abcaabc";
        auto first = str.c_str();
        EXPECT_EQ(
            *prefix_parse(first, boost::parser::detail::text::null_sentinel, flat_vector_rule),
            std::vector<char>({'a', 'b', 'c'}));
    }
    {
        std::string const str = "abcaabc";
        auto first = str.c_str();
        EXPECT_EQ(
            callback_prefix_parse(
                first, boost::parser::detail::text::null_sentinel, flat_vector_rule, int{}),
            true);
    }
}
constexpr callback_rule<struct callback_vector_rule_tag, std::vector<char>>
    callback_vector_rule = "callback_vector_rule";
constexpr auto callback_vector_rule_def = string("abc") | string("def");
BOOST_PARSER_DEFINE_RULE(callback_vector_rule);

constexpr callback_rule<struct callback_void_rule_tag> callback_void_rule =
    "callback_void_rule";
constexpr auto callback_void_rule_def = string("abc") | string("def");
BOOST_PARSER_DEFINE_RULE(callback_void_rule);

struct callback_vector_rule_tag
{};
struct callback_void_rule_tag
{};

struct callbacks_t
{
    void operator()(callback_vector_rule_tag, std::vector<char> && vec) const
    {
        all_results.push_back(std::move(vec));
    }
    void operator()(callback_void_rule_tag) const
    {
        void_callback_called = true;
    }

    mutable std::vector<std::vector<char>> all_results;
    mutable bool void_callback_called = false;
};

TEST(parser, callback_rules)
{
    {
        std::string const str = "xyz";
        callbacks_t callbacks;
        EXPECT_FALSE(callback_parse(str, callback_vector_rule, callbacks));
        EXPECT_EQ(callbacks.all_results.size(), 0u);
    }
    {
        std::string const str = "abc";
        callbacks_t callbacks;
        EXPECT_TRUE(callback_parse(str, callback_vector_rule, callbacks));
        EXPECT_EQ(callbacks.all_results.size(), 1u);
        EXPECT_EQ(callbacks.all_results[0], std::vector<char>({'a', 'b', 'c'}));
    }
    {
        std::string const str = "def";
        callbacks_t callbacks;
        EXPECT_TRUE(callback_parse(str, callback_vector_rule, callbacks));
        EXPECT_EQ(callbacks.all_results.size(), 1u);
        EXPECT_EQ(callbacks.all_results[0], std::vector<char>({'d', 'e', 'f'}));
    }

    {
        std::string const str = "xyz";
        callbacks_t callbacks;
        EXPECT_FALSE(callback_parse(str, callback_void_rule, callbacks));
        EXPECT_FALSE(callbacks.void_callback_called);
    }
    {
        std::string const str = "abc";
        callbacks_t callbacks;
        EXPECT_TRUE(callback_parse(str, callback_void_rule, callbacks));
        EXPECT_TRUE(callbacks.void_callback_called);
    }
    {
        std::string const str = "def";
        callbacks_t callbacks;
        EXPECT_TRUE(callback_parse(str, callback_void_rule, callbacks));
        EXPECT_TRUE(callbacks.void_callback_called);
    }

    {
        std::string const str = "xyz";
        std::vector<std::vector<char>> all_results;
        auto callbacks =
            [&all_results](callback_vector_rule_tag, std::vector<char> && vec) {
                all_results.push_back(std::move(vec));
            };
        EXPECT_FALSE(callback_parse(str, callback_vector_rule, callbacks));
        EXPECT_EQ(all_results.size(), 0u);
    }
    {
        std::string const str = "abc";
        std::vector<std::vector<char>> all_results;
        auto callbacks =
            [&all_results](callback_vector_rule_tag, std::vector<char> && vec) {
                all_results.push_back(std::move(vec));
            };
        EXPECT_TRUE(callback_parse(str, callback_vector_rule, callbacks));
        EXPECT_EQ(all_results.size(), 1u);
        EXPECT_EQ(all_results[0], std::vector<char>({'a', 'b', 'c'}));
    }
    {
        std::string const str = "def";
        std::vector<std::vector<char>> all_results;
        auto callbacks =
            [&all_results](callback_vector_rule_tag, std::vector<char> && vec) {
                all_results.push_back(std::move(vec));
            };
        EXPECT_TRUE(callback_parse(str, callback_vector_rule, callbacks));
        EXPECT_EQ(all_results.size(), 1u);
        EXPECT_EQ(all_results[0], std::vector<char>({'d', 'e', 'f'}));
    }

    {
        std::string const str = "xyz";
        bool void_callback_called = false;
        auto callbacks = [&void_callback_called](callback_void_rule_tag) {
            void_callback_called = true;
        };
        EXPECT_FALSE(callback_parse(str, callback_void_rule, callbacks));
        EXPECT_FALSE(void_callback_called);
    }
    {
        std::string const str = "abc";
        bool void_callback_called = false;
        auto callbacks = [&void_callback_called](callback_void_rule_tag) {
            void_callback_called = true;
        };
        EXPECT_TRUE(callback_parse(str, callback_void_rule, callbacks));
        EXPECT_TRUE(void_callback_called);
    }
    {
        std::string const str = "def";
        bool void_callback_called = false;
        auto callbacks = [&void_callback_called](callback_void_rule_tag) {
            void_callback_called = true;
        };
        EXPECT_TRUE(callback_parse(str, callback_void_rule, callbacks));
        EXPECT_TRUE(void_callback_called);
    }
}

TEST(parser, callback_rules_normal_parse)
{
    {
        std::string const str = "xyz";
        std::vector<char> chars;
        EXPECT_FALSE(parse(str, callback_vector_rule, chars));
    }
    {
        std::string const str = "abc";
        std::vector<char> chars;
        EXPECT_TRUE(parse(str, callback_vector_rule, chars));
        EXPECT_EQ(chars, std::vector<char>({'a', 'b', 'c'}));
    }
    {
        std::string const str = "def";
        std::vector<char> chars;
        EXPECT_TRUE(parse(str, callback_vector_rule, chars));
        EXPECT_EQ(chars, std::vector<char>({'d', 'e', 'f'}));
    }

    {
        std::string const str = "def";
        EXPECT_TRUE(parse(str, callback_void_rule));
    }

    {
        std::string const str = "xyz";
        auto const chars = parse(str, callback_vector_rule);
        EXPECT_FALSE(chars);
    }
    {
        std::string const str = "abc";
        auto const chars = parse(str, callback_vector_rule);
        EXPECT_TRUE(chars);
        EXPECT_EQ(chars, std::vector<char>({'a', 'b', 'c'}));
    }
    {
        std::string const str = "def";
        auto const chars = parse(str, callback_vector_rule);
        EXPECT_TRUE(chars);
        EXPECT_EQ(chars, std::vector<char>({'d', 'e', 'f'}));
    }

    {
        std::string const str = "xyz";
        EXPECT_FALSE(parse(str, callback_vector_rule));
    }
    {
        std::string const str = "abc";
        EXPECT_TRUE(parse(str, callback_vector_rule));
    }
    {
        std::string const str = "def";
        EXPECT_TRUE(parse(str, callback_vector_rule));
    }
}

////////////////////////////////////////////////////////////////////////////////
// More recursive rules

struct recursive_strings_rule_tag
{};
constexpr callback_rule<recursive_strings_rule_tag, std::vector<std::string>>
    recursive_strings_rule = "recursive_strings_rule";
auto push_back = [](auto & ctx) { _val(ctx).push_back(std::move(_attr(ctx))); };
constexpr auto recursive_strings_rule_def = string("abc")[push_back] >>
                                            -('a' >> recursive_strings_rule);
BOOST_PARSER_DEFINE_RULE(recursive_strings_rule);

TEST(param_parser, container_populating_recursive_rule)
{
    {
        std::string const str = "xyz";
        EXPECT_FALSE(parse(str, recursive_strings_rule));
    }
    {
        std::string const str = "abc";
        EXPECT_EQ(
            *parse(str, recursive_strings_rule),
            std::vector<std::string>({"abc"}));
    }
    {
        std::string const str = "abcaabc";
        EXPECT_TRUE(parse(str, recursive_strings_rule));
    }
    {
        std::string const str = "abcaabc";
        auto first = str.c_str();
        EXPECT_EQ(
            *prefix_parse(
                first,
                boost::parser::detail::text::null_sentinel,
                recursive_strings_rule),
            std::vector<std::string>({"abc", "abc"}));
    }
}

template<typename Tag, typename Attribute>
struct recursive_rule_callbacks_t
{
    void operator()(Tag, Attribute && vec) const
    {
        all_results.push_back(std::move(vec));
    }

    mutable std::vector<Attribute> all_results;
};

TEST(param_parser, container_populating_recursive_cb_rule)
{
    using callbacks_type = recursive_rule_callbacks_t<
        recursive_strings_rule_tag,
        std::vector<std::string>>;

    {
        std::string const str = "xyz";
        callbacks_type callbacks;
        EXPECT_FALSE(callback_parse(str, recursive_strings_rule, callbacks));
    }
    {
        std::string const str = "abc";
        callbacks_type callbacks;
        EXPECT_TRUE(callback_parse(str, recursive_strings_rule, callbacks));
        EXPECT_EQ(callbacks.all_results.size(), 1u);
        EXPECT_EQ(callbacks.all_results[0], std::vector<std::string>({"abc"}));
    }
    {
        std::string const str = "abcaabc";
        callbacks_type callbacks;
        EXPECT_TRUE(callback_parse(str, recursive_strings_rule, callbacks));
    }
    {
        std::string const str = "abcaabc";
        auto first = str.c_str();
        callbacks_type callbacks;
        EXPECT_TRUE(callback_prefix_parse(
            first,
            boost::parser::detail::text::null_sentinel,
            recursive_strings_rule,
            callbacks));
        EXPECT_EQ(callbacks.all_results.size(), 1u);
        EXPECT_EQ(
            callbacks.all_results[0], std::vector<std::string>({"abc", "abc"}));
    }
}

struct recursive_string_rule_tag
{};

TEST(param_parser, string_recursive_cb_rule)
{
    using callbacks_type =
        recursive_rule_callbacks_t<recursive_string_rule_tag, std::string>;

    {
        std::string const str = "xyz";
        callbacks_type callbacks;
        EXPECT_FALSE(callback_parse(str, recursive_string_rule, callbacks));
    }
    {
        std::string const str = "def";
        callbacks_type callbacks;
        EXPECT_FALSE(callback_parse(str, recursive_string_rule, callbacks));
    }
    {
        std::string const str = "abc";
        callbacks_type callbacks;
        EXPECT_TRUE(callback_parse(str, recursive_string_rule, callbacks));
        EXPECT_EQ(callbacks.all_results.size(), 1u);
        EXPECT_EQ(callbacks.all_results[0], "abc");
    }
    {
        std::string const str = "abcaabc";
        callbacks_type callbacks;
        EXPECT_TRUE(callback_parse(str, recursive_string_rule, callbacks));
    }
    {
        std::string const str = "abcaabc";
        auto first = str.c_str();
        callbacks_type callbacks;
        EXPECT_TRUE(callback_prefix_parse(
            first,
            boost::parser::detail::text::null_sentinel,
            recursive_string_rule,
            callbacks));
        EXPECT_EQ(callbacks.all_results.size(), 1u);
        EXPECT_EQ(callbacks.all_results[0], "abcabc");
    }
}

namespace more_about_rules_1 {
    namespace bp = boost::parser;

    bp::rule<struct value_tag> value =
        "an integer, or a list of integers in braces";

    auto const ints = '{' > (value % ',') > '}';
    auto const value_def = bp::int_ | ints;

    BOOST_PARSER_DEFINE_RULE(value);
}

namespace more_about_rules_2 {
    namespace bp = boost::parser;

    bp::rule<struct value_tag> value =
        "an integer, or a list of integers in braces";
    bp::rule<struct comma_values_tag> comma_values =
        "a comma-delimited list of integers";

    auto const ints = '{' > comma_values > '}';
    auto const value_def = bp::int_ | ints;
    auto const comma_values_def = (value % ',');

    BOOST_PARSER_DEFINE_RULES(value, comma_values);
}

namespace more_about_rules_3 {
    namespace bp = boost::parser;

    bp::rule<struct parens_tag> parens = "matched parentheses";

    auto const parens_def = ('(' >> parens > ')') | bp::eps;

    BOOST_PARSER_DEFINE_RULES(parens);
}

namespace more_about_rules_4 {
    namespace bp = boost::parser;

    bp::rule<struct parens_tag> parens = "matched parentheses";

    auto const parens_def = ('(' >> parens > ')') | bp::eps;

    BOOST_PARSER_DEFINE_RULES(parens);

    bool balanced_parens(std::string_view str);
}

TEST(parser, doc_exaparensles)
{
    {
        using namespace more_about_rules_1;

        bp::parse("{ 4, 5 a", value, bp::ws);
        bp::parse("{ }", value, bp::ws);
    }
    {
        using namespace more_about_rules_2;

        bp::parse("{ }", value, bp::ws);
    }
    {
        using namespace more_about_rules_3;

        EXPECT_TRUE(bp::parse("(((())))", parens, bp::ws));
        EXPECT_FALSE(bp::parse("(((()))", parens, bp::ws));
    }
    {
        using namespace more_about_rules_4;
        assert(balanced_parens("(())"));
    }
}

namespace more_about_rules_4 {
    bool balanced_parens(std::string_view str)
    {
        namespace bp = boost::parser;
        return bp::parse(str, bp::omit[parens], bp::ws);
    }
}
