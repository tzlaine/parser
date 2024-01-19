/**
 *   Copyright (C) 2024 T. Zachary Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See
 *   accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt)
 */

#include <boost/parser/parser.hpp>


#include <gtest/gtest.h>


using namespace boost::parser;


TEST(class_type, std_type_from_tuple)
{
    {
        constexpr auto parser = lexeme[+(char_ - ' ')] >> uint_ >> uint_;
        std::string out;
        auto result = parse("something 4 5", parser, ws, out);
        EXPECT_TRUE(result);
        EXPECT_EQ(out, "thing");
    }
    {
        constexpr auto p = lexeme[+(char_ - ' ')] >> uint_ >> uint_;
        constexpr auto parser = +p >> -p;
        std::vector<std::string> out;
        auto result = parse("something 4 5 some 0 2", parser, ws, out);
        EXPECT_TRUE(result);
        EXPECT_EQ(out.size(), 2u);
        EXPECT_EQ(out[0], "thing");
        EXPECT_EQ(out[1], "so");
    }
    {
        constexpr auto p = lexeme[+(char_ - ' ')] >> uint_ >> uint_;
        constexpr auto parser = -p;
        std::optional<std::string> out;
        auto result = parse("something 4 5", parser, ws, out, trace::on);
        EXPECT_TRUE(result);
        EXPECT_TRUE(out);
        EXPECT_EQ(*out, "thing");
    }
    {
        constexpr auto parser = lexeme[+(char_ - ' ')] >> uint_ >> uint_;
        std::optional<std::string> out;
        auto result = parse("something 4 5", parser, ws, out);
        EXPECT_TRUE(result);
        EXPECT_TRUE(out);
        EXPECT_EQ(*out, "thing");
    }
    {
        constexpr auto parser = uint_ >> char_ >> char_;
        std::vector<std::string> out;
        auto result = parse("4 ab", parser, ws, out);
        EXPECT_TRUE(result);
        EXPECT_EQ(out, std::vector<std::string>({"ab", "ab", "ab", "ab"}));
    }
}

struct s0_rule_tag
{};
struct s1_rule_a_tag
{};
struct s1_rule_b_tag
{};
struct s2_rule_a_tag
{};
struct s2_rule_b_tag
{};


struct s0
{
    s0() = default;
    s0(int i, std::string str, std::vector<int> vec) :
        i_(i), str_(std::move(str)), vec_(std::move(vec))
    {}

    int i() const { return i_; }
    std::string str() const { return str_; }
    std::vector<int> vec() const { return vec_; }

private:
    int i_;
    std::string str_;
    std::vector<int> vec_;
};

using s0_tuple = tuple<int, std::string, std::vector<int>>;

auto s0_parser = "s0" >> int_ >> lexeme[+(char_ - ' ')] >> *int_;

callback_rule<s0_rule_tag, s0> s0_rule = "s0_rule";
auto s0_rule_def = s0_parser;

struct s1
{
    s1() = default;
    s1(int i, std::string str, std::vector<int> vec) :
        i_(i), str_(std::move(str)), vec_(std::move(vec))
    {}
    s1(int i, double str, std::vector<int> vec) :
        i_(i), str_(str), vec_(std::move(vec))
    {}

    int i() const { return i_; }
    std::variant<std::string, double> str() const { return str_; }
    std::vector<int> vec() const { return vec_; }

private:
    int i_;
    std::variant<std::string, double> str_;
    std::vector<int> vec_;
};

using s1_tuple =
    tuple<int, std::variant<std::string, double>, std::vector<int>>;

auto s1_parser_a = "s1" >> int_ >> lexeme[+(char_ - ' ')] >> *int_;
auto s1_parser_b = "s1" >> int_ >> double_ >> *int_;

callback_rule<s1_rule_a_tag, s1> s1_rule_a = "s1_rule_a";
callback_rule<s1_rule_b_tag, s1> s1_rule_b = "s1_rule_b";
auto s1_rule_a_def = s1_parser_a;
auto s1_rule_b_def = s1_parser_b;

struct s2
{
    s2() = default;
    s2(int i, std::string str, std::optional<std::vector<int>> vec) :
        i_(i), str_(std::move(str)), vec_(std::move(vec))
    {}

    int i() const { return i_; }
    std::string str() const { return str_; }
    std::optional<std::vector<int>> vec() const { return vec_; }

private:
    int i_;
    std::string str_;
    std::optional<std::vector<int>> vec_;
};

using s2_tuple = tuple<int, std::string, std::optional<std::vector<int>>>;

auto s2_parser_a = "s2" >> int_ >> lexeme[+(char_ - ' ')] >> *int_;
auto s2_parser_b = "s2" >> int_ >> lexeme[+(char_ - ' ')] >> -+int_;

callback_rule<s2_rule_a_tag, s2> s2_rule_a = "s2_rule_a";
callback_rule<s2_rule_b_tag, s2> s2_rule_b = "s2_rule_b";
auto s2_rule_a_def = s2_parser_a;
auto s2_rule_b_def = s2_parser_b;

BOOST_PARSER_DEFINE_RULES(s0_rule, s1_rule_a, s1_rule_b, s2_rule_a, s2_rule_b);


