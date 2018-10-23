#ifndef BOOST_PARSER_DETAIL_PRINTING_IMPL_HPP
#define BOOST_PARSER_DETAIL_PRINTING_IMPL_HPP

#include <boost/parser/detail/printing.hpp>

#include <boost/type_index.hpp>


namespace boost { namespace parser { namespace detail {

    template<typename Parser>
    void parser_name(Parser const & parser, std::string & str, int components)
    {
        str += "<<unknown-parser>>";
    }

    template<typename Parser>
    void parser_name(
        repeat_parser<Parser, detail::nope> const & parser,
        std::string & str,
        int components)
    {
        if (parser.min_ == 0 && parser.max_ == Inf) {
            str += "*";
            parser_name(parser.parser_, str, components + 1);
        } else if (parser.min_ == 1 && parser.max_ == Inf) {
            str += "+";
            parser_name(parser.parser_, str, components + 1);
        } else {
            str += "repeat(";
            str += std::to_string(parser.min_);
            if (parser.min_ == parser.max_) {
                str += ")[";
            } else {
                str += ", ";
                if (parser.max_ == unbounded)
                    str += "Inf";
                else
                    str += std::to_string(parser.max_);
                str += ")[";
            }
            parser_name(parser.parser_, str, components + 1);
            str += "]";
        }
    }

    template<typename Parser>
    void parser_name(
        zero_plus_parser<Parser> const & parser,
        std::string & str,
        int components)
    {
        str += "*";
        parser_name(parser.parser_, str, components + 1);
    }

    template<typename Parser>
    void parser_name(
        one_plus_parser<Parser> const & parser,
        std::string & str,
        int components)
    {
        str += "+";
        parser_name(parser.parser_, str, components + 1);
    }

    template<typename Parser, typename DelimiterParser>
    void parser_name(
        delimited_seq_parser<Parser, DelimiterParser> const & parser,
        std::string & str,
        int components)
    {
        parser_name(parser.parser_, str, components + 1);
        str += " % ";
        parser_name(parser.delimiter_parser_, str, components + 2);
    }

    template<typename Parser>
    void parser_name(
        opt_parser<Parser> const & parser,
        std::string & str,
        int components)
    {
        str += "-";
        parser_name(parser.parser_, str, components + 1);
    }

    template<typename ParserTuple>
    void parser_name(
        or_parser<ParserTuple> const & parser,
        std::string & str,
        int components)
    {
        int i = 0;
        bool printed_ellipsis = false;
        hana::for_each(parser.parsers_, [&](auto const & parser) {
            if (components == parser_component_limit) {
                if (!printed_ellipsis)
                    str += " | ...";
                printed_ellipsis = true;
                return;
            }
            if (i)
                str += " | ";
            parser_name(parser, str, components);
            ++components;
            ++i;
        });
    }

