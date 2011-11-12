/**
 *   Copyright (C) 2010, 2011 Object Modeling Designs
 */

#include "../yaml/generator/scalar_def.hpp"
#include <boost/detail/lightweight_test.hpp>

namespace
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Char>
    struct output_iterator
    {
        typedef std::basic_string<Char> string_type;
        typedef std::back_insert_iterator<string_type> type;
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename Char, typename T>
    void print_if_failed(char const* func, bool result
      , std::basic_string<Char> const& generated, T const& expected)
    {
        if (!result)
            std::cerr << "in " << func << ": result is false" << std::endl;
        else if (generated != expected)
            std::cerr << "in " << func << ": generated \""
                << std::string(generated.begin(), generated.end())
                << "\"" << std::endl;
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename Char, typename Generator, typename Attr>
    inline bool test(Char const *expected, Generator const& g, Attr const& attr)
    {
        namespace karma = boost::spirit::karma;
        typedef std::basic_string<Char> string_type;

        string_type generated;
        std::back_insert_iterator<string_type> outit(generated);
        bool result = karma::generate(outit, g, attr);

        print_if_failed("test", result, generated, expected);
        return result && generated == expected;
    }
}

int main()
{
    using omd::generator::scalar;
    using omd::ast::value_t;
    using omd::ast::null_t;

    scalar<output_iterator<char>::type> g;

    BOOST_TEST(test("12345", g, value_t(12345)));
    BOOST_TEST(test("true", g, value_t(true)));
    BOOST_TEST(test("false", g, value_t(false)));
    BOOST_TEST(test("123.45", g, value_t(123.45)));
    BOOST_TEST(test("123.456789012", g, value_t(123.456789012)));
    BOOST_TEST(test("null", g, value_t(null_t())));
    BOOST_TEST(test("\"Hello, World\"", g, value_t(std::string("Hello, World"))));

    return boost::report_errors();
}

