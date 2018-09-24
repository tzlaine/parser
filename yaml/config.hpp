/**
 *   Copyright (C) 2017 Zach Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_YAML_CONFIG_HPP
#define BOOST_YAML_CONFIG_HPP


#ifndef BOOST_YAML_HEADER_ONLY
#define BOOST_YAML_HEADER_ONLY 0
#endif

#if BOOST_YAML_HEADER_ONLY
#define BOOST_YAML_HEADER_ONLY_INLINE inline
#else
#define BOOST_YAML_HEADER_ONLY_INLINE
#endif

#ifndef BOOST_YAML_NO_SPIRIT_DEBUGGING
#define BOOST_SPIRIT_DEBUG
#endif

#define BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
#define BOOST_SPIRIT_ACTIONS_ALLOW_ATTR_COMPAT
#define BOOST_SPIRIT_UNICODE

#endif
