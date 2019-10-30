#ifndef BOOST_YAML_YAML_HPP
#define BOOST_YAML_YAML_HPP

#include <boost/yaml/yaml_fwd.hpp>
#include <boost/yaml/detail/yaml.hpp>

#include <boost/optional.hpp>
#include <boost/utility/string_view.hpp>


namespace boost { namespace yaml {

    // TODO: Needs tests.
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

        template<typename YAMLMap>
        value(
            YAMLMap const & m,
            typename std::enable_if<detail::is_map<YAMLMap>::value>::type **
                enable = nullptr);

        value(map && m);

        template<typename YAMLSeq>
        value(
            YAMLSeq const & s,
            typename std::enable_if<detail::is_seq<YAMLSeq>::value>::type **
                enable = nullptr);

        value(seq && s);

        value(double d);

        value(int i);

        template<typename String>
        value(
            String const & str,
            typename std::enable_if<detail::is_string<String>::value>::type **
                enable = nullptr);
        value(std::string && str);
        value(std::string_view str);

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

        value & operator=(map && m);

        template<typename YAMLSeq>
        typename std::enable_if<detail::is_seq<YAMLSeq>::value, value &>::type
        operator=(YAMLSeq const & s);

        value & operator=(seq && s);

        value & operator=(int i);

        value & operator=(double d);

        template<typename String>
        typename std::enable_if<detail::is_string<String>::value, value &>::type
        operator=(String const & str);
        value & operator=(std::string && str);
        value & operator=(std::string_view str);

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
        bool is_int() const noexcept { return kind() == value_kind::int_; }
        bool is_double() const noexcept
        {
            return kind() == value_kind::double_;
        }
        bool is_string() const noexcept { return kind() == value_kind::string; }
        bool is_map() const noexcept { return kind() == value_kind::map; }
        bool is_seq() const noexcept { return kind() == value_kind::seq; }
        bool is_alias() const noexcept { return kind() == value_kind::alias; }
        bool is_property_node() const noexcept
        {
            return kind() == value_kind::property_node;
        }
        bool is_user_defined() const noexcept
        {
            return kind() == value_kind::user_defined;
        }

        template<typename T>
        bool is() const noexcept
        {
            return storage_.remote_.ptr_->type_id() == typeindex::type_id<T>();
        }

        bool operator==(value const & rhs) const noexcept
        {
            if (rhs.kind() != kind())
                return false;
            switch (storage_.local_.kind_) {
            case value::null_k: return true;
            case value::boolean_k:
                return storage_.local_.bytes_[3] ==
                       rhs.storage_.local_.bytes_[3];
            case value::int_k: return *int_ptr() == *rhs.int_ptr();
            case value::double_k: return *double_ptr() == *rhs.double_ptr();
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

        bool is_local() const noexcept { return storage_.local_.kind_ < seq_k; }

        int const * int_ptr() const noexcept
        {
            int const * retval = reinterpret_cast<int const *>(
                storage_.local_.bytes_.data() + 3);
            BOOST_ASSERT(std::uintptr_t(retval) % alignof(int) == 0);
            return retval;
        }
        int * int_ptr() noexcept
        {
            int * retval =
                reinterpret_cast<int *>(storage_.local_.bytes_.data() + 3);
            BOOST_ASSERT(std::uintptr_t(retval) % alignof(int) == 0);
            return retval;
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
            int_k,
            double_k,
            local_string_k,
            seq_k,
            map_k,
            alias_k,
            property_node_k,
            user_defined_k,
            remote_string_k
        };

        struct local
        {
            uint8_t kind_;
            std::array<char, 15> bytes_;
        };
        struct remote
        {
            uint8_t kind_;
            std::unique_ptr<detail::value_impl_base> ptr_;
        };
        union storage
        {
            storage() : local_{null_k} {}
            storage & operator=(storage const & other)
            {
                destroy();
                BOOST_ASSERT(other.local_.kind_ < seq_k);
                local_ = other.local_;
                return *this;
            }
            ~storage() { destroy(); }

            void destroy() noexcept
            {
                if (local_.kind_ < seq_k)
                    local_.~local();
                else
                    remote_.~remote();
            }

            local local_;
            remote remote_;
        };
        storage storage_;

        template<typename T>
        friend decltype(auto) get(value const & v) noexcept;
        template<typename T>
        friend decltype(auto) get(value & v) noexcept;

        friend std::size_t hash_append(std::size_t seed, value const & v);
    };

    using error_function = std::function<void(std::string const &)>;

    optional<value> parse(
        string_view str,
        error_function parse_error = error_function(),
        int max_recursion = 512);

}}

#include <boost/yaml/detail/yaml_impl.hpp>

namespace boost { namespace yaml {

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
    }

