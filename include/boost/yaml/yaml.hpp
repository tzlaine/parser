#ifndef BOOST_YAML_YAML_HPP
#define BOOST_YAML_YAML_HPP

#include <boost/yaml/yaml_fwd.hpp>
#include <boost/yaml/detail/yaml.hpp>

#include <boost/optional.hpp>
#include <boost/utility/string_view.hpp>


namespace boost { namespace yaml {

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

        template<typename YAMLMap>
        value(
            YAMLMap const & m,
            typename std::enable_if<detail::is_map<YAMLMap>::value>::type **
                enable = nullptr);

        template<typename YAMLSeq>
        value(
            YAMLSeq const & s,
            typename std::enable_if<detail::is_seq<YAMLSeq>::value>::type **
                enable = nullptr);

        value(double d);

        value(int i);

        template<typename String>
        value(
            String const & str,
            typename std::enable_if<detail::is_string<String>::value>::type **
                enable = nullptr);
        value(std::string && str);
        value(char const * c_str);

        value(bool b);

        value(null_t);

        value(alias a);

        value(property_node pn);

        // TODO: Document that YAMLUserDefined must be copyable, and that
        // std::ostream & to_yaml(std::ostream & os, YAMLUserDefined const &),
        // bool operator==(YAMLUserDefined const &, YAMLUserDefined const &),
        // and std::size_t hash(T const & x) must exist.

        // user_defined
        template<typename YAMLUserDefined>
        value(
            YAMLUserDefined x,
            typename std::enable_if<
                !detail::is_map<YAMLUserDefined>::value &&
                !detail::is_seq<YAMLUserDefined>::value &&
                !detail::is_string<YAMLUserDefined>::value>::type ** enable =
                nullptr);

        template<typename YAMLMap>
        typename std::enable_if<detail::is_map<YAMLMap>::value, value &>::type
        operator=(YAMLMap const & m);

        template<typename YAMLSeq>
        typename std::enable_if<detail::is_seq<YAMLSeq>::value, value &>::type
        operator=(YAMLSeq const & s);

        value & operator=(double d);

        template<typename String>
        typename std::enable_if<detail::is_string<String>::value, value &>::type
        operator=(String const & str);
        value & operator=(std::string && str);
        value & operator=(char const * c_str);

        value & operator=(bool b);

        value & operator=(null_t);

        // alias
        value & operator=(alias a);

        // property_node
        value & operator=(property_node pn);

        // user_defined
        template<typename YAMLUserDefined>
        typename std::enable_if<
            !detail::is_map<YAMLUserDefined>::value &&
                !detail::is_seq<YAMLUserDefined>::value &&
                !detail::is_string<YAMLUserDefined>::value,
            value &>::type
        operator=(YAMLUserDefined x);

        value_kind kind() const noexcept { return ptr_->kind(); }

        bool is_map() const noexcept { return ptr_->kind() == value_kind::map; }

        bool is_seq() const noexcept { return ptr_->kind() == value_kind::seq; }

        bool is_double() const noexcept
        {
            return ptr_->kind() == value_kind::double_;
        }

        bool is_int() const noexcept
        {
            return ptr_->kind() == value_kind::int_;
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

        bool is_alias() const noexcept
        {
            return ptr_->kind() == value_kind::alias;
        }

        bool is_property_node() const noexcept
        {
            return ptr_->kind() == value_kind::property_node;
        }

        bool is_user_defined() const noexcept
        {
            return ptr_->kind() == value_kind::user_defined;
        }

        template<typename T>
        bool is() const noexcept
        {
            return ptr_->type_id() == typeindex::type_id<T>();
        }

        bool operator==(value const & rhs) const noexcept
        {
            auto const this_kind = kind();
            if (rhs.kind() != this_kind)
                return false;
            if (this_kind == value_kind::user_defined &&
                ptr_->type_id() != rhs.ptr_->type_id()) {
                return false;
            }
            return ptr_->equal_impl(rhs);
        }

        bool operator!=(value const & rhs) const noexcept
        {
            return !(*this == rhs);
        }

        friend std::ostream & operator<<(std::ostream & os, value const & value)
        {
            return value.ptr_->to_yaml_impl(os);
        }

    private:
        std::unique_ptr<detail::value_impl_base> ptr_;

        template<typename T>
        friend struct detail::get_impl;

        friend std::size_t hash_append(std::size_t seed, value const & v);
    };

    using error_function = std::function<void(std::string const &)>;

    optional<value> parse(
        string_view const & str,
        error_function parse_error = error_function(),
        int max_recursive_count = 512);

}}

#include <boost/yaml/detail/yaml_impl.hpp>

namespace boost { namespace yaml {

    inline value::value() { *this = null_t{}; }

    template<typename YAMLMap>
    value::value(
        YAMLMap const & m,
        typename std::enable_if<detail::is_map<YAMLMap>::value>::type **
            enable) :
        ptr_(new detail::value_impl<map>(m.begin(), m.end()))
    {}

