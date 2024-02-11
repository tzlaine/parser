/**
 *   Copyright (C) 2018 T. Zachary Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See
 *   accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt)
 */

#include <boost/parser/parser.hpp>
#include <boost/parser/transcode_view.hpp>

#if __has_include(<boost/optional/optional.hpp>)
#define TEST_BOOST_OPTIONAL 1
#include <boost/optional/optional.hpp>
#else
#define TEST_BOOST_OPTIONAL 0
#endif

#include <gtest/gtest.h>


using namespace boost::parser;

#if BOOST_PARSER_DETAIL_TEXT_USE_CONCEPTS && defined(_MSC_VER)
#include <algorithm>

TEST(parser, msvc_string_view)
{
    std::string_view sv = "text";
    std::wstring_view wsv = L"text";

    {
        auto r = detail::text::as_utf8(sv);
        std::string str = "    ";
        std::ranges::copy(r, str.begin());
        EXPECT_EQ(str, sv);
    }
    {
        auto r = detail::text::as_utf8(wsv);
        std::wstring wstr = L"    ";
        std::ranges::copy(r, wstr.begin());
        EXPECT_EQ(wstr, wsv);
    }
    {
        auto r = sv | detail::text::as_utf8;
        std::string str = "    ";
        std::ranges::copy(r, str.begin());
        EXPECT_EQ(str, sv);
    }
    {
        auto r = wsv | detail::text::as_utf8;
        std::wstring wstr = L"    ";
        std::ranges::copy(r, wstr.begin());
        EXPECT_EQ(wstr, wsv);
    }

    {
        auto r = detail::text::as_utf16(sv);
        std::string str = "    ";
        std::ranges::copy(r, str.begin());
        EXPECT_EQ(str, sv);
    }
    {
        auto r = detail::text::as_utf16(wsv);
        std::wstring wstr = L"    ";
        std::ranges::copy(r, wstr.begin());
        EXPECT_EQ(wstr, wsv);
    }
    {
        auto r = sv | detail::text::as_utf16;
        std::string str = "    ";
        std::ranges::copy(r, str.begin());
        EXPECT_EQ(str, sv);
    }
    {
        auto r = wsv | detail::text::as_utf16;
        std::wstring wstr = L"    ";
        std::ranges::copy(r, wstr.begin());
        EXPECT_EQ(wstr, wsv);
    }

    {
        auto r = detail::text::as_utf32(sv);
        std::string str = "    ";
        std::ranges::copy(r, str.begin());
        EXPECT_EQ(str, sv);
    }
    {
        auto r = detail::text::as_utf32(wsv);
        std::wstring wstr = L"    ";
        std::ranges::copy(r, wstr.begin());
        EXPECT_EQ(wstr, wsv);
    }
    {
        auto r = sv | detail::text::as_utf32;
        std::string str = "    ";
        std::ranges::copy(r, str.begin());
        EXPECT_EQ(str, sv);
    }
    {
        auto r = wsv | detail::text::as_utf32;
        std::wstring wstr = L"    ";
        std::ranges::copy(r, wstr.begin());
        EXPECT_EQ(wstr, wsv);
    }
}

TEST(parser, msvc_string)
{
    std::string sv = "text";
    std::wstring wsv = L"text";

    {
        auto r = detail::text::as_utf8(sv);
        std::string str = "    ";
        std::ranges::copy(r, str.begin());
        EXPECT_EQ(str, sv);
    }
    {
        auto r = detail::text::as_utf8(wsv);
        std::wstring wstr = L"    ";
        std::ranges::copy(r, wstr.begin());
        EXPECT_EQ(wstr, wsv);
    }
    {
        auto r = sv | detail::text::as_utf8;
        std::string str = "    ";
        std::ranges::copy(r, str.begin());
        EXPECT_EQ(str, sv);
    }
    {
        auto r = wsv | detail::text::as_utf8;
        std::wstring wstr = L"    ";
        std::ranges::copy(r, wstr.begin());
        EXPECT_EQ(wstr, wsv);
    }

    {
        auto r = detail::text::as_utf16(sv);
        std::string str = "    ";
        std::ranges::copy(r, str.begin());
        EXPECT_EQ(str, sv);
    }
    {
        auto r = detail::text::as_utf16(wsv);
        std::wstring wstr = L"    ";
        std::ranges::copy(r, wstr.begin());
        EXPECT_EQ(wstr, wsv);
    }
    {
        auto r = sv | detail::text::as_utf16;
        std::string str = "    ";
        std::ranges::copy(r, str.begin());
        EXPECT_EQ(str, sv);
    }
    {
        auto r = wsv | detail::text::as_utf16;
        std::wstring wstr = L"    ";
        std::ranges::copy(r, wstr.begin());
        EXPECT_EQ(wstr, wsv);
    }

    {
        auto r = detail::text::as_utf32(sv);
        std::string str = "    ";
        std::ranges::copy(r, str.begin());
        EXPECT_EQ(str, sv);
    }
    {
        auto r = detail::text::as_utf32(wsv);
        std::wstring wstr = L"    ";
        std::ranges::copy(r, wstr.begin());
        EXPECT_EQ(wstr, wsv);
    }
    {
        auto r = sv | detail::text::as_utf32;
        std::string str = "    ";
        std::ranges::copy(r, str.begin());
        EXPECT_EQ(str, sv);
    }
    {
        auto r = wsv | detail::text::as_utf32;
        std::wstring wstr = L"    ";
        std::ranges::copy(r, wstr.begin());
        EXPECT_EQ(wstr, wsv);
    }
}
#endif

#if TEST_BOOST_OPTIONAL
template<typename T>
constexpr bool boost::parser::enable_optional<boost::optional<T>> = true;
#endif

