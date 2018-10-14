#ifndef BOOST_PARSER_DETAIL_PRINTING_HPP
#define BOOST_PARSER_DETAIL_PRINTING_HPP

#include <boost/parser/parser_fwd.hpp>
#include <boost/parser/detail/detection.hpp>

#include <boost/hana.hpp>
#include <boost/optional.hpp>
#include <boost/optional/optional_io.hpp>
#include <boost/variant.hpp>

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>


namespace boost { namespace parser { namespace detail {

    enum { parser_component_limit = 4 };

    template<typename Parser>
    void
    parser_name(Parser const & parser, std::string & str, int components = 0);

    template<typename Parser>
    void parser_name(
        repeat_parser<Parser, detail::nope> const & parser,
        std::string & str,
        int components = 0);

    template<typename Parser, typename DelimiterParser>
    void parser_name(
        repeat_parser<Parser, DelimiterParser> const & parser,
        std::string & str,
        int components = 0);

    template<typename Parser>
    void parser_name(
        opt_parser<Parser> const & parser,
        std::string & str,
        int components = 0);

    template<typename ParserTuple>
    void parser_name(
        or_parser<ParserTuple> const & parser,
        std::string & str,
        int components = 0);

    template<typename ParserTuple, typename BacktrackingTuple>
    void parser_name(
        seq_parser<ParserTuple, BacktrackingTuple> const & parser,
        std::string & str,
        int components = 0);

    template<typename Parser, typename Action>
    void parser_name(
        action_parser<Parser, Action> const & parser,
        std::string & str,
        int components = 0);

    template<typename Parser>
    void parser_name(
        omit_parser<Parser> const & parser,
        std::string & str,
        int components = 0);

    template<typename Parser>
    void parser_name(
        raw_parser<Parser> const & parser,
        std::string & str,
        int components = 0);

    template<typename Parser>
    void parser_name(
        lexeme_parser<Parser> const & parser,
        std::string & str,
        int components = 0);

    template<typename Parser>
    void parser_name(
        expect_parser<Parser, true> const & parser,
        std::string & str,
        int components = 0);

    template<typename Parser>
    void parser_name(
        expect_parser<Parser, false> const & parser,
        std::string & str,
        int components = 0);

    template<typename Parser, typename Attribute, typename LocalState>
    void parser_name(
        rule_parser<Parser, Attribute, LocalState> const & parser,
        std::string & str,
        int components = 0);

    template<typename Predicate>
    void parser_name(
        eps_parser<Predicate> const & parser,
        std::string & str,
        int components = 0);

    void parser_name(
        eps_parser<nope> const & parser, std::string & str, int components = 0);

    inline void parser_name(
        eoi_parser const & parser, std::string & str, int components = 0);

    template<typename Expected>
    void parser_name(
        char_parser<Expected> const & parser,
        std::string & str,
        int components = 0);

    inline void parser_name(
        char_parser<nope> const & parser,
        std::string & str,
        int components = 0);

    template<typename Expected>
    void parser_name(
        omit_parser<char_parser<Expected>> const & parser,
        std::string & str,
        int components = 0);

    inline void parser_name(
        string_parser const & parser, std::string & str, int components = 0);

    inline void parser_name(
        omit_parser<string_parser> const & parser,
        std::string & str,
        int components = 0);

    inline void parser_name(
        eol_parser const & parser, std::string & str, int components = 0);

    template<
        typename T,
        int Radix,
        int MinDigits,
        int MaxDigits,
        typename Expected>
    void parser_name(
        uint_parser<T, Radix, MinDigits, MaxDigits, Expected> const & parser,
        std::string & str,
        int components = 0);

    template<typename T, int Radix, int MinDigits, int MaxDigits>
    void parser_name(
        uint_parser<T, Radix, MinDigits, MaxDigits, nope> const & parser,
        std::string & str,
        int components = 0);

    inline void parser_name(
        uint_parser<unsigned int, 2> const & parser,
        std::string & str,
        int components = 0);

    inline void parser_name(
        uint_parser<unsigned int, 8> const & parser,
        std::string & str,
        int components = 0);

    inline void parser_name(
        uint_parser<unsigned int, 16> const & parser,
        std::string & str,
        int components = 0);

    inline void parser_name(
        uint_parser<unsigned short> const & parser,
        std::string & str,
        int components = 0);

    inline void parser_name(
        uint_parser<unsigned int> const & parser,
        std::string & str,
        int components = 0);

    inline void parser_name(
        uint_parser<unsigned long> const & parser,
        std::string & str,
        int components = 0);

    inline void parser_name(
        uint_parser<unsigned long long> const & parser,
        std::string & str,
        int components = 0);

