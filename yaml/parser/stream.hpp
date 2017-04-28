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
        stream (std::string const & source_file);

        block_styles<Iterator> block_styles_;

        qi::rule<Iterator> document_prefix;
        qi::rule<Iterator> document_suffix;
        qi::rule<Iterator> forbidden;
        qi::rule<Iterator, ast::value_t()> bare_document;
        qi::rule<Iterator, ast::value_t()> explicit_document;
        qi::rule<Iterator, ast::value_t()> directive_document;
        qi::rule<Iterator, ast::value_t()> any_document;
        qi::rule<Iterator, std::vector<ast::value_t>()> yaml_stream;

        qi::rule<Iterator> end_of_input;

        using error_handler_t = error_handler<Iterator>;
        boost::phoenix::function<error_handler_t> const error_handler_;
    };

#if YAML_HEADER_ONLY
    inline
#endif
    bool parse_yaml(
        std::istream & is,
        std::vector<ast::value_t> & result,
        std::string const& source_file = ""
    );

} }

#include <yaml/detail/parse_impl.hpp>

#endif