TEST(parser, basic)
{
    constexpr auto parser_1 = char_ >> char_;
    constexpr auto parser_2 = char_ >> char_ >> char_;
    constexpr auto parser_3 = char_ | char_;
    constexpr auto parser_4 = char_('a') | char_('b') | char_('c');
    constexpr auto parser_5 = char_('a') | char_('b') | eps;

    {
        std::string str = "a";
        EXPECT_TRUE(parse(str, char_));
        EXPECT_FALSE(parse(str, char_('b')));
    }
    {
        std::string str = "a";
        char c = '\0';
        EXPECT_TRUE(parse(str, char_, c));
        EXPECT_EQ(c, 'a');
        EXPECT_FALSE(parse(str, char_('b')));
    }
    {
        std::string str = "b";
        char c = '\0';
        EXPECT_TRUE(parse(str, char_("ab"), c));
        EXPECT_EQ(c, 'b');
        EXPECT_FALSE(parse(str, char_("cd")));
    }
    {
        std::string str = "b";
        char c = '\0';
        std::string const pattern_1 = "ab";
        std::string const pattern_2 = "cd";
        EXPECT_TRUE(parse(str, char_(pattern_1), c));
        EXPECT_EQ(c, 'b');
        EXPECT_FALSE(parse(str, char_(pattern_2)));
    }
    {
        std::string str = "b";
        char c = '\0';
        EXPECT_TRUE(parse(str, char_('a', 'b'), c));
        EXPECT_EQ(c, 'b');
        EXPECT_FALSE(parse(str, char_('c', 'd')));
    }
    {
        std::string str = " ";
        EXPECT_TRUE(parse(str, blank));
        EXPECT_FALSE(parse(str, lower));
    }
    {
        std::string str = "ab";
        EXPECT_FALSE(parse(str, char_));
        {
            auto first = str.c_str();
            EXPECT_TRUE(prefix_parse(
                first, boost::parser::detail::text::null_sentinel, char_));
        }
        EXPECT_TRUE(parse(str, parser_1));
        EXPECT_FALSE(parse(str, parser_2));
    }
    {
        std::string str = "ab";
        tuple<char, char> result;
        EXPECT_TRUE(parse(str, parser_1, result));
        using namespace boost::parser::literals;
        EXPECT_EQ(get(result, 0_c), 'b');
        EXPECT_EQ(get(result, 1_c), '\0');
    }
    {
        std::string str = "abc";
        EXPECT_FALSE(parse(str, parser_1));
        {
            auto first = str.c_str();
            EXPECT_TRUE(prefix_parse(
                first, boost::parser::detail::text::null_sentinel, parser_1));
        }
        EXPECT_TRUE(parse(str, parser_2));
    }
    {
        std::string str = "abc";
        tuple<char, char, char> result;
        EXPECT_TRUE(parse(str, parser_2, result));
        using namespace boost::parser::literals;
        EXPECT_EQ(get(result, 0_c), 'c');
        EXPECT_EQ(get(result, 1_c), '\0');
        EXPECT_EQ(get(result, 2_c), '\0');
    }
    {
        std::string str = "a";
        EXPECT_TRUE(parse(str, parser_3));
        EXPECT_TRUE(parse(str, parser_4));
    }
    {
        std::string str = "a";
        char c = '\0';
        EXPECT_TRUE(parse(str, parser_3, c));
        EXPECT_EQ(c, 'a');
    }
    {
        std::string str = "a";
        char c = '\0';
        EXPECT_TRUE(parse(str, parser_4, c));
        EXPECT_EQ(c, 'a');
    }
    {
        std::string str = "z";
        EXPECT_TRUE(parse(str, parser_3));
        EXPECT_FALSE(parse(str, parser_4));
    }
    {
        std::string str = "a";
        EXPECT_TRUE(parse(str, parser_5));
    }
    {
        std::string str = "z";
        EXPECT_FALSE(parse(str, parser_5));
        {
            auto first = str.c_str();
            EXPECT_TRUE(prefix_parse(
                first, boost::parser::detail::text::null_sentinel, parser_5));
        }
    }
    {
        std::string str = "a";
        std::optional<char> c;
        EXPECT_TRUE(parse(str, parser_5, c));
        EXPECT_EQ(c, 'a');
    }
    {
        std::string str = "z";
        std::optional<char> c;
        EXPECT_FALSE(parse(str, parser_5, c));
    }
    {
        std::string str = "z";
        std::optional<char> c;
        auto first = str.c_str();
        EXPECT_TRUE(prefix_parse(
            first, boost::parser::detail::text::null_sentinel, parser_5, c));
        EXPECT_EQ(c, std::nullopt);
    }
#if TEST_BOOST_OPTIONAL
    {
        std::string str = "a";
        boost::optional<char> c;
        EXPECT_TRUE(parse(str, parser_5, c));
        EXPECT_EQ(c, 'a');
    }
    {
        std::string str = "z";
        boost::optional<char> c;
        EXPECT_FALSE(parse(str, parser_5, c));
    }
    {
        std::string str = "z";
        boost::optional<char> c;
        auto first = str.c_str();
        EXPECT_TRUE(prefix_parse(
            first, boost::parser::detail::text::null_sentinel, parser_5, c));
        EXPECT_EQ(c, boost::none);
    }
#endif
    {
        constexpr auto parser = *(char_ - "str") >> *string("str");
        std::string str = "somethingstrstrstr";
        auto result = boost::parser::parse(str, parser);
        EXPECT_TRUE(result);
        EXPECT_EQ(
            *result,
            std::vector<std::string>({"something", "str", "str", "str"}));
    }
}

TEST(parser, int_uint)
{
    {
        std::string str = "-42";
        int i = 0;
        EXPECT_TRUE(parse(str, int_, i));
        EXPECT_EQ(i, -42);
    }
    {
        std::string str = "42";
        int i = 0;
        EXPECT_TRUE(parse(str, int_, i));
        EXPECT_EQ(i, 42);
    }
    {
        std::string str = "-42";
        int i = 3;
        EXPECT_FALSE(parse(str, uint_, i));
        EXPECT_EQ(i, 0);
    }
    {
        std::string str = "42";
        int i = 0;
        EXPECT_TRUE(parse(str, uint_, i));
        EXPECT_EQ(i, 42);
    }
}

TEST(parser, bool_)
{
    {
        std::string str = "";
        bool b = false;
        EXPECT_FALSE(parse(str, bool_, b));
    }
    {
        std::string str = "true";
        bool b = false;
        EXPECT_TRUE(parse(str, bool_, b));
        EXPECT_EQ(b, true);
    }
    {
        std::string str = "false ";
        bool b = true;
        EXPECT_FALSE(parse(str, bool_, b));
        EXPECT_EQ(b, false);
    }
    {
        std::string str = "false ";
        bool b = true;
        auto first = str.c_str();
        EXPECT_TRUE(prefix_parse(
            first, boost::parser::detail::text::null_sentinel, bool_, b));
        EXPECT_EQ(b, false);
    }
    {
        std::string str = "true ";
        auto r = boost::parser::detail::text::as_utf32(str);
        bool b = false;
        auto first = r.begin();
        auto const last = r.end();
        EXPECT_TRUE(prefix_parse(first, last, bool_, b));
        EXPECT_EQ(b, true);
    }
    {
        std::string str = "false";
        auto r = boost::parser::detail::text::as_utf32(str);
        bool b = true;
        auto first = r.begin();
        auto const last = r.end();
        EXPECT_TRUE(prefix_parse(first, last, bool_, b));
        EXPECT_EQ(b, false);
    }
}

TEST(parser, star)
{
    {
        constexpr auto parser = *char_;
        {
            std::string str = "";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>());
        }
        {
            std::string str = "a";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'a'}));
        }
        {
            std::string str = "ba";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'b', 'a'}));
        }
    }

    {
        constexpr auto parser = *char_('b');
        {
            std::string str = "";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>());
        }
        {
            std::string str = "b";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'b'}));
        }
        {
            std::string str = "bb";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'b', 'b'}));
        }
    }
}

TEST(parser, plus)
{
    {
        constexpr auto parser = +char_;

        {
            std::string str = "";
            std::vector<char> chars;
            EXPECT_FALSE(parse(str, parser, chars));
        }
        {
            std::string str = "a";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'a'}));
        }
        {
            std::string str = "ba";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'b', 'a'}));
        }
    }

    {
        constexpr auto parser = +char_('b');

        {
            std::string str = "";
            std::vector<char> chars;
            EXPECT_FALSE(parse(str, parser, chars));
        }
        {
            std::string str = "b";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'b'}));
        }
        {
            std::string str = "bb";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'b', 'b'}));
        }
    }
}

TEST(parser, star_and_plus_collapsing)
{
    {
        constexpr auto parser = +(+char_('b'));

        {
            std::string str = "";
            std::vector<char> chars;
            EXPECT_FALSE(parse(str, parser, chars));
        }
        {
            std::string str = "b";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'b'}));
        }
        {
            std::string str = "bb";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'b', 'b'}));
        }
    }

    {
        constexpr auto parser = **char_('z');

        {
            std::string str = "";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>());
        }
        {
            std::string str = "z";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'z'}));
        }
        {
            std::string str = "zz";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'z', 'z'}));
        }
    }

    {
        constexpr auto parser = +*char_('z');

        {
            std::string str = "";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>());
        }
        {
            std::string str = "z";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'z'}));
        }
        {
            std::string str = "zz";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'z', 'z'}));
        }
    }

    {
        constexpr auto parser = *+char_('z');

        {
            std::string str = "";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>());
        }
        {
            std::string str = "z";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'z'}));
        }
        {
            std::string str = "zz";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'z', 'z'}));
        }
    }
}

TEST(parser, action)
{
    {{std::string str = "";
    std::stringstream ss;
    auto action = [&ss](auto & context) { ss << _attr(context); };
    auto parser = *char_('b')[action];
    EXPECT_TRUE(parse(str, parser));
    EXPECT_EQ(ss.str(), "");
}
{
    std::string str = "b";
    std::stringstream ss;
    auto action = [&ss](auto & context) { ss << _attr(context); };
    auto parser = *char_('b')[action];
    EXPECT_TRUE(parse(str, parser));
    EXPECT_EQ(ss.str(), "b");
}
{
    std::string str = "bb";
    std::stringstream ss;
    auto action = [&ss](auto & context) { ss << _attr(context); };
    auto parser = *char_('b')[action];
    EXPECT_TRUE(parse(str, parser));
    EXPECT_TRUE(parse(str, parser));
    EXPECT_EQ(ss.str(), "bbbb");
}
}

{
    {
        std::string str = "";
        std::stringstream ss;
        auto action = [&ss](auto & context) { ss << _attr(context); };
        auto parser = +char_('b')[action];
        EXPECT_FALSE(parse(str, parser));
        EXPECT_EQ(ss.str(), "");
    }
    {
        std::string str = "b";
        std::stringstream ss;
        auto action = [&ss](auto & context) { ss << _attr(context); };
        auto parser = +char_('b')[action];
        EXPECT_TRUE(parse(str, parser));
        EXPECT_EQ(ss.str(), "b");
    }
    {
        std::string str = "bb";
        std::stringstream ss;
        auto action = [&ss](auto & context) { ss << _attr(context); };
        auto parser = +char_('b')[action];
        EXPECT_TRUE(parse(str, parser));
        EXPECT_TRUE(parse(str, parser));
        EXPECT_EQ(ss.str(), "bbbb");
    }
}
}