TEST(class_type, seq_parser_struct_rule)
{
    ////////////////////////////////////////////////////////////////////////////
    // Parse-generated attribute.

    {
        std::optional<s0> result = parse("s0 42 text 1 2 3", s0_rule, ws);
        EXPECT_TRUE(result);
        s0 & struct_ = *result;
        EXPECT_EQ(struct_.i(), 42);
        EXPECT_EQ(struct_.str(), "text");
        EXPECT_EQ(struct_.vec(), std::vector<int>({1, 2, 3}));
    }
    {
        std::optional<s1> const result =
            parse("s1 42 text 1 2 3", s1_rule_a, ws);
        EXPECT_TRUE(result);
        s1 const & struct_ = *result;
        EXPECT_EQ(struct_.i(), 42);
        EXPECT_EQ(struct_.str().index(), 0u);
        EXPECT_EQ(std::get<0>(struct_.str()), "text");
        EXPECT_EQ(struct_.vec(), std::vector<int>({1, 2, 3}));
    }
    {
        std::optional<s1> const result =
            parse("s1 42 13.0 1 2 3", s1_rule_b, ws);
        EXPECT_TRUE(result);
        s1 const & struct_ = *result;
        EXPECT_EQ(struct_.i(), 42);
        EXPECT_EQ(struct_.str().index(), 1u);
        EXPECT_EQ(std::get<1>(struct_.str()), 13.0);
        EXPECT_EQ(struct_.vec(), std::vector<int>({1, 2, 3}));
    }
    {
        std::optional<s2> const result =
            parse("s2 42 text 1 2 3", s2_rule_a, ws);
        EXPECT_TRUE(result);
        s2 const & struct_ = *result;
        EXPECT_EQ(struct_.i(), 42);
        EXPECT_EQ(struct_.str(), "text");
        EXPECT_EQ(struct_.vec(), std::vector<int>({1, 2, 3}));
    }
    {
        std::optional<s2> const result =
            parse("s2 42 text 1 2 3", s2_rule_b, ws);
        EXPECT_TRUE(result);
        s2 const & struct_ = *result;
        EXPECT_EQ(struct_.i(), 42);
        EXPECT_EQ(struct_.str(), "text");
        EXPECT_EQ(struct_.vec(), std::vector<int>({1, 2, 3}));
    }

    // Use the rule as part of a larger parse.
    {
        std::optional<tuple<int, s0>> const result =
            parse("99 s0 42 text 1 2 3", int_ >> s0_rule, ws);
        auto i_ = get(*result, llong<0>{});
        EXPECT_EQ(i_, 99);
        auto struct_ = get(*result, llong<1>{});
        EXPECT_EQ(struct_.i(), 42);
        EXPECT_EQ(struct_.str(), "text");
        EXPECT_EQ(struct_.vec(), std::vector<int>({1, 2, 3}));
    }
    {
        std::optional<tuple<int, s1>> const result =
            parse("99 s1 42 text 1 2 3", int_ >> s1_rule_a, ws);
        auto i_ = get(*result, llong<0>{});
        EXPECT_EQ(i_, 99);
        auto struct_ = get(*result, llong<1>{});
        EXPECT_EQ(struct_.i(), 42);
        EXPECT_EQ(struct_.str().index(), 0u);
        EXPECT_EQ(std::get<0>(struct_.str()), "text");
        EXPECT_EQ(struct_.vec(), std::vector<int>({1, 2, 3}));
    }
    {
        std::optional<tuple<int, s1>> const result =
            parse("99 s1 42 13.0 1 2 3", int_ >> s1_rule_b, ws);
        auto i_ = get(*result, llong<0>{});
        EXPECT_EQ(i_, 99);
        auto struct_ = get(*result, llong<1>{});
        EXPECT_EQ(struct_.i(), 42);
        EXPECT_EQ(struct_.str().index(), 1u);
        EXPECT_EQ(std::get<1>(struct_.str()), 13.0);
        EXPECT_EQ(struct_.vec(), std::vector<int>({1, 2, 3}));
    }
    {
        std::optional<tuple<int, s2>> const result =
            parse("99 s2 42 text 1 2 3", int_ >> s2_rule_a, ws);
        auto i_ = get(*result, llong<0>{});
        EXPECT_EQ(i_, 99);
        auto struct_ = get(*result, llong<1>{});
        EXPECT_EQ(struct_.i(), 42);
        EXPECT_EQ(struct_.str(), "text");
        EXPECT_EQ(struct_.vec(), std::vector<int>({1, 2, 3}));
    }
    {
        std::optional<tuple<int, s2>> const result =
            parse("99 s2 42 text 1 2 3", int_ >> s2_rule_b, ws);
        auto i_ = get(*result, llong<0>{});
        EXPECT_EQ(i_, 99);
        auto struct_ = get(*result, llong<1>{});
        EXPECT_EQ(struct_.i(), 42);
        EXPECT_EQ(struct_.str(), "text");
        EXPECT_EQ(struct_.vec(), std::vector<int>({1, 2, 3}));
    }

    ////////////////////////////////////////////////////////////////////////////
    // Pass attribute to parse.

    {
        s0 struct_;

        EXPECT_TRUE(parse("s0 42 text 1 2 3", s0_rule, ws, struct_));
        EXPECT_EQ(struct_.i(), 42);
        EXPECT_EQ(struct_.str(), "text");
        EXPECT_EQ(struct_.vec(), std::vector<int>({1, 2, 3}));
    }
    {
        s1 struct_;

        EXPECT_TRUE(parse("s1 42 text 1 2 3", s1_rule_a, ws, struct_));
        EXPECT_EQ(struct_.i(), 42);
        EXPECT_EQ(struct_.str().index(), 0u);
        EXPECT_EQ(std::get<0>(struct_.str()), "text");
        EXPECT_EQ(struct_.vec(), std::vector<int>({1, 2, 3}));
    }
    {
        s1 struct_;

        EXPECT_TRUE(parse("s1 42 13.0 1 2 3", s1_rule_b, ws, struct_));
        EXPECT_EQ(struct_.i(), 42);
        EXPECT_EQ(struct_.str().index(), 1u);
        EXPECT_EQ(std::get<1>(struct_.str()), 13.0);
        EXPECT_EQ(struct_.vec(), std::vector<int>({1, 2, 3}));
    }
    {
        s2 struct_;

        EXPECT_TRUE(parse("s2 42 text 1 2 3", s2_rule_a, ws, struct_));
        EXPECT_EQ(struct_.i(), 42);
        EXPECT_EQ(struct_.str(), "text");
        EXPECT_EQ(struct_.vec(), std::vector<int>({1, 2, 3}));
    }
    {
        s2 struct_;

        EXPECT_TRUE(parse("s2 42 text 1 2 3", s2_rule_b, ws, struct_));
        EXPECT_EQ(struct_.i(), 42);
        EXPECT_EQ(struct_.str(), "text");
        EXPECT_EQ(struct_.vec(), std::vector<int>({1, 2, 3}));
    }

    // Use the rule as part of a larger parse.
    {
        tuple<int, s0> result;

        EXPECT_TRUE(parse("99 s0 42 text 1 2 3", int_ >> s0_rule, ws, result));
        auto i_ = get(result, llong<0>{});
        EXPECT_EQ(i_, 99);
        auto struct_ = get(result, llong<1>{});
        EXPECT_EQ(struct_.i(), 42);
        EXPECT_EQ(struct_.str(), "text");
        EXPECT_EQ(struct_.vec(), std::vector<int>({1, 2, 3}));
    }
    {
        tuple<int, s1> result;

        EXPECT_TRUE(parse("99 s1 42 text 1 2 3", int_ >> s1_rule_a, ws, result));
        auto i_ = get(result, llong<0>{});
        EXPECT_EQ(i_, 99);
        auto struct_ = get(result, llong<1>{});
        EXPECT_EQ(struct_.i(), 42);
        EXPECT_EQ(struct_.str().index(), 0u);
        EXPECT_EQ(std::get<0>(struct_.str()), "text");
        EXPECT_EQ(struct_.vec(), std::vector<int>({1, 2, 3}));
    }
    {
        tuple<int, s1> result;

        EXPECT_TRUE(parse("99 s1 42 13.0 1 2 3", int_ >> s1_rule_b, ws, result));
        auto i_ = get(result, llong<0>{});
        EXPECT_EQ(i_, 99);
        auto struct_ = get(result, llong<1>{});
        EXPECT_EQ(struct_.i(), 42);
        EXPECT_EQ(struct_.str().index(), 1u);
        EXPECT_EQ(std::get<1>(struct_.str()), 13.0);
        EXPECT_EQ(struct_.vec(), std::vector<int>({1, 2, 3}));
    }
    {
        tuple<int, s2> result;

        EXPECT_TRUE(parse("99 s2 42 text 1 2 3", int_ >> s2_rule_a, ws, result));
        auto i_ = get(result, llong<0>{});
        EXPECT_EQ(i_, 99);
        auto struct_ = get(result, llong<1>{});
        EXPECT_EQ(struct_.i(), 42);
        EXPECT_EQ(struct_.str(), "text");
        EXPECT_EQ(struct_.vec(), std::vector<int>({1, 2, 3}));
    }
    {
        tuple<int, s2> result;

        EXPECT_TRUE(parse("99 s2 42 text 1 2 3", int_ >> s2_rule_b, ws, result));
        auto i_ = get(result, llong<0>{});
        EXPECT_EQ(i_, 99);
        auto struct_ = get(result, llong<1>{});
        EXPECT_EQ(struct_.i(), 42);
        EXPECT_EQ(struct_.str(), "text");
        EXPECT_EQ(struct_.vec(), std::vector<int>({1, 2, 3}));
    }
}

