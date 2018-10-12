#ifndef BOOST_PARSER_PARSER_HPP
#define BOOST_PARSER_PARSER_HPP

#include <boost/parser/parser_fwd.hpp>
#include <boost/parser/error_handling.hpp>
#include <boost/parser/detail/printing.hpp>

#include <boost/spirit/home/x3/numeric/real_policies.hpp>
#include <boost/spirit/home/x3/support/numeric_utils/extract_int.hpp>
#include <boost/spirit/home/x3/support/numeric_utils/extract_real.hpp>
#include <boost/variant.hpp>

#include <type_traits>
#include <vector>


namespace boost { namespace parser {

    template<typename Iter>
    struct range
    {
        using iterator = Iter;

        range() {}
        range(Iter first, Iter last) : first_(first), last_(last) {}

        iterator begin() const noexcept { return first_; }
        iterator end() const noexcept { return last_; }

        bool operator==(range rhs) const noexcept
        {
            return first_ == rhs.first_ && last_ == rhs.last_;
        }
        bool operator!=(range rhs) const noexcept { return !(*this == rhs); }

    private:
        Iter first_;
        Iter last_;
    };

    template<typename Iter>
    constexpr range<Iter> make_range(Iter first, Iter last) noexcept
    {
        return range<Iter>(first, last);
    }



    namespace detail {

        // Utility types.

        struct nope
        {
            // Assignable from anything.
            template<typename T>
            constexpr nope & operator=(T const &)
            {
                return *this;
            }

            // Convertible to optional.
            operator none_t() const noexcept { return none; }

            // Also acts as a dummy predicate.
            template<typename Context>
            constexpr bool operator()(Context const &) const noexcept
            {
                return true;
            }
        };
        constexpr bool operator==(nope, nope) { return true; }
        constexpr bool operator!=(nope, nope) { return false; }
        template<typename T>
        constexpr bool operator==(T, nope)
        {
            return false;
        }
        template<typename T>
        constexpr bool operator!=(T, nope)
        {
            return false;
        }

        inline nope global_nope;

        template<typename ErrorHandler>
        inline auto make_context(
            bool & success,
            int & indent,
            ErrorHandler const & error_handler) noexcept
        {
            return hana::make_map(
                hana::make_pair(hana::type_c<pass_tag>, &success),
                hana::make_pair(hana::type_c<val_tag>, global_nope),
                hana::make_pair(hana::type_c<attr_tag>, global_nope),
                hana::make_pair(hana::type_c<locals_tag>, global_nope),
                hana::make_pair(hana::type_c<trace_indent_tag>, &indent),
                hana::make_pair(
                    hana::type_c<error_handler_tag>, &error_handler));
        }

        template<typename Context>
        inline decltype(auto) _indent(Context const & context)
        {
            return *context[hana::type_c<trace_indent_tag>];
        }


        // Type traits.

        template<typename T>
        using begin_and_end =
            decltype(std::declval<T>().begin(), std::declval<T>().end());

        template<typename T, typename U>
        using range_t =
            typename std::enable_if<is_detected<begin_and_end, T>{}, U>::type;

        template<typename T, typename U>
        using non_range_t =
            typename std::enable_if<!is_detected<begin_and_end, T>{}, U>::type;

        template<typename T>
        using insert_range_insert_begin_and_end = decltype(
            std::declval<T>().insert(
                std::declval<T>().end(), *std::declval<T>().end()),
            std::declval<T>().insert(
                std::declval<T>().end(),
                std::declval<T>().begin(),
                std::declval<T>().end()));

        template<typename T>
        struct is_container : is_detected<insert_range_insert_begin_and_end, T>
        {
        };

        template<typename T, typename U>
        using insert_range_insert_begin_and_end_2 = decltype(
            std::declval<T>().insert(
                std::declval<T>().end(), std::declval<U>()),
            std::declval<T>().insert(
                std::declval<T>().end(),
                std::declval<T>().begin(),
                std::declval<T>().end()));

        template<typename T, typename U>
        struct is_container_and_insertable
            : is_detected<insert_range_insert_begin_and_end_2, T, U>
        {
        };

        template<typename T>
        struct is_hana_tuple : std::false_type
        {
        };

        template<typename... T>
        struct is_hana_tuple<hana::tuple<T...>> : std::true_type
        {
        };

        template<typename T>
        struct is_zero_plus_p : std::false_type
        {
        };
        template<typename T>
        struct is_zero_plus_p<zero_plus_parser<T>> : std::true_type
        {
        };

        template<typename T>
        struct is_or_p : std::false_type
        {
        };
        template<typename T>
        struct is_or_p<or_parser<T>> : std::true_type
        {
        };

        template<typename T>
        struct is_seq_p : std::false_type
        {
        };
        template<typename T, typename U>
        struct is_seq_p<seq_parser<T, U>> : std::true_type
        {
        };

        template<typename T>
        struct is_one_plus_p : std::false_type
        {
        };
        template<typename T>
        struct is_one_plus_p<one_plus_parser<T>> : std::true_type
        {
        };

        template<typename T>
        struct is_optional : std::false_type
        {
        };
        template<typename T>
        struct is_optional<optional<T>> : std::true_type
        {
        };

        template<typename T>
        struct is_variant : std::false_type
        {
        };
        template<typename... T>
        struct is_variant<variant<T...>> : std::true_type
        {
        };

        template<typename T, typename U>
        using move_assignable =
            decltype(std::declval<T &>() = std::declval<U>());
        template<typename T, typename U>
        struct is_move_assignable : is_detected<move_assignable, T, U>
        {
        };



        // Metafunctions.

        template<typename Pair>
        struct hana_tuple_to_or_type;

        template<typename... T>
        struct hana_tuple_to_or_type<
            hana::pair<hana::tuple<T...>, std::false_type>>
        {
            using type = variant<T...>;
        };

        template<typename T>
        struct hana_tuple_to_or_type<
            hana::pair<hana::tuple<T>, std::false_type>>
        {
            using type = T;
        };

        template<typename... T>
        struct hana_tuple_to_or_type<
            hana::pair<hana::tuple<T...>, std::true_type>>
        {
            using type = optional<variant<T...>>;
        };

        template<typename T>
        struct hana_tuple_to_or_type<hana::pair<hana::tuple<T>, std::true_type>>
        {
            using type = optional<T>;
        };

        template<typename T>
        struct hana_tuple_to_or_type<
            hana::pair<hana::tuple<optional<T>>, std::true_type>>
        {
            using type = optional<T>;
        };

        template<typename IsOptional>
        struct hana_tuple_to_or_type<hana::pair<hana::tuple<>, IsOptional>>
        {
            using type = nope;
        };

        template<typename T>
        using hana_tuple_to_or_type_t = typename hana_tuple_to_or_type<T>::type;

        template<typename T>
        struct sequence_of_impl
        {
            using type = std::vector<T>;
        };

        template<>
        struct sequence_of_impl<nope>
        {
            using type = nope;
        };

        template<typename T>
        using sequence_of = typename sequence_of_impl<T>::type;

        template<typename T>
        struct optional_of_impl
        {
            using type = optional<T>;
        };

        template<>
        struct optional_of_impl<nope>
        {
            using type = nope;
        };

        template<typename T>
        using optional_of = typename optional_of_impl<T>::type;

        template<typename T>
        struct unwrapped_optional
        {
            using type = T;
        };
        template<typename T>
        struct unwrapped_optional<optional<T>>
        {
            using type = T;
        };
        template<typename T>
        using unwrapped_optional_t = typename unwrapped_optional<T>::type;



        // Etc.

        struct unwrap
        {
            template<typename T>
            constexpr auto operator()(T wrapped_type) const
            {
                return typename decltype(wrapped_type)::type{};
            }
        };

        template<typename Container, typename T>
        void append(Container & c, T && x, bool gen_attrs)
        {
            if (gen_attrs)
                c.insert(c.end(), std::move(x));
        }

        inline void append(nope &, nope &&, bool gen_attrs) {}

        constexpr inline flags default_flags()
        {
            return flags(
                uint32_t(flags::gen_attrs) | uint32_t(flags::use_skip));
        }
        constexpr inline flags enable_skip(flags f)
        {
            return flags(uint32_t(f) | uint32_t(flags::use_skip));
        }
        constexpr inline flags disable_skip(flags f)
        {
            return flags(uint32_t(f) & ~uint32_t(flags::use_skip));
        }
        constexpr inline flags enable_attrs(flags f)
        {
            return flags(uint32_t(f) | uint32_t(flags::gen_attrs));
        }
        constexpr inline flags disable_attrs(flags f)
        {
            return flags(uint32_t(f) & ~uint32_t(flags::gen_attrs));
        }
        constexpr inline flags enable_trace(flags f)
        {
            return flags(uint32_t(f) | uint32_t(flags::trace));
        }
        constexpr inline bool gen_attrs(flags f)
        {
            return (uint32_t(f) & uint32_t(flags::gen_attrs)) ==
                   uint32_t(flags::gen_attrs);
        }
        constexpr inline bool use_skip(flags f)
        {
            return (uint32_t(f) & uint32_t(flags::use_skip)) ==
                   uint32_t(flags::use_skip);
        }

        struct null_parser
        {};

        struct skip_skipper
        {
            template<typename Iter, typename Context, typename SkipParser>
            detail::nope call(
                Iter & first,
                Iter last,
                Context const & context,
                SkipParser const & skip,
                detail::flags flags,
                bool & success) const noexcept
            {
                return {};
            }

            template<
                typename Iter,
                typename Context,
                typename SkipParser,
                typename Attribute>
            void call(
                Iter & first,
                Iter last,
                Context const & context,
                SkipParser const & skip,
                detail::flags flags,
                bool & success,
                Attribute & retval) const
            {}
        };

        template<typename Iter>
        void skip(Iter & first, Iter last, null_parser const & skip_, flags f)
        {}

        template<typename Iter, typename SkipParser>
        void skip(Iter & first, Iter last, SkipParser const & skip_, flags f)
        {
            if (!use_skip(f))
                return;
            bool success = true;
            int indent = 0;
            rethrow_error_handler eh;
            auto const context = make_context(success, indent, eh);
            while (success) {
                skip_(
                    first,
                    last,
                    context,
                    skip_skipper{},
                    disable_skip(f),
                    success);
            }
        }

        enum : int64_t { unbounded = -1 };

        template<typename T>
        optional<T> make_parse_result(T & x, bool success)
        {
            optional<T> retval;
            if (success)
                retval = std::move(x);
            return retval;
        }

        inline bool make_parse_result(nope &, bool success) { return success; }

        template<typename T>
        struct char_pair
        {
            template<typename T2>
            friend bool operator!=(T2 c, char_pair<T> const & chars)
            {
                return c < chars.lo_ || chars.hi_ < c;
            }

