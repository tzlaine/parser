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
        typedef boost::iterator_range<Iterator> range_t;
        typedef std::pair<range_t, range_t> raw_block_t;

        white_space_t ws;
        qi::rule<Iterator, ast::value_t()> start;
        qi::rule<Iterator, ast::value_t()> flow;
        qi::rule<Iterator, ast::value_t()> scalar;
        //~ qi::rule<Iterator, ast::value_t&(ast::value_t&), white_space_t> block_content;
        flow_t flow_value;

        qi::rule<Iterator, std::size_t()> indent;
        qi::rule<Iterator> blank_line;
        qi::rule<Iterator, void(std::size_t)> line;
        qi::rule<Iterator> first_line;
        qi::rule<Iterator, raw_block_t(), qi::locals<std::size_t> > block;

        qi::rule<Iterator, ast::value_t()> blocks;

        typedef omd::parser::error_handler<Iterator> error_handler_t;
        boost::phoenix::function<error_handler_t> const error_handler;
    };
}}

#endif
