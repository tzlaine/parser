#ifndef BOOST_PARSER_DETAIL_PRINTING_HPP
#define BOOST_PARSER_DETAIL_PRINTING_HPP

#include <boost/parser/parser_fwd.hpp>
#include <boost/parser/detail/detection.hpp>

#include <boost/hana.hpp>
#include <boost/optional.hpp>
#include <boost/variant.hpp>
#include <boost/text/utf8.hpp>
#include <boost/text/utility.hpp>

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>


namespace boost { namespace parser { namespace detail {

    enum { parser_component_limit = 4 };

    template<typename Parser>
    void
    parser_name(Parser const & parser, std::ostream & os, int components = 0);

    template<typename Parser>
    void parser_name(
        repeat_parser<Parser, nope> const & parser,
        std::ostream & os,
        int components = 0);

    template<typename Parser, typename DelimiterParser>
    void parser_name(
        repeat_parser<Parser, DelimiterParser> const & parser,
        std::ostream & os,
        int components = 0);

    template<typename Parser>
    void parser_name(
        opt_parser<Parser> const & parser,
        std::ostream & os,
        int components = 0);

    template<typename ParserTuple>
    void parser_name(
        or_parser<ParserTuple> const & parser,
        std::ostream & os,
        int components = 0);

    template<typename ParserTuple, typename BacktrackingTuple>
    void parser_name(
        seq_parser<ParserTuple, BacktrackingTuple> const & parser,
        std::ostream & os,
        int components = 0);

    template<typename Parser, typename Action>
    void parser_name(
        action_parser<Parser, Action> const & parser,
        std::ostream & os,
        int components = 0);

    template<typename Parser>
    void parser_name(
        omit_parser<Parser> const & parser,
        std::ostream & os,
        int components = 0);

    template<typename Parser>
    void parser_name(
        raw_parser<Parser> const & parser,
        std::ostream & os,
        int components = 0);

    template<typename Parser>
    void parser_name(
        lexeme_parser<Parser> const & parser,
        std::ostream & os,
        int components = 0);

    template<typename Parser>
    void parser_name(
        skip_parser<Parser, nope> const & parser,
        std::ostream & os,
        int components = 0);

    template<typename Parser, typename SkipParser>
    void parser_name(
        skip_parser<Parser> const & parser,
        std::ostream & os,
        int components = 0);

    template<typename Parser>
    void parser_name(
        expect_parser<Parser, true> const & parser,
        std::ostream & os,
        int components = 0);

    template<typename Parser>
    void parser_name(
        expect_parser<Parser, false> const & parser,
        std::ostream & os,
        int components = 0);

    template<
        bool UseCallbacks,
        typename Parser,
        typename Attribute,
        typename LocalState,
        typename ParamsTuple>
    void parser_name(
        rule_parser<
            UseCallbacks,
            Parser,
            Attribute,
            LocalState,
            ParamsTuple> const & parser,
        std::ostream & os,
        int components = 0);

    template<typename T>
    void parser_name(
        symbol_parser<T> const & parser, std::ostream & os, int components = 0);

    template<typename Predicate>
    void parser_name(
        eps_parser<Predicate> const & parser,
        std::ostream & os,
        int components = 0);

    void parser_name(
        eps_parser<nope> const & parser, std::ostream & os, int components = 0);

    inline void parser_name(
        eoi_parser const & parser, std::ostream & os, int components = 0);

    template<typename Atribute>
    void parser_name(
        attr_parser<Atribute> const & parser,
        std::ostream & os,
        int components = 0);

    template<typename Expected>
    void parser_name(
        char_parser<Expected> const & parser,
        std::ostream & os,
        int components = 0);

    inline void parser_name(
        char_parser<nope> const & parser,
        std::ostream & os,
        int components = 0);

    template<typename Expected>
    void parser_name(
        omit_parser<char_parser<Expected>> const & parser,
        std::ostream & os,
        int components = 0);

    template<typename Expected>
    void parser_name(
        char_parser<Expected, uint32_t> const & parser,
        std::ostream & os,
        int components = 0);

    inline void parser_name(
        char_parser<nope, uint32_t> const & parser,
        std::ostream & os,
        int components = 0);

    inline void parser_name(
        string_parser const & parser, std::ostream & os, int components = 0);

    inline void parser_name(
        omit_parser<string_parser> const & parser,
        std::ostream & os,
        int components = 0);

    inline void parser_name(
        eol_parser const & parser, std::ostream & os, int components = 0);

    inline void parser_name(
        bool_parser const & parser, std::ostream & os, int components = 0);

    template<
        typename T,
        int Radix,
        int MinDigits,
        int MaxDigits,
        typename Expected>
    void parser_name(
        uint_parser<T, Radix, MinDigits, MaxDigits, Expected> const & parser,
        std::ostream & os,
        int components = 0);

    template<typename T, int Radix, int MinDigits, int MaxDigits>
    void parser_name(
        uint_parser<T, Radix, MinDigits, MaxDigits, nope> const & parser,
        std::ostream & os,
        int components = 0);

