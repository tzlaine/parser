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

        template<typename T>
        friend T const & get(value const & v) noexcept;
        template<typename T>
        friend T & get(value & v) noexcept;

        friend std::ostream & operator<<(std::ostream & os, value const & value)
        {
            return value.ptr_->to_json(os);
        }

    private:
        std::unique_ptr<detail::value_impl_base> ptr_;
    };

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

    inline value::value(std::string && s) :
        ptr_(new detail::value_impl<std::string>{std::move(s)})
    {}

    inline value::value(char const * c_str) : value(std::string(c_str)) {}

    template<typename String>
    value::value(
        String const & str,
        typename std::enable_if<detail::is_string<String>::value>::type **
            enable) :
        value(std::string(std::begin(str), std::end(str)))
    {}

    inline value::value(bool b) : ptr_(new detail::value_impl<bool>(b)) {}

    inline value::value(null_t) : ptr_(new detail::value_impl<null_t>) {}

    template<typename JSONObject>
    typename std::enable_if<detail::is_object<JSONObject>::value, value &>::type
    value::operator=(JSONObject const & object)
    {
        return *this = value(object);
    }

    template<typename JSONArray>
    typename std::enable_if<detail::is_array<JSONArray>::value, value &>::type
    value::operator=(JSONArray const & object)
    {
        return *this = value(object);
    }

    inline value & value::operator=(double d) { return *this = value(d); }

    inline value & value::operator=(std::string && s)
    {
        return *this = value(std::move(s));
    }

    inline value & value::operator=(char const * c_str)
    {
        return *this = value(std::string(c_str));
    }

    template<typename String>
    typename std::enable_if<detail::is_string<String>::value, value &>::type
    value::operator=(String const & str)
    {
        return *this = value(std::string(std::begin(str), std::end(str)));
    }

    inline value & value::operator=(bool b) { return *this = value(b); }

    inline value & value::operator=(null_t) { return *this = value(null_t{}); }

    template<>
    inline object const & get<object>(value const & v) noexcept
    {
        assert(v.is_object());
        return static_cast<detail::value_impl<object> *>(v.ptr_.get())->value_;
    }

    template<>
    inline array const & get<array>(value const & v) noexcept
    {
        assert(v.is_array());
        return static_cast<detail::value_impl<array> *>(v.ptr_.get())->value_;
    }

    template<>
    inline double const & get<double>(value const & v) noexcept
    {
        assert(v.is_number());
        return static_cast<detail::value_impl<double> *>(v.ptr_.get())->value_;
    }

    template<>
    inline std::string const & get<std::string>(value const & v) noexcept
    {
        assert(v.is_string());
        return static_cast<detail::value_impl<std::string> *>(v.ptr_.get())
            ->value_;
    }

    template<>
    inline bool const & get<bool>(value const & v) noexcept
    {
        assert(v.is_boolean());
        return static_cast<detail::value_impl<bool> *>(v.ptr_.get())->value_;
    }

    template<>
    inline null_t const & get<null_t>(value const & v) noexcept
    {
        assert(v.is_null());
        return static_cast<detail::value_impl<null_t> *>(v.ptr_.get())->value_;
    }

    template<>
    inline object & get<object>(value & v) noexcept
    {
        assert(v.is_object());
        return static_cast<detail::value_impl<object> *>(v.ptr_.get())->value_;
    }

    template<>
    inline array & get<array>(value & v) noexcept
    {
        assert(v.is_array());
        return static_cast<detail::value_impl<array> *>(v.ptr_.get())->value_;
    }

    template<>
    inline double & get<double>(value & v) noexcept
    {
        assert(v.is_number());
        return static_cast<detail::value_impl<double> *>(v.ptr_.get())->value_;
    }

    template<>
    inline std::string & get<std::string>(value & v) noexcept
    {
        assert(v.is_string());
        return static_cast<detail::value_impl<std::string> *>(v.ptr_.get())
            ->value_;
    }

    template<>
    inline bool & get<bool>(value & v) noexcept
    {
        assert(v.is_boolean());
        return static_cast<detail::value_impl<bool> *>(v.ptr_.get())->value_;
    }

    template<>
    inline null_t & get<null_t>(value & v) noexcept
    {
        assert(v.is_null());
        return static_cast<detail::value_impl<null_t> *>(v.ptr_.get())->value_;
    }

    boost::optional<value> parse(
        boost::string_view const & str,
        std::function<void(std::string const &)> parse_error,
        int max_recursive_count = 512);

    namespace detail {

        inline bool value_impl<object>::equal_impl(value const & rhs) const noexcept
        {
            return value_ == get<object>(rhs);
        }

        inline bool value_impl<array>::equal_impl(value const & rhs) const noexcept
        {
            return value_ == get<array>(rhs);
        }

        inline bool value_impl<double>::equal_impl(value const & rhs) const noexcept
        {
            return value_ == get<double>(rhs);
        }

        inline bool value_impl<std::string>::equal_impl(value const & rhs) const noexcept
        {
            return value_ == get<std::string>(rhs);
        }

        inline bool value_impl<bool>::equal_impl(value const & rhs) const noexcept
        {
            return value_ == get<bool>(rhs);
        }

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

        std::ostream & value_impl<array>::to_json(std::ostream & os) const
            noexcept
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
    }

}}

#endif
