/**
 *   Copyright (C) 2020 T. Zachary Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See
 *   accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt)
 */

#include <boost/parser/detail/hl.hpp>

#include <tuple>
#include <sstream>

#include <gtest/gtest.h>


using namespace boost::parser;

TEST(hl, for_each)
{
    {
        std::tuple<std::string, int> t{"foo", 4};
        std::ostringstream oss;
        detail::hl::for_each(t, [&](auto x) { oss << x << ' '; });
        EXPECT_EQ(std::get<0>(t), "foo");
        EXPECT_EQ(oss.str(), "foo 4 ");
    }
    {
        std::tuple<std::string, int> t{"foo", 4};
        std::ostringstream oss;
        detail::hl::for_each(std::move(t), [&](auto x) { oss << x << ' '; });
        EXPECT_EQ(std::get<0>(t), "");
        EXPECT_EQ(oss.str(), "foo 4 ");
    }
}

TEST(hl, transform)
{
    {
        std::tuple<std::string, int> t{"foo", 4};
        auto t2 = detail::hl::transform(
            t, [&](auto x) { return std::optional<decltype(x)>{x}; });
        EXPECT_EQ(std::get<0>(t), "foo");
        EXPECT_EQ(std::get<0>(t2), std::optional<std::string>{"foo"});
        EXPECT_EQ(std::get<1>(t2), std::optional<int>{4});
    }
    {
        std::tuple<std::string, int> t{"foo", 4};
        auto t2 = detail::hl::transform(std::move(t), [&](auto x) {
            return std::optional<decltype(x)>{x};
        });
        EXPECT_EQ(std::get<0>(t), "");
        EXPECT_EQ(std::get<0>(t2), std::optional<std::string>{"foo"});
        EXPECT_EQ(std::get<1>(t2), std::optional<int>{4});
    }
}

TEST(hl, fold_left)
{
    std::tuple<std::string, int> t{"foo", 4};
    auto t2 = detail::hl::fold_left(
        t, std::tuple<>{}, [](auto const & state, auto x) {
            return detail::hl::append(state, x);
        });
    EXPECT_EQ(t, t2);
}

TEST(hl, size)
{
    {
        std::tuple<std::string, int> t{"foo", 4};
        EXPECT_EQ(detail::hl::size(t), 2u);
    }
    {
        std::tuple<std::string, int> t{"foo", 4};
        constexpr std::size_t size = detail::hl::size(t);
        EXPECT_EQ(size, 2u);
    }
}

TEST(hl, contains)
{
    std::tuple<std::string, int, double> t{"foo", 4, 3.0};
    EXPECT_TRUE(detail::hl::contains(t, 3.0));
    EXPECT_TRUE(detail::hl::contains(t, "foo"));
    EXPECT_TRUE(detail::hl::contains(t, std::string_view("foo")));
    EXPECT_FALSE(detail::hl::contains(t, std::string_view("banana")));
}

TEST(hl, front_back)
{
    std::tuple<std::string, int> t{"foo", 4};
    EXPECT_EQ(detail::hl::front(t), "foo");
    EXPECT_EQ(detail::hl::back(t), 4);
}

TEST(hl, drop_front)
{
    {
        std::tuple<std::string, int> t{"foo", 4};
        auto t2 = detail::hl::drop_front(t);
        EXPECT_EQ(std::get<0>(t), "foo");
        EXPECT_EQ(std::get<0>(t2), 4);
    }
    {
        std::tuple<std::string, int, double> t{"foo", 4, 3.0};
        auto t2 = detail::hl::drop_front(std::move(t));
        EXPECT_EQ(std::get<0>(t), "foo");
        EXPECT_EQ(std::get<0>(t2), 4);
        EXPECT_EQ(std::get<1>(t2), 3.0);
    }
}

TEST(hl, drop_back)
{
    {
        std::tuple<std::string, int> t{"foo", 4};
        auto t2 = detail::hl::drop_back(t);
        EXPECT_EQ(std::get<0>(t), "foo");
        EXPECT_EQ(std::get<0>(t2), "foo");
    }
    {
        std::tuple<std::string, int, double> t{"foo", 4, 3.0};
        auto t2 = detail::hl::drop_back(std::move(t));
        EXPECT_EQ(std::get<0>(t), "");
        EXPECT_EQ(std::get<0>(t2), "foo");
        EXPECT_EQ(std::get<1>(t2), 4);
    }
}

TEST(hl, first_second)
{
    std::tuple<std::string, int> t{"foo", 4};
    EXPECT_EQ(detail::hl::first(t), "foo");
    EXPECT_EQ(detail::hl::second(t), 4);
}

TEST(hl, append)
{
    {
        std::tuple<std::string> t{"foo"};
        auto t2 = detail::hl::append(t, 4);
        EXPECT_EQ(std::get<0>(t), "foo");
        EXPECT_EQ(std::get<0>(t2), "foo");
        EXPECT_EQ(std::get<1>(t2), 4);
    }
    {
        std::tuple<std::string, int> t{"foo", 4};
        auto t2 = detail::hl::append(std::move(t), 3.0);
        EXPECT_EQ(std::get<0>(t), "");
        EXPECT_EQ(std::get<0>(t2), "foo");
        EXPECT_EQ(std::get<1>(t2), 4);
        EXPECT_EQ(std::get<2>(t2), 3.0);
    }
}

TEST(hl, prepend)
{
    {
        std::tuple<std::string> t{"foo"};
        auto t2 = detail::hl::prepend(t, 4);
        EXPECT_EQ(std::get<0>(t), "foo");
        EXPECT_EQ(std::get<0>(t2), 4);
        EXPECT_EQ(std::get<1>(t2), "foo");
    }
    {
        std::tuple<std::string, int> t{"foo", 4};
        auto t2 = detail::hl::prepend(std::move(t), 3.0);
        EXPECT_EQ(std::get<0>(t), "");
        EXPECT_EQ(std::get<0>(t2), 3.0);
        EXPECT_EQ(std::get<1>(t2), "foo");
        EXPECT_EQ(std::get<2>(t2), 4);
    }
}

TEST(hl, zip)
{
    {
        std::tuple<std::string, int> t1{"foo", 4};
        std::tuple<double, std::string> t2{3.0, "bar"};
        auto t3 = detail::hl::zip(t1, t2);
        EXPECT_EQ(
            std::get<0>(t3), (std::tuple<std::string, double>("foo", 3.0)));
        EXPECT_EQ(std::get<1>(t3), (std::tuple<int, std::string>(4, "bar")));
    }
    {
        std::tuple<std::string, int> t1{"foo", 4};
        std::tuple<double, std::string> t2{3.0, "bar"};
        std::tuple<std::string, std::string> t3{"baz", "baz"};
        auto t4 = detail::hl::zip(t1, t2, t3);
        EXPECT_EQ(
            std::get<0>(t4),
            (std::tuple<std::string, double, std::string>("foo", 3.0, "baz")));
        EXPECT_EQ(
            std::get<1>(t4),
            (std::tuple<int, std::string, std::string>(4, "bar", "baz")));
    }
}
