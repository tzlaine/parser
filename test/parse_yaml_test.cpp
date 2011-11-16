/**
 *   Copyright (C) 2010, 2011 Object Modeling Designs
 */

#define BOOST_SPIRIT_DEBUG

#include "../yaml/parser/yaml_def.hpp"
#include "../yaml/parser/flow_def.hpp"
#include "../yaml/parser/scalar_def.hpp"

#include <iostream>
#include <fstream>

#include <boost/spirit/include/support_istream_iterator.hpp>
#include <boost/spirit/include/support_line_pos_iterator.hpp>

namespace
{
    template <typename Char>
    bool parse(
        std::basic_istream<Char>& is,
        omd::ast::value_t& result,
        std::string const& source_file = "")
    {
        //~ // no white space skipping in the stream!
        //~ is.unsetf(std::ios::skipws);

        //~ typedef
            //~ boost::spirit::basic_istream_iterator<Char>
        //~ stream_iterator_type;
        //~ stream_iterator_type sfirst(is);
        //~ stream_iterator_type slast;

        //~ typedef boost::spirit::line_pos_iterator<stream_iterator_type>
            //~ iterator_type;
        //~ iterator_type first(sfirst);
        //~ iterator_type last(slast);

        std::string file; // We will read the contents here.
        is.unsetf(std::ios::skipws); // No white space skipping!
        std::copy(
            std::istream_iterator<char>(is),
            std::istream_iterator<char>(),
            std::back_inserter(file));

        typedef char const* base_iterator_type;
        base_iterator_type sfirst(&file[0]);
        base_iterator_type slast(sfirst + file.size());

        typedef boost::spirit::line_pos_iterator<base_iterator_type>
            iterator_type;
        iterator_type first(sfirst);
        iterator_type last(slast);

        omd::parser::yaml<iterator_type> p(source_file);

        using boost::spirit::qi::parse;
        return parse(first, last, p, result);
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