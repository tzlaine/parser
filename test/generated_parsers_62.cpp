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

TEST(parser, generated_62_000)
{
    {
        constexpr auto parser = (eps >> -int_ >> *char_ >> *char_) | -(-int_ >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<optional<int>, std::vector<char>>, optional<std::vector<optional<int>>>>>>));

        std::string const str = "3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(eps | -int_ | *char_ | *char_) >> (-int_ | -int_ | eps);
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
        constexpr auto parser = (eps >> -int_ >> *char_ >> *char_) | (eps >> *char_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<optional<int>, std::vector<char>>, std::vector<char>>>>));

        std::string const str = "3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (eps | -int_ | *char_ | *char_) >> (eps | *char_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<std::vector<char>>>>>));

        std::string const str = "";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(eps >> -int_ >> *char_ >> *char_) | -(-int_ >> eps >> eps >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<optional<int>, std::vector<char>>>, optional<int>>>>));

        std::string const str = "3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_001)
{
    {
        constexpr auto parser = (eps | -int_ | *char_ | *char_) >> (-int_ | eps | eps | eps);
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
        constexpr auto parser = (eps >> -int_ >> *char_ >> *char_) | (eps >> eps >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<optional<int>, std::vector<char>>, optional<int>>>>));

        std::string const str = "3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(eps | -int_ | *char_ | *char_) >> (eps | eps | -int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<int>>>>));

        std::string const str = "";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (eps >> -int_ >> *char_ >> *char_) | -(-int_ >> *char_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<optional<int>, std::vector<char>>, optional<tuple<optional<int>, std::vector<char>, optional<int>>>>>>));

        std::string const str = "3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (eps | -int_ | *char_ | *char_) >> (-int_ | *char_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, variant<optional<int>, std::vector<char>>>>>));

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

