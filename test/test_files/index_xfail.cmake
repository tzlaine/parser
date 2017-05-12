set(expected_parse_failures
    2SXE # Has the pattern a: b: without a line break.

    # flow_in_block uses flow(n+1,c), but "quotes" in "double\nquotes is not
    # indented.
    XW4D
)
