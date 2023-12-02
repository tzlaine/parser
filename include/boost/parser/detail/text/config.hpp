// Copyright (C) 2020 T. Zachary Laine
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_PARSER_DETAIL_TEXT_CONFIG_HPP
#define BOOST_PARSER_DETAIL_TEXT_CONFIG_HPP

#include <boost/parser/config.hpp>


#if !BOOST_PARSER_USE_CONCEPTS
#    define BOOST_PARSER_DETAIL_TEXT_USE_CONCEPTS 0
#else
// This is now hard-coded to use the pre-C++20 code path.  There are a bunch
// of really odd compile errorswith Clang+libstdc++ I can't be bothered to
// address right now.  (The latest version of Boost.Text might fix these
// errors, but there's also no pre-C++20 code path in that version of Text.)
#    define BOOST_PARSER_DETAIL_TEXT_USE_CONCEPTS 0
#endif

// The inline namespaces v1 and v2 represent pre- and post-C++20.  v1 is
// inline for standards before C++20, and v2 is inline for C++20 and later.
// Note that this only applies to code for which a v2 namespace alternative
// exists.  Some instances of the v1 namespace may still be inline, if there
// is no v2 version of its contents.
#if BOOST_PARSER_DETAIL_TEXT_USE_CONCEPTS
#    define BOOST_PARSER_DETAIL_TEXT_NAMESPACE_V1 namespace v1
#    define BOOST_PARSER_DETAIL_TEXT_NAMESPACE_V2 inline namespace v2
#else
#    define BOOST_PARSER_DETAIL_TEXT_NAMESPACE_V1 inline namespace v1
#    define BOOST_PARSER_DETAIL_TEXT_NAMESPACE_V2 namespace v2
#endif

#if BOOST_PARSER_DETAIL_TEXT_USE_CONCEPTS
namespace boost::parser::detail { namespace text { namespace detail {
    inline constexpr auto begin = std::ranges::begin;
    inline constexpr auto end = std::ranges::end;
}}}
#else
#include <boost/parser/detail/text/detail/begin_end.hpp>
#endif

#endif
