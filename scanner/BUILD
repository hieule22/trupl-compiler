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
  ]
)