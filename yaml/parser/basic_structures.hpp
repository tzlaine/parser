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

    template <typename CharIter>
    struct basic_structures_t
    {
        using iterator_t = pos_iterator<CharIter>;

        explicit basic_structures_t (boost::phoenix::function<error_handler_t> const & error_handler);

        characters_t<CharIter> characters_;

        qi::rule<iterator_t, void(int)> indent;    // indent exactly n spaces
        qi::rule<iterator_t, void(int)> indent_lt; // indent <= n spaces
        qi::rule<iterator_t, void(int)> indent_le; // indent < n spaces
        qi::rule<iterator_t, void()> separate_in_line;
        qi::rule<iterator_t, void(int, context_t)> line_prefix;
        qi::rule<iterator_t, void(int, context_t)> l_empty;
        qi::rule<iterator_t, char(int, context_t, bool stop_at_document_delimiter)> b_l_folded;
        qi::rule<iterator_t, char(int, bool stop_at_document_delimiter)> flow_folded;
        qi::rule<iterator_t, void()> comment_text;
        qi::rule<iterator_t, void(eoi_state_t &)> s_b_comment;
        qi::rule<iterator_t, void(eoi_state_t &)> l_comment;
        qi::rule<iterator_t, void(eoi_state_t &)> s_l_comments;
        qi::rule<iterator_t, void(int, context_t)> separate;
        qi::rule<iterator_t, void(int), qi::locals<eoi_state_t>> separate_lines;

        qi::rule<iterator_t, qi::locals<eoi_state_t>> directive;
        qi::rule<iterator_t> reserved_directive;
        qi::rule<iterator_t, qi::locals<unsigned int>> yaml_directive;
        qi::rule<iterator_t> tag_directive;
        qi::rule<iterator_t> tag_handle;
        qi::rule<iterator_t> tag_prefix;

        qi::rule<
            iterator_t,
            ast::properties_t(int, context_t),
            qi::locals<ast::string_t, ast::string_t>
        > properties;

        qi::rule<iterator_t, std::string()> tag_property;
        qi::rule<iterator_t, std::string()> anchor_property;
        qi::rule<iterator_t, std::string()> anchor_name;

        qi::rule<iterator_t, void (eoi_state_t &)> one_time_eoi;

        std::reference_wrapper<boost::phoenix::function<error_handler_t> const> error_handler_;
    };

} }

#endif
