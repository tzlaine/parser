// Copyright (C) 2020 T. Zachary Laine
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_PARSER_DETAIL_HL_HPP
#define BOOST_PARSER_DETAIL_HL_HPP

#include <boost/parser/config.hpp>
#include <boost/parser/tuple.hpp>
#include <boost/parser/detail/detection.hpp>

#include <type_traits>
#include <utility>


namespace boost { namespace parser { namespace detail::hl {

    // Boost.Hana lite.  These functions work with boost::hana::tuple and
    // std::tuple.

    struct forward
    {
        template<typename T>
        decltype(auto) operator()(T && t)
        {
            return (T &&) t;
        }
    };

    // for_each

    template<typename F, typename Tuple, std::size_t... I>
    void for_each_impl(
        Tuple const & t, F && f, std::integer_sequence<std::size_t, I...>)
    {
        int _[] = {0, (f(parser::get(t, llong<I>{})), 0)...};
        (void)_;
    }
    template<
        typename F,
        typename Tuple,
        std::size_t... I,
        typename Enable = std::enable_if_t<!std::is_reference_v<Tuple>>>
    void
    for_each_impl(Tuple && t, F && f, std::integer_sequence<std::size_t, I...>)
    {
        int _[] = {0, (f(std::move(parser::get(t, llong<I>{}))), 0)...};
        (void)_;
    }

    template<typename F, typename... Args>
    void for_each(tuple<Args...> && t, F && f)
    {
        hl::for_each_impl(
            std::move(t),
            (F &&) f,
            std::make_integer_sequence<std::size_t, sizeof...(Args)>());
    }
    template<typename F, typename... Args>
    void for_each(tuple<Args...> const & t, F && f)
    {
        hl::for_each_impl(
            t,
            (F &&) f,
            std::make_integer_sequence<std::size_t, sizeof...(Args)>());
    }


    // transform

    template<int offset, typename F, typename Tuple, std::size_t... I>
    auto transform_impl(
        Tuple const & t, F && f, std::integer_sequence<std::size_t, I...>)
    {
        return tuple<
            std::decay_t<decltype(f(parser::get(t, llong<I + offset>{})))>...>{
            f(parser::get(t, llong<I + offset>{}))...};
    }
    template<
        int offset,
        typename F,
        typename Tuple,
        std::size_t... I,
        typename Enable = std::enable_if_t<!std::is_reference_v<Tuple>>>
    auto
    transform_impl(Tuple && t, F && f, std::integer_sequence<std::size_t, I...>)
    {
        return tuple<std::decay_t<decltype(
            f(std::move(parser::get(t, llong<I + offset>{}))))>...>{
            f(std::move(parser::get(t, llong<I + offset>{})))...};
    }

    template<typename F, typename... Args>
    auto transform(tuple<Args...> && t, F && f)
    {
        return hl::transform_impl<0>(
            std::move(t),
            (F &&) f,
            std::make_integer_sequence<std::size_t, sizeof...(Args)>());
    }
    template<typename F, typename... Args>
    auto transform(tuple<Args...> const & t, F && f)
    {
        return hl::transform_impl<0>(
            t,
            (F &&) f,
            std::make_integer_sequence<std::size_t, sizeof...(Args)>());
    }


    // fold_left

    template<std::size_t I, std::size_t N>
    struct fold_left_dispatch
    {
        template<typename F, typename State, typename... Args>
        static auto call(tuple<Args...> const & t, State && s, F const & f)
        {
            return fold_left_dispatch<I + 1, N>::call(
                t, f((State &&) s, parser::get(t, llong<I>{})), f);
        }
    };
    template<std::size_t I>
    struct fold_left_dispatch<I, I>
    {
        template<typename F, typename State, typename... Args>
        static auto call(tuple<Args...> const & t, State && s, F const & f)
        {
            return (State &&) s;
        }
    };

    template<typename F, typename State, typename... Args>
    auto fold_left(tuple<Args...> const & t, State && s, F const & f)
    {
        return hl::fold_left_dispatch<0, sizeof...(Args)>::call(
            t, (State &&) s, (F &&) f);
    }


    // size

    template<typename... Args>
    constexpr auto size(tuple<Args...> const & t)
    {
        return llong<sizeof...(Args)>{};
    }

    template<typename... Args>
    constexpr auto size_minus_one(tuple<Args...> const & t)
    {
        return llong<sizeof...(Args) - 1>{};
    }


    // contains

    template<typename T, typename U>
    using comparable = decltype(std::declval<T>() == std::declval<U>());

    struct typesafe_equals
    {
        template<typename T, typename U>
        bool operator()(T const & t, U const & u)
        {
            if constexpr (detail::is_detected<comparable, T, U>::value) {
                return t == u;
            } else {
                return false;
            }
        }
    };

    template<typename T, typename Tuple, std::size_t... I>
    bool contains_impl(
        Tuple const & t, T const & x, std::integer_sequence<std::size_t, I...>)
    {
        typesafe_equals eq;
        return (eq(parser::get(t, llong<I>{}), x) || ...);
    }

