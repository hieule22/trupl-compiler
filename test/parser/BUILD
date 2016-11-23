cc_test(
  name = "symbol_table_test",
  srcs = ["symbol_table_test.cc"],
  size = "small",
  deps = [
       "//parser:symbol_table",
       "//third_party/gtest:gtest_main",
  ],
  copts = ["-std=c++14", "-Wall", "-Wextra", "--pedantic"],
)

cc_test(
  name = "parser_test",
  srcs = ["parser_test.cc"],
  deps = [
       "//parser:parser",
       "//scanner:buffer",
       "//scanner:stream_buffer",
       "//third_party/gtest:gtest_main",
  ],
  copts = ["-std=c++14", "-Wall", "-Wextra", "--pedantic"],
)