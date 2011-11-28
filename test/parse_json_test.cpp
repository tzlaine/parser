/**
 *   Copyright (C) 2010, 2011 Object Modeling Designs
 */

//~ #define BOOST_SPIRIT_DEBUG

#include "../yaml/parser/flow_def.hpp"
#include "../yaml/parser/scalar_def.hpp"

#include <iostream>
#include <fstream>

#include <boost/spirit/include/support_istream_iterator.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>

namespace
{
    template <typename Char>
    bool parse(
        std::basic_istream<Char>& is,
        omd::ast::value_t& result,
        std::string const& source_file = "")
    {
        std::string file; // We will read the contents here.
        is.unsetf(std::ios::skipws); // No white space skipping!
        std::copy(
            std::istream_iterator<char>(is),
            std::istream_iterator<char>(),
            std::back_inserter(file));

        typedef std::string::const_iterator base_iterator_type;
        base_iterator_type sfirst(file.begin());
        base_iterator_type slast(file.end());

        typedef boost::spirit::classic::position_iterator<base_iterator_type>
            iterator_type;
        iterator_type first(sfirst, slast);
        iterator_type last;
        first.set_tabchars(1);

        int indent = 0;
        omd::parser::flow<iterator_type> p(indent, source_file);
        omd::parser::white_space<iterator_type> ws;

        using boost::spirit::qi::phrase_parse;
        return phrase_parse(first, last, p, ws, result);
    }
}

///////////////////////////////////////////////////////////////////////////////
//  Main program
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
    char const* filename = NULL;
    if (argc > 1)
    {
        filename = argv[1];
    }
    else
    {
        std::cerr << "Error: No input file provided." << std::endl;
        return 1;
    }

    std::ifstream in(filename, std::ios_base::in);

    if (!in)
    {
        std::cerr << "Error: Could not open input file: "
            << filename << std::endl;
        return 1;
    }

    // Ignore the BOM marking the beginning of a UTF-8 file in Windows
    char c = in.peek();
    if (c == '\xef')
    {
        char s[4];
        in >> s[0] >> s[1] >> s[2];
        s[3] = '\0';
        if (s != std::string("\xef\xbb\xbf"))
        {
            std::cerr << "Error: Unexpected characters from input file: "
                << filename << std::endl;
            return 1;
        }
    }

    using omd::ast::value_t;
    namespace qi = boost::spirit::qi;

    value_t result;
    if (parse(in, result, filename))
    {
        std::cout << "success: \n";
        omd::ast::print_json(std::cout, result);
        std::cout << std::endl;
    }
    else
    {
        std::cout << "parse error" << std::endl;
    }

    return 0;
}