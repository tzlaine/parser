#!/usr/bin/env python

import argparse
import os
import shutil
import sys


parser = argparse.ArgumentParser(description='Create an index of the .json test files from JSONTestSuite.')
parser.add_argument('--json-test-suite-path', '-y', type=str, required=True,
                    help='the path to JSONTestSuite')
parser.add_argument('--output-dir', '-o', type=str, required=True,
                    help='the directory into which to write the json file index')
args = parser.parse_args()

in_path = os.path.join(args.json_test_suite_path, 'test_parsing')
all_files = sorted([f for f in os.listdir(in_path) if os.path.isfile(os.path.join(in_path, f))])
json_files = [f for f in all_files if f.endswith('.json')]

tests = [f for f in all_files if not f.startswith('n_')]
error_tests = [f for f in all_files if f.startswith('n_')]

index_file = open(os.path.join(args.output_dir, 'json_index.cmake'), 'w')
index_file.write('set(json_file_index\n\n')
index_file.write('\n'.join(tests) + '\n')
index_file.write('\n)\n')
index_file.write('set(error_json_file_index\n\n')
index_file.write('\n'.join(error_tests) + '\n')
index_file.write('\n)\n')
