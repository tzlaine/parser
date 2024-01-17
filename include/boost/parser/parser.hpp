#ifndef BOOST_PARSER_PARSER_HPP
#define BOOST_PARSER_PARSER_HPP

#include <boost/parser/parser_fwd.hpp>
#include <boost/parser/concepts.hpp>
#include <boost/parser/error_handling.hpp>
#include <boost/parser/tuple.hpp>
#include <boost/parser/detail/hl.hpp>
#include <boost/parser/detail/numeric.hpp>
#include <boost/parser/detail/case_fold.hpp>
#include <boost/parser/detail/pp_for_each.hpp>
#include <boost/parser/detail/printing.hpp>

#include <boost/parser/detail/text/algorithm.hpp>
#include <boost/parser/detail/text/trie.hpp>
#include <boost/parser/detail/text/unpack.hpp>

#include <type_traits>
#include <variant>
#include <vector>


namespace boost { namespace parser {

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
        // Follows boost/mpl/print.hpp.
#if defined(_MSC_VER)
#pragma warning(push, 3)
#pragma warning(disable : 4307)
#endif
#if defined(__EDG_VERSION__)
        namespace print_aux {
            template<typename T>
            struct dependent_unsigned
            {
                static const unsigned int value = 1;
            };
        }
#endif
        template<typename T>
        struct identity_t
        {
            using type = T;
        };
        template<typename T>
        struct print_t : identity_t<T>
        {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++11-extensions"
            const int x_ = 1 / (sizeof(T) - sizeof(T));
#pragma clang diagnostic pop
#elif defined(_MSC_VER)
            enum { n = sizeof(T) + -1 };
#elif defined(__MWERKS__)
            void f(int);
#else
            enum {
                n =
#if defined(__EDG_VERSION__)
                    print_aux::dependent_unsigned<T>::value > -1
#else
                    sizeof(T) > -1
#endif
            };
#endif
        };
#if defined(_MSC_VER)
#pragma warning(pop)
#endif
        template<typename T>
        using print_type = typename print_t<T>::type;


        // Utility types.

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
            typename RuleTag = void,
            typename RuleLocals = nope,
            typename RuleParams = nope,
            typename Where = nope>
        struct parse_context
        {
            parse_context() = default;
            parse_context(parse_context const &) = default;
            parse_context & operator=(parse_context const &) = default;

            using rule_tag = RuleTag;

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
            int no_case_depth_ = 0;

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
                typename OldRuleTag,
                typename OldRuleLocals,
                typename OldRuleParams,
                typename NewVal,
                typename NewRuleTag,
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
                    OldRuleTag,
                    OldRuleLocals,
                    OldRuleParams> const & other,
                NewRuleTag * tag_ptr,
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
                no_case_depth_(other.no_case_depth_)
            {
                if constexpr (
                    std::is_same_v<OldRuleTag, NewRuleTag> &&
                    !std::is_same_v<OldRuleTag, void>) {
                    val_ = other.val_;
                    locals_ = other.locals_;
                    params_ = other.params_;
                } else {
                    val_ = other_or_address(other.val_, value);
                    locals_ = other_or_address(other.locals_, locals);
                    params_ = other_or_address(other.params_, params);
                }
            }

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
                    RuleTag,
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
                where_(nope_or_address(where)),
                no_case_depth_(other.no_case_depth_)
            {}
        };

