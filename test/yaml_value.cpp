// Copyright (C) 2018 T. Zachary Laine
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#include <boost/yaml/yaml.hpp>

#include <gtest/gtest.h>


using namespace boost::yaml;

struct udt
{
    int data_;

    bool operator==(udt const & rhs) const noexcept
    {
        return data_ == rhs.data_;
    }
    bool operator!=(udt const & rhs) const noexcept { return !(*this == rhs); }
};

int const int_num = 42;
double const double_num = 42.13;
std::string_view short_string = "short";
std::string_view long_string =
    "this is not going to fix within the SSO of value, so it'll have to go on "
    "the heap instead.";
map const yaml_map = {map::value_type{int_num, double_num}};
seq const yaml_seq = {double_num, short_string};
alias const yaml_alias{"first", std::make_shared<value const>(value("second"))};
property_node const yaml_property_node{{"tag", "anchor"}, value(int_num)};
udt const user_defined{-1};

TEST(yaml_value, default_ctor)
{
    value v;
    EXPECT_EQ(v, value());
    EXPECT_FALSE(v != value());
    EXPECT_EQ(v.kind(), value_kind::null);
    EXPECT_TRUE(v.is_null());
    EXPECT_FALSE(v.is_boolean());
    EXPECT_FALSE(v.is_int());
    EXPECT_FALSE(v.is_double());
    EXPECT_FALSE(v.is_string());
    EXPECT_FALSE(v.is_map());
    EXPECT_FALSE(v.is_seq());
    EXPECT_FALSE(v.is_alias());
    EXPECT_FALSE(v.is_property_node());
    EXPECT_FALSE(v.is_user_defined());
    EXPECT_FALSE(v.is<udt>());
    EXPECT_EQ(get<null_t>(v), null_t{});
}

TEST(yaml_value, null_ctor)
{
    value v(null_t{});
    EXPECT_EQ(v, value());
    EXPECT_FALSE(v != value());
    EXPECT_EQ(v.kind(), value_kind::null);
    EXPECT_TRUE(v.is_null());
    EXPECT_FALSE(v.is_boolean());
    EXPECT_FALSE(v.is_int());
    EXPECT_FALSE(v.is_double());
    EXPECT_FALSE(v.is_string());
    EXPECT_FALSE(v.is_map());
    EXPECT_FALSE(v.is_seq());
    EXPECT_FALSE(v.is_alias());
    EXPECT_FALSE(v.is_property_node());
    EXPECT_FALSE(v.is_user_defined());
    EXPECT_FALSE(v.is<udt>());
    EXPECT_EQ(get<null_t>(v), null_t{});
}

TEST(yaml_value, bool_ctor)
{
    value v(true);
    EXPECT_NE(v, value());
    EXPECT_EQ(v, value(true));
    EXPECT_NE(v, value(false));
    EXPECT_EQ(v.kind(), value_kind::boolean);
    EXPECT_FALSE(v.is_null());
    EXPECT_TRUE(v.is_boolean());
    EXPECT_FALSE(v.is_int());
    EXPECT_FALSE(v.is_double());
    EXPECT_FALSE(v.is_string());
    EXPECT_FALSE(v.is_map());
    EXPECT_FALSE(v.is_seq());
    EXPECT_FALSE(v.is_alias());
    EXPECT_FALSE(v.is_property_node());
    EXPECT_FALSE(v.is_user_defined());
    EXPECT_FALSE(v.is<udt>());
    EXPECT_EQ(get<bool>(v), true);
}

TEST(yaml_value, int_ctor)
{
    value v(int_num);
    EXPECT_NE(v, value());
    EXPECT_EQ(v, value(int_num));
    EXPECT_NE(v, value(0));
    EXPECT_EQ(v.kind(), value_kind::int_);
    EXPECT_FALSE(v.is_null());
    EXPECT_FALSE(v.is_boolean());
    EXPECT_TRUE(v.is_int());
    EXPECT_FALSE(v.is_double());
    EXPECT_FALSE(v.is_string());
    EXPECT_FALSE(v.is_map());
    EXPECT_FALSE(v.is_seq());
    EXPECT_FALSE(v.is_alias());
    EXPECT_FALSE(v.is_property_node());
    EXPECT_FALSE(v.is_user_defined());
    EXPECT_FALSE(v.is<udt>());
    EXPECT_EQ(get<int>(v), int_num);
}

