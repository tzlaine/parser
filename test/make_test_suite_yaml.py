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
args = parser.parse_args()

in_path = os.path.join(args.yaml_test_suite_path, 'test')
all_files = sorted([f for f in os.listdir(in_path) if os.path.isfile(os.path.join(in_path, f))])
tml_files = [f for f in all_files if f.endswith('.tml')]

tests = []

for tml_file in tml_files:
    tml_file_root = os.path.splitext(tml_file)[0]
    tml_path = os.path.join(in_path, tml_file)
    yml_path = os.path.join(args.output_dir, tml_file_root + '.yml')

    contents = open(tml_path, 'r').readlines()
    first_line = 0
    while first_line < len(contents) and 'in-yaml' not in contents[first_line]:
        first_line += 1
    if first_line == len(contents):
        continue
    first_line += 1
    last_line = first_line + 1
    while last_line < len(contents) and '+++' not in contents[last_line]:
        last_line += 1
    in_yaml = ''.join(contents[first_line : last_line]).replace(r'\%', '%').replace(r'\#', '#').replace('<TAB>', '\t').replace('<SPC>', ' ')
    tmp_file = open('tmp', 'w')
    tmp_file.write(in_yaml)
    tmp_file.close()
    shutil.move('tmp', yml_path)
    tests.append(tml_file_root)

index_file = open(os.path.join(args.output_dir, 'index.cmake'), 'w')
index_file.write('set(yml_file_index\n\n')
index_file.write('\n'.join(tests) + '\n')
index_file.write('\n)\n')
