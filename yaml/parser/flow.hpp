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
        flow(std::string const& source_file = "");

        typedef std::pair<ast::value_t, ast::value_t> element_t;
        typedef white_space<Iterator> white_space;

        qi::rule<Iterator, ast::value_t(), white_space> value;
        qi::rule<Iterator, ast::object_t(), white_space> object;
        qi::rule< Iterator, element_t(), white_space > member_pair;
        qi::rule<Iterator, ast::array_t(), white_space> array;
        scalar<Iterator> scalar_value;

        typedef omd::parser::error_handler<Iterator> error_handler_t;
        boost::phoenix::function<error_handler_t> const error_handler;
    };
}}

#endif
