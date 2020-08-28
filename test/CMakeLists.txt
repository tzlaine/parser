include_directories(${CMAKE_HOME_DIRECTORY})

include(CTest)

enable_testing()

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} -j4 -C ${CMAKE_CFG_INTDIR})

set(BUILD_HEADER_ONLY_TEST false CACHE BOOL "Set to true to build a test app with -DBOOST_YAML_HEADER_ONLY=1.")


##################################################
# Parser tests
##################################################
add_executable(parser_ parser.cpp)
set_property(TARGET parser_ PROPERTY CXX_STANDARD ${CXX_STD})
target_link_libraries(parser_ parser gtest gtest_main ${link_flags})
add_test(NAME parser_ COMMAND parser_ ---gtest_catch_exceptions=1)

add_executable(parser_api parser_api.cpp)
set_property(TARGET parser_api PROPERTY CXX_STANDARD ${CXX_STD})
target_link_libraries(parser_api parser gtest gtest_main ${link_flags})
add_test(NAME parser_api COMMAND parser_api ---gtest_catch_exceptions=1)

add_executable(
    compile_tests
    compile_tests_main.cpp
    compile_seq_attribute.cpp
    compile_or_attribute.cpp
)
set_property(TARGET compile_tests PROPERTY CXX_STANDARD ${CXX_STD})
target_link_libraries(compile_tests yaml)
add_definitions(-ftemplate-backtrace-limit=0)

macro(add_test_executable name)
    add_executable(${name} ${name}.cpp)
    set_property(TARGET ${name} PROPERTY CXX_STANDARD ${CXX_STD})
    target_link_libraries(${name} parser gtest gtest_main ${link_flags})
    add_test(NAME ${name} COMMAND ${name} --gtest_catch_exceptions=1)
endmacro()

# Disabling these.  They served their purpose, but take too long to build and
# run.
#file(GLOB generated_parser_tests generated_parsers_???.cpp)
#foreach(test ${generated_parser_tests})
#    get_filename_component(test_name ${test} NAME_WE)
#    add_test_executable(${test_name})
#endforeach()

add_test_executable(parser_lazy_params)
add_test_executable(parser_if_switch)
add_test_executable(parser_rule)
add_test_executable(parser_rule_with_params)
add_test_executable(parser_action)
add_test_executable(parser_action_with_params)
add_test_executable(parser_symbol_table)

##################################################
# YAML/JSON data type tests
##################################################

add_test_executable(json_value)
add_test_executable(yaml_value)

##################################################
# Header-only build test
##################################################
if (BUILD_HEADER_ONLY_TEST)
add_executable(
    header_only_parse_test
    parse_yaml_test.cpp
)
set_property(TARGET header_only_parse_test PROPERTY CXX_STANDARD ${CXX_STD})
target_link_libraries(header_only_parse_test yaml gtest ${link_flags})
target_compile_definitions(header_only_parse_test PRIVATE -DBOOST_YAML_HEADER_ONLY=1)
endif ()

##################################################
# Parse-only test executable
##################################################
add_executable(
    parse_yaml_test
    parse_yaml_test.cpp
)
set_property(TARGET parse_yaml_test PROPERTY CXX_STANDARD ${CXX_STD})
target_link_libraries(parse_yaml_test yaml gtest ${link_flags})

add_executable(
    parse_json_test
    parse_json_test.cpp
)
set_property(TARGET parse_json_test PROPERTY CXX_STANDARD ${CXX_STD})
target_link_libraries(parse_json_test yaml gtest ${link_flags})



# TODO: Temporary build for experimental JSON parser.
add_executable(
    json_parser
    json_parser.cpp
)
set_property(TARGET json_parser PROPERTY CXX_STANDARD ${CXX_STD})
target_link_libraries(json_parser yaml ${link_flags})