        template<
            typename I,
            typename S,
            typename ErrorHandler,
            typename GlobalState,
            typename Callbacks,
            typename Val,
            typename RuleTag,
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
                RuleTag,
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
                RuleTag,
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
            typename RuleTag,
            typename RuleLocals,
            typename RuleParams,
            typename NewVal,
            typename NewRuleTag,
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
                RuleTag,
                RuleLocals,
                RuleParams> const & context,
            NewRuleTag * tag_ptr,
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
                NewRuleTag,
                std::conditional_t<
                    std::is_same_v<NewRuleLocals, nope>,
                    RuleLocals,
                    NewRuleLocals>,
                std::conditional_t<
                    std::is_same_v<NewRuleParams, nope>,
                    RuleParams,
                    NewRuleParams>>;
            return result_type(context, tag_ptr, value, locals, params);
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
            bool Callable = is_detected_v<callable, T const &, Context const &>>
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
            using trie_t = text::trie<std::vector<char32_t>, T>;
            symbol_table_tries_t & symbol_table_tries =
                *context.symbol_table_tries_;
            any_copyable & a = symbol_table_tries[(void *)&symbol_parser];
            if (a.empty()) {
                a = trie_t{};
                trie_t & trie = a.cast<trie_t>();
                for (auto const & e : symbol_parser.initial_elements()) {
                    trie.insert(e.first | text::as_utf32, e.second);
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
        constexpr bool is_equality_comparable_with_v =
            is_detected_v<comparison, T, U>;

        template<typename T>
        struct is_nope : std::false_type
        {};
        template<>
        struct is_nope<nope> : std::true_type
        {};
        template<typename T>
        constexpr bool is_nope_v = is_nope<remove_cv_ref_t<T>>::value;

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
        template<typename T, typename U, typename V>
        struct is_seq_p<seq_parser<T, U, V>> : std::true_type
        {};

        template<typename T>
        struct is_one_plus_p : std::false_type
        {};
        template<typename T>
        struct is_one_plus_p<one_plus_parser<T>> : std::true_type
        {};

        template<typename T>
        struct is_utf8_view : std::false_type
        {};
        template<typename V>
        struct is_utf8_view<text::utf8_view<V>> : std::true_type
        {};

        template<typename T>
        using optional_type = remove_cv_ref_t<decltype(*std::declval<T &>())>;

        template<typename F, typename... Args>
        constexpr bool is_invocable_v = is_detected_v<callable, F, Args...>;

        template<typename T>
        using has_begin =
            decltype(*detail::text::detail::begin(std::declval<T &>()));
        template<typename T>
        using has_end =
            decltype(detail::text::detail::end(std::declval<T &>()));

        template<typename T>
        constexpr bool is_range =
            is_detected_v<has_begin, T> && is_detected_v<has_end, T>;

        template<typename T>
        using has_push_back =
            decltype(std::declval<T &>().push_back(*std::declval<T>().begin()));

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
        constexpr bool is_parsable_code_unit_v = parsable_code_unit<T>;

#else

        template<typename T>
        using iterator_t =
            decltype(detail::text::detail::begin(std::declval<T &>()));
        template<typename Range>
        using sentinel_t =
            decltype(detail::text::detail::end(std::declval<Range>()));
        template<typename T>
        using iter_value_t = typename std::iterator_traits<T>::value_type;
        template<typename T>
        using iter_reference_t = decltype(*std::declval<T &>());
        template<typename T>
        using range_value_t = iter_value_t<iterator_t<T>>;

        template<typename T>
        using has_insert = decltype(std::declval<T &>().insert(
            std::declval<T>().begin(), *std::declval<T>().begin()));
        template<typename T>
        using has_range_insert = decltype(std::declval<T &>().insert(
            std::declval<T>().begin(),
            std::declval<T>().begin(),
            std::declval<T>().end()));

        template<typename T>
        constexpr bool is_container_v = is_detected_v<has_insert, T>;

        template<typename T, typename U>
        constexpr bool container_and_value_type =
            is_container_v<T> &&
            (std::is_same_v<detected_t<range_value_t, T>, U> ||
             (std::is_same_v<T, std::string> && std::is_same_v<U, char32_t>));

        template<typename T>
        constexpr bool is_parsable_code_unit_impl =
            std::is_same_v<T, char> || std::is_same_v<T, wchar_t> ||
#if defined(__cpp_char8_t)
            std::is_same_v<T, char8_t> ||
#endif
            std::is_same_v<T, char16_t> || std::is_same_v<T, char32_t>;

        template<typename T>
        constexpr bool is_parsable_code_unit_v =
            is_parsable_code_unit_impl<std::remove_cv_t<T>>;

        template<typename T>
        constexpr bool is_parsable_iter_v = is_parsable_code_unit_v<
            remove_cv_ref_t<detected_t<iter_value_t, T>>>;

        template<typename T>
        constexpr bool is_parsable_range_v = is_parsable_code_unit_v<
            remove_cv_ref_t<detected_t<has_begin, T>>> &&
            is_detected_v<has_end, T>;

        template<typename T>
        constexpr bool is_parsable_pointer_v =
            std::is_pointer_v<remove_cv_ref_t<T>> && is_parsable_code_unit_v<
                std::remove_pointer_t<remove_cv_ref_t<T>>>;

        template<typename T>
        constexpr bool is_parsable_range_like_v =
            is_parsable_range_v<T> || is_parsable_pointer_v<T>;
    }

    template<typename T>
    constexpr bool container = detail::is_container_v<T>;

    namespace detail {
#endif

        template<typename I>
        constexpr bool is_char8_iter_v =
#if defined(__cpp_char8_t)
            std::is_same_v<iter_value_t<I>, char8_t>
#else
            false
#endif
            ;

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
                std::conditional_t<is_optional_v<T>, T, std::optional<T>>;
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

        template<typename T>
        auto make_sequence_of()
        {
            if constexpr (
                std::is_same_v<T, char> || std::is_same_v<T, char32_t>) {
                return std::string{};
            } else if constexpr (std::is_same_v<T, nope>) {
                return nope{};
            } else {
                return std::vector<T>{};
            }
        }

        template<typename T>
        constexpr bool is_char_type_v =
            std::is_same_v<T, char> || std::is_same_v<T, char32_t>;

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
        void insert(Container & c, T && x)
        {
            if constexpr (is_detected_v<has_push_back, Container>) {
                c.push_back((T &&) x);
            } else {
                c.insert((T &&) x);
            }
        }

        template<typename Container, typename I>
        void insert(Container & c, I first, I last)
        {
            std::for_each(first, last, [&](auto && x) {
                using type = decltype(x);
                insert(c, (type &&) x);
            });
        }

        template<typename Container, typename T>
        constexpr bool needs_transcoding_to_utf8 =
            (std::is_same_v<range_value_t<remove_cv_ref_t<Container>>, char>
#if defined(__cpp_char8_t)
             || std::is_same_v<range_value_t<remove_cv_ref_t<Container>>, char8_t>
#endif
                ) && (std::is_same_v<remove_cv_ref_t<T>, char32_t>
#if !defined(_MSC_VER)
             || std::is_same_v<remove_cv_ref_t<T>, wchar_t>
#endif
             );

        template<typename Container, typename T>
        void append(Container & c, T && x, bool gen_attrs)
        {
            if (!gen_attrs)
                return;
            if constexpr (needs_transcoding_to_utf8<Container, T>) {
                char32_t cps[1] = {(char32_t)x};
                auto const r = cps | text::as_utf8;
                c.insert(c.end(), r.begin(), r.end());
            } else {
                detail::insert(c, std::move(x));
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
            if constexpr (needs_transcoding_to_utf8<
                              Container,
                              iter_value_t<Iter>>) {
                auto const r =
                    BOOST_PARSER_SUBRANGE(first, last) | text::as_utf8;
                c.insert(c.end(), r.begin(), r.end());
            } else {
                detail::insert(c, first, last);
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

        using case_fold_array_t = std::array<char32_t, detail::longest_mapping>;

        template<typename I, typename S>
        struct no_case_iter : stl_interfaces::iterator_interface<
                                  no_case_iter<I, S>,
                                  std::forward_iterator_tag,
                                  char32_t,
                                  char32_t>
        {
            no_case_iter() : it_(), last_(), idx_(0), last_idx_() {}
            no_case_iter(I it, S last) :
                it_(it), last_(last), idx_(0), last_idx_(0)
            {
                fold();
            }

            char32_t operator*() const { return folded_[idx_]; }
            no_case_iter & operator++()
            {
                if (last_idx_ <= ++idx_) {
                    ++it_;
                    fold();
                }
                return *this;
            }
            I base() const { return it_; }
            friend bool operator==(no_case_iter lhs, S rhs) noexcept
            {
                return lhs.it_ == rhs;
            }
            friend bool operator==(no_case_iter lhs, no_case_iter rhs) noexcept
            {
                return lhs.it_ == rhs.it_ && lhs.idx_ == rhs.idx_;
            }

            using base_type = stl_interfaces::iterator_interface<
                no_case_iter<I, S>,
                std::forward_iterator_tag,
                char32_t,
                char32_t>;
            using base_type::operator++;

        private:
            void fold()
            {
                idx_ = 0;
                if (it_ == last_) {
                    folded_[0] = 0;
                    return;
                }
                auto const folded_last =
                    detail::case_fold(*it_, folded_.begin());
                last_idx_ = folded_last - folded_.begin();
            }

            case_fold_array_t folded_;
            I it_;
            [[no_unique_address]] S last_;
            int idx_;
            int last_idx_;
        };

        template<typename Iter, typename Sentinel>
        struct char_range
        {
            template<typename T, typename Context>
            bool contains(T c_, Context const & context) const
            {
                if (context.no_case_depth_) {
                    case_fold_array_t folded;
                    auto folded_last = detail::case_fold(c_, folded.begin());
                    if constexpr (std::is_same_v<T, char32_t>) {
                        auto const cps = chars_ | text::as_utf32;
                        auto chars_first = no_case_iter(cps.begin(), cps.end());
                        auto chars_last = cps.end();
                        auto result = text::search(
                            chars_first,
                            chars_last,
                            folded.begin(),
                            folded_last);
                        return !result.empty();
                    } else {
                        auto chars_first =
                            no_case_iter(chars_.begin(), chars_.end());
                        auto chars_last = chars_.end();
                        auto result = text::search(
                            chars_first,
                            chars_last,
                            folded.begin(),
                            folded_last);
                        return !result.empty();
                    }
                } else {
                    if constexpr (std::is_same_v<T, char32_t>) {
                        auto const cps = chars_ | text::as_utf32;
                        return text::find(cps.begin(), cps.end(), c_) !=
                               cps.end();
                    } else {
                        using element_type = decltype(*chars_.begin());
                        element_type const c = c_;
                        return text::find(chars_.begin(), chars_.end(), c) !=
                               chars_.end();
                    }
                }
            }

            BOOST_PARSER_SUBRANGE<Iter, Sentinel> chars_;
        };

        template<typename Iter, typename Sentinel>
        constexpr auto make_char_range(Iter first, Sentinel last)
        {
            return char_range<Iter, Sentinel>{
                BOOST_PARSER_SUBRANGE<Iter, Sentinel>{first, last}};
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

        template<bool Equal, typename Context>
        auto no_case_aware_compare(Context const & context)
        {
            return [no_case = context.no_case_depth_](char32_t a, char32_t b) {
                if (no_case) {
                    case_fold_array_t folded_a = {0, 0, 0};
                    detail::case_fold(a, folded_a.begin());
                    case_fold_array_t folded_b = {0, 0, 0};
                    detail::case_fold(b, folded_b.begin());
                    return Equal ? folded_a == folded_b : folded_a < folded_b;
                } else {
                    return Equal ? a == b : a < b;
                }
            };
        }

        template<typename T, typename U>
        constexpr bool both_character_types =
            is_parsable_code_unit_v<T> && is_parsable_code_unit_v<U>;

        template<typename T, typename U>
        using eq_comparable =
            decltype(std::declval<T &>() == std::declval<U &>());

        template<
            typename Context,
            typename CharType,
            typename Expected,
            bool BothCharacters = both_character_types<CharType, Expected>>
        struct unequal_impl
        {
            static bool
            call(Context const & context, CharType c, Expected const & expected)
            {
                auto resolved = detail::resolve(context, expected);
                if constexpr (is_detected_v<
                                  eq_comparable,
                                  CharType,
                                  decltype(resolved)>) {
                    auto const compare =
                        detail::no_case_aware_compare<true>(context);
                    return !compare(c, resolved);
                } else {
                    return !resolved.contains(c, context);
                }
            }
        };

        template<typename Context, typename CharType, typename Expected>
        struct unequal_impl<Context, CharType, Expected, true>
        {
            static bool
            call(Context const & context, CharType c, Expected expected)
            {

                return !detail::no_case_aware_compare<true>(context)(
                    c, expected);
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
            auto const less = detail::no_case_aware_compare<false>(context);
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
            template<typename T, typename Context>
            bool contains(T c, Context const &) const
            {
                switch (CharClass) {
                case ascii_char_class_t::alnum: return std::isalnum(c);
                case ascii_char_class_t::alpha: return std::isalpha(c);
                case ascii_char_class_t::blank: return std::isblank(c);
                case ascii_char_class_t::cntrl: return std::iscntrl(c);
                case ascii_char_class_t::digit: return std::isdigit(c);
                case ascii_char_class_t::graph: return std::isgraph(c);
                case ascii_char_class_t::print: return std::isprint(c);
                case ascii_char_class_t::punct: return std::ispunct(c);
                case ascii_char_class_t::space: return std::isspace(c);
                case ascii_char_class_t::xdigit: return std::isxdigit(c);
                case ascii_char_class_t::lower: return std::islower(c);
                case ascii_char_class_t::upper: return std::isupper(c);
                }
                return false;
            }
        };

        template<typename Container, typename T>
        using insertable = decltype(std::declval<Container &>().insert(
            std::declval<Container &>().end(), std::declval<T>()));

        template<typename Container, typename U>
        constexpr void move_back_impl(Container & c, U && x)
        {
            if constexpr (needs_transcoding_to_utf8<Container, U>) {
                char32_t cps[1] = {(char32_t)x};
                auto const r = cps | text::as_utf8;
                c.insert(c.end(), r.begin(), r.end());
            } else {
                using just_t = range_value_t<Container>;
                using just_u = remove_cv_ref_t<U>;
                if constexpr (
                    !is_tuple<just_t>::value && is_tuple<just_u>::value &&
                    std::is_aggregate_v<just_t> &&
                    !is_detected_v<insertable, Container, just_u &&> &&
                    is_struct_assignable_v<just_t, just_u>) {
                    auto int_seq =
                        std::make_integer_sequence<int, tuple_size_<just_u>>();
                    detail::insert(
                        c,
                        detail::tuple_to_aggregate<just_t>(
                            std::move(x), int_seq));
                } else if constexpr (
                    is_tuple<just_t>::value && !is_tuple<just_u>::value &&
                    std::is_aggregate_v<just_u> &&
                    !is_detected_v<insertable, Container, just_u &&> &&
                    is_tuple_assignable_v<just_t, just_u>) {
                    just_t t;
                    auto tie = detail::tie_aggregate(x);
                    detail::aggregate_to_tuple(
                        t,
                        tie,
                        std::make_integer_sequence<int, tuple_size_<just_t>>());
                    detail::insert(c, std::move(t));
                } else {
                    detail::insert(c, std::move(x));
                }
            }
        }

        template<typename Container, typename T>
        constexpr void move_back(Container & c, T && x, bool gen_attrs)
        {
            if (!gen_attrs)
                return;
            detail::move_back_impl(c, std::move(x));
        }

        template<typename Container>
        constexpr void
        move_back(Container & c, Container & x, bool gen_attrs)
        {
            if (!gen_attrs)
                return;
            c.insert(c.end(), x.begin(), x.end());
        }

        template<typename Container>
        constexpr void move_back(
            Container & c, std::optional<Container> & x, bool gen_attrs)
        {
            if (!gen_attrs || !x)
                return;
            c.insert(c.end(), x->begin(), x->end());
        }

        template<typename Container, typename T>
        constexpr void
        move_back(Container & c, std::optional<T> & x, bool gen_attrs)
        {
            if (!gen_attrs || !x)
                return;
            detail::move_back_impl(c, std::move(*x));
        }

        template<typename Container, typename T>
        constexpr void
        move_back(Container & c, std::optional<T> && x, bool gen_attrs)
        {
            if (!gen_attrs || !x)
                return;
            detail::move_back_impl(c, std::move(*x));
        }

        constexpr void move_back(nope, nope, bool gen_attrs) {}

        template<typename Container>
        constexpr void move_back(Container & c, nope, bool gen_attrs)
        {}

        template<typename T, typename U>
        constexpr void assign(T & t, U && u)
        {
            using just_t = remove_cv_ref_t<T>;
            using just_u = remove_cv_ref_t<U>;
            if constexpr (
                !is_tuple<just_t>::value && is_tuple<just_u>::value &&
                std::is_aggregate_v<just_t> &&
                !std::is_convertible_v<just_u &&, just_t> &&
                is_struct_assignable_v<just_t, just_u>) {
                auto int_seq =
                    std::make_integer_sequence<int, tuple_size_<just_u>>();
                t = detail::tuple_to_aggregate<just_t>(std::move(u), int_seq);
            } else if constexpr (
                is_tuple<just_t>::value && !is_tuple<just_u>::value &&
                std::is_aggregate_v<just_u> &&
                !std::is_convertible_v<just_u &&, just_t> &&
                is_tuple_assignable_v<just_t, just_u>) {
                auto tie = detail::tie_aggregate(u);
                detail::aggregate_to_tuple(
                    t,
                    tie,
                    std::make_integer_sequence<int, tuple_size_<just_t>>());
            } else {
                t = std::move(u);
            }
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
                    detail::assign(retval, std::variant<T...>(std::move(attr)));
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
                detail::assign(retval, std::move(attr));
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
                detail::assign(retval, std::move(attr));
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

        template<typename R>
        constexpr auto make_input_subrange(R && r) noexcept
        {
            using r_t = remove_cv_ref_t<R>;
            if constexpr (std::is_pointer_v<r_t>) {
                using value_type = iter_value_t<r_t>;
                if constexpr (std::is_same_v<value_type, char>) {
                    return BOOST_PARSER_SUBRANGE(r, text::null_sentinel);
                } else {
                    return r | text::as_utf32;
                }
            } else {
                using value_type = range_value_t<r_t>;
                if constexpr (std::is_array_v<r_t>) {
                    if constexpr (std::is_same_v<value_type, char>) {
                        auto first = detail::text::detail::begin(r);
                        auto last = detail::text::detail::end(r);
                        if (first != last && !*std::prev(last))
                            --last;
                        return BOOST_PARSER_SUBRANGE(first, last);
                    } else {
                        return r | text::as_utf32;
                    }
                } else {
                    if constexpr (
                        std::is_same_v<value_type, char> &&
                        !is_utf8_view<r_t>::value) {
                        return BOOST_PARSER_SUBRANGE(
                            detail::text::detail::begin(r),
                            detail::text::detail::end(r));
                    } else {
                        return r | text::as_utf32;
                    }
                }
            }
        }

        template<typename R>
        constexpr auto make_view_begin(R & r) noexcept
        {
            if constexpr (std::is_pointer_v<std::decay_t<R>>) {
                return r;
            } else {
                return detail::text::detail::begin(r);
            }
        }

        template<typename R>
        constexpr auto make_view_end(R & r) noexcept
        {
            if constexpr (std::is_pointer_v<std::decay_t<R>>) {
                return text::null_sentinel;
            } else {
                return detail::text::detail::end(r);
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
        std::pair<Iter1, Iter2> no_case_aware_string_mismatch(
            Iter1 first1,
            Sentinel1 last1,
            Iter2 first2,
            Sentinel2 last2,
            bool no_case)
        {
            if (no_case) {
                auto it1 = no_case_iter(first1, last1);
                auto it2 = no_case_iter(first2, last2);
                auto const mismatch = detail::mismatch(
                    it1, last1, it2, last2, std::equal_to<char32_t>{});
                return std::pair<Iter1, Iter2>{
                    mismatch.first.base(), mismatch.second.base()};
            } else {
                return detail::mismatch(
                    first1, last1, first2, last2, std::equal_to<char32_t>{});
            }
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

        // The notion of comaptibility is that, given a parser with the
        // Attribute Tuple, we can parse into Struct instead.
        template<typename Struct, typename Tuple>
        constexpr auto is_struct_compatible();

        struct element_compatibility
        {
            template<typename T, typename U>
            constexpr auto operator()(T result, U x) const
            {
                using struct_elem =
                    remove_cv_ref_t<decltype(parser::get(x, llong<0>{}))>;
                using tuple_elem =
                    remove_cv_ref_t<decltype(parser::get(x, llong<1>{}))>;
                if constexpr (!T::value) {
                    return std::false_type{};
                } else if constexpr (
                    is_optional_v<struct_elem> && is_optional_v<tuple_elem>) {
                    using struct_opt_type = optional_type<struct_elem>;
                    using tuple_opt_type = optional_type<tuple_elem>;
                    using retval_t = decltype((*this)(
                        result,
                        detail::hl::make_tuple(
                            std::declval<struct_opt_type &>(),
                            std::declval<tuple_opt_type &>())));
                    return retval_t{};
                } else if constexpr (std::is_convertible_v<
                                         tuple_elem &&,
                                         struct_elem>) {
                    return std::true_type{};
                } else if constexpr (
                    container<struct_elem> && container<tuple_elem>) {
                    return detail::is_struct_compatible<
                        range_value_t<struct_elem>,
                        range_value_t<tuple_elem>>();
                } else {
                    return std::bool_constant<detail::is_struct_compatible<
                        struct_elem,
                        tuple_elem>()>{};
                }
            }
        };

        template<typename T, typename U>
        constexpr auto is_struct_compatible()
        {
            if constexpr (
                !std::is_aggregate_v<T> ||
                struct_arity_v<T> != tuple_size_<U>) {
                return std::false_type{};
            } else {
                using result_t = decltype(detail::hl::fold_left(
                    detail::hl::zip(
                        detail::tie_aggregate(std::declval<T &>()),
                        std::declval<U &>()),
                    std::true_type{},
                    element_compatibility{}));
                return result_t{};
            }
        }

        template<typename Struct, typename Tuple>
        constexpr bool is_struct_compatible_v =
            detail::is_struct_compatible<Struct, Tuple>();

        template<typename ParserAttr, typename GivenContainerAttr>
        constexpr auto parser_attr_or_container_value_type()
        {
            if constexpr (is_nope_v<ParserAttr>) {
                return nope{};
            } else {
                using value_type = range_value_t<GivenContainerAttr>;
                return std::conditional_t<
                    std::is_convertible_v<ParserAttr, value_type>,
                    ParserAttr,
                    value_type>{};
            }
        }
        template<typename ParserAttr, typename GivenContainerAttr>
        using parser_attr_or_container_value_type_v =
            decltype(parser_attr_or_container_value_type<
                     ParserAttr,
                     GivenContainerAttr>());

        template<typename T>
        constexpr auto tuple_or_struct_size(T && x)
        {
            if constexpr (is_tuple<remove_cv_ref_t<T>>{}) {
                return hl::size(x);
            } else {
                return llong<struct_arity_v<remove_cv_ref_t<T>>>{};
            }
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
    decltype(auto) _no_case(Context const & context)
    {
        return context.no_case_depth_;
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
            auto retval = detail::make_sequence_of<attr_t>();
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

            if constexpr (detail::is_optional_v<Attribute>) {
                detail::optional_type<Attribute> attr;
                detail::apply_parser(
                    *this,
                    use_cbs,
                    first,
                    last,
                    context,
                    skip,
                    detail::set_in_apply_parser(flags),
                    success,
                    attr);
                if (success)
                    retval = std::move(attr);
            } else { // Otherwise, Attribute must be a container or a nope.
                using attr_t = detail::parser_attr_or_container_value_type_v<
                    decltype(parser_.call(
                        use_cbs, first, last, context, skip, flags, success)),
                    Attribute>;

                int64_t count = 0;

                for (int64_t end = detail::resolve(context, min_); count != end;
                     ++count) {
                    detail::skip(first, last, skip, flags);
                    attr_t attr;
                    parser_.call(
                        use_cbs,
                        first,
                        last,
                        context,
                        skip,
                        flags,
                        success,
                        attr);
                    if (!success) {
                        detail::assign(retval, Attribute());
                        return;
                    }
                    detail::move_back(
                        retval, std::move(attr), detail::gen_attrs(flags));
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
                    attr_t attr;
                    parser_.call(
                        use_cbs,
                        first,
                        last,
                        context,
                        skip,
                        flags,
                        success,
                        attr);
                    if (!success) {
                        success = true;
                        first = prev_first;
                        break;
                    }
                    detail::move_back(
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

    //[ opt_parser_beginning
    template<typename Parser>
    struct opt_parser
    {
        //]
        //[ opt_parser_attr_call
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
        //]

        //[ opt_parser_out_param_call
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
            //[ opt_parser_trace
            auto _ = detail::scoped_trace(
                *this, first, last, context, flags, retval);
            //]

            //[ opt_parser_skip
            detail::skip(first, last, skip, flags);
            //]

            //[ opt_parser_no_gen_attr_path
            if (!detail::gen_attrs(flags)) {
                parser_.call(
                    use_cbs, first, last, context, skip, flags, success);
                success = true;
                return;
            }
            //]

            //[ opt_parser_gen_attr_path
            parser_.call(
                use_cbs, first, last, context, skip, flags, success, retval);
            success = true;
            //]
        }
        //]

        //[ opt_parser_end
        Parser parser_;
    };
    //]

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
                SkipParser> const use_parser{
                first, last, context, skip, flags, success};

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
                SkipParser> const use_parser{
                first, last, context, skip, flags, success};

            bool done = false;
            auto try_parser = [prev_first = first,
                               use_parser,
                               &success,
                               flags,
                               &retval,
                               &done](auto const & parser) {
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
                else
                    use_parser.first_ = prev_first;
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

    namespace detail {
        template<int N, int... I>
        constexpr auto
        make_default_combining_impl(std::integer_sequence<int, I...>)
        {
            return hl::make_tuple(((void)I, llong<N>{})...);
        }
        template<template<class...> class Tuple, typename... Args>
        constexpr auto make_default_combining(Tuple<Args...>)
        {
            return detail::make_default_combining_impl<0>(
                std::make_integer_sequence<int, sizeof...(Args)>());
        }
        template<typename ParserTuple>
        using default_combining_t = decltype(detail::make_default_combining(
            std::declval<ParserTuple>()));

        struct default_combine_t
        {};
        struct merge_t
        {};
        struct separate_t
        {};

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

        template<typename... Args>
        constexpr void static_assert_merge_attributes(tuple<Args...> parsers);

        // Combining groups are: 0, which is default merge behavior, as in
        // seq_parser::combine; -1, which is don't merge with anything, ever;
        // and N>0, which is merge with other members of group N.
        template<typename CombiningGroups, typename... Args>
        constexpr auto make_combining(tuple<Args...> parsers)
        {
            if constexpr (std::is_same_v<CombiningGroups, default_combine_t>) {
                return detail::make_default_combining_impl<0>(
                    std::make_integer_sequence<int, sizeof...(Args)>());
            } else if constexpr (std::is_same_v<CombiningGroups, merge_t>) {
                detail::static_assert_merge_attributes(parsers);
                return detail::make_default_combining_impl<1>(
                    std::make_integer_sequence<int, sizeof...(Args)>());
            } else if constexpr (std::is_same_v<CombiningGroups, separate_t>) {
                return detail::make_default_combining_impl<-1>(
                    std::make_integer_sequence<int, sizeof...(Args)>());
            } else {
                return CombiningGroups{};
            }
        }
        template<typename ParserTuple, typename CombiningGroups>
        using combining_t = decltype(detail::make_combining<CombiningGroups>(
            std::declval<ParserTuple>()));

        struct max_
        {
            template<typename T, typename U>
            constexpr auto operator()(T x, U y) const
            {
                if constexpr (T::value < U::value)
                    return y;
                else
                    return x;
            }
        };
        template<int MaxGroupIdx>
        struct adjust_combining_groups
        {
            template<typename T, typename U>
            constexpr auto operator()(T result, U x) const
            {
                if constexpr (U::value <= 0)
                    return hl::append(result, x);
                else
                    return hl::append(result, llong<MaxGroupIdx + U::value>{});
            }
        };
        template<typename Tuple1, typename Tuple2>
        constexpr auto make_combined_combining(Tuple1 lhs, Tuple2 rhs)
        {
            auto max_group_idx = detail::hl::fold_left(lhs, llong<0>{}, max_{});
            auto rhs_adjusted = detail::hl::fold_left(
                rhs,
                tuple<>{},
                adjust_combining_groups<decltype(max_group_idx)::value>{});
            return hl::concat(lhs, rhs_adjusted);
        }
        template<typename CombiningGroups1, typename CombiningGroups2>
        using combined_combining_t = decltype(detail::make_combined_combining(
            std::declval<CombiningGroups1>(),
            std::declval<CombiningGroups2>()));
    }

    template<
        typename ParserTuple,
        typename BacktrackingTuple,
        typename CombiningGroups>
    struct seq_parser
    {
        using backtracking = BacktrackingTuple;
        using combining_groups = CombiningGroups;

        constexpr seq_parser(ParserTuple parsers) : parsers_(parsers) {}

#ifndef BOOST_PARSER_DOXYGEN

        static constexpr auto true_ = std::true_type{};
        static constexpr auto false_ = std::false_type{};

        enum class merge_kind
        {
            singleton,
            merged,
            group
        };

        template<merge_kind Kind>
        struct merge_kind_t
        {
            static constexpr merge_kind kind = Kind;
        };

        template<merge_kind Kind>
        static constexpr auto wrap = merge_kind_t<Kind>{};

        struct combine
        {
            template<typename T, typename U>
            auto operator()(
                T result_merging_indices_and_prev_group, U x_and_group) const
            {
                using namespace literals;

                auto x = parser::get(x_and_group, 0_c);
                auto group = parser::get(x_and_group, 1_c);

                auto result =
                    parser::get(result_merging_indices_and_prev_group, 0_c);
                using result_back_type =
                    typename std::decay_t<decltype(detail::hl::back(
                        result))>::type;
                using unwrapped_optional_result_back_type =
                    detail::unwrapped_optional_t<result_back_type>;

                auto merging =
                    parser::get(result_merging_indices_and_prev_group, 1_c);
                auto indices =
                    parser::get(result_merging_indices_and_prev_group, 2_c);
                auto prev_group =
                    parser::get(result_merging_indices_and_prev_group, 3_c);

                using x_type = typename decltype(x)::type;
                using unwrapped_optional_x_type =
                    detail::unwrapped_optional_t<x_type>;

                if constexpr (detail::is_nope_v<x_type>) {
                    if constexpr (
                        !detail::is_nope_v<result_back_type> &&
                        0 < decltype(group)::value &&
                        decltype(group)::value != decltype(prev_group)::value) {
                        // T >> merge[nope >> ...] -> nope
                        // This is a very special case.  If we see a nope at
                        // the begining of a group, and there's a non-nope
                        // before it, we put the nope in place in the result
                        // tuple temporarily, knowing that a non-nope will
                        // come along later in the group to replace it.
                        return detail::hl::make_tuple(
                            detail::hl::append(result, x),
                            detail::hl::append(
                                merging, wrap<merge_kind::singleton>),
                            detail::hl::append(
                                indices, detail::hl::size(result)),
                            group);
                    } else {
                        // T >> nope -> T
                        return detail::hl::make_tuple(
                            result,
                            detail::hl::append(
                                merging, wrap<merge_kind::singleton>),
                            detail::hl::append(
                                indices, detail::hl::size_minus_one(result)),
                            prev_group);
                    }
                } else if constexpr (detail::is_nope_v<result_back_type>) {
                    // tuple<nope> >> T -> tuple<T>
                    return detail::hl::make_tuple(
                        detail::hl::append(detail::hl::drop_back(result), x),
                        detail::hl::append(
                            merging, wrap<merge_kind::singleton>),
                        detail::hl::append(
                            indices, detail::hl::size_minus_one(result)),
                        group);
                } else if constexpr (
                    decltype(group)::value == -1 ||
                    decltype(group)::value != decltype(prev_group)::value) {
                    return detail::hl::make_tuple(
                        detail::hl::append(result, x),
                        detail::hl::append(
                            merging, wrap<merge_kind::singleton>),
                        detail::hl::append(indices, detail::hl::size(result)),
                        group);
                } else if constexpr (0 < decltype(group)::value) {
                    if constexpr (
                        decltype(prev_group)::value == decltype(group)::value) {
                        return detail::hl::make_tuple(
                            result,
                            detail::hl::append(
                                merging, wrap<merge_kind::group>),
                            detail::hl::append(
                                indices, detail::hl::size_minus_one(result)),
                            group);
                    } else {
                        return detail::hl::make_tuple(
                            detail::hl::append(result, x),
                            detail::hl::append(
                                merging, wrap<merge_kind::group>),
                            detail::hl::append(
                                indices, detail::hl::size(result)),
                            group);
                    }
                } else if constexpr (
                    detail::is_char_type_v<result_back_type> &&
                    (detail::is_char_type_v<x_type> ||
                     detail::is_char_type_v<unwrapped_optional_x_type>)) {
                    // CHAR >> CHAR -> string
                    return detail::hl::make_tuple(
                        detail::hl::append(
                            detail::hl::drop_back(result),
                            detail::wrapper<std::string>{}),
                        detail::hl::append(
                            detail::hl::append(
                                detail::hl::drop_front(merging),
                                wrap<merge_kind::merged>),
                            wrap<merge_kind::merged>),
                        detail::hl::append(
                            indices, detail::hl::size_minus_one(result)),
                        group);
                } else if constexpr (
                    detail::
                        container_and_value_type<result_back_type, x_type> ||
                    detail::container_and_value_type<
                        result_back_type,
                        unwrapped_optional_x_type>) {
                    // C<T> >> T -> C<T>
                    // C<T> >> optional<T> -> C<T>
                    return detail::hl::make_tuple(
                        result,
                        detail::hl::append(merging, wrap<merge_kind::merged>),
                        detail::hl::append(
                            indices, detail::hl::size_minus_one(result)),
                        group);
                } else if constexpr (
                    detail::
                        container_and_value_type<x_type, result_back_type> ||
                    detail::container_and_value_type<
                        x_type,
                        unwrapped_optional_result_back_type>) {
                    // T >> C<T> -> C<T>
                    // optional<T> >> C<T> -> C<T>
                    return detail::hl::make_tuple(
                        detail::hl::append(detail::hl::drop_back(result), x),
                        detail::hl::append(
                            detail::hl::append(
                                detail::hl::drop_front(merging),
                                wrap<merge_kind::merged>),
                            wrap<merge_kind::singleton>),
                        detail::hl::append(
                            indices, detail::hl::size_minus_one(result)),
                        group);
                } else {
                    // tuple<Ts...> >> T -> tuple<Ts..., T>
                    return detail::hl::make_tuple(
                        detail::hl::append(result, x),
                        detail::hl::append(
                            merging, wrap<merge_kind::singleton>),
                        detail::hl::append(indices, detail::hl::size(result)),
                        group);
                }
            }
        };

        template<long long I>
        static constexpr auto
        merging_from_group(integral_constant<long long, I>)
        {
            if constexpr (0 < I)
                return wrap<merge_kind::group>;
            else
                return wrap<merge_kind::singleton>;
        }

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
            using namespace literals;

            detail::dummy_use_parser_t<
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

            using combining_groups =
                detail::combining_t<ParserTuple, CombiningGroups>;
            constexpr auto first_group = detail::hl::front(combining_groups{});

            // Generate a tuple of outputs; the index that each parser should
            // use to write into its output; and whether the attribute for
            // each parser was merged into an adjacent container-attribute.
            constexpr auto combine_start = detail::hl::make_tuple(
                detail::hl::make_tuple(detail::hl::front(all_types_wrapped{})),
                detail::hl::make_tuple(merging_from_group(first_group)),
                tuple<llong<0>>{},
                first_group);
            using combined_types = decltype(detail::hl::fold_left(
                detail::hl::zip(
                    detail::hl::drop_front(all_types_wrapped{}),
                    detail::hl::drop_front(combining_groups{})),
                combine_start,
                combine{}));

            // Unwrap the result tuple's types.
            constexpr auto result_type_wrapped =
                parser::get(combined_types{}, 0_c);
            using result_type = decltype(detail::hl::transform(
                result_type_wrapped, detail::unwrap{}));

            using indices = decltype(parser::get(combined_types{}, 2_c));

            return detail::hl::make_tuple(
                result_type{}, indices{}, parser::get(combined_types{}, 1_c));
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

            auto temp_result = make_temp_result(
                use_cbs, first, last, context, skip, flags, success);

            std::decay_t<decltype(parser::get(temp_result, llong<0>{}))> retval;

            auto _ = detail::scoped_trace(
                *this,
                first_,
                last,
                context,
                detail::in_apply_parser(flags) ? detail::disable_trace(flags)
                                               : flags,
                retval);

            std::decay_t<decltype(parser::get(temp_result, llong<1>{}))>
                indices;
            std::decay_t<decltype(parser::get(temp_result, llong<2>{}))>
                merged;
            call_impl(
                use_cbs,
                first,
                last,
                context,
                skip,
                flags,
                success,
                retval,
                indices,
                merged);

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

            auto temp_result = make_temp_result(
                use_cbs, first, last, context, skip, flags, success);
            using temp_result_attr_t =
                std::decay_t<decltype(parser::get(temp_result, llong<0>{}))>;
            std::decay_t<decltype(parser::get(temp_result, llong<1>{}))>
                indices;
            std::decay_t<decltype(parser::get(temp_result, llong<2>{}))>
                merged;
            if constexpr (detail::is_optional_v<Attribute>) {
                typename Attribute::value_type attr;
                call(
                    use_cbs, first_, last, context, skip, flags, success, attr);
                if (success)
                    detail::assign(retval, std::move(attr));
            } else if constexpr (
                detail::is_tuple<Attribute>{} ||
                detail::is_struct_compatible_v<Attribute, temp_result_attr_t>) {
                call_impl(
                    use_cbs,
                    first,
                    last,
                    context,
                    skip,
                    flags,
                    success,
                    retval,
                    indices,
                    merged);

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
                    indices,
                    merged);

                if (success && detail::gen_attrs(flags)) {
                    detail::assign(
                        retval, std::move(detail::hl::front(temp_retval)));
                }
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
            typename Indices,
            typename Merged>
        void call_impl(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval,
            Indices const & indices,
            Merged const & merged) const
        {
            static_assert(
                detail::is_tuple<Attribute>{} || std::is_aggregate_v<Attribute>,
                "");

            auto use_parser = [use_cbs,
                               &first,
                               last,
                               &context,
                               &skip,
                               flags,
                               &success,
                               &retval](auto const &
                                            parser_index_merged_and_backtrack) {
                using namespace literals;
                detail::skip(first, last, skip, flags);
                if (!success) // Someone earlier already failed...
                    return;

                auto const & parser =
                    parser::get(parser_index_merged_and_backtrack, 0_c);
                auto merge_kind_t_ =
                    parser::get(parser_index_merged_and_backtrack, 2_c);
                constexpr bool was_merged_into_adjacent_container =
                    decltype(merge_kind_t_)::kind == merge_kind::merged;
                constexpr bool is_in_a_group =
                    decltype(merge_kind_t_)::kind == merge_kind::group;
                bool const can_backtrack =
                    parser::get(parser_index_merged_and_backtrack, 3_c);

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

                auto const tuple_idx =
                    parser::get(parser_index_merged_and_backtrack, 1_c);
                auto const tuple_size = detail::tuple_or_struct_size(retval);
                static_assert(
                    decltype(tuple_idx)::value < decltype(tuple_size)::value,
                    "Looks like you're trying to write some attribute into an "
                    "out-of-bounds position in a tuple/struct.  In other "
                    "words, the attribute you're parsing into does not match "
                    "the default attribute used by this parser.  This may be "
                    "because you passed an out-param to parse() at the top "
                    "level that is not compatible with the attribute type "
                    "generated by the parser you passed to parse().");
                if constexpr (!(decltype(tuple_idx)::value <
                                decltype(tuple_size)::value)) {
                    [[maybe_unused]] detail::print_type<Attribute> _;
                }
                auto & out = parser::get(retval, tuple_idx);

                using attr_t = decltype(parser.call(
                    use_cbs, first, last, context, skip, flags, success));
                constexpr bool out_container =
                    container<std::decay_t<decltype(out)>>;
                constexpr bool attr_container = container<attr_t>;

                if constexpr (
                    (out_container == attr_container &&
                     !was_merged_into_adjacent_container) ||
                    is_in_a_group) {
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
                    if constexpr (out_container) {
                        detail::move_back(
                            out, std::move(x), detail::gen_attrs(flags));
                    } else {
                        detail::assign(out, std::move(x));
                    }
                }
            };

            auto const parsers_and_indices =
                detail::hl::zip(parsers_, indices, merged, backtracking{});
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
            BOOST_PARSER_SUBRANGE const where(initial_first, first);
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
        BOOST_PARSER_SUBRANGE<Iter> call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            BOOST_PARSER_SUBRANGE<Iter> retval;
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
            parser_.call(
                use_cbs,
                first,
                last,
                context,
                skip,
                detail::disable_attrs(flags),
                success);
            if (success && detail::gen_attrs(flags))
                detail::assign(
                    retval, BOOST_PARSER_SUBRANGE<Iter>(initial_first, first));
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
            auto r =
                parser::detail::text::unpack_iterator_and_sentinel(first, last);
            static_assert(
                std::contiguous_iterator<decltype(r.first)>,
                "string_view_parser and the string_view[] directive that uses "
                "it requires that the underlying char sequence being parsed be "
                "a contiguous range.  If you're seeing this static_assert, you "
                "have not met this contract.");
            using char_type = detail::remove_cv_ref_t<decltype(*r.first)>;
            std::basic_string_view<char_type> retval;
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
            parser_.call(
                use_cbs,
                first,
                last,
                context,
                skip,
                detail::disable_attrs(flags),
                success);

            if (!success || !detail::gen_attrs(flags))
                return;

            auto r = parser::detail::text::unpack_iterator_and_sentinel(
                initial_first, first);
            static_assert(
                std::contiguous_iterator<decltype(r.first)>,
                "string_view_parser and the string_view[] directive that uses "
                "it requires that the underlying char sequence being parsed be "
                "a contiguous range.  If you're seeing this static_assert, you "
                "have not met this contract.");
            using char_type = detail::remove_cv_ref_t<decltype(*r.first)>;
            if (initial_first == first) {
                detail::assign(retval, std::basic_string_view<char_type>{});
            } else {
                detail::assign(
                    retval,
                    std::basic_string_view<char_type>{
                        &*r.first, std::size_t(r.last - r.first)});
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

    template<typename Parser>
    struct no_case_parser
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
            Context const & context_,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            auto context = context_;
            ++context.no_case_depth_;

            using attr_t = decltype(parser_.call(
                use_cbs, first, last, context, skip, flags, success));
            attr_t retval{};
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
            Context const & context_,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto context = context_;
            ++context.no_case_depth_;

            auto _ = detail::scoped_trace(
                *this, first, last, context, flags, retval);

            parser_.call(
                use_cbs, first, last, context, skip, flags, success, retval);
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
            call(use_cbs, first, last, context, skip, flags, success, retval);
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
            parser::detail::text::trie<std::vector<char32_t>, T> & trie_ =
                detail::get_trie(context, ref());
            return trie_[str | detail::text::as_utf32];
        }

        /** Inserts an entry consisting of a UTF-8 string `str` to match, and
            an associtated attribute `x`, to the copy of the symbol table
            inside the parse context `context`. */
        template<typename Context>
        void insert(Context const & context, std::string_view str, T && x) const
        {
            parser::detail::text::trie<std::vector<char32_t>, T> & trie_ =
                detail::get_trie(context, ref());
            trie_.insert(str | detail::text::as_utf32, std::move(x));
        }

        /** Erases the entry whose UTF-8 match string is `str` from the copy
            of the symbol table inside the parse context `context`. */
        template<typename Context>
        void erase(Context const & context, std::string_view str) const
        {
            parser::detail::text::trie<std::vector<char32_t>, T> & trie_ =
                detail::get_trie(context, ref());
            trie_.erase(str | detail::text::as_utf32);
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

            parser::detail::text::trie<std::vector<char32_t>, T> const & trie_ =
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
        auto call(
            std::bool_constant<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            constexpr bool recursive_rule =
                std::is_same_v<typename Context::rule_tag, tag_type> &&
                !std::is_same_v<typename Context::rule_tag, void>;

            if constexpr (recursive_rule)
                flags = detail::disable_attrs(flags);

            attr_type retval{};
            locals_type locals = detail::make_locals<locals_type>(context);
            auto params = detail::resolve_rule_params(context, params_);
            tag_type * const tag_ptr = nullptr;
            auto const rule_context = detail::make_rule_context(
                context, tag_ptr, retval, locals, params);
            auto _ = detail::scoped_trace(
                *this, first, last, rule_context, flags, retval);

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

            if constexpr (CanUseCallbacks && UseCallbacks && !recursive_rule) {
                if (!success)
                    return attr_type{};

                auto const & callbacks = _callbacks(context);

                if constexpr (detail::is_nope_v<attr_type>) {
                    static_assert(
                        detail::is_invocable_v<decltype(callbacks), tag_type>,
                        "For rules without attributes, Callbacks must be a "
                        "struct with overloads of the form void(tag_type).  If "
                        "you're seeing an error here, you probably have not "
                        "met this contract.");
                    callbacks(tag_type{});
                } else {
                    static_assert(
                        detail::is_invocable_v<
                            decltype(callbacks),
                            tag_type,
                            decltype(std::move(retval))>,
                        "For rules with attributes, Callbacks must be a struct "
                        "with overloads of the form void(tag_type, attr_type). "
                        "If you're seeing an error here, you probably have not "
                        "met this contract.");
                    callbacks(tag_type{}, std::move(retval));
                }

                return attr_type{};
            } else {
                if (!success && !recursive_rule)
                    detail::assign(retval, attr_type());
                if constexpr (recursive_rule)
                    return detail::nope{};
                else
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
                auto attr =
                    call(use_cbs, first, last, context, skip, flags, success);
                if (success)
                    detail::assign(retval, std::move(attr));
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
                    tuple<std::true_type, std::true_type>,
                    tuple<llong<0>, llong<0>>>;
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
                std::enable_if_t<detail::is_parsable_range_like_v<R>>>
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
                    tuple<std::true_type, std::false_type>,
                    tuple<llong<0>, llong<0>>>;
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
                std::enable_if_t<detail::is_parsable_range_like_v<R>>>
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
                std::enable_if_t<detail::is_parsable_range_like_v<R>>>
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
                std::enable_if_t<detail::is_parsable_range_like_v<R>>>
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
                std::enable_if_t<detail::is_parsable_range_like_v<R>>>
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
            in all subsequent top-level parses.  Subsequent lookups during the
            current top-level parse will not match `str`. */
        symbols & insert_for_next_parse(std::string_view str, T x)
        {
            this->parser_.initial_elements_.push_back(
                std::pair<std::string_view, T>(str, std::move(x)));
            return *this;
        }

        /** Equivalent to `insert_for_next_parse(str, std::move(x))`. */
        symbols & operator()(std::string_view str, T x)
        {
            return insert_for_next_parse(str, std::move(x));
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
        static_assert(
            !std::is_same_v<TagType, void>,
            "void is not a valid tag type for a rule.");

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

#define BOOST_PARSER_DEFINE_IMPL(_, name_)                                     \
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
        auto const & parser = BOOST_PARSER_PP_CAT(name_, _def);                \
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
        auto const & parser = BOOST_PARSER_PP_CAT(name_, _def);                \
        using attr_t = decltype(parser(                                        \
            use_cbs, first, last, context, skip, flags, success));             \
        if constexpr (boost::parser::detail::is_nope_v<attr_t>) {              \
            parser(use_cbs, first, last, context, skip, flags, success);       \
        } else {                                                               \
            parser(                                                            \
                use_cbs, first, last, context, skip, flags, success, retval);  \
        }                                                                      \
    }

#endif

    /** For each given token `t`, defines a pair of `parse_rule()` overloads,
        used internally within Boost.Parser.  Each such pair implements the
        parsing behavior rule `t`, using the parser `t_def`.  This macro is
        only available when the Boost.Preprocessor headers are available. */
#define BOOST_PARSER_DEFINE_RULES(...)                                         \
    BOOST_PARSER_PP_FOR_EACH(BOOST_PARSER_DEFINE_IMPL, _, __VA_ARGS__)

    /** Defines a pair of `parse_rule()` overloads for the given rule, used
        internally within Boost.Parser.  The pair implements the parsing
        behavior rule `rule`, using the parser `rule_def`. */
#define BOOST_PARSER_DEFINE_RULE(rule) BOOST_PARSER_DEFINE_IMPL(_, rule)


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

    template<
        typename ParserTuple,
        typename BacktrackingTuple,
        typename CombiningGroups>
    template<bool AllowBacktracking, typename Parser>
    constexpr auto
    seq_parser<ParserTuple, BacktrackingTuple, CombiningGroups>::prepend(
        parser_interface<Parser> parser) const noexcept
    {
        using combining_groups =
            detail::combining_t<ParserTuple, CombiningGroups>;
        using final_combining_groups =
            decltype(detail::hl::prepend(combining_groups{}, llong<0>{}));
        using backtracking = decltype(detail::hl::prepend(
            detail::hl::prepend(
                detail::hl::drop_front(BacktrackingTuple{}),
                std::bool_constant<AllowBacktracking>{}),
            std::true_type{}));
        using parser_t = seq_parser<
            decltype(detail::hl::prepend(parsers_, parser.parser_)),
            backtracking,
            final_combining_groups>;
        return parser_interface{
            parser_t{detail::hl::prepend(parsers_, parser.parser_)}};
    }

    template<
        typename ParserTuple,
        typename BacktrackingTuple,
        typename CombiningGroups>
    template<bool AllowBacktracking, typename Parser>
    constexpr auto
    seq_parser<ParserTuple, BacktrackingTuple, CombiningGroups>::append(
        parser_interface<Parser> parser) const noexcept
    {
        using combining_groups =
            detail::combining_t<ParserTuple, CombiningGroups>;
        if constexpr (detail::is_seq_p<Parser>{}) {
            using parser_combining_groups = detail::combining_t<
                decltype(parser.parser_.parsers_),
                typename Parser::combining_groups>;
            using final_combining_groups = detail::
                combined_combining_t<combining_groups, parser_combining_groups>;
            using backtracking = decltype(detail::hl::concat(
                BacktrackingTuple{}, typename Parser::backtracking{}));
            using parser_t = seq_parser<
                decltype(detail::hl::concat(parsers_, parser.parser_.parsers_)),
                backtracking,
                final_combining_groups>;
            return parser_interface{parser_t{
                detail::hl::concat(parsers_, parser.parser_.parsers_)}};
        } else {
            using final_combining_groups =
                decltype(detail::hl::append(combining_groups{}, llong<0>{}));
            using backtracking = decltype(detail::hl::append(
                BacktrackingTuple{}, std::bool_constant<AllowBacktracking>{}));
            using parser_t = seq_parser<
                decltype(detail::hl::append(parsers_, parser.parser_)),
                backtracking,
                final_combining_groups>;
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

    /** The `omit` directive, whose `operator[]` returns a
        `parser_interface<omit_parser<P>>` from a given parser of type
        `parser_interface<P>`. */
    inline constexpr directive<omit_parser> omit;

    /** The `raw` directive, whose `operator[]` returns a
        `parser_interface<raw_parser<P>>` from a given parser of type
        `parser_interface<P>`. */
    inline constexpr directive<raw_parser> raw;

#if defined(BOOST_PARSER_DOXYGEN) || defined(__cpp_lib_concepts)
    /** The `string_view` directive, whose `operator[]` returns a
        `parser_interface<string_view_parser<P>>` from a given parser of type
        `parser_interface<P>`.  This is only available in C++20 and later. */
    inline constexpr directive<string_view_parser> string_view;
#endif

    /** The `lexeme` directive, whose `operator[]` returns a
        `parser_interface<lexeme_parser<P>>` from a given parser of type
        `parser_interface<P>`. */
    inline constexpr directive<lexeme_parser> lexeme;

    /** The `no_case` directive, whose `operator[]` returns a
        `parser_interface<no_case_parser<P>>` from a given parser of type
        `parser_interface<P>`. */
    inline constexpr directive<no_case_parser> no_case;

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
        `operator[]` returns a `parser_interface<repeat_parser<P>>` from a
        given parser of type `parser_interface<P>`. */
    template<typename T>
    constexpr repeat_directive<T, T> repeat(T n) noexcept
    {
        return repeat_directive<T, T>{n, n};
    }

    /** Returns a `repeat_directive` that repeats between `min_` and `max_`
        times, inclusive, and whose `operator[]` returns a
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

    /** The `skip_directive`, whose `operator[]` returns a
        `parser_interface<skip_parser<P>>` from a given parser of type
        `parser_interface<P>`. */
    inline constexpr skip_directive<> skip;

    /** A directive type that can only be used on sequence parsers, that
        forces the merge of all the sequence_parser's subparser's attributes
        into a single attribute. */
    struct merge_directive
    {
        template<
            typename ParserTuple,
            typename BacktrackingTuple,
            typename CombiningGroups>
        constexpr auto
        operator[](parser_interface<
                   seq_parser<ParserTuple, BacktrackingTuple, CombiningGroups>>
                       rhs) const noexcept
        {
            return parser_interface{
                seq_parser<ParserTuple, BacktrackingTuple, detail::merge_t>{
                    rhs.parser_.parsers_}};
        }
    };

    /** The `merge_directive`, whose `operator[]` returns a
        `parser_interface<P2>`, from a given parser of type
        `parser_interface<P>`, where `P` is a `seq_parser`.  `P2` is the same
        as `P`, except that its `CombiningGroups` template parameter is
        replaced with a tag type that causes the subparser's attributes to be
        merged into a single attribute. */
    inline constexpr merge_directive merge;

    /** A directive type that can only be used on sequence parsers, that
        prevents each of the sequence_parser's subparser's attributes from
        merging with any other subparser's attribute. */
    struct separate_directive
    {
        template<
            typename ParserTuple,
            typename BacktrackingTuple,
            typename CombiningGroups>
        constexpr auto
        operator[](parser_interface<
                   seq_parser<ParserTuple, BacktrackingTuple, CombiningGroups>>
                       rhs) const noexcept
        {
            return parser_interface{
                seq_parser<ParserTuple, BacktrackingTuple, detail::separate_t>{
                    rhs.parser_.parsers_}};
        }
    };

    /** The `separate_directive`, whose `operator[]` returns a
        `parser_interface<P2>`, from a given parser of type
        `parser_interface<P>`, where `P` is a `seq_parser`.  `P2` is the same
        as `P`, except that its `CombiningGroups` template parameter is
        replaced with a tag type that prevents each subparser's attribute from
        merging with any other subparser's attribute. */
    inline constexpr separate_directive separate;


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
            BOOST_PARSER_SUBRANGE const where(first, first);
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
            BOOST_PARSER_SUBRANGE const where(first, first);
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
                std::enable_if_t<!detail::is_parsable_range_like_v<T>>>
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
            matches any value in `[lo, hi]`. */
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
                std::enable_if_t<detail::is_parsable_range_like_v<R>>>
#endif
        constexpr auto operator()(R && r) const noexcept
        {
            BOOST_PARSER_ASSERT(
                ((!std::is_rvalue_reference_v<R &&> ||
                  !detail::is_range<detail::remove_cv_ref_t<R>>) &&
                     "It looks like you tried to pass an rvalue range to "
                     "char_().  Don't do that, or you'll end up with dangling "
                     "references."));
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
        point values in a string; a closed range of code point values `[lo,
        hi]`, or a set of code point values passed as a range. */
    inline constexpr parser_interface<char_parser<detail::nope>> char_;

    /** The literal code point parser.  It produces a 32-bit unsigned integer
        attribute.  This parser can be used to create code point parsers that
        match one or more specific code point values, by calling it with: a
        single value comparable to a code point; a set of code point values in
        a string; a closed range of code point values `[lo, hi]`, or a set
        of code point values passed as a range. */
    inline constexpr parser_interface<char_parser<detail::nope, char32_t>> cp;

    /** The literal code unit parser.  It produces a `char` attribute.  This
        parser can be used to create code unit parsers that match one or more
        specific code unit values, by calling it with: a single value
        comparable to a code unit; a set of code unit values in a string; a
        closed range of code unit values `[lo, hi]`, or a set of code unit
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
                std::enable_if_t<detail::is_parsable_range_like_v<R>>>
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

            if constexpr (std::is_same_v<
                              detail::remove_cv_ref_t<decltype(*first)>,
                              char32_t>) {
                auto const cps =
                    BOOST_PARSER_SUBRANGE(expected_first_, expected_last_) |
                    detail::text::as_utf32;

                auto const mismatch = detail::no_case_aware_string_mismatch(
                    first,
                    last,
                    cps.begin(),
                    cps.end(),
                    context.no_case_depth_);
                if (mismatch.second != cps.end()) {
                    success = false;
                    return;
                }

                detail::append(
                    retval, first, mismatch.first, detail::gen_attrs(flags));

                first = mismatch.first;
            } else {
                auto const mismatch = detail::no_case_aware_string_mismatch(
                    first,
                    last,
                    expected_first_,
                    expected_last_,
                    context.no_case_depth_);
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

            auto compare =
                [no_case = context.no_case_depth_](char32_t a, char32_t b) {
                    if (no_case && 0x41 <= b && b < 0x5b)
                        b += 0x20;
                    return a == b;
                };

            // The lambda quiets a signed/unsigned mismatch warning when
            // comparing the chars here to code points.
            char const t[] = "true";
            if (detail::mismatch(t, t + 4, first, last, compare).first ==
                t + 4) {
                std::advance(first, 4);
                detail::assign(retval, true);
                return;
            }
            char const f[] = "false";
            if (detail::mismatch(f, f + 5, first, last, compare).first ==
                f + 5) {
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

    /** The hexadecimal unsigned integer parser.  Produces an `unsigned int`
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
        typename Enable = std::enable_if_t<detail::is_parsable_range_like_v<R>>>
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
        typename Enable = std::enable_if_t<detail::is_parsable_range_like_v<R>>>
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
        typename Enable = std::enable_if_t<detail::is_parsable_range_like_v<R>>>
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
        typename Enable = std::enable_if_t<detail::is_parsable_range_like_v<R>>>
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
        typename Enable = std::enable_if_t<detail::is_parsable_range_like_v<R>>>
#endif
    constexpr auto operator%(R && r, parser_interface<Parser> rhs) noexcept
    {
        return parser::lit(r) % rhs;
    }

}}

#include <boost/parser/detail/printing_impl.hpp>

namespace boost { namespace parser {

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
            detail::is_parsable_iter_v<I> &&
            detail::is_equality_comparable_with_v<I, S>>>
#endif
    bool prefix_parse(
        I & first,
        S last,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        Attr & attr,
        trace trace_mode = trace::off)
    {
        if constexpr (!detail::is_char8_iter_v<I>) {
            static_assert(
                decltype(detail::has_attribute(first, last, parser)){},
                "If you're seeing this error, you're trying to get parse() to "
                "fill in attr above, using the attribute generated by parser. "
                "However, parser does not generate an attribute.");
            if (trace_mode == trace::on) {
                return detail::parse_impl<true>(
                    first, last, parser, parser.error_handler_, attr);
            } else {
                return detail::parse_impl<false>(
                    first, last, parser, parser.error_handler_, attr);
            }
        } else {
            auto r =
                BOOST_PARSER_SUBRANGE(first, last) | detail::text::as_utf32;
            auto f = r.begin();
            auto const l = r.end();
            auto _ = detail::scoped_base_assign(first, f);
            static_assert(
                decltype(detail::has_attribute(f, l, parser)){},
                "If you're seeing this error, you're trying to get parse() to "
                "fill in attr above, using the attribute generated by parser. "
                "However, parser does not generate an attribute.");
            if (trace_mode == trace::on) {
                return detail::parse_impl<true>(
                    f, l, parser, parser.error_handler_, attr);
            } else {
                return detail::parse_impl<false>(
                    f, l, parser, parser.error_handler_, attr);
            }
        }
    }

    /** Parses `r` using `parser`, and returns whether the parse was
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
            std::enable_if_t<detail::is_parsable_range_like_v<R>>>
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
            std::ranges::iterator_t<decltype(detail::make_input_subrange(r))>,
            std::ranges::sentinel_t<decltype(detail::make_input_subrange(r))>,
            GlobalState>
    // clang-format on
#endif
    {
        auto r_ = detail::make_input_subrange(r);
        auto first = r_.begin();
        auto const last = r_.end();
        return detail::if_full_parse(
            first,
            last,
            parser::prefix_parse(first, last, parser, attr, trace_mode));
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
            detail::is_parsable_iter_v<I> &&
            detail::is_equality_comparable_with_v<I, S>>>
#endif
    auto prefix_parse(
        I & first,
        S last,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        trace trace_mode = trace::off)
    {
        if constexpr (!detail::is_char8_iter_v<I>) {
            if (trace_mode == trace::on) {
                return detail::parse_impl<true>(
                    first, last, parser, parser.error_handler_);
            } else {
                return detail::parse_impl<false>(
                    first, last, parser, parser.error_handler_);
            }
        } else {
            auto r =
                BOOST_PARSER_SUBRANGE(first, last) | detail::text::as_utf32;
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

    /** Parses `r` using `parser`.  Returns a `std::optional` containing the
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
        typename Enable = std::enable_if_t<detail::is_parsable_range_like_v<R>>>
#endif
    auto parse(
        R const & r,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        trace trace_mode = trace::off)
#if BOOST_PARSER_USE_CONCEPTS
        // clang-format off
        requires error_handler<
            ErrorHandler,
            std::ranges::iterator_t<decltype(detail::make_input_subrange(r))>,
            std::ranges::sentinel_t<decltype(detail::make_input_subrange(r))>,
            GlobalState>
    // clang-format on
#endif
    {
        auto r_ = detail::make_input_subrange(r);
        auto first = r_.begin();
        auto const last = r_.end();
        return detail::if_full_parse(
            first, last, parser::prefix_parse(first, last, parser, trace_mode));
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
            detail::is_parsable_iter_v<I> &&
            detail::is_equality_comparable_with_v<I, S>>>
#endif
    bool prefix_parse(
        I & first,
        S last,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        parser_interface<SkipParser> const & skip,
        Attr & attr,
        trace trace_mode = trace::off)
    {
        if constexpr (!detail::is_char8_iter_v<I>) {
            static_assert(
                decltype(detail::has_attribute(first, last, parser)){},
                "If you're seeing this error, you're trying to get parse() to "
                "fill in attr above, using the attribute generated by parser. "
                "However, parser does not generate an attribute.");
            if (trace_mode == trace::on) {
                return detail::skip_parse_impl<true>(
                    first, last, parser, skip, parser.error_handler_, attr);
            } else {
                return detail::skip_parse_impl<false>(
                    first, last, parser, skip, parser.error_handler_, attr);
            }
        } else {
            auto r =
                BOOST_PARSER_SUBRANGE(first, last) | detail::text::as_utf32;
            auto f = r.begin();
            auto const l = r.end();
            auto _ = detail::scoped_base_assign(first, f);
            static_assert(
                decltype(detail::has_attribute(f, l, parser)){},
                "If you're seeing this error, you're trying to get parse() to "
                "fill in attr above, using the attribute generated by parser. "
                "However, parser does not generate an attribute.");
            if (trace_mode == trace::on) {
                return detail::skip_parse_impl<true>(
                    f, l, parser, skip, parser.error_handler_, attr);
            } else {
                return detail::skip_parse_impl<false>(
                    f, l, parser, skip, parser.error_handler_, attr);
            }
        }
    }

    /** Parses `r` using `parser`, skipping all input recognized by `skip`
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
        typename Enable = std::enable_if_t<detail::is_parsable_range_like_v<R>>>
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
            std::ranges::iterator_t<decltype(detail::make_input_subrange(r))>,
            std::ranges::sentinel_t<decltype(detail::make_input_subrange(r))>,
            GlobalState>
    // clang-format on
#endif
    {
        auto r_ = detail::make_input_subrange(r);
        auto first = r_.begin();
        auto const last = r_.end();
        return detail::if_full_parse(
            first,
            last,
            parser::prefix_parse(first, last, parser, skip, attr, trace_mode));
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
            detail::is_parsable_iter_v<I> &&
            detail::is_equality_comparable_with_v<I, S>>>
#endif
    auto prefix_parse(
        I & first,
        S last,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        parser_interface<SkipParser> const & skip,
        trace trace_mode = trace::off)
    {
        if constexpr (!detail::is_char8_iter_v<I>) {
            if (trace_mode == trace::on) {
                return detail::skip_parse_impl<true>(
                    first, last, parser, skip, parser.error_handler_);
            } else {
                return detail::skip_parse_impl<false>(
                    first, last, parser, skip, parser.error_handler_);
            }
        } else {
            auto r =
                BOOST_PARSER_SUBRANGE(first, last) | detail::text::as_utf32;
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
            detail::is_parsable_iter_v<I> &&
            detail::is_equality_comparable_with_v<I, S>>>
#endif
    auto prefix_parse(
        I & first,
        S last,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        rule<TagType, Attribute, LocalState, ParamsTuple> const & skip,
        trace trace_mode = trace::off)
    {
        if constexpr (!detail::is_char8_iter_v<I>) {
            if (trace_mode == trace::on) {
                return detail::skip_parse_impl<true>(
                    first, last, parser, skip, parser.error_handler_);
            } else {
                return detail::skip_parse_impl<false>(
                    first, last, parser, skip, parser.error_handler_);
            }
        } else {
            auto r =
                BOOST_PARSER_SUBRANGE(first, last) | detail::text::as_utf32;
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
            detail::is_parsable_iter_v<I> &&
            detail::is_equality_comparable_with_v<I, S>>>
#endif
    auto prefix_parse(
        I & first,
        S last,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        callback_rule<TagType, Attribute, LocalState, ParamsTuple> const & skip,
        trace trace_mode = trace::off)
    {
        if constexpr (!detail::is_char8_iter_v<I>) {
            if (trace_mode == trace::on) {
                return detail::skip_parse_impl<true>(
                    first, last, parser, skip, parser.error_handler_);
            } else {
                return detail::skip_parse_impl<false>(
                    first, last, parser, skip, parser.error_handler_);
            }
        } else {
            auto r =
                BOOST_PARSER_SUBRANGE(first, last) | detail::text::as_utf32;
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

    /** Parses `r` using `parser`, skipping all input recognized by `skip`
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
        typename Enable = std::enable_if_t<detail::is_parsable_range_like_v<R>>>
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
            std::ranges::iterator_t<decltype(detail::make_input_subrange(r))>,
            std::ranges::sentinel_t<decltype(detail::make_input_subrange(r))>,
            GlobalState>
    // clang-format on
#endif
    {
        auto r_ = detail::make_input_subrange(r);
        auto first = r_.begin();
        auto const last = r_.end();
        return detail::if_full_parse(
            first,
            last,
            parser::prefix_parse(first, last, parser, skip, trace_mode));
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
        typename Enable = std::enable_if_t<detail::is_parsable_range_like_v<R>>>
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
            std::ranges::iterator_t<decltype(detail::make_input_subrange(r))>,
            std::ranges::sentinel_t<decltype(detail::make_input_subrange(r))>,
            GlobalState>
    // clang-format on
#endif
    {
        auto r_ = detail::make_input_subrange(r);
        auto first = r_.begin();
        auto const last = r_.end();
        return detail::if_full_parse(
            first,
            last,
            parser::prefix_parse(first, last, parser, skip, trace_mode));
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
        typename Enable = std::enable_if_t<detail::is_parsable_range_like_v<R>>>
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
            std::ranges::iterator_t<decltype(detail::make_input_subrange(r))>,
            std::ranges::sentinel_t<decltype(detail::make_input_subrange(r))>,
            GlobalState>
    // clang-format on
#endif
    {
        auto r_ = detail::make_input_subrange(r);
        auto first = r_.begin();
        auto const last = r_.end();
        return detail::if_full_parse(
            first,
            last,
            parser::prefix_parse(first, last, parser, skip, trace_mode));
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
            detail::is_parsable_iter_v<I> &&
            detail::is_equality_comparable_with_v<I, S>>>
#endif
    bool callback_prefix_parse(
        I & first,
        S last,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        Callbacks const & callbacks,
        trace trace_mode = trace::off)
    {
        if constexpr (!detail::is_char8_iter_v<I>) {
            if (trace_mode == trace::on) {
                return detail::callback_parse_impl<true>(
                    first, last, parser, parser.error_handler_, callbacks);
            } else {
                return detail::callback_parse_impl<false>(
                    first, last, parser, parser.error_handler_, callbacks);
            }
        } else {
            auto r =
                BOOST_PARSER_SUBRANGE(first, last) | detail::text::as_utf32;
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

    /** Parses `r` using `parser`, and returns whether the parse was
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
        typename Enable = std::enable_if_t<detail::is_parsable_range_like_v<R>>>
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
            std::ranges::iterator_t<decltype(detail::make_input_subrange(r))>,
            std::ranges::sentinel_t<decltype(detail::make_input_subrange(r))>,
            GlobalState>
    // clang-format on
#endif
    {
        auto r_ = detail::make_input_subrange(r);
        auto first = r_.begin();
        auto const last = r_.end();
        return detail::if_full_parse(
            first,
            last,
            parser::callback_prefix_parse(first, last, parser, callbacks));
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
            detail::is_parsable_iter_v<I> &&
            detail::is_equality_comparable_with_v<I, S>>>
#endif
    bool callback_prefix_parse(
        I & first,
        S last,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        parser_interface<SkipParser> const & skip,
        Callbacks const & callbacks,
        trace trace_mode = trace::off)
    {
        if constexpr (!detail::is_char8_iter_v<I>) {
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
            auto r =
                BOOST_PARSER_SUBRANGE(first, last) | detail::text::as_utf32;
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

    /** Parses `r` using `parser`, skipping all input recognized by `skip`
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
        typename Enable = std::enable_if_t<detail::is_parsable_range_like_v<R>>>
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
            std::ranges::iterator_t<decltype(detail::make_input_subrange(r))>,
            std::ranges::sentinel_t<decltype(detail::make_input_subrange(r))>,
            GlobalState>
    // clang-format on
#endif
    {
        auto r_ = detail::make_input_subrange(r);
        auto first = r_.begin();
        auto const last = r_.end();
        return detail::if_full_parse(
            first,
            last,
            parser::callback_prefix_parse(
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

    namespace detail {
        template<typename... Args>
        constexpr void static_assert_merge_attributes(tuple<Args...> parsers)
        {
            // This code chokes older GCCs.  I can't figure out why, and this
            // is an optional check, so I'm disabling it for those GCCS.
#if !defined(__GNUC__) || 13 <= __GNUC__
            using context_t = parse_context<
                char const *,
                char const *,
                default_error_handler>;
            using skipper_t = parser_interface<ws_parser<false>>;
            using use_parser_t = dummy_use_parser_t<
                false,
                char const *,
                char const *,
                context_t,
                skipper_t> const;
            using all_types =
                decltype(hl::transform(parsers, std::declval<use_parser_t>()));
            auto all_types_wrapped = hl::transform(all_types{}, detail::wrap{});
            auto first_non_nope = hl::fold_left(
                all_types_wrapped,
                wrapper<nope>{},
                [=](auto result, auto type) {
                    if constexpr (is_nope_v<typename decltype(result)::type>) {
                        return type;
                    } else {
                        return result;
                    }
                });
            using first_t = typename decltype(first_non_nope)::type;
            static_assert(
                !is_nope_v<first_t>,
                "It looks like you wrote merge[p1 >> p2 >> ... pn], and none "
                "of the parsers p1, p2, ... pn produces an attribute.  Please "
                "fix.");
            if constexpr (is_nope_v<first_t>) {
                [[maybe_unused]] detail::print_type<tuple<Args...>> tuple_types;
                [[maybe_unused]] detail::print_type<all_types> attribute_types;
            }
            hl::for_each(all_types_wrapped, [=](auto type) {
                using t = typename decltype(type)::type;
                if constexpr (!is_nope_v<t>) {
                    static_assert(
                        std::is_same_v<t, first_t>,
                        "If you see an error here, you wrote merge[p1 >> "
                        "p2 >> ... pn] where at least one of the types in "
                        "ATTR(p1), ATTR(p2), ... ATTR(pn) is not the same "
                        "type as one of the others.");
                    if constexpr (!std::is_same_v<t, first_t>) {
                        [[maybe_unused]] detail::print_type<tuple<Args...>>
                            tuple_types;
                        [[maybe_unused]] detail::print_type<all_types>
                            attribute_types;
                        [[maybe_unused]] detail::print_type<first_t> first_type;
                        [[maybe_unused]] detail::print_type<t> this_type;
                    }
                }
            });
#endif
        }
    }
}}

#endif
