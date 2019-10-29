// Copyright (C) 2018 T. Zachary Laine
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#include <boost/yaml/json.hpp>

#include <gtest/gtest.h>


using namespace boost::json;

double const number = 42.13;
std::string_view short_string = "short";
std::string_view long_string =
    "this is not going to fix within the SSO of value, so it'll have to go on "
    "the heap instead.";
object const json_object = {object::value_type{short_string, number}};
array const json_array = {number, short_string};

TEST(json_value, default_ctor)
{
    value v;
    EXPECT_EQ(v, value());
    EXPECT_FALSE(v != value());
    EXPECT_EQ(v.kind(), value_kind::null);
    EXPECT_TRUE(v.is_null());
    EXPECT_FALSE(v.is_boolean());
    EXPECT_FALSE(v.is_number());
    EXPECT_FALSE(v.is_string());
    EXPECT_FALSE(v.is_object());
    EXPECT_FALSE(v.is_array());
    EXPECT_EQ(get<null_t>(v), null_t{});
}

TEST(json_value, null_ctor)
{
    value v(null_t{});
    EXPECT_EQ(v, value());
    EXPECT_FALSE(v != value());
    EXPECT_EQ(v.kind(), value_kind::null);
    EXPECT_TRUE(v.is_null());
    EXPECT_FALSE(v.is_boolean());
    EXPECT_FALSE(v.is_number());
    EXPECT_FALSE(v.is_string());
    EXPECT_FALSE(v.is_object());
    EXPECT_FALSE(v.is_array());
    EXPECT_EQ(get<null_t>(v), null_t{});
}

TEST(json_value, bool_ctor)
{
    value v(true);
    EXPECT_NE(v, value());
    EXPECT_EQ(v, value(true));
    EXPECT_NE(v, value(false));
    EXPECT_EQ(v.kind(), value_kind::boolean);
    EXPECT_FALSE(v.is_null());
    EXPECT_TRUE(v.is_boolean());
    EXPECT_FALSE(v.is_number());
    EXPECT_FALSE(v.is_string());
    EXPECT_FALSE(v.is_object());
    EXPECT_FALSE(v.is_array());
    EXPECT_EQ(get<bool>(v), true);
}

TEST(json_value, number_ctor)
{
    value v(number);
    EXPECT_NE(v, value());
    EXPECT_EQ(v, value(number));
    EXPECT_NE(v, value(0.0));
    EXPECT_EQ(v.kind(), value_kind::number);
    EXPECT_FALSE(v.is_null());
    EXPECT_FALSE(v.is_boolean());
    EXPECT_TRUE(v.is_number());
    EXPECT_FALSE(v.is_string());
    EXPECT_FALSE(v.is_object());
    EXPECT_FALSE(v.is_array());
    EXPECT_EQ(get<double>(v), number);
}

TEST(json_value, string_ctor)
{
    {
        std::string s(short_string);
        value v(s);
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(short_string));
        EXPECT_NE(v, value(long_string));
        EXPECT_EQ(v.kind(), value_kind::string);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_TRUE(v.is_string());
        EXPECT_FALSE(v.is_object());
        EXPECT_FALSE(v.is_array());
        EXPECT_EQ(get<std::string_view>(v), short_string);
    }
    {
        std::string s(long_string);
        value v(s);
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(long_string));
        EXPECT_NE(v, value(short_string));
        EXPECT_EQ(v.kind(), value_kind::string);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_TRUE(v.is_string());
        EXPECT_FALSE(v.is_object());
        EXPECT_FALSE(v.is_array());
        EXPECT_EQ(get<std::string_view>(v), long_string);
    }

    {
        std::vector<char> s(short_string.begin(), short_string.end());
        value v(s);
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(short_string));
        EXPECT_NE(v, value(long_string));
        EXPECT_EQ(v.kind(), value_kind::string);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_TRUE(v.is_string());
        EXPECT_FALSE(v.is_object());
        EXPECT_FALSE(v.is_array());
        EXPECT_EQ(get<std::string_view>(v), short_string);
    }
    {
        std::vector<char> s(long_string.begin(), long_string.end());
        value v(s);
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(long_string));
        EXPECT_NE(v, value(short_string));
        EXPECT_EQ(v.kind(), value_kind::string);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_TRUE(v.is_string());
        EXPECT_FALSE(v.is_object());
        EXPECT_FALSE(v.is_array());
        EXPECT_EQ(get<std::string_view>(v), long_string);
    }

    {
        value v(std::string{short_string});
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(short_string));
        EXPECT_NE(v, value(long_string));
        EXPECT_EQ(v.kind(), value_kind::string);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_TRUE(v.is_string());
        EXPECT_FALSE(v.is_object());
        EXPECT_FALSE(v.is_array());
        EXPECT_EQ(get<std::string_view>(v), short_string);
    }
    {
        value v(std::string{long_string});
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(long_string));
        EXPECT_NE(v, value(short_string));
        EXPECT_EQ(v.kind(), value_kind::string);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_TRUE(v.is_string());
        EXPECT_FALSE(v.is_object());
        EXPECT_FALSE(v.is_array());
        EXPECT_EQ(get<std::string_view>(v), long_string);
    }

    {
        value v(short_string);
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(short_string));
        EXPECT_NE(v, value(long_string));
        EXPECT_EQ(v.kind(), value_kind::string);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_TRUE(v.is_string());
        EXPECT_FALSE(v.is_object());
        EXPECT_FALSE(v.is_array());
        EXPECT_EQ(get<std::string_view>(v), short_string);
    }
    {
        value v(long_string);
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(long_string));
        EXPECT_NE(v, value(short_string));
        EXPECT_EQ(v.kind(), value_kind::string);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_TRUE(v.is_string());
        EXPECT_FALSE(v.is_object());
        EXPECT_FALSE(v.is_array());
        EXPECT_EQ(get<std::string_view>(v), long_string);
    }
}

