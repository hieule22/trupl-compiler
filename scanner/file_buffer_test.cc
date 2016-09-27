// Unit tests for FileBuffer class.
// Copyright 2016 Hieu Le.

#include "scanner/file_buffer.h"

#include "gtest/gtest.h"

namespace truplc {
namespace {

TEST(FileBufferDeathTest, ConstructWithIllegalFilename) {
  EXPECT_DEATH({ FileBuffer buffer("Foo"); }, "");
}

}  // namespace
}  // namespace truplc
