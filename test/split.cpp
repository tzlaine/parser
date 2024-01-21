/**
 *   Copyright (C) 2024 T. Zachary Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See
 *   accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt)
 */

#include <boost/parser/split.hpp>

#include <gtest/gtest.h>


namespace bp = boost::parser;

#if BOOST_PARSER_USE_CONCEPTS
namespace deduction {
    std::string str;
    auto const parser = bp::char_;
    auto const skip = bp::ws;

    auto deduced_1 = bp::split_view(str, parser, skip, bp::trace::on);
    auto deduced_2 = bp::split_view(str, parser, skip);
    auto deduced_3 = bp::split_view(str, parser, bp::trace::on);
    auto deduced_4 = bp::split_view(str, parser);
}
#endif

TEST(split, split_)
{
    {
        auto r = bp::split("", bp::lit("XYZ"), bp::ws);
        int count = 0;
        for (auto subrange : r) {
            (void)subrange;
            ++count;
        }
        EXPECT_EQ(count, 0);
    }
    {
        char const str[] = "aaXYZb";
        auto r = bp::split(str, bp::lit("XYZ"), bp::ws);
        int count = 0;
        int const offsets[] = {0, 2, 5, 6};
        for (auto subrange : r) {
            EXPECT_EQ(subrange.begin() - str, offsets[count * 2 + 0]);
            EXPECT_EQ(subrange.end() - str, offsets[count * 2 + 1]);
            ++count;
        }
        EXPECT_EQ(count, 2);
    }
    {
        char const str[] = "aaXYZbaabaXYZ";
        auto r = str | bp::split(bp::lit("XYZ"), bp::ws, bp::trace::off);
        int count = 0;
        int const offsets[] = {0, 2, 5, 10, 13, 13};
        for (auto subrange : r) {
            EXPECT_EQ(subrange.begin() - str, offsets[count * 2 + 0]);
            EXPECT_EQ(subrange.end() - str, offsets[count * 2 + 1]);
            ++count;
        }
        EXPECT_EQ(count, 3);
    }
    {
        char const str[] = "aaXYZbaabaXYZ";
        auto r = str | bp::split(bp::lit("XYZ"), bp::trace::off);
        int count = 0;
        int const offsets[] = {0, 2, 5, 10, 13, 13};
        for (auto subrange : r) {
            EXPECT_EQ(subrange.begin() - str, offsets[count * 2 + 0]);
            EXPECT_EQ(subrange.end() - str, offsets[count * 2 + 1]);
            ++count;
        }
        EXPECT_EQ(count, 3);
    }
    {
        char const str[] = "aaXYZbaabaXYZ";
        auto r = str | bp::split(bp::lit("XYZ"));
        int count = 0;
        int const offsets[] = {0, 2, 5, 10, 13, 13};
        for (auto subrange : r) {
            EXPECT_EQ(subrange.begin() - str, offsets[count * 2 + 0]);
            EXPECT_EQ(subrange.end() - str, offsets[count * 2 + 1]);
            ++count;
        }
        EXPECT_EQ(count, 3);
    }
    {
        char const str[] = "aaXYZbaabaXYZXYZ";
        auto r = str | bp::split(bp::lit("XYZ"));
        int count = 0;
        int const offsets[] = {0, 2, 5, 10, 13, 13, 16, 16};
        for (auto subrange : r) {
            EXPECT_EQ(subrange.begin() - str, offsets[count * 2 + 0]);
            EXPECT_EQ(subrange.end() - str, offsets[count * 2 + 1]);
            ++count;
        }
        EXPECT_EQ(count, 4);
    }
    {
        char const str[] = "XYZaaXYZbaabaXYZXYZ";
        auto r = str | bp::split(bp::lit("XYZ"));
        int count = 0;
        int const offsets[] = {0, 0, 3, 5, 8, 13, 16, 16, 19, 19};
        for (auto subrange : r) {
            EXPECT_EQ(subrange.begin() - str, offsets[count * 2 + 0]);
            EXPECT_EQ(subrange.end() - str, offsets[count * 2 + 1]);
            ++count;
        }
        EXPECT_EQ(count, 5);
    }
    {
        char const str[] = "XYZXYZaaXYZbaabaXYZXYZ";
        auto r = str | bp::split(bp::lit("XYZ"));
        int count = 0;
        int const offsets[] = {0, 0, 3, 3, 6, 8, 11, 16, 19, 19, 22, 22};
        for (auto subrange : r) {
            EXPECT_EQ(subrange.begin() - str, offsets[count * 2 + 0]);
            EXPECT_EQ(subrange.end() - str, offsets[count * 2 + 1]);
            ++count;
        }
        EXPECT_EQ(count, 6);
    }
    {
        char const * str = "XYZXYZaaXYZbaabaXYZXYZ";
        auto r = str | bp::split(bp::lit("XYZ"));
        int count = 0;
        int const offsets[] = {0, 0, 3, 3, 6, 8, 11, 16, 19, 19, 22, 22};
        for (auto subrange : r) {
            EXPECT_EQ(subrange.begin() - str, offsets[count * 2 + 0]);
            EXPECT_EQ(subrange.end() - str, offsets[count * 2 + 1]);
            ++count;
        }
        EXPECT_EQ(count, 6);
    }
}