TEST(class_type, repeated_seq_parser_struct_rule)
{
    ////////////////////////////////////////////////////////////////////////////
    // Parse-generated attribute.

    {
        std::optional<std::vector<s0>> result =
            parse("s0 42 text 1 2 3 s0 41 texty 1 3 2", *s0_rule, ws);
        EXPECT_TRUE(result);
        std::vector<s0> & structs_ = *result;
        EXPECT_EQ(structs_[0].i(), 42);
        EXPECT_EQ(structs_[0].str(), "text");
        EXPECT_EQ(structs_[0].vec(), std::vector<int>({1, 2, 3}));
        EXPECT_EQ(structs_[1].i(), 41);
        EXPECT_EQ(structs_[1].str(), "texty");
        EXPECT_EQ(structs_[1].vec(), std::vector<int>({1, 3, 2}));
    }
    {
        std::optional<std::vector<s1>> const result =
            parse("s1 42 text 1 2 3 s1 41 texty 1 3 2", *s1_rule_a, ws);
        EXPECT_TRUE(result);
        std::vector<s1> const & structs_ = *result;
        EXPECT_EQ(structs_[0].i(), 42);
        EXPECT_EQ(structs_[0].str().index(), 0u);
        EXPECT_EQ(std::get<0>(structs_[0].str()), "text");
        EXPECT_EQ(structs_[0].vec(), std::vector<int>({1, 2, 3}));
        EXPECT_EQ(structs_[1].i(), 41);
        EXPECT_EQ(structs_[1].str().index(), 0u);
        EXPECT_EQ(std::get<0>(structs_[1].str()), "texty");
        EXPECT_EQ(structs_[1].vec(), std::vector<int>({1, 3, 2}));
    }
    {
        std::optional<std::vector<s1>> const result =
            parse("s1 42 13.0 1 2 3 s1 41 12.0 1 3 2", *s1_rule_b, ws);
        EXPECT_TRUE(result);
        std::vector<s1> const & structs_ = *result;
        EXPECT_EQ(structs_[0].i(), 42);
        EXPECT_EQ(structs_[0].str().index(), 1u);
        EXPECT_EQ(std::get<1>(structs_[0].str()), 13.0);
        EXPECT_EQ(structs_[0].vec(), std::vector<int>({1, 2, 3}));
        EXPECT_EQ(structs_[1].i(), 41);
        EXPECT_EQ(structs_[1].str().index(), 1u);
        EXPECT_EQ(std::get<1>(structs_[1].str()), 12.0);
        EXPECT_EQ(structs_[1].vec(), std::vector<int>({1, 3, 2}));
    }
    {
        std::optional<std::vector<s2>> const result =
            parse("s2 42 text 1 2 3 s2 41 texty 1 3 2", *s2_rule_a, ws);
        EXPECT_TRUE(result);
        std::vector<s2> const & structs_ = *result;
        EXPECT_EQ(structs_[0].i(), 42);
        EXPECT_EQ(structs_[0].str(), "text");
        EXPECT_EQ(structs_[0].vec(), std::vector<int>({1, 2, 3}));
        EXPECT_EQ(structs_[1].i(), 41);
        EXPECT_EQ(structs_[1].str(), "texty");
        EXPECT_EQ(structs_[1].vec(), std::vector<int>({1, 3, 2}));
    }
    {
        std::optional<std::vector<s2>> const result =
            parse("s2 42 text 1 2 3 s2 41 texty 1 3 2", *s2_rule_b, ws);
        EXPECT_TRUE(result);
        std::vector<s2> const & structs_ = *result;
        EXPECT_EQ(structs_[0].i(), 42);
        EXPECT_EQ(structs_[0].str(), "text");
        EXPECT_EQ(structs_[0].vec(), std::vector<int>({1, 2, 3}));
        EXPECT_EQ(structs_[1].i(), 41);
        EXPECT_EQ(structs_[1].str(), "texty");
        EXPECT_EQ(structs_[1].vec(), std::vector<int>({1, 3, 2}));
    }

    // Use the rule as part of a larger parse.
    {
        std::optional<tuple<int, std::vector<s0>>> const result =
            parse("99 s0 42 text 1 2 3 s0 41 texty 1 3 2", int_ >> *s0_rule, ws);
        auto i_ = get(*result, llong<0>{});
        EXPECT_EQ(i_, 99);
        auto structs_ = get(*result, llong<1>{});
        EXPECT_EQ(structs_[0].i(), 42);
        EXPECT_EQ(structs_[0].str(), "text");
        EXPECT_EQ(structs_[0].vec(), std::vector<int>({1, 2, 3}));
        EXPECT_EQ(structs_[1].i(), 41);
        EXPECT_EQ(structs_[1].str(), "texty");
        EXPECT_EQ(structs_[1].vec(), std::vector<int>({1, 3, 2}));
    }
    {
        std::optional<tuple<int, std::vector<s1>>> const result =
            parse("99 s1 42 text 1 2 3 s1 41 texty 1 3 2", int_ >> *s1_rule_a, ws);
        auto i_ = get(*result, llong<0>{});
        EXPECT_EQ(i_, 99);
        auto structs_ = get(*result, llong<1>{});
        EXPECT_EQ(structs_[0].i(), 42);
        EXPECT_EQ(structs_[0].str().index(), 0u);
        EXPECT_EQ(std::get<0>(structs_[0].str()), "text");
        EXPECT_EQ(structs_[0].vec(), std::vector<int>({1, 2, 3}));
        EXPECT_EQ(structs_[1].i(), 41);
        EXPECT_EQ(structs_[1].str().index(), 0u);
        EXPECT_EQ(std::get<0>(structs_[1].str()), "texty");
        EXPECT_EQ(structs_[1].vec(), std::vector<int>({1, 3, 2}));
    }
    {
        std::optional<tuple<int, std::vector<s1>>> const result =
            parse("99 s1 42 13.0 1 2 3 s1 41 12.0 1 3 2", int_ >> *s1_rule_b, ws);
        auto i_ = get(*result, llong<0>{});
        EXPECT_EQ(i_, 99);
        auto structs_ = get(*result, llong<1>{});
        EXPECT_EQ(structs_[0].i(), 42);
        EXPECT_EQ(structs_[0].str().index(), 1u);
        EXPECT_EQ(std::get<1>(structs_[0].str()), 13.0);
        EXPECT_EQ(structs_[0].vec(), std::vector<int>({1, 2, 3}));
        EXPECT_EQ(structs_[1].i(), 41);
        EXPECT_EQ(structs_[1].str().index(), 1u);
        EXPECT_EQ(std::get<1>(structs_[1].str()), 12.0);
        EXPECT_EQ(structs_[1].vec(), std::vector<int>({1, 3, 2}));
    }
    {
        std::optional<tuple<int, std::vector<s2>>> const result =
            parse("99 s2 42 text 1 2 3 s2 41 texty 1 3 2", int_ >> *s2_rule_a, ws);
        auto i_ = get(*result, llong<0>{});
        EXPECT_EQ(i_, 99);
        auto structs_ = get(*result, llong<1>{});
        EXPECT_EQ(structs_[0].i(), 42);
        EXPECT_EQ(structs_[0].str(), "text");
        EXPECT_EQ(structs_[0].vec(), std::vector<int>({1, 2, 3}));
        EXPECT_EQ(structs_[1].i(), 41);
        EXPECT_EQ(structs_[1].str(), "texty");
        EXPECT_EQ(structs_[1].vec(), std::vector<int>({1, 3, 2}));
    }
    {
        std::optional<tuple<int, std::vector<s2>>> const result =
            parse("99 s2 42 text 1 2 3 s2 41 texty 1 3 2", int_ >> *s2_rule_b, ws);
        auto i_ = get(*result, llong<0>{});
        EXPECT_EQ(i_, 99);
        auto structs_ = get(*result, llong<1>{});
        EXPECT_EQ(structs_[0].i(), 42);
        EXPECT_EQ(structs_[0].str(), "text");
        EXPECT_EQ(structs_[0].vec(), std::vector<int>({1, 2, 3}));
        EXPECT_EQ(structs_[1].i(), 41);
        EXPECT_EQ(structs_[1].str(), "texty");
        EXPECT_EQ(structs_[1].vec(), std::vector<int>({1, 3, 2}));
    }

    ////////////////////////////////////////////////////////////////////////////
    // Pass attribute to parse.

    {
        std::vector<s0> structs_;

        EXPECT_TRUE(parse(
            "s0 42 text 1 2 3 s0 41 texty 1 3 2", *s0_rule, ws, structs_));
        EXPECT_EQ(structs_[0].i(), 42);
        EXPECT_EQ(structs_[0].str(), "text");
        EXPECT_EQ(structs_[0].vec(), std::vector<int>({1, 2, 3}));
        EXPECT_EQ(structs_[1].i(), 41);
        EXPECT_EQ(structs_[1].str(), "texty");
        EXPECT_EQ(structs_[1].vec(), std::vector<int>({1, 3, 2}));
    }
    {
        std::vector<s1> structs_;

        EXPECT_TRUE(parse(
            "s1 42 text 1 2 3 s1 41 texty 1 3 2", *s1_rule_a, ws, structs_));
        EXPECT_EQ(structs_[0].i(), 42);
        EXPECT_EQ(structs_[0].str().index(), 0u);
        EXPECT_EQ(std::get<0>(structs_[0].str()), "text");
        EXPECT_EQ(structs_[0].vec(), std::vector<int>({1, 2, 3}));
        EXPECT_EQ(structs_[1].i(), 41);
        EXPECT_EQ(structs_[1].str().index(), 0u);
        EXPECT_EQ(std::get<0>(structs_[1].str()), "texty");
        EXPECT_EQ(structs_[1].vec(), std::vector<int>({1, 3, 2}));
    }
    {
        std::vector<s1> structs_;

        EXPECT_TRUE(parse(
            "s1 42 13.0 1 2 3 s1 41 12.0 1 3 2", *s1_rule_b, ws, structs_));
        EXPECT_EQ(structs_[0].i(), 42);
        EXPECT_EQ(structs_[0].str().index(), 1u);
        EXPECT_EQ(std::get<1>(structs_[0].str()), 13.0);
        EXPECT_EQ(structs_[0].vec(), std::vector<int>({1, 2, 3}));
        EXPECT_EQ(structs_[1].i(), 41);
        EXPECT_EQ(structs_[1].str().index(), 1u);
        EXPECT_EQ(std::get<1>(structs_[1].str()), 12.0);
        EXPECT_EQ(structs_[1].vec(), std::vector<int>({1, 3, 2}));
    }
    {
        std::vector<s2> structs_;

        EXPECT_TRUE(parse(
            "s2 42 text 1 2 3 s2 41 texty 1 3 2", *s2_rule_a, ws, structs_));
        EXPECT_EQ(structs_[0].i(), 42);
        EXPECT_EQ(structs_[0].str(), "text");
        EXPECT_EQ(structs_[0].vec(), std::vector<int>({1, 2, 3}));
        EXPECT_EQ(structs_[1].i(), 41);
        EXPECT_EQ(structs_[1].str(), "texty");
        EXPECT_EQ(structs_[1].vec(), std::vector<int>({1, 3, 2}));
    }
    {
        std::vector<s2> structs_;

        EXPECT_TRUE(parse(
            "s2 42 text 1 2 3 s2 41 texty 1 3 2", *s2_rule_b, ws, structs_));
        EXPECT_EQ(structs_[0].i(), 42);
        EXPECT_EQ(structs_[0].str(), "text");
        EXPECT_EQ(structs_[0].vec(), std::vector<int>({1, 2, 3}));
        EXPECT_EQ(structs_[1].i(), 41);
        EXPECT_EQ(structs_[1].str(), "texty");
        EXPECT_EQ(structs_[1].vec(), std::vector<int>({1, 3, 2}));
    }

    // Use the rule as part of a larger parse.
    {
        tuple<int, std::vector<s0>> result;

        EXPECT_TRUE(parse(
            "99 s0 42 text 1 2 3 s0 41 texty 1 3 2",
            int_ >> *s0_rule,
            ws,
            result));
        auto i_ = get(result, llong<0>{});
        EXPECT_EQ(i_, 99);
        auto structs_ = get(result, llong<1>{});
        EXPECT_EQ(structs_[0].i(), 42);
        EXPECT_EQ(structs_[0].str(), "text");
        EXPECT_EQ(structs_[0].vec(), std::vector<int>({1, 2, 3}));
        EXPECT_EQ(structs_[1].i(), 41);
        EXPECT_EQ(structs_[1].str(), "texty");
        EXPECT_EQ(structs_[1].vec(), std::vector<int>({1, 3, 2}));
    }
    {
        tuple<int, std::vector<s1>> result;

        EXPECT_TRUE(parse(
            "99 s1 42 text 1 2 3 s1 41 texty 1 3 2",
            int_ >> *s1_rule_a,
            ws,
            result));
        auto i_ = get(result, llong<0>{});
        EXPECT_EQ(i_, 99);
        auto structs_ = get(result, llong<1>{});
        EXPECT_EQ(structs_[0].i(), 42);
        EXPECT_EQ(structs_[0].str().index(), 0u);
        EXPECT_EQ(std::get<0>(structs_[0].str()), "text");
        EXPECT_EQ(structs_[0].vec(), std::vector<int>({1, 2, 3}));
        EXPECT_EQ(structs_[1].i(), 41);
        EXPECT_EQ(structs_[1].str().index(), 0u);
        EXPECT_EQ(std::get<0>(structs_[1].str()), "texty");
        EXPECT_EQ(structs_[1].vec(), std::vector<int>({1, 3, 2}));
    }
    {
        tuple<int, std::vector<s1>> result;

        EXPECT_TRUE(parse(
            "99 s1 42 13.0 1 2 3 s1 41 12.0 1 3 2",
            int_ >> *s1_rule_b,
            ws,
            result));
        auto i_ = get(result, llong<0>{});
        EXPECT_EQ(i_, 99);
        auto structs_ = get(result, llong<1>{});
        EXPECT_EQ(structs_[0].i(), 42);
        EXPECT_EQ(structs_[0].str().index(), 1u);
        EXPECT_EQ(std::get<1>(structs_[0].str()), 13.0);
        EXPECT_EQ(structs_[0].vec(), std::vector<int>({1, 2, 3}));
        EXPECT_EQ(structs_[1].i(), 41);
        EXPECT_EQ(structs_[1].str().index(), 1u);
        EXPECT_EQ(std::get<1>(structs_[1].str()), 12.0);
        EXPECT_EQ(structs_[1].vec(), std::vector<int>({1, 3, 2}));
    }
    {
        tuple<int, std::vector<s2>> result;

        EXPECT_TRUE(parse(
            "99 s2 42 text 1 2 3 s2 41 texty 1 3 2",
            int_ >> *s2_rule_a,
            ws,
            result));
        auto i_ = get(result, llong<0>{});
        EXPECT_EQ(i_, 99);
        auto structs_ = get(result, llong<1>{});
        EXPECT_EQ(structs_[0].i(), 42);
        EXPECT_EQ(structs_[0].str(), "text");
        EXPECT_EQ(structs_[0].vec(), std::vector<int>({1, 2, 3}));
        EXPECT_EQ(structs_[1].i(), 41);
        EXPECT_EQ(structs_[1].str(), "texty");
        EXPECT_EQ(structs_[1].vec(), std::vector<int>({1, 3, 2}));
    }
    {
        tuple<int, std::vector<s2>> result;

        EXPECT_TRUE(parse(
            "99 s2 42 text 1 2 3 s2 41 texty 1 3 2",
            int_ >> *s2_rule_b,
            ws,
            result));
        auto i_ = get(result, llong<0>{});
        EXPECT_EQ(i_, 99);
        auto structs_ = get(result, llong<1>{});
        EXPECT_EQ(structs_[0].i(), 42);
        EXPECT_EQ(structs_[0].str(), "text");
        EXPECT_EQ(structs_[0].vec(), std::vector<int>({1, 2, 3}));
        EXPECT_EQ(structs_[1].i(), 41);
        EXPECT_EQ(structs_[1].str(), "texty");
        EXPECT_EQ(structs_[1].vec(), std::vector<int>({1, 3, 2}));
    }
}

