#ifndef BOOST_PARSER_DETAIL_PRINTING_IMPL_HPP
#define BOOST_PARSER_DETAIL_PRINTING_IMPL_HPP

#include <boost/parser/detail/printing.hpp>

#if BOOST_PARSER_USE_BOOST
#include <boost/type_index.hpp>
#else
#include <typeinfo>
#endif


namespace boost { namespace parser { namespace detail {

    template<typename T>
    auto type_name()
    {
#if BOOST_PARSER_USE_BOOST
        return typeindex::type_id<T>().pretty_name();
#else
        return typeid(T).name();
#endif
    }

    template<typename Parser>
    struct n_aray_parser : std::false_type
    {};

    template<
        typename Parser,
        typename DelimiterParser,
        typename MinType,
        typename MaxType>
    struct n_aray_parser<
        repeat_parser<Parser, DelimiterParser, MinType, MaxType>>
        : std::true_type
    {};

    template<typename Parser, typename MinType, typename MaxType>
    struct n_aray_parser<repeat_parser<Parser, detail::nope, MinType, MaxType>>
        : std::false_type
    {};

    template<typename Parser, typename DelimiterParser>
    struct n_aray_parser<delimited_seq_parser<Parser, DelimiterParser>>
        : std::true_type
    {};

    template<typename ParserTuple>
    struct n_aray_parser<or_parser<ParserTuple>> : std::true_type
    {};

    template<typename ParserTuple, typename BacktrackingTuple>
    struct n_aray_parser<seq_parser<ParserTuple, BacktrackingTuple>>
        : std::true_type
    {};

    // true iff Parser is an n-ary parser (contains N>2 subparsers).
    template<typename Parser>
    constexpr bool n_aray_parser_v = n_aray_parser<Parser>::value;

    template<typename Context, typename Expected>
    void print_expected(
        Context const & context,
        std::ostream & os,
        Expected expected,
        bool no_parens = false)
    {
        if (is_nope_v<Expected>)
            return;
        if (!no_parens)
            os << "(";
        detail::print(os, detail::resolve(context, expected));
        if (!no_parens)
            os << ")";
    }

    template<
        typename Context,
        typename Parser,
        typename DelimiterParser,
        typename MinType,
        typename MaxType>
    void print_parser(
        Context const & context,
        repeat_parser<Parser, DelimiterParser, MinType, MaxType> const & parser,
        std::ostream & os,
        int components)
    {
        if constexpr (is_nope_v<DelimiterParser>) {
            auto const min_ = detail::resolve(context, parser.min_);
            auto const max_ = detail::resolve(context, parser.max_);
            constexpr bool n_ary_child = n_aray_parser_v<Parser>;
            if (min_ == 0 && max_ == Inf) {
                os << "*";
                if (n_ary_child)
                    os << "(";
                detail::print_parser(
                    context, parser.parser_, os, components + 1);
                if (n_ary_child)
                    os << ")";
            } else if (min_ == 1 && max_ == Inf) {
                os << "+";
                if (n_ary_child)
                    os << "(";
                detail::print_parser(
                    context, parser.parser_, os, components + 1);
                if (n_ary_child)
                    os << ")";
            } else {
                os << "repeat(";
                detail::print(os, min_);
                if (min_ == max_) {
                    os << ")[";
                } else {
                    os << ", ";
                    if (max_ == unbounded)
                        os << "Inf";
                    else
                        detail::print(os, max_);
                    os << ")[";
                }
                detail::print_parser(
                    context, parser.parser_, os, components + 1);
                os << "]";
            }
        } else {
            detail::print_parser(context, parser.parser_, os, components + 1);
            os << " % ";
            detail::print_parser(
                context, parser.delimiter_parser_, os, components + 2);
        }
    }

    template<typename Context, typename Parser>
    void print_parser(
        Context const & context,
        opt_parser<Parser> const & parser,
        std::ostream & os,
        int components)
    {
        os << "-";
        constexpr bool n_ary_child = n_aray_parser_v<Parser>;
        if (n_ary_child)
            os << "(";
        detail::print_parser(context, parser.parser_, os, components + 1);
        if (n_ary_child)
            os << ")";
    }

