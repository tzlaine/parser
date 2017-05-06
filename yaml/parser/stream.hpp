/**
 *   Copyright (C) 2017 Zach Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef YAML_PARSER_STREAM_HPP
#define YAML_PARSER_STREAM_HPP

#define BOOST_SPIRIT_NO_PREDEFINED_TERMINALS

#include <yaml/parser/block_styles.hpp>


#ifndef YAML_HEADER_ONLY
#define YAML_HEADER_ONLY 1
#endif


namespace yaml { namespace parser {

    template <typename Iterator>
    struct stream
    {
        stream (
            std::string const & source_file,
            reporting_fn_t const & errors_callback,
            reporting_fn_t const & warnings_callback
        );

        block_styles<Iterator> block_styles_;

        qi::rule<Iterator, qi::locals<eoi_state_t>> document_prefix;
        qi::rule<Iterator, qi::locals<eoi_state_t>> document_suffix;
        qi::rule<Iterator> forbidden;
        qi::rule<Iterator, ast::value_t()> bare_document;
        qi::rule<Iterator, ast::value_t(), qi::locals<eoi_state_t>> explicit_document;
        qi::rule<Iterator, ast::value_t()> directive_document;
        qi::rule<Iterator, ast::value_t()> any_document;
        qi::rule<Iterator, std::vector<ast::value_t>()> yaml_stream;

        qi::rule<Iterator> end_of_input;

        boost::phoenix::function<error_handler_t> const error_handler_;
    };

#if YAML_HEADER_ONLY
    inline
#endif
    encoding_t read_bom (std::istream & is);

    template <typename Iter>
    encoding_t read_bom (Iter & first, Iter last);

#if YAML_HEADER_ONLY
    inline
#endif
    boost::optional<std::vector<ast::value_t>> parse_yaml(
        std::istream & is,
        std::string const & source_file = "",
        reporting_fn_t const & errors_callback = reporting_fn_t(),
        reporting_fn_t const & warnings_callback = reporting_fn_t()
    );

} }

#endif
