# parser

This is a parser combinator library for C++.  As a quick example of use, here
is a complete program that parses one or more `double`s separated by commas,
ignoring whitespace:

```c++
#include <boost/parser/parser.hpp>

#include <iostream>
#include <string>


namespace bp = boost::parser;

int main()
{
    std::cout << "Enter a list of doubles, separated by commas.  No pressure. ";
    std::string input;
    std::getline(std::cin, input);

    auto const result = bp::parse(
        input, bp::double_ >> *(',' >> bp::double_), bp::ws);

    if (result) {
        std::cout << "Great! It looks like you entered:\n";
        for (double x : *result) {
            std::cout << x << "\n";
        }
    } else {
        std::cout
            << "Good job!  Please proceed to the recovery annex for cake.\n";
    }
}
```

Features:

- Parsers that parse a variety of things.
- Combining operations that make complex parsers out of simpler ones.
- Multiple ways of getting data out of the parse, including via callbacks.
- Sentinel- and range-friendly.
- Very Unicode friendliness.
- Excellent error reporting, via diagnostics like those produced by GCC and Clang.
- Trace support for debugging your parsers.
- Clever hacks to make compile time errors easier to deal with.  (These are totally optional.)

This library targets submission to Boost.

Online docs: https://tzlaine.github.io/parser

[![Build Status](https://travis-ci.org/tzlaine/parser.svg?branch=master)](https://travis-ci.org/tzlaine/parser)
[![Build Status](https://ci.appveyor.com/api/projects/status/github/tzlaine/parser?branch=master&svg=true)](https://ci.appveyor.com/project/tzlaine/parser)
[![License](https://img.shields.io/badge/license-boost-brightgreen.svg)](LICENSE_1_0.txt)
