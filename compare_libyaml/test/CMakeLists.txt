include(CTest)

enable_testing()

# TODO: All this copying is horrible.  Put these files lists in a common
# location that can be shared with <root>/test.

include(${CMAKE_HOME_DIRECTORY}/test/test_files/index.cmake)
set(invalid_yaml_test_suite_files
    2SXE # Has the pattern a: b: without a line break.

    # Each has a bare "\" (not starting an escape sequence) outside of any
    # single- or double-quoted string, not indented, in the middle of a block
    # mapping.
    NHX8 P94K 5GBF

    # A bare "\" in the middle of a block scalar, without proper indentation.
    G992 M9B4

    # flow_in_block uses flow(n+1,c), but "quotes" in "double\nquotes is not
    # indented.
    XW4D

    ${error_yml_file_index}
)

##################################################
# Parse-only tests
##################################################
foreach (yml_file_root ${yml_file_index} ${error_yml_file_index})
    add_test(
        libyaml_parse_test_${yml_file_root}
        ${CMAKE_BINARY_DIR}/compare_libyaml/run-parser
        ${CMAKE_HOME_DIRECTORY}/test/test_files/${yml_file_root}.yml
    )
endforeach()

foreach (yml_file_root ${invalid_yaml_test_suite_files})
    set_tests_properties(libyaml_parse_test_${yml_file_root} PROPERTIES WILL_FAIL true)
endforeach()

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
    simple_flow_plain.yml
    escaped_percent_27NA.yml

    # Repeated contents of basic_yaml_block.yaml (contains >1 BOM).
    basic_yaml_block_repeated.yaml
)
foreach (test_file ${test_files})
    add_test(
        libyaml_parse_test_${test_file}
        ${CMAKE_BINARY_DIR}/compare_libyaml/run-parser
        ${CMAKE_HOME_DIRECTORY}/test/test_files/${test_file}
    )
endforeach()
