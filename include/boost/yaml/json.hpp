#ifndef BOOST_YAML_JSON_HPP
#define BOOST_YAML_JSON_HPP

#include <boost/yaml/json_fwd.hpp>
#include <boost/yaml/detail/json.hpp>

#include <boost/assert.hpp>
#include <boost/utility/string_view.hpp>

#include <functional>
#include <memory>
#include <optional>


namespace boost { namespace json {

    struct value
    {
        value() = default;

        value(value const & other) { copy_impl(other); }

        value(value && other) { move_impl(std::move(other)); }

        value & operator=(value const & other)
        {
            storage_ = storage();
            copy_impl(other);
            return *this;
        }

        value & operator=(value && other)
        {
            storage_ = storage();
            move_impl(std::move(other));
            return *this;
        }

        template<typename JSONObject>
        value(
            JSONObject const & o,
            typename std::enable_if<detail::is_object<JSONObject>::value>::
                type ** enable = nullptr);

        value(object && o);

        template<typename JSONArray>
        value(
            JSONArray const & a,
            typename std::enable_if<detail::is_array<JSONArray>::value>::type **
                enable = nullptr);

        value(array && a);

        value(double d);

        template<typename String>
        value(
            String const & str,
            typename std::enable_if<detail::is_string<String>::value>::type **
                enable = nullptr);
        value(std::string && str);
        value(std::string_view str);

        value(bool b);

        value(null_t);

        template<typename JSONObject>
        typename std::enable_if<detail::is_object<JSONObject>::value, value &>::
            type
            operator=(JSONObject const & o);

        value & operator=(object && o);

        template<typename JSONArray>
        typename std::enable_if<detail::is_array<JSONArray>::value, value &>::
            type
            operator=(JSONArray const & a);

        value & operator=(array && a);

        value & operator=(double d);

        template<typename String>
        typename std::enable_if<detail::is_string<String>::value, value &>::type
        operator=(String const & str);
        value & operator=(std::string && str);
        value & operator=(std::string_view str);

        value & operator=(bool b);

        value & operator=(null_t);

        value_kind kind() const noexcept
        {
            auto k = storage_.local_.kind_;
            if (k == remote_string_k)
                return value_kind::string;
            return static_cast<value_kind>(k);
        }

        bool is_null() const noexcept { return kind() == value_kind::null; }
        bool is_boolean() const noexcept
        {
            return kind() == value_kind::boolean;
        }
        bool is_number() const noexcept { return kind() == value_kind::number; }
        bool is_string() const noexcept { return kind() == value_kind::string; }
        bool is_object() const noexcept { return kind() == value_kind::object; }
        bool is_array() const noexcept { return kind() == value_kind::array; }

        bool operator==(value const & rhs) const noexcept
        {
            if (rhs.kind() != kind())
                return false;
            switch (storage_.local_.kind_) {
            case value::null_k: return true;
            case value::boolean_k:
                return storage_.local_.bytes_[3] ==
                       rhs.storage_.local_.bytes_[3];
            case value::number_k: return *double_ptr() == *rhs.double_ptr();
            case value::local_string_k:
                return strcmp(
                           storage_.local_.bytes_.data(),
                           rhs.storage_.local_.bytes_.data()) == 0;
            default: return storage_.remote_.ptr_->equal_impl(rhs);
            }
            return false;
        }

        bool operator!=(value const & rhs) const noexcept
        {
            return !(*this == rhs);
        }

        friend std::ostream &
        operator<<(std::ostream & os, value const & value);

    private:
        void copy_impl(value const & other)
        {
            if (other.is_local()) {
                storage_.local_ = other.storage_.local_;
            } else {
                storage_.remote_ = remote{other.storage_.remote_.kind_};
                storage_.remote_.ptr_ =
                    other.storage_.remote_.ptr_->copy_impl();
            }
        }

        void move_impl(value && other)
        {
            if (other.is_local())
                storage_.local_ = other.storage_.local_;
            else
                storage_.remote_ = std::move(other.storage_.remote_);
        }

        bool is_local() const noexcept
        {
            return storage_.local_.kind_ < object_k;
        }

        double const * double_ptr() const noexcept
        {
            double const * retval = reinterpret_cast<double const *>(
                storage_.local_.bytes_.data() + 7);
            BOOST_ASSERT(std::uintptr_t(retval) % alignof(double) == 0);
            return retval;
        }
        double * double_ptr() noexcept
        {
            double * retval =
                reinterpret_cast<double *>(storage_.local_.bytes_.data() + 7);
            BOOST_ASSERT(std::uintptr_t(retval) % alignof(double) == 0);
            return retval;
        }

        enum value_impl_kind {
            null_k,
            boolean_k,
            number_k,
            local_string_k,
            object_k,
            array_k,
            remote_string_k
        };

