#!/usr/bin/env python

import argparse
import os
import shutil
import sys


parser = argparse.ArgumentParser(description='Create .yml test files from yaml-test-suite .tml files.')
parser.add_argument('--yaml-test-suite-path', '-y', type=str, required=True,
                    help='the path to yaml-test-suite')
parser.add_argument('--output-dir', '-o', type=str, required=True,
                    help='the directory into which to write the yaml files')
parser.add_argument('--tests', nargs='+', required=True,
                    help='')
parser.add_argument('--xfail-tests', nargs='+', required=True,
                    help='')
args = parser.parse_args()


def full_name(file):
    retval = os.path.join(args.yaml_test_suite_path, 'test_files', f)
    if not retval.endswith('.yaml') and not retval.endswith('.yml'):
        retval += '.yml'
    return retval

tests = [full_name(f) for f in args.tests if f not in args.xfail_tests]

test_functions = ''
test_function_names = ''

function_form = '''
void {1} (benchmark::State & state)
{{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT({2})YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {{
        result = parse_yaml(
            contents, contents + strlen(contents),
            "{0}",
            reporting_fn_t(), reporting_fn_t(), false
        );
    }}
    for (auto const & v : *result) {{
        (void)v;
        std::cout << "";
    }}
}}
'''

for test in tests:
    contents = open(test, 'r').read()
    test_name = 'BM_' + os.path.split(test)[1].replace('.', '_').replace('-', '_')
    test_functions += function_form.format(test, test_name, contents)
    test_function_names += 'BENCHMARK({});\n'.format(test_name)

full_test = '''
#include <yaml/parser/stream.hpp>

#include <chrono>
#include <iostream>

#include <benchmark/benchmark.h>

void BM_create_parsers (benchmark::State & state)
{{
    using namespace yaml::parser;

    uchar_t const str[1] = {{0x0}};
    iterator_t first(str, str);
    iterator_t last;

    while (state.KeepRunning()) {{
        stream_t parser(false);
        if (&parser < (stream_t*)0x1000000)
            std::cout << "";
    }}
}}
BENCHMARK(BM_create_parsers);

{}

{}
BENCHMARK_MAIN()
'''.format(test_functions, test_function_names)

index_file = open(os.path.join(args.output_dir, 'parse_perf.cpp'), 'w')
index_file.write(full_test)
