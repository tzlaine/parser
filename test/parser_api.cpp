/**
 *   Copyright (C) 2018 T. Zachary Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See
 *   accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt)
 */

#include <boost/parser/parser.hpp>
#include <boost/mpl/assert.hpp>

#include <gtest/gtest.h>


using namespace boost::parser;


static_assert(boost::parser::detail::non_unicode_char_range_like<char const *>);
static_assert(boost::parser::detail::non_unicode_char_range_like<char *>);
static_assert(
    boost::parser::detail::non_unicode_char_range_like<signed char const *>);
static_assert(
    boost::parser::detail::non_unicode_char_range_like<signed char *>);
static_assert(
    boost::parser::detail::non_unicode_char_range_like<unsigned char const *>);
static_assert(
    boost::parser::detail::non_unicode_char_range_like<unsigned char *>);
#if defined(__cpp_char8_t)
static_assert(
    !boost::parser::detail::non_unicode_char_range_like<char8_t const *>);
static_assert(!boost::parser::detail::non_unicode_char_range_like<char8_t *>);
#endif
static_assert(
    !boost::parser::detail::non_unicode_char_range_like<char16_t const *>);
static_assert(!boost::parser::detail::non_unicode_char_range_like<char16_t *>);
static_assert(
    !boost::parser::detail::non_unicode_char_range_like<char32_t const *>);
static_assert(!boost::parser::detail::non_unicode_char_range_like<char32_t *>);
static_assert(
    !boost::parser::detail::non_unicode_char_range_like<short int const *>);
static_assert(!boost::parser::detail::non_unicode_char_range_like<short int *>);
static_assert(!boost::parser::detail::non_unicode_char_range_like<
              unsigned short int const *>);
static_assert(
    !boost::parser::detail::non_unicode_char_range_like<unsigned short int *>);
static_assert(!boost::parser::detail::non_unicode_char_range_like<int const *>);
static_assert(!boost::parser::detail::non_unicode_char_range_like<int *>);
static_assert(
    !boost::parser::detail::non_unicode_char_range_like<unsigned int const *>);
static_assert(
    !boost::parser::detail::non_unicode_char_range_like<unsigned int *>);
static_assert(
    !boost::parser::detail::non_unicode_char_range_like<long int const *>);
static_assert(!boost::parser::detail::non_unicode_char_range_like<long int *>);
static_assert(!boost::parser::detail::non_unicode_char_range_like<
              unsigned long int const *>);
static_assert(
    !boost::parser::detail::non_unicode_char_range_like<unsigned long int *>);
static_assert(
    !boost::parser::detail::non_unicode_char_range_like<long long int const *>);
static_assert(
    !boost::parser::detail::non_unicode_char_range_like<long long int *>);
static_assert(!boost::parser::detail::non_unicode_char_range_like<
              unsigned long long int const *>);
static_assert(!boost::parser::detail::non_unicode_char_range_like<
              unsigned long long int *>);


static_assert(!boost::parser::detail::non_unicode_char_range_like<char>);
static_assert(!boost::parser::detail::non_unicode_char_range_like<signed char>);
static_assert(
    !boost::parser::detail::non_unicode_char_range_like<unsigned char>);
#if defined(__cpp_char8_t)
static_assert(!boost::parser::detail::non_unicode_char_range_like<char8_t>);
#endif
static_assert(!boost::parser::detail::non_unicode_char_range_like<char16_t>);
static_assert(!boost::parser::detail::non_unicode_char_range_like<char32_t>);
static_assert(!boost::parser::detail::non_unicode_char_range_like<short int>);
static_assert(
    !boost::parser::detail::non_unicode_char_range_like<unsigned short int>);
static_assert(!boost::parser::detail::non_unicode_char_range_like<int>);
static_assert(
    !boost::parser::detail::non_unicode_char_range_like<unsigned int>);
