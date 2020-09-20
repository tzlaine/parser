// Copyright (C) 2020 T. Zachary Laine
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_PARSER_CONFIG_HPP
#define BOOST_PARSER_CONFIG_HPP

// Included for definition of __cpp_lib_concepts.
#include <iterator>


#ifdef BOOST_PARSER_DOXYGEN

/** Boost.Parser uses assertions (`BOOST_ASSERT()`) in several places to
    indicate that your use of the library has an error in it.  All of those
    places could heve instead been ill-formed code, caught at compile time.
    It is far quicker and easier to determine exactly where in your code such
    an error is located if this is a runtime failure; you can just look at the
    stack in your favorite debugger.  However, if you want to make thes kinds
    of errors always ill-formed code, define this macro. */
#    define BOOST_PARSER_NO_RUNTIME_ASSERTIONS

/** Asserts that the given condition is true.  If
    `BOOST_PARSER_NO_RUNTIME_ASSERTIONS` macro is defined by the user,
    `BOOST_PARSER_ASSERT` expends to a compile-time `static_assert()`.
    Otherwise, it expands to a run-time `BOOST_ASSERT()`. */
#    define BOOST_PARSER_ASSERT(condition)

/** Boost.Parser will automatically use concepts to constrain templates when
    building in C++20 mode, if the compiler defines `__cpp_lib_concepts`.  To
    disable the use of concepts, define this macro. */
#    define BOOST_PARSER_DISABLE_CONCEPTS

/** Define this macro to remove all Boost dependencies from Boost.Parser. */
#    define BOOST_PARSER_STANDALONE

#else

#    ifdef BOOST_PARSER_NO_RUNTIME_ASSERTIONS
#        define BOOST_PARSER_ASSERT(condition) static_assert(condition)
#    else
#        define BOOST_PARSER_ASSERT(condition) BOOST_ASSERT(condition)
#    endif

#endif

#if defined(__cpp_lib_concepts) && !defined(BOOST_PARSER_DISABLE_CONCEPTS)
#define BOOST_PARSER_USE_CONCEPTS 1
#else
#define BOOST_PARSER_USE_CONCEPTS 0
#endif

#if !defined(BOOST_PARSER_STANDALONE)
#define BOOST_PARSER_USE_BOOST 1
#else
#define BOOST_PARSER_USE_BOOST 0
#endif

#endif