TEST(yaml_value, double_ctor)
{
    value v(double_num);
    EXPECT_NE(v, value());
    EXPECT_EQ(v, value(double_num));
    EXPECT_NE(v, value(0.0));
    EXPECT_EQ(v.kind(), value_kind::double_);
    EXPECT_FALSE(v.is_null());
    EXPECT_FALSE(v.is_boolean());
    EXPECT_FALSE(v.is_int());
    EXPECT_TRUE(v.is_double());
    EXPECT_FALSE(v.is_string());
    EXPECT_FALSE(v.is_map());
    EXPECT_FALSE(v.is_seq());
    EXPECT_FALSE(v.is_alias());
    EXPECT_FALSE(v.is_property_node());
    EXPECT_FALSE(v.is_user_defined());
    EXPECT_FALSE(v.is<udt>());
    EXPECT_EQ(get<double>(v), double_num);
}

TEST(yaml_value, string_ctor)
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
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_TRUE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
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
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_TRUE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
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
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_TRUE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
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
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_TRUE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
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
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_TRUE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
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
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_TRUE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
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
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_TRUE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
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
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_TRUE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
        EXPECT_EQ(get<std::string_view>(v), long_string);
    }
}

TEST(yaml_value, map_ctor)
{
    {
        value v(yaml_map);
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(yaml_map));
        EXPECT_NE(v, value(map()));
        EXPECT_EQ(v.kind(), value_kind::map);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_FALSE(v.is_string());
        EXPECT_TRUE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
        EXPECT_EQ(get<map>(v), yaml_map);
    }
    {
        value v(map{yaml_map});
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(yaml_map));
        EXPECT_NE(v, value(map()));
        EXPECT_EQ(v.kind(), value_kind::map);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_FALSE(v.is_string());
        EXPECT_TRUE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
        EXPECT_EQ(get<map>(v), yaml_map);
    }
}

TEST(yaml_value, seq_ctor)
{
    {
        value v(yaml_seq);
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(yaml_seq));
        EXPECT_NE(v, value(seq()));
        EXPECT_EQ(v.kind(), value_kind::seq);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_TRUE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
        EXPECT_EQ(get<seq>(v), yaml_seq);
    }
    {
        seq a = yaml_seq;
        value v(std::move(a));
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(yaml_seq));
        EXPECT_NE(v, value(seq()));
        EXPECT_EQ(v.kind(), value_kind::seq);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_TRUE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
        EXPECT_EQ(get<seq>(v), yaml_seq);
    }
}

TEST(yaml_value, udt_ctor)
{
    value v(user_defined);
    EXPECT_NE(v, value());
    EXPECT_EQ(v, value(user_defined));
    EXPECT_NE(v, value(udt{}));
    EXPECT_EQ(v.kind(), value_kind::user_defined);
    EXPECT_FALSE(v.is_null());
    EXPECT_FALSE(v.is_boolean());
    EXPECT_FALSE(v.is_int());
    EXPECT_FALSE(v.is_double());
    EXPECT_FALSE(v.is_string());
    EXPECT_FALSE(v.is_map());
    EXPECT_FALSE(v.is_seq());
    EXPECT_FALSE(v.is_alias());
    EXPECT_FALSE(v.is_property_node());
    EXPECT_TRUE(v.is_user_defined());
    EXPECT_TRUE(v.is<udt>());
    EXPECT_EQ(get<udt>(v), user_defined);
}

TEST(yaml_value, copy_ctor)
{
    value v_default;
    value v_true(true);
    value v_int(int_num);
    value v_double(double_num);
    value v_short_string(short_string);
    value v_long_string(long_string);
    value v_map(yaml_map);
    value v_seq(yaml_seq);

    {
        value v(v_default);
        EXPECT_EQ(v, value());
        EXPECT_FALSE(v != value());
        EXPECT_EQ(v.kind(), value_kind::null);
        EXPECT_TRUE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
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
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
        EXPECT_EQ(get<bool>(v), true);
    }
    {
        value v(v_double);
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(double_num));
        EXPECT_NE(v, value(0.0));
        EXPECT_EQ(v.kind(), value_kind::double_);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_int());
        EXPECT_TRUE(v.is_double());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
        EXPECT_EQ(get<double>(v), double_num);
    }
    {
        value v(v_int);
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(int_num));
        EXPECT_NE(v, value(0));
        EXPECT_EQ(v.kind(), value_kind::int_);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_TRUE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
        EXPECT_EQ(get<int>(v), int_num);
    }
    {
        value v(v_short_string);
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(short_string));
        EXPECT_NE(v, value(long_string));
        EXPECT_EQ(v.kind(), value_kind::string);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_TRUE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
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
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_TRUE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
        EXPECT_EQ(get<std::string_view>(v), long_string);
    }
    {
        value v(v_map);
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(yaml_map));
        EXPECT_NE(v, value(map()));
        EXPECT_EQ(v.kind(), value_kind::map);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_FALSE(v.is_string());
        EXPECT_TRUE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
        EXPECT_EQ(get<map>(v), yaml_map);
    }
    {
        value v(v_seq);
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(yaml_seq));
        EXPECT_NE(v, value(seq()));
        EXPECT_EQ(v.kind(), value_kind::seq);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_TRUE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
        EXPECT_EQ(get<seq>(v), yaml_seq);
    }
}