struct callbacks_t
{
    void operator()(s0_rule_tag, s0 s) const { s0s.push_back(std::move(s)); }
    void operator()(s1_rule_a_tag, s1 s) const { s1s.push_back(std::move(s)); }
    void operator()(s1_rule_b_tag, s1 s) const { s1s.push_back(std::move(s)); }
    void operator()(s2_rule_a_tag, s2 s) const { s2s.push_back(std::move(s)); }
    void operator()(s2_rule_b_tag, s2 s) const { s2s.push_back(std::move(s)); }

    mutable std::vector<s0> s0s;
    mutable std::vector<s1> s1s;
    mutable std::vector<s2> s2s;
};

TEST(class_type, seq_parser_struct_cb_rule)
{
    {
        callbacks_t callbacks;
        EXPECT_TRUE(callback_parse("s0 42 text 1 2 3", s0_rule, ws, callbacks));
        EXPECT_EQ(callbacks.s0s.size(), 1u);
        s0 const & struct_ = callbacks.s0s[0];
        EXPECT_EQ(struct_.i(), 42);
        EXPECT_EQ(struct_.str(), "text");
        EXPECT_EQ(struct_.vec(), std::vector<int>({1, 2, 3}));
    }
    {
        callbacks_t callbacks;
            EXPECT_TRUE(callback_parse("s1 42 text 1 2 3", s1_rule_a, ws, callbacks));
        EXPECT_EQ(callbacks.s1s.size(), 1u);
        s1 const & struct_ = callbacks.s1s[0];
        EXPECT_EQ(struct_.i(), 42);
        EXPECT_EQ(struct_.str().index(), 0u);
        EXPECT_EQ(std::get<0>(struct_.str()), "text");
        EXPECT_EQ(struct_.vec(), std::vector<int>({1, 2, 3}));
    }
    {
        callbacks_t callbacks;
            EXPECT_TRUE(callback_parse("s1 42 13.0 1 2 3", s1_rule_b, ws, callbacks));
        EXPECT_EQ(callbacks.s1s.size(), 1u);
        s1 const & struct_ = callbacks.s1s[0];
        EXPECT_EQ(struct_.i(), 42);
        EXPECT_EQ(struct_.str().index(), 1u);
        EXPECT_EQ(std::get<1>(struct_.str()), 13.0);
        EXPECT_EQ(struct_.vec(), std::vector<int>({1, 2, 3}));
    }
    {
        callbacks_t callbacks;
            EXPECT_TRUE(callback_parse("s2 42 text 1 2 3", s2_rule_a, ws, callbacks));
        EXPECT_EQ(callbacks.s2s.size(), 1u);
        s2 const & struct_ = callbacks.s2s[0];
        EXPECT_EQ(struct_.i(), 42);
        EXPECT_EQ(struct_.str(), "text");
        EXPECT_EQ(struct_.vec(), std::vector<int>({1, 2, 3}));
    }
    {
        callbacks_t callbacks;
            EXPECT_TRUE(callback_parse("s2 42 text 1 2 3", s2_rule_b, ws, callbacks));
        EXPECT_EQ(callbacks.s2s.size(), 1u);
        s2 const & struct_ = callbacks.s2s[0];
        EXPECT_EQ(struct_.i(), 42);
        EXPECT_EQ(struct_.str(), "text");
        EXPECT_EQ(struct_.vec(), std::vector<int>({1, 2, 3}));
    }

    // Use the rule as part of a larger parse.
    {
        callbacks_t callbacks;
        EXPECT_TRUE(callback_parse(
            "99 s0 42 text 1 2 3", int_ >> s0_rule, ws, callbacks));
        EXPECT_EQ(callbacks.s0s.size(), 1u);
        s0 const & struct_ = callbacks.s0s[0];
        EXPECT_EQ(struct_.i(), 42);
        EXPECT_EQ(struct_.str(), "text");
        EXPECT_EQ(struct_.vec(), std::vector<int>({1, 2, 3}));
    }
    {
        callbacks_t callbacks;
        EXPECT_TRUE(callback_parse(
            "99 s1 42 text 1 2 3", int_ >> s1_rule_a, ws, callbacks));
        EXPECT_EQ(callbacks.s1s.size(), 1u);
        s1 const & struct_ = callbacks.s1s[0];
        EXPECT_EQ(struct_.i(), 42);
        EXPECT_EQ(struct_.str().index(), 0u);
        EXPECT_EQ(std::get<0>(struct_.str()), "text");
        EXPECT_EQ(struct_.vec(), std::vector<int>({1, 2, 3}));
    }
    {
        callbacks_t callbacks;
        EXPECT_TRUE(callback_parse(
            "99 s1 42 13.0 1 2 3", int_ >> s1_rule_b, ws, callbacks));
        EXPECT_EQ(callbacks.s1s.size(), 1u);
        s1 const & struct_ = callbacks.s1s[0];
        EXPECT_EQ(struct_.i(), 42);
        EXPECT_EQ(struct_.str().index(), 1u);
        EXPECT_EQ(std::get<1>(struct_.str()), 13.0);
        EXPECT_EQ(struct_.vec(), std::vector<int>({1, 2, 3}));
    }
    {
        callbacks_t callbacks;
        EXPECT_TRUE(callback_parse(
            "99 s2 42 text 1 2 3", int_ >> s2_rule_a, ws, callbacks));
        EXPECT_EQ(callbacks.s2s.size(), 1u);
        s2 const & struct_ = callbacks.s2s[0];
        EXPECT_EQ(struct_.i(), 42);
        EXPECT_EQ(struct_.str(), "text");
        EXPECT_EQ(struct_.vec(), std::vector<int>({1, 2, 3}));
    }
    {
        callbacks_t callbacks;
        EXPECT_TRUE(callback_parse(
            "99 s2 42 text 1 2 3", int_ >> s2_rule_b, ws, callbacks));
        EXPECT_EQ(callbacks.s2s.size(), 1u);
        s2 const & struct_ = callbacks.s2s[0];
        EXPECT_EQ(struct_.i(), 42);
        EXPECT_EQ(struct_.str(), "text");
        EXPECT_EQ(struct_.vec(), std::vector<int>({1, 2, 3}));
    }
}

