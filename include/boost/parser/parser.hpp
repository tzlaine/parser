#ifndef BOOST_PARSER_PARSER_HPP
#define BOOST_PARSER_PARSER_HPP

#include <boost/parser/parser_fwd.hpp>
#include <boost/parser/concepts.hpp>
#include <boost/parser/error_handling.hpp>
#include <boost/parser/tuple.hpp>
#include <boost/parser/detail/hl.hpp>
#include <boost/parser/detail/numeric.hpp>
#include <boost/parser/detail/printing.hpp>

#if __has_include(<boost/preprocessor/variadic/to_seq.hpp>) &&        \
    __has_include(<boost/preprocessor/variadic/elem.hpp>) &&          \
    __has_include(<boost/preprocessor/seq/for_each.hpp>)
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/variadic/elem.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#define BOOST_PARSER_HAVE_BOOST_PP 1
#else
#define BOOST_PARSER_HAVE_BOOST_PP 0
#endif

#include <boost/parser/detail/text/algorithm.hpp>
#include <boost/parser/detail/text/trie.hpp>
#include <boost/parser/detail/text/detail/unpack.hpp>

#include <type_traits>
#include <variant>
#include <vector>


namespace boost { namespace parser {

    /** A simple view type used throughout the rest of the library. */
#if BOOST_PARSER_USE_CONCEPTS
    template<std::forward_iterator I, std::sentinel_for<I> S = I>
#else
    template<typename I, typename S = I>
#endif
    struct view : parser::detail::stl_interfaces::view_interface<view<I, S>>
    {
        using iterator = I;
        using sentinel = S;

        constexpr view() = default;
        constexpr view(iterator first, sentinel last) :
            first_(first), last_(last)
        {}

        constexpr iterator begin() const noexcept { return first_; }
        constexpr sentinel end() const noexcept { return last_; }

        friend bool operator==(view lhs, view rhs) noexcept
        {
            return lhs.begin() == rhs.begin() && lhs.end() == rhs.end();
        }

    private:
        iterator first_;
        sentinel last_;
    };

    /** Makes a `view<I>` from two `I`s. */
#if BOOST_PARSER_USE_CONCEPTS
    template<std::forward_iterator I, std::sentinel_for<I> S = I>
#else
    template<typename I, typename S = I>
#endif
    constexpr view<I, S> make_view(I first, S last) noexcept
    {
        return view<I, S>(first, last);
    }


    /** A placeholder type used to represent the absence of information,
        value, etc., inside semantic actions.  For instance, calling
        `_locals(ctx)` in a semantic action associated with a parser that has
        no locals will yield a `none`. */
    struct none;

#if defined(BOOST_PARSER_NO_RUNTIME_ASSERTIONS)
    struct none
    {};
#else
    struct none
    {
        none() = default;

        // Constructible from, assignable from, and implicitly convertible to,
        // anything.
        template<typename T>
        none(T const &)
        {
            fail();
        }
        template<typename T>
        none & operator=(T const &)
        {
            fail();
            return *this;
        }
        template<typename T>
        operator T() const
        {
            fail();
            return T{};
        }

        // unary operators
        none operator+() const
        {
            fail();
            return none{};
        }
        none operator-() const
        {
            fail();
            return none{};
        }
        none operator*() const
        {
            fail();
            return none{};
        }
        none operator~() const
        {
            fail();
            return none{};
        }
        none operator&() const
        {
            fail();
            return none{};
        }
        none operator!() const
        {
            fail();
            return none{};
        }
        none operator++()
        {
            fail();
            return none{};
        }
        none & operator++(int)
        {
            fail();
            return *this;
        }
        none operator--()
        {
            fail();
            return none{};
        }
        none operator--(int)
        {
            fail();
            return *this;
        }

        // binary operators
        template<typename T>
        none operator<<(T const &) const
        {
            fail();
            return none{};
        }
        template<typename T>
        none operator>>(T const &) const
        {
            fail();
            return none{};
        }
        template<typename T>
        none operator*(T const &) const
        {
            fail();
            return none{};
        }
        template<typename T>
        none operator/(T const &) const
        {
            fail();
            return none{};
        }
        template<typename T>
        none operator%(T const &) const
        {
            fail();
            return none{};
        }
        template<typename T>
        none operator+(T const &) const
        {
            fail();
            return none{};
        }
        template<typename T>
        none operator-(T const &) const
        {
            fail();
            return none{};
        }
        template<typename T>
        none operator<(T const &) const
        {
            fail();
            return none{};
        }
        template<typename T>
        none operator>(T const &) const
        {
            fail();
            return none{};
        }
        template<typename T>
        none operator<=(T const &) const
        {
            fail();
            return none{};
        }
        template<typename T>
        none operator>=(T const &) const
        {
            fail();
            return none{};
        }
        template<typename T>
        none operator==(T const &) const
        {
            fail();
            return none{};
        }
        template<typename T>
        none operator!=(T const &) const
        {
            fail();
            return none{};
        }
        template<typename T>
        none operator||(T const &) const
        {
            fail();
            return none{};
        }
        template<typename T>
        none operator&&(T const &) const
        {
            fail();
            return none{};
        }
        template<typename T>
        none operator&(T const &) const
        {
            fail();
            return none{};
        }
        template<typename T>
        none operator|(T const &) const
        {
            fail();
            return none{};
        }
        template<typename T>
        none operator^(T const &) const
        {
            fail();
            return none{};
        }
        template<typename T>
        none operator,(T const &) const
        {
            fail();
            return none{};
        }
        template<typename T>
        none operator->*(T const &) const
        {
            fail();
            return none{};
        }
        template<typename T>
        none operator<<=(T const &)
        {
            fail();
            return none{};
        }
        template<typename T>
        none operator>>=(T const &)
        {
            fail();
            return none{};
        }
        template<typename T>
        none operator*=(T const &)
        {
            fail();
            return none{};
        }
        template<typename T>
        none operator/=(T const &)
        {
            fail();
            return none{};
        }
        template<typename T>
        none operator%=(T const &)
        {
            fail();
            return none{};
        }
        template<typename T>
        none operator+=(T const &)
        {
            fail();
            return none{};
        }
        template<typename T>
        none operator-=(T const &)
        {
            fail();
            return none{};
        }
        template<typename T>
        none operator&=(T const &)
        {
            fail();
            return none{};
        }
        template<typename T>
        none operator|=(T const &)
        {
            fail();
            return none{};
        }
        template<typename T>
        none operator^=(T const &)
        {
            fail();
            return none{};
        }
        template<typename T>
        none operator[](T const &) const
        {
            fail();
            return none{};
        }

        // n-ary operators
        template<typename... Args>
        none operator()(Args const &...) const
        {
            fail();
            return none{};
        }

        void fail() const
        {
            // If you're seeing this, you've probably gotten a `none` out of
            // the parse context, and are trying to use it because you think
            // it's something else.  For instance, if your parser produces an
            // int attribute, the semantic ation `[](auto & ctx) { _attr(ctx)
            // = 0; }` may be fine.  If you attach that same semantic action
            // to `eps`, you end up here, because `eps` has no attribute, and
            // so `_attr(ctx)` produces a `none`.
            BOOST_PARSER_DEBUG_ASSERT(false);
        }
    };
#endif

    namespace detail {
        // Utility types.

        struct common_type_equal
        {
            template<typename T, typename U>
            bool operator()(T x, U y)
            {
                using common_t = std::common_type_t<decltype(x), decltype(y)>;
                return (common_t)x == (common_t)y;
            }
        };

        struct common_type_less
        {
            template<typename T, typename U>
            bool operator()(T x, U y)
            {
                using common_t = std::common_type_t<decltype(x), decltype(y)>;
                return (common_t)x < (common_t)y;
            }
        };

        struct nope
        {
            template<typename T>
            constexpr nope & operator=(T const &)
            {
                return *this;
            }

            operator std::nullopt_t() const noexcept { return std::nullopt; }

            template<typename Context>
            constexpr bool operator()(Context const &) const noexcept
            {
                return true;
            }

            constexpr nope operator*() const noexcept { return nope{}; }

            friend constexpr bool operator==(nope, nope) { return true; }
            friend constexpr bool operator!=(nope, nope) { return false; }

            template<typename T>
            friend constexpr bool operator==(T, nope)
            {
                return false;
            }
            template<typename T>
            friend constexpr bool operator!=(T, nope)
            {
                return false;
            }
        };

        inline nope global_nope;

        template<typename T, bool AlwaysConst = false>
        using nope_or_pointer_t = std::conditional_t<
            std::is_same_v<std::remove_const_t<T>, nope>,
            nope,
            std::conditional_t<AlwaysConst, T const *, T *>>;

        template<
            typename I,
            typename S,
            typename ErrorHandler,
            typename GlobalState = nope,
            typename Callbacks = nope,
            typename Attr = nope,
            typename Val = nope,
            typename RuleLocals = nope,
            typename RuleParams = nope,
            typename Where = nope>
        struct parse_context
        {
            parse_context() = default;
            parse_context(parse_context const &) = default;
            parse_context & operator=(parse_context const &) = default;

            I first_;
            S last_;
            bool * pass_ = nullptr;
            int * trace_indent_ = nullptr;
            symbol_table_tries_t * symbol_table_tries_ = nullptr;
            ErrorHandler const * error_handler_ = nullptr;
            nope_or_pointer_t<GlobalState> globals_{};
            nope_or_pointer_t<Callbacks, true> callbacks_{};
            nope_or_pointer_t<Attr> attr_{};
            nope_or_pointer_t<Val> val_{};
            nope_or_pointer_t<RuleLocals> locals_{};
            nope_or_pointer_t<RuleParams, true> params_{};
            nope_or_pointer_t<Where, true> where_{};

            template<typename T>
            static auto nope_or_address(T & x)
            {
                if constexpr (std::is_same_v<std::remove_const_t<T>, nope>)
                    return nope{};
                else
                    return std::addressof(x);
            }

            template<typename T, typename U>
            static auto other_or_address(T other, U & x)
            {
                if constexpr (std::is_same_v<std::remove_const_t<U>, nope>)
                    return other;
                else
                    return std::addressof(x);
            }

            parse_context(
                I & first,
                S last,
                bool & success,
                int & indent,
                ErrorHandler const & error_handler,
                GlobalState & globals,
                symbol_table_tries_t & symbol_table_tries) :
                first_(first),
                last_(last),
                pass_(std::addressof(success)),
                trace_indent_(std::addressof(indent)),
                symbol_table_tries_(std::addressof(symbol_table_tries)),
                error_handler_(std::addressof(error_handler)),
                globals_(nope_or_address(globals))
            {}

            // With callbacks.
            parse_context(
                I & first,
                S last,
                bool & success,
                int & indent,
                ErrorHandler const & error_handler,
                Callbacks const & callbacks,
                GlobalState & globals,
                symbol_table_tries_t & symbol_table_tries) :
                first_(first),
                last_(last),
                pass_(std::addressof(success)),
                trace_indent_(std::addressof(indent)),
                symbol_table_tries_(std::addressof(symbol_table_tries)),
                error_handler_(std::addressof(error_handler)),
                globals_(nope_or_address(globals)),
                callbacks_(std::addressof(callbacks))
            {}

            // For making rule contexts.
            template<
                typename OldVal,
                typename OldRuleLocals,
                typename OldRuleParams,
                typename NewVal,
                typename NewRuleLocals,
                typename NewRuleParams>
            parse_context(
                parse_context<
                    I,
                    S,
                    ErrorHandler,
                    GlobalState,
                    Callbacks,
                    Attr,
                    OldVal,
                    OldRuleLocals,
                    OldRuleParams> const & other,
                NewVal & value,
                NewRuleLocals & locals,
                NewRuleParams const & params) :
                first_(other.first_),
                last_(other.last_),
                pass_(other.pass_),
                trace_indent_(other.trace_indent_),
                symbol_table_tries_(other.symbol_table_tries_),
                error_handler_(other.error_handler_),
                globals_(other.globals_),
                callbacks_(other.callbacks_),
                attr_(other.attr_),
                val_(other_or_address(other.val_, value)),
                locals_(other_or_address(other.locals_, locals)),
                params_(other_or_address(other.params_, params))
            {}

            // For making action contexts.
            template<typename OldAttr, typename OldWhere>
            parse_context(
                parse_context<
                    I,
                    S,
                    ErrorHandler,
                    GlobalState,
                    Callbacks,
                    OldAttr,
                    Val,
                    RuleLocals,
                    RuleParams,
                    OldWhere> const & other,
                Attr & attr,
                Where const & where) :
                first_(other.first_),
                last_(other.last_),
                pass_(other.pass_),
                trace_indent_(other.trace_indent_),
                symbol_table_tries_(other.symbol_table_tries_),
                error_handler_(other.error_handler_),
                globals_(other.globals_),
                callbacks_(other.callbacks_),
                attr_(nope_or_address(attr)),
                val_(other.val_),
                locals_(other.locals_),
                params_(other.params_),
                where_(nope_or_address(where))
            {}
        };

        template<
            typename I,
            typename S,
            typename ErrorHandler,
            typename GlobalState,
            typename Callbacks,
            typename Val,
            typename RuleLocals,
            typename RuleParams,
            typename Attr,
            typename Where,
            typename OldAttr>
        auto make_action_context(
            parse_context<
                I,
                S,
                ErrorHandler,
                GlobalState,
                Callbacks,
                OldAttr,
                Val,
                RuleLocals,
                RuleParams> const & context,
            Attr & attr,
            Where const & where)
        {
            using result_type = parse_context<
                I,
                S,
                ErrorHandler,
                GlobalState,
                Callbacks,
                Attr,
                Val,
                RuleLocals,
                RuleParams,
                Where>;
            return result_type(context, attr, where);
        }

        template<
            typename I,
            typename S,
            typename ErrorHandler,
            typename GlobalState,
            typename Callbacks,
            typename Attr,
            typename Val,
            typename RuleLocals,
            typename RuleParams,
            typename NewVal,
            typename NewRuleLocals,
            typename NewRuleParams>
        auto make_rule_context(
            parse_context<
                I,
                S,
                ErrorHandler,
                GlobalState,
                Callbacks,
                Attr,
                Val,
                RuleLocals,
                RuleParams> const & context,
            NewVal & value,
            NewRuleLocals & locals,
            NewRuleParams const & params)
        {
            using result_type = parse_context<
                I,
                S,
                ErrorHandler,
                GlobalState,
                Callbacks,
                Attr,
                std::conditional_t<std::is_same_v<NewVal, nope>, Val, NewVal>,
                std::conditional_t<
                    std::is_same_v<NewRuleLocals, nope>,
                    RuleLocals,
                    NewRuleLocals>,
                std::conditional_t<
                    std::is_same_v<NewRuleParams, nope>,
                    RuleParams,
                    NewRuleParams>>;
            return result_type(context, value, locals, params);
        }

        template<typename Iter, typename Sentinel, typename ErrorHandler>
        auto make_context(
            Iter first,
            Sentinel last,
            bool & success,
            int & indent,
            ErrorHandler const & error_handler,
            nope & n,
            symbol_table_tries_t & symbol_table_tries) noexcept
        {
            return parse_context(
                first,
                last,
                success,
                indent,
                error_handler,
                n,
                symbol_table_tries);
        }

        template<
            typename Iter,
            typename Sentinel,
            typename ErrorHandler,
            typename GlobalState>
        auto make_context(
            Iter first,
            Sentinel last,
            bool & success,
            int & indent,
            ErrorHandler const & error_handler,
            GlobalState & globals,
            symbol_table_tries_t & symbol_table_tries) noexcept
        {
            return parse_context(
                first,
                last,
                success,
                indent,
                error_handler,
                globals,
                symbol_table_tries);
        }

        template<
            typename Iter,
            typename Sentinel,
            typename ErrorHandler,
            typename Callbacks>
        auto make_context(
            Iter first,
            Sentinel last,
            bool & success,
            int & indent,
            ErrorHandler const & error_handler,
            Callbacks const & callbacks,
            nope & n,
            symbol_table_tries_t & symbol_table_tries) noexcept
        {
            return parse_context(
                first,
                last,
                success,
                indent,
                error_handler,
                callbacks,
                n,
                symbol_table_tries);
        }

        template<
            typename Iter,
            typename Sentinel,
            typename ErrorHandler,
            typename Callbacks,
            typename GlobalState>
        auto make_context(
            Iter first,
            Sentinel last,
            bool & success,
            int & indent,
            ErrorHandler const & error_handler,
            Callbacks const & callbacks,
            GlobalState & globals,
            symbol_table_tries_t & symbol_table_tries) noexcept
        {
            return parse_context(
                first,
                last,
                success,
                indent,
                error_handler,
                callbacks,
                globals,
                symbol_table_tries);
        }


        template<unsigned int I>
        struct param_t
        {
            template<typename Context>
            decltype(auto) operator()(Context const & context) const
            {
                return parser::_params(context)[llong<I>{}];
            }
        };


        template<typename T, typename... Args>
        using callable = decltype(std::declval<T>()(std::declval<Args>()...));

        template<
            typename Context,
            typename T,
            bool Callable = is_detected<callable, T const &, Context const &>{}>
        struct resolve_impl
        {
            static auto call(Context const &, T const & x) { return x; }
        };

        template<typename Context, typename T>
        struct resolve_impl<Context, T, true>
        {
            static auto call(Context const & context, T const & x)
            {
                return x(context);
            }
        };

        template<typename Context, typename T>
        auto resolve(Context const & context, T const & x)
        {
            return resolve_impl<Context, T>::call(context, x);
        }

        template<typename Context>
        auto resolve(Context const &, nope n)
        {
            return n;
        }


        template<typename Context, typename ParamsTuple>
        auto
        resolve_rule_params(Context const & context, ParamsTuple const & params)
        {
            return detail::hl::transform(params, [&](auto const & x) {
                return detail::resolve(context, x);
            });
        }

        template<typename Context>
        nope resolve_rule_params(Context const & context, nope)
        {
            return {};
        }

        template<typename LocalsType, typename Context>
        LocalsType make_locals_impl(Context const & context, std::true_type)
        {
            return LocalsType(context);
        }

        template<typename LocalsType, typename Context>
        LocalsType make_locals_impl(Context const & context, std::false_type)
        {
            return LocalsType();
        }

        template<typename LocalsType, typename Context>
        LocalsType make_locals(Context const & context)
        {
            return detail::make_locals_impl<LocalsType>(
                context,
                typename std::is_convertible<Context const &, LocalsType>::
                    type{});
        }


        template<typename Context>
        decltype(auto) _indent(Context const & context)
        {
            return *context.trace_indent_;
        }

        template<typename Context>
        decltype(auto) _callbacks(Context const & context)
        {
            return *context.callbacks_;
        }

        template<typename Context, typename T>
        decltype(auto) get_trie(
            Context const & context, symbol_parser<T> const & symbol_parser)
        {
            using trie_t = text::trie<std::vector<uint32_t>, T>;
            symbol_table_tries_t & symbol_table_tries =
                *context.symbol_table_tries_;
            any_copyable & a = symbol_table_tries[(void *)&symbol_parser];
            if (a.empty()) {
                a = trie_t{};
                trie_t & trie = a.cast<trie_t>();
                for (auto const & e : symbol_parser.initial_elements()) {
                    trie.insert(text::as_utf32(e.first), e.second);
                }
                return trie;
            } else {
                return a.cast<trie_t>();
            }
        }


        // Type traits.

        template<typename T>
        using remove_cv_ref_t = typename std::remove_cv<
            typename std::remove_reference<T>::type>::type;

        template<typename T, typename U>
        using comparison = decltype(std::declval<T>() == std::declval<U>());

        template<typename T, typename U>
        struct is_equality_comparable_with
            : std::integral_constant<bool, is_detected<comparison, T, U>::value>
        {};

        template<typename T>
        struct is_nope : std::false_type
        {};
        template<>
        struct is_nope<nope> : std::true_type
        {};
        template<typename T>
        constexpr bool is_nope_v = is_nope<remove_cv_ref_t<T>>::value;

        template<typename T>
        struct is_tuple : std::false_type
        {};

        template<typename... T>
        struct is_tuple<tuple<T...>> : std::true_type
        {};

        template<typename T>
        struct is_unconditional_eps : std::false_type
        {};
        template<>
        struct is_unconditional_eps<eps_parser<nope>> : std::true_type
        {};
        template<typename T>
        constexpr bool is_unconditional_eps_v =
            is_unconditional_eps<remove_cv_ref_t<T>>::value;

        template<typename T>
        struct is_zero_plus_p : std::false_type
        {};
        template<typename T>
        struct is_zero_plus_p<zero_plus_parser<T>> : std::true_type
        {};

        template<typename T>
        struct is_or_p : std::false_type
        {};
        template<typename T>
        struct is_or_p<or_parser<T>> : std::true_type
        {};

        template<typename T>
        struct is_seq_p : std::false_type
        {};
        template<typename T, typename U>
        struct is_seq_p<seq_parser<T, U>> : std::true_type
        {};

        template<typename T>
        struct is_one_plus_p : std::false_type
        {};
        template<typename T>
        struct is_one_plus_p<one_plus_parser<T>> : std::true_type
        {};

        template<typename T>
        struct is_optional : std::false_type
        {};
        template<typename T>
        struct is_optional<std::optional<T>> : std::true_type
        {};

        template<typename T>
        struct is_variant : std::false_type
        {};
        template<typename... T>
        struct is_variant<std::variant<T...>> : std::true_type
        {};

        template<typename T>
        struct is_utf8_view : std::false_type
        {};
        template<typename I, typename S>
        struct is_utf8_view<text::utf8_view<I, S>> : std::true_type
        {};

        template<typename F, typename... Args>
        struct is_invocable : std::integral_constant<
                                  bool,
                                  is_detected<callable, F, Args...>::value>
        {};

        template<typename T, typename... Args>
        constexpr bool is_invocable_v = is_invocable<T, Args...>::value;

#if BOOST_PARSER_USE_CONCEPTS

        template<typename T>
        using iterator_t = std::ranges::iterator_t<T>;
        template<typename T>
        using sentinel_t = std::ranges::sentinel_t<T>;
        template<typename T>
        using iter_value_t = std::iter_value_t<T>;
        template<typename T>
        using iter_reference_t = std::iter_reference_t<T>;
        template<typename T>
        using range_value_t = std::ranges::range_value_t<T>;

        template<typename T>
        concept non_unicode_char_range_like =
            utf8_range_like<T> &&
            (!is_utf8_view<remove_cv_ref_t<T>>::value && !char8_pointer<T>);

#else