TEST(split, split_unicode)
{
    {
        char const str_[] = "";
        auto str = str_ | bp::as_utf8;
        auto r = bp::split(str, bp::lit("XYZ"), bp::ws);
        int count = 0;
        for (auto subrange : r) {
            (void)subrange;
            ++count;
        }
        EXPECT_EQ(count, 0);
    }
    {
        char const * str_ = "aaXYZb";
        auto str = str_ | bp::as_utf16;
        auto r = bp::split(str, bp::lit("XYZ"), bp::ws);
        int count = 0;
        int const offsets[] = {0, 2, 5, 6};
        for (auto subrange : r) {
            EXPECT_EQ(subrange.begin().base() - str_, offsets[count * 2 + 0]);
            EXPECT_EQ(subrange.end().base() - str_, offsets[count * 2 + 1]);
            ++count;
        }
        EXPECT_EQ(count, 2);
    }
    {
        char const str_[] = "aaXYZbaabaXYZ";
        auto str = str_ | bp::as_utf32;
        auto r = str | bp::split(bp::lit("XYZ"), bp::ws, bp::trace::off);
        int count = 0;
        int const offsets[] = {0, 2, 5, 10, 13, 13};
        for (auto subrange : r) {
            EXPECT_EQ(subrange.begin().base() - str_, offsets[count * 2 + 0]);
            EXPECT_EQ(subrange.end().base() - str_, offsets[count * 2 + 1]);
            ++count;
        }
        EXPECT_EQ(count, 3);
    }
    {
        char const str_[] = "aaXYZbaabaXYZ";
        auto str = str_ | bp::as_utf8;
        auto r = str | bp::split(bp::lit("XYZ"), bp::trace::off);
        int count = 0;
        int const offsets[] = {0, 2, 5, 10, 13, 13};
        for (auto subrange : r) {
            EXPECT_EQ(subrange.begin().base() - str_, offsets[count * 2 + 0]);
            EXPECT_EQ(subrange.end().base() - str_, offsets[count * 2 + 1]);
            ++count;
        }
        EXPECT_EQ(count, 3);
    }
    {
        char const str_[] = "aaXYZbaabaXYZ";
        auto str = str_ | bp::as_utf16;
        auto r = str | bp::split(bp::lit("XYZ"));
        int count = 0;
        int const offsets[] = {0, 2, 5, 10, 13, 13};
        for (auto subrange : r) {
            EXPECT_EQ(subrange.begin().base() - str_, offsets[count * 2 + 0]);
            EXPECT_EQ(subrange.end().base() - str_, offsets[count * 2 + 1]);
            ++count;
        }
        EXPECT_EQ(count, 3);
    }
    {
        char const str_[] = "aaXYZbaabaXYZXYZ";
        auto str = str_ | bp::as_utf32;
        auto r = str | bp::split(bp::lit("XYZ"));
        int count = 0;
        int const offsets[] = {0, 2, 5, 10, 13, 13, 16, 16};
        for (auto subrange : r) {
            EXPECT_EQ(subrange.begin().base() - str_, offsets[count * 2 + 0]);
            EXPECT_EQ(subrange.end().base() - str_, offsets[count * 2 + 1]);
            ++count;
        }
        EXPECT_EQ(count, 4);
    }
    {
        char const str_[] = "XYZaaXYZbaabaXYZXYZ";
        auto str = str_ | bp::as_utf8;
        auto r = str | bp::split(bp::lit("XYZ"));
        int count = 0;
        int const offsets[] = {0, 0, 3, 5, 8, 13, 16, 16, 19, 19};
        for (auto subrange : r) {
            EXPECT_EQ(subrange.begin().base() - str_, offsets[count * 2 + 0]);
            EXPECT_EQ(subrange.end().base() - str_, offsets[count * 2 + 1]);
            ++count;
        }
        EXPECT_EQ(count, 5);
    }
    {
        char const str_[] = "XYZXYZaaXYZbaabaXYZXYZ";
        auto str = str_ | bp::as_utf16;
        auto r = str | bp::split(bp::lit("XYZ"));
        int count = 0;
        int const offsets[] = {0, 0, 3, 3, 6, 8, 11, 16, 19, 19, 22, 22};
        for (auto subrange : r) {
            EXPECT_EQ(subrange.begin().base() - str_, offsets[count * 2 + 0]);
            EXPECT_EQ(subrange.end().base() - str_, offsets[count * 2 + 1]);
            ++count;
        }
        EXPECT_EQ(count, 6);
    }
}

TEST(split, doc_examples)
{
    {
        auto r = "XYZaaXYZbaabaXYZXYZ" | bp::split(bp::lit("XYZ"));
        int count = 0;
        // Prints '' 'aa' 'baaba' '' ''.
        for (auto subrange : r) {
            std::cout << "'" << std::string_view(subrange.begin(), subrange.end() - subrange.begin()) << "' ";
            ++count;
        }
        std::cout << "\n";
        assert(count == 5);
    }
}