    template<typename Context, typename ParserTuple>
    void print_parser(
        Context const & context,
        or_parser<ParserTuple> const & parser,
        std::ostream & os,
        int components)
    {
        int i = 0;
        bool printed_ellipsis = false;
        hl::for_each(parser.parsers_, [&](auto const & parser) {
            if (components == parser_component_limit) {
                if (!printed_ellipsis)
                    os << " | ...";
                printed_ellipsis = true;
                return;
            }
            if (i)
                os << " | ";
            detail::print_parser(context, parser, os, components);
            ++components;
            ++i;
        });
    }

    template<typename Context, typename ParserTuple, typename BacktrackingTuple>
    void print_parser(
        Context const & context,
        seq_parser<ParserTuple, BacktrackingTuple> const & parser,
        std::ostream & os,
        int components)
    {
        int i = 0;
        bool printed_ellipsis = false;
        hl::for_each(
            hl::zip(parser.parsers_, BacktrackingTuple{}),
            [&](auto const & parser_and_backtrack) {
                using namespace literals;
                auto const & parser = parser::get(parser_and_backtrack, 0_c);
                auto const backtrack = parser::get(parser_and_backtrack, 1_c);

                if (components == parser_component_limit) {
                    if (!printed_ellipsis)
                        os << (backtrack ? " >> ..." : " > ...");
                    printed_ellipsis = true;
                    return;
                }
                if (i)
                    os << (backtrack ? " >> " : " > ");
                detail::print_parser(context, parser, os, components);
                ++components;
                ++i;
            });
    }

    template<typename Context, typename Parser, typename Action>
    void print_parser(
        Context const & context,
        action_parser<Parser, Action> const & parser,
        std::ostream & os,
        int components)
    {
        detail::print_parser(context, parser.parser_, os, components);
        os << "[<<action>>]";
    }

    template<typename Context, typename Parser>
    void print_directive(
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
            detail::print_parser(context, parser, os, components + 1);
        os << "]";
    }

    template<typename Context, typename Parser>
    void print_parser(
        Context const & context,
        omit_parser<Parser> const & parser,
        std::ostream & os,
        int components)
    {
        detail::print_directive(
            context, "omit", parser.parser_, os, components);
    }

    template<typename Context, typename Parser>
    void print_parser(
        Context const & context,
        raw_parser<Parser> const & parser,
        std::ostream & os,
        int components)
    {
        detail::print_directive(context, "raw", parser.parser_, os, components);
    }

#if defined(BOOST_PARSER_DOXYGEN) || defined(__cpp_lib_concepts)
    template<typename Context, typename Parser>
    void print_parser(
        Context const & context,
        string_view_parser<Parser> const & parser,
        std::ostream & os,
        int components)
    {
        detail::print_directive(
            context, "string_view", parser.parser_, os, components);
    }
#endif

    template<typename Context, typename Parser, typename Transform>
    void print_parser(
        Context const & context,
        input_transform_parser<Parser, Transform> const & parser,
        std::ostream & os,
        int components)
    {
        detail::print_directive(
            context, "input_transform", parser.parser_, os, components);
    }

    template<typename Context, typename Parser>
    void print_parser(
        Context const & context,
        no_input_transform_parser<Parser> const & parser,
        std::ostream & os,
        int components)
    {
        detail::print_directive(
            context, "no_input_transform", parser.parser_, os, components);
    }

    template<typename Context, typename Parser>
    void print_parser(
        Context const & context,
        lower_case_parser<Parser> const & parser,
        std::ostream & os,
        int components)
    {
        detail::print_directive(
            context, "lower_case", parser.parser_, os, components);
    }

    template<typename Context, typename Parser>
    void print_parser(
        Context const & context,
        upper_case_parser<Parser> const & parser,
        std::ostream & os,
        int components)
    {
        detail::print_directive(
            context, "upper_case", parser.parser_, os, components);
    }

    template<typename Context, typename Parser>
    void print_parser(
        Context const & context,
        lexeme_parser<Parser> const & parser,
        std::ostream & os,
        int components)
    {
        detail::print_directive(
            context, "lexeme", parser.parser_, os, components);
    }

    template<typename Context, typename Parser, typename SkipParser>
    void print_parser(
        Context const & context,
        skip_parser<Parser, SkipParser> const & parser,
        std::ostream & os,
        int components)
    {
        if constexpr (is_nope_v<SkipParser>) {
            detail::print_directive(
                context, "skip", parser.parser_, os, components);
        } else {
            os << "skip(";
            detail::print_parser(
                context, parser.skip_parser_.parser_, os, components);
            os << ")";
            detail::print_directive(
                context, "", parser.parser_, os, components + 1);
        }
    }