TEST(parser, star_as_string_or_vector)
{
    {
        constexpr auto parser = *char_('z');

        {
            std::string str = "";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, "");
        }
        {
            std::string str = "z";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, "z");
        }
        {
            std::string str = "zz";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, "zz");
        }
    }

    {
        constexpr auto parser = *char_('z');

        {
            std::string str = "";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>());
        }
        {
            std::string str = "z";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'z'}));
        }
        {
            std::string str = "zz";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'z', 'z'}));
        }
    }

    {
        constexpr auto parser = *string("zs");

        {
            std::string str = "";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<std::string>{});

            {
                std::optional<std::vector<std::string>> const chars =
                    parse(str, parser);
                EXPECT_TRUE(chars);
                EXPECT_TRUE(chars->empty());
            }
        }
        {
            std::string str = "z";
            {
                std::vector<std::string> chars;
                EXPECT_FALSE(parse(str, parser, chars));
                EXPECT_EQ(chars, std::vector<std::string>{});
            }
            {
                std::vector<std::string> chars;
                auto first = str.c_str();
                EXPECT_TRUE(prefix_parse(
                    first,
                    boost::parser::detail::text::null_sentinel,
                    parser,
                    chars));
                EXPECT_EQ(chars, std::vector<std::string>{});
            }

            {
                std::optional<std::vector<std::string>> const chars =
                    parse(str, parser);
                EXPECT_FALSE(chars);
            }
            {
                auto first = str.c_str();
                std::optional<std::vector<std::string>> const chars =
                    prefix_parse(
                        first,
                        boost::parser::detail::text::null_sentinel,
                        parser);
                EXPECT_TRUE(chars);
                EXPECT_TRUE(chars->empty());
            }
        }
        {
            std::string str = "zs";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<std::string>({"zs"}));

            {
                std::optional<std::vector<std::string>> const chars =
                    parse(str, parser);
                EXPECT_TRUE(chars);
                EXPECT_EQ(*chars, std::vector<std::string>({"zs"}));
            }
        }
        {
            std::string str = "zszs";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<std::string>({"zs", "zs"}));

            {
                std::optional<std::vector<std::string>> const chars =
                    parse(str, parser);
                EXPECT_TRUE(chars);
                EXPECT_EQ(*chars, std::vector<std::string>({"zs", "zs"}));
            }
        }
    }

    {
        constexpr auto parser = *string("zs");

        {
            std::string str = "";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<std::string>());
        }
        {
            std::string str = "z";
            std::vector<std::string> chars;
            EXPECT_FALSE(parse(str, parser, chars));
        }
        {
            std::string str = "z";
            std::vector<std::string> chars;
            auto first = str.c_str();
            EXPECT_TRUE(prefix_parse(
                first,
                boost::parser::detail::text::null_sentinel,
                parser,
                chars));
        }
        {
            std::string str = "zs";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<std::string>({"zs"}));
        }
        {
            std::string str = "zszs";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<std::string>({"zs", "zs"}));
        }
    }
}

TEST(parser, omit)
{
    {
        constexpr auto parser = omit[*+char_('z')];

        {
            std::string str = "";
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string str = "z";
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string str = "zz";
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string str = "";
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string str = "z";
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string str = "zz";
            EXPECT_TRUE(parse(str, parser));
        }
    }

    {
        constexpr auto parser = omit[*string("zs")];

        {
            std::string str = "";
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string str = "z";
            EXPECT_FALSE(parse(str, parser));
        }
        {
            std::string str = "z";
            auto first = str.c_str();
            EXPECT_TRUE(prefix_parse(
                first, boost::parser::detail::text::null_sentinel, parser));
        }
        {
            std::string str = "zs";
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string str = "zszs";
            EXPECT_TRUE(parse(str, parser));
        }
    }
}

TEST(parser, repeat)
{
    {
        constexpr auto parser = repeat(2, 3)[string("zs")];

        {
            std::string str = "";
            std::vector<std::string> chars;
            EXPECT_FALSE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<std::string>{});

            {
                std::optional<std::vector<std::string>> const chars =
                    parse(str, parser);
                EXPECT_FALSE(chars);
            }
        }
        {
            std::string str = "z";
            std::vector<std::string> chars;
            EXPECT_FALSE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<std::string>{});

            {
                std::optional<std::vector<std::string>> const chars =
                    parse(str, parser);
                EXPECT_FALSE(chars);
            }
        }
        {
            std::string str = "zs";
            std::vector<std::string> chars;
            EXPECT_FALSE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<std::string>{});

            {
                std::optional<std::vector<std::string>> const chars =
                    parse(str, parser);
                EXPECT_FALSE(chars);
            }
        }
        {
            std::string str = "zszs";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<std::string>({"zs", "zs"}));

            {
                std::optional<std::vector<std::string>> const chars =
                    parse(str, parser);
                EXPECT_TRUE(chars);
                EXPECT_EQ(*chars, std::vector<std::string>({"zs", "zs"}));
            }
        }
    }
    {
        constexpr auto parser = *char_ >> eps >> *string("str");
        auto result = parse("abcdefg", parser);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, std::vector<std::string>({"abcdefg"}));
    }
    {
        constexpr auto parser = *(char_ - "str") >> eps >> *string("str");
        auto result = parse("abcdefgstrstr", parser);
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, std::vector<std::string>({"abcdefg", "str", "str"}));
    }
}

