# Copyright Louis Dionne 2016
# Copyright Zach Laine 2024
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

###############################################################################
# Boost
###############################################################################
set(Boost_USE_STATIC_LIBS ON)

if (NOT BOOST_BRANCH)
  set(BOOST_BRANCH master)
endif()

add_custom_target(boost_clone_superproject
  DEPENDS
    ${CMAKE_BINARY_DIR}/boost_root/LICENSE_1_0.txt
  COMMENT
    "Cloning Boost superproject."
  VERBATIM)

add_custom_command(
  OUTPUT ${CMAKE_BINARY_DIR}/boost_root/LICENSE_1_0.txt
  COMMAND git clone --depth 100 -b ${BOOST_BRANCH}
    https://github.com/boostorg/boost.git boost_root
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

if (MSVC)
  set(b2_exe b2.exe)
else()
  set(b2_exe b2)
endif()

add_custom_target(boost_clone_deps
  DEPENDS
    ${CMAKE_BINARY_DIR}/boost_root/${b2_exe}
  COMMENT
    "Cloning Boost dependencies."
  VERBATIM)
add_dependencies(boost_clone_deps boost_clone_superproject)

if (MSVC)
  set(bootstrap_cmd ./bootstrap.bat)
else()
  set(bootstrap_cmd ./bootstrap.sh)
endif()

add_custom_command(
  OUTPUT ${CMAKE_BINARY_DIR}/boost_root/${b2_exe}
  COMMAND git submodule init libs/assert
  COMMAND git submodule init libs/config
  COMMAND git submodule init libs/core
  COMMAND git submodule init libs/hana
  COMMAND git submodule init tools/build
  COMMAND git submodule init libs/headers
  COMMAND git submodule init tools/boost_install
  COMMAND git submodule update --jobs 3 --depth 100
  COMMAND ${bootstrap_cmd}
  COMMAND ./b2 headers
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/boost_root)

add_library(boost INTERFACE)
add_dependencies(boost boost_clone_deps)
target_include_directories(boost INTERFACE ${CMAKE_BINARY_DIR}/boost_root)
