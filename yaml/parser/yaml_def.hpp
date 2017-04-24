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

        qi::_val_type _val;
        qi::_1_type _1;
        qi::_2_type _2;
        qi::_3_type _3;
        qi::_4_type _4;
        qi::char_type char_;
        qi::digit_type digit;
        qi::attr_type attr;
        qi::eol_type eol;
        qi::eoi_type eoi;
        qi::blank_type blank;

        auto comment = copy('#' >> *(char_ - eol) >> eol);  // comments
        auto blank_eol = copy(*blank >> (comment | eol));   // empty until eol

        auto & ns_char = block_g.flow_g.scalar_value.string_value.ns_char;
        auto & tag_char = block_g.flow_g.scalar_value.string_value.tag_char;
        auto & uri_char = block_g.flow_g.scalar_value.string_value.uri_char;
        auto & tag_handle = block_g.flow_g.scalar_value.tag_handle;

        auto pb = phx::push_back(_val, _1);

        stream =
            skip(space)[document > block_g.end_of_input]
            ;

        document =
                explicit_document
            |   implicit_document
            ;

        explicit_document_ =
                +((skip(space)["---"] >> blank_eol) > implicit_document)
            >>  -skip(space)["..."]
            ;

        implicit_document =
                block_g.flow_compound
            |   block_g
            ;

        // [82]
        directive =
                '%'
            >>  (yaml_directive | tag_directive | reserved_directive)
            >>  -comment
            ;

        // [83]
        reserved_directive =
                +ns_char
            >>  *(+blank >> +ns_char)
            ;

        // [86]
        yaml_directive =
            "YAML" >> +blank >> +digit >> '.' >> +digit
            // TODO [report warnings and errors for YAML versions != 1.2]
            ;

        // [88]
        tag_directive =
            "TAG" >> +blank >> tag_handle >> +blank >> tag_prefix
            // TODO [add tag to tag symbol table]
            ;

        // [93]
        tag_prefix =
                '!' >> *uri_char
            |   tag_char >> *uri_char
            ;

        // [202]
        document_prefix =
            /* TODO -bom >> */ *comment
            ;

        // [205]
        document_suffix =
            "..." >> comment
            ;

        // [206]
        forbidden =
                eol
            |   eoi
            |   blank
            |   "---"
            |   "..."
            /* | TODO: Detect start of line. */
            ;

        // [207]
        bare_document =
            block_g/*TODO block_node*/ - forbidden
            ;

        // [208]
        explicit_document =
                "---"
            >>  (bare_document | comment >> attr(ast::value_t()))
            ;

        // [209]
        directive_document =
                +directive
            >>  explicit_document
            ;

        // [210]
        any_document =
                directive_document
            |   explicit_document
            |   bare_document
            ;

        // [211]
        yaml_stream =
                *document_prefix
            >>  -any_document[pb]
            >>  *(
                    +document_suffix >> *document_prefix >> -any_document[pb]
                 |  *document_prefix -explicit_document[pb]
                 )
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
