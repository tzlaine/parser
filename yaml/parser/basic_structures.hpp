/**
 *   Copyright (C) 2017 Zach Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef YAML_PARSER_BASIC_STRUCTURES_HPP
#define YAML_PARSER_BASIC_STRUCTURES_HPP

#include <yaml/parser/characters.hpp>


namespace omd { namespace yaml { namespace parser {

    template <typename Iterator>
    struct basic_structures
    {
        basic_structures ();

        characters<Iterator> characters_;

        qi::rule<Iterator, std::string(int)> indent;    // indent exactly n spaces
        qi::rule<Iterator, std::string(int)> indent_lt; // indent <= n spaces
        qi::rule<Iterator, std::string(int)> indent_le; // indent < n spaces
        qi::rule<Iterator, std::string()> separate_in_line;
        // TODO: All comments should probably return void.
        qi::rule<Iterator, std::string(int, context_t)> line_prefix;
        qi::rule<Iterator, std::string(int, context_t)> l_empty;
        qi::rule<Iterator, std::string(int, context_t)> b_l_folded;
        qi::rule<Iterator, std::string(int)> flow_folded;
        qi::rule<Iterator, std::string()> comment_text;
        qi::rule<Iterator, std::string()> s_b_comment;
        qi::rule<Iterator, std::string()> l_comment;
        qi::rule<Iterator, std::string()> s_l_comments;
        qi::rule<Iterator, std::string(int, context_t)> separate;
        qi::rule<Iterator, std::string(int)> separate_lines;

        qi::rule<Iterator> directive;
        qi::rule<Iterator> reserved_directive;
        qi::rule<Iterator, qi::locals<unsigned int>> yaml_directive;
        qi::rule<Iterator> tag_directive;
        qi::rule<Iterator> tag_handle;
        qi::rule<Iterator> tag_prefix;

        qi::rule<
            Iterator,
            ast::properties_t(int, context_t),
            qi::locals<ast::string_t, ast::string_t>
        > properties;

        qi::rule<Iterator, std::string()> tag_property;
        qi::rule<Iterator, std::string()> anchor_property;
        qi::rule<Iterator, std::string()> anchor_name;
    };

} } }

#endif
