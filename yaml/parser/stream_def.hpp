/**
 *   Copyright (C) 2010 Zach Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef YAML_PARSER_STREAM_DEF_HPP
#define YAML_PARSER_STREAM_DEF_HPP

#include <yaml/parser/stream.hpp>

#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_container.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>


namespace omd { namespace yaml { namespace parser {

    template <typename Iterator>
    stream<Iterator>::stream (std::string const & source_file)
        : error_handler_ (error_handler_t(source_file))
    {
        qi::attr_type attr;
        qi::omit_type omit;
        qi::char_type char_;
        qi::_val_type _val;
        qi::_1_type _1;
        qi::_2_type _2;
        qi::_3_type _3;
        qi::_4_type _4;
        qi::lit_type lit;
        qi::blank_type blank;
        qi::eoi_type eoi;
        qi::eol_type eol;

        namespace phx = boost::phoenix;

        auto pb = phx::push_back(_val, _1);

        auto & full_bom = block_styles_.flow_styles_.basic_structures_.characters_.full_bom;

        auto & directive = block_styles_.flow_styles_.basic_structures_.directive;
        auto & l_comment = block_styles_.flow_styles_.basic_structures_.l_comment;
        auto & s_l_comments = block_styles_.flow_styles_.basic_structures_.s_l_comments;

        auto & block_node = block_styles_.block_node;


        // [202]
        document_prefix =
            -full_bom >> +l_comment
            ;

        // [205]
        document_suffix =
            "..." >> s_l_comments
            ;

        // [206]
        forbidden =
            /* TODO: This should properly begin with start of line. */
            /* >> */
                (lit("---") | "...")
            >>  (eol | blank | eoi)
            ;

        // [207]
        bare_document =
            block_node(-1, context_t::block_in) - forbidden
            ;

        // [208]
        explicit_document =
                "---"
            >>  *lit(' ')
            >>  (bare_document | attr(ast::value_t()) >> s_l_comments)
            ;

        // [209]
        directive_document =
            +directive >>  explicit_document
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
                    +document_suffix >> *document_prefix >> any_document[pb]
                 |  *document_prefix >> explicit_document[pb]
                 )
            >>  *document_suffix >> *document_prefix
            >   omit[end_of_input]
            ;

        // Allow empty and comment lines at end of input.
        end_of_input =
                *(
                    +blank >> '#' >> *(char_ - eol) >> eol
                |   *blank >> eol
                )
            >>  eoi
            ;

        BOOST_SPIRIT_DEBUG_NODES(
            (document_prefix)
            (document_suffix)
            (forbidden)
            (bare_document)
            (explicit_document)
            (directive_document)
            (any_document)
            (yaml_stream)
            (end_of_input)
        );

        qi::on_error<qi::fail>(yaml_stream, error_handler_(_1, _2, _3, _4));
    }

} } }

#endif
