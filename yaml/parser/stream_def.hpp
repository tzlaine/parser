/**
 *   Copyright (C) 2017 Zach Laine
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


namespace yaml { namespace parser {

    namespace detail {

        struct check_encoding
        {
            template <typename, typename, typename>
            struct result { using type = void; };

            template <typename Pass>
            void operator() (
                encoding_t encoding,
                error_handler_t const & error_handler,
                Pass & pass
            ) const {
                if (encoding != encoding_t::utf8) {
                    std::stringstream oss;
                    oss << "BOM for encoding "
                        << encoding
                        << " was encountered in the stream, but only "
                        << encoding_t::utf8
                        << " encoding is supported.\n";
                    error_handler.report_error(oss.str());
                    pass = false;
                }
            }
        };

    }

    template <typename Iterator>
    stream<Iterator>::stream (
        std::string const & source_file,
        reporting_fn_t const & errors_callback,
        reporting_fn_t const & warnings_callback
    )
        : block_styles_ (error_handler_)
        , error_handler_ (error_handler_t(source_file, errors_callback, warnings_callback))
    {
        qi::attr_type attr;
        qi::omit_type omit;
        qi::raw_type raw;
        qi::char_type char_;
        qi::_pass_type _pass;
        qi::_val_type _val;
        qi::_1_type _1;
        qi::_2_type _2;
        qi::_3_type _3;
        qi::_4_type _4;
        qi::_a_type _a;
        qi::lit_type lit;
        qi::blank_type blank;
        qi::eps_type eps;
        qi::eoi_type eoi;
        qi::eol_type eol;

        namespace phx = boost::phoenix;
        using phx::function;

        phx::function<detail::check_encoding> check_encoding;
        function<detail::check_start_of_line> check_start_of_line;

        auto pb = phx::push_back(_val, _1);

        auto & full_bom = block_styles_.flow_styles_.basic_structures_.characters_.full_bom;

        auto & directive = block_styles_.flow_styles_.basic_structures_.directive;
        auto & l_comment = block_styles_.flow_styles_.basic_structures_.l_comment;
        auto & s_l_comments = block_styles_.flow_styles_.basic_structures_.s_l_comments;

        auto & block_node = block_styles_.block_node;


        // [202]
        document_prefix =
                -full_bom[check_encoding(_1, phx::cref(error_handler_.f), _pass)]
            >>  eps[_a = eoi_state_t::not_at_end] >> +l_comment(_a) >> eps(_a == eoi_state_t::not_at_end)
            ;

        // [205]
        document_suffix =
            "..." >> s_l_comments(_a = eoi_state_t::not_at_end)
            ;

        // [206]
        forbidden =
                raw[eps][check_start_of_line(_1, _pass)]
            >>  (lit("---") | "...")
            >>  (eol | blank | eoi)
            ;

        // [207]
        bare_document =
            block_node(-1, context_t::block_in) - forbidden
            ;

        // [208]
        explicit_document =
                "---"
            >>  (bare_document | attr(ast::value_t()) >> s_l_comments(_a = eoi_state_t::not_at_end))
            ;

        // [209]
        directive_document =
            +directive >> explicit_document
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
                *(*blank >> -('#' >> *(char_ - eol)) >> eol)
            >>  *blank >> -('#' >> *(char_ - eoi)) >> eoi
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

} }

#endif
