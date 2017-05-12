set(dir ${CMAKE_SOURCE_DIR}/libyaml)

file(GLOB sources ${dir}/src/*.c)

include_directories(${dir}/include ${dir}/win32)

add_library(libyaml STATIC ${sources})
set_target_properties(libyaml PROPERTIES COMPILE_FLAGS "-DYAML_DECLARE_STATIC -DHAVE_CONFIG_H")

add_executable(run-parser ${dir}/tests/run-parser.c)
target_link_libraries(run-parser libyaml)

add_subdirectory(test)
