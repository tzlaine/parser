#ifndef BOOST_PARSER_DETAIL_PRINTING_IMPL_HPP
#define BOOST_PARSER_DETAIL_PRINTING_IMPL_HPP

#include <boost/parser/detail/printing.hpp>

#include <boost/type_index.hpp>


namespace boost { namespace parser { namespace detail {

#if 0
    template<typename Context, typename Parser>
    void parser_name(
        Context const & context,
        Parser const & parser,
        std::ostream & os,
        int components)
    {
        os << "<<unknown-parser>>";
    }
#endif

    template<
        typename Context,
        typename Parser,
        typename MinType,
        typename MaxType>
    void parser_name(
        Context const & context,
        repeat_parser<Parser, nope, MinType, MaxType> const & parser,
        std::ostream & os,
        int components)
    {
        auto const min_ = resolve(context, parser.min_);
        auto const max_ = resolve(context, parser.max_);
        if (min_ == 0 && max_ == Inf) {
            os << "*";
            parser_name(context, parser.parser_, os, components + 1);
        } else if (min_ == 1 && max_ == Inf) {
            os << "+";
            parser_name(context, parser.parser_, os, components + 1);
        } else {
            os << "repeat(";
            print(os, min_);
            if (min_ == max_) {
                os << ")[";
            } else {
                os << ", ";
                if (max_ == unbounded)
                    os << "Inf";
                else
                    print(os, max_);
                os << ")[";
            }
            parser_name(context, parser.parser_, os, components + 1);
            os << "]";
        }
    }

    template<
        typename Context,
        typename Parser,
        typename DelimiterParser,
        typename MinType,
        typename MaxType>
    void parser_name(
        Context const & context,
        repeat_parser<Parser, DelimiterParser, MinType, MaxType> const & parser,
        std::ostream & os,
        int components)
    {
        parser_name(context, parser.parser_, os, components + 1);
        os << " % ";
        parser_name(context, parser.delimiter_parser_, os, components + 2);
    }

    template<typename Context, typename Parser>
    void parser_name(
        Context const & context,
        opt_parser<Parser> const & parser,
        std::ostream & os,
        int components)
    {
        os << "-";
        parser_name(context, parser.parser_, os, components + 1);
    }

    template<typename Context, typename ParserTuple>
    void parser_name(
        Context const & context,
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
            parser_name(context, parser, os, components);
            ++components;
            ++i;
        });
    }