TEST(json_value, object_ctor)
{
    {
        value v(json_object);
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(json_object));
        EXPECT_NE(v, value(object()));
        EXPECT_EQ(v.kind(), value_kind::object);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_FALSE(v.is_string());
        EXPECT_TRUE(v.is_object());
        EXPECT_FALSE(v.is_array());
        EXPECT_EQ(get<object>(v), json_object);
    }
    {
        value v(object{json_object});
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(json_object));
        EXPECT_NE(v, value(object()));
        EXPECT_EQ(v.kind(), value_kind::object);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_FALSE(v.is_string());
        EXPECT_TRUE(v.is_object());
        EXPECT_FALSE(v.is_array());
        EXPECT_EQ(get<object>(v), json_object);
    }
}

TEST(json_value, array_ctor)
{
    {
        value v(json_array);
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(json_array));
        EXPECT_NE(v, value(array()));
        EXPECT_EQ(v.kind(), value_kind::array);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_object());
        EXPECT_TRUE(v.is_array());
        EXPECT_EQ(get<array>(v), json_array);
    }
    {
        array a = json_array;
        value v(std::move(a));
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(json_array));
        EXPECT_NE(v, value(array()));
        EXPECT_EQ(v.kind(), value_kind::array);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_object());
        EXPECT_TRUE(v.is_array());
        EXPECT_EQ(get<array>(v), json_array);
    }
}

TEST(json_value, copy_ctor)
{
    value v_default;
    value v_true(true);
    value v_number(number);
    value v_short_string(short_string);
    value v_long_string(long_string);
    value v_object(json_object);
    value v_array(json_array);

    {
        value v(v_default);
        EXPECT_EQ(v, value());
        EXPECT_FALSE(v != value());
        EXPECT_EQ(v.kind(), value_kind::null);
        EXPECT_TRUE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_object());
        EXPECT_FALSE(v.is_array());
        EXPECT_EQ(get<null_t>(v), null_t{});
    }
    {
        value v(v_true);
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(true));
        EXPECT_NE(v, value(false));
        EXPECT_EQ(v.kind(), value_kind::boolean);
        EXPECT_FALSE(v.is_null());
        EXPECT_TRUE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_object());
        EXPECT_FALSE(v.is_array());
        EXPECT_EQ(get<bool>(v), true);
    }
    {
        value v(v_number);
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(number));
        EXPECT_NE(v, value(0.0));
        EXPECT_EQ(v.kind(), value_kind::number);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_TRUE(v.is_number());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_object());
        EXPECT_FALSE(v.is_array());
        EXPECT_EQ(get<double>(v), number);
    }
    {
        value v(v_short_string);
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(short_string));
        EXPECT_NE(v, value(long_string));
        EXPECT_EQ(v.kind(), value_kind::string);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_TRUE(v.is_string());
        EXPECT_FALSE(v.is_object());
        EXPECT_FALSE(v.is_array());
        EXPECT_EQ(get<std::string_view>(v), short_string);
    }
    {
        value v(v_long_string);
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(long_string));
        EXPECT_NE(v, value(short_string));
        EXPECT_EQ(v.kind(), value_kind::string);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_TRUE(v.is_string());
        EXPECT_FALSE(v.is_object());
        EXPECT_FALSE(v.is_array());
        EXPECT_EQ(get<std::string_view>(v), long_string);
    }
    {
        value v(v_object);
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(json_object));
        EXPECT_NE(v, value(object()));
        EXPECT_EQ(v.kind(), value_kind::object);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_FALSE(v.is_string());
        EXPECT_TRUE(v.is_object());
        EXPECT_FALSE(v.is_array());
        EXPECT_EQ(get<object>(v), json_object);
    }
    {
        value v(v_array);
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(json_array));
        EXPECT_NE(v, value(array()));
        EXPECT_EQ(v.kind(), value_kind::array);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_object());
        EXPECT_TRUE(v.is_array());
        EXPECT_EQ(get<array>(v), json_array);
    }
}

