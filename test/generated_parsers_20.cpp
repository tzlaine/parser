// WARNING!  This file is generated.
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
using boost::is_same;
using boost::optional;
using boost::variant;
using boost::hana::tuple;

char const g_chars[] = "";
auto g_first = std::begin(g_chars);
auto const g_last = std::end(g_chars);


}

TEST(parser, generated_20_000)
{
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | -(-int_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, optional<std::vector<optional<int>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ | eps | -int_ | eps) >> (-int_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | (eps >> -int_ >> eps >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, tuple<optional<int>, std::vector<char>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (eps | -int_ | eps | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> eps) | -(eps >> -int_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<optional<std::vector<optional<int>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_001)
{
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (eps | -int_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | (*char_ >> -int_ >> eps >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, tuple<std::vector<char>, std::vector<optional<int>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ | eps | -int_ | eps) >> (*char_ | -int_ | eps | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | -(-int_ >> eps >> *char_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, optional<tuple<optional<int>, std::vector<char>, optional<int>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (-int_ | eps | *char_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_002)
{
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> eps) | (*char_ >> eps >> *char_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<std::vector<optional<int>>>, tuple<std::vector<char>, optional<int>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (*char_ | eps | *char_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | -(*char_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, optional<std::vector<char>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ | eps | -int_ | eps) >> (*char_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, std::vector<char>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | (-int_ >> eps >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_003)
{
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (-int_ | eps | -int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> eps) | -(-int_ >> eps >> -int_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<std::vector<optional<int>>>, optional<tuple<std::vector<optional<int>>, std::vector<char>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (-int_ | eps | -int_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | (eps >> eps >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, std::vector<char>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ | eps | -int_ | eps) >> (eps | eps | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<std::vector<char>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_004)
{
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | -(-int_ >> -int_ >> *char_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, optional<tuple<std::vector<optional<int>>, std::vector<char>, optional<int>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (-int_ | -int_ | *char_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, variant<optional<int>, std::vector<char>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> eps) | (eps >> *char_ >> eps >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<std::vector<optional<int>>>, tuple<std::vector<char>, optional<int>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (eps | *char_ | eps | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | -(-int_ >> *char_ >> eps >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, optional<tuple<optional<int>, std::vector<char>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_005)
{
    {
        constexpr auto parser = -(-int_ | eps | -int_ | eps) >> (-int_ | *char_ | eps | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | (eps >> -int_ >> *char_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, tuple<optional<int>, std::vector<char>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (eps | -int_ | *char_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> eps) | -(-int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<std::vector<optional<int>>>, optional<int>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (-int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_006)
{
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | (-int_ >> *char_ >> *char_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, tuple<optional<int>, std::vector<char>, optional<int>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ | eps | -int_ | eps) >> (-int_ | *char_ | *char_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, variant<optional<int>, std::vector<char>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | -(eps >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, optional<int>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (eps | -int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> eps) | (*char_ >> -int_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<std::vector<optional<int>>>, tuple<std::vector<char>, std::vector<optional<int>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_007)
{
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (*char_ | -int_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, variant<std::vector<char>, optional<int>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | -(-int_ >> *char_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, optional<tuple<optional<int>, std::vector<char>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ | eps | -int_ | eps) >> (-int_ | *char_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | (-int_ >> -int_ >> *char_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, tuple<std::vector<optional<int>>, std::vector<char>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (-int_ | -int_ | *char_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, variant<optional<int>, std::vector<char>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_008)
{
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> eps) | -(*char_ >> -int_ >> -int_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<std::vector<optional<int>>>, optional<tuple<std::vector<char>, std::vector<optional<int>>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (*char_ | -int_ | -int_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, variant<std::vector<char>, optional<int>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | (eps >> -int_ >> *char_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, tuple<optional<int>, std::vector<char>, optional<int>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ | eps | -int_ | eps) >> (eps | -int_ | *char_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | -(*char_ >> *char_ >> eps >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, optional<tuple<std::vector<char>, optional<int>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_009)
{
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (*char_ | *char_ | eps | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> eps) | (eps >> *char_ >> eps >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<std::vector<optional<int>>>, std::vector<char>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (eps | *char_ | eps | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<std::vector<char>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | -(-int_ >> -int_ >> *char_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, optional<tuple<std::vector<optional<int>>, std::vector<char>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ | eps | -int_ | eps) >> (-int_ | -int_ | *char_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_010)
{
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | (eps >> *char_ >> eps >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, std::vector<char>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (eps | *char_ | eps | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<std::vector<char>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> eps) | -(eps >> -int_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<std::vector<optional<int>>>, optional<tuple<optional<int>, std::vector<char>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (eps | -int_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | (-int_ >> eps >> -int_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_011)
{
    {
        constexpr auto parser = -(-int_ | eps | -int_ | eps) >> (-int_ | eps | -int_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | -(eps >> eps >> -int_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, optional<tuple<optional<int>, std::vector<char>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (eps | eps | -int_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> eps) | (-int_ >> *char_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<std::vector<optional<int>>>, tuple<optional<int>, std::vector<char>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (-int_ | *char_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, variant<optional<int>, std::vector<char>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_012)
{
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | -(eps >> eps >> *char_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, optional<tuple<std::vector<char>, optional<int>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ | eps | -int_ | eps) >> (eps | eps | *char_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | (*char_ >> eps >> *char_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, std::vector<char>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (*char_ | eps | *char_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<std::vector<char>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> eps) | -(-int_ >> eps >> *char_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<std::vector<optional<int>>>, optional<tuple<optional<int>, std::vector<char>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_013)
{
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (-int_ | eps | *char_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | (eps >> -int_ >> eps >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, optional<int>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ | eps | -int_ | eps) >> (eps | -int_ | eps | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | -(*char_ >> eps >> -int_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (*char_ | eps | -int_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_014)
{
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> eps) | (*char_ >> eps >> *char_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<std::vector<optional<int>>>, std::vector<char>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (*char_ | eps | *char_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<std::vector<char>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | -(-int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, optional<int>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ | eps | -int_ | eps) >> (-int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | (eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<optional<std::vector<optional<int>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_015)
{
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<optional<int>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> eps) | -(eps >> eps >> *char_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<std::vector<optional<int>>>, optional<std::vector<char>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (eps | eps | *char_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<std::vector<char>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | (eps >> eps >> *char_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, std::vector<char>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ | eps | -int_ | eps) >> (eps | eps | *char_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<std::vector<char>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_016)
{
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | -(*char_ >> *char_ >> eps >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, optional<std::vector<char>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (*char_ | *char_ | eps | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<std::vector<char>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> eps) | (eps >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<std::vector<optional<int>>>, optional<int>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (eps | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | -(*char_ >> *char_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, optional<tuple<std::vector<char>, optional<int>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_017)
{
    {
        constexpr auto parser = -(-int_ | eps | -int_ | eps) >> (*char_ | *char_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, variant<std::vector<char>, optional<int>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | (*char_ >> eps >> eps >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, tuple<std::vector<char>, optional<int>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (*char_ | eps | eps | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> eps) | -(*char_ >> *char_ >> eps >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<std::vector<optional<int>>>, optional<std::vector<char>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (*char_ | *char_ | eps | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<std::vector<char>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_018)
{
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | (*char_ >> eps >> -int_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, tuple<std::vector<char>, std::vector<optional<int>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ | eps | -int_ | eps) >> (*char_ | eps | -int_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | -(*char_ >> -int_ >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, optional<tuple<std::vector<char>, std::vector<optional<int>>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (*char_ | -int_ | -int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> eps) | (*char_ >> *char_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<std::vector<optional<int>>>, std::vector<char>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_019)
{
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (*char_ | *char_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<std::vector<char>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | -(*char_ >> -int_ >> -int_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, optional<tuple<std::vector<char>, std::vector<optional<int>>, std::vector<char>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ | eps | -int_ | eps) >> (*char_ | -int_ | -int_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, variant<std::vector<char>, optional<int>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | (-int_ >> -int_ >> eps >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (-int_ | -int_ | eps | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_020)
{
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> eps) | -(-int_ >> *char_ >> *char_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<std::vector<optional<int>>>, optional<tuple<optional<int>, std::vector<char>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (-int_ | *char_ | *char_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | (eps >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, std::vector<char>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ | eps | -int_ | eps) >> (eps | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<std::vector<char>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | -(-int_ >> *char_ >> eps >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, optional<tuple<optional<int>, std::vector<char>, optional<int>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_021)
{
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (-int_ | *char_ | eps | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> eps) | (-int_ >> -int_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<std::vector<optional<int>>>, tuple<std::vector<optional<int>>, std::vector<char>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (-int_ | -int_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, variant<optional<int>, std::vector<char>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | -(eps >> *char_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, optional<std::vector<char>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ | eps | -int_ | eps) >> (eps | *char_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<std::vector<char>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_022)
{
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | (eps >> -int_ >> *char_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, tuple<optional<int>, std::vector<char>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (eps | -int_ | *char_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> eps) | -(*char_ >> -int_ >> *char_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<std::vector<optional<int>>>, optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (*char_ | -int_ | *char_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, variant<std::vector<char>, optional<int>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | (eps >> *char_ >> *char_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, std::vector<char>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_023)
{
    {
        constexpr auto parser = -(-int_ | eps | -int_ | eps) >> (eps | *char_ | *char_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<std::vector<char>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | -(*char_ >> *char_ >> -int_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (*char_ | *char_ | -int_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, variant<std::vector<char>, optional<int>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> eps) | (*char_ >> *char_ >> -int_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<std::vector<optional<int>>>, tuple<std::vector<char>, std::vector<optional<int>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (*char_ | *char_ | -int_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, variant<std::vector<char>, optional<int>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_024)
{
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | -(*char_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, optional<tuple<std::vector<char>, optional<int>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ | eps | -int_ | eps) >> (*char_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, variant<std::vector<char>, optional<int>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | (eps >> *char_ >> *char_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, std::vector<char>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (eps | *char_ | *char_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<std::vector<char>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> eps) | -(*char_ >> -int_ >> eps >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<std::vector<optional<int>>>, optional<tuple<std::vector<char>, optional<int>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_025)
{
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (*char_ | -int_ | eps | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | (eps >> -int_ >> -int_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ | eps | -int_ | eps) >> (eps | -int_ | -int_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | -(*char_ >> -int_ >> *char_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (*char_ | -int_ | *char_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_026)
{
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> eps) | (*char_ >> -int_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<std::vector<optional<int>>>, tuple<std::vector<char>, optional<int>, std::vector<char>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (*char_ | -int_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, variant<std::vector<char>, optional<int>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | -(-int_ >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, optional<std::vector<optional<int>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ | eps | -int_ | eps) >> (-int_ | -int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | (eps >> *char_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, std::vector<char>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_027)
{
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (eps | *char_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<std::vector<char>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> eps) | -(-int_ >> eps >> eps >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<std::vector<optional<int>>>, optional<int>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (-int_ | eps | eps | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | (eps >> eps >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, optional<int>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ | eps | -int_ | eps) >> (eps | eps | -int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_028)
{
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | -(-int_ >> *char_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, optional<tuple<optional<int>, std::vector<char>, optional<int>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (-int_ | *char_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, variant<optional<int>, std::vector<char>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> eps) | (*char_ >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<std::vector<optional<int>>>, tuple<std::vector<char>, optional<int>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (*char_ | -int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | -(eps >> eps >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, optional<int>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_029)
{
    {
        constexpr auto parser = -(-int_ | eps | -int_ | eps) >> (eps | eps | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | (eps >> *char_ >> -int_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, tuple<std::vector<char>, std::vector<optional<int>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (eps | *char_ | -int_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> eps) | -(-int_ >> eps >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<optional<std::vector<optional<int>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (-int_ | eps | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_030)
{
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | (*char_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, std::vector<char>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ | eps | -int_ | eps) >> (*char_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<std::vector<char>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | -(eps >> *char_ >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, optional<tuple<std::vector<char>, optional<int>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (eps | *char_ | -int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> eps) | (*char_ >> eps >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<std::vector<optional<int>>>, tuple<std::vector<char>, optional<int>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_031)
{
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (*char_ | eps | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | -(*char_ >> eps >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, optional<std::vector<char>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ | eps | -int_ | eps) >> (*char_ | eps | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<std::vector<char>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | (eps >> eps >> -int_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (eps | eps | -int_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_032)
{
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> eps) | -(-int_ >> *char_ >> -int_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<std::vector<optional<int>>>, optional<tuple<optional<int>, std::vector<char>, optional<int>, std::vector<char>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (-int_ | *char_ | -int_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, variant<optional<int>, std::vector<char>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | (-int_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, tuple<optional<int>, std::vector<char>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ | eps | -int_ | eps) >> (-int_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, variant<optional<int>, std::vector<char>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | -(-int_ >> *char_ >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, optional<tuple<optional<int>, std::vector<char>, optional<int>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_033)
{
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (-int_ | *char_ | -int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> eps) | (-int_ >> *char_ >> *char_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<std::vector<optional<int>>>, tuple<optional<int>, std::vector<char>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (-int_ | *char_ | *char_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, variant<optional<int>, std::vector<char>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | -(-int_ >> eps >> eps >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, optional<std::vector<optional<int>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ | eps | -int_ | eps) >> (-int_ | eps | eps | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_034)
{
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | (-int_ >> *char_ >> eps >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, tuple<optional<int>, std::vector<char>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (-int_ | *char_ | eps | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> eps) | -(-int_ >> eps >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<std::vector<optional<int>>>, optional<tuple<optional<int>, std::vector<char>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (-int_ | eps | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | (eps >> -int_ >> -int_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, tuple<std::vector<optional<int>>, std::vector<char>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_035)
{
    {
        constexpr auto parser = -(-int_ | eps | -int_ | eps) >> (eps | -int_ | -int_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | -(*char_ >> eps >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, optional<std::vector<char>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (*char_ | eps | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<std::vector<char>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> eps) | (*char_ >> -int_ >> *char_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<std::vector<optional<int>>>, tuple<std::vector<char>, optional<int>, std::vector<char>, optional<int>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (*char_ | -int_ | *char_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, variant<std::vector<char>, optional<int>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_036)
{
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | -(-int_ >> *char_ >> -int_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<optional<int>>, optional<tuple<optional<int>, std::vector<char>, std::vector<optional<int>>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ | eps | -int_ | eps) >> (-int_ | *char_ | -int_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, variant<optional<int>, std::vector<char>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> eps) | (eps >> -int_ >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | eps) >> (eps | -int_ | -int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> *char_) | -(eps >> *char_ >> *char_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<optional<int>>, std::vector<char>>>, optional<tuple<std::vector<char>, optional<int>>>>>>));

        std::string const str = "33cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_037)
{
    {
        constexpr auto parser = (-int_ | eps | -int_ | *char_) >> (eps | *char_ | *char_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> *char_) | (eps >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<optional<tuple<std::vector<optional<int>>, std::vector<char>>>>>));

        std::string const str = "33cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ | eps | -int_ | *char_) >> (eps | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<optional<variant<optional<int>, std::vector<char>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> *char_) | -(*char_ >> *char_ >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<optional<int>>, std::vector<char>>, optional<tuple<std::vector<char>, optional<int>>>>>>));

        std::string const str = "33cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | *char_) >> (*char_ | *char_ | -int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_038)
{
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> *char_) | (*char_ >> -int_ >> eps >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<optional<int>>, std::vector<char>>>, tuple<std::vector<char>, optional<int>, std::vector<char>>>>>));

        std::string const str = "33cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | *char_) >> (*char_ | -int_ | eps | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> *char_) | -(-int_ >> eps >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<optional<int>>, std::vector<char>>, optional<int>>>>));

        std::string const str = "33cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ | eps | -int_ | *char_) >> (-int_ | eps | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<int>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> *char_) | (-int_ >> eps >> eps >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<optional<int>>, std::vector<char>>, tuple<optional<int>, std::vector<char>>>>>));

        std::string const str = "33cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_039)
{
    {
        constexpr auto parser = (-int_ | eps | -int_ | *char_) >> (-int_ | eps | eps | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> *char_) | -(-int_ >> -int_ >> eps >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<optional<int>>, std::vector<char>>>, optional<std::vector<optional<int>>>>>>));

        std::string const str = "33cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | *char_) >> (-int_ | -int_ | eps | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<int>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> *char_) | (-int_ >> eps >> *char_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<optional<int>>, std::vector<char>>, tuple<optional<int>, std::vector<char>>>>>));

        std::string const str = "33cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ | eps | -int_ | *char_) >> (-int_ | eps | *char_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_040)
{
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> *char_) | -(-int_ >> -int_ >> eps >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<optional<int>>, std::vector<char>>, optional<tuple<std::vector<optional<int>>, std::vector<char>>>>>>));

        std::string const str = "33cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | *char_) >> (-int_ | -int_ | eps | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> *char_) | (eps >> -int_ >> eps >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<optional<int>>, std::vector<char>>>, std::vector<optional<int>>>>>));

        std::string const str = "33cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | *char_) >> (eps | -int_ | eps | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<int>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> *char_) | -(*char_ >> eps >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<optional<int>>, std::vector<char>>, optional<tuple<std::vector<char>, optional<int>>>>>>));

        std::string const str = "33cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_041)
{
    {
        constexpr auto parser = -(-int_ | eps | -int_ | *char_) >> (*char_ | eps | -int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> *char_) | (*char_ >> eps >> eps >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<optional<int>>, std::vector<char>>, std::vector<char>>>>));

        std::string const str = "33cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | *char_) >> (*char_ | eps | eps | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<std::vector<char>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> *char_) | -(eps >> *char_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<optional<int>>, std::vector<char>>>, optional<tuple<std::vector<char>, optional<int>>>>>>));

        std::string const str = "33cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | *char_) >> (eps | *char_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_042)
{
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> *char_) | (*char_ >> eps >> eps >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<optional<int>>, std::vector<char>>, std::vector<char>>>>));

        std::string const str = "33cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ | eps | -int_ | *char_) >> (*char_ | eps | eps | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<std::vector<char>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> *char_) | -(eps >> *char_ >> -int_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<optional<int>>, std::vector<char>>, optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>>>>));

        std::string const str = "33cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | *char_) >> (eps | *char_ | -int_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> *char_) | (*char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<optional<int>>, std::vector<char>>>, std::vector<char>>>>));

        std::string const str = "33cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_043)
{
    {
        constexpr auto parser = (-int_ | eps | -int_ | *char_) >> (*char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, std::vector<char>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> *char_) | -(-int_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<optional<int>>, std::vector<char>>, optional<std::vector<optional<int>>>>>>));

        std::string const str = "33cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ | eps | -int_ | *char_) >> (-int_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<int>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> *char_) | (eps >> -int_ >> eps >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<optional<int>>, std::vector<char>>, tuple<optional<int>, std::vector<char>>>>>));

        std::string const str = "33cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | *char_) >> (eps | -int_ | eps | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_044)
{
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> *char_) | -(eps >> -int_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<optional<int>>, std::vector<char>>>, optional<std::vector<optional<int>>>>>>));

        std::string const str = "33cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | *char_) >> (eps | -int_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<int>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> *char_) | (*char_ >> -int_ >> eps >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<optional<int>>, std::vector<char>>, tuple<std::vector<char>, std::vector<optional<int>>>>>>));

        std::string const str = "33cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ | eps | -int_ | *char_) >> (*char_ | -int_ | eps | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> *char_) | -(-int_ >> eps >> *char_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<optional<int>>, std::vector<char>>, optional<tuple<optional<int>, std::vector<char>, optional<int>>>>>>));

        std::string const str = "33cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_045)
{
    {
        constexpr auto parser = (-int_ | eps | -int_ | *char_) >> (-int_ | eps | *char_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> *char_) | (*char_ >> eps >> *char_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<optional<int>>, std::vector<char>>>, tuple<std::vector<char>, optional<int>>>>>));

        std::string const str = "33cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | *char_) >> (*char_ | eps | *char_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> *char_) | -(*char_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<optional<int>>, std::vector<char>>, optional<std::vector<char>>>>>));

        std::string const str = "33cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ | eps | -int_ | *char_) >> (*char_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, std::vector<char>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_046)
{
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> *char_) | (-int_ >> eps >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<optional<int>>, std::vector<char>>, std::vector<optional<int>>>>>));

        std::string const str = "33cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | *char_) >> (-int_ | eps | -int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<int>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> *char_) | -(-int_ >> eps >> -int_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<optional<tuple<std::vector<optional<int>>, std::vector<char>>>>>));

        std::string const str = "33cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | *char_) >> (-int_ | eps | -int_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> *char_) | (eps >> eps >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<optional<int>>, std::vector<char>>, std::vector<char>>>>));

        std::string const str = "33cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_047)
{
    {
        constexpr auto parser = -(-int_ | eps | -int_ | *char_) >> (eps | eps | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<std::vector<char>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> *char_) | -(-int_ >> -int_ >> *char_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<optional<int>>, std::vector<char>>, optional<tuple<std::vector<optional<int>>, std::vector<char>, optional<int>>>>>>));

        std::string const str = "33cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | *char_) >> (-int_ | -int_ | *char_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, variant<optional<int>, std::vector<char>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> *char_) | (eps >> *char_ >> eps >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<optional<int>>, std::vector<char>>>, tuple<std::vector<char>, optional<int>>>>>));

        std::string const str = "33cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | *char_) >> (eps | *char_ | eps | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_048)
{
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> *char_) | -(-int_ >> *char_ >> eps >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<optional<int>>, std::vector<char>>, optional<tuple<optional<int>, std::vector<char>>>>>>));

        std::string const str = "33cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ | eps | -int_ | *char_) >> (-int_ | *char_ | eps | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> *char_) | (eps >> -int_ >> *char_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<optional<int>>, std::vector<char>>, tuple<optional<int>, std::vector<char>>>>>));

        std::string const str = "33cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | *char_) >> (eps | -int_ | *char_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ >> eps >> -int_ >> *char_) | -(-int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<optional<int>>, std::vector<char>>>, optional<int>>>>));

        std::string const str = "33cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_20_049)
{
    {
        constexpr auto parser = (-int_ | eps | -int_ | *char_) >> (-int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<int>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> *char_) | (-int_ >> *char_ >> *char_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<optional<int>>, std::vector<char>>, tuple<optional<int>, std::vector<char>, optional<int>>>>>));

        std::string const str = "33cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(-int_ | eps | -int_ | *char_) >> (-int_ | *char_ | *char_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, variant<optional<int>, std::vector<char>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ >> eps >> -int_ >> *char_) | -(eps >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<optional<int>>, std::vector<char>>, optional<int>>>>));

        std::string const str = "33cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (-int_ | eps | -int_ | *char_) >> (eps | -int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<int>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

