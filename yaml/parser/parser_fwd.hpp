/**
 *   Copyright (C) 2017 Zach Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef YAML_PARSER_PARSER_FWD_HPP
#define YAML_PARSER_PARSER_FWD_HPP

#include <yaml/config.hpp>
#include <yaml/ast.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_copy.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>


namespace yaml { namespace parser {

    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;


    // Error reporting.
    using reporting_fn_t = std::function<void (std::string const &)>;

    struct parse_error
        : std::exception
    {
        parse_error (std::string const & msg)
            : msg_ (msg)
        {}

        virtual char const * what () const noexcept
        { return msg_.c_str(); }

        std::string msg_;
    };


    // Characters and iterators.
    using uchar_t = boost::uint32_t; // Unicode code point
    using ustring_t = std::basic_string<uchar_t>; // UCS-4 Unicode string

    // Prevents the direct use of a uchar_t as a char without UTF32-to-UTF8
    // transcoding.
    struct parsed_uchar_t
    {
        parsed_uchar_t (uchar_t c = 0) : value_ (c) {}
        uchar_t value_;

        friend std::ostream & operator<< (std::ostream & os, parsed_uchar_t c)
        {
            std::string utf8;
            using insert_iterator_t = std::back_insert_iterator<std::string>;
            insert_iterator_t out_it(utf8);
            boost::utf8_output_iterator<insert_iterator_t> utf8_it(out_it);
            *utf8_it++ = c.value_;
            return os << utf8;
        }
    };

    using iterator_t = boost::spirit::classic::position_iterator<uchar_t const *>;
    using iterator_range_t = boost::iterator_range<iterator_t>;


    // Parser enums.
    enum class context_t {
        block_in, block_out,
        flow_in, flow_out,
        block_key, flow_key
    };

#ifdef BOOST_SPIRIT_DEBUG
    inline std::ostream & operator<< (std::ostream & os, context_t c)
    {
        switch (c) {
#define CASE(x) case context_t::x: return os << #x
        CASE(block_in); CASE(block_out);
        CASE(flow_in); CASE(flow_out);
        CASE(block_key); CASE(flow_key);
#undef CASE
        }
        return os;
    }
#endif

    enum class encoding_t {
        utf32_be, utf32_le,
        utf16_be, utf16_le,
        utf8
    };

    inline std::ostream & operator<< (std::ostream & os, encoding_t c)
    {
        switch (c) {
        case encoding_t::utf32_be: return os << "UTF-32 big-endian";
        case encoding_t::utf32_le: return os << "UTF-32 little-endian";
        case encoding_t::utf16_be: return os << "UTF-16 big-endian";
        case encoding_t::utf16_le: return os << "UTF-16 little-endian";
        case encoding_t::utf8: return os << "UTF-8";
        }
        return os;
    }

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

    enum class eoi_state_t
    {
        not_at_end, at_end
    };

#ifdef BOOST_SPIRIT_DEBUG
    inline std::ostream & operator<< (std::ostream & os, eoi_state_t s)
    { return os << (s == eoi_state_t::not_at_end ? "not_at_end" : "at_end"); }
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
    };

#ifdef BOOST_SPIRIT_DEBUG
    inline std::ostream & operator<< (std::ostream & os, block_header_t b)
    { return os << b.indentation_ << ',' << b.chomping_; }
#endif


    // Functions used in the parsers.
    namespace detail {

        struct push_utf8
        {
            template <typename, typename, typename = void>
            struct result { using type = void; };

            void operator() (std::string & utf8, parsed_uchar_t code_point) const
            {
                using insert_iterator_t = std::back_insert_iterator<std::string>;
                insert_iterator_t out_it(utf8);
                boost::utf8_output_iterator<insert_iterator_t> utf8_it(out_it);
                *utf8_it++ = code_point.value_;
            }

            void operator() (std::string & utf8, parsed_uchar_t code_point_1, parsed_uchar_t code_point_2) const
            {
                using insert_iterator_t = std::back_insert_iterator<std::string>;
                insert_iterator_t out_it(utf8);
                boost::utf8_output_iterator<insert_iterator_t> utf8_it(out_it);
                *utf8_it++ = code_point_1.value_;
                *utf8_it++ = code_point_2.value_;
            }
        };

        struct check_start_of_line
        {
            template <typename, typename>
            struct result { using type = void; };

            template <typename Pass>
            void operator() (iterator_range_t const & range, Pass & pass) const
            {
                int const column = range.begin().get_position().column;
                if (column != 1)
                    pass = false;
            }
        };

        struct handle_properties
        {
            template <typename, typename, typename>
            struct result { using type = ast::value_t; };

            template <typename T>
            ast::value_t operator() (
                ast::properties_t const & properties,
                T const & x,
                qi::symbols<char, ast::alias_t> & anchors
            ) const {
                if (properties.anchor_ != "") {
                    std::shared_ptr<ast::value_t> anchor_ptr(new ast::value_t(x));
                    // TODO: Emit a warning when an anchor is redefined.
                    anchors.remove(properties.anchor_);
                    anchors.add(
                        properties.anchor_,
                        ast::alias_t(properties.anchor_, anchor_ptr)
                    );
                }
                if (properties)
                    return ast::value_t(ast::properties_node_t(properties, ast::value_t(x)));
                return ast::value_t(x);
            }
        };

#ifdef BOOST_SPIRIT_DEBUG
        struct print_indent
        {
            template <typename>
            struct result { using type = bool; };

            bool operator() (int n) const
            {
                std::cerr << n << " ======================================== " << n << "\n";
                return true;
            }
        };
#endif

#ifdef BOOST_SPIRIT_DEBUG
#define YAML_PARSER_PRINT_INDENT eps(print_indent(_r1)) >>
#else
#define YAML_PARSER_PRINT_INDENT
#endif

    }

} }

#endif
