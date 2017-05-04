/**
 *   Copyright (C) 2017 Zach Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef YAML_PARSER_BASIC_STRUCTURES_HPP
#define YAML_PARSER_BASIC_STRUCTURES_HPP

#include <yaml/parser/characters.hpp>


namespace yaml { namespace parser {

    namespace detail {

        struct check_start_of_line
        {
            template <typename, typename>
            struct result { using type = void; };

            template <typename Range, typename Pass>
            void operator() (Range const & range, Pass & pass) const
            {
                int const column = range.begin().get_position().column;
                if (column != 1)
                    pass = false;
            }
        };

    }

    enum class eoi_state_t
    {
        not_at_end, at_end
    };
#ifdef BOOST_SPIRIT_DEBUG
    inline std::ostream & operator<< (std::ostream & os, eoi_state_t s)
    { return os << (s == eoi_state_t::not_at_end ? "not_at_end" : "at_end"); }
#endif

    template <typename Iterator>
    struct basic_structures
    {
        explicit basic_structures (boost::phoenix::function<error_handler_t> const & error_handler);

        characters<Iterator> characters_;

        qi::rule<Iterator, void(int)> indent;    // indent exactly n spaces
        qi::rule<Iterator, void(int)> indent_lt; // indent <= n spaces
        qi::rule<Iterator, void(int)> indent_le; // indent < n spaces
        qi::rule<Iterator, void()> separate_in_line;
        qi::rule<Iterator, void(int, context_t)> line_prefix;
        qi::rule<Iterator, void(int, context_t)> l_empty;
        qi::rule<Iterator, char(int, context_t, bool stop_at_document_delimiter)> b_l_folded;
        qi::rule<Iterator, char(int, bool stop_at_document_delimiter)> flow_folded;
        qi::rule<Iterator, void()> comment_text;
        qi::rule<Iterator, void(eoi_state_t &)> s_b_comment;
        qi::rule<Iterator, void(eoi_state_t &)> l_comment;
        qi::rule<Iterator, void(eoi_state_t &)> s_l_comments;
        qi::rule<Iterator, void(int, context_t)> separate;
        qi::rule<Iterator, void(int), qi::locals<eoi_state_t>> separate_lines;

        qi::rule<Iterator, qi::locals<eoi_state_t>> directive;
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

        qi::rule<Iterator, void (eoi_state_t &)> one_time_eoi;

        std::reference_wrapper<boost::phoenix::function<error_handler_t> const> error_handler_;
    };

} }

#endif