        template<typename T>
        using iterator_t = decltype(std::begin(std::declval<T &>()));
        template<typename Range>
        using sentinel_t = decltype(std::end(std::declval<Range>()));
        template<typename T>
        using iter_value_t = typename std::iterator_traits<T>::value_type;
        template<typename T>
        using iter_reference_t = decltype(*std::declval<T &>());
        template<typename T>
        using range_value_t = iter_value_t<iterator_t<T>>;

        template<typename T, int N>
        struct is_integral_and_n_bytes
            : std::integral_constant<
                  bool,
                  std::is_integral_v<T> && sizeof(T) == N>
        {};

        template<typename T>
        struct is_utf8_pointer
            : std::integral_constant<
                  bool,
                  std::is_pointer_v<T> &&
                      is_integral_and_n_bytes<detected_t<iter_value_t, T>, 1>::
                          value>
        {};

        template<typename T>
        constexpr bool utf8_pointer = is_utf8_pointer<T>::value;

        template<typename T>
        using has_begin = decltype(*std::begin(std::declval<T &>()));
        template<typename T>
        using has_end = decltype(std::end(std::declval<T &>()));

        template<typename T>
        using is_utf8_range = std::integral_constant<
            bool,
            (is_integral_and_n_bytes<
                 remove_cv_ref_t<detected_t<has_begin, T>>,
                 1>::value &&
             is_detected<has_end, T>::value)>;

        template<typename T>
        using is_utf8_range_like = std::
            integral_constant<bool, is_utf8_range<T>::value || utf8_pointer<T>>;

#if defined(__cpp_char8_t)
        template<typename T>
        struct is_char8_pointer
            : std::integral_constant<
                  bool,
                  std::is_pointer_v<T> &&
                      std::is_same_v<detected_t<iter_value_t, T>, char8_t>>
        {};
#else
        template<typename T>
        struct is_char8_pointer : std::false_type
        {};
#endif

        template<typename T>
        struct is_non_unicode_char_range_like
            : std::integral_constant<
                  bool,
                  is_utf8_range_like<T>::value && !is_utf8_view<T>::value &&
                      !is_char8_pointer<T>::value>
        {};

        template<typename T>
        constexpr bool non_unicode_char_range_like =
            is_non_unicode_char_range_like<T>::value;

        template<typename T>
        using has_insert = decltype(std::declval<T>().insert(
            std::declval<T>().begin(), *std::declval<T>().begin()));
        template<typename T>
        using has_range_insert = decltype(std::declval<T>().insert(
            std::declval<T>().begin(),
            std::declval<T>().begin(),
            std::declval<T>().end()));

        template<typename T>
        struct is_container : std::integral_constant<
                                  bool,
                                  is_detected<has_insert, T>::value &&
                                      is_detected<has_range_insert, T>::value>
        {};

        template<typename T, typename U>
        struct is_container_and_value_type
            : std::integral_constant<
                  bool,
                  is_container<T>::value &&
                      std::is_same_v<detected_t<range_value_t, T>, U>>
        {};

        template<typename T, typename U>
        constexpr bool container_and_value_type =
            is_container_and_value_type<T, U>::value;

        template<typename T>
        struct is_parsable_iter
            : std::integral_constant<
                  bool,
                  std::is_integral_v<
                      remove_cv_ref_t<detected_t<iter_value_t, T>>>>
        {};

        template<typename T>
        struct is_parsable_range
            : std::integral_constant<
                  bool,
                  std::is_integral_v<
                      remove_cv_ref_t<detected_t<has_begin, T>>> &&
                      is_detected<has_end, T>::value>
        {};

        template<typename T>
        struct is_parsable_pointer
            : std::integral_constant<
                  bool,
                  std::is_pointer_v<std::decay_t<T>> &&
                      std::is_integral_v<
                          std::remove_pointer_t<std::decay_t<T>>>>
        {};

        template<typename T>
        struct is_parsable_range_like
            : std::integral_constant<
                  bool,
                  is_parsable_range<T>::value || is_parsable_pointer<T>::value>
        {};
    }

    template<typename T>
    constexpr bool container = detail::is_container<T>::value;

    namespace detail {
#endif


        // Metafunctions.

        template<bool WrapInOptional, typename Tuple>
        struct to_hana_tuple_or_type_impl;

        template<typename... T>
        struct to_hana_tuple_or_type_impl<true, tuple<T...>>
        {
            using type = std::optional<std::variant<T...>>;
        };

        template<typename... T>
        struct to_hana_tuple_or_type_impl<false, tuple<T...>>
        {
            using type = std::variant<T...>;
        };

        template<typename T>
        struct to_hana_tuple_or_type_impl<true, tuple<T>>
        {
            // The reason this is not two separate specializations, one
            // for tuple<t> and on for tuple<optional<T>>, is because
            // MSVC.
            using type =
                std::conditional_t<is_optional<T>::value, T, std::optional<T>>;
        };

        template<typename T>
        struct to_hana_tuple_or_type_impl<false, tuple<T>>
        {
            using type = T;
        };

        template<>
        struct to_hana_tuple_or_type_impl<true, tuple<>>
        {
            using type = nope;
        };

        template<>
        struct to_hana_tuple_or_type_impl<false, tuple<>>
        {
            using type = nope;
        };

        template<typename Pair>
        struct to_hana_tuple_or_type;

        template<typename Tuple, typename TrueFalse>
        struct to_hana_tuple_or_type<tuple<Tuple, TrueFalse>>
        {
            // This has to be done in two steps like this because MSVC.
            using type =
                typename to_hana_tuple_or_type_impl<TrueFalse::value, Tuple>::
                    type;
        };

        template<typename T>
        using to_hana_tuple_or_type_t = typename to_hana_tuple_or_type<T>::type;

        template<typename T, bool Container = container<T>>
        struct sequence_of_impl
        {
            using type = std::vector<T>;
        };

        template<>
        struct sequence_of_impl<nope, true>
        {
            using type = nope;
        };

        template<>
        struct sequence_of_impl<nope, false>
        {
            using type = nope;
        };

        template<typename T>
        struct sequence_of_impl<T, true>
        {
            using type = T;
        };

        template<typename T>
        using sequence_of = typename sequence_of_impl<T>::type;

        template<typename T>
        struct optional_of_impl
        {
            using type = std::optional<T>;
        };

        template<typename T>
        struct optional_of_impl<std::optional<T>>
        {
            using type = std::optional<T>;
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
        struct unwrapped_optional<std::optional<T>>
        {
            using type = T;
        };
        template<typename T>
        using unwrapped_optional_t = typename unwrapped_optional<T>::type;



        // Etc.

        template<typename T>
        struct wrapper
        {
            using type = T;

            constexpr bool operator==(wrapper) const { return true; }
        };

        struct wrap
        {
            template<typename T>
            constexpr auto operator()(T type) const
            {
                return wrapper<T>{};
            }
        };

        struct unwrap
        {
            template<typename T>
            constexpr auto operator()(T wrapped_type) const
            {
                return typename T::type{};
            }
        };

        template<typename Container, typename T>
        void append(Container & c, T && x, bool gen_attrs)
        {
            if (!gen_attrs)
                return;
            if constexpr (
                std::is_integral_v<range_value_t<Container>> &&
                std::is_integral_v<T> &&
                sizeof(range_value_t<Container>) == 1 && sizeof(T) == 4) {
                uint32_t cps[1] = {(uint32_t)x};
                auto const r = text::as_utf8(cps);
                c.insert(c.end(), r.begin(), r.end());
            } else {
                c.insert(c.end(), std::move(x));
            }
        }

        template<typename Container>
        void append(Container & c, nope &&, bool)
        {}

        template<typename T>
        void append(nope &, T &&, bool)
        {}

        inline void append(nope &, nope &&, bool) {}

        template<typename Container, typename Iter, typename Sentinel>
        void append(Container & c, Iter first, Sentinel last, bool gen_attrs)
        {
            if (!gen_attrs)
                return;
            using container_value_type = range_value_t<Container>;
            using iter_value_type = iter_value_t<Iter>;
            if constexpr (
                std::is_integral_v<container_value_type> &&
                std::is_integral_v<iter_value_type> &&
                sizeof(container_value_type) == 1 &&
                sizeof(iter_value_type) == 4) {
                auto const r = text::as_utf8(first, last);
                c.insert(c.end(), r.begin(), r.end());
            } else {
                c.insert(c.end(), first, last);
            }
        }