        struct local
        {
            uint8_t kind_;
            std::array<char, 15> bytes_;
        };
        static_assert(sizeof(local) == 16);
        static_assert(alignof(local::bytes_) == 1);
        struct remote
        {
            uint8_t kind_;
            std::unique_ptr<detail::value_impl_base> ptr_;
        };
        static_assert(sizeof(local) <= 16);
        union storage
        {
            storage() : local_{null_k} {}
            storage & operator=(storage const & other)
            {
                destroy();
                BOOST_ASSERT(other.local_.kind_ < object_k);
                local_ = other.local_;
                return *this;
            }
            ~storage() { destroy(); }

            void destroy() noexcept
            {
                if (local_.kind_ < object_k)
                    local_.~local();
                else
                    remote_.~remote();
            }

            local local_;
            remote remote_;
        };
        storage storage_;

        template<typename T>
        friend struct detail::get_impl;
    };

    static_assert(sizeof(value) == 16);

    using diagnostic_function = std::function<void(std::string const &)>;

    std::optional<value> parse(
        string_view str,
        diagnostic_function errors_callback = diagnostic_function(),
        int max_recursion = 512);

}}

#include <boost/yaml/detail/json_impl.hpp>

namespace boost { namespace json {

    namespace detail {
        template<typename Iter, typename Sentinel, typename CategoryTag>
        std::ptrdiff_t
        fast_distance_or_1000(Iter f, Sentinel l, CategoryTag tag)
        {
            return 1000;
        }

        template<typename Iter>
        std::ptrdiff_t
        fast_distance_or_1000(Iter f, Iter l, std::random_access_iterator_tag)
        {
            return l - f;
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
                BOOST_ASSERT(v.is_object());
                return static_cast<value_impl<object> *>(
                           v.storage_.remote_.ptr_.get())
                    ->value_;
            }
            static object & call(value & v) noexcept
            {
                BOOST_ASSERT(v.is_object());
                return static_cast<value_impl<object> *>(
                           v.storage_.remote_.ptr_.get())
                    ->value_;
            }
        };

        template<>
        struct get_impl<array>
        {
            static array const & call(value const & v) noexcept
            {
                BOOST_ASSERT(v.is_array());
                return static_cast<value_impl<array> *>(
                           v.storage_.remote_.ptr_.get())
                    ->value_;
            }
            static array & call(value & v) noexcept
            {
                BOOST_ASSERT(v.is_array());
                return static_cast<value_impl<array> *>(
                           v.storage_.remote_.ptr_.get())
                    ->value_;
            }
        };

        template<>
        struct get_impl<double>
        {
            static double call(value const & v) noexcept
            {
                BOOST_ASSERT(v.is_number());
                return *v.double_ptr();
            }
        };

        template<>
        struct get_impl<std::string_view>
        {
            static std::string_view call(value const & v) noexcept
            {
                BOOST_ASSERT(v.is_string());
                if (v.storage_.local_.kind_ == value::local_string_k) {
                    return std::string_view(v.storage_.local_.bytes_.data());
                } else {
                    return static_cast<value_impl<std::string> *>(
                               v.storage_.remote_.ptr_.get())
                        ->value_;
                }
            }
        };

        template<>
        struct get_impl<bool>
        {
            static bool call(value const & v) noexcept
            {
                BOOST_ASSERT(v.is_boolean());
                return v.storage_.local_.bytes_[3];
            }
        };

        template<>
        struct get_impl<null_t>
        {
            static null_t call(value const & v) noexcept
            {
                BOOST_ASSERT(v.is_null());
                return {};
            }
        };
    }

    template<typename T>
    detail::get_result_t<T, true> get(value const & v) noexcept
    {
        return detail::get_impl<T>::call(v);
    }

    template<typename T>
    detail::get_result_t<T, false> get(value & v) noexcept
    {
        return detail::get_impl<T>::call(v);
    }

    template<typename JSONObject>
    value::value(
        JSONObject const & o,
        typename std::enable_if<detail::is_object<JSONObject>::value>::type **
            enable)
    {
        storage_.remote_ = remote{
            object_k,
            std::make_unique<detail::value_impl<object>>(o.begin(), o.end())};
    }

    inline value::value(object && o)
    {
        storage_.remote_ =
            remote{object_k,
                   std::make_unique<detail::value_impl<object>>(std::move(o))};
    }

    template<typename JSONArray>
    value::value(
        JSONArray const & a,
        typename std::enable_if<detail::is_array<JSONArray>::value>::type **
            enable)
    {
        storage_.remote_ = remote{
            array_k,
            std::make_unique<detail::value_impl<array>>(a.begin(), a.end())};
    }

    inline value::value(array && a)
    {
        storage_.remote_ = remote{
            array_k, std::make_unique<detail::value_impl<array>>(std::move(a))};
    }

    inline value::value(double d)
    {
        storage_.local_ = local{number_k};
        *double_ptr() = d;
    }

    template<typename String>
    value::value(
        String const & str,
        typename std::enable_if<detail::is_string<String>::value>::type **
            enable)
    {
        auto const f = std::begin(str);
        auto const l = std::end(str);
        typename std::iterator_traits<decltype(f)>::iterator_category tag;
        if (detail::fast_distance_or_1000(f, l, tag) <= 14) {
            storage_.local_ = local{local_string_k};
            *std::copy(f, l, storage_.local_.bytes_.data()) = 0;
        } else {
            storage_.remote_ = remote{remote_string_k};
            storage_.remote_.ptr_ =
                std::make_unique<detail::value_impl<std::string>>(f, l);
        }
    }

