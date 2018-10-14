#!/usr/bin/env python

atoms = ['*char_', 'eps', '-int_']

infix_ops = ['>>', '|']
unary_ops = ['-']


atoms_4 = []
atom_parts = [None, None, None, None]
for i in range(len(atoms)):
    atom_parts[0] = atoms[i]
    for j in range(len(atoms)):
        atom_parts[1] = atoms[j]
        for k in range(len(atoms)):
            atom_parts[2] = atoms[k]
            for l in range(len(atoms)):
                atom_parts[3] = atoms[l]
                new_atoms = [atom_parts[0], atom_parts[1], atom_parts[2], atom_parts[3]]
                # No more than two in a row.
                if new_atoms[0] == new_atoms[1] and new_atoms[1] == new_atoms[2]:
                    new_atoms = new_atoms[1:]
                if new_atoms[0] == new_atoms[1] and new_atoms[1] == new_atoms[2]:
                    new_atoms = new_atoms[1:]
                atoms_4.append(tuple(new_atoms))

atoms_3 = []
atom_parts = [None, None, None]
for i in range(len(atoms)):
    atom_parts[0] = atoms[i]
    for j in range(len(atoms)):
        atom_parts[1] = atoms[j]
        for k in range(len(atoms)):
            atom_parts[2] = atoms[k]
            new_atoms = [atom_parts[0], atom_parts[1], atom_parts[2]]
            # No more than two in a row.
            if new_atoms[0] == new_atoms[1] and new_atoms[1] == new_atoms[2]:
                new_atoms = new_atoms[1:]
            atoms_3.append(tuple(new_atoms))

atoms_2 = []
atom_parts = [None, None]
for i in range(len(atoms)):
    atom_parts[0] = atoms[i]
    for j in range(len(atoms)):
        atom_parts[1] = atoms[j]
        new_atoms = [atom_parts[0], atom_parts[1]]
        atoms_2.append(tuple(new_atoms))

atoms_1 = []
atom_parts = [None]
for i in range(len(atoms)):
    atom_parts[0] = atoms[i]
    new_atoms = [atom_parts[0]]
    atoms_1.append(tuple(new_atoms))

all_atoms = list(set(atoms_1 + atoms_2 + atoms_3 + atoms_4))

#print all_atoms
#print len(all_atoms)

def add_infix_op(t, op):
    retval = '('
    for i in range(len(t)):
        if i:
            retval += ' ' + op + ' '
        retval += t[i]
    retval += ')'
    return retval

all_exprs = []

i = 0
for first in all_atoms:
    for second in all_atoms:
        first_optional = (i % 3) == 0 and '-' or ''
        second_optional = (i % 4) == 0 and '-' or ''
        all_exprs.append(first_optional + add_infix_op(first, '>>') + ' | ' +
                         second_optional + add_infix_op(second, '>>'))
        i += 1

        first_optional = (i % 3) == 0 and '-' or ''
        second_optional = (i % 4) == 0 and '-' or ''
        all_exprs.append(first_optional + add_infix_op(first, '|') + ' >> ' +
                         second_optional + add_infix_op(second, '|'))
        i += 1

all_checks = []
for expr in all_exprs:
    check = '''\
    {{
        constexpr auto parser = {};
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, attr_t>)); // TODO
    }}
'''.format(expr)
    all_checks.append(check)

checks_per_file = 250

file_form = '''\
// Copyright (C) 2018 T. Zachary Laine
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#include <boost/parser/parser.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>


using namespace boost::parser;
using boost::is_same;
using boost::optional;
using boost::variant;
using boost::hana::tuple;

void compile_or_seq_attribute()
{{
    char const chars[] = "";
    auto first = std::begin(chars);
    auto const last = std::end(chars);

{}
}}
'''

i = 0
while i < len(all_checks):
    f = open('generated_parsers_{:02}.cpp'.format(i / checks_per_file), 'w')
    if i + checks_per_file <= len(all_checks):
        f.write(file_form.format(''.join(all_checks[i:i + checks_per_file])))
    else:
        f.write(file_form.format(''.join(all_checks[i:])))
    i += checks_per_file
