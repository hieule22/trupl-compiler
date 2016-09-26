package(default_visibility = ["//visibility:public"])

cc_library(
  name = "token",
  srcs = ["token.cc"],
  hdrs = ["token.h"],
)

cc_test(
  name = "token_test",
  srcs = ["token_test.cc"],
  size = "small",
  deps = [
       ":token",
       "//third_party/gtest:gtest_main",
  ],
)

cc_library(
  name = "keyword_token",
  srcs = ["keyword_token.cc"],
  hdrs = ["keyword_token.h"],
  deps = [":token"],
)

cc_test(
  name = "keyword_token_test",
  srcs = ["keyword_token_test.cc"],
  size = "small",
  deps = [
       ":keyword_token",
       "//third_party/gtest:gtest_main",
  ],
)

cc_library(
  name = "punctuation_token",
  srcs = ["punctuation_token.cc"],
  hdrs = ["punctuation_token.h"],
  deps = [":token"],
)

cc_test(
  name = "punctuation_token_test",
  srcs = ["punctuation_token_test.cc"],
  size = "small",
  deps = [
       ":punctuation_token",
       "//third_party/gtest:gtest_main",
  ],
)

cc_library(
  name = "rel_operator_token",
  srcs = ["rel_operator_token.cc"],
  hdrs = ["rel_operator_token.h"],
  deps = [":token"],
)

cc_test(
  name = "rel_operator_token_test",
  srcs = ["rel_operator_token_test.cc"],
  size = "small",
  deps = [
       ":rel_operator_token",
       "//third_party/gtest:gtest_main",
  ],
)

cc_library(
  name = "add_operator_token",
  srcs = ["add_operator_token.cc"],
  hdrs = ["add_operator_token.h"],
  deps = [":token"],
)

cc_test(
  name = "add_operator_token_test",
  srcs = ["add_operator_token_test.cc"],
  size = "small",
  deps = [
       ":add_operator_token",
       "//third_party/gtest:gtest_main",
  ],
)

cc_library(
  name = "mul_operator_token",
  srcs = ["mul_operator_token.cc"],
  hdrs = ["mul_operator_token.h"],
  deps = [":token"],
)

cc_test(
  name = "mul_operator_token_test",
  srcs = ["mul_operator_token_test.cc"],
  size = "small",
  deps = [
       ":mul_operator_token",
       "//third_party/gtest:gtest_main",
  ],
)

cc_library(
  name = "number_token",
  srcs = ["number_token.cc"],
  hdrs = ["number_token.h"],
  deps = [":token"],
)

cc_test(
  name = "number_token_test",
  srcs = ["number_token_test.cc"],
  size = "small",
  deps = [
       ":number_token",
       "//third_party/gtest:gtest_main",
  ],
)

cc_library(
  name = "identifier_token",
  srcs = ["identifier_token.cc"],
  hdrs = ["identifier_token.h"],
  deps = [":token"],
)

cc_test(
  name = "identifier_token_test",
  srcs = ["identifier_token_test.cc"],
  size = "small",
  deps = [
       ":identifier_token",
       "//third_party/gtest:gtest_main",
  ],
)

cc_library(
  name = "eof_token",
  srcs = ["eof_token.cc"],
  hdrs = ["eof_token.h"],
  deps = [":token"],
)

cc_test(
  name = "eof_token_test",
  srcs = ["eof_token_test.cc"],
  deps = [
       ":eof_token",
       "//third_party/gtest:gtest_main",
  ],
  copts = ["-std=c++14"],
)