TEST(parser, raw)
{
    {
        constexpr auto parser = raw[*string("zs")];
        using range_t =
            BOOST_PARSER_DETAIL_TEXT_SUBRANGE<std::string::const_iterator>;

        {
            std::string const str = "";
            range_t r;
            EXPECT_TRUE(parse(str, parser, r));
            EXPECT_EQ(r.begin(), str.begin());
            EXPECT_EQ(r.end(), str.begin());
        }
        {
            std::string const str = "z";
            range_t r;
            EXPECT_FALSE(parse(str, parser, r));
            EXPECT_EQ(r.begin(), r.end());
        }
        {
            std::string const str = "z";
            range_t r;
            auto first = str.begin();
            EXPECT_TRUE(prefix_parse(first, str.end(), parser, r));
            EXPECT_EQ(r.begin(), str.begin());
            EXPECT_EQ(r.end(), str.begin());
        }
        {
            std::string const str = "zs";
            range_t r;
            EXPECT_TRUE(parse(str, parser, r));
            EXPECT_EQ(r.begin(), str.begin());
            EXPECT_EQ(r.end(), str.end());
        }
        {
            std::string const str = "zszs";
            range_t r;
            EXPECT_TRUE(parse(str, parser, r));
            EXPECT_EQ(r.begin(), str.begin());
            EXPECT_EQ(r.end(), str.end());
        }
        {
            std::string const str = "";
            std::optional<range_t> result = parse(str, parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(result->begin(), str.begin());
            EXPECT_EQ(result->end(), str.begin());
        }
        {
            std::string const str = "z";
            std::optional<range_t> result = parse(str, parser);
            EXPECT_FALSE(result);
        }
        {
            std::string const str = "z";
            auto first = str.begin();
            std::optional<range_t> result =
                prefix_parse(first, str.end(), parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(result->begin(), str.begin());
            EXPECT_EQ(result->end(), str.begin());
        }
        {
            std::string const str = "zs";
            std::optional<range_t> result = parse(str, parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(result->begin(), str.begin());
            EXPECT_EQ(result->end(), str.end());
        }
        {
            std::string const str = "zszs";
            std::optional<range_t> result = parse(str, parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(result->begin(), str.begin());
            EXPECT_EQ(result->end(), str.end());
        }
    }
}

#if defined(__cpp_lib_concepts)
TEST(parser, string_view)
{
    {
        constexpr auto parser = string_view[*string("zs")];
        using range_t = std::string_view;

        {
            std::string const str = "";
            range_t r;
            EXPECT_TRUE(parse(str, parser, r));
            EXPECT_EQ(r, "");
        }
        {
            std::string const str = "z";
            range_t r;
            EXPECT_FALSE(parse(str, parser, r));
            EXPECT_EQ(r, "");
        }
        {
            std::string const str = "z";
            range_t r;
            auto first = str.begin();
            EXPECT_TRUE(prefix_parse(first, str.end(), parser, r));
            EXPECT_EQ(r, "");
        }
        {
            std::string const str = "zs";
            range_t r;
            EXPECT_TRUE(parse(str, parser, r));
            EXPECT_EQ(r, "zs");
        }
        {
            std::string const str = "zszs";
            range_t r;
            EXPECT_TRUE(parse(str, parser, r));
            EXPECT_EQ(r, "zszs");
        }
        {
            std::string const str = "";
            std::optional<range_t> result = parse(str, parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, "");
        }
        {
            std::string const str = "z";
            std::optional<range_t> result = parse(str, parser);
            EXPECT_FALSE(result);
        }
        {
            std::string const str = "z";
            auto first = str.begin();
            std::optional<range_t> result =
                prefix_parse(first, str.end(), parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, "");
        }
        {
            std::string const str = "zs";
            std::optional<range_t> result = parse(str, parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, "zs");
        }
        {
            std::string const str = "zszs";
            std::optional<range_t> result = parse(str, parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, "zszs");
        }
    }
    {
        constexpr auto parser = string_view[*string("zs")];
        using range_t = std::u32string_view;

        {
            std::u32string const str = U"";
            range_t r;
            EXPECT_TRUE(parse(str, parser, r));
            EXPECT_TRUE(r == U"");
        }
        {
            std::u32string const str = U"z";
            range_t r;
            EXPECT_FALSE(parse(str, parser, r));
            EXPECT_TRUE(r == U"");
        }
        {
            std::u32string const str = U"z";
            range_t r;
            auto first = str.begin();
            EXPECT_TRUE(prefix_parse(first, str.end(), parser, r));
            EXPECT_TRUE(r == U"");
        }
        {
            std::u32string const str = U"zs";
            range_t r;
            EXPECT_TRUE(parse(str, parser, r));
            EXPECT_TRUE(r == U"zs");
        }
        {
            std::u32string const str = U"zszs";
            range_t r;
            EXPECT_TRUE(parse(str, parser, r));
            EXPECT_TRUE(r == U"zszs");
        }
        {
            std::u32string const str = U"";
            std::optional<range_t> result = parse(str, parser);
            EXPECT_TRUE(result);
            EXPECT_TRUE(*result == U"");
        }
        {
            std::u32string const str = U"z";
            std::optional<range_t> result = parse(str, parser);
            EXPECT_FALSE(result);
        }
        {
            std::u32string const str = U"z";
            auto first = str.begin();
            std::optional<range_t> result =
                prefix_parse(first, str.end(), parser);
            EXPECT_TRUE(result);
            EXPECT_TRUE(*result == U"");
        }
        {
            std::u32string const str = U"zs";
            std::optional<range_t> result = parse(str, parser);
            EXPECT_TRUE(result);
            EXPECT_TRUE(*result == U"zs");
        }
        {
            std::u32string const str = U"zszs";
            std::optional<range_t> result = parse(str, parser);
            EXPECT_TRUE(result);
            EXPECT_TRUE(*result == U"zszs");
        }
    }
}
#endif

TEST(parser, delimited)
{
    {
        constexpr auto parser = string("yay") % ',';

        {
            std::string str = "";
            std::vector<std::string> chars;
            EXPECT_FALSE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<std::string>{});

            {
                std::optional<std::vector<std::string>> const chars =
                    parse(str, parser);
                EXPECT_FALSE(chars);
            }
        }
        {
            std::string str = "z";
            std::vector<std::string> chars;
            EXPECT_FALSE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<std::string>{});

            {
                std::optional<std::vector<std::string>> const chars =
                    parse(str, parser);
                EXPECT_FALSE(chars);
            }
        }
        {
            std::string str = ",";
            std::vector<std::string> chars;
            EXPECT_FALSE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<std::string>{});

            {
                std::optional<std::vector<std::string>> const chars =
                    parse(str, parser);
                EXPECT_FALSE(chars);
            }
        }
        {
            std::string str = ",yay";
            std::vector<std::string> chars;
            EXPECT_FALSE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<std::string>{});

            {
                std::optional<std::vector<std::string>> const chars =
                    parse(str, parser);
                EXPECT_FALSE(chars);
            }
        }
        {
            std::string str = "yay";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<std::string>({"yay"}));

            {
                std::optional<std::vector<std::string>> const chars =
                    parse(str, parser);
                EXPECT_TRUE(chars);
                EXPECT_EQ(*chars, std::vector<std::string>({"yay"}));
            }
        }
        {
            std::string str = "yayyay";
            {
                std::vector<std::string> chars;
                EXPECT_FALSE(parse(str, parser, chars));
                EXPECT_EQ(chars, std::vector<std::string>{});
            }
            {
                std::vector<std::string> chars;
                auto first = str.c_str();
                EXPECT_TRUE(prefix_parse(
                    first,
                    boost::parser::detail::text::null_sentinel,
                    parser,
                    chars));
                EXPECT_EQ(chars, std::vector<std::string>({"yay"}));
            }

            {
                std::optional<std::vector<std::string>> const chars =
                    parse(str, parser);
                EXPECT_FALSE(chars);
            }
            {
                auto first = str.c_str();
                std::optional<std::vector<std::string>> const chars =
                    prefix_parse(
                        first,
                        boost::parser::detail::text::null_sentinel,
                        parser);
                EXPECT_TRUE(chars);
                EXPECT_EQ(*chars, std::vector<std::string>({"yay"}));
            }
        }
        {
            std::string str = "yay,";
            {
                std::vector<std::string> chars;
                EXPECT_FALSE(parse(str, parser, chars));
            }
            {
                std::vector<std::string> chars;
                auto first = str.c_str();
                EXPECT_TRUE(prefix_parse(
                    first,
                    boost::parser::detail::text::null_sentinel,
                    parser,
                    chars));
                EXPECT_EQ(chars, std::vector<std::string>({"yay"}));
            }

            {
                std::optional<std::vector<std::string>> const chars =
                    parse(str, parser);
                EXPECT_FALSE(chars);
            }
            {
                auto first = str.c_str();
                std::optional<std::vector<std::string>> const chars =
                    prefix_parse(
                        first,
                        boost::parser::detail::text::null_sentinel,
                        parser);
                EXPECT_TRUE(chars);
                EXPECT_EQ(*chars, std::vector<std::string>({"yay"}));
            }
        }
        {
            std::string str = "yay,yay,yay";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<std::string>({"yay", "yay", "yay"}));

            {
                std::optional<std::vector<std::string>> const chars =
                    parse(str, parser);
                EXPECT_TRUE(chars);
                EXPECT_EQ(
                    *chars, std::vector<std::string>({"yay", "yay", "yay"}));
            }
        }
    }

    {
        constexpr auto parser = string("yay") % ',';
        {
            std::string str = "";
            std::vector<std::string> chars;
            EXPECT_FALSE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>{});
        }

        {
            std::string str = "";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser, char_(' '));
            EXPECT_FALSE(chars);
        }
        {
            std::string str = "z";
            std::vector<std::string> chars;
            EXPECT_FALSE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>{});
        }
        {
            std::string str = "z";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser, char_(' '));
            EXPECT_FALSE(chars);
        }
        {
            std::string str = ",";
            std::vector<std::string> chars;
            EXPECT_FALSE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>{});
        }
        {
            std::string str = ",";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser, char_(' '));
            EXPECT_FALSE(chars);
        }
        {
            std::string str = " ,yay";
            std::vector<std::string> chars;
            EXPECT_FALSE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>{});
        }
        {
            std::string str = " ,yay";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser, char_(' '));
            EXPECT_FALSE(chars);
        }
        {
            std::string str = ", yay";
            std::vector<std::string> chars;
            EXPECT_FALSE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>{});
        }
        {
            std::string str = ", yay";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser, char_(' '));
            EXPECT_FALSE(chars);
        }
        {
            std::string str = ",yay ";
            std::vector<std::string> chars;
            EXPECT_FALSE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>{});
        }
        {
            std::string str = ",yay ";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser, char_(' '));
            EXPECT_FALSE(chars);
        }

        {
            std::string str = " , yay ";
            std::vector<std::string> chars;
            EXPECT_FALSE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>{});
        }
        {
            std::string str = " , yay ";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser, char_(' '));
            EXPECT_FALSE(chars);
        }
        {
            std::string str = "yay";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>({"yay"}));
        }
        {
            std::string str = "yay";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser, char_(' '));
            EXPECT_TRUE(chars);
        }
        {
            std::string str = "yayyay";
            std::vector<std::string> chars;
            auto first = str.c_str();
            EXPECT_TRUE(prefix_parse(
                first,
                boost::parser::detail::text::null_sentinel,
                parser,
                char_(' '),
                chars));
            EXPECT_EQ(chars, std::vector<std::string>({"yay"}));
        }
        {
            std::string str = "yayyay";
            std::vector<std::string> chars;
            EXPECT_FALSE(parse(str, parser, char_(' '), chars));
        }
        {
            std::string str = "yayyay";
            std::vector<std::string> chars;
            auto first = str.c_str();
            EXPECT_TRUE(prefix_parse(
                first,
                boost::parser::detail::text::null_sentinel,
                parser,
                char_(' '),
                chars));
            EXPECT_EQ(chars, std::vector<std::string>({"yay"}));
        }
        {
            std::string str = "yayyay";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser, char_(' '));
            EXPECT_FALSE(chars);
        }
        {
            std::string str = "yayyay";
            auto first = str.c_str();
            std::optional<std::vector<std::string>> const chars = prefix_parse(
                first,
                boost::parser::detail::text::null_sentinel,
                parser,
                char_(' '));
            EXPECT_TRUE(chars);
                EXPECT_EQ(*chars, std::vector<std::string>({"yay"}));
        }
        {
            std::string str = "yay,";
            std::vector<std::string> chars;
            EXPECT_FALSE(parse(str, parser, char_(' '), chars));
        }
        {
            std::string str = "yay,";
            std::vector<std::string> chars;
            auto first = str.c_str();
            EXPECT_TRUE(prefix_parse(
                first,
                boost::parser::detail::text::null_sentinel,
                parser,
                char_(' '),
                chars));
            EXPECT_EQ(chars, std::vector<std::string>({"yay"}));
        }
        {
            std::string str = "yay,";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser, char_(' '));
            EXPECT_FALSE(chars);
        }
        {
            std::string str = "yay,";
            auto first = str.c_str();
            std::optional<std::vector<std::string>> const chars = prefix_parse(
                first,
                boost::parser::detail::text::null_sentinel,
                parser,
                char_(' '));
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, std::vector<std::string>({"yay"}));
        }
        {
            std::string str = "yay,yay,yay";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }
        {
            std::string str = "yay,yay,yay";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser, char_(' '));
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }
        {
            std::string str = " yay,yay,yay";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }
        {
            std::string str = " yay,yay,yay";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser, char_(' '));
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }
        {
            std::string str = "yay ,yay,yay";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }

        {
            std::string str = "yay ,yay,yay";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser, char_(' '));
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }
        {
            std::string str = "yay, yay,yay";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }
        {
            std::string str = "yay, yay,yay";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser, char_(' '));
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }
        {
            std::string str = "yay,yay ,yay";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }

        {
            std::string str = "yay,yay ,yay";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser, char_(' '));
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }
        {
            std::string str = "yay,yay, yay";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }

        {
            std::string str = "yay,yay, yay";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser, char_(' '));
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }
        {
            std::string str = "yay,yay,yay ";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }

        {
            std::string str = "yay,yay,yay ";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser, char_(' '));
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }
        {
            std::string str = " yay , yay , yay ";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }

        {
            std::string str = " yay , yay , yay ";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser, char_(' '));
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }
        {
            std::string str = "yay, yay, yay";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }

        {
            std::string str = "yay, yay, yay";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser, char_(' '));
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }
    }

    {
        constexpr auto yay = string("yay") % ',';
        constexpr auto aww = string("aww") % ',';
        constexpr auto parser = yay >> ',' >> aww;

        {
            std::string str = "yay, yay, yay, aww, aww";
            auto result = parse(str, parser, ws);
            EXPECT_TRUE(result);
            EXPECT_EQ(
                *result,
                (tuple<std::vector<std::string>, std::vector<std::string>>(
                    std::vector<std::string>({"yay", "yay", "yay"}),
                    std::vector<std::string>({"aww", "aww"}))));
        }
        {
            std::string str = "yay, yay, yay , aww, aww";
            auto result = parse(str, parser, ws);
            EXPECT_TRUE(result);
            EXPECT_EQ(
                *result,
                (tuple<std::vector<std::string>, std::vector<std::string>>(
                    std::vector<std::string>({"yay", "yay", "yay"}),
                    std::vector<std::string>({"aww", "aww"}))));
        }
    }

    {
        constexpr auto yay = string("yay") % ',';
        constexpr auto aww = string("aww") % ',';
        constexpr auto parser = raw[yay] >> ',' >> raw[aww];

        {
            std::string str = "yay, yay, yay, aww, aww";
            auto result = parse(str, parser, ws);
            EXPECT_TRUE(result);
            auto subrange_0 = boost::parser::get(*result, llong<0>{});
            auto subrange_1 = boost::parser::get(*result, llong<1>{});
            EXPECT_EQ(subrange_0.begin(), str.begin());
            EXPECT_EQ(subrange_0.end(), str.begin() + 13);
            EXPECT_EQ(subrange_1.begin(), str.begin() + 15);
            EXPECT_EQ(subrange_1.end(), str.begin() + 23);
        }
        {
            std::string str = "yay, yay, yay , aww, aww";
            auto result = parse(str, parser, ws);
            EXPECT_TRUE(result);
            auto subrange_0 = boost::parser::get(*result, llong<0>{});
            auto subrange_1 = boost::parser::get(*result, llong<1>{});
            EXPECT_EQ(subrange_0.begin(), str.begin());
            EXPECT_EQ(subrange_0.end(), str.begin() + 13);
            EXPECT_EQ(subrange_1.begin(), str.begin() + 16);
            EXPECT_EQ(subrange_1.end(), str.begin() + 24);
        }
    }

    {
        constexpr auto yay = *string("yay");
        constexpr auto aww = *string("aww");
        constexpr auto parser = raw[yay] >> ',' >> raw[aww];

        {
            std::string str = "yay yay yay, aww aww";
            auto result = parse(str, parser, ws);
            EXPECT_TRUE(result);
            auto subrange_0 = boost::parser::get(*result, llong<0>{});
            auto subrange_1 = boost::parser::get(*result, llong<1>{});
            EXPECT_EQ(subrange_0.begin(), str.begin());
            EXPECT_EQ(subrange_0.end(), str.begin() + 11);
            EXPECT_EQ(subrange_1.begin(), str.begin() + 13);
            EXPECT_EQ(subrange_1.end(), str.begin() + 20);
        }
        {
            std::string str = "yay yay yay , aww aww";
            auto result = parse(str, parser, ws);
            EXPECT_TRUE(result);
            auto subrange_0 = boost::parser::get(*result, llong<0>{});
            auto subrange_1 = boost::parser::get(*result, llong<1>{});
            EXPECT_EQ(subrange_0.begin(), str.begin());
            EXPECT_EQ(subrange_0.end(), str.begin() + 11);
            EXPECT_EQ(subrange_1.begin(), str.begin() + 14);
            EXPECT_EQ(subrange_1.end(), str.begin() + 21);
        }
    }
}