            T lo_;
            T hi_;
        };

        template<typename Range>
        struct char_range
        {
            template<typename RangeIter>
            char_range(RangeIter first, RangeIter last) : chars_(first, last)
            {}

            template<typename T>
            friend bool operator!=(T c, char_range<Range> const & chars)
            {
                return std::find(chars.chars_.begin(), chars.chars_.end(), c) ==
                       chars.chars_.end();
            }

            range<std::decay_t<decltype(std::declval<Range>().begin())>> chars_;
        };

        enum class ascii_char_class_t {
            alnum,
            alpha,
            blank,
            cntrl,
            digit,
            graph,
            print,
            punct,
            space,
            xdigit,
            lower,
            upper
        };

        template<ascii_char_class_t CharClass>
        struct ascii_char_class
        {
            template<typename T>
            friend bool operator!=(T c, ascii_char_class<CharClass> const &)
            {
                switch (CharClass) {
                case ascii_char_class_t::alnum: return !std::isalnum(c);
                case ascii_char_class_t::alpha: return !std::isalpha(c);
                case ascii_char_class_t::blank: return !std::isblank(c);
                case ascii_char_class_t::cntrl: return !std::iscntrl(c);
                case ascii_char_class_t::digit: return !std::isdigit(c);
                case ascii_char_class_t::graph: return !std::isgraph(c);
                case ascii_char_class_t::print: return !std::isprint(c);
                case ascii_char_class_t::punct: return !std::ispunct(c);
                case ascii_char_class_t::space: return !std::isspace(c);
                case ascii_char_class_t::xdigit: return !std::isxdigit(c);
                case ascii_char_class_t::lower: return !std::islower(c);
                case ascii_char_class_t::upper: return !std::isupper(c);
                }
                return true;
            }
        };

        template<typename Container, typename T>
        constexpr void move_back(Container & c, T && x)
        {
            c.insert(c.end(), std::move(x));
        }

        template<typename Container, typename T>
        constexpr void move_back(Container & c, optional<T> & x)
        {
            if (x)
                c.insert(c.end(), std::move(*x));
        }

        template<typename Container, typename T>
        constexpr void move_back(Container & c, optional<T> && x)
        {
            if (x)
                c.insert(c.end(), std::move(*x));
        }

        template<typename Container>
        constexpr void move_back(Container &, nope)
        {}

        template<typename T, typename U>
        constexpr void assign(T & t, U && u)
        {
            t = std::move(u);
        }

        template<typename T>
        constexpr void assign(T &, nope)
        {}
    }



    template<typename T>
    constexpr hana::type<T> tag{};

    inline constexpr auto val_ = tag<detail::val_tag>;
    inline constexpr auto attr_ = tag<detail::attr_tag>;
    inline constexpr auto where_ = tag<detail::where_tag>;
    inline constexpr auto pass_ = tag<detail::pass_tag>;
    inline constexpr auto locals_ = tag<detail::locals_tag>;
    inline constexpr auto error_handler_ = tag<detail::error_handler_tag>;

    template<typename Context>
    inline decltype(auto) _val(Context const & context)
    {
        return *context[val_];
    }
    template<typename Context>
    inline decltype(auto) _attr(Context const & context)
    {
        return *context[attr_];
    }
    template<typename Context>
    inline decltype(auto) _where(Context const & context)
    {
        return *context[where_];
    }
    template<typename Context>
    inline decltype(auto) _pass(Context const & context)
    {
        return *context[pass_];
    }
    template<typename Context>
    inline decltype(auto) _locals(Context const & context)
    {
        return *context[locals_];
    }
    template<typename Context>
    inline decltype(auto) _error_handler(Context const & context)
    {
        return *context[error_handler_];
    }



    // TODO: no_skip[]?

    // TODO: symbol table parser.


    // TODO: All the parsers are constexpr.  Figure out how to use them for
    // compile-time parsing.



    // Second order parsers.


    int64_t const Inf = detail::unbounded;

    template<typename Parser, typename DelimiterParser>
    struct repeat_parser
    {
        constexpr repeat_parser(
            Parser parser,
            int64_t _min,
            int64_t _max,
            DelimiterParser delimiter_parser = DelimiterParser{}) :
            parser_(parser),
            delimiter_parser_(delimiter_parser),
            min_(_min),
            max_(_max)
        {}

        template<typename Iter, typename Context, typename SkipParser>
        auto call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            using attr_t = decltype(
                parser_.call(first, last, context, skip, flags, success));
            if constexpr (detail::is_container<attr_t>{}) {
                attr_t retval;
                call(first, last, context, skip, flags, success, retval);
                return retval;
            } else {
                detail::sequence_of<attr_t> retval;
                call(first, last, context, skip, flags, success, retval);
                return retval;
            }
        }

        template<
            typename Iter,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = scoped_trace(*this, first, last, context, flags, retval);

            using attr_t = decltype(
                parser_.call(first, last, context, skip, flags, success));
            if constexpr (detail::is_variant<Attribute>{}) {
                using attr_t =
                    decltype(call(first, last, context, skip, flags, success));
                attr_t attr;
                call(first, last, context, skip, flags, success, attr);
                detail::assign(retval, std::move(attr));
            } else if constexpr (detail::is_container<attr_t>{}) {
                int64_t count = 0;

                for (; count != min_; ++count) {
                    detail::skip(first, last, skip, flags);
                    parser_.call(
                        first, last, context, skip, flags, success, retval);
                    if (!success) {
                        retval = Attribute();
                        return;
                    }
                }

                for (; count != max_; ++count) {
                    auto const prev_first = first;
                    // This is only ever used in delimited_parser, which
                    // always has a min=1; we therefore know we're after a
                    // previous element when this executes.
                    if constexpr (!std::is_same<
                                      DelimiterParser,
                                      detail::nope>{}) {
                        detail::skip(first, last, skip, flags);
                        delimiter_parser_.call(
                            first,
                            last,
                            context,
                            skip,
                            detail::disable_attrs(flags),
                            success);
                        if (!success) {
                            success = true;
                            break;
                        }
                    }

                    detail::skip(first, last, skip, flags);
                    parser_.call(
                        first, last, context, skip, flags, success, retval);
                    if (!success) {
                        success = true;
                        first = prev_first;
                        break;
                    }
                }
            } else {
                attr_t attr;
                int64_t count = 0;

                for (; count != min_; ++count) {
                    detail::skip(first, last, skip, flags);
                    if (gen_attrs(flags)) {
                        attr = parser_.call(
                            first, last, context, skip, flags, success);
                    } else {
                        parser_.call(
                            first, last, context, skip, flags, success);
                    }
                    if (!success) {
                        retval = Attribute();
                        return;
                    }
                    detail::append(retval, std::move(attr), gen_attrs(flags));
                }

                for (; count != max_; ++count) {
                    auto const prev_first = first;
                    if constexpr (!std::is_same<
                                      DelimiterParser,
                                      detail::nope>{}) {
                        detail::skip(first, last, skip, flags);
                        delimiter_parser_.call(
                            first,
                            last,
                            context,
                            skip,
                            detail::disable_attrs(flags),
                            success);
                        if (!success) {
                            success = true;
                            break;
                        }
                    }

                    detail::skip(first, last, skip, flags);
                    if (gen_attrs(flags)) {
                        attr = parser_.call(
                            first, last, context, skip, flags, success);
                    } else {
                        parser_.call(
                            first, last, context, skip, flags, success);
                    }
                    if (!success) {
                        success = true;
                        first = prev_first;
                        break;
                    }
                    detail::append(retval, std::move(attr), gen_attrs(flags));
                }
            }
        }

