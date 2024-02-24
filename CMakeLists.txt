cmake_minimum_required(VERSION 3.15)
project(parse)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_definitions(-Wall)
endif ()

##################################################
# Build config
##################################################
set(BUILD_WITHOUT_HANA false CACHE BOOL "Build with BOOST_PARSER_DISABLE_HANA_TUPLE defined.")

##################################################
# Dependencies
##################################################
find_package(Boost)
# GoogleTest
add_subdirectory(${PROJECT_SOURCE_DIR}/googletest-release-1.10.0)

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
target_include_directories(parser INTERFACE ${PROJECT_SOURCE_DIR}/include)
target_compile_features(parser INTERFACE cxx_std_17)
if (Boost_FOUND)
   target_link_libraries(parser INTERFACE Boost::headers)
endif()
if (BUILD_WITHOUT_HANA)
  target_compile_definitions(parser PUBLIC BOOST_PARSER_DISABLE_HANA_TUPLE)
endif()

##################################################
# Subdirectories
##################################################
add_subdirectory(test)
add_subdirectory(example)
