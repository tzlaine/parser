/**
 *   Copyright (C) 2017 T. Zachary Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See
 *   accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_YAML_PARSER_BASIC_STRUCTURES_HPP
#define BOOST_YAML_PARSER_BASIC_STRUCTURES_HPP

#include <boost/yaml/parser/parser_fwd.hpp>
#include <boost/yaml/parser/characters.hpp>


namespace boost { namespace yaml { namespace parser {

    struct basic_structures_t
    {
        explicit basic_structures_t(
            boost::phoenix::function<error_handler_t> & error_handler,
            bool verbose);

        characters_t characters_;

        qi::rule<iterator_t, void(int)> indent;    // indent exactly n spaces
        qi::rule<iterator_t, void(int)> indent_lt; // indent <= n spaces
        qi::rule<iterator_t, void(int)> indent_le; // indent < n spaces
        qi::rule<iterator_t> separate_in_line;
        qi::rule<iterator_t, void(int, context_t)> line_prefix;
        qi::rule<iterator_t, char(int, context_t)> l_empty;
        qi::rule<
            iterator_t,
            std::string(int, context_t, bool stop_at_document_delimiter)>
            b_l_folded;
        qi::rule<iterator_t, std::string(int, bool stop_at_document_delimiter)>
            flow_folded;
        qi::rule<iterator_t> comment_text;
        qi::rule<iterator_t, void(eoi_state_t &)> s_b_comment;
        qi::rule<iterator_t, void(eoi_state_t &)> l_comment;
        qi::rule<iterator_t, void(eoi_state_t &)> s_l_comments;
        qi::rule<iterator_t, void(int, context_t)> separate;
        qi::rule<iterator_t, void(int), qi::locals<eoi_state_t>> separate_lines;

        qi::rule<iterator_t, qi::locals<eoi_state_t>> directive;
        qi::rule<iterator_t> reserved_directive;
        qi::rule<iterator_t, qi::locals<iterator_range_t, unsigned int>>
            yaml_directive;
        qi::rule<iterator_t, qi::locals<iterator_range_t>> tag_directive;
        qi::rule<iterator_t> tag_handle;
        qi::rule<iterator_t> tag_prefix;

        qi::rule<
            iterator_t,
            parser_properties_t(int, context_t),
            qi::locals<std::string, iterator_range_t>>
            properties;

        qi::rule<iterator_t, std::string()> tag_property;
        qi::rule<iterator_t, iterator_range_t()> anchor_property;
        qi::rule<iterator_t, iterator_range_t()> anchor_name;

        qi::rule<iterator_t, void(eoi_state_t &)> one_time_eoi;

        struct tag_t
        {
            std::string prefix_;
            iterator_t position_;
            bool default_;
        };
        qi::symbols<char, tag_t> tags;

        boost::phoenix::function<error_handler_t> error_handler_;

        bool yaml_directive_seen_;
        iterator_t first_yaml_directive_it_;
    };

}}}

#if BOOST_YAML_HEADER_ONLY
#include <boost/yaml/parser/basic_structures_def.hpp>
#endif

#endif
