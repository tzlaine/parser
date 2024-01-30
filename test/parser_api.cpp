/**
 *   Copyright (C) 2018 T. Zachary Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See
 *   accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt)
 */
#include <boost/parser/parser.hpp>
#include <boost/parser/transcode_view.hpp>

#include "ill_formed.hpp"

#include <gtest/gtest.h>

#include <any>
#include <deque>


using namespace boost::parser;


constexpr callback_rule<struct callback_char_rule_tag, char>
    callback_char_rule = "callback_char_rule";
constexpr auto callback_char_rule_def = char_;
BOOST_PARSER_DEFINE_RULES(callback_char_rule);

struct callback_char_rule_tag
{};

TEST(parser, full_parse_api)
{
    std::string const str = "a";

    // attr out param, iter/sent
    {
        char out = 0;
        auto first = str.c_str();
        EXPECT_TRUE(prefix_parse(
            first, boost::parser::detail::text::null_sentinel, char_, out));
        first = str.c_str();
        EXPECT_EQ(out, 'a');
        out = 0;
        first = str.c_str();
        EXPECT_TRUE(!prefix_parse(
            first,
            boost::parser::detail::text::null_sentinel,
            char_('b'),
            out));
        EXPECT_EQ(out, 0);
    }
    // attr out param, range
    {
        char out = 0;
        EXPECT_TRUE(parse(str, char_, out));
        EXPECT_EQ(out, 'a');
        out = 0;
        EXPECT_FALSE(parse(str, char_('b'), out));
        EXPECT_EQ(out, 0);
    }
    // attr out param, pointer-as-range
    {
        char out = 0;
        EXPECT_TRUE(parse(str.c_str(), char_, out));
        EXPECT_EQ(out, 'a');
        out = 0;
        EXPECT_FALSE(parse(str.c_str(), char_('b'), out));
        EXPECT_EQ(out, 0);
    }

    // returned attr, iter/sent
    {
        auto first = str.c_str();
        EXPECT_TRUE(prefix_parse(
            first, boost::parser::detail::text::null_sentinel, char_));
        first = str.c_str();
        EXPECT_EQ(
            *prefix_parse(
                first, boost::parser::detail::text::null_sentinel, char_),
            'a');
        first = str.c_str();
        EXPECT_FALSE(prefix_parse(
            first, boost::parser::detail::text::null_sentinel, char_('b')));
    }
    // returned attr, range
    {
        EXPECT_TRUE(parse(str, char_));
        EXPECT_EQ(*parse(str, char_), 'a');
        EXPECT_FALSE(parse(str, char_('b')));
    }
    // returned attr, pointer-as-range
    {
        EXPECT_TRUE(parse(str.c_str(), char_));
        EXPECT_EQ(*parse(str.c_str(), char_), 'a');
        EXPECT_FALSE(parse(str.c_str(), char_('b')));
    }
    // returned attr, UTF-16
    {
        EXPECT_TRUE(parse(u"a", char_));
        auto const result = *parse(u"a", char_);
        EXPECT_EQ(uint16_t(result), uint16_t('a'));
        EXPECT_FALSE(parse(u"a", char_('b')));
    }

    // attr out param, using skipper, iter/sent
    {
        char out = 0;
        auto first = str.c_str();
        EXPECT_TRUE(prefix_parse(
            first,
            boost::parser::detail::text::null_sentinel,
            char_,
            ws,
            out));
        first = str.c_str();
        EXPECT_EQ(out, 'a');
        out = 0;
        first = str.c_str();
        EXPECT_FALSE(prefix_parse(
            first,
            boost::parser::detail::text::null_sentinel,
            char_('b'),
            ws,
            out));
        EXPECT_EQ(out, 0);
    }
    // attr out param, using skipper, range
    {
        char out = 0;
        EXPECT_TRUE(parse(str, char_, ws, out));
        EXPECT_EQ(out, 'a');
        out = 0;
        EXPECT_FALSE(parse(str, char_('b'), ws, out));
        EXPECT_EQ(out, 0);
    }
    // attr out param, using skipper, pointer-as-range
    {
        char out = 0;
        EXPECT_TRUE(parse(str.c_str(), char_, ws, out));
        EXPECT_EQ(out, 'a');
        out = 0;
        EXPECT_FALSE(parse(str.c_str(), char_('b'), ws, out));
        EXPECT_EQ(out, 0);
    }

    // returned attr, using skipper, iter/sent
    {
        auto first = str.c_str();
        EXPECT_TRUE(prefix_parse(
            first, boost::parser::detail::text::null_sentinel, char_, ws));
        first = str.c_str();
        EXPECT_EQ(
            *prefix_parse(
                first,
                boost::parser::detail::text::null_sentinel,
                char_,
                ws),
            'a');
        first = str.c_str();
        EXPECT_TRUE(!prefix_parse(
            first,
            boost::parser::detail::text::null_sentinel,
            char_('b'),
            ws));
    }
    // returned attr, using skipper, range
    {
        EXPECT_TRUE(parse(str, char_, ws));
        EXPECT_EQ(*parse(str, char_, ws), 'a');
        EXPECT_FALSE(parse(str, char_('b'), ws));
    }
    // returned attr, using skipper, pointer-as-range
    {
        EXPECT_TRUE(parse(str.c_str(), char_, ws));
        EXPECT_EQ(*parse(str.c_str(), char_, ws), 'a');
        EXPECT_FALSE(parse(str.c_str(), char_('b'), ws));
    }

    // callback, iter/sent
    {
        char out = 0;
        auto callbacks = [&out](auto tag, auto x) { out = x; };
        auto first = str.c_str();
        EXPECT_TRUE(callback_prefix_parse(
            first,
            boost::parser::detail::text::null_sentinel,
            callback_char_rule,
            callbacks));
        first = str.c_str();
        EXPECT_EQ(out, 'a');
    }
    // callback, range
    {
        char out = 0;
        auto callbacks = [&out](auto tag, auto x) { out = x; };
        EXPECT_TRUE(callback_parse(str, callback_char_rule, callbacks));
        EXPECT_EQ(out, 'a');
    }
    // callback, pointer-as-range
    {
        char out = 0;
        auto callbacks = [&out](auto tag, auto x) { out = x; };
        EXPECT_TRUE(callback_parse(str.c_str(), callback_char_rule, callbacks));
        EXPECT_EQ(out, 'a');
    }

    // callback, using skipper, iter/sent
    {
        char out = 0;
        auto callbacks = [&out](auto tag, auto x) { out = x; };
        auto first = str.c_str();
        EXPECT_TRUE(callback_prefix_parse(
            first,
            boost::parser::detail::text::null_sentinel,
            callback_char_rule,
            ws,
            callbacks));
        first = str.c_str();
        EXPECT_EQ(out, 'a');
    }
    // callback, using skipper, range
    {
        char out = 0;
        auto callbacks = [&out](auto tag, auto x) { out = x; };
        EXPECT_TRUE(
            callback_parse(str, callback_char_rule, ws, callbacks));
        EXPECT_EQ(out, 'a');
    }
    // callback, using skipper, pointer-as-range
    {
        char out = 0;
        auto callbacks = [&out](auto tag, auto x) { out = x; };
        EXPECT_TRUE(callback_parse(
            str.c_str(), callback_char_rule, ws, callbacks));
        EXPECT_EQ(out, 'a');
    }
}

