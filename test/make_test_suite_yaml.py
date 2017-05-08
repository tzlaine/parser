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
error_tests = []

def write_section(contents, section_name, path):
    first_line = 0
    while first_line < len(contents) and section_name not in contents[first_line]:
        first_line += 1
    if first_line == len(contents):
        return False
    first_line += 1
    last_line = first_line + 1
    while last_line < len(contents) and '+++' not in contents[last_line]:
        last_line += 1
    section = ''.join(contents[first_line : last_line]).replace(r'\%', '%').replace(r'\#', '#').replace('<TAB>', '\t').replace('<SPC>', ' ')
    if section == '':
        return False

    tmp_file = open('tmp', 'w')
    tmp_file.write(section)
    tmp_file.close()
    shutil.move('tmp', path)
    return True

for tml_file in tml_files:
    tml_file_root = os.path.splitext(tml_file)[0]
    tml_path = os.path.join(in_path, tml_file)
    in_yml_path = os.path.join(args.output_dir, tml_file_root + '.yml')
    out_yml_path = os.path.join(args.output_dir, tml_file_root + '-out.yml')
    json_path = os.path.join(args.output_dir, tml_file_root + '.json')

    contents = open(tml_path, 'r').readlines()

    error_test = False
    for line in contents:
        if line.startswith('tags:') and 'error' in line:
            error_test = True

    if write_section(contents, 'in-yaml', in_yml_path) == False:
        continue
    if error_test:
        error_tests.append(tml_file_root)
        continue
    
    tests.append(tml_file_root)

    write_section(contents, 'out-yaml', out_yml_path)
    write_section(contents, 'json', json_path)

index_file = open(os.path.join(args.output_dir, 'index.cmake'), 'w')
index_file.write('set(yml_file_index\n\n')
index_file.write('\n'.join(tests) + '\n')
index_file.write('\n)\n')
index_file.write('set(error_yml_file_index\n\n')
index_file.write('\n'.join(error_tests) + '\n')
index_file.write('\n)\n')