    template<typename Context, typename Parser, bool FailOnMatch>
    void print_parser(
        Context const & context,
        expect_parser<Parser, FailOnMatch> const & parser,
        std::ostream & os,
        int components)
    {
        if (FailOnMatch)
            os << "!";
        else
            os << "&";
        constexpr bool n_ary_child = n_aray_parser_v<Parser>;
        if (n_ary_child)
            os << "(";
        detail::print_parser(context, parser.parser_, os, components + 1);
        if (n_ary_child)
            os << ")";
    }

    template<
        typename Context,
        bool UseCallbacks,
        typename Parser,
        typename Attribute,
        typename LocalState,
        typename ParamsTuple>
    void print_parser(
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
        os << parser.name_;
        if constexpr (!is_nope_v<ParamsTuple>) {
            os << ".with(";
            int i = 0;
            hl::for_each(parser.params_, [&](auto const & param) {
                if (i++)
                    os << ", ";
                detail::print_expected(context, os, param, true);
            });
            os << ")";
        }
    }

    template<typename Context, typename T>
    void print_parser(
        Context const & context,
        symbol_parser<T> const & parser,
        std::ostream & os,
        int components)
    {
        os << "symbols<" << detail::type_name<T>() << ">";
    }

    template<typename Context, typename Predicate>
    void print_parser(
        Context const & context,
        eps_parser<Predicate> const & parser,
        std::ostream & os,
        int components)
    {
        os << "eps(<<pred>>)";
    }

    template<typename Context>
    void print_parser(
        Context const & context,
        eps_parser<nope> const & parser,
        std::ostream & os,
        int components)
    {
        os << "eps";
    }

    template<typename Context>
    void print_parser(
        Context const & context,
        eoi_parser const & parser,
        std::ostream & os,
        int components)
    {
        os << "eoi";
    }

    template<typename Context, typename Atribute>
    void print_parser(
        Context const & context,
        attr_parser<Atribute> const & parser,
        std::ostream & os,
        int components)
    {
        os << "attr";
        detail::print_expected(context, os, parser.attr_);
    }

    template<
        typename Context,
        typename ResolvedExpected,
        bool Integral = std::is_integral<ResolvedExpected>{},
        int SizeofExpected = sizeof(ResolvedExpected)>
    struct print_expected_char_impl
    {
        static void call(
            Context const & context,
            std::ostream & os,
            ResolvedExpected expected)
        {
            detail::print(os, expected);
        }
    };

    template<typename Context, typename Expected>
    struct print_expected_char_impl<Context, Expected, true, 4>
    {
        static void
        call(Context const & context, std::ostream & os, Expected expected)
        {
            std::array<uint32_t, 1> cps = {{(uint32_t)expected}};
            auto const r = text::as_utf8(cps);
            os << "'";
            for (auto c : r) {
                detail::print_char(os, c);
            }
            os << "'";
        }
    };

    template<typename Context, typename Expected>
    void print_expected_char(
        Context const & context, std::ostream & os, Expected expected)
    {
        auto resolved_expected = detail::resolve(context, expected);
        detail::print_expected_char_impl<Context, decltype(resolved_expected)>::
            call(context, os, resolved_expected);
    }

    template<typename Context, typename T>
    struct char_print_parser_impl
    {
        static void call(Context const & context, std::ostream & os, T expected)
        {
            detail::print_expected_char(context, os, expected);
        }
    };

    template<typename Context, typename T, typename U>
    struct char_print_parser_impl<Context, char_pair<T, U>>
    {
        static void call(
            Context const & context,
            std::ostream & os,
            char_pair<T, U> expected)
        {
            detail::print_expected_char(context, os, expected.lo_);
            os << ", ";
            detail::print_expected_char(context, os, expected.hi_);
        }
    };

    template<typename Context, typename Iter, typename Sentinel>
    struct char_print_parser_impl<Context, char_range<Iter, Sentinel>>
    {
        static void call(
            Context const & context,
            std::ostream & os,
            char_range<Iter, Sentinel> expected)
        {
            os << "\"";
            auto const r = text::as_utf8(expected.chars_);
            for (auto c : r) {
                detail::print_char(os, c);
            }
            os << "\"";
        }
    };

