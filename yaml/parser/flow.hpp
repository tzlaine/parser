/**
 *   Copyright (C) 2010, 2011 Object Modeling Designs
 */

#if !defined(OMD_PARSER_FLOW_HPP)
#define OMD_PARSER_FLOW_HPP

#define BOOST_SPIRIT_NO_PREDEFINED_TERMINALS

#include <string>
#include "scalar.hpp"

namespace omd { namespace parser
{
    template <typename Iterator>
    struct white_space : qi::grammar<Iterator>
    {
        white_space();
        qi::rule<Iterator> start;
    };

    template <typename Iterator>
    struct flow : qi::grammar<Iterator, ast::value_t(), white_space<Iterator> >
    {
        flow(int& indent, std::string const& source_file = "");

        typedef std::pair<ast::string_t, ast::value_t> map_element_t;
        typedef white_space<Iterator> white_space_t;

        qi::rule<Iterator, ast::value_t(), white_space_t> flow_start;
        qi::rule<Iterator, ast::value_t(), white_space_t> flow_value;
        qi::rule<Iterator, ast::object_t(), white_space_t> object;
        qi::rule<Iterator, map_element_t(), white_space_t> member_pair;
        qi::rule<Iterator, ast::array_t(), white_space_t> array;
        qi::rule<Iterator, ast::anchored_object_t(), white_space_t> anchored_value;
        qi::rule<Iterator, ast::anchored_object_t(), white_space_t> top_anchored_value;
        scalar<Iterator> scalar_value;

        typedef omd::parser::error_handler<Iterator> error_handler_t;
        boost::phoenix::function<error_handler_t> const error_handler;
    };
}}

#endif
