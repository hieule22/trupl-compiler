// Test class for token.h
// Copyright 2016 Hieu Le.

#include "scanner/token.h"

#include "gtest/gtest.h"

namespace truplc {
namespace {

TEST(Token, GetTokenType) {
  const TokenType type = TokenType::kPunctuation;
  Token token(type);
  EXPECT_EQ(token.GetTokenType(), type);
}

TEST(Token, DebugString) {
  Token token(TokenType::kKeyword);
  EXPECT_TRUE(token.DebugString().empty());
}

}  // namespace
}  // namespace truplc