TEST(parser, basic)
{
    constexpr auto parser_1 = char_ >> char_;
    constexpr auto parser_2 = char_ >> char_ >> char_;
    constexpr auto parser_3 = char_ | char_;
    constexpr auto parser_4 = char_('a') | char_('b') | char_('c');
    constexpr auto parser_5 = char_('a') | char_('b') | eps;

    {
        char const * str = "a";
        EXPECT_TRUE(parse(str, char_));
        EXPECT_FALSE(parse(str, char_('b')));
    }
    {
        char const * str = "a";
        char c = '\0';
        EXPECT_TRUE(parse(str, char_, c));
        EXPECT_EQ(c, 'a');
        EXPECT_FALSE(parse(str, char_('b')));
    }
    {
        char const * str = "b";
        char c = '\0';
        EXPECT_TRUE(parse(str, char_("ab"), c));
        EXPECT_EQ(c, 'b');
        EXPECT_FALSE(parse(str, char_("cd")));
    }
    {
        char const * str = "b";
        char c = '\0';
        std::string const pattern_1 = "ab";
        std::string const pattern_2 = "cd";
        EXPECT_TRUE(parse(str, char_(pattern_1), c));
        EXPECT_EQ(c, 'b');
        EXPECT_FALSE(parse(str, char_(pattern_2)));
    }
    {
        char const * str = "b";
        char c = '\0';
        EXPECT_TRUE(parse(str, char_('a', 'b'), c));
        EXPECT_EQ(c, 'b');
        EXPECT_FALSE(parse(str, char_('c', 'd')));
    }
    {
        char const * str = " ";
        EXPECT_TRUE(parse(str, blank));
        EXPECT_FALSE(parse(str, lower));
    }
    {
        char const * str = "ab";
        EXPECT_FALSE(parse(str, char_));
        EXPECT_TRUE(parse(str, parser_1));
        EXPECT_FALSE(parse(str, parser_2));
    }
    {
        std::string str = "ab";
        auto first = str.c_str();
        EXPECT_TRUE(prefix_parse(
            first, boost::parser::detail::text::null_sentinel, char_));
        first = str.c_str();
        EXPECT_TRUE(prefix_parse(
            first, boost::parser::detail::text::null_sentinel, parser_1));
        first = str.c_str();
        EXPECT_FALSE(parse(str, parser_2));
    }
    {
        char const * str = "ab";
        tuple<char, char> result;
        EXPECT_TRUE(parse(str, parser_1, result));
        using namespace boost::parser::literals;
        EXPECT_EQ(get(result, 0_c), 'b');
        EXPECT_EQ(get(result, 1_c), '\0');
    }
    {
        char const * str = "abc";
        EXPECT_FALSE(parse(str, parser_1));
        EXPECT_TRUE(parse(str, parser_2));
    }
    {
        std::string str = "abc";
        auto first = str.c_str();
        EXPECT_TRUE(prefix_parse(
            first, boost::parser::detail::text::null_sentinel, parser_1));
        first = str.c_str();
        EXPECT_TRUE(prefix_parse(
            first, boost::parser::detail::text::null_sentinel, parser_2));
    }
    {
        char const * str = "abc";
        tuple<char, char, char> result;
        EXPECT_TRUE(parse(str, parser_2, result));
        using namespace boost::parser::literals;
        EXPECT_EQ(get(result, 0_c), 'c');
        EXPECT_EQ(get(result, 1_c), '\0');
        EXPECT_EQ(get(result, 2_c), '\0');
    }
    {
        char const * str = "a";
        EXPECT_TRUE(parse(str, parser_3));
        EXPECT_TRUE(parse(str, parser_4));
    }
    {
        char const * str = "a";
        char c = '\0';
        EXPECT_TRUE(parse(str, parser_3, c));
        EXPECT_EQ(c, 'a');
    }
    {
        char const * str = "a";
        char c = '\0';
        EXPECT_TRUE(parse(str, parser_4, c));
        EXPECT_EQ(c, 'a');
    }
    {
        char const * str = "z";
        EXPECT_TRUE(parse(str, parser_3));
        EXPECT_FALSE(parse(str, parser_4));
    }
    {
        char const * str = "a";
        EXPECT_TRUE(parse(str, parser_5));
    }
    {
        char const * str = "z";
        EXPECT_FALSE(parse(str, parser_5));
    }
    {
        std::string str = "z";
        auto first = str.c_str();
        EXPECT_TRUE(prefix_parse(
            first, boost::parser::detail::text::null_sentinel, parser_5));
    }
    {
        char const * str = "a";
        std::optional<char> c;
        EXPECT_TRUE(parse(str, parser_5, c));
        EXPECT_EQ(c, 'a');
    }
    {
        char const * str = "z";
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

TEST(parser, int_)
{
    {
        char const * str = "-42";
        short i = 0;
        EXPECT_TRUE(parse(str, short_, i));
        EXPECT_EQ(i, -42);
    }
    {
        char const * str = "42";
        short i = 0;
        EXPECT_TRUE(parse(str, short_, i));
        EXPECT_EQ(i, 42);
    }
    {
        char const * str = "-2000000000";
        int i = 0;
        EXPECT_TRUE(parse(str, int_, i));
        EXPECT_EQ(i, -2000000000);
    }
    {
        char const * str = "2000000000";
        int i = 0;
        EXPECT_TRUE(parse(str, int_, i));
        EXPECT_EQ(i, 2000000000);
    }
    {
        char const * str = "-2000000000";
        long i = 0;
        EXPECT_TRUE(parse(str, long_, i));
        EXPECT_EQ(i, -2000000000);
    }
    {
        char const * str = "2000000000";
        long i = 0;
        EXPECT_TRUE(parse(str, long_, i));
        EXPECT_EQ(i, 2000000000);
    }
    {
        char const * str = "-4000000000";
        long long i = 0;
        EXPECT_TRUE(parse(str, long_long, i));
        EXPECT_EQ(i, -4000000000LL);
    }
    {
        char const * str = "4000000000";
        long long i = 0;
        EXPECT_TRUE(parse(str, long_long, i));
        EXPECT_EQ(i, 4000000000LL);
    }
}

TEST(parser, uint_)
{
    {
        char const * str = "10011";
        unsigned int i = 0;
        EXPECT_TRUE(parse(str, bin, i));
        EXPECT_EQ(i, 19);
    }
    {
        char const * str = "107";
        unsigned int i = 0;
        EXPECT_TRUE(parse(str, oct, i));
        EXPECT_EQ(i, 71);
    }
    {
        char const * str = "beef";
        unsigned int i = 0;
        EXPECT_TRUE(parse(str, hex, i));
        EXPECT_EQ(i, 48879);
    }

    {
        char const * str = "42";
        unsigned int i = 0;
        EXPECT_TRUE(parse(str, ushort_, i));
        EXPECT_EQ(i, 42);
    }
    {
        char const * str = "-42";
        unsigned int i = 3;
        EXPECT_FALSE(parse(str, uint_, i));
        EXPECT_EQ(i, 0);
    }
    {
        char const * str = "42";
        unsigned int i = 0;
        EXPECT_TRUE(parse(str, uint_, i));
        EXPECT_EQ(i, 42);
    }
    {
        char const * str = "42";
        unsigned long i = 0;
        EXPECT_TRUE(parse(str, ulong_, i));
        EXPECT_EQ(i, 42);
    }
    {
        char const * str = "42";
        unsigned long long i = 0;
        EXPECT_TRUE(parse(str, ulong_long, i));
        EXPECT_EQ(i, 42);
    }
}

TEST(parser, bool_)
{
    {
        char const * str = "";
        bool b = false;
        EXPECT_FALSE(parse(str, bool_, b));
    }
    {
        char const * str = "true";
        bool b = false;
        EXPECT_TRUE(parse(str, bool_, b));
        EXPECT_EQ(b, true);
    }
    {
        char const * str = "false ";
        bool b = true;
        EXPECT_FALSE(parse(str, bool_, b));
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
        char const * str = "true ";
        auto r = boost::parser::as_utf32(str);
        bool b = false;
        auto first = r.begin();
        auto const last = r.end();
        EXPECT_TRUE(prefix_parse(first, last, bool_, b));
        EXPECT_EQ(b, true);
    }
    {
        char const * str = "false";
        auto r = boost::parser::as_utf32(str);
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
            char const * str = "";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>());
        }
        {
            char const * str = "a";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'a'}));
        }
        {
            char const * str = "ba";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'b', 'a'}));
        }
    }

    {
        constexpr auto parser = *char_('b');
        {
            char const * str = "";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>());
        }
        {
            char const * str = "b";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'b'}));
        }
        {
            char const * str = "bb";
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
            char const * str = "";
            std::vector<char> chars;
            EXPECT_FALSE(parse(str, parser, chars));
        }
        {
            char const * str = "a";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'a'}));
        }
        {
            char const * str = "ba";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'b', 'a'}));
        }
    }

    {
        constexpr auto parser = +char_('b');

        {
            char const * str = "";
            std::vector<char> chars;
            EXPECT_FALSE(parse(str, parser, chars));
        }
        {
            char const * str = "b";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'b'}));
        }
        {
            char const * str = "bb";
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
            char const * str = "";
            std::vector<char> chars;
            EXPECT_FALSE(parse(str, parser, chars));
        }
        {
            char const * str = "b";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'b'}));
        }
        {
            char const * str = "bb";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'b', 'b'}));
        }
    }

    {
        constexpr auto parser = **char_('z');

        {
            char const * str = "";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>());
        }
        {
            char const * str = "z";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'z'}));
        }
        {
            char const * str = "zz";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'z', 'z'}));
        }
    }

    {
        constexpr auto parser = +*char_('z');

        {
            char const * str = "";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>());
        }
        {
            char const * str = "z";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'z'}));
        }
        {
            char const * str = "zz";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'z', 'z'}));
        }
    }

    {
        constexpr auto parser = *+char_('z');

        {
            char const * str = "";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>());
        }
        {
            char const * str = "z";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'z'}));
        }
        {
            char const * str = "zz";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'z', 'z'}));
        }
    }
}