TEST(json_value, move_ctor)
{
    value v_default;
    value v_true(true);
    value v_number(number);
    value v_short_string(short_string);
    value v_long_string(long_string);
    value v_object(json_object);
    value v_array(json_array);

    {
        value v(std::move(v_default));
        EXPECT_EQ(v, value());
        EXPECT_FALSE(v != value());
        EXPECT_EQ(v.kind(), value_kind::null);
        EXPECT_TRUE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_object());
        EXPECT_FALSE(v.is_array());
        EXPECT_EQ(get<null_t>(v), null_t{});
    }
    {
        value v(std::move(v_true));
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(true));
        EXPECT_NE(v, value(false));
        EXPECT_EQ(v.kind(), value_kind::boolean);
        EXPECT_FALSE(v.is_null());
        EXPECT_TRUE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_object());
        EXPECT_FALSE(v.is_array());
        EXPECT_EQ(get<bool>(v), true);
    }
    {
        value v(std::move(v_number));
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(number));
        EXPECT_NE(v, value(0.0));
        EXPECT_EQ(v.kind(), value_kind::number);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_TRUE(v.is_number());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_object());
        EXPECT_FALSE(v.is_array());
        EXPECT_EQ(get<double>(v), number);
    }
    {
        value v(std::move(v_short_string));
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(short_string));
        EXPECT_NE(v, value(long_string));
        EXPECT_EQ(v.kind(), value_kind::string);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_TRUE(v.is_string());
        EXPECT_FALSE(v.is_object());
        EXPECT_FALSE(v.is_array());
        EXPECT_EQ(get<std::string_view>(v), short_string);
    }
    {
        value v(std::move(v_long_string));
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(long_string));
        EXPECT_NE(v, value(short_string));
        EXPECT_EQ(v.kind(), value_kind::string);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_TRUE(v.is_string());
        EXPECT_FALSE(v.is_object());
        EXPECT_FALSE(v.is_array());
        EXPECT_EQ(get<std::string_view>(v), long_string);
    }
    {
        value v(std::move(v_object));
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(json_object));
        EXPECT_NE(v, value(object()));
        EXPECT_EQ(v.kind(), value_kind::object);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_FALSE(v.is_string());
        EXPECT_TRUE(v.is_object());
        EXPECT_FALSE(v.is_array());
        EXPECT_EQ(get<object>(v), json_object);
    }
    {
        value v(std::move(v_array));
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(json_array));
        EXPECT_NE(v, value(array()));
        EXPECT_EQ(v.kind(), value_kind::array);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_object());
        EXPECT_TRUE(v.is_array());
        EXPECT_EQ(get<array>(v), json_array);
    }
}

