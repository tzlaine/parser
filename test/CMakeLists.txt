include_directories(${CMAKE_HOME_DIRECTORY})

include(CTest)

enable_testing()

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} -C ${CMAKE_CFG_INTDIR})

set(BUILD_HEADER_ONLY_TEST false CACHE BOOL "Set to true to build a test app with -DBOOST_YAML_HEADER_ONLY=1.")


##################################################
# Header-only build test
##################################################
if (BUILD_HEADER_ONLY_TEST)
add_executable(
    header_only_parse_test
    parse_yaml_test.cpp
)
target_link_libraries(header_only_parse_test yaml gtest ${link_flags})
target_compile_definitions(header_only_parse_test PRIVATE -DBOOST_YAML_HEADER_ONLY=1)  
if (clang_on_linux)
    target_link_libraries(header_only_parse_test c++)
endif ()
endif ()

##################################################
# Parse-only test executable
##################################################
add_executable(
    parse_test
    parse_yaml_test.cpp
)
target_link_libraries(parse_test yaml gtest ${link_flags})
if (clang_on_linux)
    target_link_libraries(parse_test c++)
endif ()



# TODO: Temporary build for experimental JSON parser.
add_executable(
    json_parser
    json_parser.cpp
)
target_compile_features(json_parser PRIVATE cxx_generic_lambdas)
target_include_directories(json_parser PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(json_parser PUBLIC boost)
if (clang_on_linux)
    target_link_libraries(json_parser c++)
endif ()



##################################################
# Parse-and-compare test executable
##################################################
add_executable(
    parse_compare_test
    parse_yaml_compare_test.cpp
)
target_link_libraries(parse_compare_test yaml gtest ${link_flags})
if (clang_on_linux)
    target_link_libraries(parse_compare_test c++)
endif ()

##################################################
# Parse-write-read round-trip test executable
##################################################
# TODO: Turn this on after the parse tests pass.
if (false)
add_executable(
    parse_round_trip_test
    characters.cpp
    basic_structures.cpp
    flow_style.cpp
    block_style.cpp
    stream.cpp
    parse_yaml_round_trip_test.cpp
)
target_link_libraries(parse_round_trip_test yaml gtest ${link_flags})

if (clang_on_linux)
    target_link_libraries(parse_round_trip_test c++)
endif ()
endif()

##################################################
# Make test files from .tml files
##################################################
if (PYTHONINTERP_FOUND)
    message("-- Running make_test_suite_yaml.py -y ${CMAKE_HOME_DIRECTORY}/yaml-test-suite -o ${CMAKE_CURRENT_SOURCE_DIR}/test_files ...")
    execute_process(
        COMMAND
            ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/make_test_suite_yaml.py
            -y ${CMAKE_HOME_DIRECTORY}/yaml-test-suite
            -o ${CMAKE_CURRENT_SOURCE_DIR}/test_files
        RESULT_VARIABLE
            result
    )
    if (result STREQUAL "" OR result EQUAL 0)
         message("     ... Success!")
    else ()
         message("     *** Failed with result=\"${result}\" ***!")
    endif()

    message("-- Running make_test_suite_json.py -y ${CMAKE_HOME_DIRECTORY}/JSONTestSuite -o ${CMAKE_CURRENT_SOURCE_DIR}/test_files ...")
    execute_process(
        COMMAND
            ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/make_test_suite_json.py
            -y ${CMAKE_HOME_DIRECTORY}/JSONTestSuite
            -o ${CMAKE_CURRENT_SOURCE_DIR}/test_files
        RESULT_VARIABLE
            result
    )
    if (result STREQUAL "" OR result EQUAL 0)
         message("     ... Success!")
    else ()
         message("     *** Failed with result=\"${result}\" ***!")
    endif()
else ()
    message("-- Python not found.  YAML and JSON test inputs will not be rebuilt.")
endif()

include(test_files/index.cmake) 
include(test_files/index_xfail.cmake)
list(APPEND expected_parse_failures ${error_yml_file_index})
include(test_files/json_index.cmake)

##################################################
# Parse-only tests
##################################################
foreach (yml_file_root ${yml_file_index} ${error_yml_file_index})
    add_test(
        parse_test_${yml_file_root}
        ${CMAKE_CURRENT_BINARY_DIR}/parse_test
        --gtest_catch_exceptions=1
        ${CMAKE_CURRENT_SOURCE_DIR}/test_files/${yml_file_root}.yml
    )
    # TODO: Turn this on after the parse tests pass.
    if (false)
        add_test(
            parse_test_round_trip_${yml_file_root}
            ${CMAKE_CURRENT_BINARY_DIR}/parse_round_trip_test
            --gtest_catch_exceptions=1
            ${CMAKE_CURRENT_SOURCE_DIR}/test_files/${yml_file_root}.yml
        )
    endif()
endforeach()

foreach (yml_file_root ${expected_parse_failures})
    set_tests_properties(parse_test_${yml_file_root} PROPERTIES WILL_FAIL true)
endforeach()

include(test_files/local_index.cmake)
foreach (test_file ${local_test_files})
    add_test(
        parse_test_${test_file}
        ${CMAKE_CURRENT_BINARY_DIR}/parse_test
        ${CMAKE_CURRENT_SOURCE_DIR}/test_files/${test_file}
    )
    # TODO: Turn this on after the parse tests pass.
    if (false)
        add_test(
            parse_test_round_trip_${test_file}
            ${CMAKE_CURRENT_BINARY_DIR}/parse_round_trip_test
            ${CMAKE_CURRENT_SOURCE_DIR}/test_files/${test_file}
        )
    endif()
endforeach()

foreach (test_file ${error_local_test_files})
    add_test(
        parse_test_${test_file}
        ${CMAKE_CURRENT_BINARY_DIR}/parse_test
        ${CMAKE_CURRENT_SOURCE_DIR}/test_files/${test_file}
    )
    set_tests_properties(parse_test_${test_file} PROPERTIES WILL_FAIL true)
endforeach()

foreach (test_file ${json_file_index})
    # TODO: This file seems to hang the parser.  Update: it's a perf issue!
    if (NOT ${test_file} STREQUAL i_structure_500_nested_arrays.json)
    add_test(
        parse_test_${test_file}
        ${CMAKE_CURRENT_BINARY_DIR}/parse_test
        --gtest_catch_exceptions=1
        ${CMAKE_SOURCE_DIR}/JSONTestSuite/test_parsing/${test_file}
    )
    endif ()
endforeach()

foreach (test_file ${error_json_file_index})
    add_test(
        parse_test_${test_file}
        ${CMAKE_CURRENT_BINARY_DIR}/parse_test
        --gtest_catch_exceptions=1
        ${CMAKE_SOURCE_DIR}/JSONTestSuite/test_parsing/${test_file}
    )
    set_tests_properties(parse_test_${test_file} PROPERTIES WILL_FAIL true)
endforeach()

set(expected_json_parse_failures
    # These fail, and all have the "i_" prefix, indicating that they need not
    # be parsed correctly to be JSON-conformant.
    i_string_UTF-16LE_with_BOM.json
    i_string_utf16BE_no_BOM.json
    i_string_utf16LE_no_BOM.json
)

foreach (yml_file_root ${expected_json_parse_failures})
    set_tests_properties(parse_test_${yml_file_root} PROPERTIES WILL_FAIL true)
endforeach()

set(expected_json_parse_non_failures
    # Parsed just fine as YAML, since it is a superset of JSON.
    n_array_1_true_without_comma.json
    n_array_a_invalid_utf8.json 
    n_array_colon_instead_of_comma.json
    n_array_extra_comma.json
    n_array_invalid_utf8.json
    n_array_items_separated_by_semicolon.json
    n_array_number_and_comma.json
    n_incomplete_false.json
    n_incomplete_null.json
    n_incomplete_true.json
    n_number_++.json
    n_number_+1.json
    n_number_+Inf.json
    n_number_-01.json
    n_number_-1.0..json
    n_number_-2..json
    n_number_-NaN.json
    n_number_.-1.json
    n_number_.2e-3.json
    n_number_0.1.2.json
    n_number_0.3e+.json
    n_number_0.3e.json
    n_number_0.e1.json
    n_number_0_capital_E+.json
    n_number_0_capital_E.json
    n_number_0e+.json
    n_number_0e.json
    n_number_1.0e+.json
    n_number_1.0e-.json
    n_number_1.0e.json
    n_number_1_000.json
    n_number_1eE2.json
    n_number_2.e+3.json
    n_number_2.e-3.json
    n_number_2.e3.json
    n_number_9.e+.json
    n_number_Inf.json
    n_number_NaN.json
    n_number_U+FF11_fullwidth_digit_one.json
    n_number_expression.json
    n_number_hex_1_digit.json
    n_number_hex_2_digits.json
    n_number_infinity.json
    n_number_invalid+-.json
    n_number_invalid-negative-real.json
    n_number_invalid-utf-8-in-bigger-int.json
    n_number_invalid-utf-8-in-exponent.json
    n_number_invalid-utf-8-in-int.json
    n_number_minus_infinity.json
    n_number_minus_sign_with_trailing_garbage.json
    n_number_neg_int_starting_with_zero.json
    n_number_neg_real_without_int_part.json
    n_number_neg_with_garbage_at_end.json
    n_number_real_garbage_after_e.json
    n_number_real_with_invalid_utf8_after_e.json
    n_number_real_without_fractional_part.json
    n_number_starting_with_dot.json
    n_number_with_alpha.json
    n_number_with_alpha_char.json
    n_number_with_leading_zero.json
    n_object_bad_value.json
    n_object_comma_instead_of_colon.json
    n_object_double_colon.json
    n_object_emoji.json
    n_object_key_with_single_quotes.json
    n_object_non_string_key_but_huge_number_instead.json
    n_object_pi_in_key_and_trailing_comma.json
    n_object_repeated_null_null.json
    n_object_single_quote.json
    n_object_trailing_comma.json
    n_object_unquoted_key.json
    n_object_with_single_string.json
    n_single_space.json
    n_string_accentuated_char_no_quotes.json
    n_string_escape_x.json
    n_string_escaped_ctrl_char_tab.json
    n_string_invalid_backslash_esc.json
    n_string_leading_uescaped_thinspace.json
    n_string_no_quotes_with_bad_escape.json
    n_string_single_quote.json
    n_string_single_string_no_double_quotes.json
    n_string_unescaped_newline.json
    n_string_unescaped_tab.json
    n_structure_U+2060_word_joined.json
    n_structure_UTF8_BOM_no_data.json
    n_structure_angle_bracket_..json
    n_structure_angle_bracket_null.json
    n_structure_ascii-unicode-identifier.json
    n_structure_capitalized_True.json
    n_structure_close_unopened_array.json
    n_structure_incomplete_UTF8_BOM.json
    n_structure_lone-invalid-utf-8.json
    n_structure_no_data.json
    n_structure_number_with_trailing_garbage.json
    n_structure_object_with_comment.json
    n_structure_single_eacute.json
    n_structure_uescaped_LF_before_string.json
    n_structure_unicode-identifier.json
    n_structure_whitespace_U+2060_word_joiner.json
    n_structure_whitespace_formfeed.json
    n_object_missing_key.json
    n_object_non_string_key.json
)

foreach (yml_file_root ${expected_json_parse_non_failures})
    set_tests_properties(parse_test_${yml_file_root} PROPERTIES WILL_FAIL false)
endforeach()

##################################################
# Parse-and-compare tests
##################################################
set(expected_comparison_failures
    parse_compare_test_2JQS_in_vs_json # YAML null vs. JSON "" mismatch
    parse_compare_test_4ABK_in_vs_out  # Borked yaml-out section
    parse_compare_test_4ABK_in_vs_json # YAML null vs. JSON "" mismatch
    parse_compare_test_C2DT_in_vs_json # YAML null vs. JSON "" mismatch
    parse_compare_test_DFF7_in_vs_json # YAML null vs. JSON "" mismatch
    parse_compare_test_FRK4_in_vs_json # YAML null vs. JSON "" mismatch
    parse_compare_test_S3PD_in_vs_json # YAML null vs. JSON "" mismatch

    # Contains "!!str: bar" as a map entry, but the ":" is a valid tag-char
    parse_compare_test_WZ62_in_vs_out
    parse_compare_test_FH7J_in_vs_out

    # Badly broken test (libyaml-specific stuff, plus a literal with a
    # non-comment "# <comment>" pattern in it.
    parse_compare_test_M7A3_in_vs_out

    # YAML version is empty (-- no documents), and the JSON version is a doc
    # containing a single null.
    parse_compare_test_AVM7_in_vs_json

    # JSON output is missing one of the ": - ()" elements.
    parse_compare_test_DBG4_in_vs_json

    # TODO: Address later.  This is due to the lack of typesafe parsing.  This
    # is the thing that requires the Nablialek trick.
    # null vs."null" mismatch
    parse_compare_test_7W2P_in_vs_json
    parse_compare_test_JTV5_in_vs_json
    parse_compare_test_5WE3_in_vs_json
    parse_compare_test_W42U_in_vs_json
    parse_compare_test_NHX8_in_vs_json
)

foreach (yml_file_root ${yml_file_index})
    if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/test_files/${yml_file_root}-out.yml)
        add_test(
            parse_compare_test_${yml_file_root}_in_vs_out
            ${CMAKE_CURRENT_BINARY_DIR}/parse_compare_test
            --gtest_catch_exceptions=1
            ${CMAKE_CURRENT_SOURCE_DIR}/test_files/${yml_file_root}.yml
            ${CMAKE_CURRENT_SOURCE_DIR}/test_files/${yml_file_root}-out.yml
        )
        set(parse_compare_test_${yml_file_root}_in_vs_out_sentinal true)
    endif()
    if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/test_files/${yml_file_root}.json)
        add_test(
            parse_compare_test_${yml_file_root}_in_vs_json
            ${CMAKE_CURRENT_BINARY_DIR}/parse_compare_test
            --gtest_catch_exceptions=1
            ${CMAKE_CURRENT_SOURCE_DIR}/test_files/${yml_file_root}.yml
            ${CMAKE_CURRENT_SOURCE_DIR}/test_files/${yml_file_root}.json
        )
        set(parse_compare_test_${yml_file_root}_in_vs_json_sentinal true)
    endif()
endforeach()

foreach (yml_file_root ${expected_parse_failures})
    if (DEFINED parse_compare_test_${yml_file_root}_in_vs_out_sentinal)
        set_tests_properties(
            parse_compare_test_${yml_file_root}_in_vs_out
            PROPERTIES
                WILL_FAIL true
        )
    endif()
    if (DEFINED parse_compare_test_${yml_file_root}_in_vs_json_sentinal)
        set_tests_properties(
            parse_compare_test_${yml_file_root}_in_vs_json
            PROPERTIES
                WILL_FAIL true
        )
    endif()
endforeach()

foreach (test ${expected_comparison_failures})
    set_tests_properties(${test} PROPERTIES WILL_FAIL true)
endforeach()

##################################################
# Warnings test
##################################################
add_executable(
    warnings_test_bin
    warnings_test.cpp
)
target_link_libraries(warnings_test_bin yaml gtest ${link_flags})
if (clang_on_linux)
    target_link_libraries(warnings_test_bin c++)
endif ()
add_test(
    warnings_test
    ${CMAKE_CURRENT_BINARY_DIR}/warnings_test_bin
    --gtest_catch_exceptions=1
)