static_assert(!boost::parser::detail::non_unicode_char_range_like<long int>);
static_assert(
    !boost::parser::detail::non_unicode_char_range_like<unsigned long int>);
static_assert(
    !boost::parser::detail::non_unicode_char_range_like<long long int>);
static_assert(!boost::parser::detail::non_unicode_char_range_like<
              unsigned long long int>);


constexpr callback_rule<struct callback_char_rule_tag, char>
    callback_char_rule = "callback_char_rule";
constexpr auto callback_char_rule_def = char_;
BOOST_PARSER_DEFINE_RULES(callback_char_rule);

TEST(parser, full_parse_api)
{
    constexpr auto skip_ws = ascii::space;

    std::string const str = "a";

    // attr out param
    {
        char out = 0;
        auto first = str.c_str();
        EXPECT_TRUE(parse(first, boost::text::null_sentinel{}, char_, out));
        first = str.c_str();
        EXPECT_EQ(out, 'a');
        out = 0;
        first = str.c_str();
        EXPECT_TRUE(
            !parse(first, boost::text::null_sentinel{}, char_('b'), out));
        EXPECT_EQ(out, 0);
    }
    // attr out param
    {
        char out = 0;
        EXPECT_TRUE(parse(str, char_, out));
        EXPECT_EQ(out, 'a');
        out = 0;
        EXPECT_FALSE(parse(str, char_('b'), out));
        EXPECT_EQ(out, 0);
    }

    // returned attr
    {
        auto first = str.c_str();
        EXPECT_TRUE(parse(first, boost::text::null_sentinel{}, char_));
        first = str.c_str();
        EXPECT_EQ(*parse(first, boost::text::null_sentinel{}, char_), 'a');
        first = str.c_str();
        EXPECT_FALSE(parse(first, boost::text::null_sentinel{}, char_('b')));
    }
    // returned attr
    {
        EXPECT_TRUE(parse(str, char_));
        EXPECT_EQ(*parse(str, char_), 'a');
        EXPECT_FALSE(parse(str, char_('b')));
    }

    // attr out param, using skipper
    {
        char out = 0;
        auto first = str.c_str();
        EXPECT_TRUE(
            parse(first, boost::text::null_sentinel{}, char_, skip_ws, out));
        first = str.c_str();
        EXPECT_EQ(out, 'a');
        out = 0;
        first = str.c_str();
        EXPECT_FALSE(parse(
            first, boost::text::null_sentinel{}, char_('b'), skip_ws, out));
        EXPECT_EQ(out, 0);
    }
    // attr out param, using skipper
    {
        char out = 0;
        EXPECT_TRUE(parse(str, char_, skip_ws, out));
        EXPECT_EQ(out, 'a');
        out = 0;
        EXPECT_FALSE(parse(str, char_('b'), skip_ws, out));
        EXPECT_EQ(out, 0);
    }

    // returned attr, using skipper
    {
        auto first = str.c_str();
        EXPECT_TRUE(parse(first, boost::text::null_sentinel{}, char_, skip_ws));
        first = str.c_str();
        EXPECT_EQ(
            *parse(first, boost::text::null_sentinel{}, char_, skip_ws), 'a');
        first = str.c_str();
        EXPECT_TRUE(
            !parse(first, boost::text::null_sentinel{}, char_('b'), skip_ws));
    }
    // returned attr, using skipper
    {
        EXPECT_TRUE(parse(str, char_, skip_ws));
        EXPECT_EQ(*parse(str, char_, skip_ws), 'a');
        EXPECT_FALSE(parse(str, char_('b'), skip_ws));
    }

    // callback
    {
        char out = 0;
        auto callbacks = [&out](auto tag, auto x) { out = x; };
        auto first = str.c_str();
        EXPECT_TRUE(callback_parse(
            first,
            boost::text::null_sentinel{},
            callback_char_rule,
            callbacks));
        first = str.c_str();
        EXPECT_EQ(out, 'a');
    }
    // callback
    {
        char out = 0;
        auto callbacks = [&out](auto tag, auto x) { out = x; };
        EXPECT_TRUE(callback_parse(str, callback_char_rule, callbacks));
        EXPECT_EQ(out, 'a');
    }

#if 0 // TODO: Fix!
    // callback, using skipper
    {
        char out = 0;
        auto callbacks = [&out](auto tag, auto x) { out = x; };
        auto first = str.c_str();
        EXPECT_TRUE(callback_parse(
            first,
            boost::text::null_sentinel{},
            callback_char_rule,
            skip_ws,
            callbacks));
        first = str.c_str();
        EXPECT_EQ(out, 'a');
    }
    // callback, using skipper
    {
        char out = 0;
        auto callbacks = [&out](auto tag, auto x) { out = x; };
        EXPECT_TRUE(
            callback_parse(str, callback_char_rule, skip_ws, callbacks));
        EXPECT_EQ(out, 'a');
    }
#endif
}

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
        EXPECT_TRUE(parse(str, parser_1));
        EXPECT_FALSE(parse(str, parser_2));
    }
    {
        std::string str = "ab";
        auto first = str.c_str();
        EXPECT_TRUE(parse(first, boost::text::null_sentinel{}, char_));
        first = str.c_str();
        EXPECT_TRUE(parse(first, boost::text::null_sentinel{}, parser_1));
        first = str.c_str();
        EXPECT_FALSE(parse(str, parser_2));
    }
    {
        std::string str = "ab";
        std::vector<char> result;
        EXPECT_TRUE(parse(str, parser_1, result));
        using namespace boost::hana::literals;
        EXPECT_EQ(result[0_c], 'a');
        EXPECT_EQ(result[1_c], 'b');
    }
    {
        std::string str = "abc";
        EXPECT_FALSE(parse(str, parser_1));
        EXPECT_TRUE(parse(str, parser_2));
    }
    {
        std::string str = "abc";
        auto first = str.c_str();
        EXPECT_TRUE(parse(first, boost::text::null_sentinel{}, parser_1));
        first = str.c_str();
        EXPECT_TRUE(parse(first, boost::text::null_sentinel{}, parser_2));
    }
    {
        std::string str = "abc";
        std::vector<char> result;
        EXPECT_TRUE(parse(str, parser_2, result));
        using namespace boost::hana::literals;
        EXPECT_EQ(result[0_c], 'a');
        EXPECT_EQ(result[1_c], 'b');
        EXPECT_EQ(result[2_c], 'c');
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
    }
    {
        std::string str = "z";
        auto first = str.c_str();
        EXPECT_TRUE(parse(first, boost::text::null_sentinel{}, parser_5));
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
        EXPECT_TRUE(parse(first, boost::text::null_sentinel{}, parser_5, c));
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
    }
    {
        std::string str = "false ";
        bool b = true;
        auto first = str.c_str();
        EXPECT_TRUE(parse(first, boost::text::null_sentinel{}, bool_, b));
        EXPECT_EQ(b, false);
    }
    {
        std::string str = "true ";
        auto r = boost::text::as_utf32(str);
        bool b = false;
        auto first = r.begin();
        auto const last = r.end();
        EXPECT_TRUE(parse(first, last, bool_, b));
        EXPECT_EQ(b, true);
    }
    {
        std::string str = "false";
        auto r = boost::text::as_utf32(str);
        bool b = true;
        auto first = r.begin();
        auto const last = r.end();
        EXPECT_TRUE(parse(first, last, bool_, b));
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
    {
#if 0 // TODO: Should not compile, because the action makes the parser return a
      // nope!
        {
            std::string str = "";
            std::stringstream ss;
            auto action = [&ss](auto & context) { ss << _attr(context); };
            auto parser = *char_('b')[action];
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
        }
#endif

        {
            std::string str = "";
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
#if 0 // TODO: Should not compile, because the action makes the parser return a
      // nope!
        {
            std::string str = "";
            std::stringstream ss;
            auto action = [&ss](auto & context) { ss << _attr(context); };
            auto parser = +char_('b')[action];
            std::vector<char> chars;
            EXPECT_FALSE(parse(str, parser, chars));
        }
#endif

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
            std::string chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, "");

            {
                std::optional<std::string> const chars = parse(str, parser);
                EXPECT_TRUE(chars);
                EXPECT_EQ(*chars, "");
            }
        }
        {
            std::string str = "z";
            {
                std::string chars;
                EXPECT_FALSE(parse(str, parser, chars));
            }
            {
                std::string chars;
                auto first = str.c_str();
                EXPECT_TRUE(
                    parse(first, boost::text::null_sentinel{}, parser, chars));
                EXPECT_EQ(chars, "");
            }

            {
                std::optional<std::string> const chars = parse(str, parser);
                EXPECT_FALSE(chars);
            }
            {
                auto first = str.c_str();
                std::optional<std::string> const chars =
                    parse(first, boost::text::null_sentinel{}, parser);
                EXPECT_TRUE(chars);
                EXPECT_EQ(*chars, "");
            }
        }
        {
            std::string str = "zs";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, "zs");

            {
                std::optional<std::string> const chars = parse(str, parser);
                EXPECT_TRUE(chars);
                EXPECT_EQ(*chars, "zs");
            }
        }
        {
            std::string str = "zszs";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, "zszs");

            {
                std::optional<std::string> const chars = parse(str, parser);
                EXPECT_TRUE(chars);
                EXPECT_EQ(*chars, "zszs");
            }
        }
    }

    {
        constexpr auto parser = *string("zs");

        {
            std::string str = "";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>());
        }
        {
            std::string str = "z";
            std::vector<char> chars;
            EXPECT_FALSE(parse(str, parser, chars));
        }
        {
            std::string str = "z";
            std::vector<char> chars;
            auto first = str.c_str();
            EXPECT_TRUE(
                parse(first, boost::text::null_sentinel{}, parser, chars));
        }
        {
            std::string str = "zs";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'z', 's'}));
        }
        {
            std::string str = "zszs";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>({'z', 's', 'z', 's'}));
        }
    }
}

