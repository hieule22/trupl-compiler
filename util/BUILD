package(default_visibility = ["//visibility:public"])

cc_library(
  name = "container_util",
  srcs = ["container_util.cc"],
  hdrs = ["container_util.h"],
)

cc_test(
  name = "container_util_test",
  srcs = ["container_util_test.cc"],
  deps = [
       ":container_util",
       "//third_party/gtest:gtest_main",
  ],
)