    template<typename YAMLSeq>
    value::value(
        YAMLSeq const & s,
        typename std::enable_if<detail::is_seq<YAMLSeq>::value>::type **
            enable) :
        ptr_(new detail::value_impl<seq>(s.begin(), s.end()))
    {}

    inline value::value(double d) : ptr_(new detail::value_impl<double>(d)) {}

    inline value::value(int i) : ptr_(new detail::value_impl<int>{i}) {}

    template<typename String>
    value::value(
        String const & str,
        typename std::enable_if<detail::is_string<String>::value>::type **
            enable) :
        value(std::string(std::begin(str), std::end(str)))
    {}

    inline value::value(std::string && str) :
        ptr_(new detail::value_impl<std::string>{std::move(str)})
    {}

    inline value::value(char const * c_str) : value(std::string(c_str)) {}

    inline value::value(bool b) : ptr_(new detail::value_impl<bool>(b)) {}

    inline value::value(null_t) : ptr_(new detail::value_impl<null_t>) {}

    inline value::value(alias a) :
        ptr_(new detail::value_impl<alias>(std::move(a)))
    {}

    inline value::value(property_node pn) :
        ptr_(new detail::value_impl<property_node>(std::move(pn)))
    {}

    // user_defined
    template<typename T>
    value::value(
        T x,
        typename std::enable_if<
            !detail::is_map<T>::value && !detail::is_seq<T>::value &&
            !detail::is_string<T>::value>::type ** enable) :
        ptr_(new detail::value_impl<T>(std::move(x)))
    {}

    template<typename YAMLMap>
    typename std::enable_if<detail::is_map<YAMLMap>::value, value &>::type
    value::operator=(YAMLMap const & m)
    {
        return *this = value(m);
    }

    template<typename YAMLSeq>
    typename std::enable_if<detail::is_seq<YAMLSeq>::value, value &>::type
    value::operator=(YAMLSeq const & s)
    {
        return *this = value(s);
    }

    inline value & value::operator=(double d) { return *this = value(d); }

    template<typename String>
    typename std::enable_if<detail::is_string<String>::value, value &>::type
    value::operator=(String const & str)
    {
        return *this = value(std::string(std::begin(str), std::end(str)));
    }

    inline value & value::operator=(std::string && str)
    {
        return *this = value(std::move(str));
    }

    inline value & value::operator=(char const * c_str)
    {
        return *this = value(std::string(c_str));
    }

    inline value & value::operator=(bool b) { return *this = value(b); }

    inline value & value::operator=(null_t) { return *this = value(null_t{}); }

    inline value & value::operator=(alias a)
    {
        return *this = value(std::move(a));
    }

    inline value & value::operator=(property_node pn)
    {
        return *this = value(std::move(pn));
    }

    // user_defined
    template<typename T>
    typename std::enable_if<
        !detail::is_map<T>::value && !detail::is_seq<T>::value &&
            !detail::is_string<T>::value,
        value &>::type
    value::operator=(T x)
    {
        return *this = value(std::move(x));
    }

    namespace detail {

        inline std::ostream &
        value_impl<map>::to_yaml_impl(std::ostream & os) const noexcept
        {
            // TODO: Indentation; also too simplistic.
            os << '{';
            bool first = true;
            for (auto const & pair : value_) {
                if (!first)
                    os << ", ";
                os << pair.first << ": " << pair.second;
                first = false;
            }
            os << '}';
            return os;
        }