TEST(yaml_value, move_ctor)
{
    value v_default;
    value v_true(true);
    value v_double(double_num);
    value v_int(int_num);
    value v_short_string(short_string);
    value v_long_string(long_string);
    value v_map(yaml_map);
    value v_seq(yaml_seq);

    {
        value v(std::move(v_default));
        EXPECT_EQ(v, value());
        EXPECT_FALSE(v != value());
        EXPECT_EQ(v.kind(), value_kind::null);
        EXPECT_TRUE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
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
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
        EXPECT_EQ(get<bool>(v), true);
    }
    {
        value v(std::move(v_int));
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(int_num));
        EXPECT_NE(v, value(0));
        EXPECT_EQ(v.kind(), value_kind::int_);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_TRUE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
        EXPECT_EQ(get<int>(v), int_num);
    }
    {
        value v(std::move(v_double));
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(double_num));
        EXPECT_NE(v, value(0.0));
        EXPECT_EQ(v.kind(), value_kind::double_);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_int());
        EXPECT_TRUE(v.is_double());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
        EXPECT_EQ(get<double>(v), double_num);
    }
    {
        value v(std::move(v_short_string));
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(short_string));
        EXPECT_NE(v, value(long_string));
        EXPECT_EQ(v.kind(), value_kind::string);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_TRUE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
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
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_TRUE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
        EXPECT_EQ(get<std::string_view>(v), long_string);
    }
    {
        value v(std::move(v_map));
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(yaml_map));
        EXPECT_NE(v, value(map()));
        EXPECT_EQ(v.kind(), value_kind::map);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_FALSE(v.is_string());
        EXPECT_TRUE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
        EXPECT_EQ(get<map>(v), yaml_map);
    }
    {
        value v(std::move(v_seq));
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(yaml_seq));
        EXPECT_NE(v, value(seq()));
        EXPECT_EQ(v.kind(), value_kind::seq);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_TRUE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
        EXPECT_EQ(get<seq>(v), yaml_seq);
    }
}

