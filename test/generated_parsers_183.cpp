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
using std::optional;
using std::variant;
using boost::hana::tuple;

char const g_chars[] = "";
auto g_first = std::begin(g_chars);
auto const g_last = std::end(g_chars);


TEST(parser, generated_183_000)
{
    {
        constexpr auto parser = -(-int_ >> eps >> eps >> eps) | -(*char_ >> -int_ >> eps >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, optional<tuple<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (-int_ | eps | eps | eps) >> (*char_ | -int_ | eps | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (-int_ >> eps >> eps >> eps) | (eps >> -int_ >> -int_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, std::vector<optional<int>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = -(-int_ | eps | eps | eps) >> (eps | -int_ | -int_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (-int_ >> eps >> eps >> eps) | -(*char_ >> -int_ >> *char_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
}

TEST(parser, generated_183_001)
{
    {
        constexpr auto parser = (-int_ | eps | eps | eps) >> (*char_ | -int_ | *char_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = -(-int_ >> eps >> eps >> eps) | (*char_ >> -int_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, tuple<std::vector<char>, optional<int>, std::vector<char>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (-int_ | eps | eps | eps) >> (*char_ | -int_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, variant<std::vector<char>, optional<int>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (-int_ >> eps >> eps >> eps) | -(-int_ >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, optional<std::vector<optional<int>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = -(-int_ | eps | eps | eps) >> (-int_ | -int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
}

TEST(parser, generated_183_002)
{
    {
        constexpr auto parser = (-int_ >> eps >> eps >> eps) | (eps >> *char_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, std::vector<char>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (-int_ | eps | eps | eps) >> (eps | *char_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<std::vector<char>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = -(-int_ >> eps >> eps >> eps) | -(-int_ >> eps >> eps >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<optional<int>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (-int_ | eps | eps | eps) >> (-int_ | eps | eps | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (-int_ >> eps >> eps >> eps) | (eps >> eps >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<optional<int>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
}

TEST(parser, generated_183_003)
{
    {
        constexpr auto parser = -(-int_ | eps | eps | eps) >> (eps | eps | -int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (-int_ >> eps >> eps >> eps) | -(-int_ >> *char_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, optional<tuple<optional<int>, std::vector<char>, optional<int>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (-int_ | eps | eps | eps) >> (-int_ | *char_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, variant<optional<int>, std::vector<char>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = -(-int_ >> eps >> eps >> eps) | (*char_ >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, tuple<std::vector<char>, optional<int>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (-int_ | eps | eps | eps) >> (*char_ | -int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
}

TEST(parser, generated_183_004)
{
    {
        constexpr auto parser = (-int_ >> eps >> eps >> eps) | -(eps >> eps >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<optional<int>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = -(-int_ | eps | eps | eps) >> (eps | eps | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (-int_ >> eps >> eps >> eps) | (eps >> *char_ >> -int_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, tuple<std::vector<char>, std::vector<optional<int>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (-int_ | eps | eps | eps) >> (eps | *char_ | -int_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = -(-int_ >> eps >> eps >> eps) | -(-int_ >> eps >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, optional<std::vector<optional<int>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
}

TEST(parser, generated_183_005)
{
    {
        constexpr auto parser = (-int_ | eps | eps | eps) >> (-int_ | eps | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (-int_ >> eps >> eps >> eps) | (*char_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, std::vector<char>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = -(-int_ | eps | eps | eps) >> (*char_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<std::vector<char>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (-int_ >> eps >> eps >> eps) | -(eps >> *char_ >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, optional<tuple<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (-int_ | eps | eps | eps) >> (eps | *char_ | -int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
}

TEST(parser, generated_183_006)
{
    {
        constexpr auto parser = -(-int_ >> eps >> eps >> eps) | (*char_ >> eps >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, tuple<std::vector<char>, optional<int>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (-int_ | eps | eps | eps) >> (*char_ | eps | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (-int_ >> eps >> eps >> eps) | -(*char_ >> eps >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, optional<std::vector<char>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = -(-int_ | eps | eps | eps) >> (*char_ | eps | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<std::vector<char>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (-int_ >> eps >> eps >> eps) | (eps >> eps >> -int_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, std::vector<optional<int>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
}

TEST(parser, generated_183_007)
{
    {
        constexpr auto parser = (-int_ | eps | eps | eps) >> (eps | eps | -int_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = -(-int_ >> eps >> eps >> eps) | -(-int_ >> *char_ >> -int_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, optional<tuple<optional<int>, std::vector<char>, optional<int>, std::vector<char>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (-int_ | eps | eps | eps) >> (-int_ | *char_ | -int_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, variant<optional<int>, std::vector<char>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (-int_ >> eps >> eps >> eps) | (-int_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, tuple<optional<int>, std::vector<char>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = -(-int_ | eps | eps | eps) >> (-int_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, variant<optional<int>, std::vector<char>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
}

TEST(parser, generated_183_008)
{
    {
        constexpr auto parser = (-int_ >> eps >> eps >> eps) | -(-int_ >> *char_ >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, optional<tuple<optional<int>, std::vector<char>, optional<int>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (-int_ | eps | eps | eps) >> (-int_ | *char_ | -int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = -(-int_ >> eps >> eps >> eps) | (-int_ >> *char_ >> *char_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, tuple<optional<int>, std::vector<char>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (-int_ | eps | eps | eps) >> (-int_ | *char_ | *char_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, variant<optional<int>, std::vector<char>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (-int_ >> eps >> eps >> eps) | -(-int_ >> eps >> eps >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, optional<std::vector<optional<int>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
}

TEST(parser, generated_183_009)
{
    {
        constexpr auto parser = -(-int_ | eps | eps | eps) >> (-int_ | eps | eps | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (-int_ >> eps >> eps >> eps) | (-int_ >> *char_ >> eps >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, tuple<optional<int>, std::vector<char>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (-int_ | eps | eps | eps) >> (-int_ | *char_ | eps | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = -(-int_ >> eps >> eps >> eps) | -(-int_ >> eps >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, optional<tuple<optional<int>, std::vector<char>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (-int_ | eps | eps | eps) >> (-int_ | eps | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
}

TEST(parser, generated_183_010)
{
    {
        constexpr auto parser = (-int_ >> eps >> eps >> eps) | (eps >> -int_ >> -int_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, tuple<std::vector<optional<int>>, std::vector<char>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = -(-int_ | eps | eps | eps) >> (eps | -int_ | -int_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (-int_ >> eps >> eps >> eps) | -(*char_ >> eps >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, optional<std::vector<char>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (-int_ | eps | eps | eps) >> (*char_ | eps | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<std::vector<char>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = -(-int_ >> eps >> eps >> eps) | (*char_ >> -int_ >> *char_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, tuple<std::vector<char>, optional<int>, std::vector<char>, optional<int>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
}

TEST(parser, generated_183_011)
{
    {
        constexpr auto parser = (-int_ | eps | eps | eps) >> (*char_ | -int_ | *char_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, variant<std::vector<char>, optional<int>>>>>));

        std::string const str = "3cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (-int_ >> eps >> eps >> eps) | -(-int_ >> *char_ >> -int_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, optional<tuple<optional<int>, std::vector<char>, std::vector<optional<int>>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = -(-int_ | eps | eps | eps) >> (-int_ | *char_ | -int_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, variant<optional<int>, std::vector<char>>>>>));

        std::string const str = "33";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (-int_ >> eps >> eps >> eps) | (eps >> -int_ >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, std::vector<optional<int>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (-int_ | eps | eps | eps) >> (eps | -int_ | -int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
}

TEST(parser, generated_183_012)
{
    {
        constexpr auto parser = -(eps >> eps >> -int_ >> eps) | -(eps >> *char_ >> *char_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, optional<tuple<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (eps | eps | -int_ | eps) >> (eps | *char_ | *char_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (eps >> eps >> -int_ >> eps) | (eps >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<optional<int>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = -(eps | eps | -int_ | eps) >> (eps | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<optional<int>>>));

        std::string const str = "";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (eps >> eps >> -int_ >> eps) | -(*char_ >> *char_ >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, optional<tuple<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
}

TEST(parser, generated_183_013)
{
    {
        constexpr auto parser = (eps | eps | -int_ | eps) >> (*char_ | *char_ | -int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = -(eps >> eps >> -int_ >> eps) | (*char_ >> -int_ >> eps >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, tuple<std::vector<char>, optional<int>, std::vector<char>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (eps | eps | -int_ | eps) >> (*char_ | -int_ | eps | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (eps >> eps >> -int_ >> eps) | -(-int_ >> eps >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<optional<int>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = -(eps | eps | -int_ | eps) >> (-int_ | eps | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
}

TEST(parser, generated_183_014)
{
    {
        constexpr auto parser = (eps >> eps >> -int_ >> eps) | (-int_ >> eps >> eps >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, tuple<optional<int>, std::vector<char>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (eps | eps | -int_ | eps) >> (-int_ | eps | eps | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = -(eps >> eps >> -int_ >> eps) | -(-int_ >> -int_ >> eps >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, optional<std::vector<optional<int>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (eps | eps | -int_ | eps) >> (-int_ | -int_ | eps | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (eps >> eps >> -int_ >> eps) | (-int_ >> eps >> *char_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, tuple<optional<int>, std::vector<char>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
}

TEST(parser, generated_183_015)
{
    {
        constexpr auto parser = -(eps | eps | -int_ | eps) >> (-int_ | eps | *char_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (eps >> eps >> -int_ >> eps) | -(-int_ >> -int_ >> eps >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, optional<tuple<std::vector<optional<int>>, std::vector<char>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (eps | eps | -int_ | eps) >> (-int_ | -int_ | eps | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = -(eps >> eps >> -int_ >> eps) | (eps >> -int_ >> eps >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, std::vector<optional<int>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (eps | eps | -int_ | eps) >> (eps | -int_ | eps | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
}

TEST(parser, generated_183_016)
{
    {
        constexpr auto parser = (eps >> eps >> -int_ >> eps) | -(*char_ >> eps >> -int_ >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, optional<tuple<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = -(eps | eps | -int_ | eps) >> (*char_ | eps | -int_ | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (eps >> eps >> -int_ >> eps) | (*char_ >> eps >> eps >> eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, std::vector<char>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (eps | eps | -int_ | eps) >> (*char_ | eps | eps | eps);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<std::vector<char>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = -(eps >> eps >> -int_ >> eps) | -(eps >> *char_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, optional<tuple<std::vector<char>, optional<int>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
}

TEST(parser, generated_183_017)
{
    {
        constexpr auto parser = (eps | eps | -int_ | eps) >> (eps | *char_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (eps >> eps >> -int_ >> eps) | (*char_ >> eps >> eps >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, std::vector<char>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = -(eps | eps | -int_ | eps) >> (*char_ | eps | eps | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<std::vector<char>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (eps >> eps >> -int_ >> eps) | -(eps >> *char_ >> -int_ >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (eps | eps | -int_ | eps) >> (eps | *char_ | -int_ | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
}

TEST(parser, generated_183_018)
{
    {
        constexpr auto parser = -(eps >> eps >> -int_ >> eps) | (*char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, std::vector<char>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (eps | eps | -int_ | eps) >> (*char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, std::vector<char>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (eps >> eps >> -int_ >> eps) | -(-int_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, optional<std::vector<optional<int>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = -(eps | eps | -int_ | eps) >> (-int_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (eps >> eps >> -int_ >> eps) | (eps >> -int_ >> eps >> *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, tuple<optional<int>, std::vector<char>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
}

TEST(parser, generated_183_019)
{
    {
        constexpr auto parser = (eps | eps | -int_ | eps) >> (eps | -int_ | eps | *char_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<optional<int>, std::vector<char>>>>>>));

        std::string const str = "";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = -(eps >> eps >> -int_ >> eps) | -(eps >> -int_ >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, optional<std::vector<optional<int>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (eps | eps | -int_ | eps) >> (eps | -int_ | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<int>>>>));

        std::string const str = "";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = (eps >> eps >> -int_ >> eps) | (*char_ >> -int_ >> eps >> -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<int>, tuple<std::vector<char>, std::vector<optional<int>>>>>>));

        std::string const str = "3";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
    {
        constexpr auto parser = -(eps | eps | -int_ | eps) >> (*char_ | -int_ | eps | -int_);
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<int>, optional<variant<std::vector<char>, optional<int>>>>>>));

        std::string const str = "cb";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
    }
}

