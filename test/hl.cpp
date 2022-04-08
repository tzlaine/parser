/**
 *   Copyright (C) 2020 T. Zachary Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See
 *   accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt)
 */

#include <boost/parser/detail/hl.hpp>

#include <optional>
#include <sstream>
#include <tuple>

#include <gtest/gtest.h>


using namespace boost::parser;

TEST(hl, for_each)
{
    {
        tuple<std::string, int> t{"foo", 4};
        std::ostringstream oss;
        detail::hl::for_each(t, [&](auto x) { oss << x << ' '; });
        EXPECT_EQ(get(t, llong<0>{}), "foo");
        EXPECT_EQ(oss.str(), "foo 4 ");
    }
    {
        tuple<std::string, int> t{"foo", 4};
        std::ostringstream oss;
        detail::hl::for_each(std::move(t), [&](auto x) { oss << x << ' '; });
        EXPECT_EQ(get(t, llong<0>{}), "");
        EXPECT_EQ(oss.str(), "foo 4 ");
    }
}

TEST(hl, transform)
{
    {
        tuple<std::string, int> t{"foo", 4};
        auto t2 = detail::hl::transform(
            t, [&](auto x) { return std::optional<decltype(x)>{x}; });
        EXPECT_EQ(get(t, llong<0>{}), "foo");
        EXPECT_EQ(get(t2, llong<0>{}), std::optional<std::string>{"foo"});
        EXPECT_EQ(get(t2, llong<1>{}), std::optional<int>{4});
    }
    {
        tuple<std::string, int> t{"foo", 4};
        auto t2 = detail::hl::transform(std::move(t), [&](auto x) {
            return std::optional<decltype(x)>{x};
        });
        EXPECT_EQ(get(t, llong<0>{}), "");
        EXPECT_EQ(get(t2, llong<0>{}), std::optional<std::string>{"foo"});
        EXPECT_EQ(get(t2, llong<1>{}), std::optional<int>{4});
    }
}

TEST(hl, fold_left)
{
    tuple<std::string, int> t{"foo", 4};
    auto t2 =
        detail::hl::fold_left(t, tuple<>{}, [](auto const & state, auto x) {
            return detail::hl::append(state, x);
        });
    EXPECT_EQ(t, t2);
}

TEST(hl, size)
{
    {
        tuple<std::string, int> t{"foo", 4};
        EXPECT_EQ(detail::hl::size(t).value, 2u);
    }
    {
        tuple<std::string, int> t{"foo", 4};
        constexpr std::size_t size = detail::hl::size(t).value;
        EXPECT_EQ(size, 2u);
    }
}

TEST(hl, contains)
{
    tuple<std::string, int, double> t{"foo", 4, 3.0};
    EXPECT_TRUE(detail::hl::contains(t, 3.0));
    EXPECT_TRUE(detail::hl::contains(t, "foo"));
    EXPECT_TRUE(detail::hl::contains(t, std::string_view("foo")));
    EXPECT_FALSE(detail::hl::contains(t, std::string_view("banana")));
}

TEST(hl, front_back)
{
    tuple<std::string, int> t{"foo", 4};
    EXPECT_EQ(detail::hl::front(t), "foo");
    EXPECT_EQ(detail::hl::back(t), 4);
}

TEST(hl, drop_front)
{
    {
        tuple<std::string, int> t{"foo", 4};
        auto t2 = detail::hl::drop_front(t);
        EXPECT_EQ(get(t, llong<0>{}), "foo");
        EXPECT_EQ(get(t2, llong<0>{}), 4);
    }
    {
        tuple<std::string, int, double> t{"foo", 4, 3.0};
        auto t2 = detail::hl::drop_front(std::move(t));
        EXPECT_EQ(get(t, llong<0>{}), "foo");
        EXPECT_EQ(get(t2, llong<0>{}), 4);
        EXPECT_EQ(get(t2, llong<1>{}), 3.0);
    }
}

TEST(hl, drop_back)
{
    {
        tuple<std::string, int> t{"foo", 4};
        auto t2 = detail::hl::drop_back(t);
        EXPECT_EQ(get(t, llong<0>{}), "foo");
        EXPECT_EQ(get(t2, llong<0>{}), "foo");
    }
    {
        tuple<std::string, int, double> t{"foo", 4, 3.0};
        auto t2 = detail::hl::drop_back(std::move(t));
        EXPECT_EQ(get(t, llong<0>{}), "");
        EXPECT_EQ(get(t2, llong<0>{}), "foo");
        EXPECT_EQ(get(t2, llong<1>{}), 4);
    }
}

TEST(hl, first_second)
{
    tuple<std::string, int> t{"foo", 4};
    EXPECT_EQ(detail::hl::first(t), "foo");
    EXPECT_EQ(detail::hl::second(t), 4);
}

TEST(hl, append)
{
    {
        tuple<std::string> t{"foo"};
        auto t2 = detail::hl::append(t, 4);
        EXPECT_EQ(get(t, llong<0>{}), "foo");
        EXPECT_EQ(get(t2, llong<0>{}), "foo");
        EXPECT_EQ(get(t2, llong<1>{}), 4);
    }
    {
        tuple<std::string, int> t{"foo", 4};
        auto t2 = detail::hl::append(std::move(t), 3.0);
        EXPECT_EQ(get(t, llong<0>{}), "");
        EXPECT_EQ(get(t2, llong<0>{}), "foo");
        EXPECT_EQ(get(t2, llong<1>{}), 4);
        EXPECT_EQ(get(t2, llong<2>{}), 3.0);
    }
}

TEST(hl, prepend)
{
    {
        tuple<std::string> t{"foo"};
        auto t2 = detail::hl::prepend(t, 4);
        EXPECT_EQ(get(t, llong<0>{}), "foo");
        EXPECT_EQ(get(t2, llong<0>{}), 4);
        EXPECT_EQ(get(t2, llong<1>{}), "foo");
    }
    {
        tuple<std::string, int> t{"foo", 4};
        auto t2 = detail::hl::prepend(std::move(t), 3.0);
        EXPECT_EQ(get(t, llong<0>{}), "");
        EXPECT_EQ(get(t2, llong<0>{}), 3.0);
        EXPECT_EQ(get(t2, llong<1>{}), "foo");
        EXPECT_EQ(get(t2, llong<2>{}), 4);
    }
}

TEST(hl, zip)
{
    {
        tuple<std::string, int> t1{"foo", 4};
        tuple<double, std::string> t2{3.0, "bar"};
        auto t3 = detail::hl::zip(t1, t2);
        EXPECT_EQ(
            get(t3, llong<0>{}), (tuple<std::string, double>("foo", 3.0)));
        EXPECT_EQ(get(t3, llong<1>{}), (tuple<int, std::string>(4, "bar")));
    }
    {
        tuple<std::string, int> t1{"foo", 4};
        tuple<double, std::string> t2{3.0, "bar"};
        tuple<std::string, std::string> t3{"baz", "baz"};
        auto t4 = detail::hl::zip(t1, t2, t3);
        EXPECT_EQ(
            get(t4, llong<0>{}),
            (tuple<std::string, double, std::string>("foo", 3.0, "baz")));
        EXPECT_EQ(
            get(t4, llong<1>{}),
            (tuple<int, std::string, std::string>(4, "bar", "baz")));
    }
}
