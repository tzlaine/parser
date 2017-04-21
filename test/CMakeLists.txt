include_directories(${CMAKE_HOME_DIRECTORY})

include(CTest)

enable_testing()

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} -VV -C ${CMAKE_CFG_INTDIR})

add_executable(parse_test scalar.cpp flow.cpp block.cpp yaml.cpp parse_yaml_test.cpp)
target_link_libraries(parse_test yaml)# gtest gtest_main)
if (clang_on_linux)
    target_link_libraries(parse_test c++)
endif ()

set(test_files
    anchors.yaml
    basic_yaml_block.yaml
    basic_yaml_block2.yaml
    basic_yaml_block3.yaml
    basic_yaml_flow.yaml
    block_literals.yaml
    block_literals2.yaml
    data-types.yaml
    invoice.yaml
    relational.yaml
    scalar.yaml
    test.yaml
    yaml_block_array1.yaml
    yaml_block_array2.yaml
    yaml_block_array3.yaml
    yaml_block_array4.yaml
    yaml_block_array5.yaml
    yaml_block_array6.yaml
    yaml_block_array7.yaml
    yaml_block_map1.yaml
    yaml_block_map10.yaml
    yaml_block_map11.yaml
    yaml_block_map12.yaml
    yaml_block_map13.yaml
    yaml_block_map2.yaml
    yaml_block_map3.yaml
    yaml_block_map4.yaml
    yaml_block_map5.yaml
    yaml_block_map6.yaml
    yaml_block_map7.yaml
    yaml_block_map8.yaml
    yaml_block_map9.yaml
)
foreach (test_file ${test_files})
    message(${test_file})
    add_test(
        parse_test_${test_file}
        ${CMAKE_CURRENT_BINARY_DIR}/parse_test
        ${CMAKE_CURRENT_SOURCE_DIR}/test_files/${test_file} --gtest_catch_exceptions=1
    )
endforeach()
