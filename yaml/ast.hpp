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

    // ------------------- AST types --------------------
    //
    typedef std::string                         string_t;
    typedef double                              double_t;
    typedef int                                 int_t;
    typedef bool                                bool_t;

    struct null_t {};

    // nulls always compare
    inline bool operator==(null_t a, null_t b) { return true;  }
    inline bool operator!=(null_t a, null_t b) { return false; }
    inline bool operator<(null_t a, null_t b) { return false; }

#ifdef BOOST_SPIRIT_DEBUG
    inline std::ostream& operator<<(std::ostream& out, null_t)
    { return out << "<null>"; }
#endif

    struct                                               value_t;
    typedef std::pair<value_t, value_t>                  object_element_t;
    typedef boost::container::stable_vector<value_t>     array_t;
    typedef std::pair<string_t, value_t>                 anchored_object_t;
    typedef std::pair<string_t, value_t*>                alias_t;

    struct properties_t
    {
        properties_t () {}
        properties_t (string_t tag, string_t anchor)
            : tag_ (std::move(tag)), anchor_ (std::move(anchor))
        {}

        string_t tag_;
        string_t anchor_;
    };
#ifdef BOOST_SPIRIT_DEBUG
    inline std::ostream& operator<<(std::ostream& out, properties_t p)
    { return out << p.tag_ << ',' << p.anchor_; }
#endif

    struct object_t;

    // TODO:
    // array_t -> seq_t
    // object_t -> map_t
    // anchored_object_t -> anchored_node_t
    // object_element_t -> map_element_t
    struct value_t
        : boost::spirit::extended_variant<
          null_t,
          bool_t,
          string_t,
          double_t,
          int_t,
          boost::recursive_wrapper<object_t>,
          array_t,
          alias_t,
          boost::recursive_wrapper<anchored_object_t>
        >
    {
        value_t(char const* val) : base_type(string_t(val)) {}
        value_t(string_t const& val) : base_type(val) {}
        value_t(double_t val) : base_type(val) {}
        value_t(int_t val) : base_type(val) {}
        value_t(bool_t val) : base_type(val) {}
        value_t(null_t val = null_t()) : base_type(val) {}
        value_t(object_t const& val) : base_type(val) {}
        value_t(array_t const& val) : base_type(val) {}
        value_t(alias_t const& val) : base_type(val) {}
        value_t(anchored_object_t const& val) : base_type(val) {}

        value_t(value_t const& rhs)
            : base_type(rhs.get()) {}
    };
#ifdef BOOST_SPIRIT_DEBUG
    inline std::ostream & operator<< (std::ostream & os, value_t const & v)
    { return os << "<value>"; }
#endif

    bool operator==(value_t const& a, value_t const& b);
    bool operator!=(value_t const& a, value_t const& b);
    bool operator<(value_t const& a, value_t const& b);

    struct object_t
    {
        using vector_t = boost::container::stable_vector<object_element_t>;
        using value_type = vector_t::value_type;
        using size_type = vector_t::size_type;
        using iterator = vector_t::iterator;
        using const_iterator = vector_t::const_iterator;

        inline object_t ();
        inline object_t (object_t const & o);
        inline object_t & operator= (object_t const & rhs);
        object_t (object_t && o) = default;
        object_t & operator= (object_t && rhs) = default;

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

        iterator begin ()
        { return elements_.begin(); }
        iterator end ()
        { return elements_.end(); }

        inline std::pair<iterator, bool> insert (object_element_t const & e);
        inline iterator insert (const_iterator at, object_element_t const & e);

        friend bool operator== (object_t const & a, object_t const & b)
        { return a.elements_ == b.elements_; }
        friend bool operator!= (object_t const & a, object_t const & b)
        { return a.elements_ != b.elements_; }
        friend bool operator< (object_t const & a, object_t const & b)
        { return a.elements_ < b.elements_; }
#ifdef BOOST_SPIRIT_DEBUG
        friend std::ostream & operator<< (std::ostream & os, object_t const & o)
        { return os << "{ " << o.elements_.size() << " elements }"; }
#endif

    private:
        using element_iterator_t =
            boost::container::stable_vector<object_element_t>::iterator;

        boost::container::stable_vector<object_element_t> elements_;

        struct index_t;
        std::unique_ptr<index_t> index_;
    };

    // Link all aliases in a YAML value
    void link_yaml(value_t& val);

    // Print a YAML value
    template <int Spaces, bool ExpandAliases>
    std::ostream& print_yaml(std::ostream& out, value_t const& val);

    inline std::ostream& print_yaml(std::ostream& out, value_t const& val)
    { return print_yaml<2, false>(out, val); }

    // ---------------------------------------------------

} }

#include <yaml/detail/ast_impl.hpp>

#endif