        template<typename Iter, typename Sentinel>
        void append(nope &, Iter first, Sentinel last, bool gen_attrs)
        {}

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
        constexpr inline flags disable_trace(flags f)
        {
            return flags(uint32_t(f) & ~uint32_t(flags::trace));
        }
        constexpr inline flags set_in_apply_parser(flags f)
        {
            return flags(uint32_t(f) | uint32_t(flags::in_apply_parser));
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
        constexpr inline bool in_apply_parser(flags f)
        {
            return (uint32_t(f) & uint32_t(flags::in_apply_parser)) ==
                   uint32_t(flags::in_apply_parser);
        }

        struct null_parser
        {};

        struct skip_skipper
        {
            template<
                bool UseCallbacks,
                typename Iter,
                typename Sentinel,
                typename Context,
                typename SkipParser>
            nope operator()(
                std::bool_constant<UseCallbacks> use_cbs,
                Iter & first,
                Sentinel last,
                Context const & context,
                SkipParser const & skip,
                flags flags,
                bool & success) const noexcept
            {
                return {};
            }

            template<
                bool UseCallbacks,
                typename Iter,
                typename Sentinel,
                typename Context,
                typename SkipParser,
                typename Attribute>
            void operator()(
                std::bool_constant<UseCallbacks> use_cbs,
                Iter & first,
                Sentinel last,
                Context const & context,
                SkipParser const & skip,
                flags flags,
                bool & success,
                Attribute & retval) const
            {}
        };

        template<typename Iter, typename Sentinel>
        void
        skip(Iter & first, Sentinel last, null_parser const & skip_, flags f)
        {}

        template<typename Iter, typename Sentinel, typename SkipParser>
        void
        skip(Iter & first, Sentinel last, SkipParser const & skip_, flags f)
        {
            if (!detail::use_skip(f))
                return;
            bool success = true;
            int indent = 0;
            rethrow_error_handler eh;
            nope n;
            symbol_table_tries_t symbol_table_tries;
            auto const context = detail::make_context(
                first, last, success, indent, eh, n, symbol_table_tries);
            while (success) {
                skip_(
                    std::false_type{},
                    first,
                    last,
                    context,
                    skip_skipper{},
                    detail::disable_trace(detail::disable_skip(f)),
                    success);
            }
        }

        enum : int64_t { unbounded = -1 };

        template<typename T>
        std::optional<T> make_parse_result(T & x, bool success)
        {
            std::optional<T> retval;
            if (success)
                retval = x;
            return retval;
        }

        inline bool make_parse_result(nope &, bool success) { return success; }

        template<typename LoType, typename HiType>
        struct char_pair
        {
            LoType lo_;
            HiType hi_;
        };

        template<typename Iter, typename Sentinel>
        struct char_range
        {
            template<typename T>
            friend bool
            operator!=(T c_, char_range<Iter, Sentinel> const & chars)
            {
                if (sizeof(c_) == 4) {
                    auto const cps = text::as_utf32(chars.chars_);
                    using element_type = decltype(*cps.begin());
                    element_type const c = c_;
                    return text::find(cps.begin(), cps.end(), c) == cps.end();
                } else {
                    using element_type = decltype(*chars.chars_.begin());
                    element_type const c = c_;
                    return text::find(
                               chars.chars_.begin(), chars.chars_.end(), c) ==
                           chars.chars_.end();
                }
            }

            view<Iter, Sentinel> chars_;
        };

        template<typename Iter, typename Sentinel>
        auto make_char_range(Iter first, Sentinel last)
        {
            return char_range<Iter, Sentinel>{
                view<Iter, Sentinel>{first, last}};
        }

        template<typename R>
        constexpr auto make_char_range(R && r) noexcept
        {
            if constexpr (std::is_pointer_v<std::decay_t<R>>) {
                return detail::make_char_range(r, text::null_sentinel);
            } else {
                return detail::make_char_range(r.begin(), r.end());
            }
        }

        template<
            typename Context,
            typename CharType,
            typename Expected,
            bool BothIntegral =
                std::is_integral<CharType>{} && std::is_integral<Expected>{}>
        struct unequal_impl
        {
            static bool
            call(Context const & context, CharType c, Expected const & expected)
            {
                return c != detail::resolve(context, expected);
            }
        };

        template<typename Context, typename CharType, typename Expected>
        struct unequal_impl<Context, CharType, Expected, true>
        {
            static bool call(Context const &, CharType c, Expected expected)
            {
                return !common_type_equal{}(c, expected);
            }
        };

        template<typename Context, typename CharType, typename Expected>
        bool unequal(Context const & context, CharType c, Expected expected)
        {
            return unequal_impl<Context, CharType, Expected>::call(
                context, c, expected);
        }

        template<
            typename Context,
            typename CharType,
            typename LoType,
            typename HiType>
        bool unequal(
            Context const & context,
            CharType c,
            char_pair<LoType, HiType> const & expected)
        {
            common_type_less less;
            {
                auto lo = detail::resolve(context, expected.lo_);
                if (less(c, lo))
                    return true;
            }
            {
                auto hi = detail::resolve(context, expected.hi_);
                if (less(hi, c))
                    return true;
            }
            return false;
        }

        template<typename Context, typename CharType>
        bool unequal(Context const &, CharType, nope)
        {
            return false;
        }

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

        template<typename Container>
        constexpr void move_back(Container & c, Container & x)
        {
            c.insert(c.end(), x.begin(), x.end());
        }

        template<typename Container>
        constexpr void move_back(Container & c, std::optional<Container> & x)
        {
            if (x)
                c.insert(c.end(), x->begin(), x->end());
        }

        template<typename Container, typename T>
        constexpr void move_back(Container & c, std::optional<T> & x)
        {
            if (x)
                c.insert(c.end(), std::move(*x));
        }

        template<typename Container, typename T>
        constexpr void move_back(Container & c, std::optional<T> && x)
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

        template<typename T, typename U>
        constexpr void assign_copy(T & t, U const & u)
        {
            t = u;
        }

        template<typename T>
        constexpr void assign_copy(T &, nope)
        {}

        template<
            typename Parser,
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser,
            typename... T>
        void apply_parser(
            Parser const & parser,
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            flags flags,
            bool & success,
            std::optional<std::variant<T...>> & retval)
        {
            using attr_t = decltype(parser.call(
                use_cbs, first, last, context, skip, flags, success));
            if constexpr (std::is_same<
                              attr_t,
                              std::optional<std::variant<T...>>>{}) {
                parser.call(
                    use_cbs,
                    first,
                    last,
                    context,
                    skip,
                    flags,
                    success,
                    retval);
            } else if constexpr (is_nope_v<attr_t>) {
                parser.call(
                    use_cbs, first, last, context, skip, flags, success);
            } else {
                auto attr = parser.call(
                    use_cbs, first, last, context, skip, flags, success);
                if (success)
                    assign(retval, std::variant<T...>(std::move(attr)));
            }
        }

        template<
            typename Parser,
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser,
            typename... T>
        void apply_parser(
            Parser const & parser,
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            flags flags,
            bool & success,
            std::variant<T...> & retval)
        {
            auto attr = parser.call(
                use_cbs, first, last, context, skip, flags, success);
            if (success)
                assign(retval, attr);
        }

        template<
            typename Parser,
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser,
            typename T>
        void apply_parser(
            Parser const & parser,
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            flags flags,
            bool & success,
            std::optional<T> & retval)
        {
            auto attr = parser.call(
                use_cbs, first, last, context, skip, flags, success);
            if (success)
                assign(retval, attr);
        }

        template<
            typename Parser,
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void apply_parser(
            Parser const & parser,
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            flags flags,
            bool & success,
            Attribute & retval)
        {
            parser.call(
                use_cbs, first, last, context, skip, flags, success, retval);
        }



        // API implementations

        template<typename Iter, typename Sentinel, typename Parser>
        auto has_attribute(Iter first, Sentinel last, Parser parser)
        {
            constexpr auto flags = detail::flags::gen_attrs;
            using context = decltype(detail::make_context(
                first,
                last,
                std::declval<bool &>(),
                std::declval<int &>(),
                parser.error_handler_,
                parser.globals_,
                std::declval<detail::symbol_table_tries_t &>()));
            using attr_t = decltype(parser(
                std::false_type{},
                first,
                last,
                std::declval<context>(),
                detail::null_parser{},
                flags,
                std::declval<bool &>()));
            return std::integral_constant<bool, !is_nope_v<attr_t>>{};
        }

        template<typename BaseIter, typename Iter>
        struct scoped_base_assign
        {
            scoped_base_assign(BaseIter & base, Iter & it) :
                base_(base), it_(it)
            {}
            ~scoped_base_assign() { base_ = it_.base(); }

            BaseIter & base_;
            Iter & it_;
        };

        template<
            bool Debug,
            typename Iter,
            typename Sentinel,
            typename Parser,
            typename Attr,
            typename ErrorHandler>
        bool parse_impl(
            Iter & first,
            Sentinel last,
            Parser const & parser,
            ErrorHandler const & error_handler,
            Attr & attr)
        {
            auto const initial_first = first;
            bool success = true;
            int trace_indent = 0;
            detail::symbol_table_tries_t symbol_table_tries;
            auto context = detail::make_context(
                first,
                last,
                success,
                trace_indent,
                error_handler,
                parser.globals_,
                symbol_table_tries);
            auto const flags =
                Debug ? detail::enable_trace(detail::flags::gen_attrs)
                      : detail::flags::gen_attrs;
            try {
                parser(
                    std::false_type{},
                    first,
                    last,
                    context,
                    detail::null_parser{},
                    flags,
                    success,
                    attr);
                if (Debug)
                    detail::final_trace(context, flags, attr);
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
            bool Debug,
            typename Iter,
            typename Sentinel,
            typename Parser,
            typename ErrorHandler>
        auto parse_impl(
            Iter & first,
            Sentinel last,
            Parser const & parser,
            ErrorHandler const & error_handler)
        {
            auto const initial_first = first;
            bool success = true;
            int trace_indent = 0;
            detail::symbol_table_tries_t symbol_table_tries;
            auto context = detail::make_context(
                first,
                last,
                success,
                trace_indent,
                error_handler,
                parser.globals_,
                symbol_table_tries);
            auto const flags =
                Debug ? detail::enable_trace(detail::flags::gen_attrs)
                      : detail::flags::gen_attrs;
            using attr_t = decltype(parser(
                std::false_type{},
                first,
                last,
                context,
                detail::null_parser{},
                flags,
                success));
            try {
                attr_t attr_ = parser(
                    std::false_type{},
                    first,
                    last,
                    context,
                    detail::null_parser{},
                    flags,
                    success);
                if (Debug)
                    detail::final_trace(context, flags, nope{});
                return detail::make_parse_result(attr_, success);
            } catch (parse_error<Iter> const & e) {
                if (error_handler(initial_first, last, e) ==
                    error_handler_result::rethrow) {
                    throw;
                }
                attr_t attr_{};
                return detail::make_parse_result(attr_, false);
            }
        }

        template<
            bool Debug,
            typename Iter,
            typename Sentinel,
            typename Parser,
            typename ErrorHandler,
            typename Callbacks>
        bool callback_parse_impl(
            Iter & first,
            Sentinel last,
            Parser const & parser,
            ErrorHandler const & error_handler,
            Callbacks const & callbacks)
        {
            auto const initial_first = first;
            bool success = true;
            int trace_indent = 0;
            detail::symbol_table_tries_t symbol_table_tries;
            auto context = detail::make_context(
                first,
                last,
                success,
                trace_indent,
                error_handler,
                callbacks,
                parser.globals_,
                symbol_table_tries);
            auto const flags =
                Debug ? detail::enable_trace(detail::flags::gen_attrs)
                      : detail::flags::gen_attrs;
            try {
                parser(
                    std::true_type{},
                    first,
                    last,
                    context,
                    detail::null_parser{},
                    flags,
                    success);
                if (Debug)
                    detail::final_trace(context, flags, nope{});
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
            bool Debug,
            typename Iter,
            typename Sentinel,
            typename Parser,
            typename SkipParser,
            typename Attr,
            typename ErrorHandler>
        bool skip_parse_impl(
            Iter & first,
            Sentinel last,
            Parser const & parser,
            SkipParser const & skip,
            ErrorHandler const & error_handler,
            Attr & attr)
        {
            auto const initial_first = first;
            bool success = true;
            int trace_indent = 0;
            detail::symbol_table_tries_t symbol_table_tries;
            auto context = detail::make_context(
                first,
                last,
                success,
                trace_indent,
                error_handler,
                parser.globals_,
                symbol_table_tries);
            auto const flags =
                Debug ? detail::enable_trace(detail::default_flags())
                      : detail::default_flags();
            detail::skip(first, last, skip, flags);
            try {
                parser(
                    std::false_type{},
                    first,
                    last,
                    context,
                    skip,
                    flags,
                    success,
                    attr);
                detail::skip(first, last, skip, flags);
                if (Debug)
                    detail::final_trace(context, flags, attr);
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
            bool Debug,
            typename Iter,
            typename Sentinel,
            typename Parser,
            typename SkipParser,
            typename ErrorHandler>
        auto skip_parse_impl(
            Iter & first,
            Sentinel last,
            Parser const & parser,
            SkipParser const & skip,
            ErrorHandler const & error_handler)
        {
            auto const initial_first = first;
            bool success = true;
            int trace_indent = 0;
            detail::symbol_table_tries_t symbol_table_tries;
            auto context = detail::make_context(
                first,
                last,
                success,
                trace_indent,
                error_handler,
                parser.globals_,
                symbol_table_tries);
            auto const flags =
                Debug ? detail::enable_trace(detail::default_flags())
                      : detail::default_flags();
            detail::skip(first, last, skip, flags);
            using attr_t = decltype(parser(
                std::false_type{}, first, last, context, skip, flags, success));
            try {
                attr_t attr_ = parser(
                    std::false_type{},
                    first,
                    last,
                    context,
                    skip,
                    flags,
                    success);
                detail::skip(first, last, skip, flags);
                if (Debug)
                    detail::final_trace(context, flags, nope{});
                return detail::make_parse_result(attr_, success);
            } catch (parse_error<Iter> const & e) {
                if (error_handler(initial_first, last, e) ==
                    error_handler_result::rethrow) {
                    throw;
                }
                attr_t attr_{};
                return detail::make_parse_result(attr_, false);
            }
        }

        template<
            bool Debug,
            typename Iter,
            typename Sentinel,
            typename Parser,
            typename SkipParser,
            typename ErrorHandler,
            typename Callbacks>
        bool callback_skip_parse_impl(
            Iter & first,
            Sentinel last,
            Parser const & parser,
            SkipParser const & skip,
            ErrorHandler const & error_handler,
            Callbacks const & callbacks)
        {
            auto const initial_first = first;
            bool success = true;
            int trace_indent = 0;
            detail::symbol_table_tries_t symbol_table_tries;
            auto context = detail::make_context(
                first,
                last,
                success,
                trace_indent,
                error_handler,
                callbacks,
                parser.globals_,
                symbol_table_tries);
            auto const flags =
                Debug ? detail::enable_trace(detail::default_flags())
                      : detail::default_flags();
            detail::skip(first, last, skip, flags);
            try {
                parser(
                    std::true_type{},
                    first,
                    last,
                    context,
                    skip,
                    flags,
                    success);
                detail::skip(first, last, skip, flags);
                if (Debug)
                    detail::final_trace(context, flags, nope{});
                return success;
            } catch (parse_error<Iter> const & e) {
                if (error_handler(initial_first, last, e) ==
                    error_handler_result::rethrow) {
                    throw;
                }
                return false;
            }
        }

        template<typename I, typename S>
        text::utf32_view<I, S>
        remove_utf32_terminator(text::utf32_view<I, S> view)
        {
            return view;
        }
        template<typename I>
        text::utf32_view<I> remove_utf32_terminator(text::utf32_view<I> view)
        {
            if (!view.empty() && view.back() == 0) {
                return text::utf32_view<I>(
                    view.begin(),
#if BOOST_PARSER_USE_CONCEPTS
                    std::ranges::prev(view.end())
#else
                    std::prev(view.end())
#endif
                );
            }
            return view;
        }
        template<typename R>
        auto as_utf32_no_terminator(R & r)
            -> decltype(detail::remove_utf32_terminator(text::as_utf32(r)))
        {
            return detail::remove_utf32_terminator(text::as_utf32(r));
        }

        template<typename R>
        constexpr auto make_input_view(R && r) noexcept
        {
            if constexpr (non_unicode_char_range_like<remove_cv_ref_t<R>>) {
                if constexpr (utf8_pointer<remove_cv_ref_t<R>>) {
                    return parser::make_view(r, text::null_sentinel);
                } else if constexpr (std::is_array_v<remove_cv_ref_t<R>>) {
                    auto first = std::begin(r);
                    auto last = std::end(r);
                    if (first != last) {
                        if (*
#if BOOST_PARSER_USE_CONCEPTS
                            std::ranges::prev(last)
#else
                            std::prev(last)
#endif

                            == 0) {
                            --last;
                        }
                    }
                    return parser::make_view(first, last);
                } else {
                    return parser::make_view(std::begin(r), std::end(r));
                }
            } else {
                auto r_ = detail::as_utf32_no_terminator(r);
                return parser::make_view(r_.begin(), r_.end());
            }
        }

        template<typename R>
        constexpr auto make_view_begin(R & r) noexcept
        {
            if constexpr (std::is_pointer_v<std::decay_t<R>>) {
                return r;
            } else {
                return std::begin(r);
            }
        }

        template<typename R>
        constexpr auto make_view_end(R & r) noexcept
        {
            if constexpr (std::is_pointer_v<std::decay_t<R>>) {
                return text::null_sentinel;
            } else {
                return std::end(r);
            }
        }

        template<
            typename Iter1,
            typename Sentinel1,
            typename Iter2,
            typename Sentinel2,
            typename Pred>
        std::pair<Iter1, Iter2> mismatch(
            Iter1 first1,
            Sentinel1 last1,
            Iter2 first2,
            Sentinel2 last2,
            Pred pred)
        {
            std::pair<Iter1, Iter2> retval{first1, first2};
            while (retval.first != last1 && retval.second != last2 &&
                   pred(*retval.first, *retval.second)) {
                ++retval.first;
                ++retval.second;
            }
            return retval;
        }

        template<
            typename Iter1,
            typename Sentinel1,
            typename Iter2,
            typename Sentinel2>
        std::pair<Iter1, Iter2>
        mismatch(Iter1 first1, Sentinel1 last1, Iter2 first2, Sentinel2 last2)
        {
            return detail::mismatch(
                first1, last1, first2, last2, common_type_equal{});
        }

        template<typename I, typename S, typename T>
        std::optional<T>
        if_full_parse(I & first, S last, std::optional<T> retval)
        {
            if (first != last)
                retval = std::nullopt;
            return retval;
        }
        template<typename I, typename S>
        bool if_full_parse(I & first, S last, bool retval)
        {
            if (first != last)
                retval = false;
            return retval;
        }
    }


    template<typename Context>
    decltype(auto) _val(Context const & context)
    {
        if constexpr (detail::is_nope_v<decltype(*context.val_)>)
            return none{};
        else
            return *context.val_;
    }

    template<typename Context>
    decltype(auto) _attr(Context const & context)
    {
        if constexpr (detail::is_nope_v<decltype(*context.attr_)>)
            return none{};
        else
            return *context.attr_;
    }

    template<typename Context>
    decltype(auto) _where(Context const & context)
    {
        return *context.where_;
    }

    template<typename Context>
    decltype(auto) _begin(Context const & context)
    {
        return context.first_;
    }

    template<typename Context>
    decltype(auto) _end(Context const & context)
    {
        return context.last_;
    }

    template<typename Context>
    decltype(auto) _pass(Context const & context)
    {
        return *context.pass_;
    }

    template<typename Context>
    decltype(auto) _locals(Context const & context)
    {
        if constexpr (detail::is_nope_v<decltype(*context.locals_)>)
            return none{};
        else
            return *context.locals_;
    }

    template<typename Context>
    decltype(auto) _params(Context const & context)
    {
        if constexpr (detail::is_nope_v<decltype(*context.params_)>)
            return none{};
        else
            return *context.params_;
    }

    template<typename Context>
    decltype(auto) _globals(Context const & context)
    {
        if constexpr (detail::is_nope_v<decltype(*context.globals_)>)
            return none{};
        else
            return *context.globals_;
    }

    template<typename Context>
    decltype(auto) _error_handler(Context const & context)
    {
        return *context.error_handler_;
    }

#if BOOST_PARSER_USE_CONCEPTS
    template<std::forward_iterator I, typename Context>
#else
    template<typename I, typename Context>
#endif
    void
    _report_error(Context const & context, std::string_view message, I location)
    {
        return context.error_handler_->diagnose(
            diagnostic_kind::error, message, context, location);
    }

    template<typename Context>
    void _report_error(Context const & context, std::string_view message)
    {
        return context.error_handler_->diagnose(
            diagnostic_kind::error, message, context);
    }

#if BOOST_PARSER_USE_CONCEPTS
    template<std::forward_iterator I, typename Context>
#else
    template<typename I, typename Context>
#endif
    void _report_warning(
        Context const & context, std::string_view message, I location)
    {
        return context.error_handler_->diagnose(
            diagnostic_kind::warning, message, context, location);
    }

    template<typename Context>
    void _report_warning(Context const & context, std::string_view message)
    {
        return context.error_handler_->diagnose(
            diagnostic_kind::warning, message, context);
    }

    /** An invocable that returns the `I`th parameter to the bottommost rule.
        This is useful for forwarding parameters to sub-rules. */
    template<unsigned int I>
    inline constexpr detail::param_t<I> _p = {};



    // Second order parsers.

    /** A very large sentinel value used to represent pseudo-infinity. */
    int64_t const Inf = detail::unbounded;

    template<
        typename Parser,
        typename DelimiterParser,
        typename MinType,
        typename MaxType>
    struct repeat_parser
    {
        constexpr repeat_parser(
            Parser parser,
            MinType _min,
            MaxType _max,
            DelimiterParser delimiter_parser = DelimiterParser{}) :
            parser_(parser),
            delimiter_parser_(delimiter_parser),
            min_(_min),
            max_(_max)
        {}

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser>
        auto call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            using attr_t = decltype(parser_.call(
                use_cbs, first, last, context, skip, flags, success));
            detail::sequence_of<attr_t> retval;
            call(use_cbs, first, last, context, skip, flags, success, retval);
            return retval;
        }

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = detail::scoped_trace(
                *this,
                first,
                last,
                context,
                detail::in_apply_parser(flags) ? detail::disable_trace(flags)
                                               : flags,
                retval);

            using attr_t = decltype(parser_.call(
                use_cbs, first, last, context, skip, flags, success));
            if constexpr (
                detail::is_variant<Attribute>{} ||
                detail::is_optional<Attribute>{}) {
                detail::apply_parser(
                    *this,
                    use_cbs,
                    first,
                    last,
                    context,
                    skip,
                    detail::set_in_apply_parser(flags),
                    success,
                    retval);
            } else if constexpr (container<attr_t>) {
                int64_t count = 0;

                for (int64_t end = detail::resolve(context, min_); count != end;
                     ++count) {
                    detail::skip(first, last, skip, flags);
                    parser_.call(
                        use_cbs,
                        first,
                        last,
                        context,
                        skip,
                        flags,
                        success,
                        retval);
                    if (!success) {
                        detail::assign(retval, Attribute());
                        return;
                    }
                }

                int64_t const end = detail::resolve(context, max_);

                // It looks like you've created a repeated epsilon parser, by
                // writing "*eps", "+eps", "repeat(2, Inf)[eps]", or similar.
                BOOST_PARSER_DEBUG_ASSERT(
                    !detail::is_unconditional_eps<Parser>{} || end < Inf);

                for (; count != end; ++count) {
                    auto const prev_first = first;
                    // This is only ever used in delimited_parser, which
                    // always has a min=1; we therefore know we're after a
                    // previous element when this executes.
                    if constexpr (!detail::is_nope_v<DelimiterParser>) {
                        detail::skip(first, last, skip, flags);
                        delimiter_parser_.call(
                            use_cbs,
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
                        use_cbs,
                        first,
                        last,
                        context,
                        skip,
                        flags,
                        success,
                        retval);
                    if (!success) {
                        success = true;
                        first = prev_first;
                        break;
                    }
                }
            } else {
                attr_t attr{};
                int64_t count = 0;

                for (int64_t end = detail::resolve(context, min_); count != end;
                     ++count) {
                    detail::skip(first, last, skip, flags);
                    if (detail::gen_attrs(flags)) {
                        attr = parser_.call(
                            use_cbs,
                            first,
                            last,
                            context,
                            skip,
                            flags,
                            success);
                    } else {
                        parser_.call(
                            use_cbs,
                            first,
                            last,
                            context,
                            skip,
                            flags,
                            success);
                    }
                    if (!success) {
                        detail::assign(retval, Attribute());
                        return;
                    }
                    detail::append(
                        retval, std::move(attr), detail::gen_attrs(flags));
                }

                int64_t const end = detail::resolve(context, max_);

                // It looks like you've created a repeated epsilon parser, by
                // writing "*eps", "+eps", "repeat(2, Inf)[eps]", or similar.
                BOOST_PARSER_DEBUG_ASSERT(
                    !detail::is_unconditional_eps<Parser>{} || end < Inf);

                for (; count != end; ++count) {
                    auto const prev_first = first;
                    if constexpr (!detail::is_nope_v<DelimiterParser>) {
                        detail::skip(first, last, skip, flags);
                        delimiter_parser_.call(
                            use_cbs,
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
                    if (detail::gen_attrs(flags)) {
                        attr = parser_.call(
                            use_cbs,
                            first,
                            last,
                            context,
                            skip,
                            flags,
                            success);
                    } else {
                        parser_.call(
                            use_cbs,
                            first,
                            last,
                            context,
                            skip,
                            flags,
                            success);
                    }
                    if (!success) {
                        success = true;
                        first = prev_first;
                        break;
                    }
                    detail::append(
                        retval, std::move(attr), detail::gen_attrs(flags));
                }
            }
        }

        Parser parser_;
        DelimiterParser delimiter_parser_;
        MinType min_;
        MaxType max_;
    };

    /** A simplified `repeat_parser` that applies `parser` zero or more
        times.  */
    template<typename Parser>
    struct zero_plus_parser : repeat_parser<Parser>
    {
        constexpr zero_plus_parser(Parser parser) :
            repeat_parser<Parser>(parser, 0, Inf)
        {}
    };

    /** A simplified `repeat_parser` that applies `parser` one or more
        times.  */
    template<typename Parser>
    struct one_plus_parser : repeat_parser<Parser>
    {
        constexpr one_plus_parser(Parser parser) :
            repeat_parser<Parser>(parser, 1, Inf)
        {}
    };

    /** A simplified `repeat_parser` that applies `parser` zero or more times,
        with `delimiter_parser` applied before each application of `parser`
        after the first.  */
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
        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser>
        auto call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            using attr_t = decltype(parser_.call(
                use_cbs, first, last, context, skip, flags, success));
            detail::optional_of<attr_t> retval;
            call(use_cbs, first, last, context, skip, flags, success, retval);
            return retval;
        }

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = detail::scoped_trace(
                *this, first, last, context, flags, retval);

            detail::skip(first, last, skip, flags);

            if (!detail::gen_attrs(flags)) {
                parser_.call(
                    use_cbs, first, last, context, skip, flags, success);
                success = true;
                return;
            }

            parser_.call(
                use_cbs, first, last, context, skip, flags, success, retval);
            success = true;
        }

        Parser parser_;
    };

    template<typename ParserTuple>
    struct or_parser
    {
        constexpr or_parser(ParserTuple parsers) : parsers_(parsers) {}

#ifndef BOOST_PARSER_DOXYGEN

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser>
        struct use_parser_t
        {
            use_parser_t(
                Iter & first,
                Sentinel last,
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
                    std::bool_constant<UseCallbacks>{},
                    first_,
                    last_,
                    context_,
                    skip_,
                    flags_,
                    success_);
            }

            template<typename Parser, typename Attribute>
            void operator()(Parser const & parser, Attribute & retval) const
            {
                detail::skip(first_, last_, skip_, flags_);
                success_ = true; // In case someone earlier already failed...

                detail::apply_parser(
                    parser,
                    std::bool_constant<UseCallbacks>{},
                    first_,
                    last_,
                    context_,
                    skip_,
                    flags_,
                    success_,
                    retval);
            }

            Iter & first_;
            Sentinel last_;
            Context const & context_;
            SkipParser const & skip_;
            detail::flags flags_;
            bool & success_;
        };

#endif

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser>
        auto call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            use_parser_t<
                UseCallbacks,
                Iter,
                Sentinel,
                Context,
                SkipParser> const
                use_parser(first, last, context, skip, flags, success);

            // A result type for each of the parsers in parsers_.
            using all_types =
                decltype(detail::hl::transform(parsers_, use_parser));

            // Same as above, wrapped in detail::wrapper.
            using all_types_wrapped =
                decltype(detail::hl::transform(all_types{}, detail::wrap{}));

            // Returns a tuple<> containing two things: 1) A tuple of only the
            // unique wrapped types from above, without nopes; this may be
            // empty. 2) std::true_type or std::false_type indicating whether
            // nopes were found; if so, the final result is an optional.
            auto append_unique = [](auto result, auto x) {
                using x_type = typename decltype(x)::type;
                if constexpr (detail::is_nope_v<x_type>) {
                    return detail::hl::make_pair(
                        detail::hl::first(result), std::true_type{});
                } else if constexpr (detail::hl::contains(
                                         detail::hl::first(result), x)) {
                    return result;
                } else {
                    return detail::hl::make_pair(
                        detail::hl::append(detail::hl::first(result), x),
                        detail::hl::second(result));
                }
            };
            using wrapped_unique_types = decltype(detail::hl::fold_left(
                all_types_wrapped{},
                detail::hl::make_pair(tuple<>{}, std::false_type{}),
                append_unique));

            // Same as above, with the tuple types unwrapped.
            using unwrapped_types = decltype(detail::hl::make_pair(
                detail::hl::transform(
                    detail::hl::first(wrapped_unique_types{}),
                    detail::unwrap{}),
                detail::hl::second(wrapped_unique_types{})));

            // Types above converted to a "variant", which may actually be a
            // non-variant type T if that is the only unique non-nope type, or a
            // nope if unwrapped_types is empty.
            using result_t = detail::to_hana_tuple_or_type_t<unwrapped_types>;

            result_t retval;
            call(use_cbs, first, last, context, skip, flags, success, retval);
            return retval;
        }

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = detail::scoped_trace(
                *this, first, last, context, flags, retval);

            use_parser_t<
                UseCallbacks,
                Iter,
                Sentinel,
                Context,
                SkipParser> const
                use_parser(first, last, context, skip, flags, success);

            bool done = false;
            auto try_parser = [use_parser, &success, flags, &retval, &done](
                                  auto const & parser) {
                if (done)
                    return;
                if (detail::gen_attrs(flags)) {
                    use_parser(parser, retval);
                    if (!success)
                        detail::assign(retval, Attribute());
                } else {
                    use_parser(parser);
                }
                if (success)
                    done = true;
            };
            detail::hl::for_each(parsers_, try_parser);

            if (!done)
                success = false;
        }

#ifndef BOOST_PARSER_DOXYGEN

        template<typename Parser>
        constexpr auto prepend(parser_interface<Parser> parser) const noexcept;
        template<typename Parser>
        constexpr auto append(parser_interface<Parser> parser) const noexcept;

#endif

        ParserTuple parsers_;
    };

    template<typename ParserTuple, typename BacktrackingTuple>
    struct seq_parser
    {
        using backtracking = BacktrackingTuple;

        constexpr seq_parser(ParserTuple parsers) : parsers_(parsers) {}

#ifndef BOOST_PARSER_DOXYGEN

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser>
        struct dummy_use_parser_t
        {
            dummy_use_parser_t(
                Iter & first,
                Sentinel last,
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
                    std::bool_constant<UseCallbacks>{},
                    first_,
                    last_,
                    context_,
                    skip_,
                    flags_,
                    success_);
            }
            Iter & first_;
            Sentinel last_;
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
                auto result = detail::hl::first(result_and_indices);
                using result_back_type = typename std::decay_t<decltype(
                    detail::hl::back(result))>::type;
                using unwrapped_optional_result_back_type =
                    detail::unwrapped_optional_t<result_back_type>;

                auto indices = detail::hl::second(result_and_indices);

                using x_type = typename decltype(x)::type;
                using unwrapped_optional_x_type =
                    detail::unwrapped_optional_t<x_type>;

                if constexpr (detail::is_nope_v<x_type>) {
                    // T >> nope -> T
                    return detail::hl::make_pair(
                        result,
                        detail::hl::append(
                            indices, detail::hl::size_minus_one(result)));
                } else if constexpr (
                    std::is_same<result_back_type, x_type>{} ||
                    std::is_same<
                        result_back_type,
                        unwrapped_optional_x_type>{}) {
                    if constexpr (container<result_back_type>) {
                        // C<T> >> C<T> -> C<T>
                        return detail::hl::make_pair(
                            result,
                            detail::hl::append(
                                indices, detail::hl::size_minus_one(result)));
                    } else {
                        // T >> T -> vector<T>
                        return detail::hl::make_pair(
                            detail::hl::append(
                                detail::hl::drop_back(result),
                                detail::wrapper<
                                    std::vector<result_back_type>>{}),
                            detail::hl::append(
                                indices, detail::hl::size_minus_one(result)));
                    }
                } else if constexpr (
                    detail::
                        container_and_value_type<result_back_type, x_type> ||
                    detail::container_and_value_type<
                        result_back_type,
                        unwrapped_optional_x_type>) {
                    // C<T> >> T -> C<T>
                    // C<T> >> optional<T> -> C<T>
                    return detail::hl::make_pair(
                        result,
                        detail::hl::append(
                            indices, detail::hl::size_minus_one(result)));
                } else if constexpr (
                    detail::
                        container_and_value_type<x_type, result_back_type> ||
                    detail::container_and_value_type<
                        x_type,
                        unwrapped_optional_result_back_type>) {
                    // T >> C<T> -> C<T>
                    // optional<T> >> C<T> -> C<T>
                    return detail::hl::make_pair(
                        detail::hl::append(detail::hl::drop_back(result), x),
                        detail::hl::append(
                            indices, detail::hl::size_minus_one(result)));
                } else if constexpr (detail::is_nope_v<result_back_type>) {
                    // tuple<nope> >> T -> tuple<T>
                    return detail::hl::make_pair(
                        detail::hl::append(detail::hl::drop_back(result), x),
                        detail::hl::append(
                            indices, detail::hl::size_minus_one(result)));
                } else {
                    // tuple<Ts...> >> T -> tuple<Ts..., T>
                    return detail::hl::make_pair(
                        detail::hl::append(result, x),
                        detail::hl::append(indices, detail::hl::size(result)));
                }
            }
        };

        // Returns the tuple of values produced by this parser, and the
        // indices into that tuple that each parser should use in turn.  The
        // case where the tuple only has one element is handled elsewhere.
        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser>
        auto make_temp_result(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            dummy_use_parser_t<
                UseCallbacks,
                Iter,
                Sentinel,
                Context,
                SkipParser> const
                dummy_use_parser(first, last, context, skip, flags, success);

            // A result type for each of the parsers in parsers_.
            using all_types =
                decltype(detail::hl::transform(parsers_, dummy_use_parser));

            // Same as above, wrapped in detail::wrapper.
            using all_types_wrapped =
                decltype(detail::hl::transform(all_types{}, detail::wrap{}));

            // Generate a tuple of outputs, and the index that each parser
            // should use to write into its output.
            constexpr auto combine_start = detail::hl::make_pair(
                detail::hl::make_tuple(detail::hl::front(all_types_wrapped{})),
                tuple<llong<0>>{});
            using combined_types = decltype(detail::hl::fold_left(
                detail::hl::drop_front(all_types_wrapped{}),
                combine_start,
                combine{}));

            // Unwrap the result tuple's types.
            using result_type = decltype(detail::hl::transform(
                detail::hl::first(combined_types{}), detail::unwrap{}));

            return detail::hl::make_pair(
                result_type(), detail::hl::second(combined_types{}));
        }

#endif

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser>
        auto call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first_,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            Iter first = first_;