        Parser parser_;
        DelimiterParser delimiter_parser_;
        int64_t min_;
        int64_t max_;
    };

    template<typename Parser>
    struct zero_plus_parser : repeat_parser<Parser>
    {
        constexpr zero_plus_parser(Parser parser) :
            repeat_parser<Parser>(parser, 0, Inf)
        {}
    };

    template<typename Parser>
    struct one_plus_parser : repeat_parser<Parser>
    {
        constexpr one_plus_parser(Parser parser) :
            repeat_parser<Parser>(parser, 1, Inf)
        {}
    };

    template<typename Parser, typename DelimiterParser>
    struct delimited_seq_parser : repeat_parser<Parser, DelimiterParser>
    {
        constexpr delimited_seq_parser(
            Parser parser, DelimiterParser delimiter_parser) :
            repeat_parser<Parser, DelimiterParser>(
                parser, 1, Inf, delimiter_parser)
        {}
    };

    template<typename Parser>
    struct opt_parser
    {
        template<typename Iter, typename Context, typename SkipParser>
        auto call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            using attr_t = decltype(
                parser_.call(first, last, context, skip, flags, success));
            detail::optional_of<attr_t> retval;
            call(first, last, context, skip, flags, success, retval);
            return retval;
        }

        template<
            typename Iter,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = scoped_trace(*this, first, last, context, flags, retval);

            detail::skip(first, last, skip, flags);

            if (!gen_attrs(flags)) {
                parser_.call(first, last, context, skip, flags, success);
                return;
            }

            if constexpr (detail::is_variant<Attribute>{}) {
                using attr_t =
                    decltype(call(first, last, context, skip, flags, success));
                typename attr_t::value_type attr;
                call(first, last, context, skip, flags, success, attr);
                detail::assign(retval, attr_t(std::move(attr)));
            } else {
                parser_.call(
                    first, last, context, skip, flags, success, retval);
            }
        }

        Parser parser_;
    };

    template<typename ParserTuple>
    struct or_parser
    {
        constexpr or_parser(ParserTuple parsers) : parsers_(parsers) {}

        // This more-verbose form (a lambda would have been easier!) prevents
        // a Clang 6 ICE.
        template<typename Iter, typename Context, typename SkipParser>
        struct use_parser_t
        {
            use_parser_t(
                Iter & first,
                Iter last,
                Context const & context,
                SkipParser const & skip,
                detail::flags flags,
                bool & success) :
                first_(first),
                last_(last),
                context_(context),
                skip_(skip),
                flags_(flags),
                success_(success)
            {}

            template<typename Parser>
            auto operator()(Parser const & parser) const
            {
                detail::skip(first_, last_, skip_, flags_);
                success_ = true; // In case someone earlier already failed...
                return parser.call(
                    first_, last_, context_, skip_, flags_, success_);
            }

            template<typename Parser, typename Attribute>
            void operator()(Parser const & parser, Attribute & retval) const
            {
                detail::skip(first_, last_, skip_, flags_);
                success_ = true; // In case someone earlier already failed...

                if constexpr (detail::is_optional<Attribute>{}) {
                    using retval_inner_type = typename Attribute::value_type;
                    retval_inner_type retval_inner;
                    parser.call(
                        first_,
                        last_,
                        context_,
                        skip_,
                        flags_,
                        success_,
                        retval_inner);
                    detail::assign(retval, retval_inner);
                } else if constexpr (detail::is_variant<Attribute>{}) {
                    using attr_t = decltype(parser.call(
                        first_, last_, context_, skip_, flags_, success_));
                    attr_t attr;
                    parser.call(
                        first_, last_, context_, skip_, flags_, success_, attr);
                    detail::assign(retval, std::move(attr));
                } else {
                    parser.call(
                        first_,
                        last_,
                        context_,
                        skip_,
                        flags_,
                        success_,
                        retval);
                }
            }

            Iter & first_;
            Iter last_;
            Context const & context_;
            SkipParser const & skip_;
            detail::flags flags_;
            bool & success_;
        };

        template<typename Iter, typename Context, typename SkipParser>
        auto call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            use_parser_t<Iter, Context, SkipParser> const use_parser(
                first, last, context, skip, flags, success);

            // A result type for each of the parsers in parsers_.
            using all_types = decltype(hana::transform(parsers_, use_parser));

            // Same as above, wrapped in hana::basic_type.
            using all_types_wrapped =
                decltype(hana::transform(all_types{}, hana::make_type));

            // Returns a hana::pair<> containing two things: 1) A tuple of only
            // the unique wrapped types from above, without nopes; this may be
            // empty. 2) std::true_type or std::false_type indicating whether
            // nopes were found; if so, the final result is an optional.
            auto append_unique = [](auto result, auto x) {
                using x_type = typename decltype(x)::type;
                if constexpr (std::is_same<x_type, detail::nope>{}) {
                    return hana::make_pair(
                        hana::first(result), std::true_type{});
                } else if constexpr (hana::contains(hana::first(result), x)) {
                    return result;
                } else {
                    return hana::make_pair(
                        hana::append(hana::first(result), x),
                        hana::second(result));
                }
            };
            using wrapped_unique_types = decltype(hana::fold_left(
                all_types_wrapped{},
                hana::make_pair(hana::tuple<>{}, std::false_type{}),
                append_unique));

            // Same as above, with the tuple types unwrapped.
            using unwrapped_types = decltype(hana::make_pair(
                hana::transform(
                    hana::first(wrapped_unique_types{}), detail::unwrap{}),
                hana::second(wrapped_unique_types{})));

            // Types above converted to a "variant", which may actually be a
            // non-variant type T if that is the only unique non-nope type, or a
            // nope if unwrapped_types is empty.
            using result_t = detail::hana_tuple_to_or_type_t<unwrapped_types>;

            result_t retval;
            call(first, last, context, skip, flags, success, retval);
            return retval;
        }

        template<
            typename Iter,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = scoped_trace(*this, first, last, context, flags, retval);

            use_parser_t<Iter, Context, SkipParser> const use_parser(
                first, last, context, skip, flags, success);

            bool done = false;
            auto try_parser = [use_parser, &success, flags, &retval, &done](
                                  auto const & parser) {
                if (done)
                    return;
                if (gen_attrs(flags)) {
                    use_parser(parser, retval);
                    if (!success)
                        retval = Attribute();
                } else {
                    use_parser(parser);
                }
                if (success)
                    done = true;
            };
            hana::for_each(parsers_, try_parser);
        }

        template<typename Parser>
        constexpr auto prepend(Parser parser) const noexcept;
        template<typename Parser>
        constexpr auto append(Parser parser) const noexcept;

        ParserTuple parsers_;
    };

    template<typename ParserTuple, typename BacktrackingTuple>
    struct seq_parser
    {
        using backtracking = BacktrackingTuple;

        constexpr seq_parser(ParserTuple parsers) : parsers_(parsers) {}

        template<typename Iter, typename Context, typename SkipParser>
        struct dummy_use_parser_t
        {
            dummy_use_parser_t(
                Iter & first,
                Iter last,
                Context const & context,
                SkipParser const & skip,
                detail::flags flags,
                bool & success) :
                first_(first),
                last_(last),
                context_(context),
                skip_(skip),
                flags_(flags),
                success_(success)
            {}
            template<typename Parser>
            auto operator()(Parser const & parser) const
            {
                return parser.call(
                    first_, last_, context_, skip_, flags_, success_);
            }
            Iter & first_;
            Iter last_;
            Context const & context_;
            SkipParser const & skip_;
            detail::flags flags_;
            bool & success_;
        };

        struct combine
        {
            template<typename T, typename U>
            auto operator()(T result_and_indices, U x) const
            {
                auto result = hana::first(result_and_indices);
                using result_back_type =
                    typename std::decay_t<decltype(hana::back(result))>::type;
                using unwrapped_optional_result_back_type =
                    detail::unwrapped_optional_t<result_back_type>;

                auto indices = hana::second(result_and_indices);

                using x_type = typename decltype(x)::type;
                using unwrapped_optional_x_type =
                    detail::unwrapped_optional_t<x_type>;

                constexpr auto one = hana::size_c<1>;
                (void)one;

                if constexpr (std::is_same<x_type, detail::nope>{}) {
                    // T >> nope -> T
                    return hana::make_pair(
                        result,
                        hana::append(indices, hana::size(result) - one));
                } else if constexpr (std::is_same<result_back_type, x_type>{}) {
                    if constexpr (detail::is_container<x_type>{}) {
                        // C<T> >> C<T> -> C<T>
                        return hana::make_pair(
                            result,
                            hana::append(indices, hana::size(result) - one));
                    } else {
                        // T >> T -> vector<T>
                        return hana::make_pair(
                            hana::append(
                                hana::drop_back(result),
                                hana::type_c<std::vector<x_type>>),
                            hana::append(indices, hana::size(result) - one));
                    }
                } else if constexpr (
                    detail::is_container_and_insertable<
                        result_back_type,
                        x_type>{} ||
                    detail::is_container_and_insertable<
                        result_back_type,
                        unwrapped_optional_x_type>{}) {
                    // C<T> >> T -> C<T>
                    // C<T> >> optional<T> -> C<T>
                    return hana::make_pair(
                        result,
                        hana::append(indices, hana::size(result) - one));
                } else if constexpr (
                    detail::is_container_and_insertable<
                        x_type,
                        result_back_type>{} ||
                    detail::is_container_and_insertable<
                        x_type,
                        unwrapped_optional_result_back_type>{}) {
                    // T >> C<T> -> C<T>
                    // optional<T> >> C<T> -> C<T>
                    return hana::make_pair(
                        hana::append(hana::drop_back(result), x),
                        hana::append(indices, hana::size(result) - one));
                } else if constexpr (std::is_same<
                                         result_back_type,
                                         detail::nope>{}) {
                    // hana::tuple<nope> >> T -> hana::tuple<T>
                    return hana::make_pair(
                        hana::append(hana::drop_back(result), x),
                        hana::append(indices, hana::size(result) - one));
                } else {
                    // hana::tuple<Ts...> >> T -> hana::tuple<Ts..., T>
                    return hana::make_pair(
                        hana::append(result, x),
                        hana::append(indices, hana::size(result)));
                }
            }
        };

        // Returns the tuple of values produced by this parser, and the
        // indices into that tuple that each parser should use in turn.  The
        // case where the tuple only has one element is handled elsewhere.
        template<typename Iter, typename Context, typename SkipParser>
        auto make_temp_result(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
#if 0 // GCC chokes on this less verbose form.
            auto dummy_use_parser =
                [&first, last, &context, flags, &success](auto const & parser)
                -> decltype(
                    parser.call(first, last, context, skip, flags, success)) {
                return parser.call(first, last, context, skip, flags, success);
            };
#else
            dummy_use_parser_t<Iter, Context, SkipParser> const
                dummy_use_parser(first, last, context, skip, flags, success);
#endif

            // A result type for each of the parsers in parsers_.
            using all_types =
                decltype(hana::transform(parsers_, dummy_use_parser));

            // Same as above, wrapped in hana::basic_type.
            using all_types_wrapped =
                decltype(hana::transform(all_types{}, hana::make_type));

            // Generate a tuple of outputs, and the index that each parser
            // should use to write into its output.
            constexpr auto combine_start = hana::make_pair(
                hana::make_tuple(hana::front(all_types_wrapped{})),
                hana::tuple_c<std::size_t, 0>);
            using combined_types = decltype(hana::fold_left(
                hana::drop_front(all_types_wrapped{}),
                combine_start,
                combine{}));

            // Unwrap the result tuple's types.
            using result_type = decltype(hana::transform(
                hana::first(combined_types{}), detail::unwrap{}));

            return hana::make_pair(
                result_type(), hana::second(combined_types{}));
        }

        template<typename Iter, typename Context, typename SkipParser>
        auto call(
            Iter & first_,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            Iter first = first_;

            std::decay_t<decltype(hana::first(
                make_temp_result(first, last, context, skip, flags, success)))>
                retval;

            auto _ = scoped_trace(*this, first_, last, context, flags, retval);

            std::decay_t<decltype(hana::second(
                make_temp_result(first, last, context, skip, flags, success)))>
                indices;
            call_impl(
                first, last, context, skip, flags, success, retval, indices);

            if (success)
                first_ = first;

            // A 1-tuple is converted to a scalar.
            if constexpr (hana::size(retval) == hana::size_c<1>) {
                using namespace hana::literals;
                return retval[0_c];
            } else {
                return retval;
            }
        }

        template<
            typename Iter,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            Iter & first_,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = scoped_trace(*this, first_, last, context, flags, retval);

            Iter first = first_;

            std::decay_t<decltype(hana::second(
                make_temp_result(first, last, context, skip, flags, success)))>
                indices;
            if constexpr (detail::is_hana_tuple<Attribute>{}) {
                call_impl(
                    first,
                    last,
                    context,
                    skip,
                    flags,
                    success,
                    retval,
                    indices);

                if (!success || !gen_attrs(flags))
                    retval = Attribute();
            } else {
                // call_impl requires a tuple, so we must wrap this scalar.
                hana::tuple<Attribute> temp_retval;
                call_impl(
                    first,
                    last,
                    context,
                    skip,
                    flags,
                    success,
                    temp_retval,
                    indices);

                if (success && gen_attrs(flags))
                    retval = hana::front(std::move(temp_retval));
            }

            if (success)
                first_ = first;
        }

        // Invokes each parser, placing the resulting values (if any) into
        // retval, using the index mapping in indices.  The case of a tulple
        // containing only a single value is handled elsewhere.
        template<
            typename Iter,
            typename Context,
            typename SkipParser,
            typename Attribute,
            typename Indices>
        void call_impl(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval,
            Indices const & indices) const
        {
            static_assert(detail::is_hana_tuple<Attribute>{}, "");

            auto use_parser = [&first,
                               last,
                               &context,
                               &skip,
                               flags,
                               &success,
                               &retval](
                                  auto const & parser_index_and_backtrack) {
                using namespace hana::literals;
                detail::skip(first, last, skip, flags);
                if (!success) // Someone earlier already failed...
                    return;

                auto const & parser = parser_index_and_backtrack[0_c];
                bool const can_backtrack = parser_index_and_backtrack[2_c];

                if (!gen_attrs(flags)) {
                    parser.call(first, last, context, skip, flags, success);
                    if (!success && !can_backtrack) {
                        std::string name;
                        detail::parser_name(parser, name);
                        throw parse_error<Iter>(first, name);
                    }
                    return;
                }

                auto & out = retval[parser_index_and_backtrack[1_c]];

                using attr_t = decltype(
                    parser.call(first, last, context, skip, flags, success));
                constexpr bool out_container =
                    detail::is_container<std::decay_t<decltype(out)>>{};
                constexpr bool attr_container = detail::is_container<attr_t>{};

                if constexpr (out_container == attr_container) {
                    // TODO: Document that the user can pass anything she
                    // likes for retval, but that if retval is not a
                    // container, but the default retval would have been,
                    // weird assignments may occur.  For instance,
                    // parse(first, last, char_ >> char_, a), where 'a' is
                    // a boost::any, will only yeild a single char in the
                    // any.
                    parser.call(
                        first, last, context, skip, flags, success, out);
                    if (!success) {
                        if (!can_backtrack) {
                            std::string name;
                            detail::parser_name(parser, name);
                            throw parse_error<Iter>(first, name);
                        }
                        out = std::decay_t<decltype(out)>();
                        return;
                    }
                } else {
                    attr_t x =
                        parser.call(first, last, context, skip, flags, success);
                    if (!success) {
                        if (!can_backtrack) {
                            std::string name;
                            detail::parser_name(parser, name);
                            throw parse_error<Iter>(first, name);
                        }
                        return;
                    }
                    if constexpr (out_container)
                        detail::move_back(out, x);
                    else
                        detail::assign(out, x);
                }
            };

            auto const parsers_and_indices =
                hana::zip(parsers_, indices, backtracking{});
            hana::for_each(parsers_and_indices, use_parser);
        }

        template<bool AllowBacktracking, typename Parser>
        constexpr auto prepend(Parser parser) const noexcept;
        template<bool AllowBacktracking, typename Parser>
        constexpr auto append(Parser parser) const noexcept;

        ParserTuple parsers_; // This should be (parser, can-backtrack) pairs.
    };

    // Wraps a parser, applying a semantic action to it.
    template<typename Parser, typename Action>
    struct action_parser
    {
        template<typename Iter, typename Context, typename SkipParser>
        detail::nope call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            detail::nope retval;
            call(first, last, context, skip, flags, success, retval);
            return retval;
        }

        template<
            typename Iter,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = scoped_trace(*this, first, last, context, flags, retval);

            auto const initial_first = first;
            auto attr = parser_.call(
                first,
                last,
                context,
                skip,
                detail::enable_attrs(flags),
                success);
            range const where(initial_first, first);
            if (success) {
                // Replace the context's current attribute with attr, and add
                // where to the context.
                auto const action_context = hana::insert(
                    hana::insert(
                        hana::erase_key(context, attr_),
                        hana::make_pair(attr_, &attr)),
                    hana::make_pair(where_, &where));
                action_(action_context);
            }
        }

        Parser parser_;
        Action action_;
    };

    template<typename Parser>
    struct omit_parser
    {
        template<typename Iter, typename Context, typename SkipParser>
        detail::nope call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            auto _ = scoped_trace(
                *this, first, last, context, flags, detail::global_nope);

            parser_.call(
                first,
                last,
                context,
                skip,
                detail::disable_attrs(flags),
                success);
            return {};
        }

        template<
            typename Iter,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = scoped_trace(*this, first, last, context, flags, retval);

            parser_.call(
                first,
                last,
                context,
                skip,
                detail::disable_attrs(flags),
                success);
        }

        Parser parser_;
    };

    template<typename Parser>
    struct raw_parser
    {
        template<typename Iter, typename Context, typename SkipParser>
        range<Iter> call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            range<Iter> retval;
            call(
                first,
                last,
                context,
                skip,
                detail::disable_attrs(flags),
                success,
                retval);
            return retval;
        }

        template<
            typename Iter,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = scoped_trace(*this, first, last, context, flags, retval);

            auto const initial_first = first;
            parser_.call(
                first,
                last,
                context,
                skip,
                detail::disable_attrs(flags),
                success);
            retval = range<Iter>(initial_first, first);
        }

        Parser parser_;
    };

    template<typename Parser>
    struct lexeme_parser
    {
        template<typename Iter, typename Context, typename SkipParser>
        auto call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            using attr_t = decltype(
                parser_.call(first, last, context, skip, flags, success));
            attr_t retval;
            call(
                first,
                last,
                context,
                skip,
                detail::disable_skip(flags),
                success,
                retval);
            return retval;
        }

        template<
            typename Iter,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = scoped_trace(*this, first, last, context, flags, retval);

            parser_.call(
                first,
                last,
                context,
                skip,
                detail::disable_skip(flags),
                success,
                retval);
        }

        Parser parser_;
    };

    template<typename Parser, typename SkipParser>
    struct skip_parser
    {
        template<typename Iter, typename Context, typename SkipParser_>
        auto call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser_ const & skip,
            detail::flags flags,
            bool & success) const
        {
            using attr_t = decltype(
                parser_.call(first, last, context, skip, flags, success));
            attr_t retval;
            call(
                first,
                last,
                context,
                skip,
                detail::enable_skip(flags),
                success,
                retval);
            return retval;
        }

        template<
            typename Iter,
            typename Context,
            typename SkipParser_,
            typename Attribute>
        void call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser_ const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            if constexpr (std::is_same<SkipParser, detail::nope>{}) {
                parser_.call(
                    first,
                    last,
                    context,
                    skip,
                    detail::enable_skip(flags),
                    success,
                    retval);
            } else {
                parser_.call(
                    first,
                    last,
                    context,
                    skip_parser_,
                    detail::enable_skip(flags),
                    success,
                    retval);
            }
        }

        Parser parser_;
        SkipParser skip_parser_;
    };

    template<typename Parser, bool FailOnMatch>
    struct expect_parser
    {
        template<typename Iter, typename Context, typename SkipParser>
        detail::nope call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            detail::nope retval;
            call(
                first,
                last,
                context,
                skip,
                detail::disable_attrs(flags),
                success,
                retval);
            return retval;
        }

        template<
            typename Iter,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = scoped_trace(*this, first, last, context, flags, retval);

            parser_.call(
                first,
                last,
                context,
                skip,
                detail::disable_attrs(flags),
                success);
            if (FailOnMatch)
                success = !success;
        }

        Parser parser_;
    };

    // TODO: Consider making this parser go through a tag-dispatched function
    // call instead of storing its parser.
    template<typename Parser, typename Attribute, typename LocalState>
    struct rule_parser
    {
        using attr_type = Attribute;
        using locals_type = LocalState;

        template<typename Iter, typename Context, typename SkipParser>
        auto call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            if constexpr (std::is_same<attr_type, detail::nope>{}) {
                using attr_t = decltype(
                    parser_.call(first, last, context, skip, flags, success));
                attr_t retval;
                call(first, last, context, skip, flags, success, retval);
                return retval;
            } else {
                attr_type retval;
                call(first, last, context, skip, flags, success, retval);
                return retval;
            }
        }

        template<
            typename Iter,
            typename Context,
            typename SkipParser,
            typename Attribute_>
        void call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute_ & retval) const
        {
            auto _ = scoped_trace(*this, first, last, context, flags, retval);

            if constexpr (std::is_same<locals_type, detail::nope>{}) {
                parser_.call(
                    first, last, context, skip, flags, success, retval);
            } else {
                locals_type locals;
                // Replace the context's current locals with these, and its
                // current val with retval.
                auto const action_context = hana::insert(
                    hana::insert(
                        hana::erase_key(
                            hana::erase_key(context, locals_), val_),
                        hana::make_pair(locals_, &locals)),
                    hana::make_pair(val_, &retval));
                parser_.call(
                    first, last, context, skip, flags, success, retval);
            }
        }

        Parser parser_;
        std::string_view name_;
    };



    // Parser interface.

    template<typename Parser>
    struct parser_interface
    {
        constexpr parser_interface() {}
        constexpr parser_interface(Parser parser) : parser_(parser) {}

        template<typename Attribute, typename LocalState>
        constexpr auto
        make_rule(std::string_view name = std::string_view()) const noexcept
        {
            using rule_t = rule_parser<Parser, Attribute, LocalState>;
            return parser_interface<rule_t>{rule_t{parser_, name}};
        }

        constexpr auto operator!() const noexcept
        {
            return parser_interface<expect_parser<Parser, true>>{
                expect_parser<Parser, true>{parser_}};
        }
        constexpr auto operator&() const noexcept
        {
            return parser_interface<expect_parser<Parser, false>>{
                expect_parser<Parser, false>{parser_}};
        }
        constexpr auto operator*() const noexcept
        {
            if constexpr (detail::is_zero_plus_p<Parser>{}) {
                return *this;
            } else if constexpr (detail::is_one_plus_p<Parser>{}) {
                using inner_parser = decltype(Parser::parser_);
                return parser_interface<zero_plus_parser<inner_parser>>{
                    zero_plus_parser<inner_parser>(parser_.parser_)};
            } else {
                return parser_interface<zero_plus_parser<Parser>>{
                    zero_plus_parser<Parser>(parser_)};
            }
        }
        constexpr auto operator+() const noexcept
        {
            if constexpr (detail::is_zero_plus_p<Parser>{}) {
                using inner_parser = decltype(Parser::parser_);
                return parser_interface<zero_plus_parser<inner_parser>>{
                    zero_plus_parser<inner_parser>(parser_.parser_)};
            } else if constexpr (detail::is_one_plus_p<Parser>{}) {
                return *this;
            } else {
                return parser_interface<one_plus_parser<Parser>>{
                    one_plus_parser<Parser>(parser_)};
            }
        }
        constexpr auto operator-() const noexcept
        {
            return parser_interface<opt_parser<Parser>>{
                opt_parser<Parser>{parser_}};
        }

        template<typename Parser2>
        constexpr auto operator>>(parser_interface<Parser2> rhs) const noexcept
        {
            if constexpr (detail::is_seq_p<Parser>{}) {
                return parser_.template append<true>(rhs.parser_);
            } else {
                using parser_t = seq_parser<
                    hana::tuple<Parser, Parser2>,
                    hana::tuple<hana::true_, hana::true_>>;
                return parser_interface<parser_t>{parser_t{
                    hana::tuple<Parser, Parser2>{parser_, rhs.parser_}}};
            }
        }

        constexpr auto operator>>(char rhs) const noexcept;
        constexpr auto operator>>(char32_t rhs) const noexcept;
        constexpr auto operator>>(std::string_view rhs) const noexcept;

        template<typename Parser2>
        constexpr auto operator>(parser_interface<Parser2> rhs) const noexcept
        {
            if constexpr (detail::is_seq_p<Parser>{}) {
                return parser_.template append<false>(rhs.parser_);
            } else {
                using parser_t = seq_parser<
                    hana::tuple<Parser, Parser2>,
                    hana::tuple<hana::true_, hana::false_>>;
                return parser_interface<parser_t>{parser_t{
                    hana::tuple<Parser, Parser2>{parser_, rhs.parser_}}};
            }
        }
        constexpr auto operator>(char rhs) const noexcept;
        constexpr auto operator>(char32_t rhs) const noexcept;
        constexpr auto operator>(std::string_view rhs) const noexcept;

        template<typename Parser2>
        constexpr auto operator|(parser_interface<Parser2> rhs) const noexcept
        {
            if constexpr (detail::is_or_p<Parser>{}) {
                return parser_.append(rhs.parser_);
            } else {
                return parser_interface<
                    or_parser<hana::tuple<Parser, Parser2>>>{
                    or_parser<hana::tuple<Parser, Parser2>>{
                        hana::tuple<Parser, Parser2>{parser_, rhs.parser_}}};
            }
        }

        constexpr auto operator|(char rhs) const noexcept;
        constexpr auto operator|(char32_t rhs) const noexcept;
        constexpr auto operator|(std::string_view rhs) const noexcept;

        template<typename Parser2>
        constexpr auto operator-(parser_interface<Parser2> rhs) const noexcept
        {
            return *this >> !rhs;
        }

        constexpr auto operator-(char rhs) const noexcept;
        constexpr auto operator-(char32_t rhs) const noexcept;
        constexpr auto operator-(std::string_view rhs) const noexcept;

        template<typename Parser2>
        constexpr auto operator%(parser_interface<Parser2> rhs) const noexcept
        {
            return parser_interface<delimited_seq_parser<Parser, Parser2>>{
                delimited_seq_parser<Parser, Parser2>(parser_, rhs.parser_)};
        }

        constexpr auto operator%(char rhs) const noexcept;
        constexpr auto operator%(char32_t rhs) const noexcept;
        constexpr auto operator%(std::string_view rhs) const noexcept;

        template<typename Action>
        constexpr auto operator[](Action action)
        {
            using action_parser_t = action_parser<Parser, Action>;
            return parser_interface<action_parser_t>{
                action_parser_t{parser_, action}};
        }

        // For parsers that can be used like "char_('x')".
        template<typename T>
        constexpr auto operator()(T && x) const noexcept
            -> decltype(std::declval<Parser>()(static_cast<T &&>(x)))
        {
            return parser_(static_cast<T &&>(x));
        }

        // For parsers that can be used like "char_('x', 'y')".
        template<typename T, typename U>
        constexpr auto operator()(T && x, U && y) const noexcept -> decltype(
            std::declval<Parser>()(static_cast<T &&>(x), static_cast<T &&>(y)))
        {
            return parser_(static_cast<T &&>(x), static_cast<T &&>(y));
        }

        template<typename Iter, typename Context, typename SkipParser>
        auto operator()(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            return parser_.call(first, last, context, skip, flags, success);
        }

        template<
            typename Iter,
            typename Context,
            typename SkipParser,
            typename Attribute>
        auto operator()(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & attr) const
        {
            return parser_.call(
                first, last, context, skip, flags, success, attr);
        }

        Parser parser_;
    };

    template<typename ParserTuple>
    template<typename Parser>
    constexpr auto or_parser<ParserTuple>::prepend(Parser parser) const noexcept
    {
        return parser_interface<
            or_parser<decltype(hana::prepend(parsers_, parser))>>{
            or_parser<decltype(hana::prepend(parsers_, parser))>{
                hana::prepend(parsers_, parser)}};
    }

    template<typename ParserTuple>
    template<typename Parser>
    constexpr auto or_parser<ParserTuple>::append(Parser parser) const noexcept
    {
        return parser_interface<
            or_parser<decltype(hana::append(parsers_, parser))>>{
            or_parser<decltype(hana::append(parsers_, parser))>{
                hana::append(parsers_, parser)}};
    }

    template<typename ParserTuple, typename BacktrackingTuple>
    template<bool AllowBacktracking, typename Parser>
    constexpr auto
    seq_parser<ParserTuple, BacktrackingTuple>::prepend(Parser parser) const
        noexcept
    {
        using backtracking = decltype(hana::prepend(
            hana::prepend(
                hana::drop_front(backtracking{}),
                hana::bool_c<AllowBacktracking>),
            hana::true_c));
        using parser_t =
            seq_parser<decltype(hana::prepend(parsers_, parser)), backtracking>;
        return parser_interface<parser_t>{
            parser_t{hana::prepend(parsers_, parser)}};
    }

    template<typename ParserTuple, typename BacktrackingTuple>
    template<bool AllowBacktracking, typename Parser>
    constexpr auto
    seq_parser<ParserTuple, BacktrackingTuple>::append(Parser parser) const
        noexcept
    {
        using backtracking = decltype(
            hana::append(backtracking{}, hana::bool_c<AllowBacktracking>));
        using parser_t =
            seq_parser<decltype(hana::append(parsers_, parser)), backtracking>;
        return parser_interface<parser_t>{
            parser_t{hana::append(parsers_, parser)}};
    }



    // Diretives.

    template<template<class> class Parser>
    struct directive
    {
        template<typename Parser2>
        constexpr auto operator[](parser_interface<Parser2> rhs) const noexcept
        {
            return parser_interface<Parser<Parser2>>{
                Parser<Parser2>{rhs.parser_}};
        }
    };

    inline constexpr directive<omit_parser> omit;
    inline constexpr directive<raw_parser> raw;
    inline constexpr directive<lexeme_parser> lexeme;

    struct repeat_directive
    {
        template<typename Parser2>
        constexpr auto operator[](parser_interface<Parser2> rhs) const noexcept
        {
            return parser_interface<repeat_parser<Parser2>>{
                repeat_parser<Parser2>{rhs.parser_, min_, max_}};
        }

        int64_t min_;
        int64_t max_;
    };

    inline constexpr repeat_directive repeat(int64_t n) noexcept
    {
        return repeat_directive{n, n};
    }

    inline constexpr repeat_directive
    repeat(int64_t min_, int64_t max_) noexcept
    {
        assert(max_ == Inf || min_ < max_);
        return repeat_directive{min_, max_};
    }

    template<typename SkipParser = detail::nope>
    struct skip_directive
    {
        template<typename Parser>
        constexpr auto operator[](parser_interface<Parser> rhs) const noexcept
        {
            return parser_interface<skip_parser<Parser, SkipParser>>{
                skip_parser<Parser, SkipParser>{rhs.parser_, skip_parser_}};
        }

        template<typename SkipParser2>
        constexpr auto operator()(SkipParser2 skip_parser) const noexcept
        {
            static_assert(
                std::is_same<SkipParser, detail::nope>{},
                "If you're seeing this, you tried to chain calls on skip, "
                "like 'skip(foo)(bar).  Quit it!'");
            return skip_directive<SkipParser2>{skip_parser};
        }

        SkipParser skip_parser_;
    };

    inline constexpr skip_directive<> skip;



    // First order parsers.

    template<typename Predicate>
    struct eps_parser
    {
        template<typename Iter, typename Context, typename SkipParser>
        detail::nope call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const noexcept
        {
            auto _ = scoped_trace(
                *this, first, last, context, flags, detail::global_nope);
            success = predicate_(context);
            return {};
        }

        template<
            typename Iter,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = scoped_trace(*this, first, last, context, flags, retval);
            success = predicate_(context);
        }

        template<typename Predicate2>
        constexpr auto operator()(Predicate2 predicate) const noexcept
        {
            static_assert(
                std::is_same<Predicate, detail::nope>{},
                "If you're seeing this, you tried to chain calls on eps, "
                "like 'eps(foo)(bar).  Quit it!'");
            return parser_interface<eps_parser<Predicate2>>{
                eps_parser<Predicate2>{std::move(predicate)}};
        }

        Predicate predicate_;
    };

    inline constexpr parser_interface<eps_parser<detail::nope>> eps;

    struct eoi_parser
    {
        template<typename Iter, typename Context, typename SkipParser>
        detail::nope call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            auto _ = scoped_trace(
                *this, first, last, context, flags, detail::global_nope);
            if (first != last)
                success = false;
            return {};
        }

        template<
            typename Iter,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = scoped_trace(*this, first, last, context, flags, retval);
            if (first != last)
                success = false;
        }
    };

    inline constexpr parser_interface<eoi_parser> eoi;

    template<typename Attribute>
    struct attr_parser
    {
        template<typename Iter, typename Context, typename SkipParser>
        auto call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const &,
            detail::flags flags,
            bool &) const
        {
            auto _ = scoped_trace(
                *this, first, last, context, flags, detail::global_nope);
            return attr_;
        }

        template<
            typename Iter,
            typename Context,
            typename SkipParser,
            typename Attribute_>
        void call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute_ & retval) const
        {
            auto _ = scoped_trace(*this, first, last, context, flags, retval);
            if (gen_attrs(flags))
                retval = attr_;
        }

        Attribute attr_;
    };

    template<typename Attribute>
    inline constexpr auto attr(Attribute a) noexcept
    {
        return parser_interface<attr_parser<Attribute>>{
            attr_parser<Attribute>{std::move(a)}};
    }

    template<typename Expected>
    struct char_parser
    {
        constexpr char_parser() {}
        constexpr char_parser(Expected expected) : expected_(expected) {}

        template<typename Iter, typename Context, typename SkipParser>
        auto call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const -> std::decay_t<decltype(*first)>
        {
            std::decay_t<decltype(*first)> retval;
            call(first, last, context, skip, flags, success, retval);
            return retval;
        }

        template<
            typename Iter,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = scoped_trace(*this, first, last, context, flags, retval);

            if (first == last) {
                success = false;
                return;
            }
            auto x = *first;
            if (x != expected_) {
                success = false;
                return;
            }
            retval = std::move(x);
            ++first;
        }

        template<typename T>
        constexpr detail::non_range_t<T, parser_interface<char_parser<T>>>
        operator()(T x) const noexcept
        {
            static_assert(
                std::is_same<Expected, detail::nope>{},
                "If you're seeing this, you tried to chain calls on char_, "
                "like 'char_('a')('b').  Quit it!'");
            return parser_interface<char_parser<T>>{
                char_parser<T>{std::move(x)}};
        }

        // TODO: Document this conversion to string_view.
        auto operator()(char const * s) const noexcept
        {
            static_assert(
                std::is_same<Expected, detail::nope>{},
                "If you're seeing this, you tried to chain calls on char_, "
                "like 'char_(\"chars\")(\"chars\").  Quit it!'");
            std::string_view const range(s);
            using char_range_t = detail::char_range<std::string_view>;
            using char_parser_t = char_parser<char_range_t>;
            return parser_interface<char_parser_t>(
                char_parser_t(char_range_t(range.begin(), range.end())));
        }

        template<typename T>
        constexpr auto operator()(T lo, T hi) const noexcept
        {
            static_assert(
                std::is_same<Expected, detail::nope>{},
                "If you're seeing this, you tried to chain calls on char_, "
                "like 'char_('a', 'b')('c', 'd').  Quit it!'");
            return parser_interface<char_parser<detail::char_pair<T>>>(
                char_parser<detail::char_pair<T>>(
                    detail::char_pair<T>{std::move(lo), std::move(hi)}));
        }

        template<typename Range>
        constexpr auto
        operator()(Range const & r) const noexcept -> detail::range_t<
            Range,
            parser_interface<char_parser<
                detail::char_range<decltype(make_range(r.begin(), r.end()))>>>>
        {
            static_assert(
                std::is_same<Expected, detail::nope>{},
                "If you're seeing this, you tried to chain calls on char_, "
                "like 'char_(char-set)(char-set).  Quit it!'");
            auto range = make_range(r.begin(), r.end());
            using char_range_t = detail::char_range<decltype(range)>;
            using char_parser_t = char_parser<char_range_t>;
            return parser_interface<char_parser_t>(
                char_parser_t(char_range_t(range.begin(), range.end())));
        }

        Expected expected_;
    };

    inline constexpr parser_interface<char_parser<detail::nope>> char_;

    inline constexpr auto lit(char c) noexcept { return omit[char_(c)]; }

    inline constexpr auto lit(char32_t c) noexcept { return omit[char_(c)]; }

    struct string_parser
    {
        constexpr string_parser() {}
        constexpr string_parser(std::string_view expected) :
            expected_(std::move(expected))
        {}

        template<typename Iter, typename Context, typename SkipParser>
        std::string call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            std::string retval;
            call(first, last, context, skip, flags, success, retval);
            return retval;
        }

        template<
            typename Iter,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = scoped_trace(*this, first, last, context, flags, retval);

            if (first == last) {
                success = false;
                return;
            }

            // TODO: Automagically treat expected_ as UTF-8 and transcode for
            // this comparison if is_integral<decltype(*first)> &&
            // sizeof(*first) == 4.

            // TODO: The analogous same thing should happen in char_ when
            // comparing a char32_t expected value to a [first, last) sequence
            // of char.

            auto const mismatch =
                std::mismatch(first, last, expected_.begin(), expected_.end());
            if (mismatch.second != expected_.end()) {
                success = false;
                return;
            }

            first = mismatch.first;

            if (gen_attrs(flags))
                retval.insert(retval.end(), expected_.begin(), expected_.end());
        }

        std::string_view expected_;
    };

    inline constexpr auto string(std::string_view str) noexcept
    {
        return parser_interface<string_parser>{string_parser{str}};
    }

    inline constexpr auto lit(std::string_view str) noexcept
    {
        return omit[string(str)];
    }

    struct eol_parser
    {
        constexpr eol_parser() {}

        template<typename Iter, typename Context, typename SkipParser>
        detail::nope call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            detail::nope nope;
            call(first, last, context, skip, flags, success, nope);
            return {};
        }

        template<
            typename Iter,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = scoped_trace(*this, first, last, context, flags, retval);

            if (first == last) {
                success = false;
                return;
            }
            auto x = *first;
            if ((x & detail::eol_cp_mask) == x &&
                std::find(detail::eol_cps.begin(), detail::eol_cps.end(), x) ==
                    detail::eol_cps.end()) {
                success = false;
                return;
            }
            ++first;
            if (x == 0x000d && first != last && *first == 0x000a)
                ++first;
        }
    };

    inline constexpr parser_interface<eol_parser> eol;

    namespace ascii {

        inline constexpr parser_interface<char_parser<
            detail::ascii_char_class<detail::ascii_char_class_t::alnum>>>
            alnum;

        inline constexpr parser_interface<char_parser<
            detail::ascii_char_class<detail::ascii_char_class_t::alpha>>>
            alpha;

        inline constexpr parser_interface<char_parser<
            detail::ascii_char_class<detail::ascii_char_class_t::blank>>>
            blank;

        inline constexpr parser_interface<char_parser<
            detail::ascii_char_class<detail::ascii_char_class_t::cntrl>>>
            cntrl;

        inline constexpr parser_interface<char_parser<
            detail::ascii_char_class<detail::ascii_char_class_t::digit>>>
            digit;

        inline constexpr parser_interface<char_parser<
            detail::ascii_char_class<detail::ascii_char_class_t::graph>>>
            graph;

        inline constexpr parser_interface<char_parser<
            detail::ascii_char_class<detail::ascii_char_class_t::print>>>
            print;

        inline constexpr parser_interface<char_parser<
            detail::ascii_char_class<detail::ascii_char_class_t::punct>>>
            punct;

        inline constexpr parser_interface<char_parser<
            detail::ascii_char_class<detail::ascii_char_class_t::space>>>
            space;

        inline constexpr parser_interface<char_parser<
            detail::ascii_char_class<detail::ascii_char_class_t::xdigit>>>
            xdigit;

        inline constexpr parser_interface<char_parser<
            detail::ascii_char_class<detail::ascii_char_class_t::lower>>>
            lower;

        inline constexpr parser_interface<char_parser<
            detail::ascii_char_class<detail::ascii_char_class_t::upper>>>
            upper;
    }

    template<
        typename T,
        int Radix = 10,
        int MinDigits = 1,
        int MaxDigits = -1,
        typename Expected = detail::nope>
    struct uint_parser
    {
        static_assert(
            Radix == 2 || Radix == 8 || Radix == 10 || Radix == 16,
            "Unsupported radix.");

        constexpr uint_parser() {}

        template<typename Iter, typename Context, typename SkipParser>
        T call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            T retval;
            call(first, last, context, skip, flags, success, retval);
            return {};
        }

        template<
            typename Iter,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = scoped_trace(*this, first, last, context, flags, retval);
            using extract =
                spirit::x3::extract_uint<T, Radix, MinDigits, MaxDigits>;
            T attr = 0;
            success = extract::call(first, last, attr);
            if (attr != expected_)
                success = false;
            if (success)
                retval = attr;
        }

        constexpr auto operator()(T x) const noexcept
        {
            static_assert(
                std::is_same<Expected, detail::nope>{},
                "If you're seeing this, you tried to chain calls on this "
                "parser, like 'uint_(2)(3).  Quit it!'");
            using parser_t = uint_parser<T, Radix, MinDigits, MaxDigits, T>;
            return parser_interface<parser_t>{parser_t{x}};
        }

        Expected expected_;
    };

    inline constexpr parser_interface<uint_parser<unsigned int, 2>> bin;
    inline constexpr parser_interface<uint_parser<unsigned int, 8>> oct;
    inline constexpr parser_interface<uint_parser<unsigned int, 16>> hex;

    inline constexpr parser_interface<uint_parser<unsigned short>> ushort_;
    inline constexpr parser_interface<uint_parser<unsigned int>> uint_;
    inline constexpr parser_interface<uint_parser<unsigned long>> ulong_;
    inline constexpr parser_interface<uint_parser<unsigned long long>>
        ulong_long;

    template<
        typename T,
        int Radix = 10,
        int MinDigits = 1,
        int MaxDigits = -1,
        typename Expected = detail::nope>
    struct int_parser
    {
        constexpr int_parser() {}

        template<typename Iter, typename Context, typename SkipParser>
        T call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            T retval;
            call(first, last, context, skip, flags, success, retval);
            return {};
        }

        template<
            typename Iter,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = scoped_trace(*this, first, last, context, flags, retval);
            using extract =
                spirit::x3::extract_int<T, Radix, MinDigits, MaxDigits>;
            T attr = 0;
            success = extract::call(first, last, attr);
            if (attr != expected_)
                success = false;
            if (success)
                retval = attr;
        }

        constexpr auto operator()(T x) const noexcept
        {
            static_assert(
                std::is_same<Expected, detail::nope>{},
                "If you're seeing this, you tried to chain calls on this "
                "parser, like 'int_(2)(3).  Quit it!'");
            using parser_t = int_parser<T, Radix, MinDigits, MaxDigits, T>;
            return parser_interface<parser_t>{parser_t{x}};
        }

        Expected expected_;
    };

    inline constexpr parser_interface<int_parser<short>> short_;
    inline constexpr parser_interface<int_parser<int>> int_;
    inline constexpr parser_interface<int_parser<long>> long_;
    inline constexpr parser_interface<int_parser<long long>> long_long;

    template<typename T>
    struct float_parser
    {
        constexpr float_parser() {}

        template<typename Iter, typename Context, typename SkipParser>
        T call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            T retval;
            call(first, last, context, skip, flags, success, retval);
            return {};
        }

        template<
            typename Iter,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            Iter & first,
            Iter last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = scoped_trace(*this, first, last, context, flags, retval);
            spirit::x3::real_policies<T> policies;
            using extract =
                spirit::x3::extract_real<T, spirit::x3::real_policies<T>>;
            T attr = 0;
            if (extract::parse(first, last, attr, policies))
                retval = attr;
        }
    };

    inline constexpr parser_interface<float_parser<float>> float_;
    inline constexpr parser_interface<float_parser<double>> double_;

    template<typename Parser>
    constexpr auto parser_interface<Parser>::operator>>(char rhs) const noexcept
    {
        if constexpr (detail::is_seq_p<Parser>{}) {
            return parser_.append<true>(lit(rhs));
        } else {
            return *this >> lit(rhs);
        }
    }

    template<typename Parser>
    constexpr auto parser_interface<Parser>::operator>>(char32_t rhs) const
        noexcept
    {
        if constexpr (detail::is_seq_p<Parser>{}) {
            return parser_.append<true>(lit(rhs));
        } else {
            return *this >> lit(rhs);
        }
    }

    template<typename Parser>
    constexpr auto parser_interface<Parser>::
    operator>>(std::string_view rhs) const noexcept
    {
        if constexpr (detail::is_seq_p<Parser>{}) {
            return parser_.append<true>(lit(rhs));
        } else {
            return *this >> lit(rhs);
        }
    }

    template<typename Parser>
    constexpr auto operator>>(char c, parser_interface<Parser> rhs) noexcept
    {
        if constexpr (detail::is_seq_p<Parser>{}) {
            return rhs.parser_.prepend<true>(lit(c));
        } else {
            return lit(c) >> rhs;
        }
    }

    template<typename Parser>
    constexpr auto operator>>(char32_t c, parser_interface<Parser> rhs) noexcept
    {
        if constexpr (detail::is_seq_p<Parser>{}) {
            return rhs.parser_.prepend<true>(lit(c));
        } else {
            return lit(c) >> rhs;
        }
    }

    template<typename Parser>
    constexpr auto
    operator>>(std::string_view str, parser_interface<Parser> rhs) noexcept
    {
        if constexpr (detail::is_seq_p<Parser>{}) {
            return rhs.parser_.prepend<true>(lit(str));
        } else {
            return lit(str) >> rhs;
        }
    }

    template<typename Parser>
    constexpr auto parser_interface<Parser>::operator>(char rhs) const noexcept
    {
        if constexpr (detail::is_seq_p<Parser>{}) {
            return parser_.append<false>(lit(rhs));
        } else {
            return *this > lit(rhs);
        }
    }

    template<typename Parser>
    constexpr auto parser_interface<Parser>::operator>(char32_t rhs) const
        noexcept
    {
        if constexpr (detail::is_seq_p<Parser>{}) {
            return parser_.append<false>(lit(rhs));
        } else {
            return *this > lit(rhs);
        }
    }

    template<typename Parser>
    constexpr auto parser_interface<Parser>::
    operator>(std::string_view rhs) const noexcept
    {
        if constexpr (detail::is_seq_p<Parser>{}) {
            return parser_.append<false>(lit(rhs));
        } else {
            return *this > lit(rhs);
        }
    }

    template<typename Parser>
    constexpr auto operator>(char c, parser_interface<Parser> rhs) noexcept
    {
        if constexpr (detail::is_seq_p<Parser>{}) {
            return rhs.parser_.prepend<false>(lit(c));
        } else {
            return lit(c) > rhs;
        }
    }

    template<typename Parser>
    constexpr auto operator>(char32_t c, parser_interface<Parser> rhs) noexcept
    {
        if constexpr (detail::is_seq_p<Parser>{}) {
            return rhs.parser_.prepend<false>(lit(c));
        } else {
            return lit(c) > rhs;
        }
    }

    template<typename Parser>
    constexpr auto
    operator>(std::string_view str, parser_interface<Parser> rhs) noexcept
    {
        if constexpr (detail::is_seq_p<Parser>{}) {
            return rhs.parser_.prepend<false>(lit(str));
        } else {
            return lit(str) > rhs;
        }
    }

    template<typename Parser>
    constexpr auto parser_interface<Parser>::operator|(char rhs) const noexcept
    {
        if constexpr (detail::is_seq_p<Parser>{}) {
            return parser_.append(lit(rhs));
        } else {
            return *this | lit(rhs);
        }
    }

    template<typename Parser>
    constexpr auto parser_interface<Parser>::operator|(char32_t rhs) const
        noexcept
    {
        if constexpr (detail::is_seq_p<Parser>{}) {
            return parser_.append(lit(rhs));
        } else {
            return *this | lit(rhs);
        }
    }

    template<typename Parser>
    constexpr auto parser_interface<Parser>::
    operator|(std::string_view rhs) const noexcept
    {
        if constexpr (detail::is_seq_p<Parser>{}) {
            return parser_.append(lit(rhs));
        } else {
            return *this | lit(rhs);
        }
    }

    template<typename Parser>
    constexpr auto operator|(char c, parser_interface<Parser> rhs) noexcept
    {
        if constexpr (detail::is_or_p<Parser>{}) {
            return rhs.parser_.prepend(lit(c));
        } else {
            return lit(c) | rhs;
        }
    }

    template<typename Parser>
    constexpr auto operator|(char32_t c, parser_interface<Parser> rhs) noexcept
    {
        if constexpr (detail::is_or_p<Parser>{}) {
            return rhs.parser_.prepend(lit(c));
        } else {
            return lit(c) | rhs;
        }
    }

    template<typename Parser>
    constexpr auto
    operator|(std::string_view str, parser_interface<Parser> rhs) noexcept
    {
        if constexpr (detail::is_or_p<Parser>{}) {
            return rhs.parser_.prepend(lit(str));
        } else {
            return lit(str) | rhs;
        }
    }

    template<typename Parser>
    constexpr auto parser_interface<Parser>::operator-(char rhs) const noexcept
    {
        return *this >> !lit(rhs);
    }

    template<typename Parser>
    constexpr auto parser_interface<Parser>::operator-(char32_t rhs) const
        noexcept
    {
        return *this >> !lit(rhs);
    }

    template<typename Parser>
    constexpr auto parser_interface<Parser>::
    operator-(std::string_view rhs) const noexcept
    {
        return *this >> !lit(rhs);
    }

    template<typename Parser>
    constexpr auto operator-(char c, parser_interface<Parser> rhs) noexcept
    {
        return lit(c) >> !rhs;
    }

    template<typename Parser>
    constexpr auto operator-(char32_t c, parser_interface<Parser> rhs) noexcept
    {
        return lit(c) >> !rhs;
    }

    template<typename Parser>
    constexpr auto
    operator-(std::string_view str, parser_interface<Parser> rhs) noexcept
    {
        return lit(str) >> !rhs;
    }

    template<typename Parser>
    constexpr auto parser_interface<Parser>::operator%(char rhs) const noexcept
    {
        return *this % lit(rhs);
    }

    template<typename Parser>
    constexpr auto parser_interface<Parser>::operator%(char32_t rhs) const
        noexcept
    {
        return *this % lit(rhs);
    }

    template<typename Parser>
    constexpr auto parser_interface<Parser>::
    operator%(std::string_view rhs) const noexcept
    {
        return *this % lit(rhs);
    }

    template<typename Parser>
    constexpr auto operator%(char c, parser_interface<Parser> rhs) noexcept
    {
        return lit(c) % rhs;
    }

    template<typename Parser>
    constexpr auto operator%(char32_t c, parser_interface<Parser> rhs) noexcept
    {
        return lit(c) % rhs;
    }

    template<typename Parser>
    constexpr auto
    operator%(std::string_view str, parser_interface<Parser> rhs) noexcept
    {
        return lit(str) % rhs;
    }

    namespace literals {

        constexpr auto operator""_l(char c) { return lit(c); }
        constexpr auto operator""_l(char32_t c) { return lit(c); }
        constexpr auto operator""_l(char const * c_str) { return lit(c_str); }

        constexpr auto operator""_p(char c) { return char_(c); }
        constexpr auto operator""_p(char32_t c) { return char_(c); }
        constexpr auto operator""_p(char const * c_str)
        {
            return string(c_str);
        }
    }

}}

