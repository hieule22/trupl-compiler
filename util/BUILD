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

cc_library(
  name = "text_colorizer",
  srcs = ["text_colorizer.cc"],
  hdrs = ["text_colorizer.h"],
)

cc_test(
  name = "text_colorizer_test",
  srcs = ["text_colorizer_test.cc"],
  deps = [
       ":text_colorizer",
       "//third_party/gtest:gtest_main",
  ],
)

cc_library(
  name = "string_util",
  srcs = ["string_util.cc"],
  hdrs = ["string_util.h"],
)

cc_test(
  name = "string_util_test",
  srcs = ["string_util_test.cc"],
  deps = [
       ":string_util",
       "//third_party/gtest:gtest_main",
  ],
)