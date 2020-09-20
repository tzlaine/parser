// Copyright (C) 2020 T. Zachary Laine
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#include <boost/parser/parser.hpp>

#include <gtest/gtest.h>


using namespace boost::parser;

rule<class test_rule, std::string> const test_rule = "test_rule";
auto const test_rule_def = +char_;
#if BOOST_PARSER_USE_BOOST
BOOST_PARSER_DEFINE_RULES(test_rule);
#else
BOOST_PARSER_DEFINE_RULE(test_rule);
#endif

rule<class ints, std::vector<int>> const ints = "ints";
auto twenty_zeros = [](auto & ctx) { _val(ctx).resize(20, 0); };
auto push_back = [](auto & ctx) { _val(ctx).push_back(_attr(ctx)); };
auto const ints_def = lit("20-zeros")[twenty_zeros] | +int_[push_back];
#if BOOST_PARSER_USE_BOOST
BOOST_PARSER_DEFINE_RULES(ints);
#else
BOOST_PARSER_DEFINE_RULE(ints);
#endif

TEST(parse_empty, all)
{
    char const * chars = "";
    auto first = chars;
    boost::text::null_sentinel last;

    {
        constexpr auto parser = eps;
        auto result = parse(first, last, parser);
        EXPECT_TRUE(result);
    }
    {
        constexpr auto parser = eol;
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        constexpr auto parser = eoi;
        auto result = parse(first, last, parser);
        EXPECT_TRUE(result);
    }
    {
        constexpr auto parser = attr(3.0);
        auto result = parse(first, last, parser);
        EXPECT_TRUE(result);
    }
    {
        constexpr auto parser = attr('c');
        auto result = parse(first, last, parser);
        EXPECT_TRUE(result);
    }
    {
        constexpr auto parser = cp;
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        constexpr auto parser = cu;
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = 'c'_l;
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = u8'c'_l;
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = U'c'_l;
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = "str"_l;
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = u8"str"_l;
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = U"str"_l;
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = 'c'_p;
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = u8'c'_p;
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = U'c'_p;
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = "str"_p;
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = u8"str"_p;
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = U"str"_p;
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        constexpr auto parser = lit('c');
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        constexpr auto parser = lit(U'c');
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        constexpr auto parser = lit("str");
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        std::string str = "str";
        auto parser = lit(str);
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        constexpr auto parser = bool_;
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        constexpr auto parser = bin;
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        constexpr auto parser = oct;
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        constexpr auto parser = hex;
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        constexpr auto parser = ushort_;
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        constexpr auto parser = uint_;
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        constexpr auto parser = ulong_;
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        constexpr auto parser = ulong_long;
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        constexpr auto parser = short_;
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        constexpr auto parser = int_;
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        constexpr auto parser = long_;
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        constexpr auto parser = long_long;
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        constexpr auto parser = float_;
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        constexpr auto parser = double_;
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        symbols<float> parser;
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        auto const c = [](auto & ctx) { return true; };
        constexpr auto parser = if_(c)[double_];
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        auto const x = [](auto & ctx) { return 2; };
        auto parser = switch_(x)(0, double_)(2, int_);
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }

    {
        constexpr auto parser = int_ | int_;
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        constexpr auto parser = double_ | int_;
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        constexpr auto parser = double_ | int_ | eps;
        auto result = parse(first, last, parser);
        EXPECT_TRUE(result);
    }

    {
        constexpr auto parser = *cu >> string("str");
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
    {
        constexpr auto parser = cu >> string("str");
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }

    {
        auto a = [](auto & ctx) {};
        constexpr auto parser = cu[a];
        auto result = parse(first, last, parser);
        EXPECT_FALSE(result);
    }
}