TEST(parser, lexeme)
{
    {
        constexpr auto parser = lexeme[string("yay") % ','];

        {
            std::string str = "yay, yay, yay";
            {
                std::vector<std::string> chars;
                EXPECT_FALSE(parse(str, parser, char_(' '), chars));
            }
            {
                std::vector<std::string> chars;
                auto first = str.c_str();
                EXPECT_TRUE(prefix_parse(
                    first,
                    boost::parser::detail::text::null_sentinel,
                    parser,
                    char_(' '),
                    chars));
                EXPECT_EQ(chars, std::vector<std::string>({"yay"}));
            }

            {
                std::string str = "yay, yay, yay";
                std::optional<std::vector<std::string>> const chars =
                    parse(str, parser, char_(' '));
                EXPECT_FALSE(chars);
            }
            {
                std::string str = "yay, yay, yay";
                auto first = str.c_str();
                std::optional<std::vector<std::string>> const chars =
                    prefix_parse(
                        first,
                        boost::parser::detail::text::null_sentinel,
                        parser,
                        char_(' '));
                EXPECT_TRUE(chars);
                EXPECT_EQ(*chars, std::vector<std::string>({"yay"}));
            }
        }
        {
            std::string str = " yay, yay, yay";
            {
                std::vector<std::string> chars;
                EXPECT_FALSE(parse(str, parser, char_(' '), chars));
            }
            {
                std::vector<std::string> chars;
                auto first = str.c_str();
                EXPECT_TRUE(prefix_parse(
                    first,
                    boost::parser::detail::text::null_sentinel,
                    parser,
                    char_(' '),
                    chars));
                EXPECT_EQ(chars, std::vector<std::string>({"yay"}));
            }

            {
                std::string str = " yay, yay, yay";
                std::optional<std::vector<std::string>> const chars =
                    parse(str, parser, char_(' '));
                EXPECT_FALSE(chars);
            }
            {
                std::string str = " yay, yay, yay";
                auto first = str.c_str();
                std::optional<std::vector<std::string>> const chars =
                    prefix_parse(
                        first,
                        boost::parser::detail::text::null_sentinel,
                        parser,
                        char_(' '));
                EXPECT_TRUE(chars);
                EXPECT_EQ(*chars, std::vector<std::string>({"yay"}));
            }
        }
    }

    {
        constexpr auto parser = lexeme[skip[string("yay") % ',']];

        {
            std::string str = "yay, yay, yay";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>({"yay", "yay", "yay"}));

            {
                std::string str = "yay, yay, yay";
                std::optional<std::vector<std::string>> const chars =
                    parse(str, parser, char_(' '));
                EXPECT_TRUE(chars);
                EXPECT_EQ(
                    *chars, std::vector<std::string>({"yay", "yay", "yay"}));
            }
        }
        {
            std::string str = " yay, yay, yay";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>({"yay", "yay", "yay"}));

            {
                std::string str = " yay, yay, yay";
                std::optional<std::vector<std::string>> const chars =
                    parse(str, parser, char_(' '));
                EXPECT_TRUE(chars);
                EXPECT_EQ(
                    *chars, std::vector<std::string>({"yay", "yay", "yay"}));
            }
        }
    }

    {
        auto const parser = string("abc");

        // Follows the parser used in transform_replace().
        auto before = [&](auto & ctx) {};
        auto after = [&](auto & ctx) {};
        auto const search_parser =
            omit[*(char_ - parser)] >>
            -lexeme[eps[before] >> skip[parser] >> eps[after]];

        {
            std::string str = "abc";
            std::optional<std::string> result;
            EXPECT_TRUE(parse(str, search_parser, char_(' '), result));
            EXPECT_EQ(*result, "abc");

            {
                std::string str = "abc";
                auto first = detail::text::detail::begin(str);
                auto last = detail::text::detail::end(str);
                auto const result =
                    prefix_parse(first, last, search_parser, char_(' '));
                static_assert(std::is_same_v<
                              decltype(result),
                              std::optional<std::optional<std::string>> const>);
                EXPECT_TRUE(result);
                EXPECT_EQ(**result, "abc");
            }
        }
        {
            std::string str = " abc";
            std::optional<std::string> result;
            EXPECT_TRUE(parse(str, search_parser, char_(' '), result));
            EXPECT_EQ(*result, "abc");

            {
                std::string str = " abc";
                auto const result = parse(str, search_parser, char_(' '));
                static_assert(std::is_same_v<
                              decltype(result),
                              std::optional<std::optional<std::string>> const>);
                EXPECT_TRUE(result);
                EXPECT_EQ(**result, "abc");
            }
        }
    }

    {
        auto const parser = int_ % ',';

        // Follows the parser used in transform_replace().
        auto before = [&](auto & ctx) {};
        auto after = [&](auto & ctx) {};
        auto const search_parser =
            omit[*(char_ - parser)] >>
            -lexeme[eps[before] >> skip[parser] >> eps[after]];

        {
            std::string str = "1, 2, 4";
            std::optional<std::vector<int>> result;
            EXPECT_TRUE(parse(str, search_parser, char_(' '), result));
            EXPECT_EQ(*result, std::vector<int>({1, 2, 4}));

            {
                std::string str = "1, 2, 4";
                auto const result = parse(str, search_parser, char_(' '));
                static_assert(
                    std::is_same_v<
                        decltype(result),
                        std::optional<std::optional<std::vector<int>>> const>);
                EXPECT_TRUE(result);
                EXPECT_EQ(**result, std::vector<int>({1, 2, 4}));
            }
        }
        {
            std::string str = " 1, 2, 4";
            std::optional<std::vector<int>> result;
            EXPECT_TRUE(parse(str, search_parser, char_(' '), result));
            EXPECT_EQ(*result, std::vector<int>({1, 2, 4}));

            {
                std::string str = " 1, 2, 4";
                auto const result = parse(str, search_parser, char_(' '));
                static_assert(
                    std::is_same_v<
                        decltype(result),
                        std::optional<std::optional<std::vector<int>>> const>);
                EXPECT_TRUE(result);
                EXPECT_EQ(**result, std::vector<int>({1, 2, 4}));
            }
        }
    }
}