    template<typename T, typename... Args>
    bool contains(tuple<Args...> & t, T const & x)
    {
        return contains_impl(
            t, x, std::make_integer_sequence<std::size_t, sizeof...(Args)>());
    }


    // front, back

    template<typename Arg, typename... Args>
    decltype(auto) front(tuple<Arg, Args...> & t)
    {
        return parser::get(t, llong<0>{});
    }
    template<typename Arg, typename... Args>
    decltype(auto) front(tuple<Arg, Args...> const & t)
    {
        return parser::get(t, llong<0>{});
    }
    template<typename Arg, typename... Args>
    decltype(auto) back(tuple<Arg, Args...> & t)
    {
        return parser::get(t, llong<sizeof...(Args)>{});
    }
    template<typename Arg, typename... Args>
    decltype(auto) back(tuple<Arg, Args...> const & t)
    {
        return parser::get(t, llong<sizeof...(Args)>{});
    }


    // drop_front

    template<typename Arg, typename... Args>
    auto drop_front(tuple<Arg, Args...> && t)
    {
        return hl::transform_impl<1>(
            std::move(t),
            forward{},
            std::make_integer_sequence<std::size_t, sizeof...(Args)>());
    }
    template<typename Arg, typename... Args>
    auto drop_front(tuple<Arg, Args...> const & t)
    {
        return hl::transform_impl<1>(
            t,
            forward{},
            std::make_integer_sequence<std::size_t, sizeof...(Args)>());
    }


    // drop_back

    template<typename Arg, typename... Args>
    auto drop_back(tuple<Arg, Args...> && t)
    {
        return hl::transform_impl<0>(
            std::move(t),
            forward{},
            std::make_integer_sequence<std::size_t, sizeof...(Args)>());
    }
    template<typename Arg, typename... Args>
    auto drop_back(tuple<Arg, Args...> const & t)
    {
        return hl::transform_impl<0>(
            t,
            forward{},
            std::make_integer_sequence<std::size_t, sizeof...(Args)>());
    }


    // first, second

    template<typename T, typename U>
    decltype(auto) first(tuple<T, U> & t)
    {
        return parser::get(t, llong<0>{});
    }
    template<typename T, typename U>
    decltype(auto) first(tuple<T, U> const & t)
    {
        return parser::get(t, llong<0>{});
    }
    template<typename T, typename U>
    decltype(auto) second(tuple<T, U> & t)
    {
        return parser::get(t, llong<1>{});
    }
    template<typename T, typename U>
    decltype(auto) second(tuple<T, U> const & t)
    {
        return parser::get(t, llong<1>{});
    }


    // zip

    template<std::size_t I, typename... Tuples>
    decltype(auto) make_zip_elem(Tuples const &... ts)
    {
#if BOOST_PARSER_USE_STD_TUPLE
        return std::make_tuple(parser::get(ts, llong<I>{})...);
#else
        return hana::make_tuple(parser::get(ts, llong<I>{})...);
#endif
    }

    template<std::size_t... I, typename... Tuples>
    auto zip_impl(std::index_sequence<I...>, Tuples const &... ts)
    {
#if BOOST_PARSER_USE_STD_TUPLE
        return std::make_tuple(hl::make_zip_elem<I>(ts...)...);
#else
        return hana::make_tuple(hl::make_zip_elem<I>(ts...)...);
#endif
    }

    template<typename T>
    struct tuplesize;
    template<typename... Args>
    struct tuplesize<tuple<Args...>>
    {
        constexpr static std::size_t value = sizeof...(Args);
    };

    template<typename Tuple, typename... Tuples>
    auto zip(Tuple const & t, Tuples const &... ts)
    {
        return hl::zip_impl(
            std::make_integer_sequence<
                std::size_t,
                tuplesize<std::remove_reference_t<Tuple>>::value>(),
            t,
            ts...);
    }


    // append

    template<typename... Args, typename T>
    auto append(tuple<Args...> && t, T && x)
    {
#if BOOST_PARSER_USE_STD_TUPLE
        return std::tuple_cat(std::move(t), std::make_tuple((T &&) x));
#else
        return hana::append(std::move(t), (T &&) x);
#endif
    }
    template<typename... Args, typename T>
    auto append(tuple<Args...> const & t, T && x)
    {
#if BOOST_PARSER_USE_STD_TUPLE
        return std::tuple_cat(t, std::make_tuple((T &&) x));
#else
        return hana::append(t, (T &&) x);
#endif
    }


    // prepend

    template<typename... Args, typename T>
    auto prepend(tuple<Args...> && t, T && x)
    {
#if BOOST_PARSER_USE_STD_TUPLE
        return std::tuple_cat(std::make_tuple((T &&) x), std::move(t));
#else
        return hana::prepend(std::move(t), (T &&) x);
#endif
    }
    template<typename... Args, typename T>
    auto prepend(tuple<Args...> const & t, T && x)
    {
#if BOOST_PARSER_USE_STD_TUPLE
        return std::tuple_cat(std::make_tuple((T &&) x), t);
#else
        return hana::prepend(t, (T &&) x);
#endif
    }

}}}

#endif