TEST(parser, action)
{
    {{char const * str = "";
    std::stringstream ss;
    auto action = [&ss](auto & context) { ss << _attr(context); };
    auto parser = *char_('b')[action];
    EXPECT_TRUE(parse(str, parser));
    EXPECT_EQ(ss.str(), "");
}
{
    char const * str = "b";
    std::stringstream ss;
    auto action = [&ss](auto & context) { ss << _attr(context); };
    auto parser = *char_('b')[action];
    EXPECT_TRUE(parse(str, parser));
    EXPECT_EQ(ss.str(), "b");
}
{
    char const * str = "bb";
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
        char const * str = "";
        std::stringstream ss;
        auto action = [&ss](auto & context) { ss << _attr(context); };
        auto parser = +char_('b')[action];
        EXPECT_FALSE(parse(str, parser));
        EXPECT_EQ(ss.str(), "");
    }
    {
        char const * str = "b";
        std::stringstream ss;
        auto action = [&ss](auto & context) { ss << _attr(context); };
        auto parser = +char_('b')[action];
        EXPECT_TRUE(parse(str, parser));
        EXPECT_EQ(ss.str(), "b");
    }
    {
        char const * str = "bb";
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
            char const * str = "";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, "");
        }
        {
            char const * str = "z";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, "z");
        }
        {
            char const * str = "zz";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, "zz");
        }
    }

    {
        constexpr auto parser = *char_('z');

        {
            char const * str = "";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>());
        }
        {
            char const * str = "z";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'z'}));
        }
        {
            char const * str = "zz";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'z', 'z'}));
        }
    }

    {
        constexpr auto parser = *string("zs");

        {
            char const * str = "";
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
            char const * str = "zs";
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
            char const * str = "zszs";
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
            char const * str = "";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<std::string>{});
        }
        {
            char const * str = "z";
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
            char const * str = "zs";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<std::string>({"zs"}));
        }
        {
            char const * str = "zszs";
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
            char const * str = "";
            EXPECT_TRUE(parse(str, parser));
        }
        {
            char const * str = "z";
            EXPECT_TRUE(parse(str, parser));
        }
        {
            char const * str = "zz";
            EXPECT_TRUE(parse(str, parser));
        }
        {
            char const * str = "";
            EXPECT_TRUE(parse(str, parser));
        }
        {
            char const * str = "z";
            EXPECT_TRUE(parse(str, parser));
        }
        {
            char const * str = "zz";
            EXPECT_TRUE(parse(str, parser));
        }
    }

    {
        constexpr auto parser = omit[*string("zs")];

        {
            char const * str = "";
            EXPECT_TRUE(parse(str, parser));
        }
        {
            char const * str = "z";
            EXPECT_FALSE(parse(str, parser));
        }
        {
            std::string str = "z";
            auto first = str.c_str();
            EXPECT_TRUE(prefix_parse(
                first, boost::parser::detail::text::null_sentinel, parser));
        }
        {
            char const * str = "zs";
            EXPECT_TRUE(parse(str, parser));
        }
        {
            char const * str = "zszs";
            EXPECT_TRUE(parse(str, parser));
        }
    }
}