    template<typename Context, typename Expected, typename AttributeType>
    void print_parser(
        Context const & context,
        char_parser<Expected, AttributeType> const & parser,
        std::ostream & os,
        int components)
    {
        if (std::is_same_v<
                Expected,
                ascii_char_class<ascii_char_class_t::alnum>>) {
            os << "ascii::alnum";
        } else if (std::is_same_v<
                       Expected,
                       ascii_char_class<ascii_char_class_t::alpha>>) {
            os << "ascii::alpha";
        } else if (std::is_same_v<
                       Expected,
                       ascii_char_class<ascii_char_class_t::blank>>) {
            os << "ascii::blank";
        } else if (std::is_same_v<
                       Expected,
                       ascii_char_class<ascii_char_class_t::cntrl>>) {
            os << "ascii::cntrl";
        } else if (std::is_same_v<
                       Expected,
                       ascii_char_class<ascii_char_class_t::digit>>) {
            os << "ascii::digit";
        } else if (std::is_same_v<
                       Expected,
                       ascii_char_class<ascii_char_class_t::graph>>) {
            os << "ascii::graph";
        } else if (std::is_same_v<
                       Expected,
                       ascii_char_class<ascii_char_class_t::print>>) {
            os << "ascii::print";
        } else if (std::is_same_v<
                       Expected,
                       ascii_char_class<ascii_char_class_t::punct>>) {
            os << "ascii::punct";
        } else if (std::is_same_v<
                       Expected,
                       ascii_char_class<ascii_char_class_t::space>>) {
            os << "ascii::space";
        } else if (std::is_same_v<
                       Expected,
                       ascii_char_class<ascii_char_class_t::xdigit>>) {
            os << "ascii::xdigit";
        } else if (std::is_same_v<
                       Expected,
                       ascii_char_class<ascii_char_class_t::lower>>) {
            os << "ascii::lower";
        } else if (std::is_same_v<
                       Expected,
                       ascii_char_class<ascii_char_class_t::upper>>) {
            os << "ascii::upper";
        } else {
            if (std::is_same_v<AttributeType, uint32_t>)
                os << "cp";
            else if (std::is_same_v<AttributeType, char>)
                os << "cu";
            else
                os << "char_";
            if constexpr (!is_nope_v<Expected>) {
                os << "(";
                char_print_parser_impl<Context, Expected>::call(
                    context, os, parser.expected_);
                os << ")";
            }
        }
    }

    template<typename Context, typename Expected, typename AttributeType>
    void print_parser(
        Context const & context,
        omit_parser<char_parser<Expected, AttributeType>> const & parser,
        std::ostream & os,
        int components)
    {
        if constexpr (is_nope_v<Expected>) {
            os << "omit[char_]";
        } else {
            char_print_parser_impl<Context, Expected>::call(
                context, os, parser.parser_.expected_);
        }
    }

    template<typename Context, typename StrIter, typename StrSentinel>
    void print_parser(
        Context const & context,
        string_parser<StrIter, StrSentinel> const & parser,
        std::ostream & os,
        int components)
    {
        os << "string(\"";
        for (auto c :
             text::as_utf8(parser.expected_first_, parser.expected_last_)) {
            detail::print_char(os, c);
        }
        os << "\")";
    }

    template<typename Context, typename StrIter, typename StrSentinel>
    void print_parser(
        Context const & context,
        omit_parser<string_parser<StrIter, StrSentinel>> const & parser,
        std::ostream & os,
        int components)
    {
        os << "\"";
        for (auto c : text::as_utf8(
                 parser.parser_.expected_first_,
                 parser.parser_.expected_last_)) {
            detail::print_char(os, c);
        }
        os << "\"";
    }

    template<typename Context>
    void print_parser(
        Context const & context,
        ws_parser<true> const & parser,
        std::ostream & os,
        int components)
    {
        os << "eol";
    }

    template<typename Context>
    void print_parser(
        Context const & context,
        ws_parser<false> const & parser,
        std::ostream & os,
        int components)
    {
        os << "ws";
    }

