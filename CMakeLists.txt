cmake_minimum_required(VERSION 3.5)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(cxx_defs)
set(std_flag) 
set(clang_on_linux false)
if (CMAKE_CXX_COMPILER_ID STREQUAL Clang)
    set(std_flag -std=c++11)
    add_definitions(-g -Wall)
    set(cxx_defs
        ${std_flag}
        -stdlib=libc++
        -Wno-parentheses
        -ftemplate-depth-300
    )
    if (CMAKE_SYSTEM_NAME STREQUAL Linux)
        set(clang_on_linux true)
    endif ()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL GNU)
    set(std_flag -std=c++11)
    add_definitions(-g -Wall) 
    set(cxx_defs ${std_flag} -ftemplate-depth-300 -Wno-parentheses) 
endif ()

include(dependencies)

find_package(PythonInterp)
if (PYTHONINTERP_FOUND)
    message("-- Found Python ${PYTHON_VERSION_STRING} (${PYTHON_EXECUTABLE})")
endif ()

add_library(yaml INTERFACE)
target_include_directories(yaml INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(yaml INTERFACE boost)

add_subdirectory(test)
add_subdirectory(perf)


set(BUILD_COMPARE_LIBYAML false CACHE BOOL "Set to true to build correctness and perf tests for libyaml.") 
if (BUILD_COMPARE_LIBYAML)
    add_subdirectory(compare_libyaml)
endif ()
