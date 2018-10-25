/**
 *   Copyright (C) 2018 T. Zachary Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See
 *   accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt)
 */

#include <boost/parser/parser.hpp>

#include <gtest/gtest.h>


using namespace boost::parser;


struct char_globals
{
    char c_ = 'd';
};
auto global_char = [](auto & context) { return _globals(context).c_; };

struct int_globals
{
    int i_ = 3;
};
auto global_int = [](auto & context) { return _globals(context).i_; };

auto always_3 = [](auto & context) { return 3; };
auto always_3u = [](auto & context) { return 3u; };


TEST(parser, lazy)
{
    {
        std::string str = "a";
        EXPECT_TRUE(parse(str, char_));
        EXPECT_FALSE(parse(str, char_('b')));
        char_globals globals;
        auto parser = with_globals(char_(global_char), globals);
        EXPECT_FALSE(parse(str, parser));
    }
    {
        std::string str = "d";
        EXPECT_TRUE(parse(str, char_));
        EXPECT_TRUE(parse(str, char_('d')));
        char_globals globals;
        auto result = parse(str, with_globals(char_(global_char), globals));
        EXPECT_TRUE(result);
        EXPECT_EQ(*result, 'd');
    }

    {
        std::string str = "b";
        char c = '\0';
        char_globals globals;
        auto parser = with_globals(char_('a', global_char), globals);
        EXPECT_TRUE(parse(str, parser, c));
        EXPECT_EQ(c, 'b');
        EXPECT_FALSE(
            parse(str, with_globals(char_(global_char, global_char), globals)));
    }

    {
        std::string str = "abc";
        int_globals globals;
        auto parser = with_globals(repeat(2, global_int)[char_], globals);
        std::string out_str;
        EXPECT_TRUE(parse(str, parser, out_str));
        EXPECT_EQ(out_str, "abc");
        EXPECT_FALSE(parse("a", parser, out_str));
    }

    {
        std::string str = "3";
        EXPECT_TRUE(parse(str, int_(always_3)));
    }

    {
        std::string str = "3";
        EXPECT_TRUE(parse(str, uint_(always_3u)));
    }
}
