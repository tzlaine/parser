#ifndef BOOST_PARSER_DETAIL_PRINTING_IMPL_HPP
#define BOOST_PARSER_DETAIL_PRINTING_IMPL_HPP

#include <boost/parser/detail/printing.hpp>

#include <boost/type_index.hpp>


namespace boost { namespace parser { namespace detail {

    template<typename Parser>
    void parser_name(Parser const & parser, std::ostream & os, int components)
    {
        os << "<<unknown-parser>>";
    }

    template<typename Parser>
    void parser_name(
        repeat_parser<Parser, detail::nope> const & parser,
        std::ostream & os,
        int components)
    {
        if (parser.min_ == 0 && parser.max_ == Inf) {
            os << "*";
            parser_name(parser.parser_, os, components + 1);
        } else if (parser.min_ == 1 && parser.max_ == Inf) {
            os << "+";
            parser_name(parser.parser_, os, components + 1);
        } else {
            os << "repeat(";
            print(os, parser.min_);
            if (parser.min_ == parser.max_) {
                os << ")[";
            } else {
                os << ", ";
                if (parser.max_ == unbounded)
                    os << "Inf";
                else
                    print(os, parser.max_);
                os << ")[";
            }
            parser_name(parser.parser_, os, components + 1);
            os << "]";
        }
    }

    template<typename Parser, typename DelimiterParser>
    void parser_name(
        repeat_parser<Parser, DelimiterParser> const & parser,
        std::ostream & os,
        int components)
    {
        parser_name(parser.parser_, os, components + 1);
        os << " % ";
        parser_name(parser.delimiter_parser_, os, components + 2);
    }

    template<typename Parser>
    void parser_name(
        opt_parser<Parser> const & parser, std::ostream & os, int components)
    {
        os << "-";
        parser_name(parser.parser_, os, components + 1);
    }

    template<typename ParserTuple>
    void parser_name(
        or_parser<ParserTuple> const & parser,
        std::ostream & os,
        int components)
    {
        int i = 0;
        bool printed_ellipsis = false;
        hana::for_each(parser.parsers_, [&](auto const & parser) {
            if (components == parser_component_limit) {
                if (!printed_ellipsis)
                    os << " | ...";
                printed_ellipsis = true;
                return;
            }
            if (i)
                os << " | ";
            parser_name(parser, os, components);
            ++components;
            ++i;
        });
    }

    template<typename ParserTuple, typename BacktrackingTuple>
    void parser_name(
        seq_parser<ParserTuple, BacktrackingTuple> const & parser,
        std::ostream & os,
        int components)
    {
        int i = 0;
        bool printed_ellipsis = false;
        hana::for_each(
            hana::zip(parser.parsers_, BacktrackingTuple{}),
            [&](auto const & parser_and_backtrack) {
                using namespace hana::literals;
                auto const & parser = parser_and_backtrack[0_c];
                auto const backtrack = parser_and_backtrack[1_c];

                if (components == parser_component_limit) {
                    if (!printed_ellipsis)
                        os << (backtrack ? " >> ..." : " > ...");
                    printed_ellipsis = true;
                    return;
                }
                if (i)
                    os << (backtrack ? " >> " : " > ");
                parser_name(parser, os, components);
                ++components;
                ++i;
            });
    }

    template<typename Parser, typename Action>
    void parser_name(
        action_parser<Parser, Action> const & parser,
        std::ostream & os,
        int components)
    {
        parser_name(parser.parser_, os, components);
        os << "[<<action>>]";
    }

    template<typename Parser>
    void directive_name(
        std::string_view name,
        Parser const & parser,
        std::ostream & os,
        int components)
    {
        os << name << "[";
        if (++components == parser_component_limit)
            os << "...";
        else
            parser_name(parser, os, components + 1);
        os << "]";
    }

    template<typename Parser>
    void parser_name(
        omit_parser<Parser> const & parser, std::ostream & os, int components)
    {
        directive_name("omit", parser.parser_, os, components);
    }

    template<typename Parser>
    void parser_name(
        raw_parser<Parser> const & parser, std::ostream & os, int components)
    {
        directive_name("raw", parser.parser_, os, components);
    }

    template<typename Parser>
    void parser_name(
        lexeme_parser<Parser> const & parser, std::ostream & os, int components)
    {
        directive_name("lexeme", parser.parser_, os, components);
    }