    inline void parser_name(
        uint_parser<unsigned int, 2> const & parser,
        std::ostream & os,
        int components = 0);

    inline void parser_name(
        uint_parser<unsigned int, 8> const & parser,
        std::ostream & os,
        int components = 0);

    inline void parser_name(
        uint_parser<unsigned int, 16> const & parser,
        std::ostream & os,
        int components = 0);

    inline void parser_name(
        uint_parser<unsigned short> const & parser,
        std::ostream & os,
        int components = 0);

    inline void parser_name(
        uint_parser<unsigned int> const & parser,
        std::ostream & os,
        int components = 0);

    inline void parser_name(
        uint_parser<unsigned long> const & parser,
        std::ostream & os,
        int components = 0);

    inline void parser_name(
        uint_parser<unsigned long long> const & parser,
        std::ostream & os,
        int components = 0);

    template<
        typename T,
        int Radix,
        int MinDigits,
        int MaxDigits,
        typename Expected>
    void parser_name(
        int_parser<T, Radix, MinDigits, MaxDigits, Expected> const & parser,
        std::ostream & os,
        int components = 0);

    template<typename T, int Radix, int MinDigits, int MaxDigits>
    void parser_name(
        int_parser<T, Radix, MinDigits, MaxDigits, nope> const & parser,
        std::ostream & os,
        int components = 0);

    inline void parser_name(
        int_parser<short> const & parser,
        std::ostream & os,
        int components = 0);

    inline void parser_name(
        int_parser<int> const & parser, std::ostream & os, int components = 0);

    inline void parser_name(
        int_parser<long> const & parser, std::ostream & os, int components = 0);

    inline void parser_name(
        int_parser<long long> const & parser,
        std::ostream & os,
        int components = 0);

    template<typename T>
    void parser_name(
        float_parser<T> const & parser, std::ostream & os, int components = 0);

    inline void parser_name(
        float_parser<float> const & parser,
        std::ostream & os,
        int components = 0);

    inline void parser_name(
        float_parser<double> const & parser,
        std::ostream & os,
        int components = 0);

    enum { trace_indent_factor = 2 };

    inline void trace_indent(int indent)
    {
        for (int i = 0, end = trace_indent_factor * indent; i != end; ++i) {
            std::cout << ' ';
        }
    }

    template<typename Iter, int SizeofValueType>
    struct trace_input_impl
    {
        static void call(
            std::ostream & os,
            Iter first_,
            Iter last_,
            bool quote,
            int64_t trace_input_cps)
        {
            static_assert(
                std::is_integral<std::decay_t<decltype(*first_)>>{}, "");
            static_assert(SizeofValueType == 4, "");
            auto first =
                text::utf8::make_from_utf32_iterator(first_, first_, last_);
            auto last =
                text::utf8::make_from_utf32_iterator(first_, last_, last_);
            if (quote)
                os << '"';
            for (int64_t i = 0; i < trace_input_cps && first != last;
                 ++i, ++first) {
                os << *first;
            }
            if (quote)
                os << '"';
        }
    };

    template<typename Iter>
    struct trace_input_impl<Iter, 1>
    {
        static void call(
            std::ostream & os,
            Iter first_,
            Iter last_,
            bool quote,
            int64_t trace_input_cps)
        {
            auto first =
                text::utf8::make_to_utf32_iterator(first_, first_, last_);
            auto last =
                text::utf8::make_to_utf32_iterator(first_, last_, last_);
            static_assert(sizeof(*first_) == 1);
            for (int64_t i = 0; i < trace_input_cps && first != last; ++i) {
                ++first;
            }
            if (quote)
                os << '"';
            for (Iter it = first_, end = first.base(); it != end; ++it) {
                os << *it;
            }
            if (quote)
                os << '"';
        }
    };

    template<typename Iter>
    inline void trace_input(
        std::ostream & os,
        Iter first,
        Iter last,
        bool quote = true,
        int64_t trace_input_cps = 8)
    {
        trace_input_impl<Iter, sizeof(*first)>::call(
            os, first, last, quote, trace_input_cps);
    }

    template<typename Iter>
    inline void
    trace_begin_match(Iter first, Iter last, int indent, std::string_view name)
    {
        trace_indent(indent);
        std::cout << "[begin " << name << "; input=";
        trace_input(std::cout, first, last);
        std::cout << "]" << std::endl;
    }

    template<typename Iter>
    inline void
    trace_end_match(Iter first, Iter last, int indent, std::string_view name)
    {
        trace_indent(indent);
        std::cout << "[end " << name << "; input=";
        trace_input(std::cout, first, last);
        std::cout << "]" << std::endl;
    }

    template<typename Iter, typename Context>
    void trace_prefix(
        Iter first, Iter last, Context const & context, std::string_view name)
    {
        int & indent = _indent(context);
        trace_begin_match(first, last, indent, name);
        ++indent;
    }

