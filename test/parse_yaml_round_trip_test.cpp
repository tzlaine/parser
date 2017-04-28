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
    ASSERT_EQ(result.size(), 1u);

    print_yaml(std::cout, result[0]);
    std::cout << std::endl;

    {
        std::stringstream expanded_once;
        yaml::ast::print_yaml<3, true>(expanded_once, result[0]);
        std::vector<value_t> reparsed_once_result;
        bool const expanded_once_parse =
            parse_yaml(expanded_once, reparsed_once_result, filename + std::string("_expanded_once_string"));
        EXPECT_TRUE(expanded_once_parse) << "reparse of expanded_once string failed!";
        EXPECT_EQ(reparsed_once_result.size(), 1u);
        if (expanded_once_parse && reparsed_once_result.size() == 1u) {
            std::stringstream expanded_twice;
            yaml::ast::print_yaml<3, true>(expanded_twice, reparsed_once_result[0]);
            std::vector<value_t> reparsed_twice_result;
            bool const expanded_twice_parse =
                parse_yaml(expanded_twice, reparsed_twice_result, filename + std::string("_expanded_twice_string"));
            EXPECT_TRUE(expanded_twice_parse) << "reparse of expanded_twice string failed!";
            EXPECT_EQ(reparsed_twice_result.size(), 1u);
            if (expanded_twice_parse && reparsed_twice_result.size() == 1u) {
                EXPECT_EQ(reparsed_twice_result, reparsed_once_result) << "in parse -> print and expand -> parse -> print and expand -> parse, the final parse differs from middle parse!";
            }
        }
    }

    {
        std::stringstream unexpanded;
        yaml::ast::print_yaml(unexpanded, result[0]);
        std::vector<value_t> reparsed_result;
        bool const unexpanded_parse =
            parse_yaml(unexpanded, reparsed_result, filename + std::string("_unexpanded_string"));
        EXPECT_TRUE(unexpanded_parse) << "reparse of unexpanded string failed!";
        EXPECT_EQ(reparsed_result.size(), 1u);
        if (unexpanded_parse && reparsed_result.size() == 1u) {
            EXPECT_EQ(reparsed_result, result) << "result of parse -> print and don't expand -> parse differs from initial parse!";
        }
    }
}


int main (int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Error: No input file provided." << std::endl;
        return 1;
    }

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
