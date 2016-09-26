// Unit tests for EOFToken class.
// Copyright 2016 Hieu Le.

#include "tokens/eof_token.h"

#include <memory>

#include "gtest/gtest.h"

namespace truplc {
namespace {

TEST(EOFTokenTest, DebugString) {
  std::unique_ptr<Token> token = std::make_unique<EOFToken>();
  EXPECT_EQ(token->DebugString(), "kEOF:EndOfFile");
}

}  // namespace
}  // namespace truplc
