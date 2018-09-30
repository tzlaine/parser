#ifndef BOOST_YAML_DETAIL_YAML_HPP
#define BOOST_YAML_DETAIL_YAML_HPP

#include <boost/yaml/yaml_fwd.hpp>
#include <boost/yaml/detail/common.hpp>

#include <boost/type_index.hpp>


namespace boost { namespace yaml { namespace detail {

    struct value_impl_base
    {
        virtual ~value_impl_base() = 0;

        virtual std::unique_ptr<value_impl_base> copy_impl() const = 0;

        virtual value_kind kind() const noexcept = 0;

        virtual bool equal_impl(value const & rhs) const noexcept = 0;

        virtual std::ostream & to_yaml_impl(std::ostream & os) const
            noexcept = 0;

        virtual typeindex::type_index type_id() const noexcept = 0;

        // Only ever called for user_defined.
        virtual std::size_t hash_append_impl(std::size_t seed) const noexcept
        {
            assert(!"Unreachable");
            return seed;
        }
    };

    inline value_impl_base::~value_impl_base() {}

    template<typename T>
    struct value_impl;

    // TODO: Use this, and put objects (unordered_maps) on the heap, in
    // the implementation of value_impl below.
    constexpr int value_buffer_size()
    {
        return (std::max)(sizeof(std::vector<int>), sizeof(std::string));
    }

    template<typename T>
    struct is_map
        : is_range_of<T, std::pair<value, value>, std::pair<value const, value>>
    {
    };

    template<typename T>
    struct is_seq : is_range_of<T, value>
    {
    };

}}}

#endif
