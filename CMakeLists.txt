cmake_minimum_required(VERSION 3.5)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(std_flag) 
set(clang_on_linux false)
if (CMAKE_CXX_COMPILER_ID STREQUAL Clang)
    set(std_flag -std=c++11)
    add_definitions(
        ${std_flag}
        -stdlib=libc++
        -g
        -Wall
        -Wno-parentheses
        -ftemplate-depth-300
    )
    if (CMAKE_SYSTEM_NAME STREQUAL Linux)
        set(clang_on_linux true)
    endif ()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL GNU)
    set(std_flag -std=c++11)
    add_definitions(${std_flag} -g -Wall -ftemplate-depth-300)
endif ()

include(dependencies)

add_library(yaml INTERFACE)
target_include_directories(yaml INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(yaml INTERFACE boost)

add_subdirectory(test)
