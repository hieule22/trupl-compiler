package(default_visibility = ["//visibility:public"])

cc_library(
  name = "container_util",
  hdrs = ["container_util.h"],
)

cc_test(
  name = "container_util_test",
  srcs = ["container_util_test.cc"],
  size = "small",
  deps = [
       ":container_util",
       "//third_party/gtest:gtest_main",
  ],
)