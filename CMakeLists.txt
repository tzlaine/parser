cmake_minimum_required(VERSION 3.5)
project(yaml)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

##################################################
# C++ standard version selection
##################################################
set(CXX_STD 14 CACHE STRING "Set to 14, 17, etc., to enable C++14, C++17, etc.")
message("-- Using -std=c++${CXX_STD}")

set(cxx_defs)
set(clang_on_linux false)
if (CMAKE_CXX_COMPILER_ID STREQUAL Clang)
    add_definitions(-g -Wall)
    set(cxx_defs
        -stdlib=libc++
        -Wno-parentheses
        -ftemplate-depth-300
    )
    if (CMAKE_SYSTEM_NAME STREQUAL Linux)
        set(clang_on_linux true)
    endif ()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL GNU)
    add_definitions(-g -Wall)
    set(cxx_defs -ftemplate-depth-300 -Wno-parentheses) 
endif ()

include(dependencies)

find_package(PythonInterp)
if (PYTHONINTERP_FOUND)
    message("-- Found Python ${PYTHON_VERSION_STRING} (${PYTHON_EXECUTABLE})")
endif ()


##################################################
# Sanitizers
##################################################
set(USE_ASAN false CACHE BOOL "Set to true to enable -fsanitize=address when building tests.") 
set(USE_UBSAN false CACHE BOOL "Set to true to enable -fsanitize=undefined when building tests.")
if (USE_ASAN AND USE_UBSAN)
    message(FATAL_ERROR "USE_ASAN and USE_UBSAN must not be enabled at the same time")
elseif (USE_ASAN)
    set(link_flags -fsanitize=address)
elseif (USE_UBSAN)
    set(link_flags -fsanitize=undefined)
endif()


##################################################
# Parser sub-library
##################################################
add_library(parser INTERFACE)
target_include_directories(parser INTERFACE ${CMAKE_SOURCE_DIR}/include)



# TODO: Turn this on if a static lib is desired; there's no need for it now.
if (false)
##################################################
# Static lib
##################################################
add_library(
    yaml-static
    STATIC
    src/characters.cpp
    src/basic_structures.cpp
    src/flow_style.cpp
    src/block_style.cpp
    src/stream.cpp
    src/json.cpp
    src/yaml.cpp
)
target_compile_options(yaml-static PUBLIC ${cxx_defs})
set_property(TARGET yaml-static PROPERTY CXX_STANDARD ${CXX_STD})
target_include_directories(yaml-static PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(yaml-static PUBLIC boost)
target_link_libraries(yaml-static ${link_flags})
if (USE_ASAN OR USE_UBSAN)
    target_compile_options(yaml-static PUBLIC ${link_flags})
endif()
if (clang_on_linux)
    target_compile_options(yaml PUBLIC -stdlib=libstdc++)
endif ()
endif ()


##################################################
# Dynamic lib
##################################################
add_library(
    yaml
    SHARED
    src/characters.cpp
    src/basic_structures.cpp
    src/flow_style.cpp
    src/block_style.cpp
    src/stream.cpp
    src/json.cpp
    src/yaml.cpp
)
set_property(TARGET yaml PROPERTY CXX_STANDARD ${CXX_STD})
target_include_directories(yaml PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(yaml PUBLIC boost)
target_link_libraries(yaml ${link_flags})
if (USE_ASAN OR USE_UBSAN)
    target_compile_options(yaml PUBLIC ${link_flags})
endif()
if (clang_on_linux)
    target_compile_options(yaml PUBLIC -stdlib=libstdc++)
endif ()


add_subdirectory(test)
add_subdirectory(perf)


set(BUILD_COMPARE_LIBYAML false CACHE BOOL "Set to true to build correctness and perf tests for libyaml.") 
if (BUILD_COMPARE_LIBYAML)
    add_subdirectory(compare_libyaml)
endif ()
