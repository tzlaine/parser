/**
 *   Copyright (C) 2010, 2011, 2012 Object Modeling Designs
 *   consultomd.com
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if !defined(OMD_PARSER_YAML_DEF_HPP)
#define OMD_PARSER_YAML_DEF_HPP

#include <yaml/parser/yaml.hpp>

#include <algorithm>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_container.hpp>
#include <boost/spirit/include/phoenix_statement.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

namespace omd { namespace yaml { namespace parser
{
    template <typename Iterator>
    yaml<Iterator>::yaml(std::string const& source_file)
      : yaml::base_type(stream),
        block_g(source_file),
        error_handler(error_handler_t(source_file))
    {
        namespace phx = boost::phoenix;
        using boost::spirit::qi::copy;

        qi::skip_type skip;
        auto space = ws.start.alias();

        qi::_1_type _1;
        qi::_2_type _2;
        qi::_3_type _3;
        qi::_4_type _4;
        qi::char_type char_;

        qi::eol_type eol;
        qi::blank_type blank;

        auto comment = copy('#' >> *(char_ - eol) >> eol);  // comments
        auto blank_eol = copy(*blank >> (comment | eol));   // empty until eol

        stream =
            skip(space)[document > block_g.end_of_input]
            ;

        document =
                explicit_document
            |   implicit_document
            ;

        explicit_document =
                +((skip(space)["---"] >> blank_eol) > implicit_document)
            >>  -skip(space)["..."]
            ;

        implicit_document =
                block_g.flow_compound
            |   block_g
            ;

        BOOST_SPIRIT_DEBUG_NODES(
            (stream)
            (document)
            (explicit_document)
            (implicit_document)
        );

        qi::on_error<qi::fail>(stream, error_handler(_1, _2, _3, _4));
    }
}}}

#endif