    template<typename T>
    decltype(auto) get(value const & v) noexcept
    {
        if constexpr (std::is_same<T, seq>::value) {
            BOOST_ASSERT(v.is_seq());
            return static_cast<detail::value_impl<seq> const *>(
                       v.storage_.remote_.ptr_.get())
                ->value_;
        } else if constexpr (std::is_same<T, map>::value) {
            BOOST_ASSERT(v.is_map());
            return static_cast<detail::value_impl<map> const *>(
                       v.storage_.remote_.ptr_.get())
                ->value_;
        } else if constexpr (std::is_same<T, null_t>::value) {
            BOOST_ASSERT(v.is_null());
            return null_t{};
        } else if constexpr (std::is_same<T, bool>::value) {
            BOOST_ASSERT(v.is_boolean());
            return bool(v.storage_.local_.bytes_[3]);
        } else if constexpr (std::is_same<T, int>::value) {
            BOOST_ASSERT(v.is_int());
            return int(*v.int_ptr());
        } else if constexpr (std::is_same<T, double>::value) {
            BOOST_ASSERT(v.is_double());
            return double(*v.double_ptr());
        } else if constexpr (std::is_same<T, std::string_view>::value) {
            BOOST_ASSERT(v.is_string());
            if (v.storage_.local_.kind_ == value::local_string_k) {
                return std::string_view(v.storage_.local_.bytes_.data());
            } else {
                return std::string_view(
                    static_cast<detail::value_impl<std::string> *>(
                        v.storage_.remote_.ptr_.get())
                        ->value_);
            }
        } else if constexpr (std::is_same<T, alias>::value) {
            BOOST_ASSERT(v.is_alias());
            return static_cast<detail::value_impl<alias> const *>(
                       v.storage_.remote_.ptr_.get())
                ->value_;
        } else if constexpr (std::is_same<T, property_node>::value) {
            BOOST_ASSERT(v.is_property_node());
            return static_cast<detail::value_impl<property_node> const *>(
                       v.storage_.remote_.ptr_.get())
                ->value_;
        } else { // user defined
            BOOST_ASSERT(v.is_user_defined());
            BOOST_ASSERT(
                v.storage_.remote_.ptr_->type_id() == typeindex::type_id<T>());
            return static_cast<detail::value_impl<T> const *>(
                       v.storage_.remote_.ptr_.get())
                ->value_;
        }
    }

    template<typename T>
    decltype(auto) get(value & v) noexcept
    {
        if constexpr (std::is_same<T, seq>::value) {
            BOOST_ASSERT(v.is_seq());
            return static_cast<detail::value_impl<seq> *>(
                       v.storage_.remote_.ptr_.get())
                ->value_;
        } else if constexpr (std::is_same<T, map>::value) {
            BOOST_ASSERT(v.is_map());
            return static_cast<detail::value_impl<map> *>(
                       v.storage_.remote_.ptr_.get())
                ->value_;
        } else if constexpr (std::is_same<T, null_t>::value) {
            BOOST_ASSERT(v.is_null());
            return null_t{};
        } else if constexpr (std::is_same<T, bool>::value) {
            BOOST_ASSERT(v.is_boolean());
            return bool(v.storage_.local_.bytes_[3]);
        } else if constexpr (std::is_same<T, int>::value) {
            BOOST_ASSERT(v.is_int());
            return int(*v.int_ptr());
        } else if constexpr (std::is_same<T, double>::value) {
            BOOST_ASSERT(v.is_double());
            return double(*v.double_ptr());
        } else if constexpr (std::is_same<T, std::string_view>::value) {
            BOOST_ASSERT(v.is_string());
            if (v.storage_.local_.kind_ == value::local_string_k) {
                return std::string_view(v.storage_.local_.bytes_.data());
            } else {
                return std::string_view(
                    static_cast<detail::value_impl<std::string> *>(
                        v.storage_.remote_.ptr_.get())
                        ->value_);
            }
        } else if constexpr (std::is_same<T, alias>::value) {
            BOOST_ASSERT(v.is_alias());
            return static_cast<detail::value_impl<alias> const *>(
                       v.storage_.remote_.ptr_.get())
                ->value_;
        } else if constexpr (std::is_same<T, property_node>::value) {
            BOOST_ASSERT(v.is_property_node());
            return static_cast<detail::value_impl<property_node> const *>(
                       v.storage_.remote_.ptr_.get())
                ->value_;
        } else { // user defined
            BOOST_ASSERT(v.is_user_defined());
            BOOST_ASSERT(
                v.storage_.remote_.ptr_->type_id() == typeindex::type_id<T>());
            return static_cast<detail::value_impl<T> *>(
                       v.storage_.remote_.ptr_.get())
                ->value_;
        }
    }

    template<typename YAMLMap>
    value::value(
        YAMLMap const & m,
        typename std::enable_if<detail::is_map<YAMLMap>::value>::type **
            enable)
    {
        storage_.remote_ = remote{
            map_k,
            std::make_unique<detail::value_impl<map>>(m.begin(), m.end())};
    }

