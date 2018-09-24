/**
 *   Copyright (C) 2017 Zach Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <yaml/parser/stream.hpp>

#include <gtest/gtest.h>

#include <iostream>
#include <fstream>


using boost::yaml::ast::value_t;
using boost::yaml::parser::reporting_fn_t;
using boost::yaml::parser::parse_yaml;
using boost::yaml::ast::print_yaml;

std::vector<std::string> errors;
std::vector<std::string> warnings;

auto report_error = [](std::string const & error) {
    errors.push_back(error);
};
auto report_warning = [](std::string const & warning) {
    warnings.push_back(warning);
};

void clear_reports ()
{
    errors.clear();
    warnings.clear();
}

void dump_reports ()
{
    for (auto const & error : errors) {
        std::cout << error;
    }
    for (auto const & warning : warnings) {
        std::cout << warning;
    }
}

TEST(warnings, test_reserved_directive)
{
    char const * reserved_directive_str = R"YAML(
%FOO  bar baz # Should be ignored
              # with a warning.
--- "foo"
)YAML";

    std::string const warning = R"(reserved_directive_str:2:2: warning: All directives except %YAML and %TAG are reserved for future use.  The directive '%FOO  bar baz # Should be ignored' will be ignored:
%FOO  bar baz # Should be ignored
 ^
)";

    clear_reports();

    boost::optional<std::vector<value_t>> result = parse_yaml(
        reserved_directive_str, reserved_directive_str + strlen(reserved_directive_str),
        "reserved_directive_str",
        report_error, report_warning,
        false
    );

    dump_reports();

    ASSERT_TRUE(result) << "failed initial parse of reserved_directive_str";
    ASSERT_TRUE(errors.empty()) << "initial parse of reserved_directive_str produced error messages";

    ASSERT_EQ(warnings.size(), std::size_t{1});
    EXPECT_EQ(warnings[0], warning);
}

TEST(warnings, test_yaml_directive_minor_version)
{
    char const * yaml_directive_minor_version_str = R"YAML(
%YAML 1.3 # Attempt parsing
          # with a warning
---
"foo"
)YAML";

    std::string const warning = R"(yaml_directive_minor_version_str:2:2: warning: The current document has a %YAML 1.3 directive.  This parser recognizes YAML 1.2, and so might not work.  Trying anyway...:
%YAML 1.3 # Attempt parsing
 ^
)";

    clear_reports();

    boost::optional<std::vector<value_t>> result = parse_yaml(
        yaml_directive_minor_version_str, yaml_directive_minor_version_str + strlen(yaml_directive_minor_version_str),
        "yaml_directive_minor_version_str",
        report_error, report_warning,
        false
    );

    dump_reports();

    ASSERT_TRUE(result) << "failed initial parse of yaml_directive_minor_version_str";
    ASSERT_TRUE(errors.empty()) << "initial parse of yaml_directive_minor_version_str produced error messages";

    ASSERT_EQ(warnings.size(), std::size_t{1});
    EXPECT_EQ(warnings[0], warning);
}

TEST(warnings, test_redefined_anchor)
{
    char const * redefined_anchor_str = R"YAML(
&a key1:
  key2: &a value
)YAML";

    std::string const warning_0 = R"(redefined_anchor_str:3:10: warning: Redefining anchor a:
  key2: &a value
         ^
)";
    std::string const warning_1 = R"(redefined_anchor_str:2:2: warning: The previous one was was here:
&a key1:
 ^
)";

    clear_reports();

    boost::optional<std::vector<value_t>> result = parse_yaml(
        redefined_anchor_str, redefined_anchor_str + strlen(redefined_anchor_str),
        "redefined_anchor_str",
        report_error, report_warning,
        false
    );

    dump_reports();

    ASSERT_TRUE(result) << "failed initial parse of redefined_anchor_str";
    ASSERT_TRUE(errors.empty()) << "initial parse of redefined_anchor_str produced error messages";

    ASSERT_EQ(warnings.size(), std::size_t{2});
    EXPECT_EQ(warnings[0], warning_0);
    EXPECT_EQ(warnings[1], warning_1);
}

TEST(warnings, test_duplicate_map_entry)
{
    char const * duplicate_map_entry_str = R"YAML(
y : {x: 1, x: 2, c: 3}
y : 6
)YAML";

    std::string const warning_0 = R"(duplicate_map_entry_str:2:12: warning: Ignoring map entry with duplicate key '"x"':
y : {x: 1, x: 2, c: 3}
           ^
)";
    std::string const warning_1 = R"(duplicate_map_entry_str:3:1: warning: Ignoring map entry with duplicate key '"y"':
y : 6
^
)";

    clear_reports();

    boost::optional<std::vector<value_t>> result = parse_yaml(
        duplicate_map_entry_str, duplicate_map_entry_str + strlen(duplicate_map_entry_str),
        "duplicate_map_entry_str",
        report_error, report_warning,
        false
    );

    dump_reports();

    ASSERT_TRUE(result) << "failed initial parse of duplicate_map_entry_str";
    ASSERT_TRUE(errors.empty()) << "initial parse of duplicate_map_entry_str produced error messages";

    ASSERT_EQ(warnings.size(), std::size_t{2});
    EXPECT_EQ(warnings[0], warning_0);
    EXPECT_EQ(warnings[1], warning_1);
}

int main (int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