TEST(json_value, copy_assign)
{
    value v_default;
    value v_true(true);
    value v_number(number);
    value v_short_string(short_string);
    value v_long_string(long_string);
    value v_object(json_object);
    value v_array(json_array);

    // assign to local
    {
        value v(true);
        v = v_default;
        EXPECT_EQ(v, value());
        EXPECT_FALSE(v != value());
        EXPECT_EQ(v.kind(), value_kind::null);
        EXPECT_TRUE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_object());
        EXPECT_FALSE(v.is_array());
        EXPECT_EQ(get<null_t>(v), null_t{});
    }
    {
        value v(number);
        v = v_true;
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(true));
        EXPECT_NE(v, value(false));
        EXPECT_EQ(v.kind(), value_kind::boolean);
        EXPECT_FALSE(v.is_null());
        EXPECT_TRUE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_object());
        EXPECT_FALSE(v.is_array());
        EXPECT_EQ(get<bool>(v), true);
    }
    {
        value v(short_string);
        v = v_number;
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(number));
        EXPECT_NE(v, value(0.0));
        EXPECT_EQ(v.kind(), value_kind::number);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_TRUE(v.is_number());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_object());
        EXPECT_FALSE(v.is_array());
        EXPECT_EQ(get<double>(v), number);
    }
    {
        value v;
        v = v_short_string;
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(short_string));
        EXPECT_NE(v, value(long_string));
        EXPECT_EQ(v.kind(), value_kind::string);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_TRUE(v.is_string());
        EXPECT_FALSE(v.is_object());
        EXPECT_FALSE(v.is_array());
        EXPECT_EQ(get<std::string_view>(v), short_string);
    }
    {
        value v(false);
        v = v_long_string;
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(long_string));
        EXPECT_NE(v, value(short_string));
        EXPECT_EQ(v.kind(), value_kind::string);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_TRUE(v.is_string());
        EXPECT_FALSE(v.is_object());
        EXPECT_FALSE(v.is_array());
        EXPECT_EQ(get<std::string_view>(v), long_string);
    }
    {
        value v(number);
        v = v_object;
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(json_object));
        EXPECT_NE(v, value(object()));
        EXPECT_EQ(v.kind(), value_kind::object);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_FALSE(v.is_string());
        EXPECT_TRUE(v.is_object());
        EXPECT_FALSE(v.is_array());
        EXPECT_EQ(get<object>(v), json_object);
    }
    {
        value v;
        v = v_array;
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(json_array));
        EXPECT_NE(v, value(array()));
        EXPECT_EQ(v.kind(), value_kind::array);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_object());
        EXPECT_TRUE(v.is_array());
        EXPECT_EQ(get<array>(v), json_array);
    }

    // assign to remote
    {
        value v(json_object);
        v = v_default;
        EXPECT_EQ(v, value());
        EXPECT_FALSE(v != value());
        EXPECT_EQ(v.kind(), value_kind::null);
        EXPECT_TRUE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_object());
        EXPECT_FALSE(v.is_array());
        EXPECT_EQ(get<null_t>(v), null_t{});
    }
    {
        value v(json_array);
        v = v_true;
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(true));
        EXPECT_NE(v, value(false));
        EXPECT_EQ(v.kind(), value_kind::boolean);
        EXPECT_FALSE(v.is_null());
        EXPECT_TRUE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_object());
        EXPECT_FALSE(v.is_array());
        EXPECT_EQ(get<bool>(v), true);
    }
    {
        value v(long_string);
        v = v_number;
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(number));
        EXPECT_NE(v, value(0.0));
        EXPECT_EQ(v.kind(), value_kind::number);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_TRUE(v.is_number());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_object());
        EXPECT_FALSE(v.is_array());
        EXPECT_EQ(get<double>(v), number);
    }
    {
        value v(json_object);
        v = v_short_string;
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(short_string));
        EXPECT_NE(v, value(long_string));
        EXPECT_EQ(v.kind(), value_kind::string);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_TRUE(v.is_string());
        EXPECT_FALSE(v.is_object());
        EXPECT_FALSE(v.is_array());
        EXPECT_EQ(get<std::string_view>(v), short_string);
    }
    {
        value v(json_array);
        v = v_long_string;
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(long_string));
        EXPECT_NE(v, value(short_string));
        EXPECT_EQ(v.kind(), value_kind::string);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_TRUE(v.is_string());
        EXPECT_FALSE(v.is_object());
        EXPECT_FALSE(v.is_array());
        EXPECT_EQ(get<std::string_view>(v), long_string);
    }
    {
        value v(long_string);
        v = v_object;
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(json_object));
        EXPECT_NE(v, value(object()));
        EXPECT_EQ(v.kind(), value_kind::object);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_FALSE(v.is_string());
        EXPECT_TRUE(v.is_object());
        EXPECT_FALSE(v.is_array());
        EXPECT_EQ(get<object>(v), json_object);
    }
    {
        value v(json_object);
        v = v_array;
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(json_array));
        EXPECT_NE(v, value(array()));
        EXPECT_EQ(v.kind(), value_kind::array);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_number());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_object());
        EXPECT_TRUE(v.is_array());
        EXPECT_EQ(get<array>(v), json_array);
    }
}

