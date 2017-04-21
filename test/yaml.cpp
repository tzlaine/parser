/**
 *   Copyright (C) 2010, 2011 Object Modeling Designs
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <yaml/parser/yaml_def.hpp>
#include <iostream>
#include <fstream>
#include <string>

#include <boost/spirit/include/classic_position_iterator.hpp>

typedef std::string::const_iterator base_iterator_type;
typedef boost::spirit::classic::position_iterator<base_iterator_type>
    iterator_type;

template struct omd::yaml::parser::yaml<iterator_type>;
