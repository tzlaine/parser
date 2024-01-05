/**
 *   Copyright (C) 2024 T. Zachary Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See
 *   accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt)
 */

#include <boost/parser/parser.hpp>
#include <boost/parser/transcode_view.hpp>

#include <gtest/gtest.h>


using namespace boost::parser;


TEST(no_case, basic)
{
    constexpr auto char_p = no_case[char_('a') | char_('B')];

    {
        auto const result = parse("a", char_p);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 'a');
    }
    {
        auto const result = parse("A", char_p);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 'A');
    }

    {
        auto const result = parse("b", char_p);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 'b');
    }
    {
        auto const result = parse("B", char_p);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 'B');
    }

    constexpr auto str_p = string("sOmE TeXT");

    {
        auto const result = parse("some text", str_p);
        EXPECT_FALSE(result);
    }
    {
        auto const result = parse("some text", no_case[str_p]);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "some text");
    }
    {
        auto const result = parse("SomE tEXt", str_p);
        EXPECT_FALSE(result);
    }
    {
        auto const result = parse("SomE tEXt", no_case[str_p]);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, "SomE tEXt");
    }
}

TEST(no_case, char_range)
{
    constexpr auto lower_alpha_p = char_('a', 'b');
    {
        EXPECT_FALSE(parse("A", lower_alpha_p));
        auto const result = parse("a", lower_alpha_p);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 'a');
    }
    {
        auto const result = parse("A", no_case[lower_alpha_p]);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 'A');
    }

    constexpr auto upper_alpha_p = char_('A', 'B');
    {
        EXPECT_FALSE(parse("a", upper_alpha_p));
        auto const result = parse("A", upper_alpha_p);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 'A');
    }
    {
        auto const result = parse("a", no_case[upper_alpha_p]);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 'a');
    }
}

TEST(no_case, match_any_within_string)
{
    constexpr auto _trasse_p = no_case[char_(u8"_traße")];
    {
        auto const result = parse(U"ß", _trasse_p);
        EXPECT_TRUE(result);
        EXPECT_TRUE(*result == U'ß');
    }
    {
        auto const result = parse(U"s", _trasse_p); // TODO
        EXPECT_TRUE(result);
        EXPECT_TRUE(*result == U's');
    }
    {
        auto const result = parse("s", _trasse_p);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 's');
    }
    {
        auto const result = parse(U"S", _trasse_p); // TODO
        EXPECT_TRUE(result);
        EXPECT_TRUE(*result == U'S');
    }
    {
        auto const result = parse("S", _trasse_p);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 'S');
    }
    {
        auto const result = parse(U"t", _trasse_p);
        EXPECT_TRUE(result);
        EXPECT_TRUE(*result == U't');
    }
    {
        auto const result = parse("t", _trasse_p);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 't');
    }
    {
        auto const result = parse(U"T", _trasse_p);
        EXPECT_TRUE(result);
        EXPECT_TRUE(*result == U'T');
    }
    {
        auto const result = parse("T", _trasse_p);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 'T');
    }
}

constexpr auto capital_sharp_s = u8"ẞ"; // U+1E9E
constexpr auto small_sharp_s = u8"ß";   // U+00DF
constexpr auto double_s = u8"sS";       // U+0073 U+0073

