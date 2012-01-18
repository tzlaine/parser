/**
 *   Copyright (C) 2010, 2011 Object Modeling Designs
 */

#include "../yaml/parser/flow_def.hpp"
#include <iostream>
#include <fstream>
#include <string>

#include <boost/spirit/include/support_istream_iterator.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>

#include <boost/spirit/include/classic_position_iterator.hpp>

typedef std::string::const_iterator base_iterator_type;
typedef boost::spirit::classic::position_iterator<base_iterator_type>
    iterator_type;

template struct omd::parser::white_space<iterator_type>;
template struct omd::parser::flow<iterator_type>;