    template<typename Parser>
    void parser_name(
        skip_parser<Parser, detail::nope> const & parser,
        std::ostream & os,
        int components)
    {
        directive_name("skip", parser.parser_, os, components);
    }

    template<typename Parser, typename SkipParser>
    void parser_name(
        skip_parser<Parser> const & parser, std::ostream & os, int components)
    {
        os << "skip(";
        parser_name(parser.skip_parser_, os, components);
        os << ")";
        directive_name("", parser.parser_, os, components + 1);
    }

    template<typename Parser>
    void parser_name(
        expect_parser<Parser, true> const & parser,
        std::ostream & os,
        int components)
    {
        os << "!";
        parser_name(parser.parser_, os, components + 1);
    }

    template<typename Parser>
    void parser_name(
        expect_parser<Parser, false> const & parser,
        std::ostream & os,
        int components)
    {
        os << "&";
        parser_name(parser.parser_, os, components + 1);
    }

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
        int components)
    {
        // TODO: Print params?
        os << parser.name_;
    }

    template<typename T>
    void parser_name(
        symbol_parser<T> const & parser, std::ostream & os, int components)
    {
        os << "symbols<" << typeindex::type_id<T>().pretty_name() << ">";
    }

    template<typename Predicate>
    void parser_name(
        eps_parser<Predicate> const & parser, std::ostream & os, int components)
    {
        os << "eps(<<predicate>>)";
    }

    inline void parser_name(
        eps_parser<nope> const & parser, std::ostream & os, int components)
    {
        os << "eps";
    }

    inline void
    parser_name(eoi_parser const & parser, std::ostream & os, int components)
    {
        os << "eoi";
    }

    template<typename Atribute>
    void parser_name(
        attr_parser<Atribute> const & parser, std::ostream & os, int components)
    {
        os << "attr(";
        print(os, parser.attr_);
        os << ")";
    }

    template<
        typename Expected,
        bool Integral = std::is_integral<Expected>{},
        int SizeofExpected = sizeof(Expected)>
    struct print_expected_impl
    {
        static void call(std::ostream & os, Expected expected)
        {
            print(os, expected);
        }
    };

    template<typename Expected>
    struct print_expected_impl<Expected, true, 4>
    {
        static void call(std::ostream & os, Expected expected)
        {
            std::array<uint32_t, 1> cps = {{(uint32_t)expected}};
            auto const r = text::make_from_utf32_range(cps);
            for (auto c : r) {
                os << c;
            }
        }
    };

    template<typename Expected>
    void print_expected(std::ostream & os, Expected expected)
    {
        print_expected_impl<Expected>::call(os, expected);
    }

    template<typename T>
    struct char_parser_name_impl
    {
        static void call(std::ostream & os, T expected)
        {
            os << "char_(";
            print_expected(os, expected);
            os << ")";
        }
    };

    template<typename T>
    struct char_parser_name_impl<char_pair<T>>
    {
        static void call(std::ostream & os, char_pair<T> expected)
        {
            os << "char_(";
            print_expected(os, expected.lo_);
            os << ", ";
            print_expected(os, expected.hi_);
            os << ")";
        }
    };

    template<typename Range>
    struct char_parser_name_impl<char_range<Range>>
    {
        static void call(std::ostream & os, char_range<Range> expected)
        {
            os << "char_(";
            for (auto c : expected.chars_) {
                print_expected(os, c);
            }
            os << ")";
        }
    };

    template<typename Expected>
    void parser_name(
        char_parser<Expected> const & parser, std::ostream & os, int components)
    {
        char_parser_name_impl<Expected>::call(os, parser.expected_);
    }

    inline void parser_name(
        char_parser<nope> const & parser, std::ostream & os, int components)
    {
        os << "char_";
    }

    template<typename Expected>
    void parser_name(
        omit_parser<char_parser<Expected>> const & parser,
        std::ostream & os,
        int components)
    {
        parser_name(parser.parser_, os, components);
    }

    template<typename Expected>
    void parser_name(
        char_parser<Expected, uint32_t> const & parser,
        std::ostream & os,
        int components)
    {
        os << "cp(";
        print(os, parser.expected_);
        os << ")";
    }

    inline void parser_name(
        char_parser<nope, uint32_t> const & parser,
        std::ostream & os,
        int components)
    {
        os << "cp";
    }