#include <boost/parser/detail/printing_impl.hpp>

namespace boost { namespace parser {

    // Parse API.

    template<
        typename Iter,
        typename Parser,
        typename Attr,
        typename ErrorHandler>
    bool parse(
        Iter & first,
        Iter last,
        Parser const & parser,
        ErrorHandler const & error_handler,
        Attr & attr)
    {
        auto const initial_first = first;
        bool success = true;
        int trace_indent = 0;
        auto context =
            detail::make_context(success, trace_indent, error_handler);
        try {
            parser(
                first,
                last,
                context,
                detail::null_parser{},
                detail::flags::gen_attrs,
                success,
                attr);
            return success;
        } catch (parse_error<Iter> const & e) {
            if (error_handler(initial_first, last, e) ==
                error_handler_result::rethrow) {
                throw;
            }
            return false;
        }
    }

    template<typename Iter, typename Parser, typename Attr>
    bool parse(Iter & first, Iter last, Parser const & parser, Attr & attr)
    {
        return parse(first, last, parser, default_error_handler{}, attr);
    }

    template<typename Parser, typename Attr>
    bool parse(std::string_view str, Parser const & parser, Attr & attr)
    {
        auto first = str.begin();
        auto const last = str.end();
        return parse(first, last, parser, default_error_handler{}, attr);
    }

