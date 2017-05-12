include(CTest)

enable_testing()

add_custom_target(libyaml_check COMMAND ${CMAKE_CTEST_COMMAND} -C ${CMAKE_CFG_INTDIR})

include(${CMAKE_HOME_DIRECTORY}/test/test_files/index.cmake)
include(${CMAKE_HOME_DIRECTORY}/test/test_files/index_xfail.cmake)
list(APPEND expected_parse_failures ${error_yml_file_index})


##################################################
# Parse-only tests
##################################################
foreach (yml_file_root ${yml_file_index} ${error_yml_file_index})
    add_test(
        libyaml_parse_test_${yml_file_root}
        ${CMAKE_BINARY_DIR}/compare_libyaml/run-parser
        ${CMAKE_HOME_DIRECTORY}/test/test_files/${yml_file_root}.yml
    )
endforeach()

foreach (yml_file_root ${expected_parse_failures})
    set_tests_properties(libyaml_parse_test_${yml_file_root} PROPERTIES WILL_FAIL true)
endforeach()

foreach (test_file ${local_test_files})
    add_test(
        libyaml_parse_test_${test_file}
        ${CMAKE_BINARY_DIR}/compare_libyaml/run-parser
        ${CMAKE_HOME_DIRECTORY}/test/test_files/${test_file}
    )
endforeach()
