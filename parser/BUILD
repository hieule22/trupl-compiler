package(default_visibility = ["//visibility:public"])

cc_library(
  name = "symbol_table",
  srcs = ["symbol_table.cc"],
  hdrs = ["symbol_table.h"],
  deps = ["//util:string_util"],
  copts = ["-std=c++14", "-Wall", "-Wextra", "--pedantic"],
)

cc_library(
  name = "parser",
  srcs = ["parser.cc"],
  hdrs = ["parser.h"],
  deps = [
       "//parser/internal:topdown_parser",
       "//scanner:scanner"
  ],
  copts = ["-std=c++14", "-Wall", "-Wextra", "--pedantic"],
)