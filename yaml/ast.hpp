/**
 *   Copyright (C) 2010, 2011, 2012 Michael Caisse, Object Modeling Designs
 *   consultomd.com
 *   Copyright (C) 2017 Zach Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef YAML_AST_VALUE_HPP
#define YAML_AST_VALUE_HPP

#include <boost/container/stable_vector.hpp>
#include <boost/spirit/include/support_extended_variant.hpp>

#include <ostream>
#include <string>
#include <unordered_map>


namespace yaml { namespace ast {

    using string_t = std::string;
    using double_t = double;
    using int_t = int;
    using bool_t = bool;

    struct null_t
    {
        friend bool operator==(null_t a, null_t b) { return true; }
        friend bool operator!=(null_t a, null_t b) { return false; }
        friend bool operator<(null_t a, null_t b) { return false; }
    };

#ifdef BOOST_SPIRIT_DEBUG
    inline std::ostream & operator<<(std::ostream & out, null_t)
    { return out << "<null>"; }
#endif

    struct value_t;

    using map_element_t = std::pair<value_t, value_t>;
    using seq_t = boost::container::stable_vector<value_t>;
    using alias_t = std::pair<string_t, std::shared_ptr<const value_t>>;

    struct properties_t
    {
        properties_t () {}
        properties_t (string_t tag, string_t anchor)
            : tag_ (std::move(tag)), anchor_ (std::move(anchor))
        {}

        explicit operator bool () const
        { return tag_ != "" || anchor_ != ""; }

        string_t tag_;
        string_t anchor_;
    };
#ifdef BOOST_SPIRIT_DEBUG
    inline std::ostream & operator<<(std::ostream & out, properties_t const & p)
    { return out << p.tag_ << ',' << p.anchor_; }
#endif

    using properties_node_t = std::pair<properties_t, value_t>;

    struct map_t;

    struct value_t
        : boost::spirit::extended_variant<
          null_t,
          bool_t,
          string_t,
          double_t,
          int_t,
          boost::recursive_wrapper<map_t>,
          seq_t,
          alias_t,
          boost::recursive_wrapper<properties_node_t>
        >
    {
        value_t(char const* val) : base_type(string_t(val)) {}
        value_t(string_t const & val) : base_type(val) {}
        value_t(double_t val) : base_type(val) {}
        value_t(int_t val) : base_type(val) {}
        value_t(bool_t val) : base_type(val) {}
        value_t(null_t val = null_t()) : base_type(val) {}
        value_t(map_t const & val) : base_type(val) {}
        value_t(seq_t const & val) : base_type(val) {}
        value_t(alias_t const & val) : base_type(val) {}
        value_t(properties_node_t const & val) : base_type(val) {}

        value_t(value_t const & rhs) : base_type(rhs.get()) {}
    };
#ifdef BOOST_SPIRIT_DEBUG
    inline std::ostream & operator<< (std::ostream & os, value_t const & v)
    { return os << "<value>"; }
#endif

    bool operator==(value_t const & a, value_t const & b);
    bool operator!=(value_t const & a, value_t const & b);
    bool operator<(value_t const & a, value_t const & b);

    struct map_t
    {
        using vector_t = boost::container::stable_vector<map_element_t>;
        using key_type = map_element_t::first_type;
        using mapped_type = map_element_t::second_type;
        using value_type = vector_t::value_type;
        using size_type = vector_t::size_type;
        using iterator = vector_t::iterator;
        using const_iterator = vector_t::const_iterator;

        inline map_t ();
        inline map_t (map_t const & o);
        inline map_t & operator= (map_t const & rhs);
        map_t (map_t && o) = default;
        map_t & operator= (map_t && rhs) = default;

        const_iterator begin () const
        { return elements_.begin(); }
        const_iterator end () const
        { return elements_.end(); }
        const_iterator cbegin () const
        { return elements_.begin(); }
        const_iterator cend () const
        { return elements_.end(); }

        size_type size () const
        { return elements_.size(); }

        inline const_iterator find (key_type const & k) const;
        inline size_type count (key_type const & k) const;

        iterator begin ()
        { return elements_.begin(); }
        iterator end ()
        { return elements_.end(); }

        inline std::pair<iterator, bool> insert (map_element_t const & e);
        inline iterator insert (const_iterator at, map_element_t const & e);

        friend bool operator== (map_t const & a, map_t const & b)
        { return a.elements_ == b.elements_; }
        friend bool operator!= (map_t const & a, map_t const & b)
        { return a.elements_ != b.elements_; }
        friend bool operator< (map_t const & a, map_t const & b)
        { return a.elements_ < b.elements_; }
#ifdef BOOST_SPIRIT_DEBUG
        friend std::ostream & operator<< (std::ostream & os, map_t const & o)
        { return os << "{ " << o.elements_.size() << " elements }"; }
#endif

    private:
        using element_iterator_t =
            boost::container::stable_vector<map_element_t>::iterator;

        boost::container::stable_vector<map_element_t> elements_;

        struct index_t;
        std::unique_ptr<index_t> index_;
    };

    template <int Spaces, bool ExpandAliases, bool InlineCollections, bool ExplicitMapEntriesAndTags>
    std::ostream & print_yaml(std::ostream & out, value_t const & val);

    inline std::ostream & print_yaml(std::ostream & out, value_t const & val)
    { return print_yaml<2, false, true, false>(out, val); }

    inline std::ostream & print_yaml_canonical(std::ostream & out, value_t const & val)
    {
        out << "%YAML 1.2\n---\n";
        return print_yaml<2, true, false, true>(out, val);
    }

    // ---------------------------------------------------

} }

#include <yaml/detail/ast_impl.hpp>

#endif
