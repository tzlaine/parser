/**
 *   Copyright (C) 2010, 2011 Object Modeling Designs
 */

#if !defined(OMD_PARSER_YAML_HPP)
#define OMD_PARSER_YAML_HPP

#define BOOST_SPIRIT_NO_PREDEFINED_TERMINALS

#include <string>
#include "flow.hpp"

namespace omd { namespace parser
{
    template <typename Iterator>
    struct yaml : qi::grammar<Iterator, ast::value_t()>
    {
        yaml(std::string const& source_file = "");

        typedef white_space<Iterator> white_space_t;
        typedef flow<Iterator> flow_t;

        white_space_t ws;
        qi::rule<Iterator, ast::value_t()> start;
        flow_t flow_value;

        qi::rule<Iterator, std::size_t()> indent;
        qi::rule<Iterator> blank_line;
        qi::rule<Iterator, std::string(std::size_t)> line;
        qi::rule<Iterator, std::string()> first_line;
        qi::rule<Iterator, std::string(), qi::locals<std::size_t> > block;

        qi::rule<Iterator, ast::array_t()> blocks;

        typedef omd::parser::error_handler<Iterator> error_handler_t;
        boost::phoenix::function<error_handler_t> const error_handler;
    };
}}

#endif
