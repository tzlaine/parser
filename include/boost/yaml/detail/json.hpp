#ifndef BOOST_YAML_DETAIL_JSON_HPP
#define BOOST_YAML_DETAIL_JSON_HPP

#include <boost/yaml/json_fwd.hpp>

#include <boost/text/algorithm.hpp>
#include <boost/text/utility.hpp>

#include <iomanip>
#include <iostream>


namespace boost { namespace json { namespace detail {

    template<typename T>
    struct is_object;

    template<typename T>
    struct is_array;

    template<typename T>
    struct is_string;

    struct value_impl_base
    {
        virtual ~value_impl_base() = 0;

        virtual std::unique_ptr<value_impl_base> copy_impl() const = 0;

        virtual value_kind kind() const noexcept = 0;

        virtual bool equal_impl(value const & rhs) const noexcept = 0;

        virtual std::ostream & to_json(std::ostream & os) const noexcept = 0;
    };

    inline value_impl_base::~value_impl_base() {}

    template<typename T>
    struct value_impl;

    // TODO: Use this, and put objects (unordered_maps) on the heap, in
    // the implementation of jason_value_impl below.
    constexpr int value_buffer_size()
    {
        return (std::max)(sizeof(std::vector<int>), sizeof(std::string));
    }

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

    template<typename T>
    struct is_object : is_range_of<
                           T,
                           std::pair<std::string, value>,
                           std::pair<std::string const, value>>
    {
    };

    template<typename T>
    struct is_array : is_range_of<T, value>
    {
    };

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

}}}

#endif
