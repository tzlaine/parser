#ifndef BOOST_YAML_JSON_FWD_HPP
#define BOOST_YAML_JSON_FWD_HPP

#include <string>
#include <unordered_map>
#include <vector>


namespace boost { namespace json {

    struct value;

    enum class value_kind { object, array, number, string, boolean, null };

    struct null_t
    {};

    template<typename T>
    T const & get(value const & v) noexcept;
    template<typename T>
    T & get(value & v) noexcept;

    using array = std::vector<value>;
    using object = std::unordered_map<std::string, value>;

}}

#endif