    inline value::value(map && m)
    {
        storage_.remote_ = remote{
            map_k, std::make_unique<detail::value_impl<map>>(std::move(m))};
    }

    template<typename YAMLSeq>
    value::value(
        YAMLSeq const & s,
        typename std::enable_if<detail::is_seq<YAMLSeq>::value>::type **
            enable)
    {
        storage_.remote_ = remote{
            seq_k,
            std::make_unique<detail::value_impl<seq>>(s.begin(), s.end())};
    }

    inline value::value(seq && s)
    {
        storage_.remote_ = remote{
            seq_k, std::make_unique<detail::value_impl<seq>>(std::move(s))};
    }

    inline value::value(double d)
    {
        storage_.local_ = local{double_k};
        *double_ptr() = d;
    }

    inline value::value(int i)
    {
        storage_.local_ = local{int_k};
        *int_ptr() = i;
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

    inline value::value(alias a)
    {
        storage_.remote_ = remote{
            alias_k, std::make_unique<detail::value_impl<alias>>(std::move(a))};
    }

    inline value::value(property_node pn)
    {
        storage_.remote_ = remote{
            property_node_k,
            std::make_unique<detail::value_impl<property_node>>(std::move(pn))};
    }

    // user_defined
    template<typename T>
    value::value(
        T x,
        typename std::enable_if<
            !detail::is_map<T>::value && !detail::is_seq<T>::value &&
            !detail::is_string<T>::value>::type ** enable)
    {
        storage_.remote_ =
            remote{user_defined_k,
                   std::make_unique<detail::value_impl<T>>(std::move(x))};
    }

    template<typename YAMLMap>
    typename std::enable_if<detail::is_map<YAMLMap>::value, value &>::type
    value::operator=(YAMLMap const & m)
    {
        if (is_map()) {
            get<map>(*this) = map(m.begin(), m.end());
            return *this;
        }
        return *this = value(m);
    }

    inline value & value::operator=(map && m)
    {
        if (is_map()) {
            get<map>(*this) = std::move(m);
            return *this;
        }
        return *this = value(m);
    }

    template<typename YAMLSeq>
    typename std::enable_if<detail::is_seq<YAMLSeq>::value, value &>::type
    value::operator=(YAMLSeq const & s)
    {
        if (is_seq()) {
            get<seq>(*this) = seq(s.begin(), s.end());
            return *this;
        }
        return *this = value(s);
    }

    inline value & value::operator=(seq && s)
    {
        if (is_seq()) {
            get<seq>(*this) = std::move(s);
            return *this;
        }
        return *this = value(s);
    }

    inline value & value::operator=(double d) { return *this = value(d); }

    inline value & value::operator=(int i) { return *this = value(i); }

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

    inline value & value::operator=(null_t) { return *this = value(null_t{}); }

    inline value & value::operator=(alias a)
    {
        if (is_alias()) {
            static_cast<detail::value_impl<alias> *>(
                storage_.remote_.ptr_.get())
                ->value_ = std::move(a);
            return *this;
        }
        return *this = value(std::move(a));
    }

    inline value & value::operator=(property_node pn)
    {
        if (is_property_node()) {
            static_cast<detail::value_impl<property_node> *>(
                storage_.remote_.ptr_.get())
                ->value_ = std::move(pn);
            return *this;
        }
        return *this = value(std::move(pn));
    }

    inline std::ostream & operator<<(std::ostream & os, value const & value)
    {
        switch (value.storage_.local_.kind_) {
        case value::null_k: return os << "null";
        case value::boolean_k:
            return os << (value.storage_.local_.bytes_[3] ? "true" : "false");
        case value::int_k: return os << *value.int_ptr();
        case value::double_k: return os << *value.double_ptr();
        case value::local_string_k:
            return detail::to_yaml_impl(
                os, value.storage_.local_.bytes_.data());
        default: return value.storage_.remote_.ptr_->to_yaml_impl(os);
        }
        return os;
    }

    // user_defined
    template<typename T>
    typename std::enable_if<
        !detail::is_map<T>::value && !detail::is_seq<T>::value &&
            !detail::is_string<T>::value,
        value &>::type
    value::operator=(T x)
    {
        if (is<T>()) {
            get<T>(*this) = std::move(x);
            return *this;
        }
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
        case value_kind::user_defined:
            return v.storage_.remote_.ptr_->hash_append_impl(seed);
        }

        BOOST_ASSERT(!"Unreachable");
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

    namespace detail {
        inline bool value_impl<map>::equal_impl(value const & rhs) const
            noexcept
        {
            return value_ == get<map>(rhs);
        }
        inline bool value_impl<seq>::equal_impl(value const & rhs) const
            noexcept
        {
            return value_ == get<seq>(rhs);
        }
        inline bool value_impl<std::string>::equal_impl(value const & rhs) const
            noexcept
        {
            return value_ == get<std::string_view>(rhs);
        }
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
