/**
 *   Copyright (C) 2010, 2011 Object Modeling Designs
 */

#include "../yaml/parser/scalar_def.hpp"
#include <boost/detail/lightweight_test.hpp>

namespace
{
    template <typename Char, typename Parser, typename Attr>
    bool test_attr(Char const* in, Parser const& p
        , Attr& attr, bool full_match = true)
    {
        Char const* last = in;
        while (*last)
            last++;
        return boost::spirit::qi::parse(in, last, p, attr)
            && (!full_match || (in == last));
    }
}

#define SCALAR_TEST(input, type, expected)                                     \
  {                                                                            \
      BOOST_TEST(test_attr(input, g, attr));                                   \
      BOOST_TEST(boost::get<type>(attr.get()) == expected);                    \
  }                                                                            \
  /***/

int main()
{
    using omd::parser::scalar;
    using omd::ast::value_t;
    using omd::ast::null_t;

    int indent = 0;
    scalar<char const*> g(indent);
    value_t attr;

    SCALAR_TEST("12345", int, 12345);
    SCALAR_TEST("true", bool, true);
    SCALAR_TEST("False", bool, false);
    SCALAR_TEST("On", bool, true);
    SCALAR_TEST("123.45", double, 123.45);
    SCALAR_TEST("0x4D2", int, 0x4D2);
    SCALAR_TEST("02333", int, 02333);
    SCALAR_TEST("~", null_t, null_t());
    SCALAR_TEST("null", null_t, null_t());

    SCALAR_TEST("\"Hello, World\"", std::string, "Hello, World");
    SCALAR_TEST("\"this is a unicode \u20AC string\"",
        std::string, "this is a unicode € string");

    return boost::report_errors();
}