TEST(yaml_value, copy_assign)
{
    value v_default;
    value v_true(true);
    value v_int(int_num);
    value v_double(double_num);
    value v_short_string(short_string);
    value v_long_string(long_string);
    value v_map(yaml_map);
    value v_seq(yaml_seq);

    // assign to local
    {
        value v(true);
        v = v_default;
        EXPECT_EQ(v, value());
        EXPECT_FALSE(v != value());
        EXPECT_EQ(v.kind(), value_kind::null);
        EXPECT_TRUE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
        EXPECT_EQ(get<null_t>(v), null_t{});
    }
    {
        value v(double_num);
        v = v_true;
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(true));
        EXPECT_NE(v, value(false));
        EXPECT_EQ(v.kind(), value_kind::boolean);
        EXPECT_FALSE(v.is_null());
        EXPECT_TRUE(v.is_boolean());
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
        EXPECT_EQ(get<bool>(v), true);
    }
    {
        value v(short_string);
        v = v_int;
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(int_num));
        EXPECT_NE(v, value(0.0));
        EXPECT_EQ(v.kind(), value_kind::int_);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_TRUE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
        EXPECT_EQ(get<int>(v), int_num);
    }
    {
        value v(short_string);
        v = v_double;
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(double_num));
        EXPECT_NE(v, value(0.0));
        EXPECT_EQ(v.kind(), value_kind::double_);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_int());
        EXPECT_TRUE(v.is_double());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
        EXPECT_EQ(get<double>(v), double_num);
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
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_TRUE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
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
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_TRUE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
        EXPECT_EQ(get<std::string_view>(v), long_string);
    }
    {
        value v(double_num);
        v = v_map;
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(yaml_map));
        EXPECT_NE(v, value(map()));
        EXPECT_EQ(v.kind(), value_kind::map);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_FALSE(v.is_string());
        EXPECT_TRUE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
        EXPECT_EQ(get<map>(v), yaml_map);
    }
    {
        value v;
        v = v_seq;
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(yaml_seq));
        EXPECT_NE(v, value(seq()));
        EXPECT_EQ(v.kind(), value_kind::seq);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_TRUE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
        EXPECT_EQ(get<seq>(v), yaml_seq);
    }

    // assign to remote
    {
        value v(yaml_map);
        v = v_default;
        EXPECT_EQ(v, value());
        EXPECT_FALSE(v != value());
        EXPECT_EQ(v.kind(), value_kind::null);
        EXPECT_TRUE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
        EXPECT_EQ(get<null_t>(v), null_t{});
    }
    {
        value v(yaml_seq);
        v = v_true;
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(true));
        EXPECT_NE(v, value(false));
        EXPECT_EQ(v.kind(), value_kind::boolean);
        EXPECT_FALSE(v.is_null());
        EXPECT_TRUE(v.is_boolean());
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
        EXPECT_EQ(get<bool>(v), true);
    }
    {
        value v(long_string);
        v = v_int;
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(int_num));
        EXPECT_NE(v, value(0.0));
        EXPECT_EQ(v.kind(), value_kind::int_);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_TRUE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
        EXPECT_EQ(get<int>(v), int_num);
    }
    {
        value v(long_string);
        v = v_double;
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(double_num));
        EXPECT_NE(v, value(0.0));
        EXPECT_EQ(v.kind(), value_kind::double_);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_int());
        EXPECT_TRUE(v.is_double());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
        EXPECT_EQ(get<double>(v), double_num);
    }
    {
        value v(yaml_map);
        v = v_short_string;
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(short_string));
        EXPECT_NE(v, value(long_string));
        EXPECT_EQ(v.kind(), value_kind::string);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_TRUE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
        EXPECT_EQ(get<std::string_view>(v), short_string);
    }
    {
        value v(yaml_seq);
        v = v_long_string;
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(long_string));
        EXPECT_NE(v, value(short_string));
        EXPECT_EQ(v.kind(), value_kind::string);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_TRUE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
        EXPECT_EQ(get<std::string_view>(v), long_string);
    }
    {
        value v(long_string);
        v = v_map;
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(yaml_map));
        EXPECT_NE(v, value(map()));
        EXPECT_EQ(v.kind(), value_kind::map);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_FALSE(v.is_string());
        EXPECT_TRUE(v.is_map());
        EXPECT_FALSE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
        EXPECT_EQ(get<map>(v), yaml_map);
    }
    {
        value v(yaml_map);
        v = v_seq;
        EXPECT_NE(v, value());
        EXPECT_EQ(v, value(yaml_seq));
        EXPECT_NE(v, value(seq()));
        EXPECT_EQ(v.kind(), value_kind::seq);
        EXPECT_FALSE(v.is_null());
        EXPECT_FALSE(v.is_boolean());
        EXPECT_FALSE(v.is_int());
        EXPECT_FALSE(v.is_double());
        EXPECT_FALSE(v.is_string());
        EXPECT_FALSE(v.is_map());
        EXPECT_TRUE(v.is_seq());
        EXPECT_FALSE(v.is_alias());
        EXPECT_FALSE(v.is_property_node());
        EXPECT_FALSE(v.is_user_defined());
        EXPECT_FALSE(v.is<udt>());
        EXPECT_EQ(get<seq>(v), yaml_seq);
    }
}