    template<typename Parser, typename Attr, typename ErrorHandler>
    bool parse(
        std::string_view str,
        Parser const & parser,
        ErrorHandler const & error_handler,
        Attr & attr)
    {
        auto first = str.begin();
        auto const last = str.end();
        return parse(first, last, parser, error_handler, attr);
    }

    template<typename Iter, typename Parser, typename ErrorHandler>
    auto parse(
        Iter & first,
        Iter last,
        Parser const & parser,
        ErrorHandler const & error_handler)
    {
        auto const initial_first = first;
        bool success = true;
        int trace_indent = 0;
        auto context =
            detail::make_context(success, trace_indent, error_handler);
        using attr_t = decltype(parser(
            first,
            last,
            context,
            detail::null_parser{},
            detail::flags::gen_attrs,
            success));
        try {
            attr_t attr_ = parser(
                first,
                last,
                context,
                detail::null_parser{},
                detail::flags::gen_attrs,
                success);
            return detail::make_parse_result(attr_, success);
        } catch (parse_error<Iter> const & e) {
            if (error_handler(initial_first, last, e) ==
                error_handler_result::rethrow) {
                throw;
            }
            attr_t attr_;
            return detail::make_parse_result(attr_, false);
        }
    }

    template<typename Iter, typename Parser>
    auto parse(Iter & first, Iter last, Parser const & parser)
    {
        return parse(first, last, parser, default_error_handler{});
    }

