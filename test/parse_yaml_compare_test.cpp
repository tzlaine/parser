/**
 *   Copyright (C) 2017 Zach Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <yaml/parser/stream.hpp>

#include <gtest/gtest.h>

#include <iostream>
#include <fstream>


char const * filename_1 = nullptr;
char const * filename_2 = nullptr;
std::ifstream * in_1_ptr = nullptr;
std::ifstream * in_2_ptr = nullptr;
bool verbose = false;


TEST(parse, test_parse_yaml)
{
    ASSERT_TRUE(in_1_ptr != nullptr) << "failed to set up input file stream " << filename_1;
    ASSERT_TRUE(in_2_ptr != nullptr) << "failed to set up input file stream " << filename_2;

    std::ifstream & in_1 = *in_1_ptr;
    std::ifstream & in_2 = *in_2_ptr;

    using boost::yaml::ast::value_t;
    using boost::yaml::parser::reporting_fn_t;
    using boost::yaml::parser::parse_yaml;
    using boost::yaml::ast::print_yaml;

    boost::optional<std::vector<value_t>> result_1 =
        parse_yaml(in_1, filename_1, reporting_fn_t(), reporting_fn_t(), verbose);
    ASSERT_TRUE(result_1) << "failed initial parse of " << filename_1;
    boost::optional<std::vector<value_t>> result_2 =
        parse_yaml(in_2, filename_2, reporting_fn_t(), reporting_fn_t(), verbose);
    ASSERT_TRUE(result_2) << "failed initial parse of " << filename_2;

    std::cout << "========================================\n"
              << filename_1 << "\n"
              << "========================================\n";
    for (auto const & doc : *result_1) {
        print_yaml_canonical(std::cout, doc);
        std::cout << "\n";
    }
    std::cout << std::endl;

    std::cout << "========================================\n"
              << filename_2 << "\n"
              << "========================================\n";
    for (auto const & doc : *result_2) {
        print_yaml_canonical(std::cout, doc);
        std::cout << "\n";
    }
    std::cout << std::endl;

    ASSERT_TRUE(*result_1 == *result_2);
}


int main (int argc, char** argv)
{
    if (argc < 3)
    {
        std::cerr << "Error: You did not provide two input files." << std::endl;
        return 1;
    }

    // Last two args must be the names of the files to parse and compare.
    filename_1 = argv[argc - 2];
    std::ifstream in_1(filename_1, std::ios_base::in);
    in_1_ptr = &in_1;

    filename_2 = argv[argc - 1];
    std::ifstream in_2(filename_2, std::ios_base::in);
    in_2_ptr = &in_2;

    if (!in_1)
    {
        std::cerr << "Error: Could not open input file: "
                  << filename_1 << std::endl;
        return 1;
    }
    if (!in_2)
    {
        std::cerr << "Error: Could not open input file: "
                  << filename_2 << std::endl;
        return 1;
    }

    int argc_ = argc - 2; // Don't give filename args to GTest.

    if (1 < argc_ && argv[argc_ - 1] == std::string("-v")) {
        verbose = true;
        --argc_;
    }

    ::testing::InitGoogleTest(&argc_, argv);
    return RUN_ALL_TESTS();
}
