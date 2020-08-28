#ifndef BOOST_PARSER_PARSER_HPP
#define BOOST_PARSER_PARSER_HPP

#include <boost/parser/parser_fwd.hpp>
#include <boost/parser/concepts.hpp>
#include <boost/parser/error_handling.hpp>
#include <boost/parser/detail/printing.hpp>
#include <boost/parser/detail/numeric.hpp>

#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/variadic/elem.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/text/algorithm.hpp>
#include <boost/text/trie.hpp>

#include <type_traits>
#include <variant>
#include <vector>


namespace boost { namespace parser {

    /** A simple view type used throughout the rest of the library. */
    template<typename I, std::sentinel_for<I> S = I>
    struct view : stl_interfaces::view_interface<view<I, S>>
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
    template<typename I, typename S>
    constexpr view<I, S> make_view(I first, S last) noexcept
    {
        return view<I, S>(first, last);
    }


    // TODO: Consider eps(cond) -> precondition(cond).


    /** A tag type used to create tag objects that can be used as keys usable
        to access values in the parse context. */
    template<typename T>
    constexpr hana::type<T> tag{};


    struct nope
    {
        // Assignable from anything.
        template<typename T>
        constexpr nope & operator=(T const &)
        {
            return *this;
        }

        // Convertible to optional.
        operator std::nullopt_t() const noexcept { return std::nullopt; }

        // Also acts as a dummy predicate.
        template<typename Context>
        constexpr bool operator()(Context const &) const noexcept
        {
            return true;
        }

        // Dereferencable.
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


    namespace detail {
        // Utility types.

        inline nope global_nope;

        template<typename Iter, typename Sentinel, typename ErrorHandler>
        inline auto make_context(
            Iter first,
            Sentinel last,
            bool & success,
            int & indent,
            ErrorHandler const & error_handler,
            nope &,
            symbol_table_tries_t & symbol_table_tries) noexcept
        {
            return hana::make_map(
                hana::make_pair(hana::type_c<begin_tag>, first),
                hana::make_pair(hana::type_c<end_tag>, last),
                hana::make_pair(hana::type_c<pass_tag>, &success),
                hana::make_pair(hana::type_c<val_tag>, global_nope),
                hana::make_pair(hana::type_c<attr_tag>, global_nope),
                hana::make_pair(hana::type_c<locals_tag>, global_nope),
                hana::make_pair(hana::type_c<rule_params_tag>, global_nope),
                hana::make_pair(hana::type_c<globals_tag>, global_nope),
                hana::make_pair(hana::type_c<trace_indent_tag>, &indent),
                hana::make_pair(
                    hana::type_c<error_handler_tag>, &error_handler),
                hana::make_pair(hana::type_c<callbacks_tag>, global_nope),
                hana::make_pair(
                    hana::type_c<symbol_table_tries_tag>, &symbol_table_tries));
        }

        template<
            typename Iter,
            typename Sentinel,
            typename ErrorHandler,
            typename GlobalState>
        inline auto make_context(
            Iter first,
            Sentinel last,
            bool & success,
            int & indent,
            ErrorHandler const & error_handler,
            GlobalState & globals,
            symbol_table_tries_t & symbol_table_tries) noexcept
        {
            return hana::make_map(
                hana::make_pair(hana::type_c<begin_tag>, first),
                hana::make_pair(hana::type_c<end_tag>, last),
                hana::make_pair(hana::type_c<pass_tag>, &success),
                hana::make_pair(hana::type_c<val_tag>, global_nope),
                hana::make_pair(hana::type_c<attr_tag>, global_nope),
                hana::make_pair(hana::type_c<locals_tag>, global_nope),
                hana::make_pair(hana::type_c<rule_params_tag>, global_nope),
                hana::make_pair(hana::type_c<globals_tag>, &globals),
                hana::make_pair(hana::type_c<trace_indent_tag>, &indent),
                hana::make_pair(
                    hana::type_c<error_handler_tag>, &error_handler),
                hana::make_pair(hana::type_c<callbacks_tag>, global_nope),
                hana::make_pair(
                    hana::type_c<symbol_table_tries_tag>, &symbol_table_tries));
        }

        template<
            typename Iter,
            typename Sentinel,
            typename ErrorHandler,
            typename Callbacks>
        inline auto make_context(
            Iter first,
            Sentinel last,
            bool & success,
            int & indent,
            ErrorHandler const & error_handler,
            Callbacks const & callbacks,
            nope &,
            symbol_table_tries_t & symbol_table_tries) noexcept
        {
            return hana::make_map(
                hana::make_pair(hana::type_c<begin_tag>, first),
                hana::make_pair(hana::type_c<end_tag>, last),
                hana::make_pair(hana::type_c<pass_tag>, &success),
                hana::make_pair(hana::type_c<val_tag>, global_nope),
                hana::make_pair(hana::type_c<attr_tag>, global_nope),
                hana::make_pair(hana::type_c<locals_tag>, global_nope),
                hana::make_pair(hana::type_c<rule_params_tag>, global_nope),
                hana::make_pair(hana::type_c<globals_tag>, global_nope),
                hana::make_pair(hana::type_c<trace_indent_tag>, &indent),
                hana::make_pair(
                    hana::type_c<error_handler_tag>, &error_handler),
                hana::make_pair(hana::type_c<callbacks_tag>, &callbacks),
                hana::make_pair(
                    hana::type_c<symbol_table_tries_tag>, &symbol_table_tries));
        }

        template<
            typename Iter,
            typename Sentinel,
            typename ErrorHandler,
            typename Callbacks,
            typename GlobalState>
        inline auto make_context(
            Iter first,
            Sentinel last,
            bool & success,
            int & indent,
            ErrorHandler const & error_handler,
            Callbacks const & callbacks,
            GlobalState & globals,
            symbol_table_tries_t & symbol_table_tries) noexcept
        {
            return hana::make_map(
                hana::make_pair(hana::type_c<begin_tag>, first),
                hana::make_pair(hana::type_c<end_tag>, last),
                hana::make_pair(hana::type_c<pass_tag>, &success),
                hana::make_pair(hana::type_c<val_tag>, global_nope),
                hana::make_pair(hana::type_c<attr_tag>, global_nope),
                hana::make_pair(hana::type_c<locals_tag>, global_nope),
                hana::make_pair(hana::type_c<rule_params_tag>, global_nope),
                hana::make_pair(hana::type_c<globals_tag>, &globals),
                hana::make_pair(hana::type_c<trace_indent_tag>, &indent),
                hana::make_pair(
                    hana::type_c<error_handler_tag>, &error_handler),
                hana::make_pair(hana::type_c<callbacks_tag>, &callbacks),
                hana::make_pair(
                    hana::type_c<symbol_table_tries_tag>, &symbol_table_tries));
        }


        template<unsigned int I>
        struct param_t
        {
            template<typename Context>
            decltype(auto) operator()(Context const & context) const
            {
                return _params(context)[hana::llong<I>{}];
            }
        };


        template<typename T, typename U>
        using callable = decltype(std::declval<T>()(std::declval<U>()));

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
        inline auto
        resolve_rule_params(Context const & context, ParamsTuple const & params)
        {
            return hana::transform(
                params, [&](auto const & x) { return resolve(context, x); });
        }

        template<typename Context>
        inline nope resolve_rule_params(Context const & context, nope)
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
            return make_locals_impl<LocalsType>(
                context,
                typename std::is_convertible<Context const &, LocalsType>::
                    type{});
        }

        template<
            typename Context,
            typename AttributeType,
            typename LocalState,
            typename ParamsTuple>
        inline auto make_rule_context(
            Context const & context,
            AttributeType & value,
            LocalState & locals,
            ParamsTuple const & params) noexcept
        {
            // Replace the context's current locals and params with these, and
            // its current val with value.
            return hana::insert(
                hana::insert(
                    hana::insert(
                        hana::erase_key(
                            hana::erase_key(
                                hana::erase_key(
                                    context, hana::type_c<locals_tag>),
                                hana::type_c<val_tag>),
                            hana::type_c<rule_params_tag>),
                        hana::make_pair(hana::type_c<locals_tag>, &locals)),
                    hana::make_pair(hana::type_c<val_tag>, &value)),
                hana::make_pair(hana::type_c<rule_params_tag>, &params));
        }

        template<typename Context, typename AttributeType, typename LocalState>
        inline auto make_rule_context(
            Context const & context,
            AttributeType & value,
            LocalState & locals,
            nope & params) noexcept
        {
            return hana::insert(
                hana::insert(
                    hana::erase_key(
                        hana::erase_key(context, hana::type_c<locals_tag>),
                        hana::type_c<val_tag>),
                    hana::make_pair(hana::type_c<locals_tag>, &locals)),
                hana::make_pair(hana::type_c<val_tag>, &value));
        }

        template<typename Context, typename LocalState, typename ParamsTuple>
        inline auto make_rule_context(
            Context const & context,
            nope & value,
            LocalState & locals,
            ParamsTuple const & params) noexcept
        {
            return hana::insert(
                hana::insert(
                    hana::erase_key(
                        hana::erase_key(context, hana::type_c<locals_tag>),
                        hana::type_c<rule_params_tag>),
                    hana::make_pair(hana::type_c<locals_tag>, &locals)),
                hana::make_pair(hana::type_c<rule_params_tag>, &params));
        }

        template<typename Context, typename LocalState>
        inline auto make_rule_context(
            Context const & context,
            nope & value,
            LocalState & locals,
            nope & params) noexcept
        {
            return hana::insert(
                hana::erase_key(context, hana::type_c<locals_tag>),
                hana::make_pair(hana::type_c<locals_tag>, &locals));
        }

        template<typename Context, typename AttributeType, typename ParamsTuple>
        inline auto make_rule_context(
            Context const & context,
            AttributeType & value,
            nope & locals,
            ParamsTuple const & params) noexcept
        {
            return hana::insert(
                hana::insert(
                    hana::erase_key(
                        hana::erase_key(context, hana::type_c<val_tag>),
                        hana::type_c<rule_params_tag>),
                    hana::make_pair(hana::type_c<val_tag>, &value)),
                hana::make_pair(hana::type_c<rule_params_tag>, &params));
        }

        template<typename Context, typename AttributeType>
        inline auto make_rule_context(
            Context const & context,
            AttributeType & value,
            nope & locals,
            nope & params) noexcept
        {
            return hana::insert(
                hana::erase_key(context, hana::type_c<val_tag>),
                hana::make_pair(hana::type_c<val_tag>, &value));
        }

        template<typename Context, typename ParamsTuple>
        inline auto make_rule_context(
            Context const & context,
            nope & value,
            nope & locals,
            ParamsTuple const & params) noexcept
        {
            return hana::insert(
                hana::erase_key(context, hana::type_c<rule_params_tag>),
                hana::make_pair(hana::type_c<rule_params_tag>, &params));
        }

        template<typename Context>
        inline auto make_rule_context(
            Context const & context,
            nope & value,
            nope & locals,
            nope & params) noexcept
        {
            return context;
        }