TEST(class_type, parse_into_struct)
{
    {
        s0 struct_;

        EXPECT_TRUE(parse("s0 42 text 1 2 3", s0_parser, ws, struct_));
        EXPECT_EQ(struct_.i(), 42);
        EXPECT_EQ(struct_.str(), "text");
        EXPECT_EQ(struct_.vec(), std::vector<int>({1, 2, 3}));
    }
    {
        s1 struct_;

        EXPECT_TRUE(parse("s1 42 text 1 2 3", s1_parser_a, ws, struct_));
        EXPECT_EQ(struct_.i(), 42);
        EXPECT_EQ(struct_.str().index(), 0u);
        EXPECT_EQ(std::get<0>(struct_.str()), "text");
        EXPECT_EQ(struct_.vec(), std::vector<int>({1, 2, 3}));
    }
    {
        s1 struct_;

        EXPECT_TRUE(parse("s1 42 13.0 1 2 3", s1_parser_b, ws, struct_));
        EXPECT_EQ(struct_.i(), 42);
        EXPECT_EQ(struct_.str().index(), 1u);
        EXPECT_EQ(std::get<1>(struct_.str()), 13.0);
        EXPECT_EQ(struct_.vec(), std::vector<int>({1, 2, 3}));
    }
    {
        s2 struct_;

        EXPECT_TRUE(parse("s2 42 text 1 2 3", s2_parser_a, ws, struct_));
        EXPECT_EQ(struct_.i(), 42);
        EXPECT_EQ(struct_.str(), "text");
        EXPECT_EQ(struct_.vec(), std::vector<int>({1, 2, 3}));
    }
    {
        s2 struct_;

        EXPECT_TRUE(parse("s2 42 text 1 2 3", s2_parser_b, ws, struct_));
        EXPECT_EQ(struct_.i(), 42);
        EXPECT_EQ(struct_.str(), "text");
        EXPECT_EQ(struct_.vec(), std::vector<int>({1, 2, 3}));
    }
}

