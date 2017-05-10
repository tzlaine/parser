/**
 *   Copyright (C) 2017 Zach Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef YAML_PARSER_STREAM_DEF_HPP
#define YAML_PARSER_STREAM_DEF_HPP

#include <yaml/parser/stream.hpp>

#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_container.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/regex/pending/unicode_iterator.hpp>


namespace yaml { namespace parser {

    namespace detail {

        template <typename ErrorFn>
        inline bool check_encoding (encoding_t encoding, ErrorFn const & error_fn)
        {
            if (encoding != encoding_t::utf8) {
                std::stringstream oss;
                oss << "BOM for encoding "
                    << encoding
                    << " was encountered in the stream, but only "
                    << encoding_t::utf8
                    << " encoding is supported.\n";
                error_fn(oss.str());
                return false;
            }
            return true;
        }

    }

    template <typename CharIter>
    stream_t<CharIter>::stream_t (
        std::string const & source_file,
        reporting_fn_t const & errors_callback,
        reporting_fn_t const & warnings_callback
    )
        : block_styles_ (error_handler_)
        , error_handler_ (error_handler_t(source_file, errors_callback, warnings_callback))
    {
        qi::attr_type attr;
        qi::raw_type raw;
        qi::char_type char_;
        qi::_pass_type _pass;
        qi::_val_type _val;
        qi::_1_type _1;
        qi::_2_type _2;
        qi::_3_type _3;
        qi::_4_type _4;
        qi::_a_type _a;
        qi::lit_type lit;
        qi::blank_type blank;
        qi::eps_type eps;
        qi::eoi_type eoi;
        qi::eol_type eol;

        namespace phx = boost::phoenix;
        using phx::function;

        function<detail::check_start_of_line> check_start_of_line;

        auto pb = phx::push_back(_val, _1);

        auto & bom = block_styles_.flow_styles_.basic_structures_.characters_.bom;

        auto & directive = block_styles_.flow_styles_.basic_structures_.directive;
        auto & l_comment = block_styles_.flow_styles_.basic_structures_.l_comment;
        auto & s_l_comments = block_styles_.flow_styles_.basic_structures_.s_l_comments;

        auto & block_node = block_styles_.block_node;


        // [202]
        document_prefix =
                !bom // BOM is read prior to each document.
            >>  eps[_a = eoi_state_t::not_at_end] >> +l_comment(_a) >> eps(_a == eoi_state_t::not_at_end)
            ;

        // [205]
        document_suffix =
            "..." >> s_l_comments(_a = eoi_state_t::not_at_end)
            ;

        // [206]
        forbidden =
                raw[eps][check_start_of_line(_1, _pass)]
            >>  (-bom >> "---" | "...")
            >>  (eol | blank | eoi)
            ;

        // [207]
        bare_document =
                !bom // BOM is read prior to each document.
            >>  block_node(-1, context_t::block_in) - forbidden
            ;

        // [208]
        explicit_document =
                !bom // BOM is read prior to each document.
            >>  "---"
            >>  (bare_document | attr(ast::value_t()) >> s_l_comments(_a = eoi_state_t::not_at_end))
            ;

        // [209]
        directive_document =
                !bom // BOM is read prior to each document.
            >>  +directive >> explicit_document
            ;

        // [210]
        any_document =
                directive_document
            |   explicit_document
            |   bare_document
            ;

        // [211]
        yaml_stream =
                *document_prefix
            >>  -any_document[pb]
            >>  *(
                    +(document_suffix >> !bom) >> *document_prefix >> any_document[pb]
                |   *document_prefix >> explicit_document[pb]
                )
            >>  *(document_suffix >> !bom) >> *document_prefix
            ;

        // Allow empty and comment lines at end of input.
        end_of_input =
                *(*blank >> -('#' >> *(char_ - eol)) >> eol)
            >>  *blank >> -('#' >> *(char_ - eoi)) >> eoi
            ;

        BOOST_SPIRIT_DEBUG_NODES(
            (document_prefix)
            (document_suffix)
            (forbidden)
            (bare_document)
            (explicit_document)
            (directive_document)
            (any_document)
            (yaml_stream)
            (end_of_input)
        );

        qi::on_error<qi::fail>(yaml_stream, error_handler_(_1, _2, _3, _4));
    }

    namespace detail {

        inline encoding_t read_bom_8 (char const * buf, int & size)
        {
            auto retval = encoding_t::utf8;

            /*   */if (size == 4 && buf[0] == '\x00' && buf[1] == '\x00' && buf[2] == '\xfe' && buf[3] == '\xff') {
                size = 4;
                retval = encoding_t::utf32_be;
            } else if (size == 4 && buf[0] == '\x00' && buf[1] == '\x00' && buf[2] == '\x00' /* anything */) {
                size = 4;
                retval = encoding_t::utf32_be;
            } else if (size == 4 && buf[0] == '\xff' && buf[1] == '\xfe' && buf[2] == '\x00' && buf[3] == '\x00') {
                size = 4;
                retval = encoding_t::utf32_le;
            } else if (size == 4 &&   /* anything */    buf[1] == '\x00' && buf[2] == '\x00' && buf[3] == '\x00') {
                size = 4;
                retval = encoding_t::utf32_le;
            } else if (size >= 2 && buf[0] == '\xfe' && buf[1] == '\xff') {
                size = 2;
                retval = encoding_t::utf16_be;
            } else if (size >= 2 && buf[0] == '\x00' /* anything */) {
                size = 2;
                retval = encoding_t::utf16_be;
            } else if (size >= 2 && buf[0] == '\xff' && buf[1] == '\xfe') {
                size = 2;
                retval = encoding_t::utf16_le;
            } else if (size >= 2 &&   /* anything */    buf[1] == '\x00') {
                size = 2;
                retval = encoding_t::utf16_le;
            } else if (size >= 3 && buf[0] == '\xef' && buf[1] == '\xbb' && buf[2] == '\xbf') {
                size = 3;
                retval = encoding_t::utf8;
            } else {
                size = 0;
            }

            return retval;
        }

    }