    inline void
    parser_name(string_parser const & parser, std::ostream & os, int components)
    {
        os << "string(\"" << parser.expected_ << "\")";
    }

    inline void parser_name(
        omit_parser<string_parser> const & parser,
        std::ostream & os,
        int components)
    {
        os << "\"";
        print(os, parser.parser_.expected_);
        os << "\"";
    }

    inline void
    parser_name(eol_parser const & parser, std::ostream & os, int components)
    {
        os << "eol";
    }

    inline void
    parser_name(bool_parser const & parser, std::ostream & os, int components)
    {
        os << "bool_";
    }

    template<
        typename T,
        int Radix,
        int MinDigits,
        int MaxDigits,
        typename Expected>
    void parser_name(
        uint_parser<T, Radix, MinDigits, MaxDigits, Expected> const & parser,
        std::ostream & os,
        int components)
    {
        os << "uint<" << typeindex::type_id<T>().pretty_name() << ", " << Radix
           << ", " << MinDigits << ", " << MaxDigits << ">(";
        print(os, parser.expected_);
        os << ")";
    }

    template<typename T, int Radix, int MinDigits, int MaxDigits>
    void parser_name(
        uint_parser<T, Radix, MinDigits, MaxDigits, nope> const & parser,
        std::ostream & os,
        int components)
    {
        os << "uint<" << typeindex::type_id<T>().pretty_name() << ", " << Radix
           << ", " << MinDigits << ", " << MaxDigits << ">";
    }

    inline void parser_name(
        uint_parser<unsigned int, 2> const & parser,
        std::ostream & os,
        int components)
    {
        os << "bin";
    }

    inline void parser_name(
        uint_parser<unsigned int, 8> const & parser,
        std::ostream & os,
        int components)
    {
        os << "oct";
    }

    inline void parser_name(
        uint_parser<unsigned int, 16> const & parser,
        std::ostream & os,
        int components)
    {
        os << "hex";
    }

    inline void parser_name(
        uint_parser<unsigned short> const & parser,
        std::ostream & os,
        int components)
    {
        os << "ushort_";
    }

    inline void parser_name(
        uint_parser<unsigned int> const & parser,
        std::ostream & os,
        int components)
    {
        os << "uint_";
    }

    inline void parser_name(
        uint_parser<unsigned long> const & parser,
        std::ostream & os,
        int components)
    {
        os << "ulong_";
    }

    inline void parser_name(
        uint_parser<unsigned long long> const & parser,
        std::ostream & os,
        int components)
    {
        os << "ulong_long";
    }

    template<
        typename T,
        int Radix,
        int MinDigits,
        int MaxDigits,
        typename Expected>
    void parser_name(
        int_parser<T, Radix, MinDigits, MaxDigits, Expected> const & parser,
        std::ostream & os,
        int components)
    {
        os << "int<" << typeindex::type_id<T>().pretty_name() << ", " << Radix
           << ", " << MinDigits << ", " << MaxDigits << ">(";
        print(os, parser.expected_);
        os << ")";
    }

    template<typename T, int Radix, int MinDigits, int MaxDigits>
    void parser_name(
        int_parser<T, Radix, MinDigits, MaxDigits, nope> const & parser,
        std::ostream & os,
        int components)
    {
        os << "int<" << typeindex::type_id<T>().pretty_name() << ", " << Radix
           << ", " << MinDigits << ", " << MaxDigits << ">";
    }

    inline void parser_name(
        int_parser<short> const & parser, std::ostream & os, int components)
    {
        os << "short_";
    }

    inline void parser_name(
        int_parser<int> const & parser, std::ostream & os, int components)
    {
        os << "int_";
    }

    inline void parser_name(
        int_parser<long> const & parser, std::ostream & os, int components)
    {
        os << "long_";
    }

    inline void parser_name(
        int_parser<long long> const & parser, std::ostream & os, int components)
    {
        os << "long_long";
    }

    template<typename T>
    void parser_name(
        float_parser<T> const & parser, std::ostream & os, int components)
    {
        os << "float<" << typeindex::type_id<T>().pretty_name() << ">";
    }

    inline void parser_name(
        float_parser<float> const & parser, std::ostream & os, int components)
    {
        os << "float_";
    }

    inline void parser_name(
        float_parser<double> const & parser, std::ostream & os, int components)
    {
        os << "double_";
    }

}}}

#endif
