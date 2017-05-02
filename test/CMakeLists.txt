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

add_executable(
    parse_test
    characters.cpp
    basic_structures.cpp
    flow_style.cpp
    block_style.cpp
    stream.cpp
    parser.cpp
    parse_yaml_test.cpp
)
target_link_libraries(parse_test yaml gtest ${link_flags})
target_compile_definitions(parse_test PRIVATE -DYAML_HEADER_ONLY=0)
if (USE_ASAN OR USE_UBSAN)
    target_compile_options(parse_test PRIVATE ${link_flags})
endif()
target_compile_definitions(parse_test PRIVATE -DBOOST_SPIRIT_DEBUG) # Uncomment to get verbose trace of Spirit parse.
if (clang_on_linux)
    target_link_libraries(parse_test c++)
endif ()

# TODO: Turn this on after the parse tests pass.
if (false)
add_executable(
    parse_round_trip_test
    characters.cpp
    basic_structures.cpp
    flow_style.cpp
    block_style.cpp
    stream.cpp
    parser.cpp
    parse_yaml_round_trip_test.cpp
)
target_link_libraries(parse_round_trip_test yaml gtest ${link_flags})
target_compile_definitions(parse_round_trip_test PRIVATE -DYAML_HEADER_ONLY=0)
if (USE_ASAN OR USE_UBSAN)
    target_compile_options(parse_test PRIVATE ${link_flags})
endif()
#target_compile_definitions(parse_round_trip_test PRIVATE -DBOOST_SPIRIT_DEBUG) # Uncomment to get verbose trace of Spirit parse.

if (clang_on_linux)
    target_link_libraries(parse_round_trip_test c++)
endif ()
endif()

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
foreach (yml_file_root ${yml_file_index})
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

set(invalid_yaml_test_suite_files
    # TODO
)
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
    escaped_percent_27NA.yml
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