TEST(parser, skip)
{
    {
        constexpr auto parser = skip(char_(' '))[string("yay") % ','];

        {
            std::string str = "yay, yay, yay";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }
        {
            std::string str = "yay, yay, yay";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser);
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }
        {
            std::string str = " yay, yay, yay";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }
        {
            std::string str = " yay, yay, yay";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser);
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }
    }
}

TEST(parser, combined_seq_and_or)
{
    {
        constexpr auto parser = char_('a') >> char_('b') >> char_('c') |
                                char_('x') >> char_('y') >> char_('z');
        using tup = tuple<char, char, char>;

        {
            std::string str = "abc";
            tuple<char, char, char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, tup('c', '\0', '\0'));
        }

        {
            std::string str = "abc";
            std::optional<std::string> const chars = parse(str, parser);
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, "abc");
        }

        {
            std::string str = "xyz";
            tup chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, tup('z', '\0', '\0'));
        }
    }

    {
        constexpr auto parser = char_('a') >> string("b") >> char_('c') |
                                char_('x') >> string("y") >> char_('z');
        {
            std::string str = "abc";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, "abc");
        }

        {
            std::string str = "abc";
            std::optional<std::string> const chars = parse(str, parser);
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, "abc");
        }

        {
            std::string str = "xyz";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, "xyz");
        }
    }

    {
        constexpr auto parser = char_('a') >> char_('b') >> char_('c') |
                                char_('x') >> char_('y') >> char_('z');
        using tup = tuple<char, char, char>;

        {
            std::string str = "abc";
            tuple<
                boost::parser::detail::any_copyable,
                boost::parser::detail::any_copyable,
                boost::parser::detail::any_copyable>
                chars;
            EXPECT_TRUE(parse(str, parser, chars));
        }

        {
            std::string str = "xyz";
            tuple<char, char, char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, tup('z', '\0', '\0'));
        }
    }

    {
        constexpr auto parser = !char_('a');
        std::string str = "a";
        EXPECT_FALSE(parse(str, parser));
    }

    {
        constexpr auto parser = &char_('a');
        std::string str = "a";
        EXPECT_FALSE(parse(str, parser));
    }
    {
        constexpr auto parser = &char_('a');
        std::string str = "a";
        auto first = str.c_str();
        EXPECT_TRUE(prefix_parse(
            first, boost::parser::detail::text::null_sentinel, parser));
    }

    {
#if defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Woverloaded-shift-op-parentheses"
#endif
        constexpr auto parser = (char_('a') >> string("b") > char_('c')) |
                                (char_('x') >> string("y") >> char_('z'));
#if defined(__clang__)
#pragma GCC diagnostic pop
#endif
        {
            std::string str = "abc";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, "abc");
        }

        {
            std::string str = "abc";
            std::optional<std::string> const chars = parse(str, parser);
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, "abc");
        }

        {
            std::string str = "xyz";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, "xyz");
        }

        {
            std::string str = "abz";
            std::string chars;
            rethrow_error_handler eh;
            EXPECT_ANY_THROW(parse(str, with_error_handler(parser, eh), chars));
        }

        {
            std::string str = "abz";
            std::string chars;
            EXPECT_FALSE(parse(str, parser, chars));
        }

        {
            std::string str = "abz";
            std::string chars;
            stream_error_handler eh("simple_parser.cpp");
            EXPECT_FALSE(parse(str, with_error_handler(parser, eh), chars));
        }

        {
            std::string str = "ab";
            std::string chars;
            stream_error_handler eh("simple_parser.cpp");
            EXPECT_FALSE(parse(str, with_error_handler(parser, eh), chars));
        }
    }

    {
#if defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Woverloaded-shift-op-parentheses"
#endif
        constexpr auto parser = (char_('a') >> string("b") > char_('c')) |
                                (char_('x') >> string("y") >> char_('z'));
#if defined(__clang__)
#pragma GCC diagnostic pop
#endif
        {
            std::string str = "abc";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, "abc");
        }

        {
            std::string str = "abc";
            std::optional<std::string> const chars = parse(str, parser);
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, "abc");
        }

        {
            std::string str = "xyz";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, chars, trace::on));
            EXPECT_EQ(chars, "xyz");
        }
    }
}

