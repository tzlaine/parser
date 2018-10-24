#ifndef BOOST_YAML_YAML_FWD_HPP
#define BOOST_YAML_YAML_FWD_HPP

#include <boost/yaml/exception.hpp>

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include <memory>


namespace boost { namespace yaml {

    struct value;

}}

namespace std {
    template<>
    struct hash<boost::yaml::value>
    {
        using argument_type = boost::yaml::value;
        using result_type = size_t;
        result_type operator()(argument_type const & v) const noexcept;
    };
}

namespace boost { namespace yaml {

    struct value;

    enum class value_kind {
        map,
        seq,
        double_,
        int_,
        string,
        boolean,
        null,
        alias,
        property_node,
        user_defined
    };

    struct null_t
    {
        bool operator==(null_t) const noexcept { return true; }
        bool operator!=(null_t) const noexcept { return false; }
        bool operator<(null_t) const noexcept { return false; }
    };

    // TODO: Stream inserters for these four as well.

    using seq = std::vector<value>;
    using map = std::unordered_map<value, value>;
    using map_element = std::pair<value, value>;

    struct properties
    {
        properties() {}
        properties(std::string tag, std::string anchor) :
            tag_(std::move(tag)),
            anchor_(std::move(anchor))
        {}

        explicit operator bool() const { return tag_ != "" || anchor_ != ""; }

        std::string tag_;
        std::string anchor_;
    };

    using alias = std::pair<std::string, std::shared_ptr<value const>>;
    using property_node = std::pair<properties, value>;

    template<typename T>
    T const & get(value const & v) noexcept;
    template<typename T>
    T & get(value & v) noexcept;

    std::size_t hash_append(std::size_t seed, value const & v);
    std::size_t hash_append(std::size_t seed, seq const & v);
    std::size_t hash_append(std::size_t seed, map const & v);
    std::size_t hash_append(std::size_t seed, alias const & v);
    std::size_t hash_append(std::size_t seed, property_node const & v);

    namespace detail {
        template<typename T>
        struct get_impl;
    }

}}

namespace std {
    template<>
    struct hash<boost::yaml::map>
    {
        using argument_type = boost::yaml::map;
        using result_type = size_t;
        result_type operator()(argument_type const & m) const noexcept;
    };

    template<>
    struct hash<boost::yaml::seq>
    {
        using argument_type = boost::yaml::seq;
        using result_type = size_t;
        result_type operator()(argument_type const & s) const noexcept;
    };

    template<>
    struct hash<boost::yaml::alias>
    {
        using argument_type = boost::yaml::alias;
        using result_type = size_t;
        result_type operator()(argument_type const & a) const noexcept;
    };

    template<>
    struct hash<boost::yaml::property_node>
    {
        using argument_type = boost::yaml::property_node;
        using result_type = size_t;
        result_type operator()(argument_type const & pn) const noexcept;
    };
}

#endif
