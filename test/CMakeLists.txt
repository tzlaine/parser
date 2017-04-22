include_directories(${CMAKE_HOME_DIRECTORY})

include(CTest)

enable_testing()

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} -VV -C ${CMAKE_CFG_INTDIR})

add_executable(parse_test block.cpp flow.cpp parser.cpp scalar.cpp yaml.cpp parse_yaml_test.cpp)
target_link_libraries(parse_test yaml gtest)
target_compile_definitions(parse_test PRIVATE -DYAML_HEADER_ONLY=0)
#target_compile_definitions(parse_test PRIVATE -DBOOST_SPIRIT_DEBUG) # Uncomment to get verbose trace of Spirit parse.
if (clang_on_linux)
    target_link_libraries(parse_test c++)
endif ()

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
#TODO    scalar.yaml # Appears to infinitely loop or recurse, depending on compiler.
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
)
foreach (test_file ${test_files})
    add_test(
        parse_test_${test_file}
        ${CMAKE_CURRENT_BINARY_DIR}/parse_test
        --gtest_catch_exceptions=1
        ${CMAKE_CURRENT_SOURCE_DIR}/test_files/${test_file}
    )
endforeach()