TEST(class_type, repeated_parse_into_struct)
{
    {
        std::vector<s0> structs_;

        EXPECT_TRUE(parse(
            "s0 42 text 1 2 3 s0 41 texty 1 3 2", *s0_parser, ws, structs_));
        EXPECT_EQ(structs_[0].i(), 42);
        EXPECT_EQ(structs_[0].str(), "text");
        EXPECT_EQ(structs_[0].vec(), std::vector<int>({1, 2, 3}));
        EXPECT_EQ(structs_[1].i(), 41);
        EXPECT_EQ(structs_[1].str(), "texty");
        EXPECT_EQ(structs_[1].vec(), std::vector<int>({1, 3, 2}));
    }
    {
        std::vector<s1> structs_;

        EXPECT_TRUE(parse(
            "s1 42 text 1 2 3 s1 41 texty 1 3 2", *s1_parser_a, ws, structs_));
        EXPECT_EQ(structs_[0].i(), 42);
        EXPECT_EQ(structs_[0].str().index(), 0u);
        EXPECT_EQ(std::get<0>(structs_[0].str()), "text");
        EXPECT_EQ(structs_[0].vec(), std::vector<int>({1, 2, 3}));
        EXPECT_EQ(structs_[1].i(), 41);
        EXPECT_EQ(structs_[1].str().index(), 0u);
        EXPECT_EQ(std::get<0>(structs_[1].str()), "texty");
        EXPECT_EQ(structs_[1].vec(), std::vector<int>({1, 3, 2}));
    }
    {
        std::vector<s1> structs_;

        EXPECT_TRUE(parse(
            "s1 42 13.0 1 2 3 s1 41 12.0 1 3 2", *s1_parser_b, ws, structs_));
        EXPECT_EQ(structs_[0].i(), 42);
        EXPECT_EQ(structs_[0].str().index(), 1u);
        EXPECT_EQ(std::get<1>(structs_[0].str()), 13.0);
        EXPECT_EQ(structs_[0].vec(), std::vector<int>({1, 2, 3}));
        EXPECT_EQ(structs_[1].i(), 41);
        EXPECT_EQ(structs_[1].str().index(), 1u);
        EXPECT_EQ(std::get<1>(structs_[1].str()), 12.0);
        EXPECT_EQ(structs_[1].vec(), std::vector<int>({1, 3, 2}));
    }
    {
        std::vector<s2> structs_;

        EXPECT_TRUE(parse(
            "s2 42 text 1 2 3 s2 41 texty 1 3 2", *s2_parser_a, ws, structs_));
        EXPECT_EQ(structs_[0].i(), 42);
        EXPECT_EQ(structs_[0].str(), "text");
        EXPECT_EQ(structs_[0].vec(), std::vector<int>({1, 2, 3}));
        EXPECT_EQ(structs_[1].i(), 41);
        EXPECT_EQ(structs_[1].str(), "texty");
        EXPECT_EQ(structs_[1].vec(), std::vector<int>({1, 3, 2}));
    }
    {
        std::vector<s2> structs_;

        EXPECT_TRUE(parse(
            "s2 42 text 1 2 3 s2 41 texty 1 3 2", *s2_parser_b, ws, structs_));
        EXPECT_EQ(structs_[0].i(), 42);
        EXPECT_EQ(structs_[0].str(), "text");
        EXPECT_EQ(structs_[0].vec(), std::vector<int>({1, 2, 3}));
        EXPECT_EQ(structs_[1].i(), 41);
        EXPECT_EQ(structs_[1].str(), "texty");
        EXPECT_EQ(structs_[1].vec(), std::vector<int>({1, 3, 2}));
    }
}
