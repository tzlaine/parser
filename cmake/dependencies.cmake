# Copyright Louis Dionne 2016
# Copyright Zach Laine 2016
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

###############################################################################
# Boost
###############################################################################
if (NOT BUILD_WITHOUT_BOOST)
  set(Boost_USE_STATIC_LIBS ON)
  find_package(Boost 1.71.0 COMPONENTS ${boost_components})
  if (Boost_INCLUDE_DIR)
    add_library(boost INTERFACE)
    target_include_directories(boost INTERFACE ${Boost_INCLUDE_DIR})
  else ()
    if (NOT EXISTS boost_root)
      if (NOT BOOST_BRANCH)
        set(BOOST_BRANCH master)
      endif()
      if (NOT EXISTS ${CMAKE_BINARY_DIR}/boost_root)
        message("-- Boost was not found; it will be cloned locally from ${BOOST_BRANCH}.")
        add_custom_target(
          boost_root_clone
          git clone --depth 100 -b ${BOOST_BRANCH}
            https://github.com/boostorg/boost.git boost_root
          WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
        if (MSVC)
          set(bootstrap_cmd ./bootstrap.bat)
        else()
          set(bootstrap_cmd ./bootstrap.sh)
        endif()
        add_custom_target(
          boost_clone
          COMMAND git submodule init libs/assert
          COMMAND git submodule init libs/config
          COMMAND git submodule init libs/container
          COMMAND git submodule init libs/core
          COMMAND git submodule init libs/container_hash
          COMMAND git submodule init libs/detail
          COMMAND git submodule init libs/hana
          COMMAND git submodule init libs/intrusive
          COMMAND git submodule init libs/move
          COMMAND git submodule init libs/mpl
          COMMAND git submodule init libs/predef
          COMMAND git submodule init libs/preprocessor
          COMMAND git submodule init libs/static_assert
          COMMAND git submodule init libs/type_index
          COMMAND git submodule init libs/type_traits
          COMMAND git submodule init libs/throw_exception
          COMMAND git submodule init libs/utility
          COMMAND git submodule init tools/build
          COMMAND git submodule init libs/headers
          COMMAND git submodule init tools/boost_install
          COMMAND git submodule update --jobs 3 --depth 100
          COMMAND ${bootstrap_cmd}
          COMMAND ./b2 headers
          WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/boost_root
          DEPENDS boost_root_clone)
      endif()
      add_library(boost INTERFACE)
      add_dependencies(boost boost_clone)
    else()
      add_library(boost INTERFACE)
    endif()
    target_include_directories(boost INTERFACE ${CMAKE_BINARY_DIR}/boost_root)
  endif ()
else()
  add_library(boost INTERFACE)
endif ()


###############################################################################
# GoogleTest
###############################################################################
add_subdirectory(${CMAKE_SOURCE_DIR}/googletest-release-1.10.0)
target_include_directories(gtest      INTERFACE ${CMAKE_HOME_DIRECTORY}/googletest-release-1.10.0/googletest/include)
target_include_directories(gtest_main INTERFACE ${CMAKE_HOME_DIRECTORY}/googletest-release-1.10.0/googletest/include)


###############################################################################
# Google Benchmark
###############################################################################
add_subdirectory(${CMAKE_SOURCE_DIR}/benchmark-v1.1.0)
target_include_directories(benchmark INTERFACE ${CMAKE_HOME_DIRECTORY}/benchmark-v1.1.0/include)
