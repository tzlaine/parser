/**
 *   Copyright (C) 2010, 2011, 2012 Object Modeling Designs
 *   consultomd.com
 *   Copyright (C) 2017 T. Zachary Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <boost/yaml/parser/stream.hpp>

#include <gtest/gtest.h>

#include <iostream>
#include <fstream>


char const * filename = nullptr;
std::ifstream * in_ptr = nullptr;
bool verbose = false;


TEST(parse, test_parse_yaml)
{
    ASSERT_TRUE(in_ptr != nullptr) << "failed to set up input file stream " << filename;

    std::ifstream & in = *in_ptr;

    using boost::yaml::ast::value_t;
    using boost::yaml::parser::reporting_fn_t;
    using boost::yaml::parser::parse_yaml;
    using boost::yaml::ast::print_yaml;

    std::vector<std::string> errors;
    auto report_error = [&errors](std::string const & error) {
        errors.push_back(error);
    };

    boost::optional<std::vector<value_t>> result =
        parse_yaml(in, filename, report_error, reporting_fn_t(), verbose);

    for (auto const & error : errors) {
        std::cout << error;
    }

    ASSERT_TRUE(result) << "failed initial parse of " << filename;
    ASSERT_TRUE(errors.empty()) << "initial parse of " << filename << " produced error messages";

    for (auto const & doc : *result) {
        std::cout << "---\n";
        print_yaml(std::cout, doc);
        std::cout << "\n";
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

    int argc_ = argc - 1; // Don't give filename arg to GTest.

    if (1 < argc_ && argv[argc_ - 1] == std::string("-v")) {
        verbose = true;
        --argc_;
    }

    ::testing::InitGoogleTest(&argc_, argv);
    return RUN_ALL_TESTS();
}
