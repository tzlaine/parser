/**
 *   Copyright (C) 2018 T. Zachary Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See
 *   accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt)
 */

#include <boost/parser/tuple.hpp>

#include <gtest/gtest.h>

#include "ill_formed.hpp"

#include <string>


namespace bp = boost::parser;


struct empty
{};

struct int_
{
    int i;
};

struct int_string
{
    int i;
    std::string s;
};

struct string_int
{
    std::string s;
    int i;
};

struct string_int_double
{
    std::string s;
    int i;
    double d;
};

struct string_int_double_priv
{
    std::string s;

private:
    int i;
    double d;
};

struct string_int_double_no_copy_move
{
    string_int_double_no_copy_move(string_int_double_no_copy_move const &) =
        delete;
    string_int_double_no_copy_move(string_int_double_no_copy_move &&) = delete;

private:
    std::string s;
    int i;
    double d;
};

struct employee
{
    int age;
    std::string surname;
    std::string forename;
    double salary;
};

TEST(aggr_tuple_assignment, struct_arity)
{
    using bp::detail::struct_arity_v;

    static_assert(struct_arity_v<empty> == 0);
    static_assert(struct_arity_v<int_> == 1);
    static_assert(struct_arity_v<int_string> == 2);
    static_assert(struct_arity_v<string_int> == 2);
    static_assert(struct_arity_v<string_int_double> == 3);

    // 1 due to the copy ctor.
    static_assert(struct_arity_v<string_int_double_priv> == 1);

    static_assert(struct_arity_v<string_int_double_no_copy_move> <= 0);
}

TEST(aggr_tuple_assignment, is_struct_assignable)
{
    using bp::detail::is_struct_assignable_v;

    static_assert(!is_struct_assignable_v<void, void>);
    static_assert(!is_struct_assignable_v<int, bp::tuple<int, std::string>>);
    static_assert(!is_struct_assignable_v<void, bp::tuple<int, std::string>>);
    static_assert(!is_struct_assignable_v<empty, bp::tuple<int, std::string>>);
    static_assert(!is_struct_assignable_v<int_, bp::tuple<int, std::string>>);
    static_assert(
        !is_struct_assignable_v<string_int, bp::tuple<int, std::string>>);
    static_assert(!is_struct_assignable_v<
                  string_int_double,
                  bp::tuple<std::string, int>>);
    static_assert(!is_struct_assignable_v<
                  string_int,
                  bp::tuple<std::string, int, double>>);
    static_assert(!is_struct_assignable_v<
                  string_int_double_priv,
                  bp::tuple<std::string, int, double>>);
    static_assert(!is_struct_assignable_v<
                  string_int_double_no_copy_move,
                  bp::tuple<std::string, int, double>>);

    static_assert(
        is_struct_assignable_v<int_string, bp::tuple<int, std::string>>);
    static_assert(
        is_struct_assignable_v<int_string, bp::tuple<short, char const *>>);

    static_assert(
        is_struct_assignable_v<string_int, bp::tuple<std::string, int>>);
    static_assert(
        is_struct_assignable_v<string_int, bp::tuple<char const *, short>>);

    static_assert(is_struct_assignable_v<
                  string_int_double,
                  bp::tuple<std::string, int, double>>);
    static_assert(is_struct_assignable_v<
                  string_int_double,
                  bp::tuple<char const *, short, float>>);
}

TEST(aggr_tuple_assignment, tuple_to_aggregate)
{
    {
        employee const expected_employee = {32, "Last", "First", 50000.0};
        bp::tuple<int, std::string, std::string, double> tup(
            32, "Last", "First", 50000.0);

        employee assignee;
        bp::detail::tuple_to_aggregate(
            assignee,
            std::move(tup),
            std::make_integer_sequence<
                int,
                bp::detail::tuple_size_<decltype(tup)>>());

        EXPECT_EQ(assignee.age, expected_employee.age);
        EXPECT_EQ(assignee.surname, expected_employee.surname);
        EXPECT_EQ(assignee.forename, expected_employee.forename);
        EXPECT_EQ(assignee.salary, expected_employee.salary);

        // Verify move.
        EXPECT_TRUE(bp::get(tup, bp::llong<1>{}).empty());
        EXPECT_TRUE(bp::get(tup, bp::llong<2>{}).empty());
    }
    {
        employee const expected_employee = {32, "Last", "First", 50000.0};
        bp::tuple<int, char const *, char const *, double> tup(
            32, "Last", "First", 50000.0);

        employee assignee;
        bp::detail::tuple_to_aggregate(
            assignee,
            std::move(tup),
            std::make_integer_sequence<
                int,
                bp::detail::tuple_size_<decltype(tup)>>());

        EXPECT_EQ(assignee.age, expected_employee.age);
        EXPECT_EQ(assignee.surname, expected_employee.surname);
        EXPECT_EQ(assignee.forename, expected_employee.forename);
        EXPECT_EQ(assignee.salary, expected_employee.salary);
    }
}

TEST(aggr_tuple_assignment, aggregate_to_tuple)
{
    employee assigner = {32, "Last", "First", 50000.0};

    auto tup = bp::detail::aggregate_to_tuple(std::move(assigner));

    EXPECT_EQ(bp::get(tup, bp::llong<0>{}), 32);
    EXPECT_EQ(bp::get(tup, bp::llong<1>{}), "Last");
    EXPECT_EQ(bp::get(tup, bp::llong<2>{}), "First");
    EXPECT_EQ(bp::get(tup, bp::llong<3>{}), 50000.0);

    // Verify move.
    EXPECT_TRUE(assigner.surname.empty());
    EXPECT_TRUE(assigner.forename.empty());
}