TEST(json_value, move_assign)
{
    // assign to local
    {
        value v_default;
        value v_true(true);
        value v_number(number);
        value v_short_string(short_string);
        value v_long_string(long_string);
        value v_object(json_object);
        value v_array(json_array);

        {
            value v(true);
            v = std::move(v_default);
            EXPECT_EQ(v, value());
            EXPECT_FALSE(v != value());
            EXPECT_EQ(v.kind(), value_kind::null);
            EXPECT_TRUE(v.is_null());
            EXPECT_FALSE(v.is_boolean());
            EXPECT_FALSE(v.is_number());
            EXPECT_FALSE(v.is_string());
            EXPECT_FALSE(v.is_object());
            EXPECT_FALSE(v.is_array());
            EXPECT_EQ(get<null_t>(v), null_t{});
        }
        {
            value v(number);
            v = std::move(v_true);
            EXPECT_NE(v, value());
            EXPECT_EQ(v, value(true));
            EXPECT_NE(v, value(false));
            EXPECT_EQ(v.kind(), value_kind::boolean);
            EXPECT_FALSE(v.is_null());
            EXPECT_TRUE(v.is_boolean());
            EXPECT_FALSE(v.is_number());
            EXPECT_FALSE(v.is_string());
            EXPECT_FALSE(v.is_object());
            EXPECT_FALSE(v.is_array());
            EXPECT_EQ(get<bool>(v), true);
        }
        {
            value v(short_string);
            v = std::move(v_number);
            EXPECT_NE(v, value());
            EXPECT_EQ(v, value(number));
            EXPECT_NE(v, value(0.0));
            EXPECT_EQ(v.kind(), value_kind::number);
            EXPECT_FALSE(v.is_null());
            EXPECT_FALSE(v.is_boolean());
            EXPECT_TRUE(v.is_number());
            EXPECT_FALSE(v.is_string());
            EXPECT_FALSE(v.is_object());
            EXPECT_FALSE(v.is_array());
            EXPECT_EQ(get<double>(v), number);
        }
        {
            value v;
            v = std::move(v_short_string);
            EXPECT_NE(v, value());
            EXPECT_EQ(v, value(short_string));
            EXPECT_NE(v, value(long_string));
            EXPECT_EQ(v.kind(), value_kind::string);
            EXPECT_FALSE(v.is_null());
            EXPECT_FALSE(v.is_boolean());
            EXPECT_FALSE(v.is_number());
            EXPECT_TRUE(v.is_string());
            EXPECT_FALSE(v.is_object());
            EXPECT_FALSE(v.is_array());
            EXPECT_EQ(get<std::string_view>(v), short_string);
        }
        {
            value v(false);
            v = std::move(v_long_string);
            EXPECT_NE(v, value());
            EXPECT_EQ(v, value(long_string));
            EXPECT_NE(v, value(short_string));
            EXPECT_EQ(v.kind(), value_kind::string);
            EXPECT_FALSE(v.is_null());
            EXPECT_FALSE(v.is_boolean());
            EXPECT_FALSE(v.is_number());
            EXPECT_TRUE(v.is_string());
            EXPECT_FALSE(v.is_object());
            EXPECT_FALSE(v.is_array());
            EXPECT_EQ(get<std::string_view>(v), long_string);
        }
        {
            value v(number);
            v = std::move(v_object);
            EXPECT_NE(v, value());
            EXPECT_EQ(v, value(json_object));
            EXPECT_NE(v, value(object()));
            EXPECT_EQ(v.kind(), value_kind::object);
            EXPECT_FALSE(v.is_null());
            EXPECT_FALSE(v.is_boolean());
            EXPECT_FALSE(v.is_number());
            EXPECT_FALSE(v.is_string());
            EXPECT_TRUE(v.is_object());
            EXPECT_FALSE(v.is_array());
            EXPECT_EQ(get<object>(v), json_object);
        }
        {
            value v;
            v = std::move(v_array);
            EXPECT_NE(v, value());
            EXPECT_EQ(v, value(json_array));
            EXPECT_NE(v, value(array()));
            EXPECT_EQ(v.kind(), value_kind::array);
            EXPECT_FALSE(v.is_null());
            EXPECT_FALSE(v.is_boolean());
            EXPECT_FALSE(v.is_number());
            EXPECT_FALSE(v.is_string());
            EXPECT_FALSE(v.is_object());
            EXPECT_TRUE(v.is_array());
            EXPECT_EQ(get<array>(v), json_array);
        }
    }

    // assign to remote
    {
        value v_default;
        value v_true(true);
        value v_number(number);
        value v_short_string(short_string);
        value v_long_string(long_string);
        value v_object(json_object);
        value v_array(json_array);

        {
            value v(json_object);
            v = std::move(v_default);
            EXPECT_EQ(v, value());
            EXPECT_FALSE(v != value());
            EXPECT_EQ(v.kind(), value_kind::null);
            EXPECT_TRUE(v.is_null());
            EXPECT_FALSE(v.is_boolean());
            EXPECT_FALSE(v.is_number());
            EXPECT_FALSE(v.is_string());
            EXPECT_FALSE(v.is_object());
            EXPECT_FALSE(v.is_array());
            EXPECT_EQ(get<null_t>(v), null_t{});
        }
        {
            value v(json_array);
            v = std::move(v_true);
            EXPECT_NE(v, value());
            EXPECT_EQ(v, value(true));
            EXPECT_NE(v, value(false));
            EXPECT_EQ(v.kind(), value_kind::boolean);
            EXPECT_FALSE(v.is_null());
            EXPECT_TRUE(v.is_boolean());
            EXPECT_FALSE(v.is_number());
            EXPECT_FALSE(v.is_string());
            EXPECT_FALSE(v.is_object());
            EXPECT_FALSE(v.is_array());
            EXPECT_EQ(get<bool>(v), true);
        }
        {
            value v(long_string);
            v = std::move(v_number);
            EXPECT_NE(v, value());
            EXPECT_EQ(v, value(number));
            EXPECT_NE(v, value(0.0));
            EXPECT_EQ(v.kind(), value_kind::number);
            EXPECT_FALSE(v.is_null());
            EXPECT_FALSE(v.is_boolean());
            EXPECT_TRUE(v.is_number());
            EXPECT_FALSE(v.is_string());
            EXPECT_FALSE(v.is_object());
            EXPECT_FALSE(v.is_array());
            EXPECT_EQ(get<double>(v), number);
        }
        {
            value v(json_object);
            v = std::move(v_short_string);
            EXPECT_NE(v, value());
            EXPECT_EQ(v, value(short_string));
            EXPECT_NE(v, value(long_string));
            EXPECT_EQ(v.kind(), value_kind::string);
            EXPECT_FALSE(v.is_null());
            EXPECT_FALSE(v.is_boolean());
            EXPECT_FALSE(v.is_number());
            EXPECT_TRUE(v.is_string());
            EXPECT_FALSE(v.is_object());
            EXPECT_FALSE(v.is_array());
            EXPECT_EQ(get<std::string_view>(v), short_string);
        }
        {
            value v(json_array);
            v = std::move(v_long_string);
            EXPECT_NE(v, value());
            EXPECT_EQ(v, value(long_string));
            EXPECT_NE(v, value(short_string));
            EXPECT_EQ(v.kind(), value_kind::string);
            EXPECT_FALSE(v.is_null());
            EXPECT_FALSE(v.is_boolean());
            EXPECT_FALSE(v.is_number());
            EXPECT_TRUE(v.is_string());
            EXPECT_FALSE(v.is_object());
            EXPECT_FALSE(v.is_array());
            EXPECT_EQ(get<std::string_view>(v), long_string);
        }
        {
            value v(long_string);
            v = std::move(v_object);
            EXPECT_NE(v, value());
            EXPECT_EQ(v, value(json_object));
            EXPECT_NE(v, value(object()));
            EXPECT_EQ(v.kind(), value_kind::object);
            EXPECT_FALSE(v.is_null());
            EXPECT_FALSE(v.is_boolean());
            EXPECT_FALSE(v.is_number());
            EXPECT_FALSE(v.is_string());
            EXPECT_TRUE(v.is_object());
            EXPECT_FALSE(v.is_array());
            EXPECT_EQ(get<object>(v), json_object);
        }
        {
            value v(json_object);
            v = std::move(v_array);
            EXPECT_NE(v, value());
            EXPECT_EQ(v, value(json_array));
            EXPECT_NE(v, value(array()));
            EXPECT_EQ(v.kind(), value_kind::array);
            EXPECT_FALSE(v.is_null());
            EXPECT_FALSE(v.is_boolean());
            EXPECT_FALSE(v.is_number());
            EXPECT_FALSE(v.is_string());
            EXPECT_FALSE(v.is_object());
            EXPECT_TRUE(v.is_array());
            EXPECT_EQ(get<array>(v), json_array);
        }
    }
}
