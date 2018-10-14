#!/usr/bin/env python

atoms = ['*char_', 'eps', '-int_']
atoms_pass = [['"abc"', '"z"'], [''], ['', '"3"']]

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

def add_infix_op(t, op):
    retval = '('
    for i in range(len(t)):
        if i:
            retval += ' ' + op + ' '
        retval += t[i]
    retval += ')'
    return retval

def atom_type(a):
    mapping = {'*char_': 'std::vector<char>', 'eps': 'detail::nope', '-int_': 'optional<int>', "char_('z')": 'char'}
    return mapping[a]

seq_dump = False
or_dump = False

def seq_fold(x, y):
    if y == 'detail::nope':
        if seq_dump:
            print '0 return', x
        return x
    if x[-1] == y:
        if y.startswith('std::vector<'):
            if seq_dump:
                print '1 return', x
            return x
        if seq_dump:
            print '2 return', x[:-1] + ['std::vector<{}>'.format(y)]
        return x[:-1] + ['std::vector<{}>'.format(y)]

    # x[-1] is a vector, and y is the vector's value_type
    x_back_vector_t = x[-1].startswith('std::vector<') and x[-1][len('std::vector<'):-1] or 'foo'
    y_unwrapped_optional = y.startswith('optional<') and y[len('optional<'):-1] or 'bar'
    if x_back_vector_t == y or x_back_vector_t == y_unwrapped_optional:
        if seq_dump:
            print ' ',x_back_vector_t, y_unwrapped_optional
            print '3 return',x
        return x

    # y is a vector, and x[-1] is the vector's value_type
    y_vector_t = y.startswith('std::vector<') and y[len('std::vector<'):-1] or 'foo'
    x_back_unwrapped_optional = x[-1].startswith('optional<') and x[-1][len('optional<'):-1] or 'bar'
    if y_vector_t == x[-1] or y_vector_t == x_back_unwrapped_optional:
        if seq_dump:
            print ' ',y_vector_t, x_back_unwrapped_optional
            print '4 return',x[:-1] + [y]
        return x[:-1] + [y]

    if x[-1] == 'detail::nope':
        if seq_dump:
            print '5 return', x[:-1] + [y]
        return x[:-1] + [y]

    if seq_dump:
        print '6 return',x + [y]
    return x + [y]

def or_fold(x, y):
    if y == 'detail::nope':
        return [x[0], True]
    if y in x[0]:
        return x
    return [x[0] + [y], x[1]]

def seq_of(t):
    if t[0] not in atoms:
        types = t
    else:
        types = map(atom_type, t)
    if seq_dump:
        print types
    folded = reduce(seq_fold, types[1:], [types[0]])
    if len(folded) == 1:
        return folded[0]
    return 'tuple<{}>'.format(', '.join(folded))

def or_of(t):
    if t[0] not in atoms:
        types = t
    else:
        types = map(atom_type, t)
    if or_dump:
        print types
    folded = reduce(or_fold, types, [[], False])
    if len(folded[0]) == 0:
        return 'detail::nope'
    if len(folded[0]) == 1:
        retval = folded[0][0]
        if retval.startswith('optional<'):
            return retval
    else:
        retval = 'variant<{}>'.format(', '.join(folded[0]))
    if folded[1]:
        retval = 'optional<{}>'.format(retval)
    return retval

def type_of(t, op):
    if op == '>>':
        return seq_of(t)
    else:
        return or_of(t)

def optional_of(op_token, type_str):
    if op_token == '-' and not type_str.startswith('optional<') and type_str != 'detail::nope':
        return 'optional<{}>'.format(type_str)
    return type_str

all_exprs = []
all_types = []

i = 0
for first in all_atoms:
    for second in all_atoms:
        first_opt = (i % 3) == 0 and '-' or ''
        second_opt = (i % 4) == 0 and '-' or ''
        all_exprs.append(first_opt + add_infix_op(first, '>>') + ' | ' +
                         second_opt + add_infix_op(second, '>>'))
        all_types.append(or_of((optional_of(first_opt, type_of(first, '>>')),
                                optional_of(second_opt, type_of(second, '>>')))))
        i += 1

        first_opt = (i % 3) == 0 and '-' or ''
        second_opt = (i % 4) == 0 and '-' or ''
        all_exprs.append(first_opt + add_infix_op(first, '|') + ' >> ' +
                         second_opt + add_infix_op(second, '|'))
        all_types.append(seq_of((optional_of(first_opt, type_of(first, '|')),
                                 optional_of(second_opt, type_of(second, '|')))))
        i += 1

def type_to_result(type_):
    if type_ == 'detail::nope':
        return 'bool'
    return 'optional<{}>'.format(type_)

all_checks = []
for expr_,type_ in zip(all_exprs, all_types):
    check = '''\
    {{
        constexpr auto parser = {};
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, {}>));
    }}
'''.format(expr_, type_to_result(type_))
    all_checks.append(check)

checks_per_file = 250

file_form = '''\
// WARNING!  This file is generated.
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
