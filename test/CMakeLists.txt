include_directories(${CMAKE_HOME_DIRECTORY})

include(CTest)

enable_testing()

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} -j4 -C ${CMAKE_CFG_INTDIR})


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
target_link_libraries(compile_tests parser)

macro(add_test_executable name)
    add_executable(${name} ${name}.cpp)
    set_property(TARGET ${name} PROPERTY CXX_STANDARD ${CXX_STD})
    target_link_libraries(${name} parser gtest gtest_main ${link_flags})
    add_test(NAME ${name} COMMAND ${name} --gtest_catch_exceptions=1)
endmacro()

# Disabling these.  They served their purpose, but take too long to build and
# run.  They also require a patched version of Boost.Hana, as of Boost 1.74:
# https://github.com/boostorg/hana/issues/470.
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