            std::decay_t<decltype(detail::hl::first(make_temp_result(
                use_cbs, first, last, context, skip, flags, success)))>
                retval;

            auto _ = detail::scoped_trace(
                *this,
                first_,
                last,
                context,
                detail::in_apply_parser(flags) ? detail::disable_trace(flags)
                                               : flags,
                retval);

            std::decay_t<decltype(detail::hl::second(make_temp_result(
                use_cbs, first, last, context, skip, flags, success)))>
                indices;
            call_impl(
                use_cbs,
                first,
                last,
                context,
                skip,
                flags,
                success,
                retval,
                indices);

            if (success)
                first_ = first;

            // A 1-tuple is converted to a scalar.
            if constexpr (detail::hl::size(retval) == llong<1>{}) {
                using namespace literals;
                return parser::get(retval, 0_c);
            } else {
                return retval;
            }
        }

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first_,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = detail::scoped_trace(
                *this,
                first_,
                last,
                context,
                detail::in_apply_parser(flags) ? detail::disable_trace(flags)
                                               : flags,
                retval);

            Iter first = first_;

            std::decay_t<decltype(detail::hl::second(make_temp_result(
                use_cbs, first, last, context, skip, flags, success)))>
                indices;
            if constexpr (detail::is_variant<Attribute>{}) {
                detail::apply_parser(
                    *this,
                    use_cbs,
                    first,
                    last,
                    context,
                    skip,
                    detail::set_in_apply_parser(flags),
                    success,
                    retval);
            } else if constexpr (detail::is_optional<Attribute>{}) {
                typename Attribute::value_type attr;
                call(
                    use_cbs, first_, last, context, skip, flags, success, attr);
                if (success)
                    detail::assign(retval, attr);
            } else if constexpr (detail::is_tuple<Attribute>{}) {
                call_impl(
                    use_cbs,
                    first,
                    last,
                    context,
                    skip,
                    flags,
                    success,
                    retval,
                    indices);

                if (!success || !detail::gen_attrs(flags))
                    detail::assign(retval, Attribute());
            } else {
                // call_impl requires a tuple, so we must wrap this scalar.
                tuple<Attribute> temp_retval;
                call_impl(
                    use_cbs,
                    first,
                    last,
                    context,
                    skip,
                    flags,
                    success,
                    temp_retval,
                    indices);

                if (success && detail::gen_attrs(flags))
                    detail::assign(retval, detail::hl::front(temp_retval));
            }

            if (success)
                first_ = first;
        }

#ifndef BOOST_PARSER_DOXYGEN

