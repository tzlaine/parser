#ifndef BOOST_YAML_DETAIL_JSON_HPP
#define BOOST_YAML_DETAIL_JSON_HPP

#include <boost/yaml/json_fwd.hpp>
#include <boost/yaml/detail/common.hpp>

#include <boost/text/algorithm.hpp>

#include <iomanip>
#include <iostream>


namespace boost { namespace json { namespace detail {

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

    template<typename T>
    struct is_object : yaml::detail::is_range_of<
                           T,
                           std::pair<std::string, value>,
                           std::pair<std::string const, value>>
    {
    };

    template<typename T>
    struct is_array : yaml::detail::is_range_of<T, value>
    {
    };

    template<typename T>
    using is_string = yaml::detail::is_string<T>;

    template<typename T>
    struct get_impl;

    using yaml::detail::hash_combine_;

}}}

#endif