TEST(parser, eol_)
{
    {
        constexpr auto parser = eol;

        {
            std::string str = "y";
            EXPECT_FALSE(parse(str, parser));
        }
        {
            std::string s = (char const *)u8"\u000a";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string s = (char const *)u8"\u000d\u000a";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string s = (char const *)u8"\u000b";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string s = (char const *)u8"\u000c";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string s = (char const *)u8"\u000d";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string s = (char const *)u8"\u0085";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string s = (char const *)u8"\u2028";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string s = (char const *)u8"\u2029";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_TRUE(parse(str, parser));
        }
    }
}

TEST(parser, ws_)
{
    {
        constexpr auto parser = ws;

        {
            std::string str = "y";
            EXPECT_FALSE(parse(str, parser));
        }
        {
            std::string s = (char const *)u8"\u0009";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string s = (char const *)u8"\u000a";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string s = (char const *)u8"\u000d\u000a";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string s = (char const *)u8"\u000b";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string s = (char const *)u8"\u000c";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string s = (char const *)u8"\u000d";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string s = (char const *)u8"\u0085";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string s = (char const *)u8"\u00a0";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string s = (char const *)u8"\u1680";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string s = (char const *)u8"\u2000";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string s = (char const *)u8"\u2001";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string s = (char const *)u8"\u2002";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string s = (char const *)u8"\u2003";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string s = (char const *)u8"\u2004";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string s = (char const *)u8"\u2005";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string s = (char const *)u8"\u2006";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string s = (char const *)u8"\u2007";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string s = (char const *)u8"\u2008";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string s = (char const *)u8"\u2009";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string s = (char const *)u8"\u200a";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string s = (char const *)u8"\u2028";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string s = (char const *)u8"\u2029";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string s = (char const *)u8"\u202F";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string s = (char const *)u8"\u205F";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string s = (char const *)u8"\u3000";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_TRUE(parse(str, parser));
        }
    }
}

TEST(parser, blank_)
{
    {
        constexpr auto parser = blank;
        constexpr auto alt_parser = ws - eol;

        {
            std::string str = "y";
            EXPECT_FALSE(parse(str, parser));
        }
        {
            std::string s = (char const *)u8"\u0009";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_EQ(parse(str, parser), parse(str, alt_parser));
        }
        {
            std::string s = (char const *)u8"\u000a";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_EQ(parse(str, parser), parse(str, alt_parser));
        }
        {
            std::string s = (char const *)u8"\u000d\u000a";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_EQ(parse(str, parser), parse(str, alt_parser));
        }
        {
            std::string s = (char const *)u8"\u000b";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_EQ(parse(str, parser), parse(str, alt_parser));
        }
        {
            std::string s = (char const *)u8"\u000c";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_EQ(parse(str, parser), parse(str, alt_parser));
        }
        {
            std::string s = (char const *)u8"\u000d";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_EQ(parse(str, parser), parse(str, alt_parser));
        }
        {
            std::string s = (char const *)u8"\u0085";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_EQ(parse(str, parser), parse(str, alt_parser));
        }
        {
            std::string s = (char const *)u8"\u00a0";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_EQ(parse(str, parser), parse(str, alt_parser));
        }
        {
            std::string s = (char const *)u8"\u1680";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_EQ(parse(str, parser), parse(str, alt_parser));
        }
        {
            std::string s = (char const *)u8"\u2000";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_EQ(parse(str, parser), parse(str, alt_parser));
        }
        {
            std::string s = (char const *)u8"\u2001";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_EQ(parse(str, parser), parse(str, alt_parser));
        }
        {
            std::string s = (char const *)u8"\u2002";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_EQ(parse(str, parser), parse(str, alt_parser));
        }
        {
            std::string s = (char const *)u8"\u2003";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_EQ(parse(str, parser), parse(str, alt_parser));
        }
        {
            std::string s = (char const *)u8"\u2004";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_EQ(parse(str, parser), parse(str, alt_parser));
        }
        {
            std::string s = (char const *)u8"\u2005";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_EQ(parse(str, parser), parse(str, alt_parser));
        }
        {
            std::string s = (char const *)u8"\u2006";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_EQ(parse(str, parser), parse(str, alt_parser));
        }
        {
            std::string s = (char const *)u8"\u2007";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_EQ(parse(str, parser), parse(str, alt_parser));
        }
        {
            std::string s = (char const *)u8"\u2008";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_EQ(parse(str, parser), parse(str, alt_parser));
        }
        {
            std::string s = (char const *)u8"\u2009";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_EQ(parse(str, parser), parse(str, alt_parser));
        }
        {
            std::string s = (char const *)u8"\u200a";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_EQ(parse(str, parser), parse(str, alt_parser));
        }
        {
            std::string s = (char const *)u8"\u2028";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_EQ(parse(str, parser), parse(str, alt_parser));
        }
        {
            std::string s = (char const *)u8"\u2029";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_EQ(parse(str, parser), parse(str, alt_parser));
        }
        {
            std::string s = (char const *)u8"\u202F";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_EQ(parse(str, parser), parse(str, alt_parser));
        }
        {
            std::string s = (char const *)u8"\u205F";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_EQ(parse(str, parser), parse(str, alt_parser));
        }
        {
            std::string s = (char const *)u8"\u3000";
            auto str = boost::parser::detail::text::as_utf8(s);
            EXPECT_EQ(parse(str, parser), parse(str, alt_parser));
        }
    }
}

TEST(parser, digit_)
{
    constexpr auto parser = +digit;

    std::u32string str = U"a/09:\x0659\x0660\x0669\x066a";
    std::vector<uint32_t> result;
    EXPECT_TRUE(parse(str, parser, char_ - digit, result));
    EXPECT_EQ(result, std::vector<uint32_t>({'0', '9', 0x0660, 0x0669}));
}

TEST(parser, hex_digit_)
{
    constexpr auto parser = +hex_digit;

    std::u32string str = U"a/09:A\uff0f\uff10\uff19\uff1a";
    std::vector<uint32_t> result;
    EXPECT_TRUE(parse(str, parser, char_ - hex_digit, result));
    EXPECT_EQ(
        result,
        std::vector<uint32_t>({'a', '0', '9', 'A', U'\uff10', U'\uff19'}));
}

TEST(parser, control_)
{
    constexpr auto parser = +control;

    std::u32string str = U"\u0001\u001f\u0020\u007e\u007f\u009f\u00a0";
    std::vector<uint32_t> result;
    EXPECT_TRUE(parse(str, parser, char_ - control, result));
    EXPECT_EQ(result, std::vector<uint32_t>({1, 0x001f, 0x007f, 0x009f}));
}

TEST(parser, punct_)
{
    auto parser = +punct;

    std::u32string str = U"\u0020\u0021\u0fda\u0fdb";
    std::vector<uint32_t> result;
    EXPECT_TRUE(parse(str, parser, char_ - punct, result));
    EXPECT_EQ(result, std::vector<uint32_t>({0x21, 0xfda}));
}

TEST(parser, lower_)
{
    auto parser = +lower;

    std::u32string str = U"aA\u016F\u0170";
    std::vector<uint32_t> result;
    EXPECT_TRUE(parse(str, parser, char_ - lower, result));
    EXPECT_EQ(result, std::vector<uint32_t>({'a', 0x16f}));
}

TEST(parser, upper_)
{
    auto parser = +upper;

    std::u32string str = U"aA\u0105\u0106";
    std::vector<uint32_t> result;
    EXPECT_TRUE(parse(str, parser, char_ - upper, result));
    EXPECT_EQ(result, std::vector<uint32_t>({'A', 0x106}));
}

