// Unit tests for FileBuffer class.
// Copyright 2016 Hieu Le.

#include "scanner/file_buffer.h"

#include "gtest/gtest.h"

namespace truplc {
namespace {

TEST(FileBufferDeathTest, ConstructWithIllegalFilename) {
  ASSERT_EXIT({ FileBuffer buffer("Foo"); },
              ::testing::ExitedWithCode(EXIT_FAILURE),
              "c*Error opening source file: Fooc*");
}

}  // namespace
}  // namespace truplc