        // Invokes each parser, placing the resulting values (if any) into
        // retval, using the index mapping in indices.  The case of a tuple
        // containing only a single value is handled elsewhere.
        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser,
            typename Attribute,
            typename Indices>
        void call_impl(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval,
            Indices const & indices) const
        {
            static_assert(detail::is_tuple<Attribute>{}, "");

            auto use_parser = [use_cbs,
                               &first,
                               last,
                               &context,
                               &skip,
                               flags,
                               &success,
                               &retval](
                                  auto const & parser_index_and_backtrack) {
                using namespace literals;
                detail::skip(first, last, skip, flags);
                if (!success) // Someone earlier already failed...
                    return;

                auto const & parser =
                    parser::get(parser_index_and_backtrack, 0_c);
                bool const can_backtrack =
                    parser::get(parser_index_and_backtrack, 2_c);

                if (!detail::gen_attrs(flags)) {
                    parser.call(
                        use_cbs, first, last, context, skip, flags, success);
                    if (!success && !can_backtrack) {
                        std::stringstream oss;
                        detail::print_parser(context, parser, oss);
                        throw parse_error<Iter>(first, oss.str());
                    }
                    return;
                }

                auto & out = parser::get(
                    retval, parser::get(parser_index_and_backtrack, 1_c));

                using attr_t = decltype(parser.call(
                    use_cbs, first, last, context, skip, flags, success));
                constexpr bool out_container =
                    container<std::decay_t<decltype(out)>>;
                constexpr bool attr_container = container<attr_t>;

                if constexpr (out_container == attr_container) {
                    // TODO: Document that the user can pass anything she
                    // likes for retval, but that if retval is not a
                    // container, but the default retval would have been,
                    // weird assignments may occur.  For instance,
                    // parse(first, last, char_ >> char_, a), where 'a' is
                    // a boost::any, will only yeild a single char in the
                    // any.
                    parser.call(
                        use_cbs,
                        first,
                        last,
                        context,
                        skip,
                        flags,
                        success,
                        out);
                    if (!success) {
                        if (!can_backtrack) {
                            std::stringstream oss;
                            detail::print_parser(context, parser, oss);
                            throw parse_error<Iter>(first, oss.str());
                        }
                        out = std::decay_t<decltype(out)>();
                        return;
                    }
                } else {
                    attr_t x = parser.call(
                        use_cbs, first, last, context, skip, flags, success);
                    if (!success) {
                        if (!can_backtrack) {
                            std::stringstream oss;
                            detail::print_parser(context, parser, oss);
                            throw parse_error<Iter>(first, oss.str());
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
                detail::hl::zip(parsers_, indices, backtracking{});
            detail::hl::for_each(parsers_and_indices, use_parser);
        }

        template<bool AllowBacktracking, typename Parser>
        constexpr auto prepend(parser_interface<Parser> parser) const noexcept;
        template<bool AllowBacktracking, typename Parser>
        constexpr auto append(parser_interface<Parser> parser) const noexcept;

#endif

        ParserTuple parsers_;
    };

    template<typename Parser, typename Action>
    struct action_parser
    {
        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser>
        detail::nope call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            detail::nope retval;
            call(use_cbs, first, last, context, skip, flags, success, retval);
            return retval;
        }

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = detail::scoped_trace(
                *this, first, last, context, flags, retval);

            auto const initial_first = first;
            auto attr = parser_.call(
                use_cbs,
                first,
                last,
                context,
                skip,
                detail::enable_attrs(flags),
                success);
            view const where(initial_first, first);
            if (success) {
                auto const action_context =
                    detail::make_action_context(context, attr, where);
                action_(action_context);
            }
        }

        Parser parser_;
        Action action_;
    };

    template<typename Parser>
    struct omit_parser
    {
        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser>
        detail::nope call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            auto _ = detail::scoped_trace(
                *this, first, last, context, flags, detail::global_nope);

            parser_.call(
                use_cbs,
                first,
                last,
                context,
                skip,
                detail::disable_attrs(flags),
                success);
            return {};
        }

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = detail::scoped_trace(
                *this, first, last, context, flags, retval);

            parser_.call(
                use_cbs,
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
        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser>
        view<Iter> call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            view<Iter> retval;
            call(
                use_cbs,
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
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = detail::scoped_trace(
                *this, first, last, context, flags, retval);

            auto const initial_first = first;
            parser_.call(
                use_cbs,
                first,
                last,
                context,
                skip,
                detail::disable_attrs(flags),
                success);
            detail::assign(retval, view<Iter>(initial_first, first));
        }

        Parser parser_;
    };

#if defined(BOOST_PARSER_DOXYGEN) || defined(__cpp_lib_concepts)
    template<typename Parser>
    struct string_view_parser
    {
        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser>
        auto call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            auto r = parser::detail::text::detail::unpack_iterator_and_sentinel(
                first, last);
            // string_view_parser and the string_view[] directive that uses it
            // requires that the underlying char sequence being parsed be a
            // contiguous range.  If you're seeing this static_assert, you
            // have not met this contract.
            static_assert(std::contiguous_iterator<decltype(r.f_)>);
            using char_type = detail::remove_cv_ref_t<decltype(*r.f_)>;
            std::basic_string_view<char_type> retval;
            call(
                use_cbs,
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
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = detail::scoped_trace(
                *this, first, last, context, flags, retval);

            auto const initial_first = first;
            parser_.call(
                use_cbs,
                first,
                last,
                context,
                skip,
                detail::disable_attrs(flags),
                success);

            auto r = parser::detail::text::detail::unpack_iterator_and_sentinel(
                initial_first, first);
            // string_view_parser and the string_view[] directive that uses it
            // requires that the underlying char sequence being parsed be a
            // contiguous range.  If you're seeing this static_assert, you
            // have not met this contract.
            static_assert(std::contiguous_iterator<decltype(r.f_)>);
            using char_type = detail::remove_cv_ref_t<decltype(*r.f_)>;
            if (initial_first == first) {
                detail::assign(retval, std::basic_string_view<char_type>{});
            } else {
                detail::assign(
                    retval,
                    std::basic_string_view<char_type>{
                        &*r.f_, std::size_t(r.l_ - r.f_)});
            }
        }

        Parser parser_;
    };
#endif

    template<typename Parser>
    struct lexeme_parser
    {
        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser>
        auto call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            using attr_t = decltype(parser_.call(
                use_cbs, first, last, context, skip, flags, success));
            attr_t retval{};
            call(
                use_cbs,
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
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = detail::scoped_trace(
                *this, first, last, context, flags, retval);

            parser_.call(
                use_cbs,
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
        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser_>
        auto call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser_ const & skip,
            detail::flags flags,
            bool & success) const
        {
            using attr_t = decltype(parser_.call(
                use_cbs, first, last, context, skip, flags, success));
            attr_t retval{};
            call(
                use_cbs,
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
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser_,
            typename Attribute>
        void call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser_ const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = detail::scoped_trace(
                *this, first, last, context, flags, retval);

            if constexpr (detail::is_nope_v<SkipParser>) {
                parser_.call(
                    use_cbs,
                    first,
                    last,
                    context,
                    skip,
                    detail::enable_skip(flags),
                    success,
                    retval);
            } else {
                parser_.call(
                    use_cbs,
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
        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser>
        detail::nope call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            detail::nope retval;
            call(
                use_cbs,
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
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = detail::scoped_trace(
                *this, first, last, context, flags, retval);

            auto first_copy = first;
            parser_.call(
                use_cbs,
                first_copy,
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

    template<typename T>
    struct symbol_parser
    {
        symbol_parser() : copied_from_(nullptr) {}
        symbol_parser(symbol_parser const & other) :
            initial_elements_(other.initial_elements_),
            copied_from_(other.copied_from_ ? other.copied_from_ : &other)
        {}

        /** Uses UTF-8 string `str` to look up an attribute in the table
            during parsing, returning it as an optional reference.  The lookup
            is done on the copy of the symbol table inside the parse context
            `context`. */
        template<typename Context>
        parser::detail::text::optional_ref<T>
        find(Context const & context, std::string_view str) const
        {
            parser::detail::text::trie<std::vector<uint32_t>, T> & trie_ =
                detail::get_trie(context, ref());
            return trie_[parser::detail::text::as_utf32(str)];
        }

        /** Inserts an entry consisting of a UTF-8 string `str` to match, and
            an associtated attribute `x`, to the copy of the symbol table
            inside the parse context `context`. */
        template<typename Context>
        void insert(Context const & context, std::string_view str, T && x) const
        {
            parser::detail::text::trie<std::vector<uint32_t>, T> & trie_ =
                detail::get_trie(context, ref());
            trie_.insert(parser::detail::text::as_utf32(str), std::move(x));
        }

        /** Erases the entry whose UTF-8 match string is `str` from the copy
            of the symbol table inside the parse context `context`. */
        template<typename Context>
        void erase(Context const & context, std::string_view str) const
        {
            parser::detail::text::trie<std::vector<uint32_t>, T> & trie_ =
                detail::get_trie(context, ref());
            trie_.erase(parser::detail::text::as_utf32(str));
        }

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser>
        T call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            T retval;
            call(use_cbs, first, last, context, skip, flags, success, retval);
            return retval;
        }

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = detail::scoped_trace(
                *this, first, last, context, flags, retval);

            parser::detail::text::trie<std::vector<uint32_t>, T> const & trie_ =
                detail::get_trie(context, ref());
            auto const lookup = trie_.longest_match(first, last);
            if (lookup.match) {
                std::advance(first, lookup.size);
                detail::assign(retval, T{*trie_[lookup]});
            } else {
                success = false;
            }
        }

        std::vector<std::pair<std::string_view, T>> initial_elements_;
        symbol_parser const * copied_from_;

        symbol_parser const & ref() const noexcept
        {
            if (copied_from_)
                return *copied_from_;
            return *this;
        }
        std::vector<std::pair<std::string_view, T>> const &
        initial_elements() const noexcept
        {
            return ref().initial_elements_;
        }
    };

    template<
        bool CanUseCallbacks,
        typename TagType,
        typename Attribute,
        typename LocalState,
        typename ParamsTuple>
    struct rule_parser
    {
        using tag_type = TagType;
        using attr_type = Attribute;
        using locals_type = LocalState;

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser>
        attr_type call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            attr_type retval{};
            locals_type locals = detail::make_locals<locals_type>(context);
            auto params = detail::resolve_rule_params(context, params_);
            auto const rule_context =
                detail::make_rule_context(context, retval, locals, params);
            auto _ = detail::scoped_trace(
                *this, first, last, rule_context, flags, retval);
            tag_type * const tag_ptr = nullptr;

            parse_rule(
                tag_ptr,
                use_cbs,
                first,
                last,
                rule_context,
                skip,
                flags,
                success,
                retval);

            if constexpr (CanUseCallbacks && UseCallbacks) {
                if (!success)
                    return {};

                auto const & callbacks = _callbacks(context);

                if constexpr (detail::is_nope_v<attr_type>) {
                    // For rules without attributes, Callbacks must be a
                    // struct with overloads of the form void(tag_type).  If
                    // you're seeing an error here, you probably have not met
                    // this contract.
                    static_assert(
                        detail::is_invocable_v<decltype(callbacks), tag_type>);
                    callbacks(tag_type{});
                } else {
                    // For rules with attributes, Callbacks must be a struct
                    // with overloads of the form void(tag_type, attr_type).
                    // If you're seeing an error here, you probably have not
                    // met this contract.
                    static_assert(detail::is_invocable_v<
                                  decltype(callbacks),
                                  tag_type,
                                  decltype(std::move(retval))>);
                    callbacks(tag_type{}, std::move(retval));
                }

                return {};
            } else {
                if (!success)
                    detail::assign(retval, attr_type());
                return retval;
            }
        }

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser,
            typename Attribute_>
        void call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute_ & retval) const
        {
            if constexpr (CanUseCallbacks && UseCallbacks) {
                call(use_cbs, first, last, context, skip, flags, success);
            } else {
                attr_type attr =
                    call(use_cbs, first, last, context, skip, flags, success);
                if (success)
                    detail::assign(retval, attr);
            }
        }

        std::string_view name_;
        ParamsTuple params_;
    };


    // Parser interface.

    template<typename Parser, typename GlobalState, typename ErrorHandler>
    struct parser_interface
    {
        using parser_type = Parser;
        using global_state_type = GlobalState;
        using error_handler_type = ErrorHandler;

        constexpr parser_interface() {}
        constexpr parser_interface(parser_type p) : parser_(p) {}
        constexpr parser_interface(
            parser_type p, global_state_type gs, error_handler_type eh) :
            parser_(p), globals_(gs), error_handler_(eh)
        {}

        /** Returns a `parser_interface` containing a parser equivalent to an
            `expect_parser` containing `parser_`, with `FailOnMatch ==
            true`. */
        constexpr auto operator!() const noexcept
        {
            return parser::parser_interface{
                expect_parser<parser_type, true>{parser_}};
        }

        /** Returns a `parser_interface` containing a parser equivalent to an
            `expect_parser` containing `parser_`, with `FailOnMatch ==
            false`. */
        constexpr auto operator&() const noexcept
        {
            return parser::parser_interface{
                expect_parser<parser_type, false>{parser_}};
        }

        /** Returns a `parser_interface` containing a parser equivalent to a
            `zero_plus_parser` containing `parser_`. */
        constexpr auto operator*() const noexcept
        {
            if constexpr (detail::is_zero_plus_p<parser_type>{}) {
                return *this;
            } else if constexpr (detail::is_one_plus_p<parser_type>{}) {
                using inner_parser = decltype(parser_type::parser_);
                return parser::parser_interface{
                    zero_plus_parser<inner_parser>(parser_.parser_)};
            } else {
                return parser::parser_interface{
                    zero_plus_parser<parser_type>(parser_)};
            }
        }

        /** Returns a `parser_interface` containing a parser equivalent to a
            `one_plus_parser` containing `parser_`. */
        constexpr auto operator+() const noexcept
        {
            if constexpr (detail::is_zero_plus_p<parser_type>{}) {
                using inner_parser = decltype(parser_type::parser_);
                return parser::parser_interface{
                    zero_plus_parser<inner_parser>(parser_.parser_)};
            } else if constexpr (detail::is_one_plus_p<parser_type>{}) {
                return *this;
            } else {
                return parser::parser_interface{
                    one_plus_parser<parser_type>(parser_)};
            }
        }

        /** Returns a `parser_interface` containing a parser equivalent to a
            `opt_parser` containing `parser_`. */
        constexpr auto operator-() const noexcept
        {
            return parser::parser_interface{opt_parser<parser_type>{parser_}};
        }

        /** Returns a `parser_interface` containing a parser equivalent to a
            `seq_parser` containing `parser_` followed by `rhs.parser_`. */
        template<typename ParserType2>
        constexpr auto
        operator>>(parser_interface<ParserType2> rhs) const noexcept
        {
            if constexpr (detail::is_seq_p<parser_type>{}) {
                return parser_.template append<true>(rhs);
            } else if constexpr (detail::is_seq_p<ParserType2>{}) {
                return rhs.parser_.template prepend<true>(*this);
            } else {
                using parser_t = seq_parser<
                    tuple<parser_type, ParserType2>,
                    tuple<std::true_type, std::true_type>>;
                return parser::parser_interface{parser_t{
                    tuple<parser_type, ParserType2>{parser_, rhs.parser_}}};
            }
        }

        /** Returns a `parser_interface` containing a parser equivalent to a
            `seq_parser` containing `parser_` followed by `lit(rhs)`. */
        constexpr auto operator>>(char rhs) const noexcept;

        /** Returns a `parser_interface` containing a parser equivalent to a
            `seq_parser` containing `parser_` followed by `lit(rhs)`. */
        constexpr auto operator>>(char32_t rhs) const noexcept;

        /** Returns a `parser_interface` containing a parser equivalent to a
            `seq_parser` containing `parser_` followed by `lit(rhs)`. */
#if BOOST_PARSER_USE_CONCEPTS
        template<parsable_range_like R>
#else
        template<
            typename R,
            typename Enable =
                std::enable_if_t<detail::is_parsable_range_like<R>::value>>
#endif
        constexpr auto operator>>(R && r) const noexcept;

        /** Returns a `parser_interface` containing a parser equivalent to a
            `seq_parser` containing `parser_` followed by `rhs.parser_`.  No
            back-tracking is allowed after `parser_` succeeds; if
            `rhs.parser_` fails after `parser_` succeeds, the top-level parse
            fails. */
        template<typename ParserType2>
        constexpr auto
        operator>(parser_interface<ParserType2> rhs) const noexcept
        {
            if constexpr (detail::is_seq_p<parser_type>{}) {
                return parser_.template append<false>(rhs);
            } else if constexpr (detail::is_seq_p<ParserType2>{}) {
                return rhs.parser_.template prepend<false>(*this);
            } else {
                using parser_t = seq_parser<
                    tuple<parser_type, ParserType2>,
                    tuple<std::true_type, std::false_type>>;
                return parser::parser_interface{parser_t{
                    tuple<parser_type, ParserType2>{parser_, rhs.parser_}}};
            }
        }

        /** Returns a `parser_interface` containing a parser equivalent to a
            `seq_parser` containing `parser_` followed by `lit(rhs)`.  No
            back-tracking is allowed after `parser_` succeeds; if `lit(rhs)`
            fails after `parser_` succeeds, the top-level parse fails. */
        constexpr auto operator>(char rhs) const noexcept;

        /** Returns a `parser_interface` containing a parser equivalent to a
            `seq_parser` containing `parser_` followed by `lit(rhs)`.  No
            back-tracking is allowed after `parser_` succeeds; if `lit(rhs)`
            fails after `parser_` succeeds, the top-level parse fails. */
        constexpr auto operator>(char32_t rhs) const noexcept;

        /** Returns a `parser_interface` containing a parser equivalent to a
            `seq_parser` containing `parser_` followed by `lit(rhs)`.  No
            back-tracking is allowed after `parser_` succeeds; if `lit(rhs)`
            fails after `parser_` succeeds, the top-level parse fails. */
#if BOOST_PARSER_USE_CONCEPTS
        template<parsable_range_like R>
#else
        template<
            typename R,
            typename Enable =
                std::enable_if_t<detail::is_parsable_range_like<R>::value>>
#endif
        constexpr auto operator>(R && r) const noexcept;

        /** Returns a `parser_interface` containing a parser equivalent to an
            `or_parser` containing `parser_` followed by `rhs.parser_`. */
        template<typename ParserType2>
        constexpr auto
        operator|(parser_interface<ParserType2> rhs) const noexcept
        {
            if constexpr (detail::is_or_p<parser_type>{}) {
                return parser_.append(rhs);
            } else if constexpr (detail::is_or_p<ParserType2>{}) {
                return rhs.parser_.prepend(*this);
            } else {
                // If you're seeing this as a compile- or run-time failure,
                // you've tried to put an eps parser at the beginning of an
                // alternative-parser, such as "eps | int_".  This is not what
                // you meant.  Since eps always matches any input, "eps |
                // int_" is just an awkward spelling for "eps".  To fix this
                // this, put the eps as the last alternative, so the other
                // alternatives get a chance.  Possibly, you may have meant to
                // add a condition to the eps, like "eps(condition) | int_",
                // which also is meaningful, and so is allowed.
                BOOST_PARSER_ASSERT(
                    !detail::is_unconditional_eps<parser_type>{});
                return parser::parser_interface{
                    or_parser<tuple<parser_type, ParserType2>>{
                        tuple<parser_type, ParserType2>{parser_, rhs.parser_}}};
            }
        }

        /** Returns a `parser_interface` containing a parser equivalent to an
            `or_parser` containing `parser_` followed by `lit(rhs)`. */
        constexpr auto operator|(char rhs) const noexcept;

        /** Returns a `parser_interface` containing a parser equivalent to an
            `or_parser` containing `parser_` followed by `lit(rhs)`. */
        constexpr auto operator|(char32_t rhs) const noexcept;

        /** Returns a `parser_interface` containing a parser equivalent to an
            `or_parser` containing `parser_` followed by `lit(rhs)`. */
#if BOOST_PARSER_USE_CONCEPTS
        template<parsable_range_like R>
#else
        template<
            typename R,
            typename Enable =
                std::enable_if_t<detail::is_parsable_range_like<R>::value>>
#endif
        constexpr auto operator|(R && r) const noexcept;

        /** Returns a `parser_interface` containing a parser equivalent to
            `!rhs >> *this`. */
        template<typename ParserType2>
        constexpr auto
        operator-(parser_interface<ParserType2> rhs) const noexcept
        {
            return !rhs >> *this;
        }

        /** Returns a `parser_interface` containing a parser equivalent to
            `!lit(rhs) >> *this`. */
        constexpr auto operator-(char rhs) const noexcept;

        /** Returns a `parser_interface` containing a parser equivalent to
            `!lit(rhs) >> *this`. */
        constexpr auto operator-(char32_t rhs) const noexcept;

        /** Returns a `parser_interface` containing a parser equivalent to
            `!lit(rhs) >> *this`. */
#if BOOST_PARSER_USE_CONCEPTS
        template<parsable_range_like R>
#else
        template<
            typename R,
            typename Enable =
                std::enable_if_t<detail::is_parsable_range_like<R>::value>>
#endif
        constexpr auto operator-(R && r) const noexcept;

        /** Returns a `parser_interface` containing a parser equivalent to an
           `delimited_seq_parser` containing `parser_` and `rhs.parser_`. */
        template<typename ParserType2>
        constexpr auto
        operator%(parser_interface<ParserType2> rhs) const noexcept
        {
            return parser::parser_interface{
                delimited_seq_parser<parser_type, ParserType2>(
                    parser_, rhs.parser_)};
        }

        /** Returns a `parser_interface` containing a parser equivalent to an
           `delimited_seq_parser` containing `parser_` and `lit(rhs)`. */
        constexpr auto operator%(char rhs) const noexcept;

        /** Returns a `parser_interface` containing a parser equivalent to an
           `delimited_seq_parser` containing `parser_` and `lit(rhs)`. */
        constexpr auto operator%(char32_t rhs) const noexcept;

        /** Returns a `parser_interface` containing a parser equivalent to an
           `delimited_seq_parser` containing `parser_` and `lit(rhs)`. */
#if BOOST_PARSER_USE_CONCEPTS
        template<parsable_range_like R>
#else
        template<
            typename R,
            typename Enable =
                std::enable_if_t<detail::is_parsable_range_like<R>::value>>
#endif
        constexpr auto operator%(R && r) const noexcept;

        /** Returns a `parser_interface` containing a parser equivalent to an
           `action_parser` containing `parser_`, with semantic action
           `action`. */
        template<typename Action>
        constexpr auto operator[](Action action) const
        {
            using action_parser_t = action_parser<parser_type, Action>;
            return parser::parser_interface{action_parser_t{parser_, action}};
        }

        /** Returns `parser_((Arg &&)arg, (Args &&)args...)`.  This is useful
            for those parsers that have `operator()` overloads,
            e.g. `char_('x')`.  By convention, parsers' `operator()`s return
            `parser_interface`s.

            This function does not participate in overload resolution unless
            `parser_((Arg &&)arg, (Args &&)args...)` is well-formed. */
        template<typename Arg, typename... Args>
        constexpr auto operator()(Arg && arg, Args &&... args) const noexcept
            -> decltype(std::declval<parser_type const &>()(
                (Arg &&) arg, (Args &&) args...))
        {
            return parser_((Arg &&) arg, (Args &&) args...);
        }

#ifndef BOOST_PARSER_DOXYGEN

        /** Applies `parser_`, returning the parsed attribute, if any, unless
            the attribute is reported via callback. */
        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParserType>
        auto operator()(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParserType const & skip,
            detail::flags flags,
            bool & success) const
        {
            return parser_.call(
                use_cbs, first, last, context, skip, flags, success);
        }

        /** Applies `parser_`, assiging the parsed attribute, if any, to
            `attr`, unless the attribute is reported via callback. */
        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParserType,
            typename Attribute>
        void operator()(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParserType const & skip,
            detail::flags flags,
            bool & success,
            Attribute & attr) const
        {
            parser_.call(
                use_cbs, first, last, context, skip, flags, success, attr);
        }

        parser_type parser_;
        global_state_type globals_;
        error_handler_type error_handler_;

#endif
    };


    /** Returns a `parser_interface` with the same parser and error handler,
        with `globals` added.  The resut of passing any non-top-level parser
        for the `parser` argument is undefined. */
    template<typename Parser, typename GlobalState, typename ErrorHandler>
    auto with_globals(
        parser_interface<Parser, detail::nope, ErrorHandler> const & parser,
        GlobalState & globals)
    {
        return parser_interface<Parser, GlobalState &, ErrorHandler>{
            parser.parser_, globals, parser.error_handler_};
    }

    /** Returns a `parser_interface` with the same parser and globals, with
        `error_handler` added.  The resut of passing any non-top-level parser
        for the `parser` argument is undefined. */
    template<typename Parser, typename GlobalState, typename ErrorHandler>
    auto with_error_handler(
        parser_interface<Parser, GlobalState, default_error_handler> const &
            parser,
        ErrorHandler & error_handler)
    {
        return parser_interface<Parser, GlobalState, ErrorHandler &>{
            parser.parser_, parser.globals_, error_handler};
    }


    /** A `symbols<T>` represents the initial state of a symbol table parser
        that produces attributes of type `T`.  The entries in the symbol table
        can be changed during parsing, but those mutations to not affect the
        `symbols<T>` object itself; all mutations happen to a copy of the
        symbol table in the parse context.  For table entries that should be
        used during every parse, add entries via `add()` or `operator()`.  For
        mid-parse mutations, use `insert()` and `erase()`. */
    template<typename T>
    struct symbols : parser_interface<symbol_parser<T>>
    {
        symbols() {}
        symbols(std::initializer_list<std::pair<std::string_view, T>> il)
        {
            this->parser_.initial_elements_ = il;
        }

        using parser_interface<symbol_parser<T>>::operator();

        /** Adds an entry consisting of a UTF-8 string `str` to match, and an
            associated attribute `x`, to `*this`.  The entry is added for use
            in all subsequent parsing. */
        symbols & add(std::string_view str, T x)
        {
            this->parser_.initial_elements_.push_back(
                std::pair<std::string_view, T>(str, std::move(x)));
            return *this;
        }

        /** Equivalent to `add(str, std::move(x))`. */
        symbols & operator()(std::string_view str, T x)
        {
            return add(str, std::move(x));
        }

        /** Uses UTF-8 string `str` to look up an attribute in the table
            during parsing, returning it as an optional reference.  The lookup
            is done on the copy of the symbol table inside the parse context
            `context`, not `*this`. */
        template<typename Context>
        parser::detail::text::optional_ref<T>
        find(Context const & context, std::string_view str) const
        {
            return this->parser_.find(context, str);
        }

        /** Inserts an entry consisting of a UTF-8 string to match `str`, and
            an associtated attribute `x`, to the copy of the symbol table
            inside the parse context `context`. */
        template<typename Context>
        void insert(Context const & context, std::string_view str, T x) const
        {
            this->parser_.insert(context, str, std::move(x));
        }

        /** Erases the entry whose UTF-8 match string is `str` from the copy
            of the symbol table inside the parse context `context`. */
        template<typename Context>
        void erase(Context const & context, std::string_view str) const
        {
            this->parser_.erase(context, str);
        }
    };

    template<
        typename TagType,
        typename Attribute,
        typename LocalState,
        typename ParamsTuple>
    struct rule
        : parser_interface<
              rule_parser<false, TagType, Attribute, LocalState, ParamsTuple>>
    {
        constexpr rule(char const * name) { this->parser_.name_ = name; }

        template<typename T, typename... Ts>
        constexpr auto with(T && x, Ts &&... xs) const
        {
            BOOST_PARSER_ASSERT(
                (detail::is_nope_v<ParamsTuple> &&
                 "If you're seeing this, you tried to chain calls on a rule, "
                 "like 'rule.with(foo).with(bar)'.  Quit it!'"));
            using params_tuple_type = decltype(detail::hl::make_tuple(
                static_cast<T &&>(x), static_cast<Ts &&>(xs)...));
            using rule_parser_type = rule_parser<
                false,
                TagType,
                Attribute,
                LocalState,
                params_tuple_type>;
            using result_type = parser_interface<rule_parser_type>;
            return result_type{rule_parser_type{
                this->parser_.name_,
                detail::hl::make_tuple(
                    static_cast<T &&>(x), static_cast<Ts &&>(xs)...)}};
        }
    };

    template<
        typename TagType,
        typename Attribute,
        typename LocalState,
        typename ParamsTuple>
    struct callback_rule
        : parser_interface<
              rule_parser<true, TagType, Attribute, LocalState, ParamsTuple>>
    {
        constexpr callback_rule(char const * name)
        {
            this->parser_.name_ = name;
        }

        template<typename T, typename... Ts>
        constexpr auto with(T && x, Ts &&... xs) const
        {
            BOOST_PARSER_ASSERT(
                (detail::is_nope_v<ParamsTuple> &&
                 "If you're seeing this, you tried to chain calls on a "
                 "callback_rule, like 'rule.with(foo).with(bar)'.  Quit it!'"));
            using params_tuple_type = decltype(detail::hl::make_tuple(
                static_cast<T &&>(x), static_cast<Ts &&>(xs)...));
            using rule_parser_type = rule_parser<
                true,
                TagType,
                Attribute,
                LocalState,
                params_tuple_type>;
            using result_type = parser_interface<rule_parser_type>;
            return result_type{rule_parser_type{
                this->parser_.name_,
                detail::hl::make_tuple(
                    static_cast<T &&>(x), static_cast<Ts &&>(xs)...)}};
        }
    };

#ifndef BOOST_PARSER_DOXYGEN

#define BOOST_PARSER_CAT(a, b) BOOST_PARSER_CAT_I(a, b)
#if defined(_MSC_VER)
#define BOOST_PARSER_CAT_I(a, b) BOOST_PARSER_CAT_II(~, a##b)
#define BOOST_PARSER_CAT_II(p, res) res
#else
#define BOOST_PARSER_CAT_I(a, b) a##b
#endif

#define BOOST_PARSER_DEFINE_IMPL(r, data, name_)                               \
    template<                                                                  \
        bool UseCallbacks,                                                     \
        typename Iter,                                                         \
        typename Sentinel,                                                     \
        typename Context,                                                      \
        typename SkipParser>                                                   \
    auto parse_rule(                                                           \
        decltype(name_)::parser_type::tag_type *,                              \
        std::bool_constant<UseCallbacks> use_cbs,                              \
        Iter & first,                                                          \
        Sentinel last,                                                         \
        Context const & context,                                               \
        SkipParser const & skip,                                               \
        boost::parser::detail::flags flags,                                    \
        bool & success)                                                        \
    {                                                                          \
        auto const & parser = BOOST_PARSER_CAT(name_, _def);                   \
        return parser(use_cbs, first, last, context, skip, flags, success);    \
    }                                                                          \
                                                                               \
    template<                                                                  \
        bool UseCallbacks,                                                     \
        typename Iter,                                                         \
        typename Sentinel,                                                     \
        typename Context,                                                      \
        typename SkipParser,                                                   \
        typename Attribute>                                                    \
    void parse_rule(                                                           \
        decltype(name_)::parser_type::tag_type *,                              \
        std::bool_constant<UseCallbacks> use_cbs,                              \
        Iter & first,                                                          \
        Sentinel last,                                                         \
        Context const & context,                                               \
        SkipParser const & skip,                                               \
        boost::parser::detail::flags flags,                                    \
        bool & success,                                                        \
        Attribute & retval)                                                    \
    {                                                                          \
        auto const & parser = BOOST_PARSER_CAT(name_, _def);                   \
        using attr_t = decltype(                                               \
            parser(use_cbs, first, last, context, skip, flags, success));      \
        if constexpr (boost::parser::detail::is_nope_v<attr_t>)                \
            parser(use_cbs, first, last, context, skip, flags, success);       \
        else                                                                   \
            parser(                                                            \
                use_cbs, first, last, context, skip, flags, success, retval);  \
    }

#endif

#if defined(BOOST_PARSER_DOXYGEN) || BOOST_PARSER_HAVE_BOOST_PP

    /** For each given token `t`, defines a pair of `parse_rule()` overloads,
        used internally within Boost.Parser.  Each such pair implements the
        parsing behavior rule `t`, using the parser `t_def`.  This macro is
        only available when the Boost.Preprocessor headers are available. */
#define BOOST_PARSER_DEFINE_RULES(...)                                         \
    BOOST_PP_SEQ_FOR_EACH(                                                     \
        BOOST_PARSER_DEFINE_IMPL, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))

#endif

    /** Defines a pair of `parse_rule()` overloads for the given rule, used
        internally within Boost.Parser.  The pair implements the parsing
        behavior rule `rule`, using the parser `rule_def`. */
#define BOOST_PARSER_DEFINE_RULE(rule) BOOST_PARSER_DEFINE_IMPL(_, _, rule)


#ifndef BOOST_PARSER_DOXYGEN

    template<typename ParserTuple>
    template<typename Parser>
    constexpr auto or_parser<ParserTuple>::prepend(
        parser_interface<Parser> parser) const noexcept
    {
        // If you're seeing this as a compile- or run-time failure, you've
        // tried to put an eps parser at the beginning of an
        // alternative-parser, such as "eps | (int_ | double_)".  This is not
        // what you meant.  Since eps always matches any input, "eps | (int_ |
        // double_)" is just an awkward spelling for "eps".  To fix this this,
        // put the eps as the last alternative, so the other alternatives get
        // a chance.  Possibly, you may have meant to add a condition to the
        // eps, like "eps(condition) | (int_ | double_)", which also is
        // meaningful, and so is allowed.
        BOOST_PARSER_ASSERT(!detail::is_unconditional_eps<Parser>{});
        return parser_interface{
            or_parser<decltype(detail::hl::prepend(parsers_, parser.parser_))>{
                detail::hl::prepend(parsers_, parser.parser_)}};
    }

    template<typename ParserTuple>
    template<typename Parser>
    constexpr auto or_parser<ParserTuple>::append(
        parser_interface<Parser> parser) const noexcept
    {
        // If you're seeing this as a compile- or run-time failure, you've
        // tried to put an eps parser in the middle of an alternative-parser,
        // such as "int_ | eps | double_".  This is not what you meant.  Since
        // eps always matches any input, "int_ | eps | double_" is just an
        // awkward spelling for "int_ | eps".  To fix this this, put the eps
        // as the last alternative, so the other alternatives get a chance.
        // Possibly, you may have meant to add a condition to the eps, like
        // "int_ | eps(condition) | double_", which also is meaningful, and so
        // is allowed.
        BOOST_PARSER_ASSERT(!detail::is_unconditional_eps_v<decltype(
                                detail::hl::back(parsers_))>);
        if constexpr (detail::is_or_p<Parser>{}) {
            return parser_interface{or_parser<decltype(
                detail::hl::concat(parsers_, parser.parser_.parsers_))>{
                detail::hl::concat(parsers_, parser.parser_.parsers_)}};
        } else {
            return parser_interface{or_parser<decltype(
                detail::hl::append(parsers_, parser.parser_))>{
                detail::hl::append(parsers_, parser.parser_)}};
        }
    }

    template<typename ParserTuple, typename BacktrackingTuple>
    template<bool AllowBacktracking, typename Parser>
    constexpr auto seq_parser<ParserTuple, BacktrackingTuple>::prepend(
        parser_interface<Parser> parser) const noexcept
    {
        using backtracking = decltype(detail::hl::prepend(
            detail::hl::prepend(
                detail::hl::drop_front(BacktrackingTuple{}),
                std::bool_constant<AllowBacktracking>{}),
            std::true_type{}));
        using parser_t = seq_parser<
            decltype(detail::hl::prepend(parsers_, parser.parser_)),
            backtracking>;
        return parser_interface{
            parser_t{detail::hl::prepend(parsers_, parser.parser_)}};
    }

    template<typename ParserTuple, typename BacktrackingTuple>
    template<bool AllowBacktracking, typename Parser>
    constexpr auto seq_parser<ParserTuple, BacktrackingTuple>::append(
        parser_interface<Parser> parser) const noexcept
    {
        if constexpr (detail::is_seq_p<Parser>{}) {
            using backtracking = decltype(detail::hl::concat(
                BacktrackingTuple{}, typename Parser::backtracking{}));
            using parser_t = seq_parser<
                decltype(detail::hl::concat(parsers_, parser.parser_.parsers_)),
                backtracking>;
            return parser_interface{parser_t{
                detail::hl::concat(parsers_, parser.parser_.parsers_)}};
        } else {
            using backtracking = decltype(detail::hl::append(
                BacktrackingTuple{}, std::bool_constant<AllowBacktracking>{}));
            using parser_t = seq_parser<
                decltype(detail::hl::append(parsers_, parser.parser_)),
                backtracking>;
            return parser_interface{
                parser_t{detail::hl::append(parsers_, parser.parser_)}};
        }
    }

#endif



    // Directives.

    /** Represents a unparameterized higher-order parser (e.g. `omit_parser`)
        as a directive (e.g. `omit[other_parser]`). */
    template<template<class> class Parser>
    struct directive
    {
        template<typename Parser2>
        constexpr auto operator[](parser_interface<Parser2> rhs) const noexcept
        {
            return parser_interface{Parser<Parser2>{rhs.parser_}};
        }
    };

    /** The `omit` directive, whose `operator[]` returns an
        `parser_interface<omit_parser<P>>` from a given parser of type
        `parser_interface<P>`. */
    inline constexpr directive<omit_parser> omit;

    /** The `raw` directive, whose `operator[]` returns an
        `parser_interface<raw_parser<P>>` from a given parser of type
        `parser_interface<P>`. */
    inline constexpr directive<raw_parser> raw;

    // TODO: This needs tests!
#if defined(BOOST_PARSER_DOXYGEN) || defined(__cpp_lib_concepts)
    /** The `string_view` directive, whose `operator[]` returns an
        `parser_interface<string_view_parser<P>>` from a given parser of type
        `parser_interface<P>`.  This is only available in C++20 and later. */
    inline constexpr directive<string_view_parser> string_view;
#endif

    /** The `lexeme` directive, whose `operator[]` returns an
        `parser_interface<lexeme_parser<P>>` from a given parser of type
        `parser_interface<P>`. */
    inline constexpr directive<lexeme_parser> lexeme;

    /** Represents a `repeat_parser` as a directive
        (e.g. `repeat[other_parser]`). */
    template<typename MinType, typename MaxType>
    struct repeat_directive
    {
        template<typename Parser2>
        constexpr auto operator[](parser_interface<Parser2> rhs) const noexcept
        {
            using repeat_parser_type =
                repeat_parser<Parser2, detail::nope, MinType, MaxType>;
            return parser_interface{
                repeat_parser_type{rhs.parser_, min_, max_}};
        }

        MinType min_;
        MaxType max_;
    };

    /** Returns a `repeat_directive` that repeats exactly `n` times, and whose
        `operator[]` returns an `parser_interface<repeat_parser<P>>` from a
        given parser of type `parser_interface<P>`. */
    template<typename T>
    constexpr repeat_directive<T, T> repeat(T n) noexcept
    {
        return repeat_directive<T, T>{n, n};
    }

    /** Returns a `repeat_directive` that repeats between `min_` and `max_`
        times, inclusive, and whose `operator[]` returns an
        `parser_interface<repeat_parser<P>>` from a given parser of type
        `parser_interface<P>`. */
    template<typename MinType, typename MaxType>
    constexpr repeat_directive<MinType, MaxType>
    repeat(MinType min_, MaxType max_) noexcept
    {
        return repeat_directive<MinType, MaxType>{min_, max_};
    }

    /** Represents a skip parser as a directive.  When used without a skip
        parser, e.g. `skip[parser_in_which_to_do_skipping]`, the skipper for
        the entire parse is used.  When given another parser, e.g.
        `skip(skip_parser)[parser_in_which_to_do_skipping]`, that other parser
        is used as the skipper within the directive. */
    template<typename SkipParser = detail::nope>
    struct skip_directive
    {
        template<typename Parser>
        constexpr auto operator[](parser_interface<Parser> rhs) const noexcept
        {
            return parser_interface{
                skip_parser<Parser, SkipParser>{rhs.parser_, skip_parser_}};
        }

        /** Returns a `skip_directive` with `skip_parser` as its skipper. */
        template<typename SkipParser2>
        constexpr auto
        operator()(parser_interface<SkipParser2> skip_parser) const noexcept
        {
            BOOST_PARSER_ASSERT(
                (detail::is_nope_v<SkipParser> &&
                 "If you're seeing this, you tried to chain calls on skip, "
                 "like 'skip(foo)(bar)'.  Quit it!'"));
            return skip_directive<parser_interface<SkipParser2>>{skip_parser};
        }

        SkipParser skip_parser_;
    };

    /** The `skip_directive`, whose `operator[]` returns an
        `parser_interface<skip_parser<P>>` from a given parser of type
        `parser_interface<P>`. */
    inline constexpr skip_directive<> skip;



    // First order parsers.

    template<typename Predicate>
    struct eps_parser
    {
        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser>
        detail::nope call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const noexcept
        {
            auto _ = detail::scoped_trace(
                *this, first, last, context, flags, detail::global_nope);
            view const where(first, first);
            auto const predicate_context = detail::make_action_context(
                context, detail::global_nope, where);
            // Predicate must be a parse predicate.  If you see an error here,
            // you have not met this contract.  See the terminology section of
            // the online docs if you don't know what that a parse predicate
            // is.
            success = pred_(predicate_context);
            return {};
        }

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = detail::scoped_trace(
                *this, first, last, context, flags, retval);
            view const where(first, first);
            auto const predicate_context = detail::make_action_context(
                context, detail::global_nope, where);
            // Predicate must be a parse predicate.  If you see an error here,
            // you have not met this contract.  See the terminology section of
            // the online docs if you don't know what that a parse predicate
            // is.
            success = pred_(predicate_context);
        }

        /** Returns a `parser_interface` containing an `eps_parser` that will
            fail if `pred` evaluates to false. */
        template<typename Predicate2>
        constexpr auto operator()(Predicate2 pred) const noexcept
        {
            BOOST_PARSER_ASSERT(
                (detail::is_nope_v<Predicate> &&
                 "If you're seeing this, you tried to chain calls on eps, "
                 "like 'eps(foo)(bar)'.  Quit it!'"));
            return parser_interface{eps_parser<Predicate2>{std::move(pred)}};
        }

        Predicate pred_;
    };

    /** The epsilon parser.  This matches anything, and consumes no input.  If
        used with an optional predicate, like `eps(pred)`, it matches iff
        `pred(ctx)` evaluates to true, where `ctx` is the parser context. */
    inline constexpr parser_interface<eps_parser<detail::nope>> eps;

    struct eoi_parser
    {
        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser>
        detail::nope call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            auto _ = detail::scoped_trace(
                *this, first, last, context, flags, detail::global_nope);
            if (first != last)
                success = false;
            return {};
        }

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = detail::scoped_trace(
                *this, first, last, context, flags, retval);
            if (first != last)
                success = false;
        }
    };

    /** The end-of-input parser.  It matches only the end of input. */
    inline constexpr parser_interface<eoi_parser> eoi;

    template<typename Attribute>
    struct attr_parser
    {
        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser>
        auto call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const &,
            detail::flags flags,
            bool &) const
        {
            auto _ = detail::scoped_trace(
                *this, first, last, context, flags, detail::global_nope);
            return detail::resolve(context, attr_);
        }

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser,
            typename Attribute_>
        void call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute_ & retval) const
        {
            auto _ = detail::scoped_trace(
                *this, first, last, context, flags, retval);
            if (detail::gen_attrs(flags))
                detail::assign_copy(retval, detail::resolve(context, attr_));
        }