TEST(parser, omit)
{
    {
        constexpr auto parser = omit[*+char_('z')];

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
            EXPECT_EQ(chars, std::vector<char>());
        }
        {
            std::string str = "zz";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>());
        }
        {
            std::string str = "";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string str = "z";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser));
        }
        {
            std::string str = "zz";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser));
        }
    }

    {
        constexpr auto parser = omit[*string("zs")];

        {
            std::string str = "";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>());
        }
        {
            std::string str = "z";
            std::vector<char> chars;
            EXPECT_FALSE(parse(str, parser, chars));
        }
        {
            std::string str = "z";
            std::vector<char> chars;
            auto first = str.c_str();
            EXPECT_TRUE(
                parse(first, boost::text::null_sentinel{}, parser, chars));
        }
        {
            std::string str = "zs";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>());
        }
        {
            std::string str = "zszs";
            std::vector<char> chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, std::vector<char>());
        }
    }
}

TEST(parser, repeat)
{
    {
        constexpr auto parser = repeat(2, 3)[string("zs")];

        {
            std::string str = "";
            std::string chars;
            EXPECT_FALSE(parse(str, parser, chars));
            EXPECT_EQ(chars, "");

            {
                std::optional<std::string> const chars = parse(str, parser);
                EXPECT_FALSE(chars);
            }
        }
        {
            std::string str = "z";
            std::string chars;
            EXPECT_FALSE(parse(str, parser, chars));
            EXPECT_EQ(chars, "");

            {
                std::optional<std::string> const chars = parse(str, parser);
                EXPECT_FALSE(chars);
            }
        }
        {
            std::string str = "zs";
            std::string chars;
            EXPECT_FALSE(parse(str, parser, chars));
            EXPECT_EQ(chars, "");

            {
                std::optional<std::string> const chars = parse(str, parser);
                EXPECT_FALSE(chars);
            }
        }
        {
            std::string str = "zszs";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, "zszs");

            {
                std::optional<std::string> const chars = parse(str, parser);
                EXPECT_TRUE(chars);
                EXPECT_EQ(*chars, "zszs");
            }
        }
    }
}

