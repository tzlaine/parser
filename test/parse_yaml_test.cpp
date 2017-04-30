/**
 *   Copyright (C) 2010, 2011, 2012 Object Modeling Designs
 *   consultomd.com
 *   Copyright (C) 2017 Zach Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <yaml/parser/stream.hpp>

#include <gtest/gtest.h>

#include <iostream>
#include <fstream>


char const * filename = nullptr;
std::ifstream * in_ptr = nullptr;


TEST(parse, test_parse_yaml)
{
    ASSERT_TRUE(in_ptr != nullptr) << "failed to set up input file stream " << filename;

    std::ifstream & in = *in_ptr;

    using yaml::ast::value_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    std::vector<value_t> result;
    ASSERT_TRUE((parse_yaml(in, result, filename))) << "failed initial parse of " << filename;
    ASSERT_TRUE(!result.empty());

    for (auto const & doc : result) {
        print_yaml(std::cout, doc);
    }
    std::cout << std::endl;
}


int main (int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Error: No input file provided." << std::endl;
        return 1;
    }

    // TODO: Cruft.  Replace this with tests that have different
    // BOMs/encodings.

    // Last arg must be the name of the file to parse.
    filename = argv[argc - 1];
    std::ifstream in(filename, std::ios_base::in);
    in_ptr = &in;

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

    int argc_ = argc - 1; // Don't give filename arg to GTest.
    ::testing::InitGoogleTest(&argc_, argv);
    return RUN_ALL_TESTS();
}
