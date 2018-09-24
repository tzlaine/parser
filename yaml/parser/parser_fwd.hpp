/**
 *   Copyright (C) 2017 Zach Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_YAML_PARSER_PARSER_FWD_HPP
#define BOOST_YAML_PARSER_PARSER_FWD_HPP

#include <yaml/config.hpp>
#include <yaml/ast.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_copy.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>


namespace boost { namespace yaml { namespace parser {

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


    inline std::string range_to_string (iterator_range_t range)
    {
        using to_string_iterator_t = boost::u32_to_u8_iterator<iterator_t>;
        return std::string(
            to_string_iterator_t(range.begin()),
            to_string_iterator_t(range.end())
        );
    }


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

    struct parser_properties_t
    {
        parser_properties_t () {}
        parser_properties_t (std::string const & tag, iterator_range_t anchor)
            : tag_ (tag), anchor_ (anchor)
        {}

        std::string tag_;
        iterator_range_t anchor_;
    };
#ifdef BOOST_SPIRIT_DEBUG
    inline std::ostream& operator<<(std::ostream & out, parser_properties_t const & p)
    { return out << p.tag_ << ',' << range_to_string(p.anchor_); }
#endif

    struct anchor_t
    {
        ast::alias_t alias_;
        iterator_t position_;
    };

    // Functions used in the parsers.
    namespace detail {

        struct to_str
        {
            template <typename>
            struct result { using type = std::string; };

            std::string operator() (iterator_range_t range) const
            { return range_to_string(range); }
        };

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
#define BOOST_YAML_PARSER_PRINT_INDENT eps(print_indent(_r1)) >>
#else
#define BOOST_YAML_PARSER_PRINT_INDENT
#endif

    }

}}}

#include <yaml/parser/error_handler.hpp>

namespace boost { namespace yaml { namespace parser { namespace detail {

    struct map_insert
    {
        template<typename, typename, typename>
        struct result
        {
            using type = void;
        };

        template<typename Map, typename T>
        void operator()(
            Map & map,
            T const & x,
            iterator_range_t range,
            error_handler_t const & error_handler) const
        {
            if (map.count(x.first) && error_handler.impl().warning_fn_) {
                std::ostringstream oss;
                oss << "Ignoring map entry with duplicate key '";
                ast::print_yaml<2, true, true, false>(oss, x.first);
                oss << "'";
                error_handler.impl().report_warning_at(
                    range.begin(), oss.str());
            } else {
                map.insert(x);
            }
        }
    };

    struct handle_properties
    {
        template<typename, typename, typename, typename>
        struct result
        {
            using type = ast::value_t;
        };

        template<typename T>
        ast::value_t operator()(
            parser_properties_t const & parser_properties,
            T const & x,
            qi::symbols<char, anchor_t> & anchors,
            error_handler_t const & error_handler) const
        {
            ast::properties_t properties;
            properties.tag_ = parser_properties.tag_;

            if (!parser_properties.anchor_.empty()) {
                properties.anchor_ = range_to_string(parser_properties.anchor_);

                anchor_t anchor;
                std::shared_ptr<ast::value_t> anchor_ptr(new ast::value_t(x));
                anchor.alias_ = ast::alias_t(properties.anchor_, anchor_ptr);
                anchor.position_ = parser_properties.anchor_.begin();

                auto existing_anchor = anchors.find(properties.anchor_);
                if (existing_anchor && error_handler.impl().warning_fn_) {
                    std::ostringstream oss;
                    oss << "Redefining anchor " << properties.anchor_;
                    error_handler.impl().report_warning_at(
                        parser_properties.anchor_.begin(), oss.str());
                    error_handler.impl().report_warning_at(
                        existing_anchor->position_,
                        "The previous one was was here");
                }

                anchors.remove(properties.anchor_);
                anchors.add(properties.anchor_, anchor);
            }

            if (properties)
                return ast::value_t(
                    ast::properties_node_t(properties, ast::value_t(x)));

            return ast::value_t(x);
        }
    };

}}}}

#endif