    template<
        typename T,
        int Radix,
        int MinDigits,
        int MaxDigits,
        typename Expected>
    void parser_name(
        int_parser<T, Radix, MinDigits, MaxDigits, Expected> const & parser,
        std::string & str,
        int components = 0);

    template<typename T, int Radix, int MinDigits, int MaxDigits>
    void parser_name(
        int_parser<T, Radix, MinDigits, MaxDigits, nope> const & parser,
        std::string & str,
        int components = 0);

    inline void parser_name(
        int_parser<short> const & parser,
        std::string & str,
        int components = 0);

    inline void parser_name(
        int_parser<int> const & parser,
        std::string & str,
        int components = 0);

    inline void parser_name(
        int_parser<long> const & parser,
        std::string & str,
        int components = 0);

    inline void parser_name(
        int_parser<long long> const & parser,
        std::string & str,
        int components = 0);

    template<typename T>
    void parser_name(
        float_parser<T> const & parser, std::string & str, int components = 0);

    inline void parser_name(
        float_parser<float> const & parser,
        std::string & str,
        int components = 0);

    inline void parser_name(
        float_parser<double> const & parser,
        std::string & str,
        int components = 0);

    enum { trace_indent_factor = 2, trace_input_cps = 8 };

    inline void trace_indent(int indent)
    {
        for (int i = 0, end = trace_indent_factor * indent; i != end; ++i) {
            std::cout << ' ';
        }
    }

    template<typename Iter>
    inline void trace_input(Iter first, Iter last)
    {
        // TODO: Print 8 code points worth of characters; use UTF-8 ->
        // UTF-32 iteration to get the number of code units to print when
        // *first is a char, and UTF-32 -> UTF-8 transcoding when *first
        // is a char32_t.  In both cases, the output should be UTF-8.

        std::cout << '"';
        for (int i = 0; i != trace_input_cps && first != last; ++first, ++i) {
            std::cout << *first;
        }
        std::cout << '"';
    }

    template<typename Iter>
    inline void
    trace_begin_match(Iter first, Iter last, int indent, std::string_view name)
    {
        trace_indent(indent);
        std::cout << "[begin " << name << "; input=";
        trace_input(first, last);
        std::cout << "]" << std::endl;
    }

    template<typename Iter>
    inline void
    trace_end_match(Iter first, Iter last, int indent, std::string_view name)
    {
        trace_indent(indent);
        std::cout << "[end " << name << "; input=";
        trace_input(first, last);
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

    template<typename T>
    std::string to_string(T const &)
    {
        return "<<unprintable-value>>";
    }

    inline std::string to_string(char c) { return std::string("'") + c + '\''; }

    inline std::string to_string(char32_t c)
    {
        if (c < 256) {
            return std::string("U'") + (char)c + '\'';
        } else {
            std::stringstream ss;
            ss << "U'\\U" << std::hex << std::setw(8) << std::setfill('0')
               << (uint32_t)c << "'";
            return ss.str();
        }
    }

    inline std::string to_string(std::string_view s) { return std::string(s); }

    template<typename T, typename = void_t<>>
    struct printer
    {
        std::ostream & operator()(std::ostream & os, T const &)
        {
            return os << "<<unprintable-value>>";
        }
    };

    template<typename T>
    struct printer<
        T,
        void_t<decltype(
            std::declval<std::ostream &>() << std::declval<T const &>())>>
    {
        std::ostream & operator()(std::ostream & os, T const & x)
        {
            return os << x;
        }
    };

    template<typename... T>
    inline void print(hana::tuple<T...> const & attr);

    template<typename... T>
    inline void print(variant<T...> const & attr);

    template<typename T>
    inline void print(optional<T> const & attr);

    template<typename Attribute>
    inline void print(Attribute const & attr);

    template<typename... T>
    inline void print(hana::tuple<T...> const & attr)
    {
        std::cout << "(";
        bool first = false;
        hana::for_each(attr, [&](auto const & a) {
            if (first)
                std::cout << ", ";
            print(a);
            first = false;
        });
        std::cout << ")\n";
    }

    template<typename... T>
    inline void print(variant<T...> const & attr)
    {
        std::cout << "TODO"; // TODO
    }

    template<typename T>
    inline void print(optional<T> const & attr)
    {
        if (!attr)
            std::cout << "<<empty>>";
        else
            print(*attr);
    }

    template<typename Attribute>
    inline void print(Attribute const & attr)
    {
        printer<Attribute>{}(std::cout, attr);
    }

    template<typename Attribute>
    inline void print_attribute(Attribute const & attr, int indent)
    {
        trace_indent(indent);
        std::cout << "attribute: ";
        print(attr);
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
                trace_input(initial_first_, first_);
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
        std::string name;
        parser_name(parser, name);
        return scoped_trace_t<Iter, Context, Attribute>(
            first, last, context, f, attr, std::move(name));
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