    template<typename Parser>
    auto parse(std::string_view str, Parser const & parser)
    {
        auto first = str.begin();
        auto const last = str.end();
        return parse(first, last, parser, default_error_handler{});
    }

    template<typename Parser, typename ErrorHandler>
    auto parse(
        std::string_view str,
        Parser const & parser,
        ErrorHandler const & error_handler)
    {
        auto first = str.begin();
        auto const last = str.end();
        return parse(first, last, parser, error_handler);
    }

    template<typename Iter, typename Parser, typename SkipParser, typename Attr>
    bool skip_parse(
        Iter & first,
        Iter last,
        Parser const & parser,
        SkipParser const & skip,
        Attr & attr)
    {
        return skip_parse(
            first, last, parser, skip, default_error_handler{}, attr);
    }

    template<
        typename Iter,
        typename Parser,
        typename SkipParser,
        typename Attr,
        typename ErrorHandler>
    bool skip_parse(
        Iter & first,
        Iter last,
        Parser const & parser,
        SkipParser const & skip,
        ErrorHandler const & error_handler,
        Attr & attr)
    {
        auto const initial_first = first;
        bool success = true;
        int trace_indent = 0;
        auto context =
            detail::make_context(success, trace_indent, error_handler);
        detail::skip(first, last, skip, detail::default_flags());
        try {
            parser(
                first,
                last,
                context,
                skip,
                detail::default_flags(),
                success,
                attr);
            detail::skip(first, last, skip, detail::default_flags());
            return success;
        } catch (parse_error<Iter> const & e) {
            if (error_handler(initial_first, last, e) ==
                error_handler_result::rethrow) {
                throw;
            }
            return false;
        }
    }

