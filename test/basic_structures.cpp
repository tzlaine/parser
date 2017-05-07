/**
 *   Copyright (C) 2017 Zach Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <yaml/parser/basic_structures_def.hpp>
#include <iostream>
#include <fstream>
#include <string>

using char_iterator_t = yaml::parser::ustring_t::const_iterator;
template struct yaml::parser::basic_structures_t<char_iterator_t>;
