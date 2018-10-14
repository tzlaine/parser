// WARNING!  This file is generated.
// Copyright (C) 2018 T. Zachary Laine
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#include <boost/parser/parser.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>


using namespace boost::parser;
using boost::is_same;
using boost::optional;
using boost::variant;
using boost::hana::tuple;

void compile_or_seq_attribute()
{
    char const chars[] = "";
    auto first = std::begin(chars);
    auto const last = std::end(chars);

    {
        constexpr auto parser = (-int_ >> -int_ >> *char_ >> *char_) | (eps >> eps >> -int_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<optional<int>>, std::vector<char>>, std::vector<optional<int>>>>>));
    }
    {
        constexpr auto parser = (-int_ | -int_ | *char_ | *char_) >> (eps | eps | -int_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<optional<int>, std::vector<char>>, optional<int>>>>));
    }
    {
        constexpr auto parser = -(-int_ >> -int_ >> *char_ >> *char_) | -(-int_ >> *char_ >> -int_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<optional<int>>, std::vector<char>>>, optional<tuple<optional<int>, std::vector<char>, optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = (-int_ | -int_ | *char_ | *char_) >> (-int_ | *char_ | -int_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<variant<optional<int>, std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (-int_ >> -int_ >> *char_ >> *char_) | (-int_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<optional<int>>, std::vector<char>>, tuple<optional<int>, std::vector<char>>>>>));
    }
    {
        constexpr auto parser = -(-int_ | -int_ | *char_ | *char_) >> (-int_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, variant<optional<int>, std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (-int_ >> -int_ >> *char_ >> *char_) | -(-int_ >> *char_ >> -int_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<optional<int>>, std::vector<char>>, optional<tuple<optional<int>, std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = (-int_ | -int_ | *char_ | *char_) >> (-int_ | *char_ | -int_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<optional<int>, std::vector<char>>, optional<variant<optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = -(-int_ >> -int_ >> *char_ >> *char_) | (-int_ >> *char_ >> *char_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<optional<int>>, std::vector<char>>>, tuple<optional<int>, std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (-int_ | -int_ | *char_ | *char_) >> (-int_ | *char_ | *char_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<variant<optional<int>, std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (-int_ >> -int_ >> *char_ >> *char_) | -(-int_ >> eps >> eps >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<optional<int>>, std::vector<char>>, optional<std::vector<optional<int>>>>>>));
    }
    {
        constexpr auto parser = -(-int_ | -int_ | *char_ | *char_) >> (-int_ | eps | eps | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<int>>>>));
    }
    {
        constexpr auto parser = (-int_ >> -int_ >> *char_ >> *char_) | (-int_ >> *char_ >> eps >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<optional<int>>, std::vector<char>>, tuple<optional<int>, std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (-int_ | -int_ | *char_ | *char_) >> (-int_ | *char_ | eps | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<optional<int>, std::vector<char>>, optional<variant<optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = -(-int_ >> -int_ >> *char_ >> *char_) | -(-int_ >> eps >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<optional<int>>, std::vector<char>>>, optional<tuple<optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = (-int_ | -int_ | *char_ | *char_) >> (-int_ | eps | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<optional<int>, std::vector<char>>, optional<variant<optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = (-int_ >> -int_ >> *char_ >> *char_) | (eps >> -int_ >> -int_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<std::vector<optional<int>>, std::vector<char>>>>));
    }
    {
        constexpr auto parser = -(-int_ | -int_ | *char_ | *char_) >> (eps | -int_ | -int_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<variant<optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = (-int_ >> -int_ >> *char_ >> *char_) | -(*char_ >> eps >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<optional<int>>, std::vector<char>>, optional<std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (-int_ | -int_ | *char_ | *char_) >> (*char_ | eps | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<optional<int>, std::vector<char>>, optional<std::vector<char>>>>>));
    }
    {
        constexpr auto parser = -(-int_ >> -int_ >> *char_ >> *char_) | (*char_ >> -int_ >> *char_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<optional<int>>, std::vector<char>>>, tuple<std::vector<char>, optional<int>, std::vector<char>, optional<int>>>>>));
    }
    {
        constexpr auto parser = (-int_ | -int_ | *char_ | *char_) >> (*char_ | -int_ | *char_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<optional<int>, std::vector<char>>, variant<std::vector<char>, optional<int>>>>>));
    }
    {
        constexpr auto parser = (-int_ >> -int_ >> *char_ >> *char_) | -(-int_ >> *char_ >> -int_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<optional<int>>, std::vector<char>>, optional<tuple<optional<int>, std::vector<char>, std::vector<optional<int>>>>>>>));
    }
    {
        constexpr auto parser = -(-int_ | -int_ | *char_ | *char_) >> (-int_ | *char_ | -int_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, variant<optional<int>, std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (-int_ >> -int_ >> *char_ >> *char_) | (eps >> -int_ >> -int_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<optional<int>>, std::vector<char>>, std::vector<optional<int>>>>>));
    }
    {
        constexpr auto parser = (-int_ | -int_ | *char_ | *char_) >> (eps | -int_ | -int_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<optional<int>, std::vector<char>>, optional<int>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | -(eps >> *char_ >> *char_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, std::vector<optional<int>>>>, optional<tuple<std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (eps | *char_ | *char_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (eps >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<optional<tuple<std::vector<char>, std::vector<optional<int>>>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (eps | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<optional<variant<std::vector<char>, optional<int>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(*char_ >> *char_ >> -int_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<tuple<std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (*char_ | *char_ | -int_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | (*char_ >> -int_ >> eps >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, std::vector<optional<int>>>>, tuple<std::vector<char>, optional<int>, std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (*char_ | -int_ | eps | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(-int_ >> eps >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<int>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (-int_ | eps | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<int>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (-int_ >> eps >> eps >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, tuple<optional<int>, std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (-int_ | eps | eps | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | -(-int_ >> -int_ >> eps >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, std::vector<optional<int>>>>, optional<std::vector<optional<int>>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (-int_ | -int_ | eps | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<int>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (-int_ >> eps >> *char_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, tuple<optional<int>, std::vector<char>>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (-int_ | eps | *char_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<variant<optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(-int_ >> -int_ >> eps >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<tuple<std::vector<optional<int>>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (-int_ | -int_ | eps | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | (eps >> -int_ >> eps >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, std::vector<optional<int>>>>, std::vector<optional<int>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (eps | -int_ | eps | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<int>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(*char_ >> eps >> -int_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<tuple<std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (*char_ | eps | -int_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<variant<std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (*char_ >> eps >> eps >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, std::vector<char>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (*char_ | eps | eps | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<std::vector<char>>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | -(eps >> *char_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, std::vector<optional<int>>>>, optional<tuple<std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (eps | *char_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (*char_ >> eps >> eps >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, std::vector<char>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (*char_ | eps | eps | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(eps >> *char_ >> -int_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (eps | *char_ | -int_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | (*char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, std::vector<optional<int>>>>, std::vector<char>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (*char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, std::vector<char>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(-int_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<std::vector<optional<int>>>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (-int_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<int>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (eps >> -int_ >> eps >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, tuple<optional<int>, std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (eps | -int_ | eps | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | -(eps >> -int_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, std::vector<optional<int>>>>, optional<std::vector<optional<int>>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (eps | -int_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<int>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (*char_ >> -int_ >> eps >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<std::vector<char>, std::vector<optional<int>>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (*char_ | -int_ | eps | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<variant<std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(-int_ >> eps >> *char_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<tuple<optional<int>, std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (-int_ | eps | *char_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | (*char_ >> eps >> *char_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, std::vector<optional<int>>>>, tuple<std::vector<char>, optional<int>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (*char_ | eps | *char_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(*char_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<std::vector<char>>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (*char_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, std::vector<char>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (-int_ >> eps >> -int_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, std::vector<optional<int>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (-int_ | eps | -int_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<int>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | -(-int_ >> eps >> -int_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, std::vector<optional<int>>>>, optional<tuple<std::vector<optional<int>>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (-int_ | eps | -int_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (eps >> eps >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, std::vector<char>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (eps | eps | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(-int_ >> -int_ >> *char_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<tuple<std::vector<optional<int>>, std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (-int_ | -int_ | *char_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, variant<optional<int>, std::vector<char>>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | (eps >> *char_ >> eps >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, std::vector<optional<int>>>>, tuple<std::vector<char>, optional<int>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (eps | *char_ | eps | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(-int_ >> *char_ >> eps >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<tuple<optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (-int_ | *char_ | eps | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<variant<optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (eps >> -int_ >> *char_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, tuple<optional<int>, std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (eps | -int_ | *char_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | -(-int_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, std::vector<optional<int>>>>, optional<int>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (-int_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<int>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (-int_ >> *char_ >> *char_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, tuple<optional<int>, std::vector<char>, optional<int>>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (-int_ | *char_ | *char_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, variant<optional<int>, std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(eps >> -int_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<int>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (eps | -int_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<int>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | (*char_ >> -int_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, std::vector<optional<int>>>>, tuple<std::vector<char>, std::vector<optional<int>>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (*char_ | -int_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<variant<std::vector<char>, optional<int>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(-int_ >> *char_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<tuple<optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (-int_ | *char_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<variant<optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (-int_ >> -int_ >> *char_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, tuple<std::vector<optional<int>>, std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (-int_ | -int_ | *char_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, variant<optional<int>, std::vector<char>>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | -(*char_ >> -int_ >> -int_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<optional<tuple<std::vector<char>, std::vector<optional<int>>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (*char_ | -int_ | -int_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<variant<std::vector<char>, optional<int>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (eps >> -int_ >> *char_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, tuple<optional<int>, std::vector<char>, optional<int>>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (eps | -int_ | *char_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<variant<optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(*char_ >> *char_ >> eps >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<tuple<std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (*char_ | *char_ | eps | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | (eps >> *char_ >> eps >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, std::vector<optional<int>>>>, std::vector<char>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (eps | *char_ | eps | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(-int_ >> -int_ >> *char_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<tuple<std::vector<optional<int>>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (-int_ | -int_ | *char_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<variant<optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (eps >> *char_ >> eps >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, std::vector<char>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (eps | *char_ | eps | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<std::vector<char>>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | -(eps >> -int_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, std::vector<optional<int>>>>, optional<tuple<optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (eps | -int_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (-int_ >> eps >> -int_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, std::vector<optional<int>>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (-int_ | eps | -int_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<int>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(eps >> eps >> -int_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<tuple<optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (eps | eps | -int_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | (-int_ >> *char_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, std::vector<optional<int>>>>, tuple<optional<int>, std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (-int_ | *char_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, variant<optional<int>, std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(eps >> eps >> *char_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<tuple<std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (eps | eps | *char_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<variant<std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (*char_ >> eps >> *char_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, std::vector<char>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (*char_ | eps | *char_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<std::vector<char>>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | -(-int_ >> eps >> *char_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, std::vector<optional<int>>>>, optional<tuple<optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (-int_ | eps | *char_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (eps >> -int_ >> eps >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<int>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (eps | -int_ | eps | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<int>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(*char_ >> eps >> -int_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (*char_ | eps | -int_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | (*char_ >> eps >> *char_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, std::vector<optional<int>>>>, std::vector<char>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (*char_ | eps | *char_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(-int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<int>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (-int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<int>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<optional<tuple<std::vector<char>, std::vector<optional<int>>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<std::vector<char>, optional<int>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | -(eps >> eps >> *char_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, std::vector<optional<int>>>>, optional<std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (eps | eps | *char_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (eps >> eps >> *char_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, std::vector<char>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (eps | eps | *char_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(*char_ >> *char_ >> eps >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (*char_ | *char_ | eps | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<std::vector<char>>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | (eps >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, std::vector<optional<int>>>>, optional<int>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (eps | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<int>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(*char_ >> *char_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<tuple<std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (*char_ | *char_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, variant<std::vector<char>, optional<int>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (*char_ >> eps >> eps >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, tuple<std::vector<char>, optional<int>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (*char_ | eps | eps | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | -(*char_ >> *char_ >> eps >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, std::vector<optional<int>>>>, optional<std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (*char_ | *char_ | eps | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (*char_ >> eps >> -int_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<std::vector<char>, std::vector<optional<int>>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (*char_ | eps | -int_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<optional<variant<std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(*char_ >> -int_ >> -int_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<tuple<std::vector<char>, std::vector<optional<int>>>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (*char_ | -int_ | -int_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | (*char_ >> *char_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, std::vector<optional<int>>>>, std::vector<char>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (*char_ | *char_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(*char_ >> -int_ >> -int_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<tuple<std::vector<char>, std::vector<optional<int>>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (*char_ | -int_ | -int_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, variant<std::vector<char>, optional<int>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (-int_ >> -int_ >> eps >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, std::vector<optional<int>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (-int_ | -int_ | eps | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<int>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | -(-int_ >> *char_ >> *char_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, std::vector<optional<int>>>>, optional<tuple<optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (-int_ | *char_ | *char_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (eps >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, std::vector<char>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (eps | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(-int_ >> *char_ >> eps >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<tuple<optional<int>, std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (-int_ | *char_ | eps | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | (-int_ >> -int_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, std::vector<optional<int>>>>, tuple<std::vector<optional<int>>, std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (-int_ | -int_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, variant<optional<int>, std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(eps >> *char_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<std::vector<char>>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (eps | *char_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (eps >> -int_ >> *char_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, tuple<optional<int>, std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (eps | -int_ | *char_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | -(*char_ >> -int_ >> *char_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, std::vector<optional<int>>>>, optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (*char_ | -int_ | *char_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<variant<std::vector<char>, optional<int>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (eps >> *char_ >> *char_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, std::vector<char>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (eps | *char_ | *char_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(*char_ >> *char_ >> -int_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (*char_ | *char_ | -int_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<variant<std::vector<char>, optional<int>>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | (*char_ >> *char_ >> -int_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, std::vector<optional<int>>>>, tuple<std::vector<char>, std::vector<optional<int>>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (*char_ | *char_ | -int_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<variant<std::vector<char>, optional<int>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(*char_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<tuple<std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (*char_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, variant<std::vector<char>, optional<int>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (eps >> *char_ >> *char_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, std::vector<char>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (eps | *char_ | *char_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<std::vector<char>>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | -(*char_ >> -int_ >> eps >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, std::vector<optional<int>>>>, optional<tuple<std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (*char_ | -int_ | eps | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (eps >> -int_ >> -int_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, std::vector<optional<int>>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (eps | -int_ | -int_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<int>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(*char_ >> -int_ >> *char_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<tuple<std::vector<char>, optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (*char_ | -int_ | *char_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | (*char_ >> -int_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, std::vector<optional<int>>>>, tuple<std::vector<char>, optional<int>, std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (*char_ | -int_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<variant<std::vector<char>, optional<int>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(-int_ >> -int_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<std::vector<optional<int>>>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (-int_ | -int_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<int>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (eps >> *char_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, std::vector<char>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (eps | *char_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<std::vector<char>>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | -(-int_ >> eps >> eps >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, std::vector<optional<int>>>>, optional<int>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (-int_ | eps | eps | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<int>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (eps >> eps >> -int_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<int>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (eps | eps | -int_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<int>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(-int_ >> *char_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<tuple<optional<int>, std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (-int_ | *char_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, variant<optional<int>, std::vector<char>>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | (*char_ >> -int_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, std::vector<optional<int>>>>, tuple<std::vector<char>, optional<int>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (*char_ | -int_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(eps >> eps >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<int>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (eps | eps | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<int>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (eps >> *char_ >> -int_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<std::vector<char>, std::vector<optional<int>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (eps | *char_ | -int_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | -(-int_ >> eps >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, std::vector<optional<int>>>>, optional<std::vector<optional<int>>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (-int_ | eps | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<int>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (*char_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, std::vector<char>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (*char_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(eps >> *char_ >> -int_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<tuple<std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (eps | *char_ | -int_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | (*char_ >> eps >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, std::vector<optional<int>>>>, tuple<std::vector<char>, optional<int>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (*char_ | eps | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(*char_ >> eps >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<std::vector<char>>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (*char_ | eps | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (eps >> eps >> -int_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, std::vector<optional<int>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (eps | eps | -int_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<int>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | -(-int_ >> *char_ >> -int_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, std::vector<optional<int>>>>, optional<tuple<optional<int>, std::vector<char>, optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (-int_ | *char_ | -int_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, variant<optional<int>, std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (-int_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, tuple<optional<int>, std::vector<char>>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (-int_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, variant<optional<int>, std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(-int_ >> *char_ >> -int_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<tuple<optional<int>, std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (-int_ | *char_ | -int_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | (-int_ >> *char_ >> *char_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, std::vector<optional<int>>>>, tuple<optional<int>, std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (-int_ | *char_ | *char_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, variant<optional<int>, std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(-int_ >> eps >> eps >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<std::vector<optional<int>>>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (-int_ | eps | eps | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<int>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (-int_ >> *char_ >> eps >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, tuple<optional<int>, std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (-int_ | *char_ | eps | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | -(-int_ >> eps >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, std::vector<optional<int>>>>, optional<tuple<optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (-int_ | eps | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<variant<optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (eps >> -int_ >> -int_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, tuple<std::vector<optional<int>>, std::vector<char>>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (eps | -int_ | -int_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, optional<variant<optional<int>, std::vector<char>>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(*char_ >> eps >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (*char_ | eps | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<std::vector<char>>>>>));
    }
    {
        constexpr auto parser = -(*char_ >> -int_ >> -int_ >> -int_) | (*char_ >> -int_ >> *char_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<std::vector<char>, std::vector<optional<int>>>>, tuple<std::vector<char>, optional<int>, std::vector<char>, optional<int>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (*char_ | -int_ | *char_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<variant<std::vector<char>, optional<int>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | -(-int_ >> *char_ >> -int_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, optional<tuple<optional<int>, std::vector<char>, std::vector<optional<int>>>>>>>));
    }
    {
        constexpr auto parser = -(*char_ | -int_ | -int_ | -int_) >> (-int_ | *char_ | -int_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<std::vector<char>, optional<int>>>, variant<optional<int>, std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (*char_ >> -int_ >> -int_ >> -int_) | (eps >> -int_ >> -int_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<std::vector<char>, std::vector<optional<int>>>, std::vector<optional<int>>>>>));
    }
    {
        constexpr auto parser = (*char_ | -int_ | -int_ | -int_) >> (eps | -int_ | -int_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<variant<std::vector<char>, optional<int>>, optional<int>>>>));
    }
    {
        constexpr auto parser = -(eps >> -int_ >> *char_ >> -int_) | -(eps >> *char_ >> *char_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<optional<int>, std::vector<char>, optional<int>>>, optional<tuple<std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = (eps | -int_ | *char_ | -int_) >> (eps | *char_ | *char_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<variant<std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = (eps >> -int_ >> *char_ >> -int_) | (eps >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<optional<tuple<optional<int>, std::vector<char>, optional<int>>>>>));
    }
    {
        constexpr auto parser = -(eps | -int_ | *char_ | -int_) >> (eps | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<optional<variant<optional<int>, std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (eps >> -int_ >> *char_ >> -int_) | -(*char_ >> *char_ >> -int_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<tuple<optional<int>, std::vector<char>, optional<int>>, optional<tuple<std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = (eps | -int_ | *char_ | -int_) >> (*char_ | *char_ | -int_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<variant<std::vector<char>, optional<int>>>>>>));
    }
    {
        constexpr auto parser = -(eps >> -int_ >> *char_ >> -int_) | (*char_ >> -int_ >> eps >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<variant<optional<tuple<optional<int>, std::vector<char>, optional<int>>>, tuple<std::vector<char>, optional<int>, std::vector<char>>>>>));
    }
    {
        constexpr auto parser = (eps | -int_ | *char_ | -int_) >> (*char_ | -int_ | eps | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<optional<variant<optional<int>, std::vector<char>>>, optional<variant<std::vector<char>, optional<int>>>>>>));
    }

}
