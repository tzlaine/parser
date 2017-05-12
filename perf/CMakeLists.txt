add_definitions(${cxx_defs})

# TODO: Add library to top-level CMakeLists.txt, and reuse it here and in test/.

macro(add_perf_executable name)
    add_executable(
        ${name}
        ${name}.cpp
        ${CMAKE_SOURCE_DIR}/test/characters.cpp
        ${CMAKE_SOURCE_DIR}/test/basic_structures.cpp
        ${CMAKE_SOURCE_DIR}/test/flow_style.cpp
        ${CMAKE_SOURCE_DIR}/test/block_style.cpp
        ${CMAKE_SOURCE_DIR}/test/stream.cpp
    )
    target_link_libraries(${name} yaml benchmark ${link_flags})
    if (clang_on_linux)
        target_link_libraries(${name} c++)
    endif ()
endmacro()


include(${CMAKE_HOME_DIRECTORY}/test/test_files/local_index.cmake) 
include(${CMAKE_HOME_DIRECTORY}/test/test_files/index.cmake)
include(${CMAKE_HOME_DIRECTORY}/test/test_files/index_xfail.cmake)


if (PYTHONINTERP_FOUND)
    message("-- Running make_parser_perf_test.py -y ${CMAKE_HOME_DIRECTORY}/yaml-test-suite -o ${CMAKE_CURRENT_SOURCE_DIR}/test_files ...")
    execute_process(
        COMMAND
            ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/make_parser_perf_test.py
            -y ${CMAKE_SOURCE_DIR}/test
            -o ${CMAKE_SOURCE_DIR}/perf
            --tests ${yml_file_index} ${local_test_files}
            --xfail-tests ${expected_parse_failures}
        RESULT_VARIABLE
            result
    )
    if (result STREQUAL "" OR result EQUAL 0)
         message("     ... Success!")
    else ()
         message("     *** Failed with result=\"${result}\" ***!")
    endif()
else ()
    message("-- Python not found.  Yaml parse perf test will not be rebuilt.")
endif()


add_perf_executable(parse_perf)