TEST(parser, repeat)
{
    {
        constexpr auto parser = repeat(2, 3)[string("zs")];

        {
            char const * str = "";
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
            char const * str = "z";
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
            char const * str = "zs";
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
            char const * str = "zszs";
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
        using range_t = BOOST_PARSER_SUBRANGE<std::string::const_iterator>;

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
            char const * str = "";
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
            char const * str = "z";
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
            char const * str = ",";
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
            char const * str = ",yay";
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
            char const * str = "yay";
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
            char const * str = "yay,yay,yay";
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
            char const * str = "";
            std::vector<std::string> chars;
            EXPECT_FALSE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>{});
        }

        {
            char const * str = "";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser, char_(' '));
            EXPECT_FALSE(chars);
        }
        {
            char const * str = "z";
            std::vector<std::string> chars;
            EXPECT_FALSE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>{});
        }
        {
            char const * str = "z";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser, char_(' '));
            EXPECT_FALSE(chars);
        }
        {
            char const * str = ",";
            std::vector<std::string> chars;
            EXPECT_FALSE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>{});
        }
        {
            char const * str = ",";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser, char_(' '));
            EXPECT_FALSE(chars);
        }
        {
            char const * str = " ,yay";
            std::vector<std::string> chars;
            EXPECT_FALSE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>{});
        }
        {
            char const * str = " ,yay";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser, char_(' '));
            EXPECT_FALSE(chars);
        }
        {
            char const * str = ", yay";
            std::vector<std::string> chars;
            EXPECT_FALSE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>{});
        }
        {
            char const * str = ", yay";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser, char_(' '));
            EXPECT_FALSE(chars);
        }
        {
            char const * str = ",yay ";
            std::vector<std::string> chars;
            EXPECT_FALSE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>{});
        }
        {
            char const * str = ",yay ";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser, char_(' '));
            EXPECT_FALSE(chars);
        }

        {
            char const * str = " , yay ";
            std::vector<std::string> chars;
            EXPECT_FALSE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>{});
        }
        {
            char const * str = " , yay ";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser, char_(' '));
            EXPECT_FALSE(chars);
        }
        {
            char const * str = "yay";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>({"yay"}));
        }
        {
            char const * str = "yay";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser, char_(' '));
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, std::vector<std::string>({"yay"}));
        }
        {
            char const * str = "yayyay";
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
            char const * str = "yayyay";
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
            char const * str = "yay,";
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
            char const * str = "yay,";
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
            char const * str = "yay,yay,yay";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }
        {
            char const * str = "yay,yay,yay";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser, char_(' '));
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }
        {
            char const * str = " yay,yay,yay";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }
        {
            char const * str = " yay,yay,yay";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser, char_(' '));
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }
        {
            char const * str = "yay ,yay,yay";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }

        {
            char const * str = "yay ,yay,yay";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser, char_(' '));
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }
        {
            char const * str = "yay, yay,yay";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }
        {
            char const * str = "yay, yay,yay";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser, char_(' '));
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }
        {
            char const * str = "yay,yay ,yay";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }

        {
            char const * str = "yay,yay ,yay";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser, char_(' '));
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }
        {
            char const * str = "yay,yay, yay";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }

        {
            char const * str = "yay,yay, yay";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser, char_(' '));
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }
        {
            char const * str = "yay,yay,yay ";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }

        {
            char const * str = "yay,yay,yay ";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser, char_(' '));
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }
        {
            char const * str = " yay , yay , yay ";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }

        {
            char const * str = " yay , yay , yay ";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser, char_(' '));
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }
        {
            char const * str = "yay, yay, yay";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }

        {
            char const * str = "yay, yay, yay";
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
                char const * str = "yay, yay, yay";
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
                char const * str = " yay, yay, yay";
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
            char const * str = "yay, yay, yay";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>({"yay", "yay", "yay"}));

            {
                char const * str = "yay, yay, yay";
                std::optional<std::vector<std::string>> const chars =
                    parse(str, parser, char_(' '));
                EXPECT_TRUE(chars);
                EXPECT_EQ(
                    *chars, std::vector<std::string>({"yay", "yay", "yay"}));
            }
        }
        {
            char const * str = " yay, yay, yay";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, std::vector<std::string>({"yay", "yay", "yay"}));

            {
                char const * str = " yay, yay, yay";
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
            char const * str = "yay, yay, yay";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }
        {
            char const * str = "yay, yay, yay";
            std::optional<std::vector<std::string>> const chars =
                parse(str, parser);
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }
        {
            char const * str = " yay, yay, yay";
            std::vector<std::string> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<std::string>({"yay", "yay", "yay"}));
        }
        {
            char const * str = " yay, yay, yay";
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
            char const * str = "abc";
            tuple<char, char, char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, tup('c', '\0', '\0'));
        }

        {
            char const * str = "abc";
            std::optional<std::string> const chars = parse(str, parser);
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, "abc");
        }

        {
            char const * str = "xyz";
            tuple<char, char, char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, tup('z', '\0', '\0'));
        }
    }

    {
        constexpr auto parser = char_('a') >> string("b") >> char_('c') |
                                char_('x') >> string("y") >> char_('z');
        {
            char const * str = "abc";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, "abc");
        }

        {
            char const * str = "abc";
            std::optional<std::string> const chars = parse(str, parser);
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, "abc");
        }

        {
            char const * str = "xyz";
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
            char const * str = "abc";
            tuple<
                boost::parser::detail::any_copyable,
                boost::parser::detail::any_copyable,
                boost::parser::detail::any_copyable>
                chars;
            EXPECT_TRUE(parse(str, parser, chars));
        }

        {
            char const * str = "xyz";
            tuple<char, char, char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, tup('z', '\0', '\0'));
        }
    }

    {
        constexpr auto parser = !char_('a');
        char const * str = "a";
        EXPECT_FALSE(parse(str, parser));
    }

    {
        constexpr auto parser = &char_('a');
        char const * str = "a";
        EXPECT_FALSE(parse(str, parser));
    }
    {
        constexpr auto parser = &char_('a');
        std::string str = "a";
        auto first = str.c_str();
        EXPECT_TRUE(prefix_parse(first, boost::parser::detail::text::null_sentinel, parser));
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
            char const * str = "abc";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, "abc");
        }

        {
            char const * str = "abc";
            std::optional<std::string> const chars = parse(str, parser);
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, "abc");
        }

        {
            char const * str = "xyz";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, "xyz");
        }

        {
            char const * str = "abz";
            std::string chars;
            rethrow_error_handler eh;
            EXPECT_ANY_THROW(parse(str, with_error_handler(parser, eh), chars));
        }

        {
            char const * str = "abz";
            std::string chars;
            EXPECT_FALSE(parse(str, parser, chars));
        }

        {
            char const * str = "abz";
            std::string chars;
            stream_error_handler eh("simple_parser.cpp");
            EXPECT_FALSE(parse(str, with_error_handler(parser, eh), chars));
        }

        {
            char const * str = "ab";
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
            char const * str = "abc";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, "abc");
        }

        {
            char const * str = "abc";
            std::optional<std::string> const chars = parse(str, parser);
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, "abc");
        }

        {
            char const * str = "xyz";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, chars, trace::on));
            EXPECT_EQ(chars, "xyz");
        }
    }
}

