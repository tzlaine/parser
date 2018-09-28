/*=============================================================================
    Copyright (c) 2014 Joel de Guzman
    Copyright (c) 2018 T. Zachary Laine

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_YAML_PARSER_X3_ERROR_REPORTING_HPP
#define BOOST_YAML_PARSER_X3_ERROR_REPORTING_HPP

#include <boost/spirit/home/x3.hpp>

#include <sstream>


namespace boost { namespace yaml {

    // tag used to get our error handler from the context
    struct error_handler_tag;

    template<typename Iter>
    struct x3_error_handler
    {
        using iterator = Iter;

        static_assert(
            std::is_integral<decltype(*std::declval<iterator>())>::value, "");
        static_assert(sizeof(decltype(*std::declval<iterator>())) == 4, "");

        x3_error_handler(
            iterator first,
            iterator last,
            std::function<void(std::string const &)> error_fn,
            std::string file = "") :
            error_fn_(std::move(error_fn)),
            file_(std::move(file)),
            first_(first),
            last_(last)
        {}

        void operator()(iterator err_pos, std::string const & error_message);
        void operator()(
            iterator err_first,
            iterator err_last,
            std::string const & error_message);

    private:
        void print_file_line(std::size_t line);
        void print_line(iterator first, iterator last);
        void print_indicator(iterator & first, iterator last, char ind);
        void skip_whitespace(iterator & first, iterator last);
        void skip_non_whitespace(iterator & first, iterator last);
        iterator get_line_start(iterator first, iterator last);
        std::size_t position(iterator it);
        void emit();

        std::stringstream stream_;
        std::function<void(std::string const &)> error_fn_;
        std::string file_;
        iterator first_;
        iterator last_;
    };

    template<typename Iter>
    void x3_error_handler<Iter>::print_file_line(std::size_t line)
    {
        if (file_.empty())
            stream_ << "Line ";
        else
            stream_ << file_ << ':';
        stream_ << line << ": ";
    }

    template<typename Iter>
    void x3_error_handler<Iter>::print_line(iterator first, iterator last)
    {
        auto const end = std::find_if(
            first, last, [](uint32_t cp) { return cp == '\r' || cp == '\n'; });
        std::string line(
            text::utf8::make_from_utf32_iterator(first, first, last),
            text::utf8::make_from_utf32_iterator(first, end, last));
        stream_ << line << std::endl;
    }

    template<typename Iter>
    void x3_error_handler<Iter>::print_indicator(
        iterator & first, iterator last, char ind)
    {
        for (; first != last; ++first) {
            auto const cp = *first;
            if (cp == '\r' || cp == '\n')
                break;

            if (cp == '\t') {
                for (int i = 0; i < 4; ++i) {
                    stream_ << ind;
                }
            } else {
                stream_ << ind;
            }
        }
    }

    template<typename Iter>
    void
    x3_error_handler<Iter>::skip_whitespace(iterator & first, iterator last)
    {
        while (first != last) {
            auto const cp = *first;
            if (cp < 256 && std::isspace(cp))
                ++first;
            else
                break;
        }
    }

    template<typename Iter>
    void
    x3_error_handler<Iter>::skip_non_whitespace(iterator & first, iterator last)
    {
        while (first != last) {
            auto const cp = *first;
            if (cp < 256 && std::isspace(cp))
                break;
            ++first;
        }
    }

    template<class Iter>
    inline Iter
    x3_error_handler<Iter>::get_line_start(iterator first, iterator last)
    {
        auto latest = first;
        for (auto it = first; it != last; ++it){
            if (*it == '\r' || *it == '\n')
                latest = it;
        }
        return latest;
    }

    template<typename Iter>
    std::size_t x3_error_handler<Iter>::position(iterator it)
    {
        std::size_t line = 1;
        uint32_t prev = 0;

        for (iterator pos = first_; pos != it; ++pos) {
            auto const cp = *pos;
            switch (cp) {
            case '\n':
                if (prev != '\r')
                    ++line;
                break;
            case '\r': ++line; break;
            default: break;
            }
            prev = cp;
        }

        return line;
    }

    template<typename Iter>
    void x3_error_handler<Iter>::emit()
    {
        if (error_fn_)
            error_fn_(stream_.str());
        stream_.clear();
    }

    template<typename Iter>
    void x3_error_handler<Iter>::
    operator()(iterator it, std::string const & error_message)
    {
        iterator first = first_;
        iterator last = last_;

        skip_whitespace(it, last);

        print_file_line(position(it));
        stream_ << error_message << std::endl;

        iterator start = get_line_start(first, it);
        if (start != first)
            ++start;
        print_line(start, last);
        print_indicator(start, it, '_');
        stream_ << "^_" << std::endl;

        emit();
    }

    template<typename Iter>
    void x3_error_handler<Iter>::operator()(
        iterator err_first,
        iterator err_last,
        std::string const & error_message)
    {
        iterator first = first_;
        iterator last = last_;

        skip_whitespace(err_first, last);

        print_file_line(position(err_first));
        stream_ << error_message << std::endl;

        iterator start = get_line_start(first, err_first);
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