        template<typename Context>
        inline decltype(auto) _indent(Context const & context)
        {
            return *context[hana::type_c<trace_indent_tag>];
        }

        template<typename Context>
        inline decltype(auto) _callbacks(Context const & context)
        {
            return *context[hana::type_c<callbacks_tag>];
        }

        template<typename Context, typename T>
        inline decltype(auto) get_trie(
            Context const & context, symbol_parser<T> const & symbol_parser)
        {
            using trie_t = text::trie<std::vector<uint32_t>, T>;
            symbol_table_tries_t & symbol_table_tries =
                *context[hana::type_c<symbol_table_tries_tag>];
            any & a = symbol_table_tries[(void *)&symbol_parser];
            trie_t * trie_ptr = nullptr;
            if (a.empty()) {
                a = trie_t{};
                trie_ptr = any_cast<trie_t>(&a);
                for (auto const & e : symbol_parser.initial_elements()) {
                    trie_ptr->insert(text::as_utf32(e.first), e.second);
                }
            } else {
                trie_ptr = any_cast<trie_t>(&a);
            }
            return *trie_ptr;
        }


        // Type traits.

        template<typename T>
        struct is_hana_tuple : std::false_type
        {};

        template<typename... T>
        struct is_hana_tuple<hana::tuple<T...>> : std::true_type
        {};

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

        template<typename Callbacks, typename TagType>
        using overloaded_callback_1 =
            decltype(std::declval<Callbacks>()(hana::type_c<TagType>));
        template<typename Callbacks, typename TagType>
        struct has_overloaded_callback_1
            : is_detected<overloaded_callback_1, Callbacks, TagType>
        {};

        template<typename Callbacks, typename TagType, typename ResultType>
        using overloaded_callback_2 = decltype(std::declval<Callbacks>()(
            hana::type_c<TagType>, std::declval<ResultType>()));
        template<typename Callbacks, typename TagType, typename ResultType>
        struct has_overloaded_callback_2
            : is_detected<overloaded_callback_2, Callbacks, TagType, ResultType>
        {};



        // Metafunctions.

        template<typename Pair>
        struct hana_tuple_to_or_type;

        template<typename... T>
        struct hana_tuple_to_or_type<
            hana::pair<hana::tuple<T...>, std::true_type>>
        {
            using type = std::optional<std::variant<T...>>;
        };

        template<typename... T>
        struct hana_tuple_to_or_type<
            hana::pair<hana::tuple<T...>, std::false_type>>
        {
            using type = std::variant<T...>;
        };

        template<typename T>
        struct hana_tuple_to_or_type<hana::pair<hana::tuple<T>, std::true_type>>
        {
            using type = std::optional<T>;
        };

        template<typename T>
        struct hana_tuple_to_or_type<
            hana::pair<hana::tuple<T>, std::false_type>>
        {
            using type = T;
        };

        template<typename T>
        struct hana_tuple_to_or_type<
            hana::pair<hana::tuple<std::optional<T>>, std::true_type>>
        {
            using type = std::optional<T>;
        };

        template<>
        struct hana_tuple_to_or_type<hana::pair<hana::tuple<>, std::true_type>>
        {
            using type = nope;
        };

        template<>
        struct hana_tuple_to_or_type<hana::pair<hana::tuple<>, std::false_type>>
        {
            using type = nope;
        };

