/**
 *   Copyright (C) 2010, 2011 Object Modeling Designs
 */

#if !defined(OMD_PARSER_YAML_HPP)
#define OMD_PARSER_YAML_HPP

#define BOOST_SPIRIT_NO_PREDEFINED_TERMINALS

#include "flow.hpp"
#include <string>
#include <boost/fusion/adapted/std_pair.hpp>

namespace omd { namespace parser
{
    template <typename Iterator>
    struct yaml : qi::grammar<Iterator, ast::value_t()>
    {
        yaml(std::string const& source_file = "");

        typedef white_space<Iterator> white_space_t;
        typedef flow<Iterator> flow_t;
        typedef std::pair<ast::value_t, ast::value_t> map_element_t;

        white_space_t ws;
        qi::rule<Iterator, ast::value_t()> yaml_start;
        flow_t flow_g;

        qi::rule<Iterator, std::size_t()> indent;
        qi::rule<Iterator, ast::value_t()> blocks;
        qi::rule<Iterator, ast::array_t(), qi::locals<std::size_t> > block_seq;
        qi::rule<Iterator, ast::value_t(std::size_t)> block_seq_entry;
        qi::rule<Iterator, ast::object_t(), qi::locals<std::size_t> > block_map;
        qi::rule<Iterator, map_element_t(std::size_t)> block_map_entry;

        typedef omd::parser::error_handler<Iterator> error_handler_t;
        boost::phoenix::function<error_handler_t> const error_handler;
    };
}}

#endif
