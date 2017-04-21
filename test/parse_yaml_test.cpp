/**
 *   Copyright (C) 2010, 2011, 2012 Object Modeling Designs
 *   consultomd.com
 *   Copyright (C) 2017 Zach Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <yaml/parser/yaml.hpp>

#include <iostream>
#include <fstream>


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

    using omd::yaml::ast::value_t;
    using omd::yaml::parser::parse_yaml;
    using omd::yaml::ast::print_yaml;

    value_t result;
    if (parse_yaml(in, result, filename))
    {
        print_yaml(std::cout, result);
        std::cout << std::endl;

        {
            std::stringstream expanded_once;
            omd::yaml::ast::print_yaml<3, true>(expanded_once, result);
            value_t reparsed_once_result;
            if (!parse_yaml(expanded_once, reparsed_once_result, filename + std::string("_expanded_once_string"))) {
                std::cout << "error: reparse of expanded_once string failed!" << std::endl;
            } else {
                std::stringstream expanded_twice;
                omd::yaml::ast::print_yaml<3, true>(expanded_twice, result);
                value_t reparsed_twice_result;
                if (!parse_yaml(expanded_twice, reparsed_twice_result, filename + std::string("_expanded_twice_string"))) {
                    std::cout << "error: reparse of expanded_twice string failed!" << std::endl;
                } else if (reparsed_twice_result != reparsed_once_result) {
                    std::cout << "error: in parse -> print and expand -> parse -> print and expand -> parse, the final parse differs from middle parse!" << std::endl;
                }
            }
        }

        {
            std::stringstream unexpanded;
            omd::yaml::ast::print_yaml(unexpanded, result);
            value_t reparsed_result;
            if (!parse_yaml(unexpanded, reparsed_result, filename + std::string("_unexpanded_string"))) {
                std::cout << "error: reparse of unexpanded string failed!" << std::endl;
            } else if (reparsed_result != result) {
                std::cout << "error: result of parse -> print and don't expand -> parse differs from initial parse!" << std::endl;
            }
        }
    }
    else
    {
        std::cout << "error: parse of original file failed!" << std::endl;
    }

    return 0;
}
