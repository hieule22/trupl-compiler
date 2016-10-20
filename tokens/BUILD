package(default_visibility = ["//visibility:public"])

cc_library(
  name = "token",
  srcs = ["token.cc"],
  hdrs = ["token.h"],
)

cc_library(
  name = "keyword_token",
  srcs = ["keyword_token.cc"],
  hdrs = ["keyword_token.h"],
  deps = [":token"],
)

cc_library(
  name = "punctuation_token",
  srcs = ["punctuation_token.cc"],
  hdrs = ["punctuation_token.h"],
  deps = [":token"],
)

cc_library(
  name = "rel_operator_token",
  srcs = ["rel_operator_token.cc"],
  hdrs = ["rel_operator_token.h"],
  deps = [":token"],
)

cc_library(
  name = "add_operator_token",
  srcs = ["add_operator_token.cc"],
  hdrs = ["add_operator_token.h"],
  deps = [":token"],
)

cc_library(
  name = "mul_operator_token",
  srcs = ["mul_operator_token.cc"],
  hdrs = ["mul_operator_token.h"],
  deps = [":token"],
)

cc_library(
  name = "number_token",
  srcs = ["number_token.cc"],
  hdrs = ["number_token.h"],
  deps = [":token"],
)

cc_library(
  name = "identifier_token",
  srcs = ["identifier_token.cc"],
  hdrs = ["identifier_token.h"],
  deps = [":token"],
)

cc_library(
  name = "eof_token",
  srcs = ["eof_token.cc"],
  hdrs = ["eof_token.h"],
  deps = [":token"],
)