    template<typename Iter, typename Context>
    void trace_suffix(
        Iter first, Iter last, Context const & context, std::string_view name)
    {
        int & indent = _indent(context);
        --indent;
        trace_end_match(first, last, indent, name);
    }

    template<typename T, typename = void_t<>>
    struct printer
    {
        std::ostream & operator()(std::ostream & os, T const &)
        {
            return os << "<<unprintable-value>>";
        }
    };

    template<typename T>
    void print_printable(std::ostream & os, T const & x)
    {
        os << x;
    }

    inline void print_printable(std::ostream & os, char c)
    {
        if (std::isprint(c)) {
            os << "'" << c << "'";
        } else {
            os << "'\\x" << std::hex << std::setw(2) << std::setfill('0')
               << (uint32_t)c << "'";
        }
    }

    inline void print_printable(std::ostream & os, char32_t c)
    {
        if (c < 256) {
            os << "U";
            print_printable(os, (char)c);
        } else {
            os << "U'\\U" << std::hex << std::setw(8) << std::setfill('0')
               << (uint32_t)c << "'";
        }
    }

    template<typename T>
    struct printer<
        T,
        void_t<decltype(
            std::declval<std::ostream &>() << std::declval<T const &>())>>
    {
        std::ostream & operator()(std::ostream & os, T const & x)
        {
            print_printable(os, x);
            return os;
        }
    };

    template<typename... T>
    inline void print(std::ostream & os, hana::tuple<T...> const & attr);

    template<typename... T>
    inline void print(std::ostream & os, variant<T...> const & attr);

    template<typename T>
    inline void print(std::ostream & os, optional<T> const & attr);

    template<typename Attribute>
    inline void print(std::ostream & os, Attribute const & attr);

    template<typename... T>
    inline void print(std::ostream & os, hana::tuple<T...> const & attr)
    {
        os << "(";
        bool first = false;
        hana::for_each(attr, [&](auto const & a) {
            if (first)
                os << ", ";
            print(os, a);
            first = false;
        });
        os << ")\n";
    }

    template<typename... T>
    inline void print(std::ostream & os, variant<T...> const & attr)
    {
        os << "<<variant>>";
    }

    template<typename T>
    inline void print(std::ostream & os, optional<T> const & attr)
    {
        if (!attr)
            os << "<<empty>>";
        else
            print(os, *attr);
    }

    template<typename Attribute>
    inline void print(std::ostream & os, Attribute const & attr)
    {
        printer<Attribute>{}(os, attr);
    }

    template<typename Attribute>
    inline void print_attribute(Attribute const & attr, int indent)
    {
        trace_indent(indent);
        std::cout << "attribute: ";
        print(std::cout, attr);
        std::cout << "\n";
    }

    inline void print_attribute(nope const &, int) {}

    constexpr inline bool do_trace(flags f)
    {
        return (uint32_t(f) & uint32_t(flags::trace)) == uint32_t(flags::trace);
    }

    template<typename Iter, typename Context, typename Attribute>
    struct scoped_trace_t
    {
        scoped_trace_t(
            Iter & first,
            Iter last,
            Context const & context,
            flags f,
            Attribute const & attr,
            std::string name) :
            initial_first_(first),
            first_(first),
            last_(last),
            context_(context),
            flags_(f),
            attr_(attr),
            name_(std::move(name))
        {
            if (!do_trace(flags_))
                return;
            trace_prefix(first_, last_, context_, name_);
        }

        ~scoped_trace_t()
        {
            if (!do_trace(flags_))
                return;
            trace_indent(_indent(context_));
            if (*context_[hana::type_c<pass_tag>]) {
                std::cout << "matched ";
                trace_input(std::cout, initial_first_, first_);
                std::cout << "\n";
                print_attribute(attr_, _indent(context_));
            } else {
                std::cout << "no match\n";
            }
            trace_suffix(first_, last_, context_, name_);
        }

        Iter initial_first_;
        Iter & first_;
        Iter last_;
        Context const & context_;
        flags flags_;
        Attribute const & attr_;
        std::string name_;
    };

    template<
        typename Parser,
        typename Iter,
        typename Context,
        typename Attribute>
    auto scoped_trace(
        Parser const & parser,
        Iter & first,
        Iter last,
        Context const & context,
        flags f,
        Attribute const & attr)
    {
        std::stringstream oss;
        parser_name(parser, oss);
        return scoped_trace_t<Iter, Context, Attribute>(
            first, last, context, f, attr, oss.str());
    }

    template<typename Context, typename Attribute>
    auto final_trace(Context const & context, flags f, Attribute const & attr)
    {
        if (!do_trace(f))
            return;

        std::cout << "--------------------\n";
        if (*context[hana::type_c<pass_tag>]) {
            std::cout << "parse succeeded\n";
            print_attribute(attr, 0);
        } else {
            std::cout << "parse failed\n";
        }
        std::cout << "--------------------" << std::endl;
    }

}}}

#endif