    template<typename Context>
    void print_parser(
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
    void print_parser(
        Context const & context,
        uint_parser<T, Radix, MinDigits, MaxDigits, Expected> const & parser,
        std::ostream & os,
        int components)
    {
        if (MinDigits == 1 && MaxDigits == -1) {
            if (std::is_same_v<T, unsigned short>) {
                os << "ushort_";
                detail::print_expected(context, os, parser.expected_);
                return;
            } else if (std::is_same_v<T, unsigned int>) {
                if (Radix == 2)
                    os << "bin";
                else if (Radix == 8)
                    os << "oct";
                else if (Radix == 16)
                    os << "hex";
                else if (Radix == 10)
                    os << "uint_";
                detail::print_expected(context, os, parser.expected_);
                return;
            } else if (Radix == 10 && std::is_same_v<T, unsigned long>) {
                os << "ulong_";
                detail::print_expected(context, os, parser.expected_);
                return;
            } else if (Radix == 10 && std::is_same_v<T, unsigned long long>) {
                os << "ulong_long";
                detail::print_expected(context, os, parser.expected_);
                return;
            }
        }
        os << "uint<" << detail::type_name<T>() << ", " << Radix << ", "
           << MinDigits << ", " << MaxDigits << ">";
        detail::print_expected(context, os, parser.expected_);
    }

    template<
        typename Context,
        typename T,
        int Radix,
        int MinDigits,
        int MaxDigits,
        typename Expected>
    void print_parser(
        Context const & context,
        int_parser<T, Radix, MinDigits, MaxDigits, Expected> const & parser,
        std::ostream & os,
        int components)
    {
        if (Radix == 10 && MinDigits == 1 && MaxDigits == -1) {
            if (std::is_same_v<T, short>) {
                os << "short_";
                detail::print_expected(context, os, parser.expected_);
                return;
            } else if (std::is_same_v<T, int>) {
                os << "int_";
                detail::print_expected(context, os, parser.expected_);
                return;
            } else if (std::is_same_v<T, long>) {
                os << "long_";
                detail::print_expected(context, os, parser.expected_);
                return;
            } else if (std::is_same_v<T, long long>) {
                os << "long_long";
                detail::print_expected(context, os, parser.expected_);
                return;
            }
        }
        os << "int<" << detail::type_name<T>() << ", " << Radix << ", "
           << MinDigits << ", " << MaxDigits << ">";
        detail::print_expected(context, os, parser.expected_);
    }

    template<typename Context>
    void print_parser(
        Context const & context,
        int_parser<short> const & parser,
        std::ostream & os,
        int components)
    {
        os << "short_";
    }

    template<typename Context>
    void print_parser(
        Context const & context,
        int_parser<long> const & parser,
        std::ostream & os,
        int components)
    {
        os << "long_";
    }

    template<typename Context>
    void print_parser(
        Context const & context,
        int_parser<long long> const & parser,
        std::ostream & os,
        int components)
    {
        os << "long_long";
    }

    template<typename Context, typename T>
    void print_parser(
        Context const & context,
        float_parser<T> const & parser,
        std::ostream & os,
        int components)
    {
        os << "float<" << detail::type_name<T>() << ">";
    }

    template<typename Context>
    void print_parser(
        Context const & context,
        float_parser<float> const & parser,
        std::ostream & os,
        int components)
    {
        os << "float_";
    }

    template<typename Context>
    void print_parser(
        Context const & context,
        float_parser<double> const & parser,
        std::ostream & os,
        int components)
    {
        os << "double_";
    }

    template<typename Context, typename ParserTuple, typename BacktrackingTuple>
    void print_switch_matchers(
        Context const & context,
        seq_parser<ParserTuple, BacktrackingTuple> const & parser,
        std::ostream & os,
        int components)
    {
        using namespace literals;

        os << "("
           << detail::resolve(
                  context, parser::get(parser.parsers_, 0_c).pred_.value_)
           << ", ";
        detail::print_parser(
            context, parser::get(parser.parsers_, 1_c), os, components);
        os << ")";
    }

    template<typename Context, typename ParserTuple>
    void print_switch_matchers(
        Context const & context,
        or_parser<ParserTuple> const & parser,
        std::ostream & os,
        int components)
    {
        using namespace literals;

        bool printed_ellipsis = false;
        hl::for_each(parser.parsers_, [&](auto const & parser) {
            if (components == parser_component_limit) {
                if (!printed_ellipsis)
                    os << "...";
                printed_ellipsis = true;
                return;
            }
            detail::print_switch_matchers(context, parser, os, components);
            ++components;
        });
    }

    template<typename Context, typename SwitchValue, typename OrParser>
    void print_parser(
        Context const & context,
        switch_parser<SwitchValue, OrParser> const & parser,
        std::ostream & os,
        int components)
    {
        os << "switch_(";
        detail::print(os, detail::resolve(context, parser.switch_value_));
        os << ")";
        detail::print_switch_matchers(
            context, parser.or_parser_, os, components);
    }

}}}

#endif