TEST(no_case, multi_code_point_mapping)
{
    {
        constexpr auto capital_sharp_s_p = no_case[string(capital_sharp_s)];

        {
            auto const result =
                parse(capital_sharp_s | as_utf32, capital_sharp_s_p);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, (char const *)capital_sharp_s);
        }
        {
            auto const result =
                parse(small_sharp_s | as_utf32, capital_sharp_s_p);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, (char const *)small_sharp_s);
        }
        {
            auto const result = parse(double_s | as_utf32, capital_sharp_s_p);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, (char const *)double_s);
        }
        {
            EXPECT_FALSE(parse("s" | as_utf32, capital_sharp_s_p));
        }
        {
            EXPECT_FALSE(parse("sx" | as_utf32, capital_sharp_s_p));
        }
        {
            EXPECT_FALSE(parse("xs" | as_utf32, capital_sharp_s_p));
        }
    }
    {
        constexpr auto small_sharp_s_p = no_case[string(small_sharp_s)];

        {
            auto const result =
                parse(capital_sharp_s | as_utf32, small_sharp_s_p);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, (char const *)capital_sharp_s);
        }
        {
            auto const result =
                parse(small_sharp_s | as_utf32, small_sharp_s_p);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, (char const *)small_sharp_s);
        }
        {
            auto const result = parse(double_s | as_utf32, small_sharp_s_p);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, (char const *)double_s);
        }
        {
            EXPECT_FALSE(parse("s" | as_utf32, small_sharp_s_p));
        }
        {
            EXPECT_FALSE(parse("sx" | as_utf32, small_sharp_s_p));
        }
        {
            EXPECT_FALSE(parse("xs" | as_utf32, small_sharp_s_p));
        }
    }
    {
        constexpr auto double_s_p = no_case[string(double_s)];

        {
            auto const result = parse(capital_sharp_s | as_utf32, double_s_p);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, (char const *)capital_sharp_s);
        }
        {
            auto const result = parse(small_sharp_s | as_utf32, double_s_p);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, (char const *)small_sharp_s);
        }
        {
            auto const result = parse(double_s | as_utf32, double_s_p);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, (char const *)double_s);
        }
        {
            EXPECT_FALSE(parse("s" | as_utf32, double_s_p));
        }
        {
            EXPECT_FALSE(parse("sx" | as_utf32, double_s_p));
        }
        {
            EXPECT_FALSE(parse("xs" | as_utf32, double_s_p));
        }
    }
    {
        constexpr auto s_p = no_case[string("s")];

        {
            auto const result = parse("s" | as_utf32, s_p);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, "s");
        }
        {
            EXPECT_FALSE(parse(capital_sharp_s | as_utf32, s_p));
        }
        {
            EXPECT_FALSE(parse(small_sharp_s | as_utf32, s_p));
        }
        {
            EXPECT_FALSE(parse(double_s | as_utf32, s_p));
        }
        {
            EXPECT_FALSE(parse("x" | as_utf32, s_p));
        }
    }
}

TEST(no_case, detail_no_case_iter)
{
    {
        constexpr auto mixed_sharp_s1 = U"ẞs";
        std::string folded;
        auto first =
            detail::no_case_iter(mixed_sharp_s1, detail::text::null_sentinel);
        while (first != detail::text::null_sentinel) {
            folded.push_back(*first);
            ++first;
        }
        EXPECT_EQ(folded, "sss");
        EXPECT_TRUE(first.base() == detail::text::null_sentinel);
    }
    {
        constexpr auto mixed_sharp_s2 = U"sẞ";
        std::string folded;
        auto first =
            detail::no_case_iter(mixed_sharp_s2, detail::text::null_sentinel);
        while (first != detail::text::null_sentinel) {
            folded.push_back(*first);
            ++first;
        }
        EXPECT_EQ(folded, "sss");
        EXPECT_TRUE(first.base() == detail::text::null_sentinel);
    }
}

TEST(no_case, detail_no_case_mismatch)
{
    constexpr auto mixed_sharp_s1 = U"ẞs";
    constexpr auto mixed_sharp_s2 = U"sẞ";
    auto const result = detail::no_case_aware_string_mismatch(
        mixed_sharp_s1,
        detail::text::null_sentinel,
        mixed_sharp_s2,
        detail::text::null_sentinel,
        true);
    EXPECT_TRUE(result.first == detail::text::null_sentinel);
    EXPECT_TRUE(result.second == detail::text::null_sentinel);
}