TEST(parser, generated_62_002)
{
    {
        constexpr auto parser = -(eps >> -int_ >> *char_ >> *char_) | (*char_ >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<optional<int>, std::vector<char>>>, tuple<std::vector<char>, optional<int>>>>>));

        std::string const str = "3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (eps | -int_ | *char_ | *char_) >> (*char_ | -int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (eps >> -int_ >> *char_ >> *char_) | -(eps >> eps >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<optional<int>, std::vector<char>>, optional<int>>>>));

        std::string const str = "3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(eps | -int_ | *char_ | *char_) >> (eps | eps | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<int>>>>));

        std::string const str = "";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (eps >> -int_ >> *char_ >> *char_) | (eps >> *char_ >> -int_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<optional<int>, std::vector<char>>, tuple<std::vector<char>, std::vector<optional<int>>>>>>));

        std::string const str = "3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_003)
{
    {
        constexpr auto parser = (eps | -int_ | *char_ | *char_) >> (eps | *char_ | -int_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(eps >> -int_ >> *char_ >> *char_) | -(-int_ >> eps >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<optional<int>, std::vector<char>>>, optional<std::vector<optional<int>>>>>>));

        std::string const str = "3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (eps | -int_ | *char_ | *char_) >> (-int_ | eps | -int_);
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
        constexpr auto parser = (eps >> -int_ >> *char_ >> *char_) | (*char_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<optional<int>, std::vector<char>>, std::vector<char>>>>));

        std::string const str = "3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(eps | -int_ | *char_ | *char_) >> (*char_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<std::vector<char>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_004)
{
    {
        constexpr auto parser = (eps >> -int_ >> *char_ >> *char_) | -(eps >> *char_ >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<optional<int>, std::vector<char>>, optional<tuple<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (eps | -int_ | *char_ | *char_) >> (eps | *char_ | -int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(eps >> -int_ >> *char_ >> *char_) | (*char_ >> eps >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<optional<int>, std::vector<char>>>, tuple<std::vector<char>, optional<int>>>>>));

        std::string const str = "3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (eps | -int_ | *char_ | *char_) >> (*char_ | eps | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (eps >> -int_ >> *char_ >> *char_) | -(*char_ >> eps >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<optional<int>, std::vector<char>>, optional<std::vector<char>>>>>));

        std::string const str = "3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_005)
{
    {
        constexpr auto parser = -(eps | -int_ | *char_ | *char_) >> (*char_ | eps | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<std::vector<char>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (eps >> -int_ >> *char_ >> *char_) | (eps >> eps >> -int_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<optional<int>, std::vector<char>>, std::vector<optional<int>>>>>));

        std::string const str = "3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (eps | -int_ | *char_ | *char_) >> (eps | eps | -int_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<int>>>>));

        std::string const str = "";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(eps >> -int_ >> *char_ >> *char_) | -(-int_ >> *char_ >> -int_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<optional<int>, std::vector<char>>>, optional<tuple<optional<int>, std::vector<char>, optional<int>, std::vector<char>>>>>>));

        std::string const str = "3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (eps | -int_ | *char_ | *char_) >> (-int_ | *char_ | -int_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, variant<optional<int>, std::vector<char>>>>>));

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

TEST(parser, generated_62_006)
{
    {
        constexpr auto parser = (eps >> -int_ >> *char_ >> *char_) | (-int_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, std::vector<char>>>>));

        std::string const str = "3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(eps | -int_ | *char_ | *char_) >> (-int_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, variant<optional<int>, std::vector<char>>>>>));

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
        constexpr auto parser = (eps >> -int_ >> *char_ >> *char_) | -(-int_ >> *char_ >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<optional<int>, std::vector<char>>, optional<tuple<optional<int>, std::vector<char>, optional<int>>>>>>));

        std::string const str = "3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (eps | -int_ | *char_ | *char_) >> (-int_ | *char_ | -int_ | eps);
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
        constexpr auto parser = -(eps >> -int_ >> *char_ >> *char_) | (-int_ >> *char_ >> *char_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<optional<int>, std::vector<char>>>, tuple<optional<int>, std::vector<char>>>>>));

        std::string const str = "3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_007)
{
    {
        constexpr auto parser = (eps | -int_ | *char_ | *char_) >> (-int_ | *char_ | *char_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, variant<optional<int>, std::vector<char>>>>>));

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
        constexpr auto parser = (eps >> -int_ >> *char_ >> *char_) | -(-int_ >> eps >> eps >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<optional<int>, std::vector<char>>, optional<std::vector<optional<int>>>>>>));

        std::string const str = "3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(eps | -int_ | *char_ | *char_) >> (-int_ | eps | eps | -int_);
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
        constexpr auto parser = (eps >> -int_ >> *char_ >> *char_) | (-int_ >> *char_ >> eps >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, std::vector<char>>>>));

        std::string const str = "3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (eps | -int_ | *char_ | *char_) >> (-int_ | *char_ | eps | *char_);
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

TEST(parser, generated_62_008)
{
    {
        constexpr auto parser = -(eps >> -int_ >> *char_ >> *char_) | -(-int_ >> eps >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<optional<tuple<optional<int>, std::vector<char>>>>>));

        std::string const str = "3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (eps | -int_ | *char_ | *char_) >> (-int_ | eps | *char_);
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
        constexpr auto parser = (eps >> -int_ >> *char_ >> *char_) | (eps >> -int_ >> -int_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<optional<int>, std::vector<char>>, tuple<std::vector<optional<int>>, std::vector<char>>>>>));

        std::string const str = "3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(eps | -int_ | *char_ | *char_) >> (eps | -int_ | -int_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (eps >> -int_ >> *char_ >> *char_) | -(*char_ >> eps >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<optional<int>, std::vector<char>>, optional<std::vector<char>>>>>));

        std::string const str = "3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_009)
{
    {
        constexpr auto parser = (eps | -int_ | *char_ | *char_) >> (*char_ | eps | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<std::vector<char>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(eps >> -int_ >> *char_ >> *char_) | (*char_ >> -int_ >> *char_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<optional<int>, std::vector<char>>>, tuple<std::vector<char>, optional<int>, std::vector<char>, optional<int>>>>>));

        std::string const str = "3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (eps | -int_ | *char_ | *char_) >> (*char_ | -int_ | *char_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, variant<std::vector<char>, optional<int>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (eps >> -int_ >> *char_ >> *char_) | -(-int_ >> *char_ >> -int_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<optional<int>, std::vector<char>>, optional<tuple<optional<int>, std::vector<char>, std::vector<optional<int>>>>>>>));

        std::string const str = "3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(eps | -int_ | *char_ | *char_) >> (-int_ | *char_ | -int_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, variant<optional<int>, std::vector<char>>>>>));

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

TEST(parser, generated_62_010)
{
    {
        constexpr auto parser = (eps >> -int_ >> *char_ >> *char_) | (eps >> -int_ >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<optional<int>, std::vector<char>>, std::vector<optional<int>>>>>));

        std::string const str = "3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (eps | -int_ | *char_ | *char_) >> (eps | -int_ | -int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<int>>>>));

        std::string const str = "";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> *char_ >> *char_) | -(eps >> *char_ >> *char_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>, optional<tuple<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (eps | *char_ | *char_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | (eps >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_011)
{
    {
        constexpr auto parser = -(*char_ | -int_ | *char_ | *char_) >> (eps | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<optional<variant<std::vector<char>, optional<int>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | -(*char_ >> *char_ >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, optional<tuple<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (*char_ | *char_ | -int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> *char_ >> *char_) | (*char_ >> -int_ >> eps >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>, tuple<std::vector<char>, optional<int>, std::vector<char>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (*char_ | -int_ | eps | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_012)
{
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | -(-int_ >> eps >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, optional<int>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ | -int_ | *char_ | *char_) >> (-int_ | eps | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<int>>>>));

        std::string const str = "cb3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | (-int_ >> eps >> eps >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, tuple<optional<int>, std::vector<char>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (-int_ | eps | eps | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "cb3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> *char_ >> *char_) | -(-int_ >> -int_ >> eps >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>, optional<std::vector<optional<int>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_013)
{
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (-int_ | -int_ | eps | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<int>>>>));

        std::string const str = "cb3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | (-int_ >> eps >> *char_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, tuple<optional<int>, std::vector<char>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ | -int_ | *char_ | *char_) >> (-int_ | eps | *char_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "cb3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | -(-int_ >> -int_ >> eps >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, optional<tuple<std::vector<optional<int>>, std::vector<char>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (-int_ | -int_ | eps | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "cb3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_014)
{
    {
        constexpr auto parser = -(*char_ >> -int_ >> *char_ >> *char_) | (eps >> -int_ >> eps >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>, std::vector<optional<int>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (eps | -int_ | eps | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<int>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | -(*char_ >> eps >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, optional<tuple<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ | -int_ | *char_ | *char_) >> (*char_ | eps | -int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | (*char_ >> eps >> eps >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, std::vector<char>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_015)
{
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (*char_ | eps | eps | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<std::vector<char>>>>>));

        std::string const str = "cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> *char_ >> *char_) | -(eps >> *char_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>, optional<tuple<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (eps | *char_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | (*char_ >> eps >> eps >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, std::vector<char>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ | -int_ | *char_ | *char_) >> (*char_ | eps | eps | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<std::vector<char>>>>>));

        std::string const str = "cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_016)
{
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | -(eps >> *char_ >> -int_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (eps | *char_ | -int_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> *char_ >> *char_) | (*char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>, std::vector<char>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (*char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, std::vector<char>>>>));

        std::string const str = "cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | -(-int_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, optional<std::vector<optional<int>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_017)
{
    {
        constexpr auto parser = -(*char_ | -int_ | *char_ | *char_) >> (-int_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<int>>>>));

        std::string const str = "cb3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | (eps >> -int_ >> eps >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, tuple<optional<int>, std::vector<char>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (eps | -int_ | eps | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> *char_ >> *char_) | -(eps >> -int_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>, optional<std::vector<optional<int>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (eps | -int_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<int>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_018)
{
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | (*char_ >> -int_ >> eps >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, tuple<std::vector<char>, std::vector<optional<int>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ | -int_ | *char_ | *char_) >> (*char_ | -int_ | eps | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | -(-int_ >> eps >> *char_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, optional<tuple<optional<int>, std::vector<char>, optional<int>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (-int_ | eps | *char_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "cb3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> *char_ >> *char_) | (*char_ >> eps >> *char_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>, tuple<std::vector<char>, optional<int>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_019)
{
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (*char_ | eps | *char_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | -(*char_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, optional<std::vector<char>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ | -int_ | *char_ | *char_) >> (*char_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, std::vector<char>>>>));

        std::string const str = "cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | (-int_ >> eps >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, std::vector<optional<int>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (-int_ | eps | -int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<int>>>>));

        std::string const str = "cb3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_020)
{
    {
        constexpr auto parser = -(*char_ >> -int_ >> *char_ >> *char_) | -(-int_ >> eps >> -int_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>, optional<tuple<std::vector<optional<int>>, std::vector<char>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (-int_ | eps | -int_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "cb3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | (eps >> eps >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, std::vector<char>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ | -int_ | *char_ | *char_) >> (eps | eps | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<std::vector<char>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | -(-int_ >> -int_ >> *char_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, optional<tuple<std::vector<optional<int>>, std::vector<char>, optional<int>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_021)
{
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (-int_ | -int_ | *char_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, variant<optional<int>, std::vector<char>>>>>));

        std::string const str = "cb3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> *char_ >> *char_) | (eps >> *char_ >> eps >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>, tuple<std::vector<char>, optional<int>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (eps | *char_ | eps | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | -(-int_ >> *char_ >> eps >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, optional<tuple<optional<int>, std::vector<char>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ | -int_ | *char_ | *char_) >> (-int_ | *char_ | eps | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "cb3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_022)
{
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | (eps >> -int_ >> *char_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, tuple<optional<int>, std::vector<char>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (eps | -int_ | *char_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> *char_ >> *char_) | -(-int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>, optional<int>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (-int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<int>>>>));

        std::string const str = "cb3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | (-int_ >> *char_ >> *char_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, tuple<optional<int>, std::vector<char>, optional<int>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_023)
{
    {
        constexpr auto parser = -(*char_ | -int_ | *char_ | *char_) >> (-int_ | *char_ | *char_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, variant<optional<int>, std::vector<char>>>>>));

        std::string const str = "cb3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | -(eps >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, optional<int>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (eps | -int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<int>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> *char_ >> *char_) | (*char_ >> -int_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>, tuple<std::vector<char>, std::vector<optional<int>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (*char_ | -int_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<variant<std::vector<char>, optional<int>>>>>));

        std::string const str = "cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_024)
{
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | -(-int_ >> *char_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, optional<tuple<optional<int>, std::vector<char>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ | -int_ | *char_ | *char_) >> (-int_ | *char_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "cb3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | (-int_ >> -int_ >> *char_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, tuple<std::vector<optional<int>>, std::vector<char>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (-int_ | -int_ | *char_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, variant<optional<int>, std::vector<char>>>>>));

        std::string const str = "cb3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> *char_ >> *char_) | -(*char_ >> -int_ >> -int_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>, optional<tuple<std::vector<char>, std::vector<optional<int>>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_025)
{
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (*char_ | -int_ | -int_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<variant<std::vector<char>, optional<int>>>>>));

        std::string const str = "cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | (eps >> -int_ >> *char_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, tuple<optional<int>, std::vector<char>, optional<int>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ | -int_ | *char_ | *char_) >> (eps | -int_ | *char_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | -(*char_ >> *char_ >> eps >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, optional<tuple<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (*char_ | *char_ | eps | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_026)
{
    {
        constexpr auto parser = -(*char_ >> -int_ >> *char_ >> *char_) | (eps >> *char_ >> eps >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>, std::vector<char>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (eps | *char_ | eps | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<std::vector<char>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | -(-int_ >> -int_ >> *char_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, optional<tuple<std::vector<optional<int>>, std::vector<char>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ | -int_ | *char_ | *char_) >> (-int_ | -int_ | *char_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "cb3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | (eps >> *char_ >> eps >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, std::vector<char>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_027)
{
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (eps | *char_ | eps | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<std::vector<char>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> *char_ >> *char_) | -(eps >> -int_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>, optional<tuple<optional<int>, std::vector<char>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (eps | -int_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | (-int_ >> eps >> -int_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, std::vector<optional<int>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ | -int_ | *char_ | *char_) >> (-int_ | eps | -int_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<int>>>>));

        std::string const str = "cb3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_028)
{
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | -(eps >> eps >> -int_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, optional<tuple<optional<int>, std::vector<char>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (eps | eps | -int_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> *char_ >> *char_) | (-int_ >> *char_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>, tuple<optional<int>, std::vector<char>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (-int_ | *char_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, variant<optional<int>, std::vector<char>>>>>));

        std::string const str = "cb3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | -(eps >> eps >> *char_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, optional<tuple<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_029)
{
    {
        constexpr auto parser = -(*char_ | -int_ | *char_ | *char_) >> (eps | eps | *char_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | (*char_ >> eps >> *char_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, std::vector<char>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (*char_ | eps | *char_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<std::vector<char>>>>>));

        std::string const str = "cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> *char_ >> *char_) | -(-int_ >> eps >> *char_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>, optional<tuple<optional<int>, std::vector<char>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (-int_ | eps | *char_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "cb3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_030)
{
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | (eps >> -int_ >> eps >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, optional<int>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ | -int_ | *char_ | *char_) >> (eps | -int_ | eps | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<int>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | -(*char_ >> eps >> -int_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (*char_ | eps | -int_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> *char_ >> *char_) | (*char_ >> eps >> *char_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>, std::vector<char>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_031)
{
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (*char_ | eps | *char_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<std::vector<char>>>>>));

        std::string const str = "cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | -(-int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, optional<int>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ | -int_ | *char_ | *char_) >> (-int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<int>>>>));

        std::string const str = "cb3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | (eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<char>, optional<int>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_032)
{
    {
        constexpr auto parser = -(*char_ >> -int_ >> *char_ >> *char_) | -(eps >> eps >> *char_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>, optional<std::vector<char>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (eps | eps | *char_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<std::vector<char>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | (eps >> eps >> *char_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, std::vector<char>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ | -int_ | *char_ | *char_) >> (eps | eps | *char_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<std::vector<char>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | -(*char_ >> *char_ >> eps >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, optional<std::vector<char>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_033)
{
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (*char_ | *char_ | eps | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<std::vector<char>>>>>));

        std::string const str = "cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> *char_ >> *char_) | (eps >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>, optional<int>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (eps | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<int>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | -(*char_ >> *char_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, optional<tuple<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ | -int_ | *char_ | *char_) >> (*char_ | *char_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, variant<std::vector<char>, optional<int>>>>>));

        std::string const str = "cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_034)
{
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | (*char_ >> eps >> eps >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, tuple<std::vector<char>, optional<int>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (*char_ | eps | eps | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> *char_ >> *char_) | -(*char_ >> *char_ >> eps >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>, optional<std::vector<char>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (*char_ | *char_ | eps | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<std::vector<char>>>>>));

        std::string const str = "cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | (*char_ >> eps >> -int_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, tuple<std::vector<char>, std::vector<optional<int>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_035)
{
    {
        constexpr auto parser = -(*char_ | -int_ | *char_ | *char_) >> (*char_ | eps | -int_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | -(*char_ >> -int_ >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, optional<tuple<std::vector<char>, std::vector<optional<int>>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (*char_ | -int_ | -int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> *char_ >> *char_) | (*char_ >> *char_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>, std::vector<char>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (*char_ | *char_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<std::vector<char>>>>>));

        std::string const str = "cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_036)
{
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | -(*char_ >> -int_ >> -int_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, optional<tuple<std::vector<char>, std::vector<optional<int>>, std::vector<char>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ | -int_ | *char_ | *char_) >> (*char_ | -int_ | -int_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, variant<std::vector<char>, optional<int>>>>>));

        std::string const str = "cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | (-int_ >> -int_ >> eps >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, std::vector<optional<int>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (-int_ | -int_ | eps | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<int>>>>));

        std::string const str = "cb3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> *char_ >> *char_) | -(-int_ >> *char_ >> *char_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>, optional<tuple<optional<int>, std::vector<char>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_037)
{
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (-int_ | *char_ | *char_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "cb3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | (eps >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, std::vector<char>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ | -int_ | *char_ | *char_) >> (eps | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<std::vector<char>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | -(-int_ >> *char_ >> eps >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, optional<tuple<optional<int>, std::vector<char>, optional<int>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (-int_ | *char_ | eps | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "cb3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_038)
{
    {
        constexpr auto parser = -(*char_ >> -int_ >> *char_ >> *char_) | (-int_ >> -int_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>, tuple<std::vector<optional<int>>, std::vector<char>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (-int_ | -int_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, variant<optional<int>, std::vector<char>>>>>));

        std::string const str = "cb3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | -(eps >> *char_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, optional<std::vector<char>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ | -int_ | *char_ | *char_) >> (eps | *char_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<std::vector<char>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | (eps >> -int_ >> *char_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, tuple<optional<int>, std::vector<char>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_039)
{
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (eps | -int_ | *char_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> *char_ >> *char_) | -(*char_ >> -int_ >> *char_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (*char_ | -int_ | *char_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<variant<std::vector<char>, optional<int>>>>>));

        std::string const str = "cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | (eps >> *char_ >> *char_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, std::vector<char>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ | -int_ | *char_ | *char_) >> (eps | *char_ | *char_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<std::vector<char>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_040)
{
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | -(*char_ >> *char_ >> -int_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (*char_ | *char_ | -int_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<variant<std::vector<char>, optional<int>>>>>));

        std::string const str = "cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> *char_ >> *char_) | (*char_ >> *char_ >> -int_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>, tuple<std::vector<char>, std::vector<optional<int>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (*char_ | *char_ | -int_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<variant<std::vector<char>, optional<int>>>>>));

        std::string const str = "cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | -(*char_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, optional<tuple<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_041)
{
    {
        constexpr auto parser = -(*char_ | -int_ | *char_ | *char_) >> (*char_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, variant<std::vector<char>, optional<int>>>>>));

        std::string const str = "cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | (eps >> *char_ >> *char_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, std::vector<char>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (eps | *char_ | *char_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<std::vector<char>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> *char_ >> *char_) | -(*char_ >> -int_ >> eps >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>, optional<tuple<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (*char_ | -int_ | eps | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_042)
{
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | (eps >> -int_ >> -int_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, std::vector<optional<int>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ | -int_ | *char_ | *char_) >> (eps | -int_ | -int_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<int>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | -(*char_ >> -int_ >> *char_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (*char_ | -int_ | *char_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> *char_ >> *char_) | (*char_ >> -int_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>, tuple<std::vector<char>, optional<int>, std::vector<char>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_043)
{
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (*char_ | -int_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<variant<std::vector<char>, optional<int>>>>>));

        std::string const str = "cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | -(-int_ >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, optional<std::vector<optional<int>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ | -int_ | *char_ | *char_) >> (-int_ | -int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<int>>>>));

        std::string const str = "cb3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | (eps >> *char_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, std::vector<char>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (eps | *char_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<std::vector<char>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_044)
{
    {
        constexpr auto parser = -(*char_ >> -int_ >> *char_ >> *char_) | -(-int_ >> eps >> eps >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>, optional<int>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (-int_ | eps | eps | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<int>>>>));

        std::string const str = "cb3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | (eps >> eps >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, optional<int>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ | -int_ | *char_ | *char_) >> (eps | eps | -int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<int>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | -(-int_ >> *char_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, optional<tuple<optional<int>, std::vector<char>, optional<int>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_045)
{
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (-int_ | *char_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, variant<optional<int>, std::vector<char>>>>>));

        std::string const str = "cb3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> *char_ >> *char_) | (*char_ >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>, tuple<std::vector<char>, optional<int>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (*char_ | -int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | -(eps >> eps >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, optional<int>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ | -int_ | *char_ | *char_) >> (eps | eps | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<int>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_046)
{
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | (eps >> *char_ >> -int_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, tuple<std::vector<char>, std::vector<optional<int>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (eps | *char_ | -int_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> *char_ >> *char_) | -(-int_ >> eps >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>, optional<std::vector<optional<int>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (-int_ | eps | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<int>>>>));

        std::string const str = "cb3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | (*char_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, std::vector<char>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_047)
{
    {
        constexpr auto parser = -(*char_ | -int_ | *char_ | *char_) >> (*char_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<std::vector<char>>>>>));

        std::string const str = "cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | -(eps >> *char_ >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, optional<tuple<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (eps | *char_ | -int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> *char_ >> *char_) | (*char_ >> eps >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>, tuple<std::vector<char>, optional<int>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (*char_ | eps | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_048)
{
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | -(*char_ >> eps >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, optional<std::vector<char>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ | -int_ | *char_ | *char_) >> (*char_ | eps | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<std::vector<char>>>>>));

        std::string const str = "cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | (eps >> eps >> -int_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, std::vector<optional<int>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (eps | eps | -int_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<int>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> *char_ >> *char_) | -(-int_ >> *char_ >> -int_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>, optional<tuple<optional<int>, std::vector<char>, optional<int>, std::vector<char>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

TEST(parser, generated_62_049)
{
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (-int_ | *char_ | -int_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, variant<optional<int>, std::vector<char>>>>>));

        std::string const str = "cb3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | (-int_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, tuple<optional<int>, std::vector<char>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = -(*char_ | -int_ | *char_ | *char_) >> (-int_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, variant<optional<int>, std::vector<char>>>>>));

        std::string const str = "cb3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> *char_ >> *char_) | -(-int_ >> *char_ >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, optional<int>, std::vector<char>>, optional<tuple<optional<int>, std::vector<char>, optional<int>>>>>>));

        std::string const str = "cb3cbcb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
    {
        constexpr auto parser = (*char_ | -int_ | *char_ | *char_) >> (-int_ | *char_ | -int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "cb3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
    }
}

