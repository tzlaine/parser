/**
 *   Copyright (C) 2017 Zach Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef YAML_PARSER_STREAM_HPP
#define YAML_PARSER_STREAM_HPP

// TODO: Create a macro for YAML_HEADER_ONLY_INLINE
#ifndef YAML_HEADER_ONLY
#define YAML_HEADER_ONLY 1
#endif

#include <yaml/parser/block_styles.hpp>


namespace yaml { namespace parser {

    template <typename CharIter>
    struct stream_t
    {
        using iterator_t = pos_iterator<CharIter>;

        stream_t (
            std::string const & source_file,
            reporting_fn_t const & errors_callback,
            reporting_fn_t const & warnings_callback
        );

        block_styles_t<CharIter> block_styles_;

        qi::rule<iterator_t, qi::locals<eoi_state_t>> document_prefix;
        qi::rule<iterator_t, qi::locals<eoi_state_t>> document_suffix;
        qi::rule<iterator_t> forbidden;
        qi::rule<iterator_t, ast::value_t()> bare_document;
        qi::rule<iterator_t, ast::value_t(), qi::locals<eoi_state_t>> explicit_document;
        qi::rule<iterator_t, ast::value_t()> directive_document;
        qi::rule<iterator_t, ast::value_t()> any_document;
        qi::rule<iterator_t, std::vector<ast::value_t>()> yaml_stream;

        qi::rule<iterator_t> end_of_input;

        boost::phoenix::function<error_handler_t> const error_handler_;
    };

#if YAML_HEADER_ONLY
    inline
#endif
    encoding_t read_bom (std::istream & is);

    template <typename CharIter>
    encoding_t read_bom (pos_iterator<CharIter> & first, pos_iterator<CharIter> last,
                         typename std::enable_if<sizeof(typename CharIter::value_type) == 1u>::type* = 0);

    template <typename CharIter>
    encoding_t read_bom (pos_iterator<CharIter> & first, pos_iterator<CharIter> last,
                         typename std::enable_if<sizeof(typename CharIter::value_type) == 4u>::type* = 0);

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
