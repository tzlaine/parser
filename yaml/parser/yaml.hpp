/**
 *   Copyright (C) 2010, 2011, 2012 Object Modeling Designs
 *   consultomd.com
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if !defined(OMD_PARSER_YAML_HPP)
#define OMD_PARSER_YAML_HPP

#define BOOST_SPIRIT_NO_PREDEFINED_TERMINALS

#include "flow.hpp"
#include "block.hpp"
#include <string>
#include <boost/fusion/adapted/std_pair.hpp>

namespace omd { namespace yaml { namespace parser
{
    template <typename Iterator>
    struct yaml : qi::grammar<Iterator, ast::value_t()>
    {
        yaml(std::string const& source_file = "");

        typedef white_space<Iterator> white_space_t;
        typedef block<Iterator> block_t;

        white_space_t ws;

        block_t block_g;
        qi::rule<Iterator, ast::value_t()> stream;
        qi::rule<Iterator, ast::value_t()> document;
        qi::rule<Iterator, ast::value_t()> implicit_document;
        qi::rule<Iterator, ast::array_t()> explicit_document;

        typedef omd::yaml::parser::error_handler<Iterator> error_handler_t;
        boost::phoenix::function<error_handler_t> const error_handler;
    };
}}}

#endif
