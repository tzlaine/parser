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

def add_infix_op(t, op):
    retval = '('
    for i in range(len(t)):
        if i:
            retval += ' ' + op + ' '
        retval += t[i]
    retval += ')'
    return retval

def atom_type(a):
    mapping = {'*char_': 'std::vector<char>', 'eps': 'nope', '-int_': 'optional<int>', "char_('z')": 'char'}
    return mapping[a]

seq_dump = False
or_dump = False

def seq_fold(x, y):
    if y == 'nope':
        if seq_dump:
            print '0 return', x
        return x

    y_unwrapped_optional = y.startswith('optional<') and y[len('optional<'):-1] or 'bar'
    if x[-1] == y or x[-1] == y_unwrapped_optional:
        if x[-1].startswith('std::vector<'):
            if seq_dump:
                print '1 return', x
            return x
        if seq_dump:
            print '2 return', x[:-1] + ['std::vector<{}>'.format(y)]
        final_y = x[-1] == y and y or y_unwrapped_optional
        return x[:-1] + ['std::vector<{}>'.format(final_y)]

    # x[-1] is a vector, and y is the vector's value_type
    x_back_vector_t = x[-1].startswith('std::vector<') and x[-1][len('std::vector<'):-1] or 'foo'
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

    if x[-1] == 'nope':
        if seq_dump:
            print '5 return', x[:-1] + [y]
        return x[:-1] + [y]

    if seq_dump:
        print '6 return',x + [y]
    return x + [y]

def or_fold(x, y):
    if y == 'nope':
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
        return 'nope'
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
    if op_token == '-' and not type_str.startswith('optional<') and type_str != 'nope':
        return 'optional<{}>'.format(type_str)
    return type_str

def atom_str(a):
    mapping = {'*char_': 'cb', 'eps': '', '-int_': '3', "char_('z')": 'z'}
    return mapping[a]

def seq_str(t):
    if t[0] not in atoms:
        strs = t
    else:
        strs = map(atom_str, t)
    return ''.join(strs)

def or_str(t):
    if t[0] not in atoms:
        strs = t
    else:
        strs = map(atom_str, t)
    return strs[0]

def str_of(t, op):
    if op == '>>':
        return seq_str(t)
    else:
        return or_str(t)

all_exprs = []
all_types = []
all_strs = []

i = 0
for first in all_atoms:
    for second in all_atoms:
        first_opt = (i % 3) == 0 and '-' or ''
        second_opt = (i % 4) == 0 and '-' or ''
        all_exprs.append(first_opt + add_infix_op(first, '>>') + ' | ' +
                         second_opt + add_infix_op(second, '>>'))
        all_types.append(or_of((optional_of(first_opt, type_of(first, '>>')),
                                optional_of(second_opt, type_of(second, '>>')))))
        all_strs.append(or_str((str_of(first, '>>'), str_of(second, '>>'))))
        i += 1

        first_opt = (i % 3) == 0 and '-' or ''
        second_opt = (i % 4) == 0 and '-' or ''
        all_exprs.append(first_opt + add_infix_op(first, '|') + ' >> ' +
                         second_opt + add_infix_op(second, '|'))
        all_types.append(seq_of((optional_of(first_opt, type_of(first, '|')),
                                 optional_of(second_opt, type_of(second, '|')))))
        all_strs.append(seq_str((str_of(first, '|'), str_of(second, '|'))))
        i += 1

def type_to_result(type_):
    if type_ == 'nope':
        return 'bool'
    return 'optional<{}>'.format(type_)

def type_to_fail_result(type_):
    if type_.startswith('tuple<'):
        elements = type_[len('tuple<'):-1].split(', ') + ['std::vector<int>']
        return seq_of(elements)
    return seq_of((type_, 'std::vector<int>'))

all_checks = []
for expr_,type_,str_ in zip(all_exprs, all_types, all_strs):
    check = '''\
    {{
        constexpr auto parser = {0};
        using attr_t = decltype(parse(g_first, g_last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, {1}>));

        std::string const str = "{2}";
        auto first = str.begin();
        auto const last = str.end();
        attr_t const attr = parse(first, last, parser);
        EXPECT_TRUE(attr);

        constexpr auto fail_parser = parser >> repeat(Inf)[int_];
        first = str.begin();
        auto const fail_attr = parse(first, last, fail_parser);
        EXPECT_FALSE(fail_attr);
'''.format(expr_, type_to_result(type_), str_)
    if type_to_result(type_) != 'bool':
        check += '''\
        {
            decltype(parse(first, last, fail_parser)) attr;
            auto const copy = attr;
            EXPECT_FALSE(parse(first, last, fail_parser, attr));
            EXPECT_EQ(attr, copy);
        }
'''
    check += '''\
    }
'''
    all_checks.append(check)

checks_per_file = 100
checks_per_test = 5

file_prefix = '''\
// WARNING!  This file is generated.
// Copyright (C) 2018 T. Zachary Laine
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#include <boost/parser/parser.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>

#include <gtest/gtest.h>


using namespace boost::parser;
using boost::is_same;
using std::optional;
using std::variant;
using boost::hana::tuple;

char const g_chars[] = "";
auto g_first = std::begin(g_chars);
auto const g_last = std::end(g_chars);


'''

test_prefix = '''\
TEST(parser, generated_{:03}_{:03})
{{
'''

test_suffix = '''\
}

'''

i = 0
while i < len(all_checks):
    file_index = i / checks_per_file
    f = open('generated_parsers_{:03}.cpp'.format(file_index), 'w')
    lo = i
    hi = min(i + checks_per_file, len(all_checks))
    test_index = 0
    f.write(file_prefix)
    for j in range(lo, hi):
        if test_index != 0 and j % checks_per_test == 0:
            f.write(test_suffix)
        if j % checks_per_test == 0:
            f.write(test_prefix.format(file_index, test_index))
            test_index += 1
        f.write(all_checks[j])
    f.write(test_suffix)
    i += checks_per_file
