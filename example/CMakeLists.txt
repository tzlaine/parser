# Copyright (C) 2020 T. Zachary Laine
#
# Distributed under the Boost Software License, Version 1.0. (See
# accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)
include_directories(${CMAKE_HOME_DIRECTORY})

include(CTest)

enable_testing()

add_custom_target(run_examples COMMAND ${CMAKE_CTEST_COMMAND} -VV -C ${CMAKE_CFG_INTDIR})

macro(add_sample name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} parser)
    set_property(TARGET ${name} PROPERTY CXX_STANDARD ${CXX_STD})
    add_test(${name} ${CMAKE_CURRENT_BINARY_DIR}/${name})
endmacro()

add_sample(hello)
add_sample(trivial)
add_sample(trivial_skipper)
add_sample(semantic_actions)
add_sample(rule_intro)
add_sample(struct_rule)
add_sample(parsing_into_a_struct)
add_sample(parsing_into_a_class)
add_sample(roman_numerals)
add_sample(user_error_handler)

if (Boost_FOUND)
    if (NOT BUILD_WITHOUT_HANA)
        add_sample(self_filling_symbol_table)
        add_sample(json)
    endif()

    add_sample(callback_json)
endif()