TEST(parser, raw)
{
    {
        constexpr auto parser = raw[*string("zs")];
        using range_t = view<std::string::const_iterator>;

        {
            std::string const str = "";
            range_t r;
            EXPECT_TRUE(parse(str, parser, r));
            EXPECT_EQ(r, range_t(str.begin(), str.begin()));
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
            EXPECT_TRUE(parse(first, str.end(), parser, r));
            EXPECT_EQ(r, range_t(str.begin(), str.begin()));
        }
        {
            std::string const str = "zs";
            range_t r;
            EXPECT_TRUE(parse(str, parser, r));
            EXPECT_EQ(r, range_t(str.begin(), str.end()));
        }
        {
            std::string const str = "zszs";
            range_t r;
            EXPECT_TRUE(parse(str, parser, r));
            EXPECT_EQ(r, range_t(str.begin(), str.end()));
        }
        {
            std::string const str = "";
            std::optional<range_t> result = parse(str, parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, range_t(str.begin(), str.begin()));
        }
        {
            std::string const str = "z";
            std::optional<range_t> result = parse(str, parser);
            EXPECT_FALSE(result);
        }
        {
            std::string const str = "z";
            auto first = str.begin();
            std::optional<range_t> result = parse(first, str.end(), parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, range_t(str.begin(), str.begin()));
        }
        {
            std::string const str = "zs";
            std::optional<range_t> result = parse(str, parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, range_t(str.begin(), str.end()));
        }
        {
            std::string const str = "zszs";
            std::optional<range_t> result = parse(str, parser);
            EXPECT_TRUE(result);
            EXPECT_EQ(*result, range_t(str.begin(), str.end()));
        }
    }
}

