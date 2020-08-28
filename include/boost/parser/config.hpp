// Copyright (C) 2020 T. Zachary Laine
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_PARSER_CONFIG_HPP
#define BOOST_PARSER_CONFIG_HPP

// Included for definition of __cpp_lib_concepts.
#include <iterator>

#if 1

#define BOOST_PARSER_USE_CONCEPTS 1
#if !defined(__cpp_lib_concepts)
#error "Concepts required."
#endif

#else // TODO: Re-enable this if/when SFINAE version is in place.

#if defined(__cpp_lib_concepts) && !defined(BOOST_PARSER_DISABLE_CONCEPTS)
#define BOOST_PARSER_USE_CONCEPTS 1
#else
#define BOOST_PARSER_USE_CONCEPTS 0
#endif

// The inline namespaces v1 and v2 represent pre- and post-C++20.  v1 is
// inline for standards before C++20, and v2 is inline for C++20 and later.
// Note that this only applies to code for which a v2 namespace alternative
// exists.  Some instances of the v1 namespace may still be inline, if there
// is no v2 version of its contents.
#if BOOST_PARSER_USE_CONCEPTS
#    define BOOST_PARSER_NAMESPACE_V1 namespace v1
#    define BOOST_PARSER_NAMESPACE_V2 inline namespace v2
#else
#    define BOOST_PARSER_NAMESPACE_V1 inline namespace v1
#    define BOOST_PARSER_NAMESPACE_V2 namespace v2
#endif

#endif

#endif
