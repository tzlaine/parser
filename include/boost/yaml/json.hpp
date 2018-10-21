#ifndef BOOST_YAML_JSON_HPP
#define BOOST_YAML_JSON_HPP

#include <boost/yaml/json_fwd.hpp>
#include <boost/yaml/detail/json.hpp>

#include <boost/optional.hpp>
#include <boost/utility/string_view.hpp>

#include <memory>


namespace boost { namespace json {

    struct value
    {
        value();

        value(value const & other)
        {
            if (other.ptr_)
                ptr_ = other.ptr_->copy_impl();
        }

        value & operator=(value const & other)
        {
            ptr_.reset();
            if (other.ptr_)
                ptr_ = other.ptr_->copy_impl();
            return *this;
        }

        template<typename JSONObject>
        value(
            JSONObject const & o,
            typename std::enable_if<detail::is_object<JSONObject>::value>::
                type ** enable = nullptr);

        template<typename JSONArray>
        value(
            JSONArray const & a,
            typename std::enable_if<detail::is_array<JSONArray>::value>::type **
                enable = nullptr);

        value(double d);

        template<typename String>
        value(
            String const & str,
            typename std::enable_if<detail::is_string<String>::value>::type **
                enable = nullptr);
        value(std::string && str);
        value(char const * c_str);

        value(bool b);

        value(null_t);

        template<typename JSONObject>
        typename std::enable_if<detail::is_object<JSONObject>::value, value &>::
            type
            operator=(JSONObject const & o);

        template<typename JSONArray>
        typename std::enable_if<detail::is_array<JSONArray>::value, value &>::
            type
            operator=(JSONArray const & a);

        value & operator=(double d);

        template<typename String>
        typename std::enable_if<detail::is_string<String>::value, value &>::type
        operator=(String const & str);
        value & operator=(std::string && str);
        value & operator=(char const * c_str);

        value & operator=(bool b);

        value & operator=(null_t);

        value_kind kind() const noexcept { return ptr_->kind(); }

        bool is_object() const noexcept
        {
            return ptr_->kind() == value_kind::object;
        }

        bool is_array() const noexcept
        {
            return ptr_->kind() == value_kind::array;
        }

        bool is_number() const noexcept
        {
            return ptr_->kind() == value_kind::number;
        }

        bool is_string() const noexcept
        {
            return ptr_->kind() == value_kind::string;
        }

        bool is_boolean() const noexcept
        {
            return ptr_->kind() == value_kind::boolean;
        }

        bool is_null() const noexcept
        {
            return ptr_->kind() == value_kind::null;
        }

        bool operator==(value const & rhs) const noexcept
        {
            if (rhs.kind() != kind())
                return false;
            return ptr_->equal_impl(rhs);
        }

        bool operator!=(value const & rhs) const noexcept
        {
            return !(*this == rhs);
        }

        friend std::ostream & operator<<(std::ostream & os, value const & value)
        {
            return value.ptr_->to_json(os);
        }

    private:
        std::unique_ptr<detail::value_impl_base> ptr_;

        template<typename T>
        friend struct detail::get_impl;
    };

    using error_function = std::function<void(std::string const &)>;

    optional<value> parse(
        string_view str,
        error_function parse_error = error_function(),
        int max_recursion = 512);

}}

#include <boost/yaml/detail/json_impl.hpp>

namespace boost { namespace json {

    inline value::value() { *this = null_t{}; }

    template<typename JSONObject>
    value::value(
        JSONObject const & o,
        typename std::enable_if<detail::is_object<JSONObject>::value>::type **
            enable) :
        ptr_(new detail::value_impl<object>(o.begin(), o.end()))
    {}

    template<typename JSONArray>
    value::value(
        JSONArray const & a,
        typename std::enable_if<detail::is_array<JSONArray>::value>::type **
            enable) :
        ptr_(new detail::value_impl<array>(a.begin(), a.end()))
    {}

    inline value::value(double d) : ptr_(new detail::value_impl<double>(d)) {}

    template<typename String>
    value::value(
        String const & str,
        typename std::enable_if<detail::is_string<String>::value>::type **
            enable) :
        value(std::string(std::begin(str), std::end(str)))
    {}

    inline value::value(std::string && s) :
        ptr_(new detail::value_impl<std::string>{std::move(s)})
    {}

    inline value::value(char const * c_str) : value(std::string(c_str)) {}

    inline value::value(bool b) : ptr_(new detail::value_impl<bool>(b)) {}

    inline value::value(null_t) : ptr_(new detail::value_impl<null_t>) {}

    template<typename JSONObject>
    typename std::enable_if<detail::is_object<JSONObject>::value, value &>::type
    value::operator=(JSONObject const & o)
    {
        return *this = value(o);
    }

    template<typename JSONArray>
    typename std::enable_if<detail::is_array<JSONArray>::value, value &>::type
    value::operator=(JSONArray const & a)
    {
        return *this = value(a);
    }

    inline value & value::operator=(double d) { return *this = value(d); }

    template<typename String>
    typename std::enable_if<detail::is_string<String>::value, value &>::type
    value::operator=(String const & str)
    {
        return *this = value(std::string(std::begin(str), std::end(str)));
    }

    inline value & value::operator=(std::string && s)
    {
        return *this = value(std::move(s));
    }

    inline value & value::operator=(char const * c_str)
    {
        return *this = value(std::string(c_str));
    }

