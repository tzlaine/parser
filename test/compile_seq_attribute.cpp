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

void compile_seq_attribute()
{
    char const chars[] = "";
    auto first = std::begin(chars);
    auto const last = std::end(chars);

    // scalar and eps
    {
        constexpr auto parser = int_ >> eps;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<int>>));
    }
    {
        constexpr auto parser = eps >> int_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<int>>));
    }

    // scalar >> scalar
    {
        constexpr auto parser = char_ >> char_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<char>>>));
    }
    {
        constexpr auto parser = eps >> char_ >> char_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<char>>>));
    }
    {
        constexpr auto parser = char_ >> eps >> char_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<char>>>));
    }
    {
        constexpr auto parser = char_ >> char_ >> eps;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<char>>>));
    }
    {
        constexpr auto parser = int_ >> char_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<int, char>>>));
    }
    {
        constexpr auto parser = eps >> int_ >> char_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<int, char>>>));
    }
    {
        constexpr auto parser = int_ >> eps >> char_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<int, char>>>));
    }
    {
        constexpr auto parser = int_ >> char_ >> eps;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<tuple<int, char>>>));
    }

    // -scalar >> -scalar
    {
        constexpr auto parser = -char_ >> -char_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT(
            (is_same<attr_t, optional<std::vector<optional<char>>>>));
    }
    {
        constexpr auto parser = eps >> -char_ >> -char_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT(
            (is_same<attr_t, optional<std::vector<optional<char>>>>));
    }
    {
        constexpr auto parser = -char_ >> eps >> -char_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT(
            (is_same<attr_t, optional<std::vector<optional<char>>>>));
    }
    {
        constexpr auto parser = -char_ >> -char_ >> eps;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT(
            (is_same<attr_t, optional<std::vector<optional<char>>>>));
    }
    {
        constexpr auto parser = -int_ >> -char_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT(
            (is_same<attr_t, optional<tuple<optional<int>, optional<char>>>>));
    }
    {
        constexpr auto parser = eps >> -int_ >> -char_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT(
            (is_same<attr_t, optional<tuple<optional<int>, optional<char>>>>));
    }
    {
        constexpr auto parser = -int_ >> eps >> -char_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT(
            (is_same<attr_t, optional<tuple<optional<int>, optional<char>>>>));
    }
    {
        constexpr auto parser = -int_ >> -char_ >> eps;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT(
            (is_same<attr_t, optional<tuple<optional<int>, optional<char>>>>));
    }

    // seq<T> >> seq<T>
    {
        constexpr auto parser = *char_ >> *char_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<char>>>));
    }
    {
        constexpr auto parser = eps >> *char_ >> *char_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<char>>>));
    }
    {
        constexpr auto parser = *char_ >> eps >> *char_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<char>>>));
    }
    {
        constexpr auto parser = *char_ >> *char_ >> eps;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<char>>>));
    }
    {
        constexpr auto parser = *string("str") >> *string("str");
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::string>>));
    }
    {
        constexpr auto parser = eps >> *string("str") >> *string("str");
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::string>>));
    }
    {
        constexpr auto parser = *string("str") >> eps >> *string("str");
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::string>>));
    }
    {
        constexpr auto parser = *string("str") >> *string("str") >> eps;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::string>>));
    }

    // seq<T> >> seq<U>
    {
        constexpr auto parser = *char_ >> *string("str");
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT(
            (is_same<attr_t, optional<tuple<std::vector<char>, std::string>>>));
    }
    {
        constexpr auto parser = eps >> *char_ >> *string("str");
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT(
            (is_same<attr_t, optional<tuple<std::vector<char>, std::string>>>));
    }
    {
        constexpr auto parser = *char_ >> eps >> *string("str");
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT(
            (is_same<attr_t, optional<tuple<std::vector<char>, std::string>>>));
    }
    {
        constexpr auto parser = *char_ >> *string("str") >> eps;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT(
            (is_same<attr_t, optional<tuple<std::vector<char>, std::string>>>));
    }

    // seq<T> >> T
    {
        constexpr auto parser = *char_ >> char_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<char>>>));
    }
    {
        constexpr auto parser = eps >> *char_ >> char_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<char>>>));
    }
    {
        constexpr auto parser = *char_ >> eps >> char_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<char>>>));
    }
    {
        constexpr auto parser = *char_ >> char_ >> eps;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<char>>>));
    }
    {
        constexpr auto parser = *string("str") >> char_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::string>>));
    }
    {
        constexpr auto parser = eps >> *string("str") >> char_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::string>>));
    }
    {
        constexpr auto parser = *string("str") >> eps >> char_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::string>>));
    }
    {
        constexpr auto parser = *string("str") >> char_ >> eps;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::string>>));
    }

    // T >> seq<T>
    {
        constexpr auto parser = char_ >> *char_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<char>>>));
    }
    {
        constexpr auto parser = eps >> char_ >> *char_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<char>>>));
    }
    {
        constexpr auto parser = char_ >> eps >> *char_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<char>>>));
    }
    {
        constexpr auto parser = char_ >> *char_ >> eps;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<char>>>));
    }
    {
        constexpr auto parser = char_ >> *string("str");
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::string>>));
    }
    {
        constexpr auto parser = eps >> char_ >> *string("str");
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::string>>));
    }
    {
        constexpr auto parser = char_ >> eps >> *string("str");
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::string>>));
    }
    {
        constexpr auto parser = char_ >> *string("str") >> eps;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::string>>));
    }

    // seq<T> >> optional<T>
    {
        constexpr auto parser = *char_ >> -char_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<char>>>));
    }
    {
        constexpr auto parser = eps >> *char_ >> -char_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<char>>>));
    }
    {
        constexpr auto parser = *char_ >> eps >> -char_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<char>>>));
    }
    {
        constexpr auto parser = *char_ >> -char_ >> eps;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<char>>>));
    }
    {
        constexpr auto parser = *string("str") >> -char_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::string>>));
    }
    {
        constexpr auto parser = eps >> *string("str") >> -char_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::string>>));
    }
    {
        constexpr auto parser = *string("str") >> eps >> -char_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::string>>));
    }
    {
        constexpr auto parser = *string("str") >> -char_ >> eps;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::string>>));
    }

    // optional<T> >> seq<T>
    {
        constexpr auto parser = -char_ >> *char_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<char>>>));
    }
    {
        constexpr auto parser = eps >> -char_ >> *char_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<char>>>));
    }
    {
        constexpr auto parser = -char_ >> eps >> *char_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<char>>>));
    }
    {
        constexpr auto parser = -char_ >> *char_ >> eps;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::vector<char>>>));
    }
    {
        constexpr auto parser = -char_ >> *string("str");
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::string>>));
    }
    {
        constexpr auto parser = eps >> -char_ >> *string("str");
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::string>>));
    }
    {
        constexpr auto parser = -char_ >> eps >> *string("str");
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::string>>));
    }
    {
        constexpr auto parser = -char_ >> *string("str") >> eps;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, optional<std::string>>));
    }
}
