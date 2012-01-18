/**
 *   Copyright (C) 2010, 2011, 2012 Object Modeling Designs
 *   consultomd.com
 */

#if !defined(OMD_GENERATOR_SCALAR_HPP)
#define OMD_GENERATOR_SCALAR_HPP

#define BOOST_SPIRIT_NO_PREDEFINED_TERMINALS

#include <string>

#include <boost/spirit/include/karma.hpp>

#include "../ast.hpp"         // our AST

namespace omd { namespace yaml { namespace generator
{
    namespace karma = boost::spirit::karma;
    namespace ascii = boost::spirit::ascii;

    typedef boost::uint32_t uchar; // a unicode code point

    template <typename OutputIterator>
    struct scalar : karma::grammar<OutputIterator, ast::value_t()>
    {
        scalar();

        karma::rule<OutputIterator, ast::value_t()> value;
        karma::rule<OutputIterator, ast::null_t()> null_value;
        karma::rule<OutputIterator, ast::string_t()> string_value;
    };
}}}

#endif