##################################################
# Parse-and-compare test executable
##################################################
add_executable(
    parse_compare_test
    parse_yaml_compare_test.cpp
)
set_property(TARGET parse_compare_test PROPERTY CXX_STANDARD ${CXX_STD})
target_link_libraries(parse_compare_test yaml gtest ${link_flags})

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
set_property(TARGET parse_round_trip_test PROPERTY CXX_STANDARD ${CXX_STD})
target_link_libraries(parse_round_trip_test yaml gtest ${link_flags})
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
        parse_yaml_test_${yml_file_root}
        ${CMAKE_CURRENT_BINARY_DIR}/parse_yaml_test
        --gtest_catch_exceptions=1
        ${CMAKE_CURRENT_SOURCE_DIR}/test_files/${yml_file_root}.yml
    )
    # TODO: Turn this on after the parse tests pass.
    if (false)
        add_test(
            parse_yaml_test_round_trip_${yml_file_root}
            ${CMAKE_CURRENT_BINARY_DIR}/parse_round_trip_test
            --gtest_catch_exceptions=1
            ${CMAKE_CURRENT_SOURCE_DIR}/test_files/${yml_file_root}.yml
        )
    endif()
endforeach()

foreach (yml_file_root ${expected_parse_failures})
    set_tests_properties(parse_yaml_test_${yml_file_root} PROPERTIES WILL_FAIL true)
endforeach()

include(test_files/local_index.cmake)
foreach (test_file ${local_test_files})
    add_test(
        parse_yaml_test_${test_file}
        ${CMAKE_CURRENT_BINARY_DIR}/parse_yaml_test
        ${CMAKE_CURRENT_SOURCE_DIR}/test_files/${test_file}
    )
    # TODO: Turn this on after the parse tests pass.
    if (false)
        add_test(
            parse_yaml_test_round_trip_${test_file}
            ${CMAKE_CURRENT_BINARY_DIR}/parse_round_trip_test
            ${CMAKE_CURRENT_SOURCE_DIR}/test_files/${test_file}
        )
    endif()
endforeach()

foreach (test_file ${error_local_test_files})
    add_test(
        parse_yaml_test_${test_file}
        ${CMAKE_CURRENT_BINARY_DIR}/parse_yaml_test
        ${CMAKE_CURRENT_SOURCE_DIR}/test_files/${test_file}
    )
    set_tests_properties(parse_yaml_test_${test_file} PROPERTIES WILL_FAIL true)
endforeach()

foreach (test_file ${json_file_index})
    add_test(
        parse_json_test_${test_file}
        ${CMAKE_CURRENT_BINARY_DIR}/parse_json_test
        --gtest_catch_exceptions=1
        ${CMAKE_SOURCE_DIR}/JSONTestSuite/test_parsing/${test_file}
    )
endforeach()

foreach (test_file ${error_json_file_index})
   add_test(
       parse_json_test_${test_file}
       ${CMAKE_CURRENT_BINARY_DIR}/parse_json_test
       --gtest_catch_exceptions=1
       ${CMAKE_SOURCE_DIR}/JSONTestSuite/test_parsing/${test_file}
   )
   set_tests_properties(parse_json_test_${test_file} PROPERTIES WILL_FAIL true)
endforeach()

set(expected_json_parse_failures
    # These fail, and all have the "i_" prefix, indicating that they need not
    # be parsed correctly to be JSON-conformant.
    i_string_UTF-16LE_with_BOM.json
    i_string_utf16BE_no_BOM.json
    i_string_utf16LE_no_BOM.json
    i_structure_UTF-8_BOM_empty_object.json
)

foreach (yml_file_root ${expected_json_parse_failures})
    set_tests_properties(parse_json_test_${yml_file_root} PROPERTIES WILL_FAIL true)
endforeach()

set(expected_json_parse_non_failures)

foreach (yml_file_root ${expected_json_parse_non_failures})
    set_tests_properties(parse_json_test_${yml_file_root} PROPERTIES WILL_FAIL false)
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
set_property(TARGET warnings_test_bin PROPERTY CXX_STANDARD ${CXX_STD})
target_link_libraries(warnings_test_bin yaml gtest ${link_flags})
add_test(
    warnings_test
    ${CMAKE_CURRENT_BINARY_DIR}/warnings_test_bin
    --gtest_catch_exceptions=1
)
