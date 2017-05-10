include_directories(${CMAKE_HOME_DIRECTORY})

include(CTest)

enable_testing()

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} -VV -C ${CMAKE_CFG_INTDIR})

set(USE_ASAN false CACHE BOOL "Set to true to enable -fsanitize=address when building tests.") 
set(USE_UBSAN false CACHE BOOL "Set to true to enable -fsanitize=undefined when building tests.")
if (USE_ASAN AND USE_UBSAN)
    message(FATAL_ERROR "USE_ASAN and USE_UBSAN must not be enabled at the same time")
elseif (USE_ASAN)
    set(link_flags -fsanitize=address)
elseif (USE_UBSAN)
    set(link_flags -fsanitize=undefined)
endif()

set(BUILD_HEADER_ONLY_TEST false CACHE BOOL "Set to true to build a test app with -DYAML_HEADER_ONLY=1.")


##################################################
# Header-only build test
##################################################
if (BUILD_HEADER_ONLY_TEST)
add_executable(
    header_only_parse_test
    parse_yaml_test.cpp
)
target_link_libraries(header_only_parse_test yaml gtest ${link_flags})
target_compile_definitions(header_only_parse_test PRIVATE -DYAML_HEADER_ONLY=1)
if (clang_on_linux)
    target_link_libraries(header_only_parse_test c++)
endif ()
endif ()

##################################################
# Static test lib
##################################################
add_library(
    yaml_test_lib
    STATIC
    characters.cpp
    basic_structures.cpp
    flow_style.cpp
    block_style.cpp
    stream.cpp
)
target_link_libraries(yaml_test_lib yaml gtest ${link_flags})
if (USE_ASAN OR USE_UBSAN)
    target_compile_options(yaml_test_lib PUBLIC ${link_flags})
endif()
target_compile_definitions(yaml_test_lib PUBLIC -DBOOST_SPIRIT_DEBUG) # Uncomment to get verbose trace of Spirit parse.
if (clang_on_linux)
    target_link_libraries(yaml_test_lib c++)
endif ()

##################################################
# Parse-only test executable
##################################################
add_executable(
    parse_test
    parse_yaml_test.cpp
)
target_link_libraries(parse_test yaml yaml_test_lib gtest ${link_flags})
if (clang_on_linux)
    target_link_libraries(parse_test c++)
endif ()

##################################################
# Parse-and-compare test executable
##################################################
add_executable(
    parse_compare_test
    parse_yaml_compare_test.cpp
)
target_link_libraries(parse_compare_test yaml yaml_test_lib gtest ${link_flags})
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
find_package(PythonInterp)
if (PYTHONINTERP_FOUND)
    message("-- Found Python ${PYTHON_VERSION_STRING} (${PYTHON_EXECUTABLE})")
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
else ()
    message("-- Python not found.  Yaml test inputs will not be rebuilt.")
endif()

include(test_files/index.cmake)
set(invalid_yaml_test_suite_files
    2SXE # Has the pattern a: b: without a line break.

    # Each has a bare "\" (not starting an escape sequence) outside of any
    # single- or double-quoted string, not indented, in the middle of a block
    # mapping.
    NHX8 P94K 5GBF

    # flow_in_block uses flow(n+1,c), but "quotes" in "double\nquotes is not
    # indented.
    XW4D

    ${error_yml_file_index}
)

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

foreach (yml_file_root ${invalid_yaml_test_suite_files})
    set_tests_properties(parse_test_${yml_file_root} PROPERTIES WILL_FAIL true)
endforeach()

set(test_files
    anchors.yaml
    basic_yaml_block.yaml
    basic_yaml_block2.yaml
    basic_yaml_block3.yaml
    basic_yaml_flow.yaml
    block_literals.yaml
    block_literals2.yaml
    data-types.yaml
    invoice.yaml
    relational.yaml
    scalar.yaml
    yaml_block_array1.yaml
    yaml_block_array2.yaml
    yaml_block_array3.yaml
    yaml_block_array4.yaml
    yaml_block_array5.yaml
    yaml_block_array6.yaml
    yaml_block_array7.yaml
    yaml_block_map1.yaml
    yaml_block_map10.yaml
    yaml_block_map11.yaml
    yaml_block_map12.yaml
    yaml_block_map13.yaml
    yaml_block_map2.yaml
    yaml_block_map3.yaml
    yaml_block_map4.yaml
    yaml_block_map5.yaml
    yaml_block_map6.yaml
    yaml_block_map7.yaml
    yaml_block_map8.yaml
    yaml_block_map9.yaml
    simple_flow_plain.yml
    escaped_percent_27NA.yml

    # Repeated contents of basic_yaml_block.yaml (contains >1 BOM).
    basic_yaml_block_repeated.yaml
)
foreach (test_file ${test_files})
    add_test(
        parse_test_${test_file}
        ${CMAKE_CURRENT_BINARY_DIR}/parse_test
        --gtest_catch_exceptions=1
        ${CMAKE_CURRENT_SOURCE_DIR}/test_files/${test_file}
    )
    # TODO: Turn this on after the parse tests pass.
    if (false)
        add_test(
            parse_test_round_trip_${test_file}
            ${CMAKE_CURRENT_BINARY_DIR}/parse_round_trip_test
            --gtest_catch_exceptions=1
            ${CMAKE_CURRENT_SOURCE_DIR}/test_files/${test_file}
        )
    endif()
endforeach()

set(invalid_test_files
    # TODO
)
foreach (test_file ${invalid_test_files})
    add_test(
        parse_test_${test_file}
        ${CMAKE_CURRENT_BINARY_DIR}/parse_test
        --gtest_catch_exceptions=1
        ${CMAKE_CURRENT_SOURCE_DIR}/test_files/${test_file}
    )
    set_tests_properties(parse_test_${test_file} PROPERTIES WILL_FAIL true)
endforeach()

##################################################
# Parse-and-compare tests
##################################################
set(invalid_comparison_tests
    parse_compare_test_2JQS_in_vs_json # YAML null vs. JSON "" mismatch
    parse_compare_test_4ABK_in_vs_out  # Borked yaml-out section
    parse_compare_test_4ABK_in_vs_json # YAML null vs. JSON "" mismatch
    parse_compare_test_C2DT_in_vs_json # YAML null vs. JSON "" mismatch
    parse_compare_test_DFF7_in_vs_json # YAML null vs. JSON "" mismatch
    parse_compare_test_FRK4_in_vs_json # YAML null vs. JSON "" mismatch
    parse_compare_test_S3PD_in_vs_json # YAML null vs. JSON "" mismatch

    # Contains "!!str: bar" as a map entry, but the ":" is a valid tag-char
    parse_compare_test_WZ62_in_vs_out
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

foreach (yml_file_root ${invalid_yaml_test_suite_files})
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

foreach (test ${invalid_comparison_tests})
    set_tests_properties(${test} PROPERTIES WILL_FAIL true)
endforeach()
