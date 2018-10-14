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
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | -(eps >> -int_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (eps | -int_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps >> eps >> *char_ >> -int_) | (*char_ >> -int_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (*char_ | -int_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | -(-int_ >> *char_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps | eps | *char_ | -int_) >> (-int_ | *char_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | (-int_ >> -int_ >> *char_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (-int_ | -int_ | *char_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps >> eps >> *char_ >> -int_) | -(*char_ >> -int_ >> -int_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (*char_ | -int_ | -int_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | (eps >> -int_ >> *char_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps | eps | *char_ | -int_) >> (eps | -int_ | *char_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | -(*char_ >> *char_ >> eps >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (*char_ | *char_ | eps | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps >> eps >> *char_ >> -int_) | (eps >> *char_ >> eps >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (eps | *char_ | eps | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | -(-int_ >> -int_ >> *char_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps | eps | *char_ | -int_) >> (-int_ | -int_ | *char_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | (eps >> *char_ >> eps >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (eps | *char_ | eps | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps >> eps >> *char_ >> -int_) | -(eps >> -int_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (eps | -int_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | (-int_ >> eps >> -int_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps | eps | *char_ | -int_) >> (-int_ | eps | -int_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | -(eps >> eps >> -int_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (eps | eps | -int_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps >> eps >> *char_ >> -int_) | (-int_ >> *char_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (-int_ | *char_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | -(eps >> eps >> *char_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps | eps | *char_ | -int_) >> (eps | eps | *char_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | (*char_ >> eps >> *char_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (*char_ | eps | *char_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps >> eps >> *char_ >> -int_) | -(-int_ >> eps >> *char_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (-int_ | eps | *char_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | (eps >> -int_ >> eps >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps | eps | *char_ | -int_) >> (eps | -int_ | eps | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | -(*char_ >> eps >> -int_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (*char_ | eps | -int_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps >> eps >> *char_ >> -int_) | (*char_ >> eps >> *char_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (*char_ | eps | *char_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | -(-int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps | eps | *char_ | -int_) >> (-int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | (eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps >> eps >> *char_ >> -int_) | -(eps >> eps >> *char_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (eps | eps | *char_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | (eps >> eps >> *char_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps | eps | *char_ | -int_) >> (eps | eps | *char_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | -(*char_ >> *char_ >> eps >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (*char_ | *char_ | eps | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps >> eps >> *char_ >> -int_) | (eps >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (eps | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | -(*char_ >> *char_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps | eps | *char_ | -int_) >> (*char_ | *char_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | (*char_ >> eps >> eps >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (*char_ | eps | eps | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps >> eps >> *char_ >> -int_) | -(*char_ >> *char_ >> eps >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (*char_ | *char_ | eps | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | (*char_ >> eps >> -int_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps | eps | *char_ | -int_) >> (*char_ | eps | -int_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | -(*char_ >> -int_ >> -int_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (*char_ | -int_ | -int_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps >> eps >> *char_ >> -int_) | (*char_ >> *char_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (*char_ | *char_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | -(*char_ >> -int_ >> -int_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps | eps | *char_ | -int_) >> (*char_ | -int_ | -int_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | (-int_ >> -int_ >> eps >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (-int_ | -int_ | eps | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps >> eps >> *char_ >> -int_) | -(-int_ >> *char_ >> *char_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (-int_ | *char_ | *char_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | (eps >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps | eps | *char_ | -int_) >> (eps | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | -(-int_ >> *char_ >> eps >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (-int_ | *char_ | eps | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps >> eps >> *char_ >> -int_) | (-int_ >> -int_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (-int_ | -int_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | -(eps >> *char_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps | eps | *char_ | -int_) >> (eps | *char_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | (eps >> -int_ >> *char_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (eps | -int_ | *char_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps >> eps >> *char_ >> -int_) | -(*char_ >> -int_ >> *char_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (*char_ | -int_ | *char_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | (eps >> *char_ >> *char_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps | eps | *char_ | -int_) >> (eps | *char_ | *char_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | -(*char_ >> *char_ >> -int_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (*char_ | *char_ | -int_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps >> eps >> *char_ >> -int_) | (*char_ >> *char_ >> -int_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (*char_ | *char_ | -int_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | -(*char_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps | eps | *char_ | -int_) >> (*char_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | (eps >> *char_ >> *char_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (eps | *char_ | *char_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps >> eps >> *char_ >> -int_) | -(*char_ >> -int_ >> eps >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (*char_ | -int_ | eps | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | (eps >> -int_ >> -int_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps | eps | *char_ | -int_) >> (eps | -int_ | -int_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | -(*char_ >> -int_ >> *char_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (*char_ | -int_ | *char_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps >> eps >> *char_ >> -int_) | (*char_ >> -int_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (*char_ | -int_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | -(-int_ >> -int_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps | eps | *char_ | -int_) >> (-int_ | -int_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | (eps >> *char_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (eps | *char_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps >> eps >> *char_ >> -int_) | -(-int_ >> eps >> eps >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (-int_ | eps | eps | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | (eps >> eps >> -int_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps | eps | *char_ | -int_) >> (eps | eps | -int_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | -(-int_ >> *char_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (-int_ | *char_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps >> eps >> *char_ >> -int_) | (*char_ >> -int_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (*char_ | -int_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | -(eps >> eps >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps | eps | *char_ | -int_) >> (eps | eps | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | (eps >> *char_ >> -int_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (eps | *char_ | -int_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps >> eps >> *char_ >> -int_) | -(-int_ >> eps >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (-int_ | eps | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | (*char_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps | eps | *char_ | -int_) >> (*char_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | -(eps >> *char_ >> -int_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (eps | *char_ | -int_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps >> eps >> *char_ >> -int_) | (*char_ >> eps >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (*char_ | eps | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | -(*char_ >> eps >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps | eps | *char_ | -int_) >> (*char_ | eps | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | (eps >> eps >> -int_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (eps | eps | -int_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps >> eps >> *char_ >> -int_) | -(-int_ >> *char_ >> -int_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (-int_ | *char_ | -int_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | (-int_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps | eps | *char_ | -int_) >> (-int_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | -(-int_ >> *char_ >> -int_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (-int_ | *char_ | -int_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps >> eps >> *char_ >> -int_) | (-int_ >> *char_ >> *char_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (-int_ | *char_ | *char_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | -(-int_ >> eps >> eps >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps | eps | *char_ | -int_) >> (-int_ | eps | eps | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | (-int_ >> *char_ >> eps >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (-int_ | *char_ | eps | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps >> eps >> *char_ >> -int_) | -(-int_ >> eps >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (-int_ | eps | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | (eps >> -int_ >> -int_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps | eps | *char_ | -int_) >> (eps | -int_ | -int_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | -(*char_ >> eps >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (*char_ | eps | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps >> eps >> *char_ >> -int_) | (*char_ >> -int_ >> *char_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (*char_ | -int_ | *char_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | -(-int_ >> *char_ >> -int_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(eps | eps | *char_ | -int_) >> (-int_ | *char_ | -int_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps >> eps >> *char_ >> -int_) | (eps >> -int_ >> -int_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (eps | eps | *char_ | -int_) >> (eps | -int_ | -int_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(*char_ >> eps >> *char_ >> eps) | -(eps >> *char_ >> *char_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ | eps | *char_ | eps) >> (eps | *char_ | *char_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ >> eps >> *char_ >> eps) | (eps >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(*char_ | eps | *char_ | eps) >> (eps | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ >> eps >> *char_ >> eps) | -(*char_ >> *char_ >> -int_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ | eps | *char_ | eps) >> (*char_ | *char_ | -int_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(*char_ >> eps >> *char_ >> eps) | (*char_ >> -int_ >> eps >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ | eps | *char_ | eps) >> (*char_ | -int_ | eps | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ >> eps >> *char_ >> eps) | -(-int_ >> eps >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(*char_ | eps | *char_ | eps) >> (-int_ | eps | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ >> eps >> *char_ >> eps) | (-int_ >> eps >> eps >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ | eps | *char_ | eps) >> (-int_ | eps | eps | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(*char_ >> eps >> *char_ >> eps) | -(-int_ >> -int_ >> eps >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ | eps | *char_ | eps) >> (-int_ | -int_ | eps | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ >> eps >> *char_ >> eps) | (-int_ >> eps >> *char_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(*char_ | eps | *char_ | eps) >> (-int_ | eps | *char_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ >> eps >> *char_ >> eps) | -(-int_ >> -int_ >> eps >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ | eps | *char_ | eps) >> (-int_ | -int_ | eps | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(*char_ >> eps >> *char_ >> eps) | (eps >> -int_ >> eps >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ | eps | *char_ | eps) >> (eps | -int_ | eps | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ >> eps >> *char_ >> eps) | -(*char_ >> eps >> -int_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(*char_ | eps | *char_ | eps) >> (*char_ | eps | -int_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ >> eps >> *char_ >> eps) | (*char_ >> eps >> eps >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ | eps | *char_ | eps) >> (*char_ | eps | eps | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(*char_ >> eps >> *char_ >> eps) | -(eps >> *char_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ | eps | *char_ | eps) >> (eps | *char_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ >> eps >> *char_ >> eps) | (*char_ >> eps >> eps >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(*char_ | eps | *char_ | eps) >> (*char_ | eps | eps | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ >> eps >> *char_ >> eps) | -(eps >> *char_ >> -int_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ | eps | *char_ | eps) >> (eps | *char_ | -int_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(*char_ >> eps >> *char_ >> eps) | (*char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ | eps | *char_ | eps) >> (*char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ >> eps >> *char_ >> eps) | -(-int_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(*char_ | eps | *char_ | eps) >> (-int_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ >> eps >> *char_ >> eps) | (eps >> -int_ >> eps >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ | eps | *char_ | eps) >> (eps | -int_ | eps | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(*char_ >> eps >> *char_ >> eps) | -(eps >> -int_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ | eps | *char_ | eps) >> (eps | -int_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ >> eps >> *char_ >> eps) | (*char_ >> -int_ >> eps >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(*char_ | eps | *char_ | eps) >> (*char_ | -int_ | eps | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ >> eps >> *char_ >> eps) | -(-int_ >> eps >> *char_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ | eps | *char_ | eps) >> (-int_ | eps | *char_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(*char_ >> eps >> *char_ >> eps) | (*char_ >> eps >> *char_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ | eps | *char_ | eps) >> (*char_ | eps | *char_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ >> eps >> *char_ >> eps) | -(*char_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(*char_ | eps | *char_ | eps) >> (*char_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ >> eps >> *char_ >> eps) | (-int_ >> eps >> -int_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ | eps | *char_ | eps) >> (-int_ | eps | -int_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(*char_ >> eps >> *char_ >> eps) | -(-int_ >> eps >> -int_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ | eps | *char_ | eps) >> (-int_ | eps | -int_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ >> eps >> *char_ >> eps) | (eps >> eps >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(*char_ | eps | *char_ | eps) >> (eps | eps | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ >> eps >> *char_ >> eps) | -(-int_ >> -int_ >> *char_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ | eps | *char_ | eps) >> (-int_ | -int_ | *char_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(*char_ >> eps >> *char_ >> eps) | (eps >> *char_ >> eps >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ | eps | *char_ | eps) >> (eps | *char_ | eps | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ >> eps >> *char_ >> eps) | -(-int_ >> *char_ >> eps >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(*char_ | eps | *char_ | eps) >> (-int_ | *char_ | eps | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ >> eps >> *char_ >> eps) | (eps >> -int_ >> *char_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ | eps | *char_ | eps) >> (eps | -int_ | *char_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(*char_ >> eps >> *char_ >> eps) | -(-int_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ | eps | *char_ | eps) >> (-int_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ >> eps >> *char_ >> eps) | (-int_ >> *char_ >> *char_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(*char_ | eps | *char_ | eps) >> (-int_ | *char_ | *char_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ >> eps >> *char_ >> eps) | -(eps >> -int_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ | eps | *char_ | eps) >> (eps | -int_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(*char_ >> eps >> *char_ >> eps) | (*char_ >> -int_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ | eps | *char_ | eps) >> (*char_ | -int_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ >> eps >> *char_ >> eps) | -(-int_ >> *char_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(*char_ | eps | *char_ | eps) >> (-int_ | *char_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ >> eps >> *char_ >> eps) | (-int_ >> -int_ >> *char_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ | eps | *char_ | eps) >> (-int_ | -int_ | *char_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(*char_ >> eps >> *char_ >> eps) | -(*char_ >> -int_ >> -int_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ | eps | *char_ | eps) >> (*char_ | -int_ | -int_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ >> eps >> *char_ >> eps) | (eps >> -int_ >> *char_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(*char_ | eps | *char_ | eps) >> (eps | -int_ | *char_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ >> eps >> *char_ >> eps) | -(*char_ >> *char_ >> eps >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ | eps | *char_ | eps) >> (*char_ | *char_ | eps | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(*char_ >> eps >> *char_ >> eps) | (eps >> *char_ >> eps >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ | eps | *char_ | eps) >> (eps | *char_ | eps | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ >> eps >> *char_ >> eps) | -(-int_ >> -int_ >> *char_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(*char_ | eps | *char_ | eps) >> (-int_ | -int_ | *char_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ >> eps >> *char_ >> eps) | (eps >> *char_ >> eps >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ | eps | *char_ | eps) >> (eps | *char_ | eps | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(*char_ >> eps >> *char_ >> eps) | -(eps >> -int_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ | eps | *char_ | eps) >> (eps | -int_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ >> eps >> *char_ >> eps) | (-int_ >> eps >> -int_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(*char_ | eps | *char_ | eps) >> (-int_ | eps | -int_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ >> eps >> *char_ >> eps) | -(eps >> eps >> -int_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ | eps | *char_ | eps) >> (eps | eps | -int_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(*char_ >> eps >> *char_ >> eps) | (-int_ >> *char_ >> *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ | eps | *char_ | eps) >> (-int_ | *char_ | *char_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ >> eps >> *char_ >> eps) | -(eps >> eps >> *char_ >> -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(*char_ | eps | *char_ | eps) >> (eps | eps | *char_ | -int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ >> eps >> *char_ >> eps) | (*char_ >> eps >> *char_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ | eps | *char_ | eps) >> (*char_ | eps | *char_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = -(*char_ >> eps >> *char_ >> eps) | -(-int_ >> eps >> *char_ >> eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }
    {
        constexpr auto parser = (*char_ | eps | *char_ | eps) >> (-int_ | eps | *char_ | eps);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }

}