TEST(yaml_value, move_assign)
{
    // assign to local
    {
        value v_default;
        value v_true(true);
        value v_int(int_num);
        value v_double(double_num);
        value v_short_string(short_string);
        value v_long_string(long_string);
        value v_map(yaml_map);
        value v_seq(yaml_seq);

        {
            value v(true);
            v = std::move(v_default);
            EXPECT_EQ(v, value());
            EXPECT_FALSE(v != value());
            EXPECT_EQ(v.kind(), value_kind::null);
            EXPECT_TRUE(v.is_null());
            EXPECT_FALSE(v.is_boolean());
            EXPECT_FALSE(v.is_int());
            EXPECT_FALSE(v.is_double());
            EXPECT_FALSE(v.is_string());
            EXPECT_FALSE(v.is_map());
            EXPECT_FALSE(v.is_seq());
            EXPECT_FALSE(v.is_alias());
            EXPECT_FALSE(v.is_property_node());
            EXPECT_FALSE(v.is_user_defined());
            EXPECT_FALSE(v.is<udt>());
            EXPECT_EQ(get<null_t>(v), null_t{});
        }
        {
            value v(double_num);
            v = std::move(v_true);
            EXPECT_NE(v, value());
            EXPECT_EQ(v, value(true));
            EXPECT_NE(v, value(false));
            EXPECT_EQ(v.kind(), value_kind::boolean);
            EXPECT_FALSE(v.is_null());
            EXPECT_TRUE(v.is_boolean());
            EXPECT_FALSE(v.is_int());
            EXPECT_FALSE(v.is_double());
            EXPECT_FALSE(v.is_string());
            EXPECT_FALSE(v.is_map());
            EXPECT_FALSE(v.is_seq());
            EXPECT_FALSE(v.is_alias());
            EXPECT_FALSE(v.is_property_node());
            EXPECT_FALSE(v.is_user_defined());
            EXPECT_FALSE(v.is<udt>());
            EXPECT_EQ(get<bool>(v), true);
        }
        {
            value v(short_string);
            v = std::move(v_int);
            EXPECT_NE(v, value());
            EXPECT_EQ(v, value(int_num));
            EXPECT_NE(v, value(0.0));
            EXPECT_EQ(v.kind(), value_kind::int_);
            EXPECT_FALSE(v.is_null());
            EXPECT_FALSE(v.is_boolean());
            EXPECT_TRUE(v.is_int());
            EXPECT_FALSE(v.is_double());
            EXPECT_FALSE(v.is_string());
            EXPECT_FALSE(v.is_map());
            EXPECT_FALSE(v.is_seq());
            EXPECT_FALSE(v.is_alias());
            EXPECT_FALSE(v.is_property_node());
            EXPECT_FALSE(v.is_user_defined());
            EXPECT_FALSE(v.is<udt>());
            EXPECT_EQ(get<int>(v), int_num);
        }
        {
            value v(short_string);
            v = std::move(v_double);
            EXPECT_NE(v, value());
            EXPECT_EQ(v, value(double_num));
            EXPECT_NE(v, value(0.0));
            EXPECT_EQ(v.kind(), value_kind::double_);
            EXPECT_FALSE(v.is_null());
            EXPECT_FALSE(v.is_boolean());
            EXPECT_FALSE(v.is_int());
            EXPECT_TRUE(v.is_double());
            EXPECT_FALSE(v.is_string());
            EXPECT_FALSE(v.is_map());
            EXPECT_FALSE(v.is_seq());
            EXPECT_FALSE(v.is_alias());
            EXPECT_FALSE(v.is_property_node());
            EXPECT_FALSE(v.is_user_defined());
            EXPECT_FALSE(v.is<udt>());
            EXPECT_EQ(get<double>(v), double_num);
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
            EXPECT_FALSE(v.is_int());
            EXPECT_FALSE(v.is_double());
            EXPECT_TRUE(v.is_string());
            EXPECT_FALSE(v.is_map());
            EXPECT_FALSE(v.is_seq());
            EXPECT_FALSE(v.is_alias());
            EXPECT_FALSE(v.is_property_node());
            EXPECT_FALSE(v.is_user_defined());
            EXPECT_FALSE(v.is<udt>());
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
            EXPECT_FALSE(v.is_int());
            EXPECT_FALSE(v.is_double());
            EXPECT_TRUE(v.is_string());
            EXPECT_FALSE(v.is_map());
            EXPECT_FALSE(v.is_seq());
            EXPECT_FALSE(v.is_alias());
            EXPECT_FALSE(v.is_property_node());
            EXPECT_FALSE(v.is_user_defined());
            EXPECT_FALSE(v.is<udt>());
            EXPECT_EQ(get<std::string_view>(v), long_string);
        }
        {
            value v(double_num);
            v = std::move(v_map);
            EXPECT_NE(v, value());
            EXPECT_EQ(v, value(yaml_map));
            EXPECT_NE(v, value(map()));
            EXPECT_EQ(v.kind(), value_kind::map);
            EXPECT_FALSE(v.is_null());
            EXPECT_FALSE(v.is_boolean());
            EXPECT_FALSE(v.is_int());
            EXPECT_FALSE(v.is_double());
            EXPECT_FALSE(v.is_string());
            EXPECT_TRUE(v.is_map());
            EXPECT_FALSE(v.is_seq());
            EXPECT_FALSE(v.is_alias());
            EXPECT_FALSE(v.is_property_node());
            EXPECT_FALSE(v.is_user_defined());
            EXPECT_FALSE(v.is<udt>());
            EXPECT_EQ(get<map>(v), yaml_map);
        }
        {
            value v;
            v = std::move(v_seq);
            EXPECT_NE(v, value());
            EXPECT_EQ(v, value(yaml_seq));
            EXPECT_NE(v, value(seq()));
            EXPECT_EQ(v.kind(), value_kind::seq);
            EXPECT_FALSE(v.is_null());
            EXPECT_FALSE(v.is_boolean());
            EXPECT_FALSE(v.is_int());
            EXPECT_FALSE(v.is_double());
            EXPECT_FALSE(v.is_string());
            EXPECT_FALSE(v.is_map());
            EXPECT_TRUE(v.is_seq());
            EXPECT_FALSE(v.is_alias());
            EXPECT_FALSE(v.is_property_node());
            EXPECT_FALSE(v.is_user_defined());
            EXPECT_FALSE(v.is<udt>());
            EXPECT_EQ(get<seq>(v), yaml_seq);
        }
    }

    // assign to remote
    {
        value v_default;
        value v_true(true);
        value v_int(int_num);
        value v_double(double_num);
        value v_short_string(short_string);
        value v_long_string(long_string);
        value v_map(yaml_map);
        value v_seq(yaml_seq);

        {
            value v(yaml_map);
            v = std::move(v_default);
            EXPECT_EQ(v, value());
            EXPECT_FALSE(v != value());
            EXPECT_EQ(v.kind(), value_kind::null);
            EXPECT_TRUE(v.is_null());
            EXPECT_FALSE(v.is_boolean());
            EXPECT_FALSE(v.is_int());
            EXPECT_FALSE(v.is_double());
            EXPECT_FALSE(v.is_string());
            EXPECT_FALSE(v.is_map());
            EXPECT_FALSE(v.is_seq());
            EXPECT_FALSE(v.is_alias());
            EXPECT_FALSE(v.is_property_node());
            EXPECT_FALSE(v.is_user_defined());
            EXPECT_FALSE(v.is<udt>());
            EXPECT_EQ(get<null_t>(v), null_t{});
        }
        {
            value v(yaml_seq);
            v = std::move(v_true);
            EXPECT_NE(v, value());
            EXPECT_EQ(v, value(true));
            EXPECT_NE(v, value(false));
            EXPECT_EQ(v.kind(), value_kind::boolean);
            EXPECT_FALSE(v.is_null());
            EXPECT_TRUE(v.is_boolean());
            EXPECT_FALSE(v.is_int());
            EXPECT_FALSE(v.is_double());
            EXPECT_FALSE(v.is_string());
            EXPECT_FALSE(v.is_map());
            EXPECT_FALSE(v.is_seq());
            EXPECT_FALSE(v.is_alias());
            EXPECT_FALSE(v.is_property_node());
            EXPECT_FALSE(v.is_user_defined());
            EXPECT_FALSE(v.is<udt>());
            EXPECT_EQ(get<bool>(v), true);
        }
        {
            value v(long_string);
            v = std::move(v_int);
            EXPECT_NE(v, value());
            EXPECT_EQ(v, value(int_num));
            EXPECT_NE(v, value(0.0));
            EXPECT_EQ(v.kind(), value_kind::int_);
            EXPECT_FALSE(v.is_null());
            EXPECT_FALSE(v.is_boolean());
            EXPECT_TRUE(v.is_int());
            EXPECT_FALSE(v.is_double());
            EXPECT_FALSE(v.is_string());
            EXPECT_FALSE(v.is_map());
            EXPECT_FALSE(v.is_seq());
            EXPECT_FALSE(v.is_alias());
            EXPECT_FALSE(v.is_property_node());
            EXPECT_FALSE(v.is_user_defined());
            EXPECT_FALSE(v.is<udt>());
            EXPECT_EQ(get<int>(v), int_num);
        }
        {
            value v(long_string);
            v = std::move(v_double);
            EXPECT_NE(v, value());
            EXPECT_EQ(v, value(double_num));
            EXPECT_NE(v, value(0.0));
            EXPECT_EQ(v.kind(), value_kind::double_);
            EXPECT_FALSE(v.is_null());
            EXPECT_FALSE(v.is_boolean());
            EXPECT_FALSE(v.is_int());
            EXPECT_TRUE(v.is_double());
            EXPECT_FALSE(v.is_string());
            EXPECT_FALSE(v.is_map());
            EXPECT_FALSE(v.is_seq());
            EXPECT_FALSE(v.is_alias());
            EXPECT_FALSE(v.is_property_node());
            EXPECT_FALSE(v.is_user_defined());
            EXPECT_FALSE(v.is<udt>());
            EXPECT_EQ(get<double>(v), double_num);
        }
        {
            value v(yaml_map);
            v = std::move(v_short_string);
            EXPECT_NE(v, value());
            EXPECT_EQ(v, value(short_string));
            EXPECT_NE(v, value(long_string));
            EXPECT_EQ(v.kind(), value_kind::string);
            EXPECT_FALSE(v.is_null());
            EXPECT_FALSE(v.is_boolean());
            EXPECT_FALSE(v.is_int());
            EXPECT_FALSE(v.is_double());
            EXPECT_TRUE(v.is_string());
            EXPECT_FALSE(v.is_map());
            EXPECT_FALSE(v.is_seq());
            EXPECT_FALSE(v.is_alias());
            EXPECT_FALSE(v.is_property_node());
            EXPECT_FALSE(v.is_user_defined());
            EXPECT_FALSE(v.is<udt>());
            EXPECT_EQ(get<std::string_view>(v), short_string);
        }
        {
            value v(yaml_seq);
            v = std::move(v_long_string);
            EXPECT_NE(v, value());
            EXPECT_EQ(v, value(long_string));
            EXPECT_NE(v, value(short_string));
            EXPECT_EQ(v.kind(), value_kind::string);
            EXPECT_FALSE(v.is_null());
            EXPECT_FALSE(v.is_boolean());
            EXPECT_FALSE(v.is_int());
            EXPECT_FALSE(v.is_double());
            EXPECT_TRUE(v.is_string());
            EXPECT_FALSE(v.is_map());
            EXPECT_FALSE(v.is_seq());
            EXPECT_FALSE(v.is_alias());
            EXPECT_FALSE(v.is_property_node());
            EXPECT_FALSE(v.is_user_defined());
            EXPECT_FALSE(v.is<udt>());
            EXPECT_EQ(get<std::string_view>(v), long_string);
        }
        {
            value v(long_string);
            v = std::move(v_map);
            EXPECT_NE(v, value());
            EXPECT_EQ(v, value(yaml_map));
            EXPECT_NE(v, value(map()));
            EXPECT_EQ(v.kind(), value_kind::map);
            EXPECT_FALSE(v.is_null());
            EXPECT_FALSE(v.is_boolean());
            EXPECT_FALSE(v.is_int());
            EXPECT_FALSE(v.is_double());
            EXPECT_FALSE(v.is_string());
            EXPECT_TRUE(v.is_map());
            EXPECT_FALSE(v.is_seq());
            EXPECT_FALSE(v.is_alias());
            EXPECT_FALSE(v.is_property_node());
            EXPECT_FALSE(v.is_user_defined());
            EXPECT_FALSE(v.is<udt>());
            EXPECT_EQ(get<map>(v), yaml_map);
        }
        {
            value v(yaml_map);
            v = std::move(v_seq);
            EXPECT_NE(v, value());
            EXPECT_EQ(v, value(yaml_seq));
            EXPECT_NE(v, value(seq()));
            EXPECT_EQ(v.kind(), value_kind::seq);
            EXPECT_FALSE(v.is_null());
            EXPECT_FALSE(v.is_boolean());
            EXPECT_FALSE(v.is_int());
            EXPECT_FALSE(v.is_double());
            EXPECT_FALSE(v.is_string());
            EXPECT_FALSE(v.is_map());
            EXPECT_TRUE(v.is_seq());
            EXPECT_FALSE(v.is_alias());
            EXPECT_FALSE(v.is_property_node());
            EXPECT_FALSE(v.is_user_defined());
            EXPECT_FALSE(v.is<udt>());
            EXPECT_EQ(get<seq>(v), yaml_seq);
        }
    }
}
