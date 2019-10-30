#ifndef BOOST_YAML_JSON_FWD_HPP
#define BOOST_YAML_JSON_FWD_HPP

#include <string>
#include <unordered_map>
#include <vector>


namespace boost { namespace json {

    struct value;

    enum class value_kind { null, boolean, number, string, object, array };

    struct null_t
    {
        bool operator==(null_t) const noexcept { return true; }
        bool operator!=(null_t) const noexcept { return false; }
        bool operator<(null_t) const noexcept { return false; }
    };

    // TODO: Stream inserters for these two as well.

    using array = std::vector<value>;
    using object = std::unordered_map<std::string, value>;

    // TODO: Make get<>() more like the one YAML uses.
    namespace detail {
        template<typename T, bool Const>
        struct get_result
        {
            using type = T;
        };
        template<>
        struct get_result<array, true>
        {
            using type = array const &;
        };
        template<>
        struct get_result<array, false>
        {
            using type = array &;
        };
        template<>
        struct get_result<object, true>
        {
            using type = object const &;
        };
        template<>
        struct get_result<object, false>
        {
            using type = object &;
        };

        template<typename T, bool Const>
        using get_result_t = typename get_result<T, Const>::type;
    }

    template<typename T>
    detail::get_result_t<T, true> get(value const & v) noexcept;
    template<typename T>
    detail::get_result_t<T, false> get(value & v) noexcept;

    std::size_t hash_append(std::size_t seed, value const & v);
    std::size_t hash_append(std::size_t seed, array const & v);
    std::size_t hash_append(std::size_t seed, object const & v);

    namespace detail {
        template<typename T>
        struct get_impl;
    }

}}

namespace std {
    template<>
    struct hash<boost::json::value>
    {
        using argument_type = boost::json::value;
        using result_type = size_t;
        result_type operator()(argument_type const & v) const noexcept;
    };

    template<>
    struct hash<boost::json::object>
    {
        using argument_type = boost::json::object;
        using result_type = size_t;
        result_type operator()(argument_type const & o) const noexcept;
    };

    template<>
    struct hash<boost::json::array>
    {
        using argument_type = boost::json::array;
        using result_type = size_t;
        result_type operator()(argument_type const & a) const noexcept;
    };
}

#endif
