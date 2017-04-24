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

#include <yaml/parser/flow.hpp>
#include <string>
#include <boost/fusion/adapted/std_pair.hpp>


namespace omd { namespace yaml { namespace parser {

    enum class chomping_t
    {
        strip, clip, keep
    };

    struct block_header_t
    {
        block_header_t ()
            : chomping_ (chomping_t::clip), indentation_ (0)
        {}
        block_header_t (chomping_t chomping, int indentation)
            : chomping_ (chomping), indentation_ (indentation)
        {}

        chomping_t chomping_;
        int indentation_;
    };

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

        qi::rule<Iterator, std::string()> l_empty;

        qi::rule<
            Iterator,
            block_header_t(),
            qi::locals<chomping_t, int>
        > block_header;

        qi::rule<Iterator, int()> indentation_indicator;
        qi::rule<Iterator, chomping_t()> chomping_indicator;
        qi::rule<Iterator, std::string(chomping_t)> chomped_empty;
        qi::rule<Iterator, std::string()> strip_empty;
        qi::rule<Iterator, std::string()> keep_empty;
        qi::rule<Iterator, std::string()> trail_comments;

        qi::rule<
            Iterator,
            std::string(),
            qi::locals<chomping_t, int>
        > literal;

        qi::rule<Iterator, std::string()> l_nb_literal_text;
        qi::rule<Iterator, std::string()> b_nb_literal_text;
        qi::rule<Iterator, std::string(chomping_t)> literal_content;

        int n_; // our current indent level (spaces)

        typedef omd::yaml::parser::error_handler<Iterator> error_handler_t;
        boost::phoenix::function<error_handler_t> const error_handler;
    };

} } }

#endif