    template<typename ParserTuple, typename BacktrackingTuple>
    void parser_name(
        seq_parser<ParserTuple, BacktrackingTuple> const & parser,
        std::string & str,
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
                        str += backtrack ? " >> ..." : " > ...";
                    printed_ellipsis = true;
                    return;
                }
                if (i)
                    str += backtrack ? " >> " : " > ";
                parser_name(parser, str, components);
                ++components;
                ++i;
            });
    }

    template<typename Parser, typename Action>
    void parser_name(
        action_parser<Parser, Action> const & parser,
        std::string & str,
        int components)
    {
        parser_name(parser.parser_, str, components);
        str += "[<<action>>]";
    }

    template<typename Parser>
    void directive_name(
        std::string_view name,
        Parser const & parser,
        std::string & str,
        int components)
    {
        str += name;
        str += "[";
        if (++components == parser_component_limit)
            str += "...";
        else
            parser_name(parser, str, components + 1);
        str += "]";
    }

    template<typename Parser>
    void parser_name(
        omit_parser<Parser> const & parser, std::string & str, int components)
    {
        directive_name("omit", parser.parser_, str, components);
    }

    template<typename Parser>
    void parser_name(
        raw_parser<Parser> const & parser, std::string & str, int components)
    {
        directive_name("raw", parser.parser_, str, components);
    }

    template<typename Parser>
    void parser_name(
        lexeme_parser<Parser> const & parser, std::string & str, int components)
    {
        directive_name("lexeme", parser.parser_, str, components);
    }

    template<typename Parser>
    void parser_name(
        expect_parser<Parser, true> const & parser,
        std::string & str,
        int components)
    {
        str += "!";
        parser_name(parser.parser_, str, components + 1);
    }

    template<typename Parser>
    void parser_name(
        expect_parser<Parser, false> const & parser,
        std::string & str,
        int components)
    {
        str += "&";
        parser_name(parser.parser_, str, components + 1);
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
        std::string & str,
        int components)
    {
        // TODO: Print attribute type?
        // TODO: Print locals type?
        // TODO: Print params.
        str += parser.name_;
    }

    template<typename T>
    void parser_name(
        symbol_parser<T> const & parser, std::string & str, int components)
    {
        str += "symbols<";
        str += typeindex::type_id<T>().pretty_name();
        str += ">";
    }

    template<typename Predicate>
    void parser_name(
        eps_parser<Predicate> const & parser, std::string & str, int components)
    {
        str += "eps(<<predicate>>)";
    }

    inline void parser_name(
        eps_parser<nope> const & parser, std::string & str, int components)
    {
        str += "eps";
    }

    inline void
    parser_name(eoi_parser const & parser, std::string & str, int components)
    {
        str += "eoi";
    }

    template<
        typename Expected,
        bool Integral = std::is_integral<Expected>{},
        int SizeofExpected = sizeof(Expected)>
    struct print_expected_impl
    {
        static void call(std::string & str, Expected expected)
        {
            str += to_string(expected);
        }
    };

    template<typename Expected>
    struct print_expected_impl<Expected, true, 1>
    {
        static void call(std::string & str, Expected expected)
        {
            str += to_string(expected);
        }
    };

    template<typename Expected>
    struct print_expected_impl<Expected, true, 4>
    {
        static void call(std::string & str, Expected expected)
        {
            std::array<uint32_t, 1> cps = {{(uint32_t)expected}};
            auto const r = text::make_from_utf32_range(cps);
            for (auto c : r) {
                str += c;
            }
        }
    };

    template<typename Expected>
    void print_expected(std::string & str, Expected expected)
    {
        print_expected_impl<Expected>::call(str, expected);
    }

    template<typename T>
    struct char_parser_name_impl
    {
        static void call(std::string & str, T expected)
        {
            str += "char_(";
            print_expected(str, expected);
            str += ")";
        }
    };

    template<typename T>
    struct char_parser_name_impl<char_pair<T>>
    {
        static void call(std::string & str, char_pair<T> expected)
        {
            str += "char_(";
            print_expected(str, expected.lo_);
            str += ", ";
            print_expected(str, expected.hi_);
            str += ")";
        }
    };

    template<typename Range>
    struct char_parser_name_impl<char_range<Range>>
    {
        static void call(std::string & str, char_range<Range> expected)
        {
            str += "char_(";
            for (auto c : expected.chars_) {
                print_expected(str, c);
            }
            str += ")";
        }
    };

    template<typename Expected>
    void parser_name(
        char_parser<Expected> const & parser, std::string & str, int components)
    {
        char_parser_name_impl<Expected>::call(str, parser.expected_);
    }

    inline void parser_name(
        char_parser<nope> const & parser, std::string & str, int components)
    {
        str += "char_";
    }

    template<typename Expected>
    void parser_name(
        omit_parser<char_parser<Expected>> const & parser,
        std::string & str,
        int components)
    {
        str += to_string(parser.parser_.expected_);
    }

    template<typename Expected>
    void parser_name(
        char_parser<Expected, uint32_t> const & parser,
        std::string & str,
        int components)
    {
        str += "cp(";
        str += to_string(parser.expected_);
        str += ")";
    }

    inline void parser_name(
        char_parser<nope, uint32_t> const & parser,
        std::string & str,
        int components)
    {
        str += "cp";
    }

    inline void
    parser_name(string_parser const & parser, std::string & str, int components)
    {
        str += "string(\"";
        str += parser.expected_;
        str += "\")";
    }

    inline void parser_name(
        omit_parser<string_parser> const & parser,
        std::string & str,
        int components)
    {
        str += "\"";
        str += parser.parser_.expected_;
        str += "\"";
    }

    inline void parser_name(
        eol_parser const & parser, std::string & str, int components)
    {
        str += "eol";
    }

    inline void
    parser_name(bool_parser const & parser, std::string & str, int components)
    {
        str += "bool_";
    }

    template<
        typename T,
        int Radix,
        int MinDigits,
        int MaxDigits,
        typename Expected>
    void parser_name(
        uint_parser<T, Radix, MinDigits, MaxDigits, Expected> const & parser,
        std::string & str,
        int components)
    {
        str += "uint<";
        str += typeindex::type_id<T>().pretty_name();
        str += ", ";
        str += std::to_string(Radix);
        str += ", ";
        str += std::to_string(MinDigits);
        str += ", ";
        str += std::to_string(MaxDigits);
        str += ">(";
        str += std::to_string(parser.expected_);
        str += ")";
    }

    template<
        typename T,
        int Radix,
        int MinDigits,
        int MaxDigits>
    void parser_name(
        uint_parser<T, Radix, MinDigits, MaxDigits, nope> const & parser,
        std::string & str,
        int components)
    {
        str += "uint<";
        str += typeindex::type_id<T>().pretty_name();
        str += ", ";
        str += std::to_string(Radix);
        str += ", ";
        str += std::to_string(MinDigits);
        str += ", ";
        str += std::to_string(MaxDigits);
        str += ">";
    }

    inline void parser_name(
        uint_parser<unsigned int, 2> const & parser,
        std::string & str,
        int components)
    {
        str += "bin";
    }

    inline void parser_name(
        uint_parser<unsigned int, 8> const & parser,
        std::string & str,
        int components)
    {
        str += "oct";
    }

    inline void parser_name(
        uint_parser<unsigned int, 16> const & parser,
        std::string & str,
        int components)
    {
        str += "hex";
    }

    inline void parser_name(
        uint_parser<unsigned short> const & parser,
        std::string & str,
        int components)
    {
        str += "ushort_";
    }

    inline void parser_name(
        uint_parser<unsigned int> const & parser,
        std::string & str,
        int components)
    {
        str += "uint_";
    }

    inline void parser_name(
        uint_parser<unsigned long> const & parser,
        std::string & str,
        int components)
    {
        str += "ulong_";
    }

    inline void parser_name(
        uint_parser<unsigned long long> const & parser,
        std::string & str,
        int components)
    {
        str += "ulong_long";
    }

    template<
        typename T,
        int Radix,
        int MinDigits,
        int MaxDigits,
        typename Expected>
    void parser_name(
        int_parser<T, Radix, MinDigits, MaxDigits, Expected> const & parser,
        std::string & str,
        int components)
    {
        str += "int<";
        str += typeindex::type_id<T>().pretty_name();
        str += ", ";
        str += std::to_string(Radix);
        str += ", ";
        str += std::to_string(MinDigits);
        str += ", ";
        str += std::to_string(MaxDigits);
        str += ">(";
        str += std::to_string(parser.expected_);
        str += ")";
    }

    template<typename T, int Radix, int MinDigits, int MaxDigits>
    void parser_name(
        int_parser<T, Radix, MinDigits, MaxDigits, nope> const & parser,
        std::string & str,
        int components)
    {
        str += "int<";
        str += typeindex::type_id<T>().pretty_name();
        str += ", ";
        str += std::to_string(Radix);
        str += ", ";
        str += std::to_string(MinDigits);
        str += ", ";
        str += std::to_string(MaxDigits);
        str += ">";
    }

    inline void parser_name(
        int_parser<short> const & parser, std::string & str, int components)
    {
        str += "short_";
    }

    inline void parser_name(
        int_parser<int> const & parser, std::string & str, int components)
    {
        str += "int_";
    }

    inline void parser_name(
        int_parser<long> const & parser, std::string & str, int components)
    {
        str += "long_";
    }

    inline void parser_name(
        int_parser<long long> const & parser, std::string & str, int components)
    {
        str += "long_long";
    }

    template<typename T>
    void parser_name(
        float_parser<T> const & parser, std::string & str, int components)
    {
        str += "float<";
        str += typeindex::type_id<T>().pretty_name();
        str += ">";
    }

    inline void parser_name(
        float_parser<float> const & parser, std::string & str, int components)
    {
        str += "float_";
    }

    inline void parser_name(
        float_parser<double> const & parser, std::string & str, int components)
    {
        str += "double_";
    }

}}}

#endif
