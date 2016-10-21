// Unit tests for Buffer interface.
// Copyright 2016 Hieu Le.

#include "scanner/buffer.h"

#include "gtest/gtest.h"

namespace truplc {
namespace {

class BufferTest : public Buffer, public testing::Test {
 public:
  BufferTest() {}

  ~BufferTest() {}

  char NextChar() override { return '\0'; }

  void UnreadChar(const char c) override {}
};

TEST_F(BufferTest, BufferFatalError) {
  ASSERT_EXIT(this->BufferFatalError("Error"),
              ::testing::ExitedWithCode(EXIT_FAILURE),
              "Error\nEXITING on BUFFER FATAL ERROR\n");
}

TEST_F(BufferTest, Validate) {
  for (const char c : kNonAlphanum) {
    EXPECT_TRUE(this->Validate(c));
  }

  for (int c = 'a'; c <= 'z'; ++c) {
    EXPECT_TRUE(this->Validate(static_cast<char>(c)));
  }

  EXPECT_FALSE(this->Validate(kEOFMarker));
  for (int c = 'A'; c <= 'Z'; ++c) {
    EXPECT_FALSE(this->Validate(static_cast<char>(c)));
  }
}

}  // namespace
}  // namespace truplc