TEST(parser, broken_utf8)
{
    constexpr char c = 0xcc;
    constexpr auto parser = *char_(c);
    {
        char const array[3] = {(char)0xcc, (char)0x80, 0}; // U+0300
        std::string str = array;
        std::string chars;
        auto first = str.begin();
        EXPECT_TRUE(prefix_parse(first, str.end(), parser, chars));
        char const expected[2] = {(char)0xcc, 0};
        EXPECT_EQ(chars, expected); // Finds one match of the *char* 0xcc.
    }
#if defined(__cpp_char8_t)
    {
        std::u8string str = u8"\xcc\x80"; // U+0300
        std::string chars;
        auto first = str.begin();
        EXPECT_TRUE(prefix_parse(first, str.end(), parser, chars));
        EXPECT_EQ(chars, ""); // Finds zero matches of the *code point* 0xcc.
    }
#endif
}

TEST(parser, attr_out_param_compat)
{
    {
        namespace bp = boost::parser;
        auto const p = bp::string("foo");

        std::vector<char> result;
        bool const success = bp::parse("foo", p, result);
        EXPECT_TRUE(success && result == std::vector<char>({'f', 'o', 'o'}));
    }
    {
        namespace bp = boost::parser;
        auto const p = bp::string("foo");

        std::vector<int> result;
        bool const success = bp::parse("foo", p, result);
        EXPECT_TRUE(success && result == std::vector<int>({'f', 'o', 'o'}));
    }
    {
        namespace bp = boost::parser;
        auto const p = +(bp::cp - ' ') >> ' ' >> string("foo");

        using attr_type = decltype(bp::parse(u8"", p));
        static_assert(std::is_same_v<
                      attr_type,
                      std::optional<bp::tuple<std::string, std::string>>>);

        bp::tuple<std::vector<int>, std::string> result;
        bool const success = bp::parse(u8"rôle foo" | bp::as_utf8, p, result);
        using namespace bp::literals;

        assert(success);
        assert(bp::get(result, 0_c) == std::vector<int>({'r', U'ô', 'l', 'e'}));
        assert(bp::get(result, 1_c) == "foo");
    }
    {
        namespace bp = boost::parser;
        auto const p = +(bp::cp - ' ') >> ' ' >> string("foo");

        using attr_type = decltype(bp::parse(u8"", p));
        static_assert(std::is_same_v<
                      attr_type,
                      std::optional<bp::tuple<std::string, std::string>>>);

        bp::tuple<std::vector<char>, std::string> result;
        bool const success = bp::parse(u8"rôle foo" | bp::as_utf8, p, result);
        using namespace bp::literals;

        assert(success);
        // The 4 code points "rôle" get transcoded to 5 UTF-8 code points to fit in the std::string.
        assert(bp::get(result, 0_c) == std::vector<char>({'r', (char)0xc3, (char)0xb4, 'l', 'e'}));
        assert(bp::get(result, 1_c) == "foo");
    }
}

TEST(parser, github_issue_78)
{
    namespace bp = boost::parser;
    std::vector<int> result;
    auto b = bp::parse("3 4 c", +bp::int_, bp::ws, result);
    EXPECT_FALSE(b);
    EXPECT_TRUE(result.empty());
}