TEST(parser, github_issue_36)
{
    namespace bp = boost::parser;

    auto id = bp::lexeme[+bp::char_(
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz0123456789")];
    auto ids = +id;

    std::string str;
    std::vector<std::string> vec;

    bp::parse("id1", id, bp::ws, str);      // (1)
    EXPECT_EQ(str, "id1");
    str.clear();
    bp::parse("id1 id2", ids, bp::ws, vec); // (2)
    EXPECT_EQ(vec, std::vector<std::string>({"id1", "id2"}));

    // Intentionally ill-formed.
    // bp::parse("i1 i2", ids, bp::ws, str);   // (3)
}

namespace issue_50 {
    struct X
    {
        char a;
        int b;

        bool operator<(X rhs) const { return a < rhs.a; }
    };

    struct Y
    {
        std::vector<X> x;
        int c;
    };

    struct Y2
    {
        std::set<X> x;
        int c;
    };

    static_assert(
        boost::parser::detail::is_struct_compatible<
            Y,
            boost::parser::
                tuple<std::vector<boost::parser::tuple<char, int>>, int>>());

    static_assert(
        boost::parser::detail::is_struct_compatible<
            Y2,
            boost::parser::
                tuple<std::vector<boost::parser::tuple<char, int>>, int>>());
}

TEST(parser, github_issue_50)
{
    using namespace issue_50;

    namespace bp = boost::parser;

    {
        auto parse_x = bp::char_ >> bp::int_;
        auto parse_y = +parse_x >> bp::int_;

        Y y;
        auto b = bp::parse("d 3 4", parse_y, bp::ws, y);
        EXPECT_TRUE(b);

        EXPECT_EQ(y.x[0].a, 'd');
        EXPECT_EQ(y.x[0].b, 3);
        EXPECT_EQ(y.c, 4);
    }

    {
        auto parse_x = bp::char_ >> bp::int_;
        auto parse_y = +parse_x >> bp::int_;

        Y2 y;
        auto b = bp::parse("d 3 4", parse_y, bp::ws, y);
        EXPECT_TRUE(b);

        EXPECT_EQ(y.x.begin()->a, 'd');
        EXPECT_EQ(y.x.begin()->b, 3);
        EXPECT_EQ(y.c, 4);
    }
}

namespace issue_52 {
    struct X
    {
        char a;
        int b;
    };

    struct Y
    {
        std::vector<X> x;
        int c;
    };

    struct Z
    {
        std::vector<Y> y;
        int d;
    };

    struct W
    {
        std::vector<Z> z;
        int e;
    };
}

TEST(parser, github_issue_52)
{
    using namespace issue_52;

    namespace bp = boost::parser;
    auto parse_x = bp::char_ >> bp::int_;
    auto parse_y = +parse_x >> bp::int_;
    auto parse_z = +parse_y >> bp::char_;
    auto parse_w = +parse_z >> bp::int_;

    {
        Z z;
        auto b = bp::parse("d 2 3 c", parse_z, bp::ws, z);
        EXPECT_TRUE(b);

        EXPECT_EQ(z.y[0].x[0].a, 'd');
        EXPECT_EQ(z.y[0].x[0].b, 2);
        EXPECT_EQ(z.y[0].c, 3);
        EXPECT_EQ(z.d, 'c');
    }
    {
        W w;
        auto b = bp::parse("d 2 3 c 4", parse_w, bp::ws, w);
        EXPECT_TRUE(b);

        EXPECT_EQ(w.z[0].y[0].x[0].a, 'd');
        EXPECT_EQ(w.z[0].y[0].x[0].b, 2);
        EXPECT_EQ(w.z[0].y[0].c, 3);
        EXPECT_EQ(w.z[0].d, 'c');
        EXPECT_EQ(w.e, 4);
    }
}

namespace issue_90 { namespace parser {
    const auto string =
        '"' >> boost::parser::lexeme[*(boost::parser::char_ - '"')] > '"';
    const auto specifier = string > ':' > string;
}}

TEST(parser, github_issue_90)
{
    using namespace issue_90;
    namespace bp = boost::parser;

    std::string input = R"( "dd" : "2" )";
    std::pair<std::string, std::string> result;

    auto b = bp::parse(input, parser::specifier, bp::ws, result);
    EXPECT_TRUE(b);
    EXPECT_EQ(result.first, "dd");
    EXPECT_EQ(result.second, "2");
}

TEST(parser, no_need_for_sprit_2_hold_directive)
{
    namespace bp = boost::parser;

    std::vector<int> v;
    auto result = bp::parse(
        "1 2",
        bp::repeat(3)[bp::int_] | repeat(2)[bp::int_] >> bp::attr(0),
        bp::ws,
        v,
        bp::trace::on);
    EXPECT_TRUE(result);

    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v, std::vector<int>({1, 2, 0}));
}

TEST(parser, raw_doc_example)
{
    namespace bp = boost::parser;
    auto int_parser = bp::int_ % ',';            // ATTR(int_parser) is std::vector<int>
    auto subrange_parser = bp::raw[int_parser];  // ATTR(subrange_parser) is a subrange

    // Parse using int_parser, generating integers.
    auto ints = bp::parse("1, 2, 3, 4", int_parser, bp::ws);
    assert(ints);
    assert(*ints == std::vector<int>({1, 2, 3, 4}));

    // Parse again using int_parser, but this time generating only the
    // subrange matched by int_parser.  (prefix_parse() allows matches that
    // don't consume the entire input.)
    auto const str = std::string("1, 2, 3, 4, a, b, c");
    auto first = str.begin();
    auto range = bp::prefix_parse(first, str.end(), subrange_parser, bp::ws);
    assert(range);
    assert(range->begin() == str.begin());
    assert(range->end() == str.begin() + 10);

    static_assert(
        std::is_same_v<
            decltype(range),
            std::optional<BOOST_PARSER_SUBRANGE<std::string::const_iterator>>>);

#if defined(__cpp_char8_t)
    auto const u8str = std::u8string(u8"1, 2, 3, 4, a, b, c");
    auto u8first = u8str.begin();
    auto u8range = bp::prefix_parse(u8first, u8str.end(), subrange_parser, bp::ws);
    assert(u8range);
    assert(u8range->begin().base() == u8str.begin());
    assert(u8range->end().base() == u8str.begin() + 10);
#endif
}


#if defined(__cpp_lib_concepts)
TEST(parser, string_view_doc_example)
{
    namespace bp = boost::parser;
    auto int_parser = bp::int_ % ',';              // ATTR(int_parser) is std::vector<int>
    auto sv_parser = bp::string_view[int_parser];  // ATTR(subrange_parser) is a string_view

    auto const str = std::string("1, 2, 3, 4, a, b, c");
    auto first = str.begin();
    auto sv1 = bp::prefix_parse(first, str.end(), sv_parser, bp::ws);
    assert(sv1);
    assert(*sv1 == str.substr(0, 10));

    static_assert(std::is_same_v<decltype(sv1), std::optional<std::string_view>>);

    auto sv2 = bp::parse("1, 2, 3, 4" | bp::as_utf32, sv_parser, bp::ws);
    assert(sv2);
    assert(*sv2 == "1, 2, 3, 4");

    static_assert(std::is_same_v<decltype(sv2), std::optional<std::string_view>>);
}
#endif

TEST(parser, variant_compat_example)
{
    struct key_value
    {
        int key;
        double value;
    };

    namespace bp = boost::parser;
    std::variant<key_value, double> kv_or_d;
    key_value kv;
    bp::parse("42 13.0", bp::int_ >> bp::double_, kv);      // Ok.
#if 0
    bp::parse("42 13.0", bp::int_ >> bp::double_, kv_or_d); // Error: ill-formed!
#endif
}


namespace rule_construction_example {
    struct type_t
    {
        type_t() = default;
        explicit type_t(double x) : x_(x) {}
        // etc.

        double x_;
    };

    namespace bp = boost::parser;

    auto doubles_to_type = [](auto & ctx) {
        _val(ctx) = type_t(
            bp::get(_attr(ctx), bp::llong<0>{}) *
            bp::get(_attr(ctx), bp::llong<1>{}));
    };

    bp::rule<struct type_tag, type_t> type = "type";
    auto const type_def = (bp::double_ >> bp::double_)[doubles_to_type];
    BOOST_PARSER_DEFINE_RULES(type);
}

TEST(parser, rule_example)
{
    namespace bp = boost::parser;
    using namespace rule_construction_example;
    EXPECT_TRUE(bp::parse("3 4", type, bp::ws));
}