        inline std::ostream &
        value_impl<seq>::to_yaml_impl(std::ostream & os) const noexcept
        {
            // TODO: Indentation; also too simplistic.
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

        inline std::ostream &
        value_impl<alias>::to_yaml_impl(std::ostream & os) const noexcept
        {
            // TODO
            return os;
        }

        inline std::ostream &
        value_impl<property_node>::to_yaml_impl(std::ostream & os) const
            noexcept
        {
            // TODO
            return os;
        }

        template<typename T>
        struct get_impl
        {
            static T const & call(value const & v) noexcept
            {
                assert(v.is_user_defined());
                assert(v.ptr_->type_id() == typeindex::type_id<T>());
                return static_cast<value_impl<T> *>(v.ptr_.get())->value_;
            }
            static bool & call(value & v) noexcept
            {
                assert(v.is_user_defined());
                assert(v.ptr_->type_id() == typeindex::type_id<T>());
                return static_cast<value_impl<T> *>(v.ptr_.get())->value_;
            }
        };

        template<>
        struct get_impl<map>
        {
            static map const & call(value const & v) noexcept
            {
                assert(v.is_map());
                return static_cast<value_impl<map> *>(v.ptr_.get())->value_;
            }
            static map & call(value & v) noexcept
            {
                assert(v.is_map());
                return static_cast<value_impl<map> *>(v.ptr_.get())->value_;
            }
        };

        template<>
        struct get_impl<seq>
        {
            static seq const & call(value const & v) noexcept
            {
                assert(v.is_seq());
                return static_cast<value_impl<seq> *>(v.ptr_.get())->value_;
            }
            static seq & call(value & v) noexcept
            {
                assert(v.is_seq());
                return static_cast<value_impl<seq> *>(v.ptr_.get())->value_;
            }
        };

        template<>
        struct get_impl<double>
        {
            static double const & call(value const & v) noexcept
            {
                assert(v.is_double());
                return static_cast<value_impl<double> *>(v.ptr_.get())->value_;
            }
            static double & call(value & v) noexcept
            {
                assert(v.is_double());
                return static_cast<value_impl<double> *>(v.ptr_.get())->value_;
            }
        };

        template<>
        struct get_impl<int>
        {
            static int const & call(value const & v) noexcept
            {
                assert(v.is_int());
                return static_cast<value_impl<int> *>(v.ptr_.get())->value_;
            }
            static int & call(value & v) noexcept
            {
                assert(v.is_int());
                return static_cast<value_impl<int> *>(v.ptr_.get())->value_;
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

        template<>
        struct get_impl<alias>
        {
            static alias const & call(value const & v) noexcept
            {
                assert(v.is_alias());
                return static_cast<value_impl<alias> *>(v.ptr_.get())->value_;
            }
            static alias & call(value & v) noexcept
            {
                assert(v.is_alias());
                return static_cast<value_impl<alias> *>(v.ptr_.get())->value_;
            }
        };

        template<>
        struct get_impl<property_node>
        {
            static property_node const & call(value const & v) noexcept
            {
                assert(v.is_property_node());
                return static_cast<value_impl<property_node> *>(v.ptr_.get())
                    ->value_;
            }
            static property_node & call(value & v) noexcept
            {
                assert(v.is_property_node());
                return static_cast<value_impl<property_node> *>(v.ptr_.get())
                    ->value_;
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

        std::size_t const kind_hash =
            hash_combine_(seed, std::hash<size_t>{}(size_t(v.kind())));
        switch (v.kind()) {
        case value_kind::map: return hash_append(kind_hash, get<map>(v));
        case value_kind::seq: return hash_append(kind_hash, get<seq>(v));
        case value_kind::double_:
            return hash_combine_(
                kind_hash, std::hash<double>{}(get<double>(v)));
        case value_kind::int_:
            return hash_combine_(kind_hash, std::hash<int>{}(get<int>(v)));
        case value_kind::string:
            return hash_combine_(
                kind_hash, std::hash<std::string>{}(get<std::string>(v)));
        case value_kind::boolean:
            return hash_combine_(kind_hash, std::hash<bool>{}(get<bool>(v)));
        case value_kind::null: return kind_hash;
        case value_kind::alias: return hash_append(kind_hash, get<alias>(v));
        case value_kind::property_node:
            return hash_append(kind_hash, get<property_node>(v));
        case value_kind::user_defined: return v.ptr_->hash_append_impl(seed);
        }

        assert(!"Unreachable");
        return 0;
    }

    inline std::size_t hash_append(std::size_t seed, map const & m)
    {
        using detail::hash_combine_;
        auto retval = seed;
        for (auto const & pair : m) {
            retval = hash_append(retval, pair.first);
            retval = hash_append(retval, pair.second);
        }
        return retval;
    }

    inline std::size_t hash_append(std::size_t seed, seq const & s)
    {
        using detail::hash_combine_;
        auto retval = seed;
        for (auto const & value : s) {
            retval = hash_append(retval, value);
        }
        return retval;
    }

    inline std::size_t hash_append(std::size_t seed, alias const & a)
    {
        using detail::hash_combine_;
        auto const alias_ = get<alias>(a);
        auto retval =
            hash_combine_(seed, std::hash<std::string>{}(alias_.first));
        return hash_append(retval, *alias_.second);
    }

    inline std::size_t hash_append(std::size_t seed, property_node const & pn)
    {
        using detail::hash_combine_;
        auto const property_node_ = get<property_node>(pn);
        std::hash<std::string> const str_hash;
        auto retval = hash_combine_(seed, str_hash(property_node_.first.tag_));
        retval = hash_combine_(retval, str_hash(property_node_.first.anchor_));
        return hash_append(retval, property_node_.second);
    }

}}

namespace std {
    inline size_t hash<boost::yaml::value>::
    operator()(argument_type const & v) const noexcept
    {
        return boost::yaml::hash_append(0, v);
    }

    inline size_t hash<boost::yaml::map>::
    operator()(argument_type const & m) const noexcept
    {
        return boost::yaml::hash_append(0, m);
    }

    inline size_t hash<boost::yaml::seq>::
    operator()(argument_type const & s) const noexcept
    {
        return boost::yaml::hash_append(0, s);
    }

    inline size_t hash<boost::yaml::alias>::
    operator()(argument_type const & a) const noexcept
    {
        return boost::yaml::hash_append(0, a);
    }

    inline size_t hash<boost::yaml::property_node>::
    operator()(argument_type const & pn) const noexcept
    {
        return boost::yaml::hash_append(0, pn);
    }
}

#endif