        Attribute attr_;
    };

    /** Returns an `attr_parser` which matches anything, and consumes no
        input, and which produces `a` as its attribute. */
    template<typename Attribute>
    constexpr auto attr(Attribute a) noexcept
    {
        return parser_interface{attr_parser<Attribute>{std::move(a)}};
    }

    template<typename Expected, typename AttributeType>
    struct char_parser
    {
        constexpr char_parser() {}
        constexpr char_parser(Expected expected) : expected_(expected) {}

        template<typename T>
        using attribute_t = std::conditional_t<
            std::is_same_v<AttributeType, void>,
            std::decay_t<T>,
            AttributeType>;

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser>
        auto call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const -> attribute_t<decltype(*first)>
        {
            attribute_t<decltype(*first)> retval;
            call(use_cbs, first, last, context, skip, flags, success, retval);
            return retval;
        }

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = detail::scoped_trace(
                *this, first, last, context, flags, retval);

            if (first == last) {
                success = false;
                return;
            }
            attribute_t<decltype(*first)> const x = *first;
            if (detail::unequal(context, x, expected_)) {
                success = false;
                return;
            }
            detail::assign(retval, x);
            ++first;
        }

        /** Returns a `parser_interface` containing a `char_parser` that
            matches `x`. */
#if BOOST_PARSER_USE_CONCEPTS
        template<typename T>
        // clang-format off
        requires (!parsable_range_like<T>)
#else
        template<
            typename T,
            typename Enable =
                std::enable_if_t<!detail::is_parsable_range_like<T>::value>>
#endif
        constexpr auto operator()(T x) const noexcept
        // clang-format on
        {
            BOOST_PARSER_ASSERT(
                (detail::is_nope_v<Expected> &&
                 "If you're seeing this, you tried to chain calls on char_, "
                 "like 'char_('a')('b')'.  Quit it!'"));
            return parser_interface{
                char_parser<T, AttributeType>{std::move(x)}};
        }

        /** Returns a `parser_interface` containing a `char_parser` that
            matches any value in `[lo, hi)`. */
        template<typename LoType, typename HiType>
        constexpr auto operator()(LoType lo, HiType hi) const noexcept
        {
            BOOST_PARSER_ASSERT(
                (detail::is_nope_v<Expected> &&
                 "If you're seeing this, you tried to chain calls on char_, "
                 "like 'char_('a', 'b')('c', 'd')'.  Quit it!'"));
            using char_pair_t = detail::char_pair<LoType, HiType>;
            using char_parser_t = char_parser<char_pair_t, AttributeType>;
            return parser_interface(
                char_parser_t(char_pair_t{std::move(lo), std::move(hi)}));
        }

        /** Returns a `parser_interface` containing a `char_parser` that
            matches one of the values in `r`.  If the character being matched
            during the parse is a 4-byte value, the elements of `r` are
            transcoded from their presumed encoding to UTF-32 during the
            comparison.  Otherwise, the character begin matched is directly
            compared to the elements of `r`.  The presumed encoding of `r` is
            considered UTF-8, UTF-16, or UTF-32, if the size of the elements
            of `r` are 1-, 2- or 4-bytes in size, respectively. */
#if BOOST_PARSER_USE_CONCEPTS
        template<parsable_range_like R>
#else
        template<
            typename R,
            typename Enable =
                std::enable_if_t<detail::is_parsable_range_like<R>::value>>
#endif
        constexpr auto operator()(R const & r) const noexcept
        {
            BOOST_PARSER_ASSERT(
                (detail::is_nope_v<Expected> &&
                 "If you're seeing this, you tried to chain calls on char_, "
                 "like 'char_(char-set)(char-set)'.  Quit it!'"));
            auto chars = detail::make_char_range(r);
            using char_range_t = decltype(chars);
            using char_parser_t = char_parser<char_range_t, AttributeType>;
            return parser_interface(char_parser_t(chars));
        }

        Expected expected_;
    };

    /** The literal code point parser.  The produced attribute is the type of
        the matched code point.  This parser can be used to create code point
        parsers that match one or more specific code point values, by calling
        it with: a single value comparable to a code point; a set of code
        point values in a string; a half-open range of code point values `[lo,
        hi)`, or a set of code point values passed as a range. */
    inline constexpr parser_interface<char_parser<detail::nope>> char_;

    /** The literal code point parser.  It produces a 32-bit unsigned integer
        attribute.  This parser can be used to create code point parsers that
        match one or more specific code point values, by calling it with: a
        single value comparable to a code point; a set of code point values in
        a string; a half-open range of code point values `[lo, hi)`, or a set
        of code point values passed as a range. */
    inline constexpr parser_interface<char_parser<detail::nope, uint32_t>> cp;

    /** The literal code unit parser.  It produces a `char` attribute.  This
        parser can be used to create code unit parsers that match one or more
        specific code unit values, by calling it with: a single value
        comparable to a code unit; a set of code unit values in a string; a
        half-open range of code unit values `[lo, hi)`, or a set of code unit
        values passed as a range. */
    inline constexpr parser_interface<char_parser<detail::nope, char>> cu;

    /** Returns a literal code point parser that produces no attribute. */
    inline constexpr auto lit(char c) noexcept { return omit[char_(c)]; }

#if defined(__cpp_char8_t) || defined(BOOST_PARSER_DOXYGEN)
    /** Returns a literal code point parser that produces no attribute. */
    inline constexpr auto lit(char8_t c) noexcept { return omit[char_(c)]; }
#endif

    /** Returns a literal code point parser that produces no attribute. */
    inline constexpr auto lit(char32_t c) noexcept { return omit[char_(c)]; }

    template<typename StrIter, typename StrSentinel>
    struct string_parser
    {
        constexpr string_parser() : expected_first_(), expected_last_() {}

#if BOOST_PARSER_USE_CONCEPTS
        template<parsable_range_like R>
#else
        template<
            typename R,
            typename Enable =
                std::enable_if_t<detail::is_parsable_range_like<R>::value>>
#endif
        constexpr string_parser(R && r) :
            expected_first_(detail::make_view_begin(r)),
            expected_last_(detail::make_view_end(r))
        {}

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser>
        std::string call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            std::string retval;
            call(use_cbs, first, last, context, skip, flags, success, retval);
            return retval;
        }

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = detail::scoped_trace(
                *this, first, last, context, flags, retval);

            if (first == last) {
                success = false;
                return;
            }

            if constexpr (sizeof(*first) == 4) {
                auto const cps = parser::detail::text::as_utf32(
                    expected_first_, expected_last_);
                auto const mismatch =
                    detail::mismatch(first, last, cps.begin(), cps.end());
                if (mismatch.second != cps.end()) {
                    success = false;
                    return;
                }

                detail::append(
                    retval, first, mismatch.first, detail::gen_attrs(flags));

                first = mismatch.first;
            } else {
                auto const mismatch = detail::mismatch(
                    first, last, expected_first_, expected_last_);
                if (mismatch.second != expected_last_) {
                    success = false;
                    return;
                }

                detail::append(
                    retval, first, mismatch.first, detail::gen_attrs(flags));

                first = mismatch.first;
            }
        }

        StrIter expected_first_;
        StrSentinel expected_last_;
    };

#if BOOST_PARSER_USE_CONCEPTS
    template<parsable_range_like R>
#else
    template<typename R>
#endif
    string_parser(R r) -> string_parser<
        decltype(detail::make_view_begin(r)),
        decltype(detail::make_view_end(r))>;

    /** Returns a parser that matches `str` that produces the matched string
        as its attribute. */
#if BOOST_PARSER_USE_CONCEPTS
    template<parsable_range_like R>
#else
    template<typename R>
#endif
    constexpr auto string(R && str) noexcept
    {
        return parser_interface{string_parser(str)};
    }

    /** Returns a parser that matches `str` that produces no attribute. */
#if BOOST_PARSER_USE_CONCEPTS
    template<parsable_range_like R>
#else
    template<typename R>
#endif
    constexpr auto lit(R && str) noexcept
    {
        return omit[parser::string(str)];
    }

    template<bool NewlinesOnly>
    struct ws_parser
    {
        constexpr ws_parser() {}

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser>
        detail::nope call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            detail::nope nope;
            call(use_cbs, first, last, context, skip, flags, success, nope);
            return {};
        }

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = detail::scoped_trace(
                *this, first, last, context, flags, retval);

            if (first == last) {
                success = false;
                return;
            }
            int const x = *first;
            if constexpr (NewlinesOnly) {
                if (x == 0x000a) { // lf
                    ++first;
                    return;
                }
                if (x == 0x000d) { // cr
                    ++first;
                    if (first != last && *first == 0x000a) // lf
                        ++first;
                    return;
                }
                if (0x000b == x || x == 0x000c || x == 0x0085 || x == 0x2028 ||
                    x == 0x2029) {
                    ++first;
                    return;
                }
                success = false;
            } else {
                if (x == 0x0020 || x == 0x000a) { // space, lf
                    ++first;
                    return;
                }
                if (x == 0x000d) { // cr
                    ++first;
                    if (first != last && *first == 0x000a) // lf
                        ++first;
                    return;
                }
                if (0x0009 <= x && x <= 0x000c) { // tab through cr
                    ++first;
                    return;
                }
                if (x == 0x0085 || x == 0x00a0 || x == 0x1680 ||
                    (0x2000 <= x && x <= 0x200a) || x == 0x2028 ||
                    x == 0x2029 || x == 0x202F || x == 0x205F || x == 0x3000) {
                    ++first;
                    return;
                }
                success = false;
            }
        }
    };

    /** The end-of-line parser.  This matches "\r\n", or any one of the line
        break code points from the Unicode Line Break Algorithm, described in
        https://unicode.org/reports/tr14.  Produces no attribute. */
    inline constexpr parser_interface<ws_parser<true>> eol;

    /** The whitespace parser.  This matches "\r\n", or any one of the Unicode
        code points with the White_Space property, as defined in
        https://www.unicode.org/Public/UCD/latest/ucd/PropList.txt.  Produces
        no attribute. */
    inline constexpr parser_interface<ws_parser<false>> ws;

    namespace ascii {

        /** Matches the characters for which `std::isalnum()` is true. */
        inline constexpr parser_interface<char_parser<
            detail::ascii_char_class<detail::ascii_char_class_t::alnum>>>
            alnum;

        /** Matches the characters for which `std::alpha()` is true. */
        inline constexpr parser_interface<char_parser<
            detail::ascii_char_class<detail::ascii_char_class_t::alpha>>>
            alpha;

        /** Matches the characters for which `std::isblank()` is true. */
        inline constexpr parser_interface<char_parser<
            detail::ascii_char_class<detail::ascii_char_class_t::blank>>>
            blank;

        /** Matches the characters for which `std::iscntrl()` is true. */
        inline constexpr parser_interface<char_parser<
            detail::ascii_char_class<detail::ascii_char_class_t::cntrl>>>
            cntrl;

        /** Matches the characters for which `std::isdigit()` is true. */
        inline constexpr parser_interface<char_parser<
            detail::ascii_char_class<detail::ascii_char_class_t::digit>>>
            digit;

        /** Matches the characters for which `std::isgraph()` is true. */
        inline constexpr parser_interface<char_parser<
            detail::ascii_char_class<detail::ascii_char_class_t::graph>>>
            graph;

        /** Matches the characters for which `std::isprint()` is true. */
        inline constexpr parser_interface<char_parser<
            detail::ascii_char_class<detail::ascii_char_class_t::print>>>
            print;

        /** Matches the characters for which `std::ispunct()` is true. */
        inline constexpr parser_interface<char_parser<
            detail::ascii_char_class<detail::ascii_char_class_t::punct>>>
            punct;

        /** Matches the characters for which `std::isspace()` is true. */
        inline constexpr parser_interface<char_parser<
            detail::ascii_char_class<detail::ascii_char_class_t::space>>>
            space;

        /** Matches the characters for which `std::isxdigit()` is true. */
        inline constexpr parser_interface<char_parser<
            detail::ascii_char_class<detail::ascii_char_class_t::xdigit>>>
            xdigit;

        /** Matches the characters for which `std::islower()` is true. */
        inline constexpr parser_interface<char_parser<
            detail::ascii_char_class<detail::ascii_char_class_t::lower>>>
            lower;

        /** Matches the characters for which `std::isupper()` is true. */
        inline constexpr parser_interface<char_parser<
            detail::ascii_char_class<detail::ascii_char_class_t::upper>>>
            upper;
    }

    struct bool_parser
    {
        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser>
        bool call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            bool retval;
            call(use_cbs, first, last, context, skip, flags, success, retval);
            return retval;
        }

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = detail::scoped_trace(
                *this, first, last, context, flags, retval);

            // The lambda quiets a signed/unsigned mismatch warning when
            // comparing the chars here to code points.
            char const t[] = "true";
            if (detail::mismatch(
                    t,
                    t + 4,
                    first,
                    last,
                    [](uint32_t a, uint32_t b) { return a == b; })
                    .first == t + 4) {
                std::advance(first, 4);
                detail::assign(retval, true);
                return;
            }
            char const f[] = "false";
            if (detail::mismatch(
                    f,
                    f + 5,
                    first,
                    last,
                    [](uint32_t a, uint32_t b) { return a == b; })
                    .first == f + 5) {
                std::advance(first, 5);
                detail::assign(retval, false);
                return;
            }
            success = false;
        }
    };

    /** The Boolean parser.  Parses "true" and "false", producing attributes
        `true` and `false`, respectively, and fails on any other input. */
    inline constexpr parser_interface<bool_parser> bool_;

    template<
        typename T,
        int Radix,
        int MinDigits,
        int MaxDigits,
        typename Expected>
    struct uint_parser
    {
        static_assert(2 <= Radix && Radix <= 36, "Unsupported radix.");

        constexpr uint_parser() {}
        explicit constexpr uint_parser(Expected expected) : expected_(expected)
        {}

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser>
        T call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            T retval;
            call(use_cbs, first, last, context, skip, flags, success, retval);
            return retval;
        }

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = detail::scoped_trace(
                *this, first, last, context, flags, retval);
            using extract =
                detail_spirit_x3::extract_uint<T, Radix, MinDigits, MaxDigits>;
            T attr = 0;
            success = extract::call(first, last, attr);
            if (attr != detail::resolve(context, expected_))
                success = false;
            if (success)
                detail::assign(retval, attr);
        }

        /** Returns a `parser_interface` containing a `uint_parser` that
            matches the exact value `expected`. */
        template<typename Expected2>
        constexpr auto operator()(Expected2 expected) const noexcept
        {
            BOOST_PARSER_ASSERT(
                (detail::is_nope_v<Expected> &&
                 "If you're seeing this, you tried to chain calls on this "
                 "parser, like 'uint_(2)(3)'.  Quit it!'"));
            using parser_t =
                uint_parser<T, Radix, MinDigits, MaxDigits, Expected2>;
            return parser_interface{parser_t{expected}};
        }

        Expected expected_;
    };

    /** The binary unsigned integer parser.  Produces an `unsigned int`
        attribute.  To parse a particular value `x`, use `bin(x)`. */
    inline constexpr parser_interface<uint_parser<unsigned int, 2>> bin;

    /** The octal unsigned integer parser.  Produces an `unsigned int`
        attribute.  To parse a particular value `x`, use `oct(x)`. */
    inline constexpr parser_interface<uint_parser<unsigned int, 8>> oct;

    /** The hexidecimal unsigned integer parser.  Produces an `unsigned int`
        attribute.  To parse a particular value `x`, use `hex(x)`. */
    inline constexpr parser_interface<uint_parser<unsigned int, 16>> hex;

    /** The `unsigned short` parser.  Produces an `unsigned short` attribute.
        To parse a particular value `x`, use `ushort_(x)`. */
    inline constexpr parser_interface<uint_parser<unsigned short>> ushort_;

    /** The `unsigned int` parser.  Produces an `unsigned int` attribute.  To
        parse a particular value `x`, use `uint_(x)`. */
    inline constexpr parser_interface<uint_parser<unsigned int>> uint_;

    /** The `unsigned long` parser.  Produces an `unsigned long` attribute.
        To parse a particular value `x`, use `ulong_(x)`. */
    inline constexpr parser_interface<uint_parser<unsigned long>> ulong_;

    /** The `unsigned long long` parser.  Produces an `unsigned long long`
        attribute.  To parse a particular value `x`, use `ulong_long(x)`. */
    inline constexpr parser_interface<uint_parser<unsigned long long>>
        ulong_long;

    template<
        typename T,
        int Radix,
        int MinDigits,
        int MaxDigits,
        typename Expected>
    struct int_parser
    {
        static_assert(
            Radix == 2 || Radix == 8 || Radix == 10 || Radix == 16,
            "Unsupported radix.");

        constexpr int_parser() {}
        explicit constexpr int_parser(Expected expected) : expected_(expected)
        {}

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser>
        T call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            T retval;
            call(use_cbs, first, last, context, skip, flags, success, retval);
            return retval;
        }

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = detail::scoped_trace(
                *this, first, last, context, flags, retval);
            using extract =
                detail_spirit_x3::extract_int<T, Radix, MinDigits, MaxDigits>;
            T attr = 0;
            auto const initial = first;
            success = extract::call(first, last, attr);
            if (first == initial || attr != detail::resolve(context, expected_))
                success = false;
            if (success)
                detail::assign(retval, attr);
        }

        /** Returns a `parser_interface` containing an `int_parser` that
            matches the exact value `expected`. */
        template<typename Expected2>
        constexpr auto operator()(Expected2 expected) const noexcept
        {
            BOOST_PARSER_ASSERT(
                (detail::is_nope_v<Expected> &&
                 "If you're seeing this, you tried to chain calls on this "
                 "parser, like 'int_(2)(3)'.  Quit it!'"));
            using parser_t =
                int_parser<T, Radix, MinDigits, MaxDigits, Expected2>;
            return parser_interface{parser_t{expected}};
        }

        Expected expected_;
    };

    /** The `short` parser.  Produces a `short` attribute.  To parse a
        particular value `x`, use `short_(x)`. */
    inline constexpr parser_interface<int_parser<short>> short_;

    /** The `int` parser.  Produces an `int` attribute.  To parse a particular
        value `x`, use `int_(x)`. */
    inline constexpr parser_interface<int_parser<int>> int_;

    /** The `long` parser.  Produces a `long` attribute.  To parse a particular
        value `x`, use `long_(x)`. */
    inline constexpr parser_interface<int_parser<long>> long_;

    /** The `long long` parser.  Produces a `long long` attribute.  To parse a
        particular value `x`, use `long_long(x)`. */
    inline constexpr parser_interface<int_parser<long long>> long_long;

    template<typename T>
    struct float_parser
    {
        constexpr float_parser() {}

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser>
        T call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            T retval;
            call(use_cbs, first, last, context, skip, flags, success, retval);
            return retval;
        }

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = detail::scoped_trace(
                *this, first, last, context, flags, retval);
            detail_spirit_x3::real_policies<T> policies;
            using extract = detail_spirit_x3::
                extract_real<T, detail_spirit_x3::real_policies<T>>;
            T attr = 0;
            auto const initial = first;
            success = extract::parse(first, last, attr, policies);
            if (first == initial)
                success = false;
            if (success)
                detail::assign(retval, attr);
        }
    };

    /** The `float` parser.  Produces a `float` attribute. */
    inline constexpr parser_interface<float_parser<float>> float_;

    /** The `double` parser.  Produces a `double` attribute. */
    inline constexpr parser_interface<float_parser<double>> double_;


    /** Represents a sequence parser, the first parser of which is an
        `epsilon_parser` with predicate, as a directive
        (e.g. `if_(pred)[p]`). */
    template<typename Predicate>
    struct if_directive
    {
        template<typename Parser2>
        constexpr auto operator[](parser_interface<Parser2> rhs) const noexcept
        {
            return eps(pred_) >> rhs;
        }

        Predicate pred_;
    };

    /** Returns an `if_directive` that fails if the given predicate `pred` is
        `false`, and otherwise, applies another parser.  For instance, in
        `if_(pred)[p]`, `p` is only applied if `pred` is true. */
    template<typename Predicate>
    constexpr auto if_(Predicate pred) noexcept
    {
        return if_directive<Predicate>{pred};
    }

    namespace detail {
        template<typename SwitchValue, typename Value>
        struct switch_parser_equal
        {
            template<typename Context>
            bool operator()(Context & context) const
            {
                auto const switch_value =
                    detail::resolve(context, switch_value_);
                auto const value = detail::resolve(context, value_);
                return value == switch_value;
            }
            SwitchValue switch_value_;
            Value value_;
        };
    }

    template<typename SwitchValue, typename OrParser>
    struct switch_parser
    {
        switch_parser() {}
        switch_parser(SwitchValue switch_value) : switch_value_(switch_value) {}
        switch_parser(SwitchValue switch_value, OrParser or_parser) :
            switch_value_(switch_value), or_parser_(or_parser)
        {}

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser>
        auto call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            BOOST_PARSER_ASSERT(
                (!detail::is_nope_v<OrParser> &&
                 "It looks like you tried to write switch_(val).  You need at "
                 "least one alternative, like: switch_(val)(value_1, "
                 "parser_1)(value_2, parser_2)..."));
            using attr_t = decltype(or_parser_.call(
                use_cbs, first, last, context, skip, flags, success));
            attr_t attr{};
            auto _ =
                detail::scoped_trace(*this, first, last, context, flags, attr);
            attr = or_parser_.call(
                use_cbs, first, last, context, skip, flags, success);
            return attr;
        }

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            BOOST_PARSER_ASSERT(
                (!detail::is_nope_v<OrParser>,
                 "It looks like you tried to write switch_(val).  You need at "
                 "least one alternative, like: switch_(val)(value_1, "
                 "parser_1)(value_2, parser_2)..."));
            auto _ = detail::scoped_trace(
                *this, first, last, context, flags, retval);
            or_parser_.call(
                use_cbs, first, last, context, skip, flags, success, retval);
        }

        /** Returns a `parser_interface` containing a `switch_parser`, with
            the case `value_`,`rhs` appended to its `or_parser_`. */
        template<typename Value, typename Parser2>
        constexpr auto
        operator()(Value value_, parser_interface<Parser2> rhs) const noexcept
        {
            auto const match = detail::switch_parser_equal<SwitchValue, Value>{
                switch_value_, value_};
            auto or_parser = make_or_parser(or_parser_, eps(match) >> rhs);
            using switch_parser_type =
                switch_parser<SwitchValue, decltype(or_parser)>;
            return parser_interface{
                switch_parser_type{switch_value_, or_parser}};
        }

