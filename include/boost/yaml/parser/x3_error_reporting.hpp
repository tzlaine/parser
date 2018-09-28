/*=============================================================================
    Copyright (c) 2014 Joel de Guzman
    Copyright (c) 2018 T. Zachary Laine

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_YAML_PARSER_X3_ERROR_REPORTING_HPP
#define BOOST_YAML_PARSER_X3_ERROR_REPORTING_HPP

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <sstream>

// Clang-style error handling utilities

namespace boost { namespace yaml {

    // tag used to get our error handler from the context
    struct error_handler_tag;

    struct x3_error_handler_base
    {
        template<typename Iterator, typename Exception, typename Context>
        spirit::x3::error_handler_result on_error(
            Iterator & first,
            Iterator const & last,
            Exception const & e,
            Context const & ctx)
        {
            namespace x3 = spirit::x3;
            auto & error_handler = x3::get<error_handler_tag>(ctx).get();
            std::string message = "Error! Expecting: " + e.which() + " here:";
            error_handler(e.where(), message);
            return x3::error_handler_result::fail;
        }
    };

    template<typename Iterator>
    struct x3_error_handler
    {
        using iterator_type = Iterator;

        static_assert(
            std::is_integral<decltype(*std::declval<iterator_type>())>::value);
        static_assert(sizeof(decltype(*std::declval<iterator_type>())) == 4);

        x3_error_handler(
            Iterator first,
            Iterator last,
            std::function<void(std::string const &)> error_fn,
            std::string file = "") :
            error_fn_(error_fn),
            file_(file),
            pos_cache_(first, last)
        {}

        using result_type = void;

        void operator()(Iterator err_pos, std::string const & error_message);
        void operator()(
            Iterator err_first,
            Iterator err_last,
            std::string const & error_message);
        void
        operator()(spirit::x3::position_tagged pos, std::string const & message)
        {
            auto where = pos_cache_.position_of(pos);
            (*this)(where.begin(), where.end(), message);
            emit();
        }

        template<typename AST>
        void tag(AST & ast, Iterator first, Iterator last)
        {
            return pos_cache_.annotate(ast, first, last);
        }

        boost::iterator_range<Iterator>
        position_of(spirit::x3::position_tagged pos) const
        {
            return pos_cache_.position_of(pos);
        }

        spirit::x3::position_cache<std::vector<Iterator>> const &
        get_position_cache() const
        {
            return pos_cache_;
        }

    private:
        void print_file_line(std::size_t line);
        void print_line(Iterator line_start, Iterator last);
        void print_indicator(Iterator & line_start, Iterator last, char ind);
        void skip_whitespace(Iterator & err_pos, Iterator last);
        void skip_non_whitespace(Iterator & err_pos, Iterator last);
        Iterator get_line_start(Iterator first, Iterator pos);
        std::size_t position(Iterator i);
        void emit();

        std::stringstream stream_;
        std::function<void(std::string const &)> error_fn_;
        std::string file_;
        spirit::x3::position_cache<std::vector<Iterator>> pos_cache_;
    };

    template<typename Iterator>
    void x3_error_handler<Iterator>::print_file_line(std::size_t line)
    {
        if (file_ != "") {
            stream_ << "In file " << file_ << ", ";
        } else {
            stream_ << "In ";
        }

        stream_ << "line " << line << ':' << std::endl;
    }

    template<typename Iterator>
    void
    x3_error_handler<Iterator>::print_line(Iterator start, Iterator last)
    {
        auto end = start;
        while (end != last) {
            auto c = *end;
            if (c == '\r' || c == '\n')
                break;
            else
                ++end;
        }
        std::string line(
            text::utf8::make_from_utf32_iterator(start, start, last),
            text::utf8::make_from_utf32_iterator(start, last, last));
        stream_ << line << std::endl;
    }

    template<typename Iterator>
    void x3_error_handler<Iterator>::print_indicator(
        Iterator & start, Iterator last, char ind)
    {
        for (; start != last; ++start) {
            auto c = *start;
            if (c == '\r' || c == '\n')
                break;
            else if (c == '\t')
                for (int i = 0; i < 4; ++i)
                    stream_ << ind;
            else
                stream_ << ind;
        }
    }

    template<typename Iterator>
    void x3_error_handler<Iterator>::skip_whitespace(
        Iterator & err_pos, Iterator last)
    {
        // make sure err_pos does not point to white space
        while (err_pos != last) {
            char c = *err_pos;
            if (std::isspace(c))
                ++err_pos;
            else
                break;
        }
    }

    template<typename Iterator>
    void x3_error_handler<Iterator>::skip_non_whitespace(
        Iterator & err_pos, Iterator last)
    {
        // make sure err_pos does not point to white space
        while (err_pos != last) {
            char c = *err_pos;
            if (std::isspace(c))
                break;
            else
                ++err_pos;
        }
    }

    template<class Iterator>
    inline Iterator
    x3_error_handler<Iterator>::get_line_start(Iterator first, Iterator pos)
    {
        Iterator latest = first;
        for (Iterator i = first; i != pos; ++i)
            if (*i == '\r' || *i == '\n')
                latest = i;
        return latest;
    }

    template<typename Iterator>
    std::size_t x3_error_handler<Iterator>::position(Iterator i)
    {
        std::size_t line{1};
        typename std::iterator_traits<Iterator>::value_type prev{0};

        for (Iterator pos = pos_cache_.first(); pos != i; ++pos) {
            auto c = *pos;
            switch (c) {
            case '\n':
                if (prev != '\r')
                    ++line;
                break;
            case '\r': ++line; break;
            default: break;
            }
            prev = c;
        }

        return line;
    }

    template<typename Iterator>
    void x3_error_handler<Iterator>::emit()
    {
        if (error_fn_)
            error_fn_(stream_.str());
        stream_.clear();
    }

    template<typename Iterator>
    void x3_error_handler<Iterator>::
    operator()(Iterator err_pos, std::string const & error_message)
    {
        Iterator first = pos_cache_.first();
        Iterator last = pos_cache_.last();

        // make sure err_pos does not point to white space
        skip_whitespace(err_pos, last);

        print_file_line(position(err_pos));
        stream_ << error_message << std::endl;

        Iterator start = get_line_start(first, err_pos);
        if (start != first)
            ++start;
        print_line(start, last);
        print_indicator(start, err_pos, '_');
        stream_ << "^_" << std::endl;

        emit();
    }

    template<typename Iterator>
    void x3_error_handler<Iterator>::operator()(
        Iterator err_first,
        Iterator err_last,
        std::string const & error_message)
    {
        Iterator first = pos_cache_.first();
        Iterator last = pos_cache_.last();

        // make sure err_pos does not point to white space
        skip_whitespace(err_first, last);

        print_file_line(position(err_first));
        stream_ << error_message << std::endl;

        Iterator start = get_line_start(first, err_first);
        if (start != first)
            ++start;
        print_line(start, last);
        print_indicator(start, err_first, ' ');
        print_indicator(start, err_last, '~');
        stream_ << " <<-- Here" << std::endl;

        emit();
    }

}}

#endif
