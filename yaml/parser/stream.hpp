/**
 *   Copyright (C) 2017 Zach Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef YAML_PARSER_STREAM_HPP
#define YAML_PARSER_STREAM_HPP

#include <yaml/parser/parser_fwd.hpp>
#include <yaml/parser/block_styles.hpp>


namespace yaml { namespace parser {

    struct stream_t
    {
        explicit stream_t (bool verbose);

        void set_error_handler_params (
            iterator_t & first,
            iterator_t last,
            std::string const & source_file,
            reporting_fn_t const & errors,
            reporting_fn_t const & warnings
        );
 
        void reset_error_handler_params ();

        block_styles_t block_styles_;

        qi::rule<iterator_t, qi::locals<eoi_state_t>> document_prefix;
        qi::rule<iterator_t, qi::locals<eoi_state_t>> document_suffix;
        qi::rule<iterator_t> forbidden;
        qi::rule<iterator_t, ast::value_t()> bare_document;
        qi::rule<iterator_t, ast::value_t(), qi::locals<eoi_state_t>> explicit_document;
        qi::rule<iterator_t, ast::value_t()> directive_document;
        qi::rule<iterator_t, ast::value_t()> any_document;
        qi::rule<iterator_t, std::vector<ast::value_t>()> yaml_stream;

        qi::rule<iterator_t> end_of_input;

        boost::phoenix::function<error_handler_t> error_handler_;
    };

    YAML_HEADER_ONLY_INLINE
    encoding_t read_bom (std::istream & is);

    YAML_HEADER_ONLY_INLINE
    encoding_t read_bom (char const *& first, char const * last);

    YAML_HEADER_ONLY_INLINE
    encoding_t read_bom (iterator_t & first, iterator_t last);

    YAML_HEADER_ONLY_INLINE
    boost::optional<std::vector<ast::value_t>> parse_yaml(
        stream_t & parser,
        char const * raw_first,
        char const * raw_last,
        std::string const & source_file = "",
        reporting_fn_t const & errors_callback = reporting_fn_t(),
        reporting_fn_t const & warnings_callback = reporting_fn_t()
    );

    YAML_HEADER_ONLY_INLINE
    boost::optional<std::vector<ast::value_t>> parse_yaml(
        stream_t & parser,
        std::istream & is,
        std::string const & source_file = "",
        reporting_fn_t const & errors_callback = reporting_fn_t(),
        reporting_fn_t const & warnings_callback = reporting_fn_t()
    );

    YAML_HEADER_ONLY_INLINE
    boost::optional<std::vector<ast::value_t>> parse_yaml(
        char const * raw_first,
        char const * raw_last,
        std::string const & source_file = "",
        reporting_fn_t const & errors_callback = reporting_fn_t(),
        reporting_fn_t const & warnings_callback = reporting_fn_t(),
        bool verbose = false
    );

    YAML_HEADER_ONLY_INLINE
    boost::optional<std::vector<ast::value_t>> parse_yaml(
        std::istream & is,
        std::string const & source_file = "",
        reporting_fn_t const & errors_callback = reporting_fn_t(),
        reporting_fn_t const & warnings_callback = reporting_fn_t(),
        bool verbose = false
    );

} }

#if YAML_HEADER_ONLY
#include <yaml/parser/stream_def.hpp>
#endif

#endif