    template<
        typename Parser,
        typename SkipParser,
        typename Attr,
        typename ErrorHandler>
    bool skip_parse(
        std::string_view str,
        Parser const & parser,
        SkipParser const & skip,
        ErrorHandler const & error_handler,
        Attr & attr)
    {
        auto first = str.begin();
        auto const last = str.end();
        return skip_parse(first, last, parser, skip, error_handler, attr);
    }

    template<typename Parser, typename SkipParser, typename Attr>
    bool skip_parse(
        std::string_view str,
        Parser const & parser,
        SkipParser const & skip,
        Attr & attr)
    {
        auto first = str.begin();
        auto const last = str.end();
        return skip_parse(first, last, parser, skip, attr);
    }

    template<
        typename Iter,
        typename Parser,
        typename SkipParser,
        typename ErrorHandler>
    auto skip_parse(
        Iter & first,
        Iter last,
        Parser const & parser,
        SkipParser const & skip,
        ErrorHandler const & error_handler)
    {
        auto const initial_first = first;
        bool success = true;
        int trace_indent = 0;
        auto context =
            detail::make_context(success, trace_indent, error_handler);
        detail::skip(first, last, skip, detail::default_flags());
        using attr_t = decltype(parser(
            first, last, context, skip, detail::default_flags(), success));
        try {
            attr_t attr_ = parser(
                first, last, context, skip, detail::default_flags(), success);
            detail::skip(first, last, skip, detail::default_flags());
            return detail::make_parse_result(attr_, success);
        } catch (parse_error<Iter> const & e) {
            if (error_handler(initial_first, last, e) ==
                error_handler_result::rethrow) {
                throw;
            }
            attr_t attr_;
            return detail::make_parse_result(attr_, false);
        }
    }