    inline value & value::operator=(bool b) { return *this = value(b); }

    inline value & value::operator=(null_t) { return *this = value(null_t{}); }

    namespace detail {

        inline std::ostream &
        value_impl<object>::to_json(std::ostream & os) const noexcept
        {
            // TODO: Indentation.
            os << '{';
            bool first = true;
            for (auto const & pair : value_) {
                if (!first)
                    os << ", ";
                os << '"' << pair.first << "\": " << pair.second;
                first = false;
            }
            os << '}';
            return os;
        }

        inline std::ostream &
        value_impl<array>::to_json(std::ostream & os) const noexcept
        {
            // TODO: Indentation.
            os << '[';
            bool first = true;
            for (auto const & value : value_) {
                if (!first)
                    os << ", ";
                os << value;
                first = false;
            }
            os << ']';
            return os;
        }

        template<>
        struct get_impl<object>
        {
            static object const & call(value const & v) noexcept
            {
                assert(v.is_object());
                return static_cast<value_impl<object> *>(v.ptr_.get())->value_;
            }
            static object & call(value & v) noexcept
            {
                assert(v.is_object());
                return static_cast<value_impl<object> *>(v.ptr_.get())->value_;
            }
        };

        template<>
        struct get_impl<array>
        {
            static array const & call(value const & v) noexcept
            {
                assert(v.is_array());
                return static_cast<value_impl<array> *>(v.ptr_.get())->value_;
            }
            static array & call(value & v) noexcept
            {
                assert(v.is_array());
                return static_cast<value_impl<array> *>(v.ptr_.get())->value_;
            }
        };

        template<>
        struct get_impl<double>
        {
            static double const & call(value const & v) noexcept
            {
                assert(v.is_number());
                return static_cast<value_impl<double> *>(v.ptr_.get())->value_;
            }
            static double & call(value & v) noexcept
            {
                assert(v.is_number());
                return static_cast<value_impl<double> *>(v.ptr_.get())->value_;
            }
        };

        template<>
        struct get_impl<std::string>
        {
            static std::string const & call(value const & v) noexcept
            {
                assert(v.is_string());
                return static_cast<value_impl<std::string> *>(v.ptr_.get())
                    ->value_;
            }
            static std::string & call(value & v) noexcept
            {
                assert(v.is_string());
                return static_cast<value_impl<std::string> *>(v.ptr_.get())
                    ->value_;
            }
        };

        template<>
        struct get_impl<bool>
        {
            static bool const & call(value const & v) noexcept
            {
                assert(v.is_boolean());
                return static_cast<value_impl<bool> *>(v.ptr_.get())->value_;
            }
            static bool & call(value & v) noexcept
            {
                assert(v.is_boolean());
                return static_cast<value_impl<bool> *>(v.ptr_.get())->value_;
            }
        };

        template<>
        struct get_impl<null_t>
        {
            static null_t const & call(value const & v) noexcept
            {
                assert(v.is_null());
                return static_cast<value_impl<null_t> *>(v.ptr_.get())->value_;
            }
            static null_t & call(value & v) noexcept
            {
                assert(v.is_null());
                return static_cast<value_impl<null_t> *>(v.ptr_.get())->value_;
            }
        };
    }

    template<typename T>
    T const & get(value const & v) noexcept
    {
        return detail::get_impl<T>::call(v);
    }

    template<typename T>
    T & get(value & v) noexcept
    {
        return detail::get_impl<T>::call(v);
    }

    inline std::size_t hash_append(std::size_t seed, value const & v)
    {
        using detail::hash_combine_;

        std::size_t const kind_hash = std::hash<size_t>{}(size_t(v.kind()));
        switch (v.kind()) {
        case value_kind::object: return hash_append(kind_hash, get<object>(v));
        case value_kind::array: return hash_append(kind_hash, get<array>(v));
        case value_kind::number:
            return hash_combine_(
                kind_hash, std::hash<double>{}(get<double>(v)));
        case value_kind::string:
            return hash_combine_(
                kind_hash, std::hash<std::string>{}(get<std::string>(v)));
        case value_kind::boolean:
            return hash_combine_(kind_hash, std::hash<bool>{}(get<bool>(v)));
        case value_kind::null: return kind_hash;
        }

        assert(!"Unreachable");
        return 0;
    }

    inline std::size_t hash_append(std::size_t seed, object const & o)
    {
        using detail::hash_combine_;
        std::size_t retval = std::hash<size_t>{}(size_t(value_kind::object));
        for (auto const & pair : o) {
            retval =
                hash_combine_(retval, std::hash<std::string>{}(pair.first));
            retval = hash_append(retval, pair.second);
        }
        return retval;
    }

    inline std::size_t hash_append(std::size_t seed, array const & a)
    {
        std::size_t retval =
            std::hash<size_t>{}(std::size_t(value_kind::array));
        for (auto const & value : a) {
            retval = hash_append(retval, value);
        }
        return retval;
    }

}}

namespace std {
    size_t hash<boost::json::value>::operator()(argument_type const & v) const
        noexcept
    {
        return boost::json::hash_append(0, v);
    }

    size_t hash<boost::json::object>::operator()(argument_type const & o) const
        noexcept
    {
        return boost::json::hash_append(0, o);
    }

    size_t hash<boost::json::array>::operator()(argument_type const & a) const
        noexcept
    {
        return boost::json::hash_append(0, a);
    }
}

#endif