TEST(parser, delimited)
{
    {
        constexpr auto parser = string("yay") % ',';

        {
            std::string str = "";
            std::string chars;
            EXPECT_FALSE(parse(str, parser, chars));
            EXPECT_EQ(chars, "");

            {
                std::optional<std::string> const chars = parse(str, parser);
                EXPECT_FALSE(chars);
            }
        }
        {
            std::string str = "z";
            std::string chars;
            EXPECT_FALSE(parse(str, parser, chars));
            EXPECT_EQ(chars, "");

            {
                std::optional<std::string> const chars = parse(str, parser);
                EXPECT_FALSE(chars);
            }
        }
        {
            std::string str = ",";
            std::string chars;
            EXPECT_FALSE(parse(str, parser, chars));
            EXPECT_EQ(chars, "");

            {
                std::optional<std::string> const chars = parse(str, parser);
                EXPECT_FALSE(chars);
            }
        }
        {
            std::string str = ",yay";
            std::string chars;
            EXPECT_FALSE(parse(str, parser, chars));
            EXPECT_EQ(chars, "");

            {
                std::optional<std::string> const chars = parse(str, parser);
                EXPECT_FALSE(chars);
            }
        }
        {
            std::string str = "yay";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, "yay");

            {
                std::optional<std::string> const chars = parse(str, parser);
                EXPECT_TRUE(chars);
                EXPECT_EQ(*chars, "yay");
            }
        }
        {
            std::string str = "yayyay";
            {
                std::string chars;
                EXPECT_FALSE(parse(str, parser, chars));
            }
            {
                std::string chars;
                auto first = str.c_str();
                EXPECT_TRUE(
                    parse(first, boost::text::null_sentinel{}, parser, chars));
                EXPECT_EQ(chars, "yay");
            }

            {
                std::optional<std::string> const chars = parse(str, parser);
                EXPECT_FALSE(chars);
            }
            {
                auto first = str.c_str();
                std::optional<std::string> const chars =
                    parse(first, boost::text::null_sentinel{}, parser);
                EXPECT_TRUE(chars);
                EXPECT_EQ(*chars, "yay");
            }
        }
        {
            std::string str = "yay,";
            {
                std::string chars;
                EXPECT_FALSE(parse(str, parser, chars));
            }
            {
                std::string chars;
                auto first = str.c_str();
                EXPECT_TRUE(
                    parse(first, boost::text::null_sentinel{}, parser, chars));
                EXPECT_EQ(chars, "yay");
            }

            {
                std::optional<std::string> const chars = parse(str, parser);
                EXPECT_FALSE(chars);
            }
            {
                auto first = str.c_str();
                std::optional<std::string> const chars =
                    parse(first, boost::text::null_sentinel{}, parser);
                EXPECT_TRUE(chars);
                EXPECT_EQ(*chars, "yay");
            }
        }
        {
            std::string str = "yay,yay,yay";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, "yayyayyay");

            {
                std::optional<std::string> const chars = parse(str, parser);
                EXPECT_TRUE(chars);
                EXPECT_EQ(*chars, "yayyayyay");
            }
        }
    }

    {
        constexpr auto parser = string("yay") % ',';
        {
            std::string str = "";
            std::string chars;
            EXPECT_FALSE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, "");
        }

        {
            std::string str = "";
            std::optional<std::string> const chars =
                parse(str, parser, char_(' '));
            EXPECT_FALSE(chars);
        }
        {
            std::string str = "z";
            std::string chars;
            EXPECT_FALSE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, "");
        }
        {
            std::string str = "z";
            std::optional<std::string> const chars =
                parse(str, parser, char_(' '));
            EXPECT_FALSE(chars);
        }
        {
            std::string str = ",";
            std::string chars;
            EXPECT_FALSE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, "");
        }
        {
            std::string str = ",";
            std::optional<std::string> const chars =
                parse(str, parser, char_(' '));
            EXPECT_FALSE(chars);
        }
        {
            std::string str = " ,yay";
            std::string chars;
            EXPECT_FALSE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, "");
        }
        {
            std::string str = " ,yay";
            std::optional<std::string> const chars =
                parse(str, parser, char_(' '));
            EXPECT_FALSE(chars);
        }
        {
            std::string str = ", yay";
            std::string chars;
            EXPECT_FALSE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, "");
        }
        {
            std::string str = ", yay";
            std::optional<std::string> const chars =
                parse(str, parser, char_(' '));
            EXPECT_FALSE(chars);
        }
        {
            std::string str = ",yay ";
            std::string chars;
            EXPECT_FALSE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, "");
        }
        {
            std::string str = ",yay ";
            std::optional<std::string> const chars =
                parse(str, parser, char_(' '));
            EXPECT_FALSE(chars);
        }

        {
            std::string str = " , yay ";
            std::string chars;
            EXPECT_FALSE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, "");
        }
        {
            std::string str = " , yay ";
            std::optional<std::string> const chars =
                parse(str, parser, char_(' '));
            EXPECT_FALSE(chars);
        }
        {
            std::string str = "yay";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, "yay");
        }
        {
            std::string str = "yay";
            std::optional<std::string> const chars =
                parse(str, parser, char_(' '));
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, "yay");
        }
        {
            std::string str = "yayyay";
            std::string chars;
            EXPECT_FALSE(parse(str, parser, char_(' '), chars));
        }
        {
            std::string str = "yayyay";
            std::string chars;
            auto first = str.c_str();
            EXPECT_TRUE(parse(
                first,
                boost::text::null_sentinel{},
                parser,
                char_(' '),
                chars));
            EXPECT_EQ(chars, "yay");
        }
        {
            std::string str = "yayyay";
            std::optional<std::string> const chars =
                parse(str, parser, char_(' '));
            EXPECT_FALSE(chars);
        }
        {
            std::string str = "yayyay";
            auto first = str.c_str();
            std::optional<std::string> const chars =
                parse(first, boost::text::null_sentinel{}, parser, char_(' '));
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, "yay");
        }
        {
            std::string str = "yay,";
            std::string chars;
            EXPECT_FALSE(parse(str, parser, char_(' '), chars));
        }
        {
            std::string str = "yay,";
            std::string chars;
            auto first = str.c_str();
            EXPECT_TRUE(parse(
                first,
                boost::text::null_sentinel{},
                parser,
                char_(' '),
                chars));
            EXPECT_EQ(chars, "yay");
        }
        {
            std::string str = "yay,";
            std::optional<std::string> const chars =
                parse(str, parser, char_(' '));
            EXPECT_FALSE(chars);
        }
        {
            std::string str = "yay,";
            auto first = str.c_str();
            std::optional<std::string> const chars =
                parse(first, boost::text::null_sentinel{}, parser, char_(' '));
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, "yay");
        }
        {
            std::string str = "yay,yay,yay";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, "yayyayyay");
        }
        {
            std::string str = "yay,yay,yay";
            std::optional<std::string> const chars =
                parse(str, parser, char_(' '));
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, "yayyayyay");
        }
        {
            std::string str = " yay,yay,yay";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, "yayyayyay");
        }
        {
            std::string str = " yay,yay,yay";
            std::optional<std::string> const chars =
                parse(str, parser, char_(' '));
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, "yayyayyay");
        }
        {
            std::string str = "yay ,yay,yay";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, "yayyayyay");
        }

        {
            std::string str = "yay ,yay,yay";
            std::optional<std::string> const chars =
                parse(str, parser, char_(' '));
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, "yayyayyay");
        }
        {
            std::string str = "yay, yay,yay";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, "yayyayyay");
        }
        {
            std::string str = "yay, yay,yay";
            std::optional<std::string> const chars =
                parse(str, parser, char_(' '));
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, "yayyayyay");
        }
        {
            std::string str = "yay,yay ,yay";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, "yayyayyay");
        }

        {
            std::string str = "yay,yay ,yay";
            std::optional<std::string> const chars =
                parse(str, parser, char_(' '));
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, "yayyayyay");
        }
        {
            std::string str = "yay,yay, yay";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, "yayyayyay");
        }

        {
            std::string str = "yay,yay, yay";
            std::optional<std::string> const chars =
                parse(str, parser, char_(' '));
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, "yayyayyay");
        }
        {
            std::string str = "yay,yay,yay ";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, "yayyayyay");
        }

        {
            std::string str = "yay,yay,yay ";
            std::optional<std::string> const chars =
                parse(str, parser, char_(' '));
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, "yayyayyay");
        }
        {
            std::string str = " yay , yay , yay ";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, "yayyayyay");
        }

        {
            std::string str = " yay , yay , yay ";
            std::optional<std::string> const chars =
                parse(str, parser, char_(' '));
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, "yayyayyay");
        }
        {
            std::string str = "yay, yay, yay";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, "yayyayyay");
        }

        {
            std::string str = "yay, yay, yay";
            std::optional<std::string> const chars =
                parse(str, parser, char_(' '));
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, "yayyayyay");
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
                std::string chars;
                EXPECT_FALSE(parse(str, parser, char_(' '), chars));
            }
            {
                std::string chars;
                auto first = str.c_str();
                EXPECT_TRUE(parse(
                    first,
                    boost::text::null_sentinel{},
                    parser,
                    char_(' '),
                    chars));
                EXPECT_EQ(chars, "yay");
            }

            {
                std::string str = "yay, yay, yay";
                std::optional<std::string> const chars =
                    parse(str, parser, char_(' '));
                EXPECT_FALSE(chars);
            }
            {
                std::string str = "yay, yay, yay";
                auto first = str.c_str();
                std::optional<std::string> const chars = parse(
                    first, boost::text::null_sentinel{}, parser, char_(' '));
                EXPECT_TRUE(chars);
                EXPECT_EQ(*chars, "yay");
            }
        }
        {
            std::string str = " yay, yay, yay";
            {
                std::string chars;
                EXPECT_FALSE(parse(str, parser, char_(' '), chars));
            }
            {
                std::string chars;
                auto first = str.c_str();
                EXPECT_TRUE(parse(
                    first,
                    boost::text::null_sentinel{},
                    parser,
                    char_(' '),
                    chars));
                EXPECT_EQ(chars, "yay");
            }

            {
                std::string str = " yay, yay, yay";
                std::optional<std::string> const chars =
                    parse(str, parser, char_(' '));
                EXPECT_FALSE(chars);
            }
            {
                std::string str = " yay, yay, yay";
                auto first = str.c_str();
                std::optional<std::string> const chars = parse(
                    first, boost::text::null_sentinel{}, parser, char_(' '));
                EXPECT_TRUE(chars);
                EXPECT_EQ(*chars, "yay");
            }
        }
    }

    {
        constexpr auto parser = lexeme[skip[string("yay") % ',']];

        {
            std::string str = "yay, yay, yay";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, "yayyayyay");

            {
                std::string str = "yay, yay, yay";
                std::optional<std::string> const chars =
                    parse(str, parser, char_(' '));
                EXPECT_TRUE(chars);
                EXPECT_EQ(*chars, "yayyayyay");
            }
        }
        {
            std::string str = " yay, yay, yay";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, char_(' '), chars));
            EXPECT_EQ(chars, "yayyayyay");

            {
                std::string str = " yay, yay, yay";
                std::optional<std::string> const chars =
                    parse(str, parser, char_(' '));
                EXPECT_TRUE(chars);
                EXPECT_EQ(*chars, "yayyayyay");
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
            std::string chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, "yayyayyay");
        }
        {
            std::string str = "yay, yay, yay";
            std::optional<std::string> const chars = parse(str, parser);
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, "yayyayyay");
        }
        {
            std::string str = " yay, yay, yay";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, "yayyayyay");
        }
        {
            std::string str = " yay, yay, yay";
            std::optional<std::string> const chars = parse(str, parser);
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, "yayyayyay");
        }
    }
}

