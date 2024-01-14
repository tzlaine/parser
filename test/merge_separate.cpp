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

TEST(merge_separate, merge_)
{
    {
        constexpr auto parser = merge[char_ >> ' ' >> char_];

        static_assert(
            std::is_same_v<decltype(parse("", parser)), std::optional<char>>);

        {
            auto result = parse("a b", parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, 'b');
        }
    }
    {
        constexpr auto parser = char_ >> merge[char_ >> char_] >> char_;

        static_assert(std::is_same_v<
                      decltype(parse("", parser)),
                      std::optional<tuple<char, char, char>>>);

        {
            EXPECT_FALSE(parse("ab", parser));
            EXPECT_FALSE(parse("abc", parser));
            auto result = parse("abcd", parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, detail::hl::make_tuple('a', 'c', 'd'));
        }
    }
    {
        constexpr auto parser = char_ >> merge[eps >> char_ >> char_] >> char_;

        static_assert(std::is_same_v<
                      decltype(parse("", parser)),
                      std::optional<tuple<char, char, char>>>);

        {
            EXPECT_FALSE(parse("ab", parser));
            EXPECT_FALSE(parse("abc", parser));
            auto result = parse("abcd", parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, detail::hl::make_tuple('a', 'c', 'd'));
        }
    }
    {
        constexpr auto parser = eps >> merge[eps >> char_ >> char_] >> char_;

        static_assert(std::is_same_v<
                      decltype(parse("", parser)),
                      std::optional<tuple<char, char>>>);

        {
            EXPECT_FALSE(parse("ab", parser));
            auto result = parse("abc", parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, detail::hl::make_tuple('b', 'c'));
        }
    }
    {
        constexpr auto parser = char_ >> merge[char_ >> eps >> char_] >> char_;

        static_assert(std::is_same_v<
                      decltype(parse("", parser)),
                      std::optional<tuple<char, char, char>>>);

        {
            EXPECT_FALSE(parse("ab", parser));
            EXPECT_FALSE(parse("abc", parser));
            auto result = parse("abcd", parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, detail::hl::make_tuple('a', 'c', 'd'));
        }
    }
    {
        constexpr auto parser = char_ >> merge[char_ >> char_ >> eps] >> char_;

        static_assert(std::is_same_v<
                      decltype(parse("", parser)),
                      std::optional<tuple<char, char, char>>>);

        {
            EXPECT_FALSE(parse("ab", parser));
            EXPECT_FALSE(parse("abc", parser));
            auto result = parse("abcd", parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, detail::hl::make_tuple('a', 'c', 'd'));
        }
    }
    {
        constexpr auto parser = eps >> merge[char_ >> char_ >> eps] >> char_;

        static_assert(std::is_same_v<
                      decltype(parse("", parser)),
                      std::optional<tuple<char, char>>>);

        {
            auto result = parse("abc", parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, detail::hl::make_tuple('b', 'c'));
        }
    }
    {
        constexpr auto parser = merge[string("abc") >> string("def")];

        static_assert(
            std::is_same_v<decltype(parse("", parser)), std::optional<std::string>>);

        {
            auto result = parse("abcdef", parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, "abcdef");
        }
    }
    {
        constexpr auto parser = eps >> merge[string("abc") >> string("def")];

        static_assert(
            std::is_same_v<decltype(parse("", parser)), std::optional<std::string>>);

        {
            auto result = parse("abcdef", parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, "abcdef");
        }
    }
    {
        constexpr auto parser = eps >> merge[eps >> string("abc") >> string("def")];

        static_assert(
            std::is_same_v<decltype(parse("", parser)), std::optional<std::string>>);

        {
            auto result = parse("abcdef", parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, "abcdef");
        }
    }
    {
        constexpr auto parser = merge[string("abc") >> string("def")] >> eps;

        static_assert(
            std::is_same_v<decltype(parse("", parser)), std::optional<std::string>>);

        {
            auto result = parse("abcdef", parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, "abcdef");
        }
    }
    {
        constexpr auto parser =
            eps >> merge[string("abc") >> string("def")] >> eps;

        static_assert(
            std::is_same_v<decltype(parse("", parser)), std::optional<std::string>>);

        {
            auto result = parse("abcdef", parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, "abcdef");
        }
    }
    {
        constexpr auto parser =
            char_ >> merge[string("abc") >> string("def")] >> string("ghi");

        static_assert(std::is_same_v<
                      decltype(parse("", parser)),
                      std::optional<tuple<char, std::string, std::string>>>);

        {
            auto result = parse("zabcdefghi", parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(
                *result,
                detail::hl::make_tuple(
                    'z', std::string("abcdef"), std::string("ghi")));
        }
    }
    {
        constexpr auto parser =
            char_ >>
            merge[merge[string("abc") >> string("def")] >> string("ghi")];

        static_assert(std::is_same_v<
                      decltype(parse("", parser)),
                      std::optional<tuple<char, std::string>>>);

        {
            auto result = parse("zabcdefghi", parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(
                *result, detail::hl::make_tuple('z', std::string("abcdefghi")));
        }
    }
#if 0 // TODO: Document that this does not work, and why (flattening), and how
      // making a rule for the parethesized part is a fix.
    {
        constexpr auto parser =
            char_ >> merge[(string("abc") >> char_ >> char_) >> string("ghi")];

        static_assert(std::is_same_v<
                      decltype(parse("", parser)),
                      std::optional<tuple<char, std::string>>>);

        {
            auto result = parse("abcefghi", parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(
                *result, detail::hl::make_tuple('z', std::string("abcefghi")));
        }
    }
#endif
}

TEST(merge_separate, separate_)
{
    {
        constexpr auto parser = +char_('a') >> ' ' >> char_;

        static_assert(std::is_same_v<
                      decltype(parse("", parser)),
                      std::optional<std::string>>);

        {
            auto result = parse("a b", parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, "ab");
        }
    }
    {
        constexpr auto parser = separate[+char_('a') >> ' ' >> char_];

        static_assert(std::is_same_v<
                      decltype(parse("", parser)),
                      std::optional<tuple<std::string, char>>>);

        {
            auto result = parse("a b", parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, detail::hl::make_tuple(std::string("a"), 'b'));
        }
    }
    {
        constexpr auto parser = separate[eps >> +char_('a') >> ' ' >> char_];

        static_assert(std::is_same_v<
                      decltype(parse("", parser)),
                      std::optional<tuple<std::string, char>>>);

        {
            auto result = parse("a b", parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, detail::hl::make_tuple(std::string("a"), 'b'));
        }
    }
    {
        constexpr auto parser = separate[+char_('a') >> ' ' >> char_];

        static_assert(std::is_same_v<
                      decltype(parse("", parser)),
                      std::optional<tuple<std::string, char>>>);

        {
            auto result = parse("a b", parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, detail::hl::make_tuple(std::string("a"), 'b'));
        }
    }
    {
        constexpr auto parser = separate[+char_('a') >> ' ' >> char_ >> eps];

        static_assert(std::is_same_v<
                      decltype(parse("", parser)),
                      std::optional<tuple<std::string, char>>>);

        {
            auto result = parse("a b", parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, detail::hl::make_tuple(std::string("a"), 'b'));
        }
    }
    {
        constexpr auto parser =
            eps >> separate[+char_('a') >> ' ' >> char_ >> eps];

        static_assert(std::is_same_v<
                      decltype(parse("", parser)),
                      std::optional<tuple<std::string, char>>>);

        {
            auto result = parse("a b", parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, detail::hl::make_tuple(std::string("a"), 'b'));
        }
    }
    {
        constexpr auto parser =
            separate[+char_('a') >> ' ' >> char_ >> eps] >> eps;

        static_assert(std::is_same_v<
                      decltype(parse("", parser)),
                      std::optional<tuple<std::string, char>>>);

        {
            auto result = parse("a b", parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, detail::hl::make_tuple(std::string("a"), 'b'));
        }
    }
    {
        constexpr auto parser =
            eps >> separate[+char_('a') >> ' ' >> char_ >> eps] >> eps;

        static_assert(std::is_same_v<
                      decltype(parse("", parser)),
                      std::optional<tuple<std::string, char>>>);

        {
            auto result = parse("a b", parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, detail::hl::make_tuple(std::string("a"), 'b'));
        }
    }
    {
        constexpr auto parser = eps >> separate[+char_('a') >> ' ' >> char_];

        static_assert(std::is_same_v<
                      decltype(parse("", parser)),
                      std::optional<tuple<std::string, char>>>);

        {
            auto result = parse("a b", parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, detail::hl::make_tuple(std::string("a"), 'b'));
        }
    }
    {
        constexpr auto parser = separate[+char_('a') >> ' ' >> char_] >> eps;

        static_assert(std::is_same_v<
                      decltype(parse("", parser)),
                      std::optional<tuple<std::string, char>>>);

        {
            auto result = parse("a b", parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, detail::hl::make_tuple(std::string("a"), 'b'));
        }
    }
    {
        constexpr auto parser =
            eps >> separate[+char_('a') >> ' ' >> char_] >> eps;

        static_assert(std::is_same_v<
                      decltype(parse("", parser)),
                      std::optional<tuple<std::string, char>>>);

        {
            auto result = parse("a b", parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, detail::hl::make_tuple(std::string("a"), 'b'));
        }
    }
}

TEST(merge_separate, merge_separate_interop)
{
    [[maybe_unused]] constexpr auto A =
        eps >> separate[+char_('a') >> ' ' >> char_] >> eps;
    [[maybe_unused]] constexpr auto B =
        char_ >> separate[+char_('a') >> ' ' >> char_] >> eps;
    [[maybe_unused]] constexpr auto C =
        eps >> separate[+char_('a') >> ' ' >> char_] >> char_;
    [[maybe_unused]] constexpr auto D =
        char_ >> separate[+char_('a') >> ' ' >> char_] >> char_;
    [[maybe_unused]] constexpr auto _0 =
        eps >> merge[string("abc") >> string("def")] >> eps;
    [[maybe_unused]] constexpr auto _1 =
        char_ >> merge[string("abc") >> string("def")] >> eps;
    [[maybe_unused]] constexpr auto _2 =
        eps >> merge[string("abc") >> string("def")] >> char_;
    [[maybe_unused]] constexpr auto _3 =
        char_ >> merge[string("abc") >> string("def")] >> char_;


    { // A0
        constexpr auto parser = eps >> separate[+char_('a') >> ' ' >> char_] >>
                                eps >> merge[string("abc") >> string("def")] >>
                                eps;

        static_assert(std::is_same_v<
                      decltype(parse("", parser)),
                      std::optional<tuple<std::string, char, std::string>>>);

        {
            auto result = parse("a babcdef", parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(
                *result,
                detail::hl::make_tuple(
                    std::string("a"), 'b', std::string("abcdef")));
        }
    }
    { // A1
        constexpr auto parser = eps >> separate[+char_('a') >> ' ' >> char_] >>
                                eps >> char_ >>
                                merge[string("abc") >> string("def")] >> eps;

        static_assert(
            std::is_same_v<
                decltype(parse("", parser)),
                std::optional<tuple<std::string, char, char, std::string>>>);

        {
            auto result = parse("a bzabcdef", parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(
                *result,
                detail::hl::make_tuple(
                    std::string("a"), 'b', 'z', std::string("abcdef")));
        }
    }
    { // A2
        constexpr auto parser = eps >> separate[+char_('a') >> ' ' >> char_] >>
                                eps >> merge[string("abc") >> string("def")] >>
                                char_;

        static_assert(
            std::is_same_v<
                decltype(parse("", parser)),
                std::optional<tuple<std::string, char, std::string, char>>>);

        {
            auto result = parse("a babcdefz", parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(
                *result,
                detail::hl::make_tuple(
                    std::string("a"), 'b', std::string("abcdef"), 'z'));
        }
    }
    { // A3
        constexpr auto parser = eps >> separate[+char_('a') >> ' ' >> char_] >>
                                eps >> char_ >>
                                merge[string("abc") >> string("def")] >> char_;

        static_assert(std::is_same_v<
                      decltype(parse("", parser)),
                      std::optional<
                          tuple<std::string, char, char, std::string, char>>>);

        {
            auto result = parse("a byabcdefz", parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(
                *result,
                detail::hl::make_tuple(
                    std::string("a"), 'b', 'y', std::string("abcdef"), 'z'));
        }
    }

    { // B0
        constexpr auto parser = char_ >> separate[+char_('a') >> ' ' >> char_] >>
                                eps >> merge[string("abc") >> string("def")] >>
                                eps;

        static_assert(
            std::is_same_v<
                decltype(parse("", parser)),
                std::optional<tuple<char, std::string, char, std::string>>>);
    }
    { // B1
        constexpr auto parser = char_ >> separate[+char_('a') >> ' ' >> char_] >>
                                eps >> char_ >>
                                merge[string("abc") >> string("def")] >> eps;

        static_assert(std::is_same_v<
                      decltype(parse("", parser)),
                      std::optional<
                          tuple<char, std::string, char, char, std::string>>>);
    }
    { // B2
        constexpr auto parser = char_ >> separate[+char_('a') >> ' ' >> char_] >>
                                eps >> merge[string("abc") >> string("def")] >>
                                char_;

        static_assert(std::is_same_v<
                      decltype(parse("", parser)),
                      std::optional<
                          tuple<char, std::string, char, std::string, char>>>);
    }
    { // B3
        constexpr auto parser = char_ >> separate[+char_('a') >> ' ' >> char_] >>
                                eps >> char_ >>
                                merge[string("abc") >> string("def")] >> char_;

        static_assert(
            std::is_same_v<
                decltype(parse("", parser)),
                std::optional<
                    tuple<char, std::string, char, char, std::string, char>>>);
    }

    { // C0
        constexpr auto parser = eps >> separate[+char_('a') >> ' ' >> char_] >>
                                char_ >> eps >>
                                merge[string("abc") >> string("def")] >> eps;

        static_assert(
            std::is_same_v<
                decltype(parse("", parser)),
                std::optional<tuple<std::string, char, char, std::string>>>);
    }
    { // C1
        constexpr auto parser = eps >> separate[+char_('a') >> ' ' >> char_] >>
                                char_ >> char_ >>
                                merge[string("abc") >> string("def")] >> eps;

        static_assert(std::is_same_v<
                      decltype(parse("", parser)),
                      std::optional<
                          tuple<std::string, char, std::string, std::string>>>);
    }
    { // C2
        constexpr auto parser = eps >> separate[+char_('a') >> ' ' >> char_] >>
                                char_ >> eps >>
                                merge[string("abc") >> string("def")] >> char_;

        static_assert(std::is_same_v<
                      decltype(parse("", parser)),
                      std::optional<
                          tuple<std::string, char, char, std::string, char>>>);
    }
    { // C3
        constexpr auto parser = eps >> separate[+char_('a') >> ' ' >> char_] >>
                                char_ >> char_ >>
                                merge[string("abc") >> string("def")] >> char_;

        static_assert(
            std::is_same_v<
                decltype(parse("", parser)),
                std::optional<
                    tuple<std::string, char, std::string, std::string, char>>>);
    }

    { // D0
        constexpr auto parser =
            char_ >> separate[+char_('a') >> ' ' >> char_] >> char_ >> eps >>
            merge[string("abc") >> string("def")] >> eps;

        static_assert(std::is_same_v<
                      decltype(parse("", parser)),
                      std::optional<
                          tuple<char, std::string, char, char, std::string>>>);
    }
    { // D1
        constexpr auto parser =
            char_ >> separate[+char_('a') >> ' ' >> char_] >> char_ >> char_ >>
            merge[string("abc") >> string("def")] >> eps >> char_;

        static_assert(std::is_same_v<
                      decltype(parse("", parser)),
                      std::optional<tuple<
                          char,
                          std::string,
                          char,
                          std::string,
                          std::string,
                          char>>>);
    }
    { // D2
        constexpr auto parser =
            char_ >> separate[+char_('a') >> ' ' >> char_] >> char_ >> eps >>
            merge[string("abc") >> string("def")] >> char_;

        static_assert(
            std::is_same_v<
                decltype(parse("", parser)),
                std::optional<
                    tuple<char, std::string, char, char, std::string, char>>>);
    }
    { // D3
        constexpr auto parser =
            char_ >> separate[+char_('a') >> ' ' >> char_] >> char_ >> char_ >>
            merge[string("abc") >> string("def")] >> char_;

        static_assert(std::is_same_v<
                      decltype(parse("", parser)),
                      std::optional<tuple<
                          char,
                          std::string,
                          char,
                          std::string,
                          std::string,
                          char>>>);
    }

    {
        constexpr auto parser = separate[+char_('a') >> ' ' >> char_] >>
                                merge[string("abc") >> string("def")] >>
                                separate[+char_('a') >> ' ' >> char_] >>
                                merge[string("abc") >> string("def")];

        static_assert(std::is_same_v<
                      decltype(parse("", parser)),
                      std::optional<tuple<
                          std::string,
                          char,
                          std::string,
                          std::string,
                          char,
                          std::string>>>);
    }
    {
        constexpr auto parser = separate[+char_('a') >> ' ' >> char_] >> eps >>
                                merge[string("abc") >> string("def")] >> eps >>
                                separate[+char_('a') >> ' ' >> char_] >> eps >>
                                merge[string("abc") >> string("def")];

        static_assert(std::is_same_v<
                      decltype(parse("", parser)),
                      std::optional<tuple<
                          std::string,
                          char,
                          std::string,
                          std::string,
                          char,
                          std::string>>>);
    }
}
