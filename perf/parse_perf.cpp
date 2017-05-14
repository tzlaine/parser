
#include <yaml/parser/stream.hpp>

#include <chrono>
#include <iostream>

#include <benchmark/benchmark.h>


yaml::parser::stream_t g_parser(false);


void BM_229Q_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(-
  name: Mark McGwire
  hr:   65
  avg:  0.278
-
  name: Sammy Sosa
  hr:   63
  avg:  0.288
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/229Q.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_27NA_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(%YAML 1.2
--- text
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/27NA.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_2AUY_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT( - !!str a
 - b
 - !!int 42
 - d
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/2AUY.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_2JQS_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(: a
: b
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/2JQS.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_2SXE_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(&a: key: &a value
foo:
  *a:
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/2SXE.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_2XXW_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(# Sets are represented as a
# Mapping where each key is
# associated with a null value
--- !!set
? Mark McGwire
? Sammy Sosa
? Ken Griff
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/2XXW.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_35KP_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(--- !!map
? a
: b
--- !!seq
- !!str c
--- !!str
d
e
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/35KP.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_3ALJ_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(- - s1_i1
  - s1_i2
- s2
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/3ALJ.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_3GZX_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(First occurrence: &anchor Foo
Second occurrence: *anchor
Override anchor: &anchor Bar
Reuse anchor: *anchor
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/3GZX.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_3MYT_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(k:#foo
 &a !t s
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/3MYT.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_4ABK_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT({
unquoted : "separate",
http://foo.com,
omitted value:,
: omitted key,
}
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/4ABK.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_4CQQ_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(plain:
  This unquoted scalar
  spans many lines.

quoted: "So does this
  quoted scalar.\n"
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/4CQQ.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_4GC6_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT('here''s to "quotes"'
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/4GC6.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_4UYU_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT("foo: bar\": baz"
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/4UYU.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_4ZYM_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(plain: text
  lines
quoted: "text
  	lines"
block: |
  text
   	lines
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/4ZYM.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_54T7_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT({foo: you, bar: far}
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/54T7.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_565N_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(canonical: !!binary "\
 R0lGODlhDAAMAIQAAP//9/X17unp5WZmZgAAAOfn515eXvPz7Y6OjuDg4J+fn5\
 OTk6enp56enmlpaWNjY6Ojo4SEhP/++f/++f/++f/++f/++f/++f/++f/++f/+\
 +f/++f/++f/++f/++f/++SH+Dk1hZGUgd2l0aCBHSU1QACwAAAAADAAMAAAFLC\
 AgjoEwnuNAFOhpEMTRiggcz4BNJHrv/zCFcLiwMWYNG84BwwEeECcgggoBADs="
generic: !!binary |
 R0lGODlhDAAMAIQAAP//9/X17unp5WZmZgAAAOfn515eXvPz7Y6OjuDg4J+fn5
 OTk6enp56enmlpaWNjY6Ojo4SEhP/++f/++f/++f/++f/++f/++f/++f/++f/+
 +f/++f/++f/++f/++f/++SH+Dk1hZGUgd2l0aCBHSU1QACwAAAAADAAMAAAFLC
 AgjoEwnuNAFOhpEMTRiggcz4BNJHrv/zCFcLiwMWYNG84BwwEeECcgggoBADs=
description:
 The binary value above is a tiny arrow encoded as a gif image.
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/565N.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_57H4_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(sequence: !!seq
- entry
- !!seq
 - nested
mapping: !!map
 foo: bar
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/57H4.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_5BVJ_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(literal: |
  some
  text
folded: >
  some
  text
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/5BVJ.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_5C5M_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(- { one : two , three: four , }
- {five: six,seven : eight}
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/5C5M.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_5GBF_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(Folding:
  "Empty line
   	
  as a line feed"
Chomping: |
  Clipped empty lines
 

)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/5GBF.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_5KJE_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(- [ one, two, ]
- [three ,four]
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/5KJE.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_5NYZ_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(key:    # Comment
  value
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/5NYZ.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_5TYM_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(%TAG !m! !my-
--- # Bulb here
!m!light fluorescent
...
%TAG !m! !my-
--- # Color here
!m!light green
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/5TYM.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_5WE3_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(? explicit key # Empty value
? |
  block key
: - one # Explicit compact
  - two # block value
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/5WE3.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_65WH_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(- foo
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/65WH.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_6BCT_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(# XXX Why are tabs allowed as indentation after dash?
- foo:	 bar
- - baz
  -	baz
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/6BCT.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_6CK3_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(%TAG !e! tag:example.com,2000:app/
---
- !local foo
- !!str bar
- !e!tag%21 baz
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/6CK3.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_6FWR_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(|+
 ab
 
  
...
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/6FWR.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_6H3V_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT('foo: bar\': baz'
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/6H3V.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_6HB6_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(  # Leading comment line spaces are
   # neither content nor indentation.
    
Not indented:
 By one space: |
    By four
      spaces
 Flow style: [    # Leading spaces
   By two,        # in flow style
  Also by two,    # are neither
  	Still by two   # content nor
    ]             # indentation.
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/6HB6.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_6JQW_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(# ASCII Art
--- |
  \//||\/||
  // ||  ||__
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/6JQW.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_6JWB_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(foo: !!seq
  - !!str a
  - !!map
    key: !!str value
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/6JWB.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_6LVF_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(%FOO  bar baz # Should be ignored
              # with a warning.
--- "foo"
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/6LVF.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_6M2F_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(? &a a
: &b b
: *a
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/6M2F.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_6SLA_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT("foo\nbar:baz\tx \\$%^&*()x": 23
'x\ny:z\tx $%^&*()x': 24
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/6SLA.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_6VJK_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(>
 Sammy Sosa completed another
 fine season with great stats.

   63 Home Runs
   0.288 Batting Average

 What a year!
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/6VJK.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_6ZKB_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(Document
---
# Empty
...
%YAML 1.2
---
matches %: 20
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/6ZKB.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_735Y_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(-
  "flow in block"
- >
 Block scalar
- !!map # Block collection
  foo : bar
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/735Y.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_74H7_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(!!str a: b
c: !!int 42
e: !!str f
g: h
!!int 23: !!bool false
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/74H7.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_77H8_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(---
not-date: !!str 2002-04-28

picture: !!binary |
 R0lGODlhDAAMAIQAAP//9/X
 17unp5WZmZgAAAOfn515eXv
 Pz7Y6OjuDg4J+fn5OTk6enp
 56enmleECcgggoBADs=

application specific tag: !something |
 The semantics of the tag
 above may be different for
 different documents.
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/77H8.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_7A4E_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(" 1st non-empty

 2nd non-empty 
	3rd non-empty "
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/7A4E.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_7BUB_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(---
hr:
  - Mark McGwire
  # Following node labeled SS
  - &SS Sammy Sosa
rbi:
  - *SS # Subsequent occurrence
  - Ken Griffey
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/7BUB.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_7FWL_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(!<tag:yaml.org,2002:str> foo :
  !<!bar> baz
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/7FWL.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_7T8X_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(>

 folded
 line

 next
 line
   * bullet

   * list
   * lines

 last
 line

# Comment
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/7T8X.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_7W2P_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(? a
? b
c:
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/7W2P.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_82AN_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(---word1
word2
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/82AN.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_87E4_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT('implicit block key' : [
  'implicit flow key' : value,
 ]
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/87E4.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_8G76_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(  # Comment
   


)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/8G76.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_8MK2_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(! a
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/8MK2.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_8QBE_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(key:
 - item1
 - item2
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/8QBE.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_8UDB_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT([
"double
 quoted", 'single
           quoted',
plain
 text, [ nested ],
single: pair,
]
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/8UDB.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_93JH_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT( - key: value
   key2: value2
 -
   key3: value3
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/93JH.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_96L6_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(--- >
  Mark McGwire's
  year was crippled
  by a knee injury.
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/96L6.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_98YD_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(# Comment only.
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/98YD.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_9FMG_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(a:
  b:
    c: d
  e:
    f: g
h: i
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/9FMG.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_9J7A_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(foo:
  bar: baz
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/9J7A.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_9SHH_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(single: 'text'
double: "text"
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/9SHH.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_9U5K_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(---
# Products purchased
- item    : Super Hoop
  quantity: 1
- item    : Basketball
  quantity: 4
- item    : Big Shoes
  quantity: 1
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/9U5K.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_9WXW_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(# Private
!foo "bar"
...
# Global
%TAG ! tag:example.com,2000:app/
---
!foo "bar"
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/9WXW.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_9YRD_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(a
b  
  c
d

e
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/9YRD.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_A2M4_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(# XXX Why are tabs allowed as indentation after dash?
? a
: -	b
  -  -	c
     - d
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/A2M4.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_A6F9_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(strip: |-
  text
clip: |
  text
keep: |+
  text
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/A6F9.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_A984_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(a: b
 c
d:
 e
  f
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/A984.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_AVM7_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT()YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/AVM7.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_AZ63_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(1:
- 2
- 3
4: 5
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/AZ63.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_AZW3_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(- bla"keks: foo
- bla]keks: foo
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/AZW3.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_BEC7_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(%YAML 1.3 # Attempt parsing
          # with a warning
---
"foo"
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/BEC7.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_BU8L_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(key: &anchor
 !tag
  a: b
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/BU8L.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_C2DT_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT({
"adjacent":value,
"readable": value,
"empty":
}
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/C2DT.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_C4HZ_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(%TAG ! tag:clarkevans.com,2002:
--- !shape
  # Use the ! handle for presenting
  # tag:clarkevans.com,2002:circle
- !circle
  center: &ORIGIN {x: 73, y: 129}
  radius: 7
- !line
  start: *ORIGIN
  finish: { x: 89, y: 102 }
- !label
  start: *ORIGIN
  color: 0xFFEEBB
  text: Pretty vector drawing.
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/C4HZ.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_CC74_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(%TAG !e! tag:example.com,2000:app/
---
!e!foo "bar"
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/CC74.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_CT4Q_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT([
? foo
 bar : baz
]
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/CT4Q.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_CUP7_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(anchored: !local &anchor value
alias: *anchor
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/CUP7.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_D88J_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(a: [b, c]
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/D88J.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_D9TU_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(foo: bar
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/D9TU.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_DBG4_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(# Outside flow collection:
- ::vector
- ": - ()"
- Up, up, and away!
- -123
- http://example.com/foo#bar
# Inside flow collection:
- [ ::vector,
  ": - ()",
  "Up, up and away!",
  -123,
  http://example.com/foo#bar ]
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/DBG4.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_DFF7_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT({
? explicit: entry,
implicit: entry,
?
}
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/DFF7.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_DHP8_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT([foo, bar, 42]
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/DHP8.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_DWX9_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(|
 
  
  literal
   
  
  text

 # Comment
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/DWX9.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_E76Z_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(&a a: &b b
*a : *b
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/E76Z.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_EHF6_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(!!map {
  k: !!seq
  [ a, !!str b]
}
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/EHF6.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_F2C7_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT( - &a !!str a
 - !!int 2
 - !!int &c 4
 - &d d
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/F2C7.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_F8F9_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT( # Strip
  # Comments:
strip: |-
  # text
  
 # Clip
  # comments:

clip: |
  # text
 
 # Keep
  # comments:

keep: |+
  # text

 # Trail
  # comments.
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/F8F9.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_FH7J_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(- !!str
-
  !!null : a
  b: !!str
- !!str : !!null
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/FH7J.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_FQ7F_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(- Mark McGwire
- Sammy Sosa
- Ken Griffey
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/FQ7F.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_FRK4_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(# XXX Why is ? supported in flow?
{
  ? foo :,
  : bar,
}
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/FRK4.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_FUP4_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT([a, [b, c]]
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/FUP4.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_G4RS_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(unicode: "Sosa did fine.\u263A"
control: "\b1998\t1999\t2000\n"
hex esc: "\x0d\x0a is \r\n"

single: '"Howdy!" he cried.'
quoted: ' # Not a ''comment''.'
tie-fighter: '|\-*-/|'
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/G4RS.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_G992_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(>
 folded
 text


)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/G992.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_GH63_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(? a
: 13
1.5: d
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/GH63.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_H2RW_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(foo: 1

bar: 2
    
text: |
  a
    
  b

  c
 
  d
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/H2RW.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_HMK4_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(name: Mark McGwire
accomplishment: >
  Mark set a major league
  home run record in 1998.
stats: |
  65 Home Runs
  0.278 Batting Average
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/HMK4.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_HMQ5_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(!!str &a1 "foo":
  !!str bar
&a2 baz : *a1
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/HMQ5.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_HS5T_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(1st non-empty

 2nd non-empty 
	3rd non-empty
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/HS5T.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_J3BT_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(# Tabs and spaces
quoted: "Quoted 	"
block:	|
  void main() {
  	printf("Hello, world!\n");
  }
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/J3BT.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_J5UC_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(foo: blue
bar: arrr
baz: jazz
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/J5UC.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_J7PZ_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(# Ordered maps are represented as
# A sequence of mappings, with
# each mapping having one key
--- !!omap
- Mark McGwire: 65
- Sammy Sosa: 63
- Ken Griffy: 58
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/J7PZ.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_J7VC_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(1: 2


3: 4
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/J7VC.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_J9HZ_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(---
hr: # 1998 hr ranking
  - Mark McGwire
  - Sammy Sosa
rbi:
  # 1998 rbi ranking
  - Sammy Sosa
  - Ken Griffey
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/J9HZ.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_JHB9_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(# Ranking of 1998 home runs
---
- Mark McGwire
- Sammy Sosa
- Ken Griffey

# Team ranking
---
- Chicago Cubs
- St Louis Cardinals
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/JHB9.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_JQ4R_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(block sequence:
  - one
  - two : three
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/JQ4R.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_JS2J_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(First occurrence: &anchor Value
Second occurrence: *anchor
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/JS2J.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_JTV5_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(? a
  true
: null
  d
? e
  42
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/JTV5.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_K4SU_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(- foo
- bar
- 42
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/K4SU.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_K527_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(>-
  trimmed
  
 

  as
  space
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/K527.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_K858_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(strip: >-

clip: >

keep: |+

)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/K858.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_KMK3_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(foo:
  bar: 1
baz: 2
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/KMK3.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_KSS4_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(--- "quoted
string"
--- &node foo
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/KSS4.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_KZN9_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(- [ YAML : separate ]
- [ : empty key entry ]
- [ {JSON: like}:adjacent ]
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/KZN9.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_L94M_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(? !!str a
: !!int 47
? c
: !!str d
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/L94M.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_L9U5_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(implicit block key : [
  implicit flow key : value,
 ]
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/L9U5.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_LE5A_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(- !!str "a"
- 'b'
- &anchor "c"
- *anchor
- !!str
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/LE5A.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_LP6E_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(- [a, b , c ]
- { "a"  : b
   , c : 'd' ,
   e   : "f"
  }
- [      ]
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/LP6E.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_LQZ7_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT("implicit block key" : [
  "implicit flow key" : value,
 ]
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/LQZ7.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_M29M_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(a: |
 ab
 
 cd
 ef
 

...
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/M29M.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_M5C3_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(literal: |2
  value
folded:
   !foo
  >1
 value
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/M5C3.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_M5DY_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(? - Detroit Tigers
  - Chicago cubs
:
  - 2001-07-23

? [ New York Yankees,
    Atlanta Braves ]
: [ 2001-07-02, 2001-08-12,
    2001-08-14 ]
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/M5DY.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_M7A3_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(Bare
document
...
# No document
# XXX libyaml wants a --- here
...
# XXX libyaml wants a --- here
|
# XXX literal needs indentation? libyaml sees a directive.
%!PS-Adobe-2.0 # Not the first line
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/M7A3.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_M9B4_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(|
 literal
 	text


)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/M9B4.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_MJS9_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(>
  foo 
 
  	 bar

  baz
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/MJS9.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_MXS3_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(- {a: b}
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/MXS3.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_MYW6_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(|-
 ab
 
 
...
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/MYW6.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_MZX3_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(- plain
- "double quoted"
- 'single quoted'
- >
  block
- plain again
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/MZX3.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_N782_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT([
--- ,
...
]
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/N782.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_NHX8_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(:



)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/NHX8.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_NP9H_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT("folded 
to a space,	
 
to a line feed, or 	\
 \ 	non-content"
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/NP9H.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_P2AD_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(- | # Empty header↓
 literal
- >1 # Indentation indicator↓
  folded
- |+ # Chomping indicator↓
 keep

- >1- # Both indicators↓
  strip
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/P2AD.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_P76L_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(%TAG !! tag:example.com,2000:app/
---
!!int 1 - 3 # Interval, not integer
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/P76L.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_P94K_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(key:    # Comment
        # lines
  value


)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/P94K.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_PBJ2_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(american:
  - Boston Red Sox
  - Detroit Tigers
  - New York Yankees
national:
  - New York Mets
  - Chicago Cubs
  - Atlanta Braves
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/PBJ2.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_PRH3_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(' 1st non-empty

 2nd non-empty 
	3rd non-empty '
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/PRH3.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_PW8X_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(- &a
- a
-
  &a : a
  b: &b
  &c : &a
-
  ? &d
  ? &e
  : &a
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/PW8X.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_Q88A_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(- [ a, b ]
- { a: b }
- "a"
- 'b'
- c
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/Q88A.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_Q9WF_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT({ first: Sammy, last: Sosa }:
# Statistics:
  hr:  # Home runs
     65
  avg: # Average
   0.278
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/Q9WF.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_QF4Y_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT([
foo: bar
]
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/QF4Y.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_R4YG_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(- |
 detected
- >
 
  
  # detected
- |1
  explicit
- >
 	
 detected
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/R4YG.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_RLU9_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(foo:
- 42
bar:
  - 44
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/RLU9.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_RR7F_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(a: 4.2
? 23
: d
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/RR7F.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_RTP8_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(%YAML 1.2
---
Document
# XXX Why is a comment allowed on ...?
... # Suffix
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/RTP8.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_RZT7_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(---
Time: 2001-11-23 15:01:42 -5
User: ed
Warning:
  This is an error message
  for the log file
---
Time: 2001-11-23 15:02:31 -5
User: ed
Warning:
  A slightly different error
  message.
---
Date: 2001-11-23 15:03:17 -5
User: ed
Fatal:
  Unknown variable "bar"
Stack:
  - file: TopClass.py
    line: 23
    code: |
      x = MoreObject("345\n")
  - file: MoreClass.py
    line: 58
    code: |-
      foo = bar
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/RZT7.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_S3PD_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(plain key: in-line value
: # Both empty
"quoted key":
- entry
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/S3PD.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_S4JQ_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(# Assuming conventional resolution:
- "12"
- 12
- ! 12
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/S4JQ.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_S4T7_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(aaa: bbb
...
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/S4T7.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_S9E8_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(sequence:
- one
- two
mapping:
  ? sky
  : blue
  sea : green
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/S9E8.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_SBG9_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT({a: [b, c], [d, e]: f}
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/SBG9.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_SYW4_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(hr:  65    # Home runs
avg: 0.278 # Batting average
rbi: 147   # Runs Batted In
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/SYW4.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_TE2A_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(block mapping:
 key: value
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/TE2A.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_TL85_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT("
  foo 
 
  	 bar

  baz
"
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/TL85.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_TS54_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(>
 ab
 cd
 
 ef


 gh
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/TS54.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_U3C3_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(%TAG !yaml! tag:yaml.org,2002:
---
!yaml!str "foo"
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/U3C3.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_U3XV_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(---
top1: &node1
  &k1 key1: one
top2: &node2 # comment
  key2: two
top3:
  &k3 key3: three
top4:
  &node4
  &k4 key4: four
top5:
  &node5
  key5: five
top6: &val6
  six
top7:
  &val7 seven
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/U3XV.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_U9NS_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(---
time: 20:03:20
player: Sammy Sosa
action: strike (miss)
...
---
time: 20:03:47
player: Sammy Sosa
action: grand slam
...
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/U9NS.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_UDR7_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(sequence: [ one, two, ]
mapping: { sky: blue, sea: green }
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/UDR7.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_UGM3_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(--- !<tag:clarkevans.com,2002:invoice>
invoice: 34843
date   : 2001-01-23
bill-to: &id001
    given  : Chris
    family : Dumars
    address:
        lines: |
            458 Walkman Dr.
            Suite #292
        city    : Royal Oak
        state   : MI
        postal  : 48046
ship-to: *id001
product:
    - sku         : BL394D
      quantity    : 4
      description : Basketball
      price       : 450.00
    - sku         : BL4438H
      quantity    : 1
      description : Super Hoop
      price       : 2392.00
tax  : 251.42
total: 4443.52
comments:
    Late afternoon is best.
    Backup contact is Nancy
    Billsmer @ 338-4338.
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/UGM3.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_UT92_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(---
{ matches
% : 20 }
...
---
# Empty
...
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/UT92.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_V55R_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(- &a a
- &b b
- *a
- *b
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/V55R.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_V9D5_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(- sun: yellow
- ? earth: blue
  : moon: white
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/V9D5.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_W42U_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(- # Empty
- |
 block node
- - one # Compact
  - two # sequence
- one: two # Compact mapping
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/W42U.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_W4TN_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(%YAML 1.2
--- |
%!PS-Adobe-2.0
...
%YAML1.2
---
# Empty
...
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/W4TN.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_WZ62_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT({
  foo : !!str,
  !!str : bar,
}
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/WZ62.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_X38W_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT({ &a [a, &b b]: *b, *a : [c, *b, d]}
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/X38W.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_YD5X_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(- [name        , hr, avg  ]
- [Mark McGwire, 65, 0.278]
- [Sammy Sosa  , 63, 0.288]
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/YD5X.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_Z9M4_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(%TAG !e! tag:example.com,2000:app/
---
- !e!foo "bar"
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/Z9M4.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_ZF4X_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(Mark McGwire: {hr: 65, avg: 0.278}
Sammy Sosa: {
    hr: 63,
    avg: 0.288
  }
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/ZF4X.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_ZH7C_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(&a a: b
c: &d d
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/ZH7C.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_anchors_yaml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(a: &A "Hello, World"
b: *A
c: [1, 2, &D 3, 4]
d: *D
e: &F [9, 9, 4, 6]
f: *F
g: &H h
*H: aaa
&J i: iii
x: &X
 - a
 - &B bbking
 - c
m: *B
n: *X
q: *J
p: &R >
  You're Holding It Wrong: Here's How to Hold
  Your Touch Screen Gadgets Correctly
r: *R

)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/anchors.yaml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_basic_yaml_block_yaml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(﻿american:
  - Boston Red Sox
  - Detroit Tigers
  - New York
   Yankees # this should be folded to "New York Yankees" !
national:
  - New York Mets
  - Chicago Cubs
  - Atlanta Braves
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/basic_yaml_block.yaml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_basic_yaml_block2_yaml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(﻿x:
  - a
  - b
  - c
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/basic_yaml_block2.yaml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_basic_yaml_block3_yaml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(﻿x:
  - a
  - b
  - c
y:
  - a
  - b
  - c
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/basic_yaml_block3.yaml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_basic_yaml_flow_yaml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(﻿
# Now we have comments
[
    apple ,
    Sîne
])YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/basic_yaml_flow.yaml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_block_literals_yaml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(# ASCII Art
- |           # Literal Style
  \//||\/||
  // ||  ||__
      ---> properly indented
- >
  folded
  text

  next
  line
- >
  folded
  text

  next
  line
    * bullet
    * list
    * lines
  last
  line
- >
  folded
  text

  next
  line
    * bullet

    * list
    * lines
  last
  line
- >
  default
  chomping


- >-
  strip
  chomping


- >+
  keep
  chomping


- Last)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/block_literals.yaml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_block_literals2_yaml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(accomplishment: >
  Mark set a major league
  home run record in 1998.
stats: |
  65 Home Runs
  0.278 Batting Average
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/block_literals2.yaml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_data_types_yaml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(---
a: 123                     # an integer
b: "123"                   # a string, disambiguated by quotes
c: 123.0                   # a float
d: !!float 123             # also a float via explicit data type prefixed by (''' !! ''')
e: !!str 123               # a string, disambiguated by explicit type
f: !!str Yes               # a string via explicit type
g: Yes                     # a boolean True
h: Yes we have No bananas  # a string, "Yes" and "No" disambiguated by context.)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/data-types.yaml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_invoice_yaml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(
# Below is an example of an invoice expressed via YAML(tm).
# Structure is shown through indentation (one or more spaces).
# Sequence items are denoted by a dash, and key value pairs
# within a map are separated by a colon.

--- # invoice
invoice: 34843
date   : 2001-01-23
bill-to: &id001
    given  : Chris
    family : Dumars
    address:
        lines: |
            458 Walkman Dr.
            Suite #292
        city    : Royal Oak
        state   : MI
        postal  : 48046
ship-to: *id001
product:
    - sku         : BL394D
      quantity    : 4
      description : Basketball
      price       : 450.00
    - sku         : BL4438H
      quantity    : 1
      description : Super Hoop
      price       : 2392.00
tax  : 251.42
total: 4443.52
comments: >
    Late afternoon is best.
    Backup contact is Nancy
    Billsmer @ 338-4338.

)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/invoice.yaml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_relational_yaml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(---
receipt:     Oz-Ware Purchase Invoice
date:        2007-08-06
customer:
    given:   Dorothy
    family:  Gale

items:
    - part_no:   A4786
      descrip:   Water Bucket (Filled)
      price:     1.47
      quantity:  4

    - part_no:   E1628
      descrip:   High Heeled "Ruby" Slippers
      size:      8
      price:     100.27
      quantity:  1

bill-to:  &id001
    street: |
            123 Tornado Alley
            Suite 16
    city:   East Centerville
    state:  KS

ship-to:  *id001

specialDelivery:  >
    Follow the Yellow Brick
    Road to the Emerald City.
    Pay no attention to the
    man behind the curtain.
...)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/relational.yaml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_scalar_yaml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(unicode: "Sosa did fine.\u263A"
control: "\b1998\t1999\t2000\n"
hex esc: "\x0d\x0a is \r\n"

single: '"Howdy!" he cried.'
quoted1: ' # Not a ''comment''.'
tie-fighter: '|\-*-/|'

plain:
  This unquoted scalar
  spans many lines.

quoted: "So does this
  quoted scalar.\n"

canonical-i: 12345
decimal: +12345
octal: 0o14
hexadecimal: 0xC

canonical-f: 1.23015e+3
exponential: 12.3015e+02
fixed: 1230.15
negative infinity: -.inf
not a number: .NaN

null1:
null2: ~
booleans1: [ true, false ]
hex: 0x4D2
oct: 02333
string: '012345'


## $$$ JDG FIXME UNIMPLEMENTED $$$ ##
#canonical-t: 2001-12-15T02:59:43.1Z
#iso8601: 2001-12-14t21:59:43.10-05:00
#spaced: 2001-12-14 21:59:43.10 -5
#date: 2002-12-14

!!null null: value for null key
key with null value: !!null null

negative: !!int -12
zero: !!int 0
positive: !!int 34

negative: !!float -1
zero: !!float 0
positive: !!float 2.3e4
infinity: !!float .inf
not a number: !!float .nan

A string: !!str "A string"
A numeric string: !!str 12345 # should be parsed as string



)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/scalar.yaml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_yaml_block_array1_yaml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(﻿- A
- B
- C
- [x, y, z]
- !!seq [a, b, c]
- D
- E)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/yaml_block_array1.yaml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_yaml_block_array2_yaml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(﻿- A
- B
- C
- [x, y, z]
- D
- E : yabba dabba

)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/yaml_block_array2.yaml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_yaml_block_array3_yaml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(-
- B)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/yaml_block_array3.yaml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_yaml_block_array4_yaml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(- A
-
 [
  a, b, c
 ]
- B)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/yaml_block_array4.yaml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_yaml_block_array5_yaml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(﻿- - x
  - y
-
  - a
  - b)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/yaml_block_array5.yaml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_yaml_block_array6_yaml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(﻿- - x
  - y
- a: 1
  b: 2)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/yaml_block_array6.yaml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_yaml_block_array7_yaml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(-
  name: Mark McG
  hr:   65
  avg:  0.278
-
  name: Sammy So
  hr:   63
  avg:  0.288)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/yaml_block_array7.yaml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_yaml_block_map1_yaml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(Apple : 6
Orange : [1, 2, 3]
Lemmon : !!map {a:1, b:2, c:3})YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/yaml_block_map1.yaml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_yaml_block_map10_yaml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(x :
  2
y : 3
? z
: 4
?
  w
: 9)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/yaml_block_map10.yaml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_yaml_block_map11_yaml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(null:
x: xx
z: zz)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/yaml_block_map11.yaml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_yaml_block_map12_yaml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(american:
  - Boston Red Sox
  - Detroit Tigers
  - New York Yankees
national:
  - New York Mets
  - Chicago Cubs
  - Atlanta Braves)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/yaml_block_map12.yaml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_yaml_block_map13_yaml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(Gorp : true
       is not relative
Prog : false
Burp : 3DEVENT # 3 should not be taken as an int!
Foo : on the right # strict yaml 1.2 disallows "on" as a boolean value!)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/yaml_block_map13.yaml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_yaml_block_map2_yaml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(Apple :
  x : 2
  y : 3)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/yaml_block_map2.yaml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_yaml_block_map3_yaml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(key0:
  key1: 1
  key2: # null value
  key3: 3
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/yaml_block_map3.yaml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_yaml_block_map4_yaml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(key1: 1
key2:
key3: 2
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/yaml_block_map4.yaml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_yaml_block_map5_yaml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(z :
  x : 2
  y : 3)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/yaml_block_map5.yaml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_yaml_block_map6_yaml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(the key value:
  key1: value
  key2: more value
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/yaml_block_map6.yaml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_yaml_block_map7_yaml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(Apple : 6
Orange :)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/yaml_block_map7.yaml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_yaml_block_map8_yaml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(? z
: 4)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/yaml_block_map8.yaml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_yaml_block_map9_yaml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(﻿- a: 1
  b: 2)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/yaml_block_map9.yaml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_simple_flow_plain_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(a: b
 c
d: e
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/simple_flow_plain.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_escaped_percent_27NA_yml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(\%YAML 1.2
--- text

)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/escaped_percent_27NA.yml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}

void BM_basic_yaml_block_repeated_yaml (benchmark::State & state)
{
    using yaml::ast::value_t;
    using yaml::parser::reporting_fn_t;
    using yaml::parser::parse_yaml;
    using yaml::ast::print_yaml;

    char const * contents = R"YAML_TEXT(﻿american:
  - Boston Red Sox
  - Detroit Tigers
  - New York
   Yankees # this should be folded to "New York Yankees" !
national:
  - New York Mets
  - Chicago Cubs
  - Atlanta Braves
﻿---
american:
  - Boston Red Sox
  - Detroit Tigers
  - New York
   Yankees # this should be folded to "New York Yankees" !
national:
  - New York Mets
  - Chicago Cubs
  - Atlanta Braves
...
﻿american:
  - Boston Red Sox
  - Detroit Tigers
  - New York
   Yankees # this should be folded to "New York Yankees" !
national:
  - New York Mets
  - Chicago Cubs
  - Atlanta Braves
)YAML_TEXT";

    boost::optional<std::vector<value_t>> result;
    while (state.KeepRunning()) {
        result = parse_yaml(
            g_parser,
            contents, contents + strlen(contents),
            "/Users/tzlaine/yaml_spirit/test/test_files/basic_yaml_block_repeated.yaml",
            reporting_fn_t(), reporting_fn_t()
        );
    }
    for (auto const & v : *result) {
        (void)v;
        std::cout << "";
    }
}


BENCHMARK(BM_229Q_yml);
BENCHMARK(BM_27NA_yml);
BENCHMARK(BM_2AUY_yml);
BENCHMARK(BM_2JQS_yml);
BENCHMARK(BM_2SXE_yml);
BENCHMARK(BM_2XXW_yml);
BENCHMARK(BM_35KP_yml);
BENCHMARK(BM_3ALJ_yml);
BENCHMARK(BM_3GZX_yml);
BENCHMARK(BM_3MYT_yml);
BENCHMARK(BM_4ABK_yml);
BENCHMARK(BM_4CQQ_yml);
BENCHMARK(BM_4GC6_yml);
BENCHMARK(BM_4UYU_yml);
BENCHMARK(BM_4ZYM_yml);
BENCHMARK(BM_54T7_yml);
BENCHMARK(BM_565N_yml);
BENCHMARK(BM_57H4_yml);
BENCHMARK(BM_5BVJ_yml);
BENCHMARK(BM_5C5M_yml);
BENCHMARK(BM_5GBF_yml);
BENCHMARK(BM_5KJE_yml);
BENCHMARK(BM_5NYZ_yml);
BENCHMARK(BM_5TYM_yml);
BENCHMARK(BM_5WE3_yml);
BENCHMARK(BM_65WH_yml);
BENCHMARK(BM_6BCT_yml);
BENCHMARK(BM_6CK3_yml);
BENCHMARK(BM_6FWR_yml);
BENCHMARK(BM_6H3V_yml);
BENCHMARK(BM_6HB6_yml);
BENCHMARK(BM_6JQW_yml);
BENCHMARK(BM_6JWB_yml);
BENCHMARK(BM_6LVF_yml);
BENCHMARK(BM_6M2F_yml);
BENCHMARK(BM_6SLA_yml);
BENCHMARK(BM_6VJK_yml);
BENCHMARK(BM_6ZKB_yml);
BENCHMARK(BM_735Y_yml);
BENCHMARK(BM_74H7_yml);
BENCHMARK(BM_77H8_yml);
BENCHMARK(BM_7A4E_yml);
BENCHMARK(BM_7BUB_yml);
BENCHMARK(BM_7FWL_yml);
BENCHMARK(BM_7T8X_yml);
BENCHMARK(BM_7W2P_yml);
BENCHMARK(BM_82AN_yml);
BENCHMARK(BM_87E4_yml);
BENCHMARK(BM_8G76_yml);
BENCHMARK(BM_8MK2_yml);
BENCHMARK(BM_8QBE_yml);
BENCHMARK(BM_8UDB_yml);
BENCHMARK(BM_93JH_yml);
BENCHMARK(BM_96L6_yml);
BENCHMARK(BM_98YD_yml);
BENCHMARK(BM_9FMG_yml);
BENCHMARK(BM_9J7A_yml);
BENCHMARK(BM_9SHH_yml);
BENCHMARK(BM_9U5K_yml);
BENCHMARK(BM_9WXW_yml);
BENCHMARK(BM_9YRD_yml);
BENCHMARK(BM_A2M4_yml);
BENCHMARK(BM_A6F9_yml);
BENCHMARK(BM_A984_yml);
BENCHMARK(BM_AVM7_yml);
BENCHMARK(BM_AZ63_yml);
BENCHMARK(BM_AZW3_yml);
BENCHMARK(BM_BEC7_yml);
BENCHMARK(BM_BU8L_yml);
BENCHMARK(BM_C2DT_yml);
BENCHMARK(BM_C4HZ_yml);
BENCHMARK(BM_CC74_yml);
BENCHMARK(BM_CT4Q_yml);
BENCHMARK(BM_CUP7_yml);
BENCHMARK(BM_D88J_yml);
BENCHMARK(BM_D9TU_yml);
BENCHMARK(BM_DBG4_yml);
BENCHMARK(BM_DFF7_yml);
BENCHMARK(BM_DHP8_yml);
BENCHMARK(BM_DWX9_yml);
BENCHMARK(BM_E76Z_yml);
BENCHMARK(BM_EHF6_yml);
BENCHMARK(BM_F2C7_yml);
BENCHMARK(BM_F8F9_yml);
BENCHMARK(BM_FH7J_yml);
BENCHMARK(BM_FQ7F_yml);
BENCHMARK(BM_FRK4_yml);
BENCHMARK(BM_FUP4_yml);
BENCHMARK(BM_G4RS_yml);
BENCHMARK(BM_G992_yml);
BENCHMARK(BM_GH63_yml);
BENCHMARK(BM_H2RW_yml);
BENCHMARK(BM_HMK4_yml);
BENCHMARK(BM_HMQ5_yml);
BENCHMARK(BM_HS5T_yml);
BENCHMARK(BM_J3BT_yml);
BENCHMARK(BM_J5UC_yml);
BENCHMARK(BM_J7PZ_yml);
BENCHMARK(BM_J7VC_yml);
BENCHMARK(BM_J9HZ_yml);
BENCHMARK(BM_JHB9_yml);
BENCHMARK(BM_JQ4R_yml);
BENCHMARK(BM_JS2J_yml);
BENCHMARK(BM_JTV5_yml);
BENCHMARK(BM_K4SU_yml);
BENCHMARK(BM_K527_yml);
BENCHMARK(BM_K858_yml);
BENCHMARK(BM_KMK3_yml);
BENCHMARK(BM_KSS4_yml);
BENCHMARK(BM_KZN9_yml);
BENCHMARK(BM_L94M_yml);
BENCHMARK(BM_L9U5_yml);
BENCHMARK(BM_LE5A_yml);
BENCHMARK(BM_LP6E_yml);
BENCHMARK(BM_LQZ7_yml);
BENCHMARK(BM_M29M_yml);
BENCHMARK(BM_M5C3_yml);
BENCHMARK(BM_M5DY_yml);
BENCHMARK(BM_M7A3_yml);
BENCHMARK(BM_M9B4_yml);
BENCHMARK(BM_MJS9_yml);
BENCHMARK(BM_MXS3_yml);
BENCHMARK(BM_MYW6_yml);
BENCHMARK(BM_MZX3_yml);
BENCHMARK(BM_N782_yml);
BENCHMARK(BM_NHX8_yml);
BENCHMARK(BM_NP9H_yml);
BENCHMARK(BM_P2AD_yml);
BENCHMARK(BM_P76L_yml);
BENCHMARK(BM_P94K_yml);
BENCHMARK(BM_PBJ2_yml);
BENCHMARK(BM_PRH3_yml);
BENCHMARK(BM_PW8X_yml);
BENCHMARK(BM_Q88A_yml);
BENCHMARK(BM_Q9WF_yml);
BENCHMARK(BM_QF4Y_yml);
BENCHMARK(BM_R4YG_yml);
BENCHMARK(BM_RLU9_yml);
BENCHMARK(BM_RR7F_yml);
BENCHMARK(BM_RTP8_yml);
BENCHMARK(BM_RZT7_yml);
BENCHMARK(BM_S3PD_yml);
BENCHMARK(BM_S4JQ_yml);
BENCHMARK(BM_S4T7_yml);
BENCHMARK(BM_S9E8_yml);
BENCHMARK(BM_SBG9_yml);
BENCHMARK(BM_SYW4_yml);
BENCHMARK(BM_TE2A_yml);
BENCHMARK(BM_TL85_yml);
BENCHMARK(BM_TS54_yml);
BENCHMARK(BM_U3C3_yml);
BENCHMARK(BM_U3XV_yml);
BENCHMARK(BM_U9NS_yml);
BENCHMARK(BM_UDR7_yml);
BENCHMARK(BM_UGM3_yml);
BENCHMARK(BM_UT92_yml);
BENCHMARK(BM_V55R_yml);
BENCHMARK(BM_V9D5_yml);
BENCHMARK(BM_W42U_yml);
BENCHMARK(BM_W4TN_yml);
BENCHMARK(BM_WZ62_yml);
BENCHMARK(BM_X38W_yml);
BENCHMARK(BM_YD5X_yml);
BENCHMARK(BM_Z9M4_yml);
BENCHMARK(BM_ZF4X_yml);
BENCHMARK(BM_ZH7C_yml);
BENCHMARK(BM_anchors_yaml);
BENCHMARK(BM_basic_yaml_block_yaml);
BENCHMARK(BM_basic_yaml_block2_yaml);
BENCHMARK(BM_basic_yaml_block3_yaml);
BENCHMARK(BM_basic_yaml_flow_yaml);
BENCHMARK(BM_block_literals_yaml);
BENCHMARK(BM_block_literals2_yaml);
BENCHMARK(BM_data_types_yaml);
BENCHMARK(BM_invoice_yaml);
BENCHMARK(BM_relational_yaml);
BENCHMARK(BM_scalar_yaml);
BENCHMARK(BM_yaml_block_array1_yaml);
BENCHMARK(BM_yaml_block_array2_yaml);
BENCHMARK(BM_yaml_block_array3_yaml);
BENCHMARK(BM_yaml_block_array4_yaml);
BENCHMARK(BM_yaml_block_array5_yaml);
BENCHMARK(BM_yaml_block_array6_yaml);
BENCHMARK(BM_yaml_block_array7_yaml);
BENCHMARK(BM_yaml_block_map1_yaml);
BENCHMARK(BM_yaml_block_map10_yaml);
BENCHMARK(BM_yaml_block_map11_yaml);
BENCHMARK(BM_yaml_block_map12_yaml);
BENCHMARK(BM_yaml_block_map13_yaml);
BENCHMARK(BM_yaml_block_map2_yaml);
BENCHMARK(BM_yaml_block_map3_yaml);
BENCHMARK(BM_yaml_block_map4_yaml);
BENCHMARK(BM_yaml_block_map5_yaml);
BENCHMARK(BM_yaml_block_map6_yaml);
BENCHMARK(BM_yaml_block_map7_yaml);
BENCHMARK(BM_yaml_block_map8_yaml);
BENCHMARK(BM_yaml_block_map9_yaml);
BENCHMARK(BM_simple_flow_plain_yml);
BENCHMARK(BM_escaped_percent_27NA_yml);
BENCHMARK(BM_basic_yaml_block_repeated_yaml);

BENCHMARK_MAIN()