    template<typename Iter, typename Parser, typename SkipParser>
    auto skip_parse(
        Iter & first, Iter last, Parser const & parser, SkipParser const & skip)
    {
        return skip_parse(first, last, parser, skip, default_error_handler{});
    }

    template<typename Parser, typename SkipParser, typename ErrorHandler>
    auto skip_parse(
        std::string_view str,
        Parser const & parser,
        SkipParser const & skip,
        ErrorHandler const & error_handler)
    {
        auto first = str.begin();
        auto const last = str.end();
        return skip_parse(first, last, parser, skip, error_handler);
    }

    template<typename Parser, typename SkipParser>
    auto skip_parse(
        std::string_view str, Parser const & parser, SkipParser const & skip)
    {
        auto first = str.begin();
        auto const last = str.end();
        return skip_parse(first, last, parser, skip, default_error_handler{});
    }

    template<
        typename Iter,
        typename Parser,
        typename Attr,
        typename ErrorHandler>
    bool debug_parse(
        Iter & first,
        Iter last,
        Parser const & parser,
        ErrorHandler const & error_handler,
        Attr & attr)
    {
        auto const initial_first = first;
        bool success = true;
        int trace_indent = 0;
        auto context =
            detail::make_context(success, trace_indent, error_handler);
        auto const flags = enable_trace(detail::flags::gen_attrs);
        try {
            parser(
                first,
                last,
                context,
                detail::null_parser{},
                flags,
                success,
                attr);
            final_trace(context, flags, attr);
            return success;
        } catch (parse_error<Iter> const & e) {
            if (error_handler(initial_first, last, e) ==
                error_handler_result::rethrow) {
                throw;
            }
            return false;
        }
    }

    template<typename Iter, typename Parser, typename Attr>
    bool
    debug_parse(Iter & first, Iter last, Parser const & parser, Attr & attr)
    {
        return debug_parse(first, last, parser, default_error_handler{}, attr);
    }

    template<typename Parser, typename Attr, typename ErrorHandler>
    bool debug_parse(
        std::string_view str,
        Parser const & parser,
        ErrorHandler const & error_handler,
        Attr & attr)
    {
        auto first = str.begin();
        auto const last = str.end();
        return debug_parse(first, last, parser, error_handler, attr);
    }

    template<typename Parser, typename Attr>
    bool debug_parse(std::string_view str, Parser const & parser, Attr & attr)
    {
        auto first = str.begin();
        auto const last = str.end();
        return debug_parse(first, last, parser, default_error_handler{}, attr);
    }

    template<typename Iter, typename Parser, typename ErrorHandler>
    auto debug_parse(
        Iter & first,
        Iter last,
        Parser const & parser,
        ErrorHandler const & error_handler)
    {
        auto const initial_first = first;
        bool success = true;
        int trace_indent = 0;
        auto context =
            detail::make_context(success, trace_indent, error_handler);
        auto const flags = enable_trace(detail::flags::gen_attrs);
        using attr_t = decltype(parser(
            first, last, context, detail::null_parser{}, flags, success));
        try {
            attr_t attr_ = parser(
                first, last, context, detail::null_parser{}, flags, success);
            final_trace(context, flags, detail::nope{});
            return detail::make_parse_result(attr_, success);
        } catch (parse_error<Iter> const & e) {
            if (error_handler(initial_first, last, e) ==
                error_handler_result::rethrow) {
                throw;
            }
            attr_t attr_;
            return detail::make_parse_result(attr_, false);
        }
    }

    template<typename Iter, typename Parser>
    auto debug_parse(Iter & first, Iter last, Parser const & parser)
    {
        return debug_parse(first, last, parser, default_error_handler{});
    }

    template<typename Parser, typename ErrorHandler>
    auto debug_parse(
        std::string_view str,
        Parser const & parser,
        ErrorHandler const & error_handler)
    {
        auto first = str.begin();
        auto const last = str.end();
        return debug_parse(first, last, parser, error_handler);
    }

    template<typename Parser>
    auto debug_parse(std::string_view str, Parser const & parser)
    {
        auto first = str.begin();
        auto const last = str.end();
        return debug_parse(first, last, parser, default_error_handler{});
    }

    template<
        typename Iter,
        typename Parser,
        typename SkipParser,
        typename Attr,
        typename ErrorHandler>
    bool debug_skip_parse(
        Iter & first,
        Iter last,
        Parser const & parser,
        SkipParser const & skip,
        ErrorHandler const & error_handler,
        Attr & attr)
    {
        auto const initial_first = first;
        bool success = true;
        int trace_indent = 0;
        auto context =
            detail::make_context(success, trace_indent, error_handler);
        auto const flags = enable_trace(detail::default_flags());
        detail::skip(first, last, skip, flags);
        try {
            parser(first, last, context, skip, flags, success, attr);
            detail::skip(first, last, skip, flags);
            final_trace(context, flags, attr);
            return success;
        } catch (parse_error<Iter> const & e) {
            if (error_handler(initial_first, last, e) ==
                error_handler_result::rethrow) {
                throw;
            }
            return false;
        }
    }

    template<typename Iter, typename Parser, typename SkipParser, typename Attr>
    bool debug_skip_parse(
        Iter & first,
        Iter last,
        Parser const & parser,
        SkipParser const & skip,
        Attr & attr)
    {
        return debug_skip_parse(
            first, last, parser, skip, default_error_handler{}, attr);
    }

    template<
        typename Parser,
        typename SkipParser,
        typename Attr,
        typename ErrorHandler>
    bool debug_skip_parse(
        std::string_view str,
        Parser const & parser,
        SkipParser const & skip,
        ErrorHandler const & error_handler,
        Attr & attr)
    {
        auto first = str.begin();
        auto const last = str.end();
        return debug_skip_parse(first, last, parser, skip, error_handler, attr);
    }

    template<typename Parser, typename SkipParser, typename Attr>
    bool debug_skip_parse(
        std::string_view str,
        Parser const & parser,
        SkipParser const & skip,
        Attr & attr)
    {
        auto first = str.begin();
        auto const last = str.end();
        return debug_skip_parse(
            first, last, parser, skip, default_error_handler{}, attr);
    }

    template<
        typename Iter,
        typename Parser,
        typename SkipParser,
        typename ErrorHandler>
    auto debug_skip_parse(
        Iter & first,
        Iter last,
        Parser const & parser,
        SkipParser const & skip,
        ErrorHandler const & error_handler)
    {
        auto const initial_first = first;
        bool success = true;
        int trace_indent = 0;
        auto context =
            detail::make_context(success, trace_indent, error_handler);
        auto const flags = enable_trace(detail::default_flags());
        detail::skip(first, last, skip, flags);
        using attr_t =
            decltype(parser(first, last, context, skip, flags, success));
        try {
            attr_t attr_ = parser(first, last, context, skip, flags, success);
            detail::skip(first, last, skip, flags);
            final_trace(context, flags, detail::nope{});
            return detail::make_parse_result(attr_, success);
        } catch (parse_error<Iter> const & e) {
            if (error_handler(initial_first, last, e) ==
                error_handler_result::rethrow) {
                throw;
            }
            attr_t attr_;
            return detail::make_parse_result(attr_, false);
        }
    }

    template<typename Iter, typename Parser, typename SkipParser>
    auto debug_skip_parse(
        Iter & first, Iter last, Parser const & parser, SkipParser const & skip)
    {
        return debug_skip_parse(
            first, last, parser, skip, default_error_handler{});
    }

    template<typename Parser, typename SkipParser, typename ErrorHandler>
    auto debug_skip_parse(
        std::string_view str,
        Parser const & parser,
        SkipParser const & skip,
        ErrorHandler const & error_handler)
    {
        auto first = str.begin();
        auto const last = str.end();
        return debug_skip_parse(first, last, parser, skip, error_handler);
    }

    template<typename Parser, typename SkipParser>
    auto debug_skip_parse(
        std::string_view str, Parser const & parser, SkipParser const & skip)
    {
        auto first = str.begin();
        auto const last = str.end();
        return debug_skip_parse(
            first, last, parser, skip, default_error_handler{});
    }

}}

#endif