#ifndef BOOST_PARSER_DOXYGEN

        template<typename Parser1, typename Parser2>
        static constexpr auto
        make_or_parser(Parser1 parser1, parser_interface<Parser2> parser2)
        {
            return (parser_interface{parser1} | parser2).parser_;
        }

        template<typename Parser>
        static constexpr auto
        make_or_parser(detail::nope, parser_interface<Parser> parser)
        {
            return parser.parser_;
        }

#endif

        SwitchValue switch_value_;
        OrParser or_parser_;
    };

    /** Returns a `switch`-like parser.  The resulting parser uses the given
        value `x` to select one of the following value/parser pairs, and to
        apply the selected parser.  `x` may be a value to be used directly, or
        a unary invocable that takes a reference to the parse context, and
        returns the value to use.  You can add more value/parser cases to the
        returned parser, using its call operator, e.g. `switch_(x)(y1, p1)(y2,
        p2)`.  As with the `x` passed to this function, each `yN` value can be
        a value or a unary invocable. */
    template<typename T>
    constexpr auto switch_(T x) noexcept
    {
        return switch_parser<T>{x};
    }


#ifndef BOOST_PARSER_DOXYGEN

    template<typename Parser, typename GlobalState, typename ErrorHandler>
    constexpr auto
    parser_interface<Parser, GlobalState, ErrorHandler>::operator>>(
        char rhs) const noexcept
    {
        return *this >> parser::lit(rhs);
    }

    template<typename Parser, typename GlobalState, typename ErrorHandler>
    constexpr auto
    parser_interface<Parser, GlobalState, ErrorHandler>::operator>>(
        char32_t rhs) const noexcept
    {
        return *this >> parser::lit(rhs);
    }

    template<typename Parser, typename GlobalState, typename ErrorHandler>
#if BOOST_PARSER_USE_CONCEPTS
    template<parsable_range_like R>
#else
    template<typename R, typename>
#endif
    constexpr auto
    parser_interface<Parser, GlobalState, ErrorHandler>::operator>>(
        R && r) const noexcept
    {
        return *this >> parser::lit(r);
    }

#endif

    /** Returns a parser equivalent to `lit(c) >> rhs`. */
    template<typename Parser>
    constexpr auto operator>>(char c, parser_interface<Parser> rhs) noexcept
    {
        if constexpr (detail::is_seq_p<Parser>{}) {
            return rhs.parser_.template prepend<true>(parser::lit(c));
        } else {
            return parser::lit(c) >> rhs;
        }
    }

    /** Returns a parser equivalent to `lit(c) >> rhs`. */
    template<typename Parser>
    constexpr auto operator>>(char32_t c, parser_interface<Parser> rhs) noexcept
    {
        if constexpr (detail::is_seq_p<Parser>{}) {
            return rhs.parser_.template prepend<true>(parser::lit(c));
        } else {
            return parser::lit(c) >> rhs;
        }
    }

    /** Returns a parser equivalent to `lit(str) >> rhs`. */
#if BOOST_PARSER_USE_CONCEPTS
    template<parsable_range_like R, typename Parser>
#else
    template<
        typename R,
        typename Parser,
        typename Enable =
            std::enable_if_t<detail::is_parsable_range_like<R>::value>>
#endif
    constexpr auto operator>>(R && r, parser_interface<Parser> rhs) noexcept
    {
        if constexpr (detail::is_seq_p<Parser>{}) {
            return rhs.parser_.template prepend<true>(parser::lit(r));
        } else {
            return parser::lit(r) >> rhs;
        }
    }

#ifndef BOOST_PARSER_DOXYGEN

    template<typename Parser, typename GlobalState, typename ErrorHandler>
    constexpr auto
    parser_interface<Parser, GlobalState, ErrorHandler>::operator>(
        char rhs) const noexcept
    {
        return *this > parser::lit(rhs);
    }

    template<typename Parser, typename GlobalState, typename ErrorHandler>
    constexpr auto
    parser_interface<Parser, GlobalState, ErrorHandler>::operator>(
        char32_t rhs) const noexcept
    {
        return *this > parser::lit(rhs);
    }

    template<typename Parser, typename GlobalState, typename ErrorHandler>
#if BOOST_PARSER_USE_CONCEPTS
    template<parsable_range_like R>
#else
    template<typename R, typename>
#endif
    constexpr auto
    parser_interface<Parser, GlobalState, ErrorHandler>::operator>(
        R && r) const noexcept
    {
        return *this > parser::lit(r);
    }

#endif

    /** Returns a parser equivalent to `lit(c) > rhs`. */
    template<typename Parser>
    constexpr auto operator>(char c, parser_interface<Parser> rhs) noexcept
    {
        if constexpr (detail::is_seq_p<Parser>{}) {
            return rhs.parser_.template prepend<false>(parser::lit(c));
        } else {
            return parser::lit(c) > rhs;
        }
    }

    /** Returns a parser equivalent to `lit(c) > rhs`. */
    template<typename Parser>
    constexpr auto operator>(char32_t c, parser_interface<Parser> rhs) noexcept
    {
        if constexpr (detail::is_seq_p<Parser>{}) {
            return rhs.parser_.template prepend<false>(parser::lit(c));
        } else {
            return parser::lit(c) > rhs;
        }
    }

    /** Returns a parser equivalent to `lit(str) > rhs`. */
#if BOOST_PARSER_USE_CONCEPTS
    template<parsable_range_like R, typename Parser>
#else
    template<
        typename R,
        typename Parser,
        typename Enable =
            std::enable_if_t<detail::is_parsable_range_like<R>::value>>
#endif
    constexpr auto operator>(R && r, parser_interface<Parser> rhs) noexcept
    {
        if constexpr (detail::is_seq_p<Parser>{}) {
            return rhs.parser_.template prepend<false>(parser::lit(r));
        } else {
            return parser::lit(r) > rhs;
        }
    }

#ifndef BOOST_PARSER_DOXYGEN

    template<typename Parser, typename GlobalState, typename ErrorHandler>
    constexpr auto
    parser_interface<Parser, GlobalState, ErrorHandler>::operator|(
        char rhs) const noexcept
    {
        return *this | parser::lit(rhs);
    }

    template<typename Parser, typename GlobalState, typename ErrorHandler>
    constexpr auto
    parser_interface<Parser, GlobalState, ErrorHandler>::operator|(
        char32_t rhs) const noexcept
    {
        return *this | parser::lit(rhs);
    }

    template<typename Parser, typename GlobalState, typename ErrorHandler>
#if BOOST_PARSER_USE_CONCEPTS
    template<parsable_range_like R>
#else
    template<typename R, typename>
#endif
    constexpr auto
    parser_interface<Parser, GlobalState, ErrorHandler>::operator|(
        R && r) const noexcept
    {
        return *this | parser::lit(r);
    }

#endif

    /** Returns a parser equivalent to `lit(c) | rhs`. */
    template<typename Parser>
    constexpr auto operator|(char c, parser_interface<Parser> rhs) noexcept
    {
        if constexpr (detail::is_or_p<Parser>{}) {
            return rhs.parser_.prepend(parser::lit(c));
        } else {
            return parser::lit(c) | rhs;
        }
    }

    /** Returns a parser equivalent to `lit(c) | rhs`. */
    template<typename Parser>
    constexpr auto operator|(char32_t c, parser_interface<Parser> rhs) noexcept
    {
        if constexpr (detail::is_or_p<Parser>{}) {
            return rhs.parser_.prepend(parser::lit(c));
        } else {
            return parser::lit(c) | rhs;
        }
    }

    /** Returns a parser equivalent to `lit(str) | rhs`. */
#if BOOST_PARSER_USE_CONCEPTS
    template<parsable_range_like R, typename Parser>
#else
    template<
        typename R,
        typename Parser,
        typename Enable =
            std::enable_if_t<detail::is_parsable_range_like<R>::value>>
#endif
    constexpr auto operator|(R && r, parser_interface<Parser> rhs) noexcept
    {
        if constexpr (detail::is_or_p<Parser>{}) {
            return rhs.parser_.prepend(parser::lit(r));
        } else {
            return parser::lit(r) | rhs;
        }
    }

#ifndef BOOST_PARSER_DOXYGEN

    template<typename Parser, typename GlobalState, typename ErrorHandler>
    constexpr auto
    parser_interface<Parser, GlobalState, ErrorHandler>::operator-(
        char rhs) const noexcept
    {
        return !parser::lit(rhs) >> *this;
    }

    template<typename Parser, typename GlobalState, typename ErrorHandler>
    constexpr auto
    parser_interface<Parser, GlobalState, ErrorHandler>::operator-(
        char32_t rhs) const noexcept
    {
        return !parser::lit(rhs) >> *this;
    }

    template<typename Parser, typename GlobalState, typename ErrorHandler>
#if BOOST_PARSER_USE_CONCEPTS
    template<parsable_range_like R>
#else
    template<typename R, typename>
#endif
    constexpr auto
    parser_interface<Parser, GlobalState, ErrorHandler>::operator-(
        R && r) const noexcept
    {
        return !parser::lit(r) >> *this;
    }

#endif

    /** Returns a parser equivalent to `!rhs >> lit(c)`. */
    template<typename Parser>
    constexpr auto operator-(char c, parser_interface<Parser> rhs) noexcept
    {
        return !rhs >> parser::lit(c);
    }

    /** Returns a parser equivalent to `!rhs >> lit(c)`. */
    template<typename Parser>
    constexpr auto operator-(char32_t c, parser_interface<Parser> rhs) noexcept
    {
        return !rhs >> parser::lit(c);
    }

    /** Returns a parser equivalent to `!rhs >> lit(str)`. */
#if BOOST_PARSER_USE_CONCEPTS
    template<parsable_range_like R, typename Parser>
#else
    template<
        typename R,
        typename Parser,
        typename Enable =
            std::enable_if_t<detail::is_parsable_range_like<R>::value>>
#endif
    constexpr auto operator-(R && r, parser_interface<Parser> rhs) noexcept
    {
        return !rhs >> parser::lit(r);
    }

#ifndef BOOST_PARSER_DOXYGEN

    template<typename Parser, typename GlobalState, typename ErrorHandler>
    constexpr auto
    parser_interface<Parser, GlobalState, ErrorHandler>::operator%(
        char rhs) const noexcept
    {
        return *this % parser::lit(rhs);
    }

    template<typename Parser, typename GlobalState, typename ErrorHandler>
    constexpr auto
    parser_interface<Parser, GlobalState, ErrorHandler>::operator%(
        char32_t rhs) const noexcept
    {
        return *this % parser::lit(rhs);
    }

    template<typename Parser, typename GlobalState, typename ErrorHandler>
#if BOOST_PARSER_USE_CONCEPTS
    template<parsable_range_like R>
#else
    template<typename R, typename>
#endif
    constexpr auto
    parser_interface<Parser, GlobalState, ErrorHandler>::operator%(
        R && r) const noexcept
    {
        return *this % parser::lit(r);
    }

#endif

    /** Returns a parser equivalent to `lit(c) % rhs`. */
    template<typename Parser>
    constexpr auto operator%(char c, parser_interface<Parser> rhs) noexcept
    {
        return parser::lit(c) % rhs;
    }

    /** Returns a parser equivalent to `lit(c) % rhs`. */
    template<typename Parser>
    constexpr auto operator%(char32_t c, parser_interface<Parser> rhs) noexcept
    {
        return parser::lit(c) % rhs;
    }

    /** Returns a parser equivalent to `lit(str) % rhs`. */
#if BOOST_PARSER_USE_CONCEPTS
    template<parsable_range_like R, typename Parser>
#else
    template<
        typename R,
        typename Parser,
        typename Enable =
            std::enable_if_t<detail::is_parsable_range_like<R>::value>>
#endif
    constexpr auto operator%(R && r, parser_interface<Parser> rhs) noexcept
    {
        return parser::lit(r) % rhs;
    }

}}

#include <boost/parser/detail/printing_impl.hpp>

namespace boost { namespace parser {

#if !BOOST_PARSER_USE_CONCEPTS
#if defined(__cpp_char8_t)
    template<typename T>
    struct is_char8_iter
        : std::integral_constant<
              bool,
              (std::is_integral_v<detail::detected_t<detail::text::detail::value_type_, T>> &&
               std::is_same_v<
                   detail::remove_cv_ref_t<
                       detail::detected_t<detail::text::detail::value_type_, T>>,
                   char8_t>)>
    {};

    template<typename T>
    constexpr bool char8_iter = is_char8_iter<T>::value;
#else
    template<typename T>
    constexpr bool char8_iter = false;
#endif
#endif

    /** An enumeration used for parameters to enable and disable trace in the
        `*parse()` functions. */
    enum class trace { on, off };

    // Parse API.

    /** Parses `[first, last)` using `parser`, and returns whether the parse
        was successful.  On success, `attr` will be assigned the value of the
        attribute produced by `parser`.  If `trace_mode == trace::on`, a
        verbose trace of the parse will be streamed to `std::cout`. */
#if BOOST_PARSER_USE_CONCEPTS
    template<
        parsable_iter I,
        std::sentinel_for<I> S,
        typename Parser,
        typename GlobalState,
        error_handler<I, S, GlobalState> ErrorHandler,
        typename Attr>
#else
    template<
        typename I,
        typename S,
        typename Parser,
        typename GlobalState,
        typename ErrorHandler,
        typename Attr,
        typename Enable = std::enable_if_t<
            detail::is_parsable_iter<I>::value &&
            detail::is_equality_comparable_with<I, S>::value>>
#endif
    bool parse(
        I & first,
        S last,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        Attr & attr,
        trace trace_mode = trace::off)
    {
        if constexpr (
            (detail::non_unicode_char_range_like<view<I, S>> &&
             !char8_iter<I>) ||
            sizeof(*first) == 4u) {
            // If you're seeing this error, you're trying to get parse() to
            // fill in attr above, using the attribute generated by parser.
            // However, parser does not generate an attribute.
            static_assert(
                decltype(detail::has_attribute(first, last, parser)){});
            if (trace_mode == trace::on) {
                return detail::parse_impl<true>(
                    first, last, parser, parser.error_handler_, attr);
            } else {
                return detail::parse_impl<false>(
                    first, last, parser, parser.error_handler_, attr);
            }
        } else {
            auto r = parser::detail::text::as_utf32(first, last);
            auto f = r.begin();
            auto const l = r.end();
            auto _ = detail::scoped_base_assign(first, f);
            // If you're seeing this error, you're trying to get parse() to
            // fill in attr above, using the attribute generated by parser.
            // However, parser does not generate an attribute.
            static_assert(decltype(detail::has_attribute(f, l, parser)){});
            if (trace_mode == trace::on) {
                return detail::parse_impl<true>(
                    f, l, parser, parser.error_handler_, attr);
            } else {
                return detail::parse_impl<false>(
                    f, l, parser, parser.error_handler_, attr);
            }
        }
    }

    /** Parses `str` using `parser`, and returns whether the parse was
        successful.  The entire input range `r` must be consumed for the parse
        to be considered successful.  On success, `attr` will be assigned the
        value of the attribute produced by `parser`.  If `trace_mode ==
        trace::on`, a verbose trace of the parse will be streamed to
        `std::cout`. */
#if BOOST_PARSER_USE_CONCEPTS
    template<
        parsable_range_like R,
        typename Parser,
        typename GlobalState,
        typename ErrorHandler,
        typename Attr>
#else
    template<
        typename R,
        typename Parser,
        typename GlobalState,
        typename ErrorHandler,
        typename Attr,
        typename Enable =
            std::enable_if_t<detail::is_parsable_range_like<R>::value>>
#endif
    bool parse(
        R const & r,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        Attr & attr,
        trace trace_mode = trace::off)
#if BOOST_PARSER_USE_CONCEPTS
        // clang-format off
        requires error_handler<
            ErrorHandler,
            std::ranges::iterator_t<decltype(detail::make_input_view(r))>,
            std::ranges::sentinel_t<decltype(detail::make_input_view(r))>,
            GlobalState>
    // clang-format on
#endif
    {
        auto r_ = detail::make_input_view(r);
        auto first = r_.begin();
        auto const last = r_.end();
        return detail::if_full_parse(
            first, last, parser::parse(first, last, parser, attr, trace_mode));
    }

    /** Parses `[first, last)` using `parser`.  Returns a `std::optional`
        containing the attribute produced by `parser` on parse success, and
        `std::nullopt` on parse failure.  If `trace_mode == trace::on`, a
        verbose trace of the parse will be streamed to `std::cout`. */
#if BOOST_PARSER_USE_CONCEPTS
    template<
        parsable_iter I,
        std::sentinel_for<I> S,
        typename Parser,
        typename GlobalState,
        error_handler<I, S, GlobalState> ErrorHandler>
#else
    template<
        typename I,
        typename S,
        typename Parser,
        typename GlobalState,
        typename ErrorHandler,
        typename Enable = std::enable_if_t<
            detail::is_parsable_iter<I>::value &&
            detail::is_equality_comparable_with<I, S>::value>>
#endif
    auto parse(
        I & first,
        S last,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        trace trace_mode = trace::off)
    {
        if constexpr (
            (detail::non_unicode_char_range_like<view<I, S>> &&
             !char8_iter<I>) ||
            sizeof(*first) == 4u) {
            if (trace_mode == trace::on) {
                return detail::parse_impl<true>(
                    first, last, parser, parser.error_handler_);
            } else {
                return detail::parse_impl<false>(
                    first, last, parser, parser.error_handler_);
            }
        } else {
            auto r = parser::detail::text::as_utf32(first, last);
            auto f = r.begin();
            auto const l = r.end();
            auto _ = detail::scoped_base_assign(first, f);
            if (trace_mode == trace::on) {
                return detail::parse_impl<true>(
                    f, l, parser, parser.error_handler_);
            } else {
                return detail::parse_impl<false>(
                    f, l, parser, parser.error_handler_);
            }
        }
    }

    /** Parses `str` using `parser`.  Returns a `std::optional` containing the
        attribute produced by `parser` on parse success, and `std::nullopt` on
        parse failure.  The entire input range `r` must be consumed for the
        parse to be considered successful.  If `trace_mode == trace::on`, a
        verbose trace of the parse will be streamed to `std::cout`. */
#if BOOST_PARSER_USE_CONCEPTS
    template<
        parsable_range_like R,
        typename Parser,
        typename GlobalState,
        typename ErrorHandler>
#else
    template<
        typename R,
        typename Parser,
        typename GlobalState,
        typename ErrorHandler,
        typename Enable =
            std::enable_if_t<detail::is_parsable_range_like<R>::value>>
#endif
    auto parse(
        R const & r,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        trace trace_mode = trace::off)
#if BOOST_PARSER_USE_CONCEPTS
        // clang-format off
        requires error_handler<
            ErrorHandler,
            std::ranges::iterator_t<decltype(detail::make_input_view(r))>,
            std::ranges::sentinel_t<decltype(detail::make_input_view(r))>,
            GlobalState>
    // clang-format on
#endif
    {
        auto r_ = detail::make_input_view(r);
        auto first = r_.begin();
        auto const last = r_.end();
        return detail::if_full_parse(
            first, last, parser::parse(first, last, parser, trace_mode));
    }

    /** Parses `[first, last)` using `parser`, skipping all input recognized
        by `skip` between the application of any two parsers, and returns
        whether the parse was successful.  On success, `attr` will be assigned
        the value of the attribute produced by `parser`.  If `trace_mode ==
        trace::on`, a verbose trace of the parse will be streamed to
        `std::cout`. */
#if BOOST_PARSER_USE_CONCEPTS
    template<
        parsable_iter I,
        std::sentinel_for<I> S,
        typename Parser,
        typename GlobalState,
        error_handler<I, S, GlobalState> ErrorHandler,
        typename SkipParser,
        typename Attr>
#else
    template<
        typename I,
        typename S,
        typename Parser,
        typename GlobalState,
        typename ErrorHandler,
        typename SkipParser,
        typename Attr,
        typename Enable = std::enable_if_t<
            detail::is_parsable_iter<I>::value &&
            detail::is_equality_comparable_with<I, S>::value>>
#endif
    bool parse(
        I & first,
        S last,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        parser_interface<SkipParser> const & skip,
        Attr & attr,
        trace trace_mode = trace::off)
    {
        if constexpr (
            (detail::non_unicode_char_range_like<view<I, S>> &&
             !char8_iter<I>) ||
            sizeof(*first) == 4u) {
            // If you're seeing this error, you're trying to get parse() to
            // fill in attr above, using the attribute generated by parser.
            // However, parser does not generate an attribute.
            static_assert(
                decltype(detail::has_attribute(first, last, parser)){});
            if (trace_mode == trace::on) {
                return detail::skip_parse_impl<true>(
                    first, last, parser, skip, parser.error_handler_, attr);
            } else {
                return detail::skip_parse_impl<false>(
                    first, last, parser, skip, parser.error_handler_, attr);
            }
        } else {
            auto r = parser::detail::text::as_utf32(first, last);
            auto f = r.begin();
            auto const l = r.end();
            auto _ = detail::scoped_base_assign(first, f);
            // If you're seeing this error, you're trying to get parse() to
            // fill in attr above, using the attribute generated by parser.
            // However, parser does not generate an attribute.
            static_assert(decltype(detail::has_attribute(f, l, parser)){});
            if (trace_mode == trace::on) {
                return detail::skip_parse_impl<true>(
                    f, l, parser, skip, parser.error_handler_, attr);
            } else {
                return detail::skip_parse_impl<false>(
                    f, l, parser, skip, parser.error_handler_, attr);
            }
        }
    }