#if YAML_HEADER_ONLY
    inline
#endif
    encoding_t read_bom (std::istream & is)
    {
        int size = 0;
        char buf[4];
        for (char & c : buf) {
            if (!is)
                break;
            c = is.get();
            ++size;
        }
        for (int i = size; i --> 0;) {
            is.putback(buf[i]);
        }

        auto const retval = detail::read_bom_8(buf, size);

        for (int i = 0; i < size; ++i) {
            is.get();
        }

        return retval;
    }

    template <typename CharIter>
    encoding_t read_bom (pos_iterator<CharIter> & first, pos_iterator<CharIter> last,
                         typename std::enable_if<sizeof(typename CharIter::value_type) == 1u>::type*)
    {
        pos_iterator<CharIter> it = first;
        int size = 0;
        char buf[4];
        for (char & c : buf) {
            if (it == last)
                break;
            c = *it++;
            ++size;
        }

        auto const retval = detail::read_bom_8(buf, size);

        std::advance(first, size);

        return retval;
    }

    template <typename CharIter>
    encoding_t read_bom (pos_iterator<CharIter> & first, pos_iterator<CharIter> last,
                         typename std::enable_if<sizeof(typename CharIter::value_type) == 4u>::type*)
    {
        if (first != last && *first == 0xfeff)
            ++first;
        return encoding_t::utf8;
    }

#if YAML_HEADER_ONLY
    inline
#endif
    boost::optional<std::vector<ast::value_t>> parse_yaml(
        std::istream & is,
        std::string const & source_file,
        reporting_fn_t const & errors_callback,
        reporting_fn_t const & warnings_callback
    ) {
        boost::optional<std::vector<ast::value_t>> retval;

        using raw_char_iterator_t = boost::u8_to_u32_iterator<std::string::const_iterator>;
        using ustring_t = std::basic_string<uchar_t>;
        using char_iterator_t = ustring_t::const_iterator;

        stream_t<char_iterator_t> p(
            source_file,
            errors_callback,
            warnings_callback
        );

        auto const first_encoding = read_bom(is);
        auto const encoding_ok = detail::check_encoding(
            first_encoding,
            [&errors_callback](std::string const & msg) {
                if (errors_callback)
                    errors_callback(msg);
                else
                    throw parse_error(msg);
            }
        );
        if (!encoding_ok)
            return retval;

        std::string raw_contents;
        char buf[4096];
        while (is) {
            is.read(buf, sizeof(buf));
            raw_contents.append(buf, buf + is.gcount());
        }
        ustring_t contents(
            raw_char_iterator_t(raw_contents.begin()),
            raw_char_iterator_t(raw_contents.end())
        );

        char_iterator_t contents_first(contents.begin());
        char_iterator_t contents_last(contents.end());

        using iterator_t = stream_t<char_iterator_t>::iterator_t;

        iterator_t first(contents_first, contents_last);
        iterator_t last;
        first.set_tabchars(1);

        std::vector<ast::value_t> documents;
        std::vector<ast::value_t> temp_documents;
        bool success = true;
        do {
            auto initial = first;
            success = qi::parse(first, last, p.yaml_stream, temp_documents);

            if (!success || first == initial)
                break;

            std::move(
                temp_documents.begin(), temp_documents.end(),
                std::back_inserter(documents)
            );
            temp_documents.clear();

            bool doc_boundary = qi::parse(first, last, +p.document_suffix);

            auto const encoding = read_bom(first, last);
            auto const encoding_ok = detail::check_encoding(
                encoding,
                [&p](std::string const & msg) {p.error_handler_.f.report_error(msg);}
            );

            if (!encoding_ok) {
                success = false;
            } else {
                auto pos = first.get_position();
                pos.column = 1;
                first.set_position(pos);
            }

            if (!doc_boundary) {
                qi::lit_type lit;
                doc_boundary = qi::parse(first, last, &lit("---"));
            }

            // If there's not a ... or --- separator, don't keep reading
            // documents.  However, this is not an error by itself.
            if (!doc_boundary)
                break;
        } while (success);

        if (success) {
            success = qi::parse(first, last, p.end_of_input);

            if (!success)
                p.error_handler_.f.report_error("Expected end of input\n");
        }

        if (success)
            retval = std::move(documents);

        return retval;
    }

} }

#endif
