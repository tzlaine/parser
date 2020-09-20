#ifndef BOOST_PARSER_DETAIL_HL_HPP
#define BOOST_PARSER_DETAIL_HL_HPP

#include <boost/parser/detail/detection.hpp>

#include <tuple>
#include <type_traits>
#include <utility>


namespace boost { namespace parser { namespace detail::hl {

    // Boost.Hana lite.

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
        int _[] = {0, (f(std::get<I>(t)), 0)...};
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
        int _[] = {0, (f(std::move(std::get<I>(t))), 0)...};
        (void)_;
    }

    template<typename F, typename... Args>
    void for_each(std::tuple<Args...> && t, F && f)
    {
        hl::for_each_impl(
            std::move(t),
            (F &&) f,
            std::make_integer_sequence<std::size_t, sizeof...(Args)>());
    }
    template<typename F, typename... Args>
    void for_each(std::tuple<Args...> const & t, F && f)
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
        return std::tuple<
            std::decay_t<decltype(f(std::get<I + offset>(t)))>...>{
            f(std::get<I + offset>(t))...};
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
        return std::tuple<
            std::decay_t<decltype(f(std::move(std::get<I + offset>(t))))>...>{
            f(std::move(std::get<I + offset>(t)))...};
    }

    template<typename F, typename... Args>
    auto transform(std::tuple<Args...> && t, F && f)
    {
        return hl::transform_impl<0>(
            std::move(t),
            (F &&) f,
            std::make_integer_sequence<std::size_t, sizeof...(Args)>());
    }
    template<typename F, typename... Args>
    auto transform(std::tuple<Args...> const & t, F && f)
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
        static auto call(std::tuple<Args...> const & t, State && s, F const & f)
        {
            return fold_left_dispatch<I + 1, N>::call(
                t, f((State &&) s, std::get<I>(t)), f);
        }
    };
    template<std::size_t I>
    struct fold_left_dispatch<I, I>
    {
        template<typename F, typename State, typename... Args>
        static auto call(std::tuple<Args...> const & t, State && s, F const & f)
        {
            return (State &&) s;
        }
    };

    template<typename F, typename State, typename... Args>
    auto fold_left(std::tuple<Args...> const & t, State && s, F const & f)
    {
        return hl::fold_left_dispatch<0, sizeof...(Args)>::call(
            t, (State &&) s, (F &&) f);
    }


    // size

    template<typename... Args>
    constexpr auto size(std::tuple<Args...> const & t)
    {
        return sizeof...(Args);
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
        return (eq(std::get<I>(t), x) || ...);
    }

    template<typename T, typename... Args>
    bool contains(std::tuple<Args...> & t, T const & x)
    {
        return contains_impl(
            t, x, std::make_integer_sequence<std::size_t, sizeof...(Args)>());
    }


    // front, back

    template<typename Arg, typename... Args>
    decltype(auto) front(std::tuple<Arg, Args...> & t)
    {
        return std::get<0>(t);
    }
    template<typename Arg, typename... Args>
    decltype(auto) front(std::tuple<Arg, Args...> const & t)
    {
        return std::get<0>(t);
    }
    template<typename Arg, typename... Args>
    decltype(auto) back(std::tuple<Arg, Args...> & t)
    {
        return std::get<sizeof...(Args)>(t);
    }
    template<typename Arg, typename... Args>
    decltype(auto) back(std::tuple<Arg, Args...> const & t)
    {
        return std::get<sizeof...(Args)>(t);
    }


    // drop_front

    template<typename Arg, typename... Args>
    auto drop_front(std::tuple<Arg, Args...> && t)
    {
        return hl::transform_impl<1>(
            std::move(t),
            forward{},
            std::make_integer_sequence<std::size_t, sizeof...(Args)>());
    }
    template<typename Arg, typename... Args>
    auto drop_front(std::tuple<Arg, Args...> const & t)
    {
        return hl::transform_impl<1>(
            t,
            forward{},
            std::make_integer_sequence<std::size_t, sizeof...(Args)>());
    }


    // drop_back

    template<typename Arg, typename... Args>
    auto drop_back(std::tuple<Arg, Args...> && t)
    {
        return hl::transform_impl<0>(
            std::move(t),
            forward{},
            std::make_integer_sequence<std::size_t, sizeof...(Args)>());
    }
    template<typename Arg, typename... Args>
    auto drop_back(std::tuple<Arg, Args...> const & t)
    {
        return hl::transform_impl<0>(
            t,
            forward{},
            std::make_integer_sequence<std::size_t, sizeof...(Args)>());
    }


    // first, second

    template<typename T, typename U>
    decltype(auto) first(std::tuple<T, U> & t)
    {
        return std::get<0>(t);
    }
    template<typename T, typename U>
    decltype(auto) first(std::tuple<T, U> const & t)
    {
        return std::get<0>(t);
    }
    template<typename T, typename U>
    decltype(auto) second(std::tuple<T, U> & t)
    {
        return std::get<1>(t);
    }
    template<typename T, typename U>
    decltype(auto) second(std::tuple<T, U> const & t)
    {
        return std::get<1>(t);
    }


    // zip

    template<std::size_t I, typename... Tuples>
    decltype(auto) make_zip_elem(Tuples const &... ts)
    {
        return std::make_tuple(std::get<I>(ts)...);
    }

    template<std::size_t... I, typename... Tuples>
    auto zip_impl(std::index_sequence<I...>, Tuples const &... ts)
    {
        return std::make_tuple(hl::make_zip_elem<I>(ts...)...);
    }

    template<typename Tuple, typename... Tuples>
    auto zip(Tuple const & t, Tuples const &... ts)
    {
        return hl::zip_impl(
            std::make_integer_sequence<
                std::size_t,
                std::tuple_size<std::remove_reference_t<Tuple>>::value>(),
            t,
            ts...);
    }


    // append

    template<typename... Args, typename T>
    auto append(std::tuple<Args...> && t, T && x)
    {
        return std::tuple_cat(std::move(t), std::make_tuple((T &&) x));
    }
    template<typename... Args, typename T>
    auto append(std::tuple<Args...> const & t, T && x)
    {
        return std::tuple_cat(t, std::make_tuple((T &&) x));
    }


    // prepend

    template<typename... Args, typename T>
    auto prepend(std::tuple<Args...> && t, T && x)
    {
        return std::tuple_cat(std::make_tuple((T &&) x), std::move(t));
    }
    template<typename... Args, typename T>
    auto prepend(std::tuple<Args...> const & t, T && x)
    {
        return std::tuple_cat(std::make_tuple((T &&) x), t);
    }

    // TODO: In parser namespace, get(t, i), where t is a tuple and i is a
    // std::integral_constant<std::size_t> const &.

    // TODO: In parser namespace, a literal for N_c, a la hana's literal,
    // except that it produces a type derived from
    // std::integral_constant<std::size_t>.

}}}

#endif
