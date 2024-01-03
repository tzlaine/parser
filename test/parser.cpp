/**
 *   Copyright (C) 2018 T. Zachary Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See
 *   accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt)
 */

#include <boost/parser/parser.hpp>

#include <gtest/gtest.h>

#include <any>


using namespace boost::parser;


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
        char c = '\0';
        EXPECT_TRUE(parse(str, ascii::blank, c));
        EXPECT_EQ(c, ' ');
        EXPECT_FALSE(parse(str, ascii::lower));
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
        EXPECT_EQ(get(result, 0_c), 'a');
        EXPECT_EQ(get(result, 1_c), 'b');
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
        EXPECT_EQ(get(result, 0_c), 'a');
        EXPECT_EQ(get(result, 1_c), 'b');
        EXPECT_EQ(get(result, 2_c), 'c');
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
        EXPECT_EQ(i, 3);
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
            EXPECT_EQ(r.begin(), str.begin());
            EXPECT_EQ(r.end(), str.begin());
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
                EXPECT_EQ(chars, std::vector<std::string>({"yay"}));
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
            EXPECT_EQ(chars, tup('a', 'b', 'c'));
        }

        {
            std::string str = "abc";
            std::optional<tuple<char, char, char>> const chars =
                parse(str, parser);
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, tup('a', 'b', 'c'));
        }

        {
            std::string str = "xyz";
            tup chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, tup('x', 'y', 'z'));
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
            EXPECT_EQ(chars, tup('x', 'y', 'z'));
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

TEST(parser, github_issue_36)
{
    namespace bp = boost::parser;

    auto id = bp::lexeme[+(bp::ascii::alnum | bp::char_('_'))];
    auto ids = +id;

    std::string str;
    std::vector<std::string> vec;

    bp::parse("id1", id, bp::ascii::space, str);      // (1)
    EXPECT_EQ(str, "id1");
    str.clear();
    bp::parse("id1 id2", ids, bp::ascii::space, vec); // (2)
    EXPECT_EQ(vec, std::vector<std::string>({"id1", "id2"}));

    // Intentionally ill-formed.
    // bp::parse("i1 i2", ids, bp::ascii::space, str);   // (3)
}
