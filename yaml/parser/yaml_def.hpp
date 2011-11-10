/**
 *   Copyright (C) 2010, 2011 Object Modeling Designs
 */

#if !defined(OMD_PARSER_YAML_DEF_HPP)
#define OMD_PARSER_YAML_DEF_HPP

#include "yaml.hpp"

namespace omd { namespace parser
{
    template <typename Iterator>
    yaml<Iterator>::yaml(std::string const& source_file)
      : yaml::base_type(start),
        error_handler(error_handler_t(source_file))
    {
        qi::skip_type skip;
        auto space = ws.start.alias();

        start = skip(space)[flow_value];

        qi::_1_type _1;
        qi::_2_type _2;
        qi::_3_type _3;
        qi::_4_type _4;
        qi::on_error<qi::fail>(start, error_handler(_1, _2, _3, _4));
    }
}}

#endif
