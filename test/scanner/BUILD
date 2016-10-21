cc_test(
  name = "buffer_test",
  srcs = ["buffer_test.cc"],
  size = "small",
  deps = [
       "//scanner:buffer",
       "//third_party/gtest:gtest_main",
  ],
  copts = ["-std=c++14", "-Wall", "--pedantic"],
)

cc_test(
  name = "stream_buffer_test",
  srcs = ["stream_buffer_test.cc"],
  size = "small",
  deps = [
       "//scanner:stream_buffer",
       "//third_party/gtest:gtest_main",
  ],
  copts = ["-std=c++14", "-Wall", "--pedantic"],
)

cc_test(
  name = "file_buffer_test",
  srcs = ["file_buffer_test.cc"],
  size = "small",
  deps = [
       "//scanner:file_buffer",
       "//third_party/gtest:gtest_main",
  ],
  copts = ["-std=c++14", "-Wall", "--pedantic"],
)

cc_library(
  name = "test_utils",
  hdrs = ["test_utils.h"],
  deps = [
       "//tokens:token",
       "//tokens:keyword_token",
       "//tokens:punctuation_token",
       "//tokens:rel_operator_token",
       "//tokens:add_operator_token",
       "//tokens:mul_operator_token",
       "//tokens:number_token",
       "//tokens:identifier_token",
       "//tokens:eof_token",
   ],
)

cc_test(
  name = "scanner_test",
  srcs = ["scanner_test.cc"],
  size = "small",
  deps = [
       ":test_utils",
       "//scanner:scanner",
       "//third_party/gtest:gtest_main",
  ],
  copts = ["-std=c++14", "-Wall", "--pedantic"],
)

cc_test(
  name = "lexical_analyzer_test",
  srcs = ["lexical_analyzer_test.cc"],
  size = "small",
  deps = [
       ":test_utils",
       "//scanner:scanner",
       "//scanner:stream_buffer",
       "//third_party/gtest:gtest_main",
  ],
  copts = ["-std=c++14", "-Wall", "--pedantic"],
)