        template<typename T>
        using hana_tuple_to_or_type_t = typename hana_tuple_to_or_type<T>::type;

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
            if (!gen_attrs)
                return;
            if constexpr (
                std::integral<std::ranges::range_value_t<Container>> &&
                std::integral<T> &&
                sizeof(std::ranges::range_value_t<Container>) == 1 &&
                sizeof(T) == 4) {
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
            using container_value_type = std::ranges::range_value_t<Container>;
            using iter_value_type = std::iter_value_t<Iter>;
            if constexpr (
                std::integral<container_value_type> &&
                std::integral<iter_value_type> &&
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
                hana::bool_<UseCallbacks> use_cbs,
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
                hana::bool_<UseCallbacks> use_cbs,
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
            if (!use_skip(f))
                return;
            bool success = true;
            int indent = 0;
            rethrow_error_handler eh;
            nope n;
            symbol_table_tries_t symbol_table_tries;
            auto const context = make_context(
                first, last, success, indent, eh, n, symbol_table_tries);
            while (success) {
                skip_(
                    hana::false_c,
                    first,
                    last,
                    context,
                    skip_skipper{},
                    disable_trace(disable_skip(f)),
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
            if constexpr (std::is_pointer<std::decay_t<R>>::value) {
                return detail::make_char_range(r, text::null_sentinel{});
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
                return c != resolve(context, expected);
            }
        };

        template<typename Context, typename CharType, typename Expected>
        struct unequal_impl<Context, CharType, Expected, true>
        {
            static bool call(Context const &, CharType c, Expected expected)
            {
                using common_t = std::common_type_t<CharType, Expected>;
                return (common_t)c != (common_t)expected;
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
            {
                auto lo = resolve(context, expected.lo_);
                using common_t = std::common_type_t<CharType, decltype(lo)>;
                if ((common_t)c < (common_t)lo)
                    return true;
            }
            {
                auto hi = resolve(context, expected.hi_);
                using common_t = std::common_type_t<CharType, decltype(hi)>;
                if ((common_t)hi < (common_t)c)
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
            hana::bool_<UseCallbacks> use_cbs,
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
            } else if constexpr (std::is_same<attr_t, nope>{}) {
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
            hana::bool_<UseCallbacks> use_cbs,
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
            hana::bool_<UseCallbacks> use_cbs,
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
            hana::bool_<UseCallbacks> use_cbs,
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

        template<typename Parser>
        struct ref_parser
        {
            ref_parser() : parser_(nullptr) {}
            ref_parser(Parser const * parser) : parser_(parser) {}

            template<
                bool UseCallbacks,
                typename Iter,
                typename Sentinel,
                typename Context,
                typename SkipParser>
            auto call(
                hana::bool_<UseCallbacks> use_cbs,
                Iter & first,
                Sentinel last,
                Context const & context,
                SkipParser const & skip,
                detail::flags flags,
                bool & success) const
            {
                assert(parser_);
                return parser_->call(
                    use_cbs, first, last, context, skip, flags, success);
            }

            template<
                bool UseCallbacks,
                typename Iter,
                typename Sentinel,
                typename Context,
                typename SkipParser,
                typename Attribute>
            void call(
                hana::bool_<UseCallbacks> use_cbs,
                Iter & first,
                Sentinel last,
                Context const & context,
                SkipParser const & skip,
                detail::flags flags,
                bool & success,
                Attribute & retval) const
            {
                assert(parser_);
                parser_->call(
                    use_cbs,
                    first,
                    last,
                    context,
                    skip,
                    flags,
                    success,
                    retval);
            }

            Parser const * parser_;
        };



        // API implementations

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
            auto const flags = Debug ? enable_trace(detail::flags::gen_attrs)
                                     : detail::flags::gen_attrs;
            try {
                parser(
                    hana::false_c,
                    first,
                    last,
                    context,
                    detail::null_parser{},
                    flags,
                    success,
                    attr);
                if (Debug)
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
            auto const flags = Debug ? enable_trace(detail::flags::gen_attrs)
                                     : detail::flags::gen_attrs;
            using attr_t = decltype(parser(
                hana::false_c,
                first,
                last,
                context,
                detail::null_parser{},
                flags,
                success));
            try {
                attr_t attr_ = parser(
                    hana::false_c,
                    first,
                    last,
                    context,
                    detail::null_parser{},
                    flags,
                    success);
                if (Debug)
                    final_trace(context, flags, nope{});
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
            auto const flags = Debug ? enable_trace(detail::flags::gen_attrs)
                                     : detail::flags::gen_attrs;
            try {
                parser(
                    hana::true_c,
                    first,
                    last,
                    context,
                    detail::null_parser{},
                    flags,
                    success);
                if (Debug)
                    final_trace(context, flags, nope{});
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
            auto const flags = Debug ? enable_trace(detail::default_flags())
                                     : detail::default_flags();
            detail::skip(first, last, skip, flags);
            try {
                parser(
                    hana::false_c,
                    first,
                    last,
                    context,
                    skip,
                    flags,
                    success,
                    attr);
                detail::skip(first, last, skip, flags);
                if (Debug)
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
            auto const flags = Debug ? enable_trace(detail::default_flags())
                                     : detail::default_flags();
            detail::skip(first, last, skip, flags);
            using attr_t = decltype(parser(
                hana::false_c, first, last, context, skip, flags, success));
            try {
                attr_t attr_ = parser(
                    hana::false_c, first, last, context, skip, flags, success);
                detail::skip(first, last, skip, flags);
                if (Debug)
                    final_trace(context, flags, nope{});
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
            auto const flags = Debug ? enable_trace(detail::default_flags())
                                     : detail::default_flags();
            detail::skip(first, last, skip, flags);
            try {
                parser(
                    hana::false_c, first, last, context, skip, flags, success);
                detail::skip(first, last, skip, flags);
                if (Debug)
                    final_trace(context, flags, nope{});
                return success;
            } catch (parse_error<Iter> const & e) {
                if (error_handler(initial_first, last, e) ==
                    error_handler_result::rethrow) {
                    throw;
                }
                return false;
            }
        }

        inline constexpr auto val_ = tag<val_tag>;
        inline constexpr auto attr_ = tag<attr_tag>;
        inline constexpr auto where_ = tag<where_tag>;
        inline constexpr auto begin_ = tag<begin_tag>;
        inline constexpr auto end_ = tag<end_tag>;
        inline constexpr auto pass_ = tag<pass_tag>;
        inline constexpr auto locals_ = tag<locals_tag>;
        inline constexpr auto params_ = tag<rule_params_tag>;
        inline constexpr auto globals_ = tag<globals_tag>;
        inline constexpr auto error_handler_ = tag<error_handler_tag>;

        template<typename I, typename S>
        text::utf32_view<I, S>
        remove_utf32_terminator(text::utf32_view<I, S> view)
        {
            return view;
        }
        template<typename I>
        text::utf32_view<I> remove_utf32_terminator(text::utf32_view<I> view)
        {
            if (!view.empty() && view.back() == 0)
                return text::utf32_view<I>(view.begin(), std::prev(view.end()));
            return view;
        }
        template<typename R>
        auto as_utf32_no_terminator(R & r)
            -> decltype(detail::remove_utf32_terminator(text::as_utf32(r)))
        {
            return detail::remove_utf32_terminator(text::as_utf32(r));
        }

        template<typename T>
        concept non_unicode_char_range_like = utf8_range_like<T> &&
                                              (!utf8_view<T> && !char8_ptr<T>);

        template<typename R>
        constexpr auto make_input_range(R && r) noexcept
        {
            if constexpr (non_unicode_char_range_like<R>) {
                if constexpr (utf8_pointer<R>) {
                    return parser::make_view(r, text::null_sentinel{});
                } else if constexpr (std::is_array_v<
                                         std::remove_reference_t<R>>) {
                    auto first = std::begin(r);
                    auto last = std::end(r);
                    if (first != last && *std::prev(last) == 0)
                        --last;
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
            if constexpr (std::is_pointer<std::decay_t<R>>::value) {
                return r;
            } else {
                return std::begin(r);
            }
        }

        template<typename R>
        constexpr auto make_view_end(R & r) noexcept
        {
            if constexpr (std::is_pointer<std::decay_t<R>>::value) {
                return text::null_sentinel{};
            } else {
                return std::end(r);
            }
        }

        template<
            typename Iter1,
            typename Sentinel1,
            typename Iter2,
            typename Sentinel2>
        std::pair<Iter1, Iter2>
        mismatch(Iter1 first1, Sentinel1 last1, Iter2 first2, Sentinel2 last2)
        {
            std::pair<Iter1, Iter2> retval{first1, first2};
            while (retval.first != last1 && retval.second != last2 &&
                   *retval.first == *retval.second) {
                ++retval.first;
                ++retval.second;
            }
            return retval;
        }
    }



    // TODO: Document term of art: semantic action.
    // TODO: Document term of art: topmost parser/rule.
    // TODO: Document term of art: innermost parser/rule.
    // TODO: Document term of art: top-level parse.

    // TODO: Document the convention that a parser's operator() always returns
    // a parser_interface.

    // TODO: Document what a pred/pred_ is (value or invocable), and what any
    // other value is (value or invocable).

    // TODO: Document that the parse always operates on {,signed,unsigned}
    // chars and std::bytes (or any size-1 integral besides char8_t) of
    // unknown encoding or Unicode code points.

    // TODO: Document that using char8_t or as_utf8() when passing to
    // *parse() opts you into Unicode-aware parsing.

    // TODO: Document the conversions that occur when comparing in char_parser
    // (uint32_t's compared to ASCII, etc.).

    // TODO: C++20 concepts.

    // TODO: Are _val() and _attr() redundant?

    /** Returns a reference to the attribute(s) (i.e. return value) of the
        innermost parser; multiple attributes will be stored within a
        `hana::tuple` (TODO: As reference members of the tuple?  Same for
        `_attr()`, `_locals()`, etc.).  You may write to this value in a
        semantic action to control what attribute value(s) the associated
        parser produces.  Returns `nope` if the innermost parser does produce
        an attribute. */
    template<typename Context>
    inline decltype(auto) _val(Context const & context)
    {
        return *context[detail::val_];
    }
    /** Returns a reference to the attribute or attributes already produced by
        the innermost parser; multiple attributes will be stored within a
        `hana::tuple`.  Returns `nope` if the innermost parser does produce an
        attribute. */
    template<typename Context>
    inline decltype(auto) _attr(Context const & context)
    {
        return *context[detail::attr_];
    }
    /** Returns a `view` that describes the matched range of the innermost
        parser. */
    template<typename Context>
    inline decltype(auto) _where(Context const & context)
    {
        return *context[detail::where_];
    }
    /** Returns an iterator to the beginning of the entire sequence being
        parsed.  The effect of calling this within a semantic action
        associated with a skip-parser is undefined */
    template<typename Context>
    inline decltype(auto) _begin(Context const & context)
    {
        return context[detail::begin_];
    }
    /** Returns an iterator to the end of the entire sequence being parsed. */
    template<typename Context>
    inline decltype(auto) _end(Context const & context)
    {
        return context[detail::end_];
    }
    /** Returns a reference to a `bool` that represents the success or failure
        of the innermost parser.  You can assign `false` to this within a
        semantic action to force a parser to fail its parse. */
    template<typename Context>
    inline decltype(auto) _pass(Context const & context)
    {
        return *context[detail::pass_];
    }
    /** Returns a reference to one or more local values that the innermost
        rule is declared to have; multiple values will be stored within a
        `hana::tuple`.  Returns `nope` if there is no innermost rule, or if
        that rule has no locals. */
    template<typename Context>
    inline decltype(auto) _locals(Context const & context)
    {
        return *context[detail::locals_];
    }
    /** Returns a reference to one or more parameters passed to the innermost
        rule `r`, by using `r` as `r.with(param0, param1, ... paramN)`;
        multiple values will be stored within a `hana::tuple`.  Returns `nope`
        if there is no innermost rule, or if that rule was not given any
        parameters. */
    template<typename Context>
    inline decltype(auto) _params(Context const & context)
    {
        return *context[detail::params_];
    }
    /** Returns a reference to the globals object associated with the
        innermost parser.  Returns `nope` if there is no associated globals
        object. */
    template<typename Context>
    inline decltype(auto) _globals(Context const & context)
    {
        return *context[detail::globals_];
    }
    /** Returns a reference to the error handler object associated with the
        innermost parser.  Returns `nope` if there is no associated error
        handler. */
    template<typename Context>
    inline decltype(auto) _error_handler(Context const & context)
    {
        return *context[detail::error_handler_];
    }

    /** Report that the error described in `message` occurred at `location`,
        using the context's error handler. */
    template<typename Iter, typename Context>
    inline void _report_error(
        Context const & context, std::string_view message, Iter location)
    {
        return context[detail::error_handler_]->diagnose(
            diagnostic_kind::error, message, context, location);
    }
    /** Report that the error described in `message` occurred at
        `_where(context).begin()`, using the context's error handler. */
    template<typename Context>
    inline void _report_error(Context const & context, std::string_view message)
    {
        return context[detail::error_handler_]->diagnose(
            diagnostic_kind::error, message, context);
    }
    /** Report that the warning described in `message` occurred at `location`,
        using the context's error handler. */
    template<typename Iter, typename Context>
    inline void _report_warning(
        Context const & context, std::string_view message, Iter location)
    {
        return context[detail::error_handler_]->diagnose(
            diagnostic_kind::warning, message, context, location);
    }
    /** Report that the warning described in `message` occurred at
        `_where(context).begin()`, using the context's error handler. */
    template<typename Context>
    inline void
    _report_warning(Context const & context, std::string_view message)
    {
        return context[detail::error_handler_]->diagnose(
            diagnostic_kind::warning, message, context);
    }

    /** An invocable that returns the `I`th parameter to the innermost rule.
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
            hana::bool_<UseCallbacks> use_cbs,
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
            hana::bool_<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = scoped_trace(
                *this,
                first,
                last,
                context,
                in_apply_parser(flags) ? disable_trace(flags) : flags,
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
                    set_in_apply_parser(flags),
                    success,
                    retval);
            } else if constexpr (detail::container<attr_t>) {
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

                for (int64_t end = detail::resolve(context, max_); count != end;
                     ++count) {
                    auto const prev_first = first;
                    // This is only ever used in delimited_parser, which
                    // always has a min=1; we therefore know we're after a
                    // previous element when this executes.
                    if constexpr (!std::is_same<DelimiterParser, nope>{}) {
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
                    if (gen_attrs(flags)) {
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
                    detail::append(retval, std::move(attr), gen_attrs(flags));
                }

                for (int64_t end = detail::resolve(context, max_); count != end;
                     ++count) {
                    auto const prev_first = first;
                    if constexpr (!std::is_same<DelimiterParser, nope>{}) {
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
                    if (gen_attrs(flags)) {
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
                    detail::append(retval, std::move(attr), gen_attrs(flags));
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
            hana::bool_<UseCallbacks> use_cbs,
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
            hana::bool_<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = scoped_trace(*this, first, last, context, flags, retval);

            detail::skip(first, last, skip, flags);

            if (!gen_attrs(flags)) {
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
                    hana::bool_c<UseCallbacks>,
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
                    hana::bool_c<UseCallbacks>,
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
            hana::bool_<UseCallbacks> use_cbs,
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
            using all_types = decltype(hana::transform(parsers_, use_parser));

            // Same as above, wrapped in hana::basic_type.
            using all_types_wrapped =
                decltype(hana::transform(all_types{}, hana::make_type));

            // Returns a hana::pair<> containing two things: 1) A tuple of
            // only the unique wrapped types from above, without nopes; this
            // may be empty. 2) std::true_type or std::false_type indicating
            // whether nopes were found; if so, the final result is an
            // optional.
            auto append_unique = [](auto result, auto x) {
                using x_type = typename decltype(x)::type;
                if constexpr (std::is_same<x_type, nope>{}) {
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
            hana::bool_<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = scoped_trace(*this, first, last, context, flags, retval);

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
                if (gen_attrs(flags)) {
                    use_parser(parser, retval);
                    if (!success)
                        detail::assign(retval, Attribute());
                } else {
                    use_parser(parser);
                }
                if (success)
                    done = true;
            };
            hana::for_each(parsers_, try_parser);

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
                    hana::bool_c<UseCallbacks>,
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

                if constexpr (std::is_same<x_type, nope>{}) {
                    // T >> nope -> T
                    return hana::make_pair(
                        result,
                        hana::append(indices, hana::size(result) - one));
                } else if constexpr (
                    std::is_same<result_back_type, x_type>{} ||
                    std::is_same<
                        result_back_type,
                        unwrapped_optional_x_type>{}) {
                    if constexpr (detail::container<result_back_type>) {
                        // C<T> >> C<T> -> C<T>
                        return hana::make_pair(
                            result,
                            hana::append(indices, hana::size(result) - one));
                    } else {
                        // T >> T -> vector<T>
                        return hana::make_pair(
                            hana::append(
                                hana::drop_back(result),
                                hana::type_c<std::vector<result_back_type>>),
                            hana::append(indices, hana::size(result) - one));
                    }
                } else if constexpr (
                    detail::
                        container_and_value_type<result_back_type, x_type> ||
                    detail::container_and_value_type<
                        result_back_type,
                        unwrapped_optional_x_type>) {
                    // C<T> >> T -> C<T>
                    // C<T> >> optional<T> -> C<T>
                    return hana::make_pair(
                        result,
                        hana::append(indices, hana::size(result) - one));
                } else if constexpr (
                    detail::
                        container_and_value_type<x_type, result_back_type> ||
                    detail::container_and_value_type<
                        x_type,
                        unwrapped_optional_result_back_type>) {
                    // T >> C<T> -> C<T>
                    // optional<T> >> C<T> -> C<T>
                    return hana::make_pair(
                        hana::append(hana::drop_back(result), x),
                        hana::append(indices, hana::size(result) - one));
                } else if constexpr (std::is_same<result_back_type, nope>{}) {
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
        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser>
        auto make_temp_result(
            hana::bool_<UseCallbacks> use_cbs,
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

#endif

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser>
        auto call(
            hana::bool_<UseCallbacks> use_cbs,
            Iter & first_,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            Iter first = first_;

            std::decay_t<decltype(hana::first(make_temp_result(
                use_cbs, first, last, context, skip, flags, success)))>
                retval;

            auto _ = scoped_trace(
                *this,
                first_,
                last,
                context,
                in_apply_parser(flags) ? disable_trace(flags) : flags,
                retval);

            std::decay_t<decltype(hana::second(make_temp_result(
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
            if constexpr (hana::size(retval) == hana::size_c<1>) {
                using namespace hana::literals;
                return retval[0_c];
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
            hana::bool_<UseCallbacks> use_cbs,
            Iter & first_,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = scoped_trace(
                *this,
                first_,
                last,
                context,
                in_apply_parser(flags) ? disable_trace(flags) : flags,
                retval);

            Iter first = first_;

            std::decay_t<decltype(hana::second(make_temp_result(
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
                    set_in_apply_parser(flags),
                    success,
                    retval);
            } else if constexpr (detail::is_optional<Attribute>{}) {
                typename Attribute::value_type attr;
                call(
                    use_cbs, first_, last, context, skip, flags, success, attr);
                if (success)
                    detail::assign(retval, attr);
            } else if constexpr (detail::is_hana_tuple<Attribute>{}) {
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

                if (!success || !gen_attrs(flags))
                    detail::assign(retval, Attribute());
            } else {
                // call_impl requires a tuple, so we must wrap this scalar.
                hana::tuple<Attribute> temp_retval;
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

                if (success && gen_attrs(flags))
                    detail::assign(retval, hana::front(temp_retval));
            }

            if (success)
                first_ = first;
        }

#ifndef BOOST_PARSER_DOXYGEN

        // Invokes each parser, placing the resulting values (if any) into
        // retval, using the index mapping in indices.  The case of a tulple
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
            hana::bool_<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval,
            Indices const & indices) const
        {
            static_assert(detail::is_hana_tuple<Attribute>{}, "");

            auto use_parser = [use_cbs,
                               &first,
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
                    parser.call(
                        use_cbs, first, last, context, skip, flags, success);
                    if (!success && !can_backtrack) {
                        std::stringstream oss;
                        detail::parser_name(context, parser, oss);
                        throw parse_error<Iter>(first, oss.str());
                    }
                    return;
                }

                auto & out = retval[parser_index_and_backtrack[1_c]];

                using attr_t = decltype(parser.call(
                    use_cbs, first, last, context, skip, flags, success));
                constexpr bool out_container =
                    detail::container<std::decay_t<decltype(out)>>;
                constexpr bool attr_container = detail::container<attr_t>;

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
                            detail::parser_name(context, parser, oss);
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
                            detail::parser_name(context, parser, oss);
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
                hana::zip(parsers_, indices, backtracking{});
            hana::for_each(parsers_and_indices, use_parser);
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
        nope call(
            hana::bool_<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            nope retval;
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
            hana::bool_<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = scoped_trace(*this, first, last, context, flags, retval);

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
                // Replace the context's current attribute with attr, and add
                // where to the context.
                auto const action_context = hana::insert(
                    hana::insert(
                        hana::erase_key(context, detail::attr_),
                        hana::make_pair(detail::attr_, &attr)),
                    hana::make_pair(detail::where_, &where));
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
        nope call(
            hana::bool_<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            auto _ = scoped_trace(
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
            hana::bool_<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = scoped_trace(*this, first, last, context, flags, retval);

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
            hana::bool_<UseCallbacks> use_cbs,
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
            hana::bool_<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = scoped_trace(*this, first, last, context, flags, retval);

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
            hana::bool_<UseCallbacks> use_cbs,
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
            hana::bool_<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = scoped_trace(*this, first, last, context, flags, retval);

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
            hana::bool_<UseCallbacks> use_cbs,
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
            hana::bool_<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser_ const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            if constexpr (std::is_same<SkipParser, nope>{}) {
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
        nope call(
            hana::bool_<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            nope retval;
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
            hana::bool_<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = scoped_trace(*this, first, last, context, flags, retval);

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
        text::optional_ref<T>
        find(Context const & context, std::string_view str) const
        {
            text::trie<std::vector<uint32_t>, T> & trie_ =
                detail::get_trie(context, ref());
            return trie_[text::as_utf32(str)];
        }

        /** Inserts an entry consisting of a UTF-8 string `str` to match, and
            an associtated attribute `x`, to the copy of the symbol table
            inside the parse context `context`. */
        template<typename Context>
        void insert(Context const & context, std::string_view str, T && x) const
        {
            text::trie<std::vector<uint32_t>, T> & trie_ =
                detail::get_trie(context, ref());
            trie_.insert(text::as_utf32(str), std::move(x));
        }

        /** Erases the entry whose UTF-8 match string is `str` from the copy
            of the symbol table inside the parse context `context`. */
        template<typename Context>
        void erase(Context const & context, std::string_view str) const
        {
            text::trie<std::vector<uint32_t>, T> & trie_ =
                detail::get_trie(context, ref());
            trie_.erase(text::as_utf32(str));
        }

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser>
        T call(
            hana::bool_<UseCallbacks> use_cbs,
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
            hana::bool_<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = scoped_trace(*this, first, last, context, flags, retval);

            text::trie<std::vector<uint32_t>, T> const & trie_ =
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
        typename TagType,
        typename Attribute,
        typename LocalState,
        typename ParamsTuple>
    struct rule_parser<false, TagType, Attribute, LocalState, ParamsTuple>
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
            hana::bool_<UseCallbacks> use_cbs,
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
                make_rule_context(context, retval, locals, params);
            auto _ =
                scoped_trace(*this, first, last, rule_context, flags, retval);
            tag_type * const tag_ptr = nullptr;
            parse_rule(
                tag_ptr,
                hana::false_c,
                first,
                last,
                rule_context,
                skip,
                flags,
                success,
                retval);
            if (!success)
                detail::assign(retval, attr_type());
            return retval;
        }

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser,
            typename Attribute_>
        void call(
            hana::bool_<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute_ & retval) const
        {
            attr_type attr =
                call(use_cbs, first, last, context, skip, flags, success);
            if (success)
                detail::assign(retval, attr);
        }

        std::string_view name_;
        ParamsTuple params_;
    };

    template<
        typename TagType,
        typename Attribute,
        typename LocalState,
        typename ParamsTuple>
    struct rule_parser<true, TagType, Attribute, LocalState, ParamsTuple>
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
            hana::bool_<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            if constexpr (!UseCallbacks) {
                rule_parser<false, TagType, Attribute, LocalState, ParamsTuple>
                    without_callbacks{name_, params_};
                return without_callbacks.call(
                    use_cbs, first, last, context, skip, flags, success);
            } else {
                attr_type retval{};
                locals_type locals = detail::make_locals<locals_type>(context);
                auto params = detail::resolve_rule_params(context, params_);
                auto const rule_context =
                    make_rule_context(context, retval, locals, params);
                auto _ = scoped_trace(
                    *this, first, last, rule_context, flags, retval);
                tag_type * const tag_ptr = nullptr;
                parse_rule(
                    tag_ptr,
                    hana::true_c,
                    first,
                    last,
                    rule_context,
                    skip,
                    flags,
                    success,
                    retval);

                if (!success)
                    return {};

                auto const & callbacks = _callbacks(context);

                if constexpr (std::is_same<attr_type, nope>{}) {
                    if constexpr (detail::has_overloaded_callback_1<
                                      decltype((callbacks)),
                                      tag_type>{}) {
                        callbacks(hana::type_c<tag_type>);
                    } else {
                        // For rules without attributes, Callbacks must be a
                        // struct with overloads of the form
                        // void(hana::basic_type<tag_type>) (the case above),
                        // or Callbacks mut be a hana::map that contains a
                        // callback of the form void() for each associated
                        // tag_type (this case).  If you're seeing an error
                        // here, you probably have not met this contract.
                        callbacks[hana::type_c<tag_type>]();
                    }
                } else {
                    if constexpr (detail::has_overloaded_callback_2<
                                      decltype((callbacks)),
                                      tag_type,
                                      decltype(std::move(retval))>{}) {
                        callbacks(hana::type_c<tag_type>, std::move(retval));
                    } else {
                        // For rules with attributes, Callbacks must be a
                        // struct with overloads of the form
                        // void(hana::basic_type<tag_type>, attr_type &) (the
                        // case above), or Callbacks mut be a hana::map that
                        // contains a callback of the form void(attr_type &)
                        // for each associated tag_type (this case).  If
                        // you're seeing an error here, you probably have not
                        // met this contract.
                        callbacks[hana::type_c<tag_type>](std::move(retval));
                    }
                }

                return {};
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
            hana::bool_<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute_ & attr) const
        {
            if (!UseCallbacks) {
                rule_parser<false, TagType, Attribute, LocalState, ParamsTuple>
                    without_callbacks{name_, params_};
                without_callbacks.call(
                    use_cbs, first, last, context, skip, flags, success, attr);
            } else {
                call(use_cbs, first, last, context, skip, flags, success);
            }
        }

        std::string_view name_;
        ParamsTuple params_;
    };


    // Parser interface.

    /** A wrapper for parsers that provides the operations that must be
        supported by all parsers (e.g. `operator>>()`).  `GlobalState` is an
        optional state object that can be accessed within semantic actions
        with a call to `_globals()`.  This global state object is ignored for
        all but the topmost parser; the topmost global state object is
        available in the semantic actions of all nested parsers.
        `ErrorHandler` is the type of the error handler to be used on parse
        failure.  This handler is ignored on all but the topmost parser; the
        topmost parser's error handler is used for all errors encountered
        during parsing. */
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
        template<typename parser_type_2>
        constexpr auto
        operator>>(parser_interface<parser_type_2> rhs) const noexcept
        {
            if constexpr (detail::is_seq_p<parser_type>{}) {
                return parser_.template append<true>(rhs);
            } else {
                using parser_t = seq_parser<
                    hana::tuple<parser_type, parser_type_2>,
                    hana::tuple<hana::true_, hana::true_>>;
                return parser::parser_interface{
                    parser_t{hana::tuple<parser_type, parser_type_2>{
                        parser_, rhs.parser_}}};
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
        template<parsable_range_like R>
        constexpr auto operator>>(R && range) const noexcept;

        /** Returns a `parser_interface` containing a parser equivalent to a
            `seq_parser` containing `parser_` followed by `rhs.parser_`.  No
            back-tracking is allowed after `parser_` succeeds; if
            `rhs.parser_` fails after `parser_` succeeds, the top-level parse
            fails. */
        template<typename parser_type_2>
        constexpr auto
        operator>(parser_interface<parser_type_2> rhs) const noexcept
        {
            if constexpr (detail::is_seq_p<parser_type>{}) {
                return parser_.template append<false>(rhs);
            } else {
                using parser_t = seq_parser<
                    hana::tuple<parser_type, parser_type_2>,
                    hana::tuple<hana::true_, hana::false_>>;
                return parser::parser_interface{
                    parser_t{hana::tuple<parser_type, parser_type_2>{
                        parser_, rhs.parser_}}};
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
        template<parsable_range_like R>
        constexpr auto operator>(R && range) const noexcept;

        /** Returns a `parser_interface` containing a parser equivalent to an
            `or_parser` containing `parser_` followed by `rhs.parser_`. */
        template<typename parser_type_2>
        constexpr auto
        operator|(parser_interface<parser_type_2> rhs) const noexcept
        {
            if constexpr (detail::is_or_p<parser_type>{}) {
                return parser_.append(rhs);
            } else {
                return parser::parser_interface{
                    or_parser<hana::tuple<parser_type, parser_type_2>>{
                        hana::tuple<parser_type, parser_type_2>{
                            parser_, rhs.parser_}}};
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
        template<parsable_range_like R>
        constexpr auto operator|(R && range) const noexcept;

        /** Returns a `parser_interface` containing a parser equivalent to
            `!rhs >> *this`. */
        template<typename parser_type_2>
        constexpr auto
        operator-(parser_interface<parser_type_2> rhs) const noexcept
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
        template<parsable_range_like R>
        constexpr auto operator-(R && range) const noexcept;

        /** Returns a `parser_interface` containing a parser equivalent to an
           `delimited_seq_parser` containing `parser_` and `rhs.parser_`. */
        template<typename parser_type_2>
        constexpr auto
        operator%(parser_interface<parser_type_2> rhs) const noexcept
        {
            return parser::parser_interface{
                delimited_seq_parser<parser_type, parser_type_2>(
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
        template<parsable_range_like R>
        constexpr auto operator%(R && range) const noexcept;

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

        /** Applies `parser_`, returning the parsed attribute, if any, unless
            the attribute is reported via callback. */
        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParserType>
        auto operator()(
            hana::bool_<UseCallbacks> use_cbs,
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
            hana::bool_<UseCallbacks> use_cbs,
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
    };


    /** Returns a `parser_interface` with the same parser and error handler,
        with `globals` added.  The resut of passing any non-top-level parser
        for the `parser` argument is undefined. */
    template<typename Parser, typename GlobalState, typename ErrorHandler>
    auto with_globals(
        parser_interface<Parser, nope, ErrorHandler> const & parser,
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
        text::optional_ref<T>
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

    using no_attribute = nope;
    using no_local_state = nope;
    using no_params = nope;

    /** A type used to declare named parsing rules.  The `TagType` template
        parameter is used to associate a particular `rule` with the
        `rule_parser` used during parsing. */
    template<
        typename TagType,
        typename Attribute = no_attribute,
        typename LocalState = no_local_state,
        typename ParamsTuple = no_params>
    struct rule
        : parser_interface<
              rule_parser<false, TagType, Attribute, LocalState, ParamsTuple>>
    {
        constexpr rule(char const * name) { this->parser_.name_ = name; }

        template<typename... T>
        constexpr auto with(T &&... x) const
        {
            static_assert(
                std::is_same<ParamsTuple, nope>{},
                "If you're seeing this, you tried to chain calls on a rule, "
                "like 'rule(foo)(bar)'.  Quit it!'");
            using params_tuple_type =
                decltype(hana::make_tuple(static_cast<T &&>(x)...));
            using rule_parser_type = rule_parser<
                false,
                TagType,
                Attribute,
                LocalState,
                params_tuple_type>;
            return parser_interface{rule_parser_type{
                this->parser_.name_,
                hana::make_tuple(static_cast<T &&>(x)...)}};
        }
    };

    /** A type used to declare named parsing rules that support reporting of
        attributes via callback.  The `TagType` template parameter is used to
        associate a particular `rule` with the `rule_parser` used during
        parsing. */
    template<
        typename TagType,
        typename Attribute = no_attribute,
        typename LocalState = no_local_state,
        typename ParamsTuple = no_params>
    struct callback_rule
        : parser_interface<
              rule_parser<true, TagType, Attribute, LocalState, ParamsTuple>>
    {
        constexpr callback_rule(char const * name)
        {
            this->parser_.name_ = name;
        }

        template<typename... T>
        constexpr auto with(T &&... x) const
        {
            static_assert(
                std::is_same<ParamsTuple, nope>{},
                "If you're seeing this, you tried to chain calls on a "
                "callback_rule, like 'rule(foo)(bar)'.  Quit it!'");
            using params_tuple_type =
                decltype(hana::make_tuple(static_cast<T &&>(x)...));
            using rule_parser_type = rule_parser<
                true,
                TagType,
                Attribute,
                LocalState,
                params_tuple_type>;
            return parser_interface{rule_parser_type{
                this->parser_.name_,
                hana::make_tuple(static_cast<T &&>(x)...)}};
        }
    };

#ifndef BOOST_PARSER_DOXYGEN

#define BOOST_PARSER_DEFINE_IMPL(r, data, name_)                               \
    template<                                                                  \
        bool UseCallbacks,                                                     \
        typename Iter,                                                         \
        typename Sentinel,                                                     \
        typename Context,                                                      \
        typename SkipParser>                                                   \
    auto parse_rule(                                                           \
        decltype(name_)::parser_type::tag_type *,                              \
        boost::hana::bool_<UseCallbacks> use_cbs,                              \
        Iter & first,                                                          \
        Sentinel last,                                                         \
        Context const & context,                                               \
        SkipParser const & skip,                                               \
        boost::parser::detail::flags flags,                                    \
        bool & success)                                                        \
    {                                                                          \
        auto const & parser = BOOST_PP_CAT(name_, _def);                       \
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
        boost::hana::bool_<UseCallbacks> use_cbs,                              \
        Iter & first,                                                          \
        Sentinel last,                                                         \
        Context const & context,                                               \
        SkipParser const & skip,                                               \
        boost::parser::detail::flags flags,                                    \
        bool & success,                                                        \
        Attribute & retval)                                                    \
    {                                                                          \
        auto const & parser = BOOST_PP_CAT(name_, _def);                       \
        using attr_t = decltype(                                               \
            parser(use_cbs, first, last, context, skip, flags, success));      \
        if constexpr (std::is_same<attr_t, boost::parser::nope>{})             \
            parser(use_cbs, first, last, context, skip, flags, success);       \
        else                                                                   \
            parser(                                                            \
                use_cbs, first, last, context, skip, flags, success, retval);  \
    }

#endif

    /** For each given token `t`, defines a pair of `parse_rule()` overloads,
        used internally within Boost.Parser.  Each such pair implements the
        parsing behavior rule `t`, using the parser `t_def`. */
#define BOOST_PARSER_DEFINE_RULES(...)                                         \
    BOOST_PP_SEQ_FOR_EACH(                                                     \
        BOOST_PARSER_DEFINE_IMPL, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))


#ifndef BOOST_PARSER_DOXYGEN

    template<typename ParserTuple>
    template<typename Parser>
    constexpr auto or_parser<ParserTuple>::prepend(
        parser_interface<Parser> parser) const noexcept
    {
        return parser_interface{
            or_parser<decltype(hana::prepend(parsers_, parser.parser_))>{
                hana::prepend(parsers_, parser.parser_)}};
    }

    template<typename ParserTuple>
    template<typename Parser>
    constexpr auto or_parser<ParserTuple>::append(
        parser_interface<Parser> parser) const noexcept
    {
        return parser_interface{
            or_parser<decltype(hana::append(parsers_, parser.parser_))>{
                hana::append(parsers_, parser.parser_)}};
    }

    template<typename ParserTuple, typename BacktrackingTuple>
    template<bool AllowBacktracking, typename Parser>
    constexpr auto seq_parser<ParserTuple, BacktrackingTuple>::prepend(
        parser_interface<Parser> parser) const noexcept
    {
        using backtracking = decltype(hana::prepend(
            hana::prepend(
                hana::drop_front(BacktrackingTuple{}),
                hana::bool_c<AllowBacktracking>),
            hana::true_c));
        using parser_t = seq_parser<
            decltype(hana::prepend(parsers_, parser.parser_)),
            backtracking>;
        return parser_interface{
            parser_t{hana::prepend(parsers_, parser.parser_)}};
    }

    template<typename ParserTuple, typename BacktrackingTuple>
    template<bool AllowBacktracking, typename Parser>
    constexpr auto seq_parser<ParserTuple, BacktrackingTuple>::append(
        parser_interface<Parser> parser) const noexcept
    {
        using backtracking = decltype(
            hana::append(BacktrackingTuple{}, hana::bool_c<AllowBacktracking>));
        using parser_t = seq_parser<
            decltype(hana::append(parsers_, parser.parser_)),
            backtracking>;
        return parser_interface{
            parser_t{hana::append(parsers_, parser.parser_)}};
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

    /** The omit directive, whose `operator[]` returns an
        `parser_interface<omit_parser<P>>` from a given parser of type
        `parser_interface<P>`. */
    inline constexpr directive<omit_parser> omit;

    /** The raw directive, whose `operator[]` returns an
        `parser_interface<raw_parser<P>>` from a given parser of type
        `parser_interface<P>`. */
    inline constexpr directive<raw_parser> raw;

    /** The lexeme directive, whose `operator[]` returns an
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
                repeat_parser<Parser2, nope, MinType, MaxType>;
            return parser_interface{
                repeat_parser_type{rhs.parser_, min_, max_}};
        }

        MinType min_;
        MaxType max_;
    };

    /** Returns a `repeat_directive` that repeats exactly `n` times, and whose
        `operator[]` returns an `parser_interface<omit_parser<P>>` from a
        given parser of type `parser_interface<P>`. */
    template<typename T>
    constexpr repeat_directive<T, T> repeat(T n) noexcept
    {
        return repeat_directive<T, T>{n, n};
    }

    /** Returns a `repeat_directive` that repeats `[min_, max_]` times, and
        whose `operator[]` returns an `parser_interface<omit_parser<P>>` from
        a given parser of type `parser_interface<P>`. */
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
    template<typename SkipParser = nope>
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
        constexpr auto operator()(SkipParser2 skip_parser) const noexcept
        {
            static_assert(
                std::is_same<SkipParser, nope>{},
                "If you're seeing this, you tried to chain calls on skip, "
                "like 'skip(foo)(bar)'.  Quit it!'");
            return skip_directive<SkipParser2>{skip_parser};
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
        nope call(
            hana::bool_<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const noexcept
        {
            auto _ = scoped_trace(
                *this, first, last, context, flags, detail::global_nope);
            view const where(first, first);
            auto const predicate_context =
                hana::insert(context, hana::make_pair(detail::where_, &where));
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
            hana::bool_<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = scoped_trace(*this, first, last, context, flags, retval);
            view const where(first, first);
            auto const predicate_context =
                hana::insert(context, hana::make_pair(detail::where_, &where));
            success = pred_(predicate_context);
        }

        /** Returns a `parser_interface` containing an `eps_parser` that will
            fail if `pred` evaluates to false. */
        template<typename Predicate2>
        constexpr auto operator()(Predicate2 pred) const noexcept
        {
            static_assert(
                std::is_same<Predicate, nope>{},
                "If you're seeing this, you tried to chain calls on eps, "
                "like 'eps(foo)(bar)'.  Quit it!'");
            return parser_interface{eps_parser<Predicate2>{std::move(pred)}};
        }

        Predicate pred_;
    };

    /** The epsilon parser.  This matches anything, and consumes no input.  If
        used with an optional predicate, like `eps(pred)`, it matches iff
        `pred(ctx)` evaluates to true, where `ctx` is the parser context. */
    inline constexpr parser_interface<eps_parser<nope>> eps;

    struct eoi_parser
    {
        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser>
        nope call(
            hana::bool_<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
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
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser,
            typename Attribute>
        void call(
            hana::bool_<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
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
            hana::bool_<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const &,
            detail::flags flags,
            bool &) const
        {
            auto _ = scoped_trace(
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
            hana::bool_<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute_ & retval) const
        {
            auto _ = scoped_trace(*this, first, last, context, flags, retval);
            if (gen_attrs(flags))
                detail::assign_copy(retval, detail::resolve(context, attr_));
        }

        Attribute attr_;
    };

    /** Returns an `attr_parser` which matches anything, and consumes no
        input, and which produces `a` as its attribute. */
    template<typename Attribute>
    inline constexpr auto attr(Attribute a) noexcept
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
            std::is_same<AttributeType, void>{},
            std::decay_t<T>,
            AttributeType>;

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser>
        auto call(
            hana::bool_<UseCallbacks> use_cbs,
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
            hana::bool_<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
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
        template<typename T>
        // TODO: SFINAE version would require not-range-like constraint.
        constexpr auto operator()(T x) const noexcept
        {
            static_assert(
                std::is_same<Expected, nope>{},
                "If you're seeing this, you tried to chain calls on char_, "
                "like 'char_('a')('b')'.  Quit it!'");
            return parser_interface{
                char_parser<T, AttributeType>{std::move(x)}};
        }

        /** Returns a `parser_interface` containing a `char_parser` that
            matches any value in `[lo, hi)`. */
        template<typename LoType, typename HiType>
        constexpr auto operator()(LoType lo, HiType hi) const noexcept
        {
            static_assert(
                std::is_same<Expected, nope>{},
                "If you're seeing this, you tried to chain calls on char_, "
                "like 'char_('a', 'b')('c', 'd')'.  Quit it!'");
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
        template<parsable_range_like R>
        constexpr auto operator()(R const & r) const noexcept
        {
            static_assert(
                std::is_same<Expected, nope>{},
                "If you're seeing this, you tried to chain calls on char_, "
                "like 'char_(char-set)(char-set)'.  Quit it!'");
            auto range = detail::make_char_range(r);
            using char_range_t = decltype(range);
            using char_parser_t = char_parser<char_range_t, AttributeType>;
            return parser_interface(char_parser_t(range));
        }

        Expected expected_;
    };

    /** The literal code point parser.  The produced attribute is the type of
        the matched code point.  This parser can be used to create code point
        parsers that match one or more specific code point values, by calling
        it with: a single value comparable to a code point; a set of code
        point values in a string; a half-open range of code point values `[lo,
        hi)`, or a set of code point values passed as a range. */
    inline constexpr parser_interface<char_parser<nope>> char_;

    /** The literal code point parser.  It produces a 32-bit unsigned integer
        attribute.  This parser can be used to create code point parsers that
        match one or more specific code point values, by calling it with: a
        single value comparable to a code point; a set of code point values in
        a string; a half-open range of code point values `[lo, hi)`, or a set
        of code point values passed as a range. */
    inline constexpr parser_interface<char_parser<nope, uint32_t>> cp;

    /** The literal code unit parser.  It produces a `char` attribute.  This
        parser can be used to create code unit parsers that match one or more
        specific code unit values, by calling it with: a single value
        comparable to a code unit; a set of code unit values in a string; a
        half-open range of code unit values `[lo, hi)`, or a set of code unit
        values passed as a range. */
    inline constexpr parser_interface<char_parser<nope, char>> cu;

    /** Returns a literal code point parser that produces no attribute. */
    inline constexpr auto lit(char c) noexcept { return omit[char_(c)]; }

    /** Returns a literal code point parser that produces no attribute. */
    inline constexpr auto lit(char32_t c) noexcept { return omit[char_(c)]; }

    template<typename StrIter, typename StrSentinel>
    struct string_parser
    {
        constexpr string_parser() : expected_first_(), expected_last_() {}
        template<parsable_range_like R>
        constexpr string_parser(R && range) :
            expected_first_(detail::make_view_begin(range)),
            expected_last_(detail::make_view_end(range))
        {}

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser>
        std::string call(
            hana::bool_<UseCallbacks> use_cbs,
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
            hana::bool_<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
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

            if constexpr (sizeof(*first) == 4) {
                auto const cps =
                    text::as_utf32(expected_first_, expected_last_);
                auto const mismatch =
                    detail::mismatch(first, last, cps.begin(), cps.end());
                if (mismatch.second != cps.end()) {
                    success = false;
                    return;
                }

                detail::append(retval, first, mismatch.first, gen_attrs(flags));

                first = mismatch.first;
            } else {
                auto const mismatch = detail::mismatch(
                    first, last, expected_first_, expected_last_);
                if (mismatch.second != expected_last_) {
                    success = false;
                    return;
                }

                detail::append(retval, first, mismatch.first, gen_attrs(flags));

                first = mismatch.first;
            }
        }

        StrIter expected_first_;
        StrSentinel expected_last_;
    };

    template<parsable_range_like R>
    string_parser(R range) -> string_parser<
        decltype(detail::make_view_begin(range)),
        decltype(detail::make_view_end(range))>;

    /** Returns a parser that matches `str` that produces the matched string
        as its attribute. */
    template<parsable_range_like R>
    constexpr auto string(R && str) noexcept
    {
        return parser_interface{string_parser(str)};
    }

    /** Returns a parser that matches `str` that produces no attribute. */
    template<parsable_range_like R>
    constexpr auto lit(R && str) noexcept
    {
        return omit[string(str)];
    }

    struct eol_parser
    {
        constexpr eol_parser() {}

        template<
            bool UseCallbacks,
            typename Iter,
            typename Sentinel,
            typename Context,
            typename SkipParser>
        nope call(
            hana::bool_<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            nope nope;
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
            hana::bool_<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
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

    /** The end-of-line parser.  This matches "\r\n", or any one of the line
        break code points from the Unicode Line Break Algorithm, described in
        https://unicode.org/reports/tr14.  Produces no attribute. */
    inline constexpr parser_interface<eol_parser> eol;

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
            hana::bool_<UseCallbacks> use_cbs,
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
            hana::bool_<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = scoped_trace(*this, first, last, context, flags, retval);

            char const t[] = "true";
            if (std::mismatch(t, t + 4, first, last).first == t + 4) {
                std::advance(first, 4);
                detail::assign(retval, true);
                return;
            }
            char const f[] = "false";
            if (std::mismatch(f, f + 5, first, last).first == f + 5) {
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
            hana::bool_<UseCallbacks> use_cbs,
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
            hana::bool_<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = scoped_trace(*this, first, last, context, flags, retval);
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
            static_assert(
                std::is_same<Expected, nope>{},
                "If you're seeing this, you tried to chain calls on this "
                "parser, like 'uint_(2)(3)'.  Quit it!'");
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
            hana::bool_<UseCallbacks> use_cbs,
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
            hana::bool_<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = scoped_trace(*this, first, last, context, flags, retval);
            using extract =
                detail_spirit_x3::extract_int<T, Radix, MinDigits, MaxDigits>;
            T attr = 0;
            success = extract::call(first, last, attr);
            if (attr != detail::resolve(context, expected_))
                success = false;
            if (success)
                detail::assign(retval, attr);
        }

        /** Returns a `parser_interface` containing an `int_parser` that
            matches the exact value `expected`. */
        template<typename Expected2>
        constexpr auto operator()(Expected2 expected) const noexcept
        {
            static_assert(
                std::is_same<Expected, nope>{},
                "If you're seeing this, you tried to chain calls on this "
                "parser, like 'int_(2)(3)'.  Quit it!'");
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
            hana::bool_<UseCallbacks> use_cbs,
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
            hana::bool_<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            auto _ = scoped_trace(*this, first, last, context, flags, retval);
            spirit::x3::real_policies<T> policies;
            using extract =
                detail_spirit_x3::extract_real<T, spirit::x3::real_policies<T>>;
            T attr = 0;
            if (extract::parse(first, last, attr, policies))
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
            hana::bool_<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success) const
        {
            static_assert(
                !std::is_same<OrParser, nope>{},
                "It looks like you tried to write switch_(val).  You need at "
                "least one alternative, like: switch_(val)(value_1, "
                "parser_1)(value_2, parser_2)...");
            using attr_t = decltype(or_parser_.call(
                use_cbs, first, last, context, skip, flags, success));
            attr_t attr{};
            auto _ = scoped_trace(*this, first, last, context, flags, attr);
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
            hana::bool_<UseCallbacks> use_cbs,
            Iter & first,
            Sentinel last,
            Context const & context,
            SkipParser const & skip,
            detail::flags flags,
            bool & success,
            Attribute & retval) const
        {
            static_assert(
                !std::is_same<OrParser, nope>{},
                "It looks like you tried to write switch_(val).  You need at "
                "least one alternative, like: switch_(val)(value_1, "
                "parser_1)(value_2, parser_2)...");
            auto _ = scoped_trace(*this, first, last, context, flags, retval);
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
        make_or_parser(nope, parser_interface<Parser> parser)
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
        if constexpr (detail::is_seq_p<Parser>{}) {
            return parser_.template append<true>(lit(rhs));
        } else {
            return *this >> lit(rhs);
        }
    }

    template<typename Parser, typename GlobalState, typename ErrorHandler>
    constexpr auto
    parser_interface<Parser, GlobalState, ErrorHandler>::operator>>(
        char32_t rhs) const noexcept
    {
        if constexpr (detail::is_seq_p<Parser>{}) {
            return parser_.template append<true>(lit(rhs));
        } else {
            return *this >> lit(rhs);
        }
    }

    template<typename Parser, typename GlobalState, typename ErrorHandler>
    template<parsable_range_like R>
    constexpr auto
    parser_interface<Parser, GlobalState, ErrorHandler>::operator>>(
        R && range) const noexcept
    {
        if constexpr (detail::is_seq_p<Parser>{}) {
            return parser_.template append<true>(lit(range));
        } else {
            return *this >> lit(range);
        }
    }

#endif

    /** Returns a parser equivalent to `lit(c) >> rhs`. */
    template<typename Parser>
    constexpr auto operator>>(char c, parser_interface<Parser> rhs) noexcept
    {
        if constexpr (detail::is_seq_p<Parser>{}) {
            return rhs.parser_.template prepend<true>(lit(c));
        } else {
            return lit(c) >> rhs;
        }
    }

    /** Returns a parser equivalent to `lit(c) >> rhs`. */
    template<typename Parser>
    constexpr auto operator>>(char32_t c, parser_interface<Parser> rhs) noexcept
    {
        if constexpr (detail::is_seq_p<Parser>{}) {
            return rhs.parser_.template prepend<true>(lit(c));
        } else {
            return lit(c) >> rhs;
        }
    }

    /** Returns a parser equivalent to `lit(str) >> rhs`. */
    template<parsable_range_like R, typename Parser>
    constexpr auto operator>>(R && range, parser_interface<Parser> rhs) noexcept
    {
        if constexpr (detail::is_seq_p<Parser>{}) {
            return rhs.parser_.template prepend<true>(lit(range));
        } else {
            return lit(range) >> rhs;
        }
    }

#ifndef BOOST_PARSER_DOXYGEN

    template<typename Parser, typename GlobalState, typename ErrorHandler>
    constexpr auto
    parser_interface<Parser, GlobalState, ErrorHandler>::operator>(
        char rhs) const noexcept
    {
        if constexpr (detail::is_seq_p<Parser>{}) {
            return parser_.template append<false>(lit(rhs));
        } else {
            return *this > lit(rhs);
        }
    }

    template<typename Parser, typename GlobalState, typename ErrorHandler>
    constexpr auto
    parser_interface<Parser, GlobalState, ErrorHandler>::operator>(
        char32_t rhs) const noexcept
    {
        if constexpr (detail::is_seq_p<Parser>{}) {
            return parser_.template append<false>(lit(rhs));
        } else {
            return *this > lit(rhs);
        }
    }

    template<typename Parser, typename GlobalState, typename ErrorHandler>
    template<parsable_range_like R>
    constexpr auto
    parser_interface<Parser, GlobalState, ErrorHandler>::operator>(
        R && range) const noexcept
    {
        if constexpr (detail::is_seq_p<Parser>{}) {
            return parser_.template append<false>(lit(range));
        } else {
            return *this > lit(range);
        }
    }

#endif

    /** Returns a parser equivalent to `lit(c) > rhs`. */
    template<typename Parser>
    constexpr auto operator>(char c, parser_interface<Parser> rhs) noexcept
    {
        if constexpr (detail::is_seq_p<Parser>{}) {
            return rhs.parser_.template prepend<false>(lit(c));
        } else {
            return lit(c) > rhs;
        }
    }

    /** Returns a parser equivalent to `lit(c) > rhs`. */
    template<typename Parser>
    constexpr auto operator>(char32_t c, parser_interface<Parser> rhs) noexcept
    {
        if constexpr (detail::is_seq_p<Parser>{}) {
            return rhs.parser_.template prepend<false>(lit(c));
        } else {
            return lit(c) > rhs;
        }
    }

    /** Returns a parser equivalent to `lit(str) > rhs`. */
    template<parsable_range_like R, typename Parser>
    constexpr auto operator>(R && range, parser_interface<Parser> rhs) noexcept
    {
        if constexpr (detail::is_seq_p<Parser>{}) {
            return rhs.parser_.template prepend<false>(lit(range));
        } else {
            return lit(range) > rhs;
        }
    }

#ifndef BOOST_PARSER_DOXYGEN

    template<typename Parser, typename GlobalState, typename ErrorHandler>
    constexpr auto
    parser_interface<Parser, GlobalState, ErrorHandler>::operator|(
        char rhs) const noexcept
    {
        if constexpr (detail::is_or_p<Parser>{}) {
            return parser_.append(lit(rhs));
        } else {
            return *this | lit(rhs);
        }
    }

    template<typename Parser, typename GlobalState, typename ErrorHandler>
    constexpr auto
    parser_interface<Parser, GlobalState, ErrorHandler>::operator|(
        char32_t rhs) const noexcept
    {
        if constexpr (detail::is_or_p<Parser>{}) {
            return parser_.append(lit(rhs));
        } else {
            return *this | lit(rhs);
        }
    }

    template<typename Parser, typename GlobalState, typename ErrorHandler>
    template<parsable_range_like R>
    constexpr auto
    parser_interface<Parser, GlobalState, ErrorHandler>::operator|(
        R && range) const noexcept
    {
        if constexpr (detail::is_or_p<Parser>{}) {
            return parser_.append(lit(range));
        } else {
            return *this | lit(range);
        }
    }

#endif

    /** Returns a parser equivalent to `lit(c) | rhs`. */
    template<typename Parser>
    constexpr auto operator|(char c, parser_interface<Parser> rhs) noexcept
    {
        if constexpr (detail::is_or_p<Parser>{}) {
            return rhs.parser_.prepend(lit(c));
        } else {
            return lit(c) | rhs;
        }
    }

    /** Returns a parser equivalent to `lit(c) | rhs`. */
    template<typename Parser>
    constexpr auto operator|(char32_t c, parser_interface<Parser> rhs) noexcept
    {
        if constexpr (detail::is_or_p<Parser>{}) {
            return rhs.parser_.prepend(lit(c));
        } else {
            return lit(c) | rhs;
        }
    }

    /** Returns a parser equivalent to `lit(str) | rhs`. */
    template<parsable_range_like R, typename Parser>
    constexpr auto operator|(R && range, parser_interface<Parser> rhs) noexcept
    {
        if constexpr (detail::is_or_p<Parser>{}) {
            return rhs.parser_.prepend(lit(range));
        } else {
            return lit(range) | rhs;
        }
    }

#ifndef BOOST_PARSER_DOXYGEN

    template<typename Parser, typename GlobalState, typename ErrorHandler>
    constexpr auto
    parser_interface<Parser, GlobalState, ErrorHandler>::operator-(
        char rhs) const noexcept
    {
        return !lit(rhs) >> *this;
    }

    template<typename Parser, typename GlobalState, typename ErrorHandler>
    constexpr auto
    parser_interface<Parser, GlobalState, ErrorHandler>::operator-(
        char32_t rhs) const noexcept
    {
        return !lit(rhs) >> *this;
    }

    template<typename Parser, typename GlobalState, typename ErrorHandler>
    template<parsable_range_like R>
    constexpr auto
    parser_interface<Parser, GlobalState, ErrorHandler>::operator-(
        R && range) const noexcept
    {
        return !lit(range) >> *this;
    }

#endif

    /** Returns a parser equivalent to `!rhs >> lit(c)`. */
    template<typename Parser>
    constexpr auto operator-(char c, parser_interface<Parser> rhs) noexcept
    {
        return !rhs >> lit(c);
    }

    /** Returns a parser equivalent to `!rhs >> lit(c)`. */
    template<typename Parser>
    constexpr auto operator-(char32_t c, parser_interface<Parser> rhs) noexcept
    {
        return !rhs >> lit(c);
    }

    /** Returns a parser equivalent to `!rhs >> lit(str)`. */
    template<parsable_range_like R, typename Parser>
    constexpr auto operator-(R && range, parser_interface<Parser> rhs) noexcept
    {
        return !rhs >> lit(range);
    }

#ifndef BOOST_PARSER_DOXYGEN

    template<typename Parser, typename GlobalState, typename ErrorHandler>
    constexpr auto
    parser_interface<Parser, GlobalState, ErrorHandler>::operator%(
        char rhs) const noexcept
    {
        return *this % lit(rhs);
    }

    template<typename Parser, typename GlobalState, typename ErrorHandler>
    constexpr auto
    parser_interface<Parser, GlobalState, ErrorHandler>::operator%(
        char32_t rhs) const noexcept
    {
        return *this % lit(rhs);
    }

    template<typename Parser, typename GlobalState, typename ErrorHandler>
    template<parsable_range_like R>
    constexpr auto
    parser_interface<Parser, GlobalState, ErrorHandler>::operator%(
        R && range) const noexcept
    {
        return *this % lit(range);
    }

#endif

    /** Returns a parser equivalent to `lit(c) % rhs`. */
    template<typename Parser>
    constexpr auto operator%(char c, parser_interface<Parser> rhs) noexcept
    {
        return lit(c) % rhs;
    }

    /** Returns a parser equivalent to `lit(c) % rhs`. */
    template<typename Parser>
    constexpr auto operator%(char32_t c, parser_interface<Parser> rhs) noexcept
    {
        return lit(c) % rhs;
    }

    /** Returns a parser equivalent to `lit(str) % rhs`. */
    template<parsable_range_like R, typename Parser>
    constexpr auto operator%(R && range, parser_interface<Parser> rhs) noexcept
    {
        return lit(range) % rhs;
    }

    namespace literals {
        /** Returns a literal parser equivalent to `lit(c)`. */
        constexpr auto operator""_l(char c) { return lit(c); }
        /** Returns a literal parser equivalent to `lit(c)`. */
        constexpr auto operator""_l(char32_t c) { return lit(c); }
        /** Returns a literal parser equivalent to `lit(c_str)`. */
        constexpr auto operator""_l(char const * c_str) { return lit(c_str); }

        /** Returns a literal parser equivalent to `lit(c)`. */
        constexpr auto operator""_p(char c) { return char_(c); }
        /** Returns a literal parser equivalent to `lit(c)`. */
        constexpr auto operator""_p(char32_t c) { return char_(c); }
        /** Returns a literal parser equivalent to `lit(c_str)`. */
        constexpr auto operator""_p(char const * c_str)
        {
            return string(c_str);
        }
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
    template<
        parsable_iter I,
        std::sentinel_for<I> S,
        typename Parser,
        typename GlobalState,
        error_handler<I, S, GlobalState> ErrorHandler,
        typename Attr>
    bool parse(
        I & first,
        S last,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        Attr & attr,
        trace trace_mode = trace::off)
    {
        if constexpr (
            detail::non_unicode_char_range_like<view<I, S>> ||
            sizeof(*first) == 4u) {
            if (trace_mode == trace::on) {
                return detail::parse_impl<true>(
                    first, last, parser, parser.error_handler_, attr);
            } else {
                return detail::parse_impl<false>(
                    first, last, parser, parser.error_handler_, attr);
            }
        } else {
            auto r = text::as_utf32(first, last);
            auto f = r.begin();
            auto const l = r.end();
            auto _ = detail::scoped_base_assign(first, f);
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
        successful.  On success, `attr` will be assigned the value of the
        attribute produced by `parser`.  If `trace_mode == trace::on`, a
        verbose trace of the parse will be streamed to `std::cout`. */
    template<
        parsable_range_like R,
        typename Parser,
        typename GlobalState,
        typename ErrorHandler,
        typename Attr>
    // clang-format off
        requires error_handler<
            ErrorHandler,
            std::ranges::iterator_t<R>,
            std::ranges::sentinel_t<R>,
            GlobalState>
    bool parse(
        // clang-format on
        R const & range,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        Attr & attr,
        trace trace_mode = trace::off)
    {
        auto r = detail::make_input_range(range);
        auto first = r.begin();
        auto const last = r.end();
        return parser::parse(first, last, parser, attr, trace_mode);
    }

    /** Parses `[first, last)` using `parser`.  Returns a `std::optional`
        containing the attribute produced by `parser` on parse success, and
        `std::nullopt` on parse failure.  If `trace_mode == trace::on`, a
        verbose trace of the parse will be streamed to `std::cout`. */
    template<
        parsable_iter I,
        std::sentinel_for<I> S,
        typename Parser,
        typename GlobalState,
        error_handler<I, S, GlobalState> ErrorHandler>
    auto parse(
        I & first,
        S last,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        trace trace_mode = trace::off)
    {
        if constexpr (
            detail::non_unicode_char_range_like<view<I, S>> ||
            sizeof(*first) == 4u) {
            if (trace_mode == trace::on) {
                return detail::parse_impl<true>(
                    first, last, parser, parser.error_handler_);
            } else {
                return detail::parse_impl<false>(
                    first, last, parser, parser.error_handler_);
            }
        } else {
            auto r = text::as_utf32(first, last);
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
        parse failure.  If `trace_mode == trace::on`, a verbose trace of the
        parse will be streamed to `std::cout`. */
    template<
        parsable_range_like R,
        typename Parser,
        typename GlobalState,
        typename ErrorHandler>
    // clang-format off
        requires error_handler<
            ErrorHandler,
            std::ranges::iterator_t<R>,
            std::ranges::sentinel_t<R>,
            GlobalState>
    auto parse(
        // clang-format on
        R const & range,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        trace trace_mode = trace::off)
    {
        auto r = detail::make_input_range(range);
        auto first = r.begin();
        auto const last = r.end();
        return parser::parse(first, last, parser, trace_mode);
    }

    /** Parses `[first, last)` using `parser`, and returns whether the parse
        was successful.  When a callback rule `r` is successful during the
        parse, one of two things happens: 1) if `r` has an attribute,
        `callbacks(tag, x)` will be called (where `tag` is
        `boost::hana::type<decltype(r)::tag_type>{}`, and `x` is the attribute
        produced by `r`), if that call is well-formed; otherwise,
        `callbacks[tag](x)` is called; or 2) if `r` has no attribute,
        `callbacks(tag)` will be called, if that call is well-formed;
        otherwise, `callbacks[tag]()` is called.  `Callbacks` is expected to
        either be an invocable with the correct overloads required to support
        all successful rule parses that might occur, or a `boost::hana::map`
        that contains an invocable for each `boost::hana::type` that might
        occur.  If `trace_mode == trace::on`, a verbose trace of the parse
        will be streamed to `std::cout`. */
    template<
        parsable_iter I,
        std::sentinel_for<I> S,
        typename Parser,
        typename GlobalState,
        error_handler<I, S, GlobalState> ErrorHandler,
        typename Callbacks>
    bool callback_parse(
        I & first,
        S last,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        Callbacks const & callbacks,
        trace trace_mode = trace::off)
    {
        if constexpr (
            detail::non_unicode_char_range_like<view<I, S>> ||
            sizeof(*first) == 4u) {
            if (trace_mode == trace::on) {
                return detail::callback_parse_impl<true>(
                    first, last, parser, parser.error_handler_, callbacks);
            } else {
                return detail::callback_parse_impl<false>(
                    first, last, parser, parser.error_handler_, callbacks);
            }
        } else {
            auto r = text::as_utf32(first, last);
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
        successful.  When a callback rule `r` is successful during the parse,
        one of two things happens: 1) if `r` has an attribute, `callbacks(tag,
        x)` will be called (where `tag` is
        `boost::hana::type<decltype(r)::tag_type>{}`, and `x` is the attribute
        produced by `r`), if that call is well-formed; otherwise,
        `callbacks[tag](x)` is called; or 2) if `r` has no attribute,
        `callbacks(tag)` will be called, if that call is well-formed;
        otherwise, `callbacks[tag]()` is called.  `Callbacks` is expected to
        either be an invocable with the correct overloads required to support
        all successful rule parses that might occur, or a `boost::hana::map`
        that contains an invocable for each `boost::hana::type` that might
        occur.  If `trace_mode == trace::on`, a verbose trace of the parse
        will be streamed to `std::cout`. */
    template<
        parsable_range_like R,
        typename Parser,
        typename GlobalState,
        typename ErrorHandler,
        typename Callbacks>
    // clang-format off
        requires error_handler<
            ErrorHandler,
            std::ranges::iterator_t<R>,
            std::ranges::sentinel_t<R>,
            GlobalState>
    bool callback_parse(
        // clang-format on
        R const & range,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        Callbacks const & callbacks,
        trace trace_mode = trace::off)
    {
        auto r = detail::make_input_range(range);
        auto first = r.begin();
        auto const last = r.end();
        return parser::callback_parse(first, last, parser, callbacks);
    }

    /** Parses `[first, last)` using `parser`, skipping all input recognized
        by `skip` between the application of any two parsers, and returns
        whether the parse was successful.  On success, `attr` will be assigned
        the value of the attribute produced by `parser`.  If `trace_mode ==
        trace::on`, a verbose trace of the parse will be streamed to
        `std::cout`. */
    template<
        parsable_iter I,
        std::sentinel_for<I> S,
        typename Parser,
        typename GlobalState,
        error_handler<I, S, GlobalState> ErrorHandler,
        typename SkipParser,
        typename Attr>
    bool skip_parse(
        I & first,
        S last,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        SkipParser const & skip,
        Attr & attr,
        trace trace_mode = trace::off)
    {
        if constexpr (
            detail::non_unicode_char_range_like<view<I, S>> ||
            sizeof(*first) == 4u) {
            if (trace_mode == trace::on) {
                return detail::skip_parse_impl<true>(
                    first, last, parser, skip, parser.error_handler_, attr);
            } else {
                return detail::skip_parse_impl<false>(
                    first, last, parser, skip, parser.error_handler_, attr);
            }
        } else {
            auto r = text::as_utf32(first, last);
            auto f = r.begin();
            auto const l = r.end();
            auto _ = detail::scoped_base_assign(first, f);
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
        parse was successful.  On success, `attr` will be assigned the value
        of the attribute produced by `parser`.  If `trace_mode == trace::on`,
        a verbose trace of the parse will be streamed to `std::cout`. */
    template<
        parsable_range_like R,
        typename Parser,
        typename GlobalState,
        typename ErrorHandler,
        typename SkipParser,
        typename Attr>
    // clang-format off
        requires error_handler<
            ErrorHandler,
            std::ranges::iterator_t<R>,
            std::ranges::sentinel_t<R>,
            GlobalState>
    bool skip_parse(
        // clang-format on
        R const & range,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        SkipParser const & skip,
        Attr & attr,
        trace trace_mode = trace::off)
    {
        auto r = detail::make_input_range(range);
        auto first = r.begin();
        auto const last = r.end();
        return parser::skip_parse(first, last, parser, skip, attr, trace_mode);
    }

    /** Parses `[first, last)` using `parser`, skipping all input recognized
        by `skip` between the application of any two parsers.  Returns a
        `std::optional` containing the attribute produced by `parser` on parse
        success, and `std::nullopt` on parse failure.  If `trace_mode ==
        trace::on`, a verbose trace of the parse will be streamed to
        `std::cout`. */
    template<
        parsable_iter I,
        std::sentinel_for<I> S,
        typename Parser,
        typename GlobalState,
        error_handler<I, S, GlobalState> ErrorHandler,
        typename SkipParser>
    auto skip_parse(
        I & first,
        S last,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        SkipParser const & skip,
        trace trace_mode = trace::off)
    {
        if constexpr (
            detail::non_unicode_char_range_like<view<I, S>> ||
            sizeof(*first) == 4u) {
            if (trace_mode == trace::on) {
                return detail::skip_parse_impl<true>(
                    first, last, parser, skip, parser.error_handler_);
            } else {
                return detail::skip_parse_impl<false>(
                    first, last, parser, skip, parser.error_handler_);
            }
        } else {
            auto r = text::as_utf32(first, last);
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

    /** Parses `str` using `parser`, skipping all input recognized by `skip`
        between the application of any two parsers.  Returns a `std::optional`
        containing the attribute produced by `parser` on parse success, and
        `std::nullopt` on parse failure.  If `trace_mode == trace::on`, a
        verbose trace of the parse will be streamed to `std::cout`. */
    template<
        parsable_range_like R,
        typename Parser,
        typename GlobalState,
        typename ErrorHandler,
        typename SkipParser>
    // clang-format off
        requires error_handler<
            ErrorHandler,
            std::ranges::iterator_t<R>,
            std::ranges::sentinel_t<R>,
            GlobalState>
    auto skip_parse(
        // clang-format on
        R const & range,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        SkipParser const & skip,
        trace trace_mode = trace::off)
    {
        auto r = detail::make_input_range(range);
        auto first = r.begin();
        auto const last = r.end();
        return parser::skip_parse(first, last, parser, skip, trace_mode);
    }

    /** Parses `[first, last)` using `parser`, skipping all input recognized
        by `skip` between the application of any two parsers, and returns
        whether the parse was successful.  When a callback rule `r` is
        successful during the parse, one of two things happens: 1) if `r` has
        an attribute, `callbacks(tag, x)` will be called (where `tag` is
        `boost::hana::type<decltype(r)::tag_type>{}`, and `x` is the attribute
        produced by `r`), if that call is well-formed; otherwise,
        `callbacks[tag](x)` is called; or 2) if `r` has no attribute,
        `callbacks(tag)` will be called, if that call is well-formed;
        otherwise, `callbacks[tag]()` is called.  `Callbacks` is expected to
        either be an invocable with the correct overloads required to support
        all successful rule parses that might occur, or a `boost::hana::map`
        that contains an invocable for each `boost::hana::type` that might
        occur.  If `trace_mode == trace::on`, a verbose trace of the parse
        will be streamed to `std::cout`. */
    template<
        parsable_iter I,
        std::sentinel_for<I> S,
        typename Parser,
        typename GlobalState,
        error_handler<I, S, GlobalState> ErrorHandler,
        typename SkipParser,
        typename Callbacks>
    bool callback_skip_parse(
        I & first,
        S last,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        SkipParser const & skip,
        Callbacks const & callbacks,
        trace trace_mode = trace::off)
    {
        if constexpr (
            detail::non_unicode_char_range_like<view<I, S>> ||
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
            auto r = text::as_utf32(first, last);
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
        parse was successful.  When a callback rule `r` is successful during
        the parse, one of two things happens: 1) if `r` has an attribute,
        `callbacks(tag, x)` will be called (where `tag` is
        `boost::hana::type<decltype(r)::tag_type>{}`, and `x` is the attribute
        produced by `r`), if that call is well-formed; otherwise,
        `callbacks[tag](x)` is called; or 2) if `r` has no attribute,
        `callbacks(tag)` will be called, if that call is well-formed;
        otherwise, `callbacks[tag]()` is called.  `Callbacks` is expected to
        either be an invocable with the correct overloads required to support
        all successful rule parses that might occur, or a `boost::hana::map`
        that contains an invocable for each `boost::hana::type` that might
        occur.  If `trace_mode == trace::on`, a verbose trace of the parse
        will be streamed to `std::cout`. */
    template<
        parsable_range_like R,
        typename Parser,
        typename GlobalState,
        typename ErrorHandler,
        typename SkipParser,
        typename Callbacks>
    // clang-format off
        requires error_handler<
            ErrorHandler,
            std::ranges::iterator_t<R>,
            std::ranges::sentinel_t<R>,
            GlobalState>
    bool callback_skip_parse(
        // clang-format on
        R const & range,
        parser_interface<Parser, GlobalState, ErrorHandler> const & parser,
        SkipParser const & skip,
        Callbacks const & callbacks,
        trace trace_mode = trace::off)
    {
        auto r = detail::make_input_range(range);
        auto first = r.begin();
        auto const last = r.end();
        return parser::skip_parse(
            first, last, parser, skip, callbacks, trace_mode);
    }

}}

#endif
