package(default_visibility = ["//visibility:public"])

cc_library(
  name = "token",
  srcs = ["token.cc"],
  hdrs = ["token.h"],
)

cc_test(
  name = "token_test",
  srcs = ["token_test.cc"],
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
  deps = [
       ":keyword_token",
       "//third_party/gtest:gtest_main",
  ],
)