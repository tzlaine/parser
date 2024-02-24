include(CTest)

enable_testing()

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure --no-tests=error -C $<CONFIG>)

##################################################
# Parser tests
##################################################
add_executable(
    compile_tests
    compile_tests_main.cpp
    compile_attribute.cpp
    compile_seq_attribute.cpp
    compile_or_attribute.cpp
    compile_combining_groups.cpp
)
target_link_libraries(compile_tests parser)

function(add_test_executable name)
    set(test_name "${PROJECT_NAME}-test-${name}")
    add_executable(${test_name} ${name}.cpp)
    target_link_libraries(${test_name} parser gtest gtest_main ${link_flags})
    if (MSVC)
        target_compile_options(${test_name} PRIVATE /source-charset:utf-8 /bigobj)
    endif ()
    add_test(NAME ${test_name} COMMAND ${test_name} --gtest_catch_exceptions=1)
endfunction()

add_test_executable(all_t)
add_test_executable(search)
add_test_executable(split)
add_test_executable(replace)
add_test_executable(transform_replace)
add_test_executable(hl)
add_test_executable(aggr_tuple_assignment)
add_test_executable(parser)
add_test_executable(parser_api)
add_test_executable(parser_lazy_params)
add_test_executable(parser_if_switch)
add_test_executable(parser_rule)
add_test_executable(parser_rule_with_params)
add_test_executable(parser_action)
add_test_executable(parser_action_with_params)
add_test_executable(parser_symbol_table)
add_test_executable(tracing)
add_test_executable(parse_empty)
add_test_executable(tuple_aggregate)
add_test_executable(class_type)
add_test_executable(case_fold_generated)
add_test_executable(no_case)
add_test_executable(merge_separate)
