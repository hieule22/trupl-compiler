package(default_visibility = ["//visibility:public"])

cc_library(
  name = "buffer",
  hdrs = ["buffer.h"],
  srcs = ["buffer.cc"],
)

cc_library(
  name = "stream_buffer",
  srcs = ["stream_buffer.cc"],
  hdrs = ["stream_buffer.h"],
  deps = [
       ":buffer",
  ],
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
  copts = ["-std=c++14"],
)

cc_test(
  name = "file_buffer_test",
  srcs = ["file_buffer_test.cc"],
  deps = [
       ":file_buffer",
       "//third_party/gtest:gtest_main",
  ],
  copts = ["-std=c++14"],
)