TEST(no_case, longer_multi_code_point_mapping)
{
    constexpr auto mixed_sharp_s1 = u8"ẞs";
    constexpr auto mixed_sharp_s2 = u8"sẞ";

    constexpr auto mixed_sharp_s3 = u8"sßs";

    constexpr auto all_sharp_s1 = u8"ẞßss";
    constexpr auto all_sharp_s2 = u8"ssẞß";
    constexpr auto all_sharp_s3 = u8"ẞssß";

    constexpr auto triple_s = u8"sss";
    constexpr auto quadruple_s = u8"ssSs";

    {
        constexpr auto mixed_sharp_s1_p = no_case[string(mixed_sharp_s1)];
        {
            auto const result = parse(triple_s | as_utf32, mixed_sharp_s1_p);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, (char const *)triple_s);
        }
        {
            auto const result =
                parse(mixed_sharp_s1 | as_utf32, mixed_sharp_s1_p);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, (char const *)mixed_sharp_s1);
        }
        {
            auto const result =
                parse(mixed_sharp_s2 | as_utf32, mixed_sharp_s1_p);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, (char const *)mixed_sharp_s2);
        }
    }
    {
        constexpr auto mixed_sharp_s2_p = no_case[string(mixed_sharp_s2)];
        {
            auto const result = parse(triple_s | as_utf32, mixed_sharp_s2_p);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, (char const *)triple_s);
        }
        {
            auto const result =
                parse(mixed_sharp_s1 | as_utf32, mixed_sharp_s2_p);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, (char const *)mixed_sharp_s1);
        }
        {
            auto const result =
                parse(mixed_sharp_s2 | as_utf32, mixed_sharp_s2_p);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, (char const *)mixed_sharp_s2);
        }
    }
    {
        constexpr auto triple_s_p = no_case[string(triple_s)];
        {
            auto const result = parse(triple_s | as_utf32, triple_s_p);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, (char const *)triple_s);
        }
        {
            auto const result = parse(mixed_sharp_s1 | as_utf32, triple_s_p);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, (char const *)mixed_sharp_s1);
        }
        {
            auto const result = parse(mixed_sharp_s2 | as_utf32, triple_s_p);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, (char const *)mixed_sharp_s2);
        }
    }
    {
        constexpr auto mixed_sharp_s3_p = no_case[string(mixed_sharp_s3)];
        {
            auto const result =
                parse(mixed_sharp_s3 | as_utf32, mixed_sharp_s3_p);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, (char const *)mixed_sharp_s3);
        }
        {
            auto const result = parse(quadruple_s | as_utf32, mixed_sharp_s3_p);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, (char const *)quadruple_s);
        }
    }
    {
        constexpr auto quadruple_s_p = no_case[string(quadruple_s)];
        {
            auto const result = parse(mixed_sharp_s3 | as_utf32, quadruple_s_p);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, (char const *)mixed_sharp_s3);
        }
        {
            auto const result = parse(quadruple_s | as_utf32, quadruple_s_p);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, (char const *)quadruple_s);
        }
    }
    {
        constexpr auto all_sharp_s1_p = no_case[string(all_sharp_s1)];
        {
            auto const result = parse(all_sharp_s1 | as_utf32, all_sharp_s1_p);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, (char const *)all_sharp_s1);
        }
        {
            auto const result = parse(all_sharp_s2 | as_utf32, all_sharp_s1_p);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, (char const *)all_sharp_s2);
        }
        {
            auto const result = parse(all_sharp_s3 | as_utf32, all_sharp_s1_p);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, (char const *)all_sharp_s3);
        }
        {
            auto const result = parse("ssssss" | as_utf32, all_sharp_s1_p);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, "ssssss");
        }
    }
    {
        constexpr auto all_sharp_s2_p = no_case[string(all_sharp_s1)];
        {
            auto const result = parse(all_sharp_s1 | as_utf32, all_sharp_s2_p);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, (char const *)all_sharp_s1);
        }
        {
            auto const result = parse(all_sharp_s2 | as_utf32, all_sharp_s2_p);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, (char const *)all_sharp_s2);
        }
        {
            auto const result = parse(all_sharp_s3 | as_utf32, all_sharp_s2_p);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, (char const *)all_sharp_s3);
        }
        {
            auto const result = parse("ssssss" | as_utf32, all_sharp_s2_p);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, "ssssss");
        }
    }
    {
        constexpr auto all_sharp_s3_p = no_case[string(all_sharp_s1)];
        {
            auto const result = parse(all_sharp_s1 | as_utf32, all_sharp_s3_p);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, (char const *)all_sharp_s1);
        }
        {
            auto const result = parse(all_sharp_s2 | as_utf32, all_sharp_s3_p);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, (char const *)all_sharp_s2);
        }
        {
            auto const result = parse(all_sharp_s3 | as_utf32, all_sharp_s3_p);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, (char const *)all_sharp_s3);
        }
        {
            auto const result = parse("ssSsss" | as_utf32, all_sharp_s3_p);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, "ssSsss");
        }
    }
}