    template<typename Context, typename ParserTuple, typename BacktrackingTuple>
    void parser_name(
        Context const & context,
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
                parser_name(context, parser, os, components);
                ++components;
                ++i;
            });
    }

    template<typename Context, typename Parser, typename Action>
    void parser_name(
        Context const & context,
        action_parser<Parser, Action> const & parser,
        std::ostream & os,
        int components)
    {
        parser_name(context, parser.parser_, os, components);
        os << "[<<action>>]";
    }

    template<typename Context, typename Parser>
    void directive_name(
        Context const & context,
        std::string_view name,
        Parser const & parser,
        std::ostream & os,
        int components)
    {
        os << name << "[";
        if (++components == parser_component_limit)
            os << "...";
        else
            parser_name(context, parser, os, components + 1);
        os << "]";
    }

    template<typename Context, typename Parser>
    void parser_name(
        Context const & context,
        omit_parser<Parser> const & parser,
        std::ostream & os,
        int components)
    {
        directive_name(context, "omit", parser.parser_, os, components);
    }

    template<typename Context, typename Parser>
    void parser_name(
        Context const & context,
        raw_parser<Parser> const & parser,
        std::ostream & os,
        int components)
    {
        directive_name(context, "raw", parser.parser_, os, components);
    }

    template<typename Context, typename Parser>
    void parser_name(
        Context const & context,
        lexeme_parser<Parser> const & parser,
        std::ostream & os,
        int components)
    {
        directive_name(context, "lexeme", parser.parser_, os, components);
    }

    template<typename Context, typename Parser>
    void parser_name(
        Context const & context,
        skip_parser<Parser, nope> const & parser,
        std::ostream & os,
        int components)
    {
        directive_name(context, "skip", parser.parser_, os, components);
    }

    template<typename Context, typename Parser, typename SkipParser>
    void parser_name(
        Context const & context,
        skip_parser<Parser> const & parser,
        std::ostream & os,
        int components)
    {
        os << "skip(";
        parser_name(context, parser.skip_parser_, os, components);
        os << ")";
        directive_name(context, "", parser.parser_, os, components + 1);
    }

    template<typename Context, typename Parser>
    void parser_name(
        Context const & context,
        expect_parser<Parser, true> const & parser,
        std::ostream & os,
        int components)
    {
        os << "!";
        parser_name(context, parser.parser_, os, components + 1);
    }

    template<typename Context, typename Parser>
    void parser_name(
        Context const & context,
        expect_parser<Parser, false> const & parser,
        std::ostream & os,
        int components)
    {
        os << "&";
        parser_name(context, parser.parser_, os, components + 1);
    }

    template<
        typename Context,
        bool UseCallbacks,
        typename Parser,
        typename Attribute,
        typename LocalState,
        typename ParamsTuple>
    void parser_name(
        Context const & context,
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

    template<typename Context, typename T>
    void parser_name(
        Context const & context,
        symbol_parser<T> const & parser,
        std::ostream & os,
        int components)
    {
        os << "symbols<" << typeindex::type_id<T>().pretty_name() << ">";
    }

    template<typename Context, typename Predicate>
    void parser_name(
        Context const & context,
        eps_parser<Predicate> const & parser,
        std::ostream & os,
        int components)
    {
        os << "eps(<<pred>>)";
    }

    template<typename Context>
    void parser_name(
        Context const & context,
        eps_parser<nope> const & parser,
        std::ostream & os,
        int components)
    {
        os << "eps";
    }

    template<typename Context>
    void parser_name(
        Context const & context,
        eoi_parser const & parser,
        std::ostream & os,
        int components)
    {
        os << "eoi";
    }

    template<typename Context, typename Atribute>
    void parser_name(
        Context const & context,
        attr_parser<Atribute> const & parser,
        std::ostream & os,
        int components)
    {
        os << "attr(";
        print(os, parser.attr_);
        os << ")";
    }

    template<
        typename Context,
        typename Expected,
        bool Integral = std::is_integral<Expected>{},
        int SizeofExpected = sizeof(Expected)>
    struct print_expected_impl
    {
        static void
        call(Context const & context, std::ostream & os, Expected expected)
        {
            print(os, resolve(context, expected));
        }
    };

    template<typename Context, typename Expected>
    struct print_expected_impl<Context, Expected, true, 4>
    {
        static void
        call(Context const & context, std::ostream & os, Expected expected)
        {
            std::array<uint32_t, 1> cps = {{(uint32_t)expected}};
            auto const r = text::make_from_utf32_range(cps);
            for (auto c : r) {
                os << c;
            }
        }
    };

    template<typename Context, typename Expected>
    void print_expected(
        Context const & context, std::ostream & os, Expected expected)
    {
        print_expected_impl<Context, Expected>::call(context, os, expected);
    }

    template<typename Context, typename T>
    struct char_parser_name_impl
    {
        static void call(Context const & context, std::ostream & os, T expected)
        {
            os << "char_(";
            print_expected(context, os, expected);
            os << ")";
        }
    };

    template<typename Context, typename T, typename U>
    struct char_parser_name_impl<Context, char_pair<T, U>>
    {
        static void call(
            Context const & context,
            std::ostream & os,
            char_pair<T, U> expected)
        {
            os << "char_(";
            print_expected(context, os, expected.lo_);
            os << ", ";
            print_expected(context, os, expected.hi_);
            os << ")";
        }
    };

    template<typename Context, typename Range>
    struct char_parser_name_impl<Context, char_range<Range>>
    {
        static void call(
            Context const & context,
            std::ostream & os,
            char_range<Range> expected)
        {
            os << "char_(";
            for (auto c : expected.chars_) {
                print_expected(context, os, c);
            }
            os << ")";
        }
    };

    template<typename Context, typename Expected>
    void parser_name(
        Context const & context,
        char_parser<Expected> const & parser,
        std::ostream & os,
        int components)
    {
        char_parser_name_impl<Context, Expected>::call(
            context, os, parser.expected_);
    }

    template<typename Context>
    void parser_name(
        Context const & context,
        char_parser<nope> const & parser,
        std::ostream & os,
        int components)
    {
        os << "char_";
    }

    template<typename Context, typename Expected>
    void parser_name(
        Context const & context,
        omit_parser<char_parser<Expected>> const & parser,
        std::ostream & os,
        int components)
    {
        parser_name(context, parser.parser_, os, components);
    }

    template<typename Context, typename Expected>
    void parser_name(
        Context const & context,
        char_parser<Expected, uint32_t> const & parser,
        std::ostream & os,
        int components)
    {
        os << "cp(";
        print(os, parser.expected_);
        os << ")";
    }

    template<typename Context>
    void parser_name(
        Context const & context,
        char_parser<nope, uint32_t> const & parser,
        std::ostream & os,
        int components)
    {
        os << "cp";
    }

    template<typename Context>
    void parser_name(
        Context const & context,
        string_parser const & parser,
        std::ostream & os,
        int components)
    {
        os << "string(\"" << parser.expected_ << "\")";
    }

    template<typename Context>
    void parser_name(
        Context const & context,
        omit_parser<string_parser> const & parser,
        std::ostream & os,
        int components)
    {
        os << "\"";
        print(os, parser.parser_.expected_);
        os << "\"";
    }

    template<typename Context>
    void parser_name(
        Context const & context,
        eol_parser const & parser,
        std::ostream & os,
        int components)
    {
        os << "eol";
    }

    template<typename Context>
    void parser_name(
        Context const & context,
        bool_parser const & parser,
        std::ostream & os,
        int components)
    {
        os << "bool_";
    }

    template<
        typename Context,
        typename T,
        int Radix,
        int MinDigits,
        int MaxDigits,
        typename Expected>
    void parser_name(
        Context const & context,
        uint_parser<T, Radix, MinDigits, MaxDigits, Expected> const & parser,
        std::ostream & os,
        int components)
    {
        os << "uint<" << typeindex::type_id<T>().pretty_name() << ", " << Radix
           << ", " << MinDigits << ", " << MaxDigits << ">(";
        print(os, parser.expected_);
        os << ")";
    }

    template<
        typename Context,
        typename T,
        int Radix,
        int MinDigits,
        int MaxDigits>
    void parser_name(
        Context const & context,
        uint_parser<T, Radix, MinDigits, MaxDigits, nope> const & parser,
        std::ostream & os,
        int components)
    {
        os << "uint<" << typeindex::type_id<T>().pretty_name() << ", " << Radix
           << ", " << MinDigits << ", " << MaxDigits << ">";
    }

    template<typename Context>
    void parser_name(
        Context const & context,
        uint_parser<unsigned int, 2> const & parser,
        std::ostream & os,
        int components)
    {
        os << "bin";
    }

    template<typename Context>
    void parser_name(
        Context const & context,
        uint_parser<unsigned int, 8> const & parser,
        std::ostream & os,
        int components)
    {
        os << "oct";
    }

    template<typename Context>
    void parser_name(
        Context const & context,
        uint_parser<unsigned int, 16> const & parser,
        std::ostream & os,
        int components)
    {
        os << "hex";
    }

    template<typename Context>
    void parser_name(
        Context const & context,
        uint_parser<unsigned short> const & parser,
        std::ostream & os,
        int components)
    {
        os << "ushort_";
    }

    template<typename Context>
    void parser_name(
        Context const & context,
        uint_parser<unsigned int> const & parser,
        std::ostream & os,
        int components)
    {
        os << "uint_";
    }

    template<typename Context>
    void parser_name(
        Context const & context,
        uint_parser<unsigned long> const & parser,
        std::ostream & os,
        int components)
    {
        os << "ulong_";
    }

    template<typename Context>
    void parser_name(
        Context const & context,
        uint_parser<unsigned long long> const & parser,
        std::ostream & os,
        int components)
    {
        os << "ulong_long";
    }

    template<
        typename Context,
        typename T,
        int Radix,
        int MinDigits,
        int MaxDigits,
        typename Expected>
    void parser_name(
        Context const & context,
        int_parser<T, Radix, MinDigits, MaxDigits, Expected> const & parser,
        std::ostream & os,
        int components)
    {
        os << "int<" << typeindex::type_id<T>().pretty_name() << ", " << Radix
           << ", " << MinDigits << ", " << MaxDigits << ">(";
        print(os, parser.expected_);
        os << ")";
    }

    template<
        typename Context,
        typename T,
        int Radix,
        int MinDigits,
        int MaxDigits>
    void parser_name(
        Context const & context,
        int_parser<T, Radix, MinDigits, MaxDigits, nope> const & parser,
        std::ostream & os,
        int components)
    {
        os << "int<" << typeindex::type_id<T>().pretty_name() << ", " << Radix
           << ", " << MinDigits << ", " << MaxDigits << ">";
    }

    template<typename Context>
    void parser_name(
        Context const & context,
        int_parser<short> const & parser,
        std::ostream & os,
        int components)
    {
        os << "short_";
    }

    template<typename Context>
    void parser_name(
        Context const & context,
        int_parser<int> const & parser,
        std::ostream & os,
        int components)
    {
        os << "int_";
    }

    template<typename Context>
    void parser_name(
        Context const & context,
        int_parser<long> const & parser,
        std::ostream & os,
        int components)
    {
        os << "long_";
    }

    template<typename Context>
    void parser_name(
        Context const & context,
        int_parser<long long> const & parser,
        std::ostream & os,
        int components)
    {
        os << "long_long";
    }

    template<typename Context, typename T>
    void parser_name(
        Context const & context,
        float_parser<T> const & parser,
        std::ostream & os,
        int components)
    {
        os << "float<" << typeindex::type_id<T>().pretty_name() << ">";
    }

    template<typename Context>
    void parser_name(
        Context const & context,
        float_parser<float> const & parser,
        std::ostream & os,
        int components)
    {
        os << "float_";
    }

    template<typename Context>
    void parser_name(
        Context const & context,
        float_parser<double> const & parser,
        std::ostream & os,
        int components)
    {
        os << "double_";
    }

    template<typename Context, typename ParserTuple, typename BacktrackingTuple>
    void switch_parser_matchers(
        Context const & context,
        seq_parser<ParserTuple, BacktrackingTuple> const & parser,
        std::ostream & os,
        int components)
    {
        using namespace hana::literals;

        os << "(" << resolve(context, parser.parsers_[0_c].predicate_.value_)
           << ", ";
        parser_name(context, parser.parsers_[1_c], os, components);
        os << ")";
    }

    template<typename Context, typename ParserTuple>
    void switch_parser_matchers(
        Context const & context,
        or_parser<ParserTuple> const & parser,
        std::ostream & os,
        int components)
    {
        using namespace hana::literals;

        bool printed_ellipsis = false;
        hana::for_each(parser.parsers_, [&](auto const & parser) {
            if (components == parser_component_limit) {
                if (!printed_ellipsis)
                    os << "...";
                printed_ellipsis = true;
                return;
            }
            switch_parser_matchers(context, parser, os, components);
            ++components;
        });
    }

    template<typename Context, typename SwitchValue, typename OrParser>
    void parser_name(
        Context const & context,
        switch_parser<SwitchValue, OrParser> const & parser,
        std::ostream & os,
        int components)
    {
        os << "switch_(";
        print(os, resolve(context, parser.switch_value_));
        os << ")";
        switch_parser_matchers(context, parser.or_parser_, os, components);
    }

}}}

#endif
