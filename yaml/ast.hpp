/**
 *   Copyright (C) 2010, 2011, 2012 Michael Caisse, Object Modeling Designs
 *   consultomd.com
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef OMD_YAML_AST_VALUE_HPP
#define OMD_YAML_AST_VALUE_HPP

#include <string>
#include <map>
#include <ostream>
#include <boost/container/stable_vector.hpp>
#include <boost/spirit/include/support_extended_variant.hpp>

namespace omd { namespace yaml { namespace ast
{
    // ------------------- AST types --------------------
    //
    typedef std::string                         string_t;
    typedef double                              double_t;
    typedef int                                 int_t;
    typedef bool                                bool_t;
    struct                                      null_t
    {};

    // nulls always compare
    inline bool operator==(null_t a, null_t b) { return true;  }
    inline bool operator!=(null_t a, null_t b) { return false; }

    inline std::ostream& operator<<(std::ostream& out, null_t)
    { out << "<null>"; return out; }

    struct                                               value_t;
    typedef std::map<value_t, value_t>                   object_t;
    typedef boost::container::stable_vector<value_t>     array_t;
    typedef std::pair<string_t, value_t>                 anchored_object_t;
    typedef std::pair<string_t, value_t*>                alias_t;

    struct value_t
        : boost::spirit::extended_variant<
          null_t,
          bool_t,
          string_t,
          double_t,
          int_t,
          object_t,
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

    typedef std::pair<value_t, value_t> object_element_t;

    bool operator==(value_t const& a, value_t const& b);
    bool operator!=(value_t const& a, value_t const& b);
    bool operator<(value_t const& a, value_t const& b);

    // Link all aliases in a YAML value
    void link_yaml(value_t& val);

    // Print a YAML value
    template <int Spaces, bool ExpandAliases>
    std::ostream& print_yaml(std::ostream& out, value_t const& val);

    // ---------------------------------------------------
}}}

#include "detail/ast_impl.hpp"
#endif