TEST(parser, combined_seq_and_or)
{
    {
        constexpr auto parser = char_('a') >> char_('b') >> char_('c') |
                                char_('x') >> char_('y') >> char_('z');
        {
            std::string str = "abc";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, "abc");
        }

        {
            std::string str = "abc";
            std::optional<std::vector<char>> const chars = parse(str, parser);
            EXPECT_TRUE(chars);
            EXPECT_EQ(*chars, std::vector<char>({'a', 'b', 'c'}));
        }

        {
            std::string str = "xyz";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, "xyz");
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
        {
            std::string str = "abc";
            boost::any chars;
            EXPECT_TRUE(parse(str, parser, chars));
        }

        {
            std::string str = "xyz";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, "xyz");
        }
    }

    {
        constexpr auto parser = string("a") >> string("b") >> string("c") |
                                string("x") >> string("y") >> string("z");
#if 0 // TODO: Document why this assigns "c" instead of "abc" to the any.
        {
            std::string str = "abc";
            boost::any chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(boost::any_cast<std::string>(chars), "abc");
        }
#endif

        {
            std::string str = "xyz";
            std::string chars;
            EXPECT_TRUE(parse(str, parser, chars));
            EXPECT_EQ(chars, "xyz");
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
        EXPECT_TRUE(parse(first, boost::text::null_sentinel{}, parser));
    }

    {
        constexpr auto parser = (char_('a') >> string("b") > char_('c')) |
                                (char_('x') >> string("y") >> char_('z'));
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
        constexpr auto parser = (char_('a') >> string("b") > char_('c')) |
                                (char_('x') >> string("y") >> char_('z'));
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
