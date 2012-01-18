/**
 *   Copyright (C) 2010, 2011, 2012 Object Modeling Designs
 *   consultomd.com
 */

#if !defined(OMD_GENERATOR_SCALAR_DEF_HPP)
#define OMD_GENERATOR_SCALAR_DEF_HPP

#include "scalar.hpp"

#include <boost/cstdint.hpp>
#include <boost/spirit/include/karma.hpp>

namespace boost { namespace spirit { namespace traits
{
    // this specialization tells Spirit that omd::ast::value_t is a variant-
    // like type
    template <>
    struct not_is_variant<omd::ast::value_t, karma::domain>
      : mpl::false_
    {};

    // this specialization tells Spirit how to extract the type of the value
    // stored in the given omd::ast::value_t node
    template <>
    struct variant_which<omd::ast::value_t>
    {
        static int call(omd::ast::value_t const& v)
        {
            return v.get().which();
        }
    };
}}}

namespace omd { namespace yaml { namespace generator
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct max_precision_policy : boost::spirit::karma::real_policies<T>
    {
        static unsigned int precision(T)
        {
            return 6;   // same as std C++ library default
        }
    };

    typedef karma::real_generator<double, max_precision_policy<double> >
        max_precision_double_type;
    max_precision_double_type const max_precision_double =
        max_precision_double_type();

    ///////////////////////////////////////////////////////////////////////////
    template <typename OutputIterator>
    scalar<OutputIterator>::scalar()
      : scalar::base_type(value)
    {
        karma::int_type int_;
        karma::bool_type bool_;
        karma::char_type char_;
        karma::lit_type lit;
        using boost::spirit::attr_cast;

        value =
              max_precision_double
            | int_
            | bool_
            | string_value
            | null_value
            ;

        null_value = attr_cast(lit("null"));

        string_value = '"' << *(&char_('"') << "\\\"" | char_) << '"';
    }
}}}

#endif
