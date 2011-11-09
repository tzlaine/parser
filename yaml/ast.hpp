/**
 *   Copyright (C) 2010, 2011 Michael Caisse, Object Modeling Designs
 *   consultomd.com
 *
 */
#ifndef OMD_AST_VALUE_HPP
#define OMD_AST_VALUE_HPP

#include <string>
#include <map>
#include <vector>
#include <ostream>
#include <boost/spirit/include/support_extended_variant.hpp>

namespace omd { namespace ast
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

    struct                                      value_t;
    typedef std::map<value_t, value_t>          object_t;
    typedef std::vector<value_t>                array_t;

    struct value_t
        : boost::spirit::extended_variant<
          null_t,
          bool_t,
          string_t,
          double_t,
          int_t,
          object_t,
          array_t
        >
    {
        value_t(string_t const& val) : base_type(val) {}
        value_t(double_t val) : base_type(val) {}
        value_t(int_t val) : base_type(val) {}
        value_t(bool_t val) : base_type(val) {}
        value_t(null_t val = null_t()) : base_type(val) {}
        value_t(object_t const& val) : base_type(val) {}
        value_t(array_t const& val) : base_type(val) {}

        value_t(value_t const& rhs)
            : base_type(rhs.get()) {}
    };

    bool operator==(value_t const& a, value_t const& b);
    bool operator!=(value_t const& a, value_t const& b);
    bool operator<(value_t const& a, value_t const& b);

    // ---------------------------------------------------
}}

#include "detail/ast_impl.hpp"
#endif