    inline value::value(std::string && s)
    {
        auto const f = std::begin(s);
        auto const l = std::end(s);
        typename std::iterator_traits<decltype(f)>::iterator_category tag;
        if (detail::fast_distance_or_1000(f, l, tag) <= 14) {
            storage_.local_ = local{local_string_k};
            *std::copy(f, l, storage_.local_.bytes_.data()) = 0;
        } else {
            storage_.remote_ = remote{remote_string_k};
            storage_.remote_.ptr_ =
                std::make_unique<detail::value_impl<std::string>>(std::move(s));
        }
    }

    inline value::value(std::string_view s)
    {
        auto const f = std::begin(s);
        auto const l = std::end(s);
        if (l - f <= 14) {
            storage_.local_ = local{local_string_k};
            *std::copy(f, l, storage_.local_.bytes_.data()) = 0;
        } else {
            storage_.remote_ = remote{remote_string_k};
            storage_.remote_.ptr_ =
                std::make_unique<detail::value_impl<std::string>>(s);
        }
    }

    inline value::value(bool b)
    {
        storage_.local_ = local{boolean_k, {{0, 0, 0, b}}};
    }

    inline value::value(null_t) : value() {}

    template<typename JSONObject>
    typename std::enable_if<detail::is_object<JSONObject>::value, value &>::type
    value::operator=(JSONObject const & o)
    {
        if (is_object()) {
            get<object>(*this) = object(o.begin(), o.end());
            return *this;
        }
        return *this = value(o);
    }

    inline value & value::operator=(object && o)
    {
        if (is_object()) {
            get<object>(*this) = std::move(o);
            return *this;
        }
        return *this = value(o);
    }

    template<typename JSONArray>
    typename std::enable_if<detail::is_array<JSONArray>::value, value &>::type
    value::operator=(JSONArray const & a)
    {
        if (is_array()) {
            get<array>(*this).assign(a.begin(), a.end());
            return *this;
        }
        return *this = value(a);
    }

    inline value & value::operator=(array && a)
    {
        if (is_array()) {
            get<array>(*this) = std::move(a);
            return *this;
        }
        return *this = value(a);
    }

    inline value & value::operator=(double d) { return *this = value(d); }

    template<typename String>
    typename std::enable_if<detail::is_string<String>::value, value &>::type
    value::operator=(String const & str)
    {
        if (is_string()) {
            auto const f = std::begin(str);
            auto const l = std::end(str);
            typename std::iterator_traits<decltype(f)>::iterator_category tag;
            if (is_local() && detail::fast_distance_or_1000(f, l, tag) <= 14) {
                *std::copy(f, l, storage_.local_.bytes_.data()) = 0;
            } else {
                return static_cast<detail::value_impl<std::string> *>(
                           storage_.remote_.ptr_.get())
                    ->value_.assign(f, l);
            }
            return *this;
        }
        return *this = value(str);
    }

    inline value & value::operator=(std::string && s)
    {
        if (is_string()) {
            if (is_local() && s.size() <= 14u) {
                *std::copy(
                    s.begin(), s.end(), storage_.local_.bytes_.data()) = 0;
            } else {
                static_cast<detail::value_impl<std::string> *>(
                    storage_.remote_.ptr_.get())
                    ->value_ = std::move(s);
            }
            return *this;
        }
        return *this = value(std::move(s));
    }

    inline value & value::operator=(std::string_view s)
    {
        if (is_string()) {
            if (is_local() && s.size() <= 14u) {
                *std::copy(s.begin(), s.end(), storage_.local_.bytes_.data()) =
                    0;
            } else {
                static_cast<detail::value_impl<std::string> *>(
                    storage_.remote_.ptr_.get())
                    ->value_ = s;
            }
            return *this;
        }
        return *this = value(s);
    }

    inline value & value::operator=(bool b) { return *this = value(b); }

    inline value & value::operator=(null_t n) { return *this = value(n); }

    inline std::ostream & operator<<(std::ostream & os, value const & value)
    {
        switch (value.storage_.local_.kind_) {
        case value::null_k: return os << "null";
        case value::boolean_k:
            return os << (value.storage_.local_.bytes_[3] ? "true" : "false");
        case value::number_k: return os << *value.double_ptr();
        case value::local_string_k:
            return detail::to_json(os, value.storage_.local_.bytes_.data());
        default: return value.storage_.remote_.ptr_->to_json(os);
        }
        return os;
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
                kind_hash,
                std::hash<std::string_view>{}(get<std::string_view>(v)));
        case value_kind::boolean:
            return hash_combine_(kind_hash, std::hash<bool>{}(get<bool>(v)));
        case value_kind::null: return kind_hash;
        }

        BOOST_ASSERT(!"Unreachable");
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