    /** Parses `str` using `parser`, skipping all input recognized by `skip`
        between the application of any two parsers, and returns whether the
        parse was successful.  The entire input range `r` must be consumed for
        the parse to be considered successful.  On success, `attr` will be
        assigned the value of the attribute produced by `parser`.  If
        `trace_mode == trace::on`, a verbose trace of the parse will be
        streamed to `std::cout`. */
#if BOOST_PARSER_USE_CONCEPTS
    template<
        parsable_range_like R,
        typename Parser,
        typename GlobalState,
        typename ErrorHandler,
        typename SkipParser,
        typename Attr>
#else
    template<
        typename R,
        typename Parser,
        typename GlobalState,
        typename ErrorHandler,
        typename SkipParser,
        typename Attr,
        typename Enable =
            std::enable_if_t<detail::is_parsable_range_like<R>::value>>
#endif
    bool parse(
        R const & r,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        parser_interface<SkipParser> const & skip,
        Attr & attr,
        trace trace_mode = trace::off)
#if BOOST_PARSER_USE_CONCEPTS
        // clang-format off
        requires error_handler<
            ErrorHandler,
            std::ranges::iterator_t<decltype(detail::make_input_view(r))>,
            std::ranges::sentinel_t<decltype(detail::make_input_view(r))>,
            GlobalState>
    // clang-format on
#endif
    {
        auto r_ = detail::make_input_view(r);
        auto first = r_.begin();
        auto const last = r_.end();
        return detail::if_full_parse(
            first,
            last,
            parser::parse(first, last, parser, skip, attr, trace_mode));
    }

    /** Parses `[first, last)` using `parser`, skipping all input recognized
        by `skip` between the application of any two parsers.  Returns a
        `std::optional` containing the attribute produced by `parser` on parse
        success, and `std::nullopt` on parse failure.  If `trace_mode ==
        trace::on`, a verbose trace of the parse will be streamed to
        `std::cout`. */
#if BOOST_PARSER_USE_CONCEPTS
    template<
        parsable_iter I,
        std::sentinel_for<I> S,
        typename Parser,
        typename GlobalState,
        error_handler<I, S, GlobalState> ErrorHandler,
        typename SkipParser>
#else
    template<
        typename I,
        typename S,
        typename Parser,
        typename GlobalState,
        typename ErrorHandler,
        typename SkipParser,
        typename Enable = std::enable_if_t<
            detail::is_parsable_iter<I>::value &&
            detail::is_equality_comparable_with<I, S>::value>>
#endif
    auto parse(
        I & first,
        S last,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        parser_interface<SkipParser> const & skip,
        trace trace_mode = trace::off)
    {
        if constexpr (
            (detail::non_unicode_char_range_like<view<I, S>> &&
             !char8_iter<I>) ||
            sizeof(*first) == 4u) {
            if (trace_mode == trace::on) {
                return detail::skip_parse_impl<true>(
                    first, last, parser, skip, parser.error_handler_);
            } else {
                return detail::skip_parse_impl<false>(
                    first, last, parser, skip, parser.error_handler_);
            }
        } else {
            auto r = parser::detail::text::as_utf32(first, last);
            auto f = r.begin();
            auto const l = r.end();
            auto _ = detail::scoped_base_assign(first, f);
            if (trace_mode == trace::on) {
                return detail::skip_parse_impl<true>(
                    f, l, parser, skip, parser.error_handler_);
            } else {
                return detail::skip_parse_impl<false>(
                    f, l, parser, skip, parser.error_handler_);
            }
        }
    }

#ifndef BOOST_PARSER_DOXYGEN

#if BOOST_PARSER_USE_CONCEPTS
    template<
        parsable_iter I,
        std::sentinel_for<I> S,
        typename Parser,
        typename GlobalState,
        error_handler<I, S, GlobalState> ErrorHandler,
        typename TagType,
        typename Attribute,
        typename LocalState,
        typename ParamsTuple>
#else
    template<
        typename I,
        typename S,
        typename Parser,
        typename GlobalState,
        typename ErrorHandler,
        typename TagType,
        typename Attribute,
        typename LocalState,
        typename ParamsTuple,
        typename Enable = std::enable_if_t<
            detail::is_parsable_iter<I>::value &&
            detail::is_equality_comparable_with<I, S>::value>>
#endif
    auto parse(
        I & first,
        S last,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        rule<TagType, Attribute, LocalState, ParamsTuple> const & skip,
        trace trace_mode = trace::off)
    {
        if constexpr (
            (detail::non_unicode_char_range_like<view<I, S>> &&
             !char8_iter<I>) ||
            sizeof(*first) == 4u) {
            if (trace_mode == trace::on) {
                return detail::skip_parse_impl<true>(
                    first, last, parser, skip, parser.error_handler_);
            } else {
                return detail::skip_parse_impl<false>(
                    first, last, parser, skip, parser.error_handler_);
            }
        } else {
            auto r = parser::detail::text::as_utf32(first, last);
            auto f = r.begin();
            auto const l = r.end();
            auto _ = detail::scoped_base_assign(first, f);
            if (trace_mode == trace::on) {
                return detail::skip_parse_impl<true>(
                    f, l, parser, skip, parser.error_handler_);
            } else {
                return detail::skip_parse_impl<false>(
                    f, l, parser, skip, parser.error_handler_);
            }
        }
    }

#if BOOST_PARSER_USE_CONCEPTS
    template<
        parsable_iter I,
        std::sentinel_for<I> S,
        typename Parser,
        typename GlobalState,
        error_handler<I, S, GlobalState> ErrorHandler,
        typename TagType,
        typename Attribute,
        typename LocalState,
        typename ParamsTuple>
#else
    template<
        typename I,
        typename S,
        typename Parser,
        typename GlobalState,
        typename ErrorHandler,
        typename TagType,
        typename Attribute,
        typename LocalState,
        typename ParamsTuple,
        typename Enable = std::enable_if_t<
            detail::is_parsable_iter<I>::value &&
            detail::is_equality_comparable_with<I, S>::value>>
#endif
    auto parse(
        I & first,
        S last,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        callback_rule<TagType, Attribute, LocalState, ParamsTuple> const & skip,
        trace trace_mode = trace::off)
    {
        if constexpr (
            (detail::non_unicode_char_range_like<view<I, S>> &&
             !char8_iter<I>) ||
            sizeof(*first) == 4u) {
            if (trace_mode == trace::on) {
                return detail::skip_parse_impl<true>(
                    first, last, parser, skip, parser.error_handler_);
            } else {
                return detail::skip_parse_impl<false>(
                    first, last, parser, skip, parser.error_handler_);
            }
        } else {
            auto r = parser::detail::text::as_utf32(first, last);
            auto f = r.begin();
            auto const l = r.end();
            auto _ = detail::scoped_base_assign(first, f);
            if (trace_mode == trace::on) {
                return detail::skip_parse_impl<true>(
                    f, l, parser, skip, parser.error_handler_);
            } else {
                return detail::skip_parse_impl<false>(
                    f, l, parser, skip, parser.error_handler_);
            }
        }
    }

#endif

    /** Parses `str` using `parser`, skipping all input recognized by `skip`
        between the application of any two parsers.  Returns a `std::optional`
        containing the attribute produced by `parser` on parse success, and
        `std::nullopt` on parse failure.  The entire input range `r` must be
        consumed for the parse to be considered successful.  If `trace_mode ==
        trace::on`, a verbose trace of the parse will be streamed to
        `std::cout`. */
#if BOOST_PARSER_USE_CONCEPTS
    template<
        parsable_range_like R,
        typename Parser,
        typename GlobalState,
        typename ErrorHandler,
        typename SkipParser>
#else
    template<
        typename R,
        typename Parser,
        typename GlobalState,
        typename ErrorHandler,
        typename SkipParser,
        typename Enable =
            std::enable_if_t<detail::is_parsable_range_like<R>::value>>
#endif
    auto parse(
        R const & r,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        parser_interface<SkipParser> const & skip,
        trace trace_mode = trace::off)
#if BOOST_PARSER_USE_CONCEPTS
        // clang-format off
        requires error_handler<
            ErrorHandler,
            std::ranges::iterator_t<decltype(detail::make_input_view(r))>,
            std::ranges::sentinel_t<decltype(detail::make_input_view(r))>,
            GlobalState>
    // clang-format on
#endif
    {
        auto r_ = detail::make_input_view(r);
        auto first = r_.begin();
        auto const last = r_.end();
        return detail::if_full_parse(
            first, last, parser::parse(first, last, parser, skip, trace_mode));
    }

#ifndef BOOST_PARSER_DOXYGEN

#if BOOST_PARSER_USE_CONCEPTS
    template<
        parsable_range_like R,
        typename Parser,
        typename GlobalState,
        typename ErrorHandler,
        typename TagType,
        typename Attribute,
        typename LocalState,
        typename ParamsTuple>
#else
    template<
        typename R,
        typename Parser,
        typename GlobalState,
        typename ErrorHandler,
        typename TagType,
        typename Attribute,
        typename LocalState,
        typename ParamsTuple,
        typename Enable =
            std::enable_if_t<detail::is_parsable_range_like<R>::value>>
#endif
    auto parse(
        R const & r,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        rule<TagType, Attribute, LocalState, ParamsTuple> const & skip,
        trace trace_mode = trace::off)
#if BOOST_PARSER_USE_CONCEPTS
        // clang-format off
        requires error_handler<
            ErrorHandler,
            std::ranges::iterator_t<decltype(detail::make_input_view(r))>,
            std::ranges::sentinel_t<decltype(detail::make_input_view(r))>,
            GlobalState>
    // clang-format on
#endif
    {
        auto r_ = detail::make_input_view(r);
        auto first = r_.begin();
        auto const last = r_.end();
        return detail::if_full_parse(
            first, last, parser::parse(first, last, parser, skip, trace_mode));
    }

#if BOOST_PARSER_USE_CONCEPTS
    template<
        parsable_range_like R,
        typename Parser,
        typename GlobalState,
        typename ErrorHandler,
        typename TagType,
        typename Attribute,
        typename LocalState,
        typename ParamsTuple>
#else
    template<
        typename R,
        typename Parser,
        typename GlobalState,
        typename ErrorHandler,
        typename TagType,
        typename Attribute,
        typename LocalState,
        typename ParamsTuple,
        typename Enable =
            std::enable_if_t<detail::is_parsable_range_like<R>::value>>
#endif
    auto parse(
        R const & r,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        callback_rule<TagType, Attribute, LocalState, ParamsTuple> const & skip,
        trace trace_mode = trace::off)
#if BOOST_PARSER_USE_CONCEPTS
        // clang-format off
        requires error_handler<
            ErrorHandler,
            std::ranges::iterator_t<decltype(detail::make_input_view(r))>,
            std::ranges::sentinel_t<decltype(detail::make_input_view(r))>,
            GlobalState>
    // clang-format on
#endif
    {
        auto r_ = detail::make_input_view(r);
        auto first = r_.begin();
        auto const last = r_.end();
        return detail::if_full_parse(
            first, last, parser::parse(first, last, parser, skip, trace_mode));
    }

#endif

    /** Parses `[first, last)` using `parser`, and returns whether the parse
        was successful.  When a callback rule `r` is successful during the
        parse, one of two things happens: 1) if `r` has an attribute,
        `callbacks(tag, x)` will be called (where `tag` is
        `decltype(r)::tag_type{}`, and `x` is the attribute produced by `r`);
        or 2) if `r` has no attribute, `callbacks(tag)` will be called.
        `Callbacks` is expected to be an invocable with the correct overloads
        required to support all successful rule parses that might occur.  If
        `trace_mode == trace::on`, a verbose trace of the parse will be
        streamed to `std::cout`. */
#if BOOST_PARSER_USE_CONCEPTS
    template<
        parsable_iter I,
        std::sentinel_for<I> S,
        typename Parser,
        typename GlobalState,
        error_handler<I, S, GlobalState> ErrorHandler,
        typename Callbacks>
#else
    template<
        typename I,
        typename S,
        typename Parser,
        typename GlobalState,
        typename ErrorHandler,
        typename Callbacks,
        typename Enable = std::enable_if_t<
            detail::is_parsable_iter<I>::value &&
            detail::is_equality_comparable_with<I, S>::value>>
#endif
    bool callback_parse(
        I & first,
        S last,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        Callbacks const & callbacks,
        trace trace_mode = trace::off)
    {
        if constexpr (
            (detail::non_unicode_char_range_like<view<I, S>> &&
             !char8_iter<I>) ||
            sizeof(*first) == 4u) {
            if (trace_mode == trace::on) {
                return detail::callback_parse_impl<true>(
                    first, last, parser, parser.error_handler_, callbacks);
            } else {
                return detail::callback_parse_impl<false>(
                    first, last, parser, parser.error_handler_, callbacks);
            }
        } else {
            auto r = parser::detail::text::as_utf32(first, last);
            auto f = r.begin();
            auto const l = r.end();
            auto _ = detail::scoped_base_assign(first, f);
            if (trace_mode == trace::on) {
                return detail::callback_parse_impl<true>(
                    f, l, parser, parser.error_handler_, callbacks);
            } else {
                return detail::callback_parse_impl<false>(
                    f, l, parser, parser.error_handler_, callbacks);
            }
        }
    }

    /** Parses `str` using `parser`, and returns whether the parse was
        successful.  The entire input range `r` must be consumed for the parse
        to be considered successful.  When a callback rule `r` is successful
        during the parse, one of two things happens: 1) if `r` has an
        attribute, `callbacks(tag, x)` will be called (where `tag` is
        `decltype(r)::tag_type{}`, and `x` is the attribute produced by `r`);
        or 2) if `r` has no attribute, `callbacks(tag)` will be called.
        `Callbacks` is expected to be an invocable with the correct overloads
        required to support all successful rule parses that might occur.  If
        `trace_mode == trace::on`, a verbose trace of the parse will be
        streamed to `std::cout`. */
#if BOOST_PARSER_USE_CONCEPTS
    template<
        parsable_range_like R,
        typename Parser,
        typename GlobalState,
        typename ErrorHandler,
        typename Callbacks>
#else
    template<
        typename R,
        typename Parser,
        typename GlobalState,
        typename ErrorHandler,
        typename Callbacks,
        typename Enable =
            std::enable_if_t<detail::is_parsable_range_like<R>::value>>
#endif
    bool callback_parse(
        R const & r,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        Callbacks const & callbacks,
        trace trace_mode = trace::off)
#if BOOST_PARSER_USE_CONCEPTS
        // clang-format off
        requires error_handler<
            ErrorHandler,
            std::ranges::iterator_t<decltype(detail::make_input_view(r))>,
            std::ranges::sentinel_t<decltype(detail::make_input_view(r))>,
            GlobalState>
    // clang-format on
#endif
    {
        auto r_ = detail::make_input_view(r);
        auto first = r_.begin();
        auto const last = r_.end();
        return detail::if_full_parse(
            first,
            last,
            parser::callback_parse(first, last, parser, callbacks));
    }

    /** Parses `[first, last)` using `parser`, skipping all input recognized
        by `skip` between the application of any two parsers, and returns
        whether the parse was successful.  When a callback rule `r` is
        successful during the parse, one of two things happens: 1) if `r` has
        an attribute, `callbacks(tag, x)` will be called (where `tag` is
        `decltype(r)::tag_type{}`, and `x` is the attribute produced by `r`);
        or 2) if `r` has no attribute, `callbacks(tag)` will be called.
        `Callbacks` is expected to be an invocable with the correct overloads
        required to support all successful rule parses that might occur.  If
        `trace_mode == trace::on`, a verbose trace of the parse will be
        streamed to `std::cout`. */
#if BOOST_PARSER_USE_CONCEPTS
    template<
        parsable_iter I,
        std::sentinel_for<I> S,
        typename Parser,
        typename GlobalState,
        error_handler<I, S, GlobalState> ErrorHandler,
        typename SkipParser,
        typename Callbacks>
#else
    template<
        typename I,
        typename S,
        typename Parser,
        typename GlobalState,
        typename ErrorHandler,
        typename SkipParser,
        typename Callbacks,
        typename Enable = std::enable_if_t<
            detail::is_parsable_iter<I>::value &&
            detail::is_equality_comparable_with<I, S>::value>>
#endif
    bool callback_parse(
        I & first,
        S last,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        parser_interface<SkipParser> const & skip,
        Callbacks const & callbacks,
        trace trace_mode = trace::off)
    {
        if constexpr (
            (detail::non_unicode_char_range_like<view<I, S>> &&
             !char8_iter<I>) ||
            sizeof(*first) == 4u) {
            if (trace_mode == trace::on) {
                return detail::callback_skip_parse_impl<true>(
                    first,
                    last,
                    parser,
                    skip,
                    parser.error_handler_,
                    callbacks);
            } else {
                return detail::callback_skip_parse_impl<false>(
                    first,
                    last,
                    parser,
                    skip,
                    parser.error_handler_,
                    callbacks);
            }
        } else {
            auto r = parser::detail::text::as_utf32(first, last);
            auto f = r.begin();
            auto const l = r.end();
            auto _ = detail::scoped_base_assign(first, f);
            if (trace_mode == trace::on) {
                return detail::callback_skip_parse_impl<true>(
                    f, l, parser, skip, parser.error_handler_, callbacks);
            } else {
                return detail::callback_skip_parse_impl<false>(
                    f, l, parser, skip, parser.error_handler_, callbacks);
            }
        }
    }

    /** Parses `str` using `parser`, skipping all input recognized by `skip`
        between the application of any two parsers, and returns whether the
        parse was successful.  The entire input range `r` must be consumed for
        the parse to be considered successful.  When a callback rule `r` is
        successful during the parse, one of two things happens: 1) if `r` has
        an attribute, `callbacks(tag, x)` will be called (where `tag` is
        `decltype(r)::tag_type{}`, and `x` is the attribute produced by `r`);
        or 2) if `r` has no attribute, `callbacks(tag)` will be called.
        `Callbacks` is expected to be an invocable with the correct overloads
        required to support all successful rule parses that might occur.  If
        `trace_mode == trace::on`, a verbose trace of the parse will be
        streamed to `std::cout`. */
#if BOOST_PARSER_USE_CONCEPTS
    template<
        parsable_range_like R,
        typename Parser,
        typename GlobalState,
        typename ErrorHandler,
        typename SkipParser,
        typename Callbacks>
#else
    template<
        typename R,
        typename Parser,
        typename GlobalState,
        typename ErrorHandler,
        typename SkipParser,
        typename Callbacks,
        typename Enable =
            std::enable_if_t<detail::is_parsable_range_like<R>::value>>
#endif
    bool callback_parse(
        R const & r,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        parser_interface<SkipParser> const & skip,
        Callbacks const & callbacks,
        trace trace_mode = trace::off)
#if BOOST_PARSER_USE_CONCEPTS
        // clang-format off
        requires error_handler<
            ErrorHandler,
            std::ranges::iterator_t<decltype(detail::make_input_view(r))>,
            std::ranges::sentinel_t<decltype(detail::make_input_view(r))>,
            GlobalState>
    // clang-format on
#endif
    {
        auto r_ = detail::make_input_view(r);
        auto first = r_.begin();
        auto const last = r_.end();
        return detail::if_full_parse(
            first,
            last,
            parser::callback_parse(
                first, last, parser, skip, callbacks, trace_mode));
    }

    namespace literals {
        /** Returns a literal parser equivalent to `lit(c)`. */
        constexpr auto operator""_l(char c) { return parser::lit(c); }
#if defined(__cpp_char8_t) || defined(BOOST_PARSER_DOXYGEN)
        /** Returns a literal parser equivalent to `lit(c)`. */
        constexpr auto operator""_l(char8_t c) { return parser::lit(c); }
#endif
        /** Returns a literal parser equivalent to `lit(c)`. */
        constexpr auto operator""_l(char32_t c) { return parser::lit(c); }
        /** Returns a literal parser equivalent to `lit(str)`. */
        constexpr auto operator""_l(char const * str, std::size_t)
        {
            return parser::lit(str);
        }
#if defined(__cpp_char8_t) || defined(BOOST_PARSER_DOXYGEN)
        /** Returns a literal parser equivalent to `lit(str)`. */
        constexpr auto operator""_l(char8_t const * str, std::size_t)
        {
            return parser::lit(str);
        }
#endif
        /** Returns a literal parser equivalent to `lit(str)`. */
        constexpr auto operator""_l(char32_t const * str, std::size_t)
        {
            return parser::lit(str);
        }

        /** Returns a character parser equivalent to `char_(c)`. */
        constexpr auto operator""_p(char c) { return char_(c); }
#if defined(__cpp_char8_t) || defined(BOOST_PARSER_DOXYGEN)
        /** Returns a character parser equivalent to `char_(c)`. */
        constexpr auto operator""_p(char8_t c) { return char_(c); }
#endif
        /** Returns a character parser equivalent to `char_(c)`. */
        constexpr auto operator""_p(char32_t c) { return char_(c); }
        /** Returns a string parser equivalent to `string(str)`. */
        constexpr auto operator""_p(char const * str, std::size_t)
        {
            return parser::string(str);
        }
#if defined(__cpp_char8_t) || defined(BOOST_PARSER_DOXYGEN)
        /** Returns a string parser equivalent to `string(str)`. */
        constexpr auto operator""_p(char8_t const * str, std::size_t)
        {
            return parser::string(str);
        }
#endif
        /** Returns a string parser equivalent to `string(str)`. */
        constexpr auto operator""_p(char32_t const * str, std::size_t)
        {
            return parser::string(str);
        }
    }

}}

#endif
