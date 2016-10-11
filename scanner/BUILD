package(default_visibility = ["//visibility:public"])

cc_library(
  name = "buffer",
  hdrs = ["buffer.h"],
  srcs = ["buffer.cc"],
  deps = [
       "//util:container_util",
       "//util:string_util",
       "//util:text_colorizer"
  ],
)

cc_test(
  name = "buffer_test",
  srcs = ["buffer_test.cc"],
  size = "small",
  deps = [
       ":buffer",
       "//third_party/gtest:gtest_main",
  ],
  copts = ["-std=c++14",  "-Wall", "--pedantic"],
)

cc_library(
  name = "stream_buffer",
  srcs = ["stream_buffer.cc"],
  hdrs = ["stream_buffer.h"],
  deps = [
       ":buffer",
  ],
  copts = ["-std=c++14",  "-Wall", "--pedantic"],
)

cc_test(
  name = "stream_buffer_test",
  srcs = ["stream_buffer_test.cc"],
  size = "small",
  deps = [
       ":stream_buffer",
       "//third_party/gtest:gtest_main",
  ],
  copts = ["-std=c++14"],
)

cc_library(
  name = "file_buffer",
  srcs = ["file_buffer.cc"],
  hdrs = ["file_buffer.h"],
  deps = [
       ":buffer",
       ":stream_buffer",
  ],
  copts = ["-std=c++14",  "-Wall", "--pedantic"],
)

cc_test(
  name = "file_buffer_test",
  srcs = ["file_buffer_test.cc"],
  size = "small",
  deps = [
       ":file_buffer",
       "//third_party/gtest:gtest_main",
  ],
  copts = ["-std=c++14"],
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

cc_library(
  name = "scanner",
  srcs = ["scanner.cc"],
  hdrs = ["scanner.h"],
  deps = [
       ":buffer",
       ":file_buffer",
       "//tokens:token",
       "//tokens:keyword_token",
       "//tokens:punctuation_token",
       "//tokens:rel_operator_token",
       "//tokens:add_operator_token",
       "//tokens:mul_operator_token",
       "//tokens:number_token",
       "//tokens:identifier_token",
       "//tokens:eof_token",
       "//util:container_util",
       "//util:string_util",
       "//util:text_colorizer",
  ],
  copts = ["-std=c++14",  "-Wall", "--pedantic"],
)

cc_test(
  name = "scanner_test",
  srcs = ["scanner_test.cc"],
  size = "small",
  deps = [
       ":scanner",
       ":test_utils",
        "//third_party/gtest:gtest_main",
  ],
  copts = ["-std=c++14"],
)

cc_binary(
  name = "scanner_main",
  srcs = ["scanner_main.cc"],
  deps = [
       ":scanner",
       "//util:string_util",
       "//util:text_colorizer",
  ],
)