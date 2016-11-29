package(default_visibility = ["//parser:__pkg__"])

cc_library(
  name = "topdown_parser",
  srcs = ["topdown_parser.cc"],
  hdrs = ["topdown_parser.h"],
  deps = [
       "//parser:symbol_table",
       "//scanner:scanner",
       "//tokens:add_operator_token",
       "//tokens:identifier_token",
       "//tokens:keyword_token",
       "//tokens:mul_operator_token",
       "//tokens:number_token",
       "//tokens:punctuation_token",
       "//tokens:rel_operator_token",
       "//tokens:token",
       "//util:string_util",
  ],
  copts = ["-std=c++14", "-Wall", "-Wextra", "--pedantic"],
)