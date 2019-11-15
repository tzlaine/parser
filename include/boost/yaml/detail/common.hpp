#ifndef BOOST_YAML_DETAIL_COMMON_HPP
#define BOOST_YAML_DETAIL_COMMON_HPP

#include <boost/yaml/json_fwd.hpp>

#include <boost/text/algorithm.hpp>

#include <iomanip>
#include <iostream>


namespace boost { namespace yaml { namespace detail {

    // Detection idiom.

    template<typename...>
    struct void_
    {
        using type = void;
    };

    template<typename... T>
    using void_t = typename void_<T...>::type;

    template<typename T>
    using remove_cv_ref_t =
        typename std::remove_cv<typename std::remove_reference<T>::type>::type;

    struct nonesuch
    {};

    template<
        typename Default,
        typename AlwaysVoid,
        template<typename...> class Template,
        typename... Args>
    struct detector
    {
        using value_t = std::false_type;
        using type = Default;
    };

    template<
        typename Default,
        template<typename...> class Template,
        typename... Args>
    struct detector<Default, void_t<Template<Args...>>, Template, Args...>
    {
        using value_t = std::true_type;
        using type = Template<Args...>;
    };

    template<template<typename...> class Template, typename... Args>
    using is_detected =
        typename detector<nonesuch, void, Template, Args...>::value_t;

    template<template<typename...> class Template, typename... Args>
    using detected_t =
        typename detector<nonesuch, void, Template, Args...>::type;

    template<
        typename Default,
        template<typename...> class Template,
        typename... Args>
    using detected_or =
        typename detector<Default, void, Template, Args...>::type;


    // Type traits.

    template<typename T>
    using has_begin = decltype(*std::begin(std::declval<T>()));
    template<typename T>
    using has_end = decltype(*std::end(std::declval<T>()));


    template<typename T, typename U, typename V = U>
    using is_range_of = std::integral_constant<
        bool,
        ((std::is_same<remove_cv_ref_t<detected_t<has_begin, T>>, U>::value ||
          std::is_same<remove_cv_ref_t<detected_t<has_begin, T>>, V>::value) &&
         is_detected<has_end, T>::value)>;

    template<typename T, typename BeginValueType>
    using is_range_of_char = std::integral_constant<
        bool,
        (std::is_convertible<BeginValueType, const char>::value &&
         sizeof(BeginValueType) == 1 && is_detected<has_end, T>::value)>;

    template<typename T>
    struct is_string
        : is_range_of_char<T, remove_cv_ref_t<detected_t<has_begin, T>>>
    {
    };


    // Hashing.

    inline std::size_t
    hash_combine_(std::size_t seed, std::size_t value) noexcept
    {
        return seed ^= value + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

}}}

#endif
