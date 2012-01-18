/**
 *   Copyright (C) 2010, 2011 Object Modeling Designs
 *   consultomd.com
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if !defined(OMD_PARSER_BLOCK_HPP)
#define OMD_PARSER_BLOCK_HPP

#define BOOST_SPIRIT_NO_PREDEFINED_TERMINALS

#include "flow.hpp"
#include <string>
#include <boost/fusion/adapted/std_pair.hpp>

namespace omd { namespace yaml { namespace parser
{
    template <typename Iterator>
    struct block : qi::grammar<Iterator, ast::value_t()>
    {
        block(std::string const& source_file = "");

        typedef white_space<Iterator> white_space_t;
        typedef flow<Iterator> flow_t;

        qi::symbols<char> anchors;
        white_space_t ws;
        qi::rule<Iterator> end_of_input;

        qi::rule<Iterator, ast::value_t()> block_node;
        qi::rule<Iterator, ast::anchored_object_t()> anchored_block_node;
        qi::rule<Iterator, ast::value_t()> indented_block;
        qi::rule<Iterator, ast::value_t()> compact_block;
        flow_t flow_g;

        qi::rule<Iterator> indent;
        qi::rule<Iterator> skip_indent;
        qi::rule<Iterator> skip_indent_child;
        qi::rule<Iterator, ast::value_t()> start;
        qi::rule<Iterator, ast::value_t(), qi::locals<int> > blocks;
        qi::rule<Iterator, ast::value_t(), qi::locals<int> > flow_compound;

        qi::rule<Iterator, std::string(), qi::locals<char, char, bool> > block_literal;
        qi::rule<Iterator, ast::array_t()> block_seq;
        qi::rule<Iterator, ast::value_t()> block_seq_entry;
        qi::rule<Iterator, ast::object_t()> implicit_block_map;
        qi::rule<Iterator, ast::object_t()> explicit_block_map;
        qi::rule<Iterator, ast::object_element_t()> block_map_entry;
        qi::rule<Iterator, ast::object_element_t()> explicit_block_map_entry;
        qi::rule<Iterator, ast::object_element_t()> implicit_block_map_entry;

        int current_indent; // our current indent level (spaces)

        typedef omd::yaml::parser::error_handler<Iterator> error_handler_t;
        boost::phoenix::function<error_handler_t> const error_handler;
    };
}}}

#endif
