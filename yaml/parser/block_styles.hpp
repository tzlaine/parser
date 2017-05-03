/**
 *   Copyright (C) 2017 Zach Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef YAML_PARSER_BLOCK_STYLES_HPP
#define YAML_PARSER_BLOCK_STYLES_HPP

#include <yaml/parser/flow_styles.hpp>


namespace yaml { namespace parser {

    enum class chomping_t {
        strip, clip, keep
    };

#ifdef BOOST_SPIRIT_DEBUG
    inline std::ostream & operator<< (std::ostream & os, chomping_t c)
    {
        switch (c) {
        case chomping_t::strip: return os << "strip";
        case chomping_t::clip: return os << "clip";
        case chomping_t::keep: return os << "keep";
        }
        return os;
    }
#endif

    struct block_header_t
    {
        block_header_t ()
            : indentation_ (0), chomping_ (chomping_t::clip)
        {}
        block_header_t (int indentation, chomping_t chomping)
            : indentation_ (indentation), chomping_ (chomping)
        {}

        int indentation_;
        chomping_t chomping_;

#ifdef BOOST_SPIRIT_DEBUG
        inline friend std::ostream & operator<< (std::ostream & os, block_header_t b)
        { return os << b.indentation_ << ',' << b.chomping_; }
#endif
    };

    template <typename Iterator>
    struct block_styles
    {
        explicit block_styles (boost::phoenix::function<error_handler_t> const & error_handler);

        flow_styles<Iterator> flow_styles_;

        qi::rule<
            Iterator,
            block_header_t(),
            qi::locals<int, chomping_t, eoi_state_t>
        > block_header;

        qi::rule<Iterator, int()> indentation_indicator;
        qi::rule<Iterator, chomping_t()> chomping_indicator;
        qi::rule<Iterator, std::string(int, chomping_t)> chomped_empty;
        qi::rule<Iterator, std::string(int)> strip_empty;
        qi::rule<Iterator, std::string(int)> keep_empty;
        qi::rule<Iterator, std::string(int), qi::locals<eoi_state_t>> trail_comments;

        qi::rule<
            Iterator,
            std::string(int),
            qi::locals<int, chomping_t>
        > literal;

        qi::rule<Iterator, std::string(int)> literal_text;
        qi::rule<Iterator, std::string(int)> literal_next;
        qi::rule<Iterator, std::string(int, chomping_t)> literal_content;

        qi::rule<
            Iterator,
            std::string(int),
            qi::locals<int, chomping_t>
        > folded;

        qi::rule<Iterator, std::string(int)> folded_text;
        qi::rule<Iterator, std::string(int)> folded_lines;
        qi::rule<Iterator, std::string(int)> spaced_text;
        qi::rule<Iterator, std::string(int)> spaced;
        qi::rule<Iterator, std::string(int)> spaced_lines;
        qi::rule<Iterator, std::string(int)> same_lines;
        qi::rule<Iterator, std::string(int)> diff_lines;
        qi::rule<Iterator, std::string(int, chomping_t)> folded_content;

        qi::rule<Iterator, int()> auto_detect_indent;
        qi::rule<Iterator, ast::seq_t(int), qi::locals<int>> block_sequence;
        qi::rule<Iterator, ast::value_t(int n)> block_seq_entry;
        qi::rule<Iterator, ast::value_t(int n, context_t), qi::locals<int, eoi_state_t>> block_indented;
        qi::rule<Iterator, ast::seq_t(int n)> compact_sequence;

        qi::rule<Iterator, ast::map_t(int), qi::locals<int>> block_mapping;
        qi::rule<Iterator, ast::map_element_t(int)> block_map_entry;
        qi::rule<Iterator, ast::map_element_t(int)> block_map_explicit_entry;
        qi::rule<Iterator, ast::value_t(int)> block_map_explicit_key;
        qi::rule<Iterator, ast::value_t(int)> block_map_explicit_value;
        qi::rule<Iterator, ast::map_element_t(int)> block_map_implicit_entry;
        qi::rule<Iterator, ast::value_t()> block_map_implicit_key;
        qi::rule<Iterator, ast::value_t(int), qi::locals<eoi_state_t>> block_map_implicit_value;
        qi::rule<Iterator, ast::map_t(int)> compact_mapping;

        qi::rule<Iterator, ast::value_t(int, context_t)> block_node;
        qi::rule<Iterator, ast::value_t(int), qi::locals<eoi_state_t>> flow_in_block;
        qi::rule<Iterator, ast::value_t(int, context_t)> block_in_block;

        qi::rule<
            Iterator,
            ast::value_t(int, context_t),
            qi::locals<ast::properties_t>
        > block_scalar;

        qi::rule<
            Iterator,
            ast::value_t(int, context_t),
            qi::locals<ast::properties_t, eoi_state_t>
        > block_collection;
    };

} }

#endif
