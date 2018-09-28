/**
 *   Copyright (C) 2010, 2011, 2012 Object Modeling Designs
 *   consultomd.com
 *   Copyright (C) 2017 Zach Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <boost/yaml/json.hpp>

#include <gtest/gtest.h>

#include <iostream>
#include <fstream>


char const * filename = nullptr;
std::ifstream * in_ptr = nullptr;


TEST(parse, test_parse_yaml)
{
    ASSERT_TRUE(in_ptr != nullptr) << "failed to set up input file stream " << filename;

    std::ifstream & in = *in_ptr;
    std::string str;
    while (in) {
        char c;
        if (in.get(c))
            str.push_back(c);
    }

    std::vector<std::string> errors;
    auto report_error = [&errors](std::string const & error) {
        errors.push_back(error);
    };

    boost::optional<boost::json::value> result =
        boost::json::parse(str, report_error);

    for (auto const & error : errors) {
        std::cout << error;
    }

    ASSERT_TRUE(result) << "failed initial parse of " << filename << "\n"
                        << str << "\n";
    ASSERT_TRUE(errors.empty()) << "initial parse of " << filename << "\n"
                                << str << "\nproduced error messages";

    std::cout << *result;
    std::cout << "\n";
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

    ::testing::InitGoogleTest(&argc_, argv);
    return RUN_ALL_TESTS();
}
