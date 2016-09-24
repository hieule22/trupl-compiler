// Unit tests for IdentifierToken class.
// Copyright 2016 Hieu Le.

#include "scanner/identifier_token.h"

#include "gtest/gtest.h"

namespace truplc {
namespace {

TEST(IdentifierToken, GetTokenType) {
  const IdentifierToken token("Foo");
  EXPECT_EQ(token.GetTokenType(), TokenType::kIdentifier);
}

TEST(IdentifierToken, GetAttribute) {
  const IdentifierToken default_token;
  EXPECT_TRUE(default_token.GetAttribute().empty());

  const std::string attribute = "Bar";
  const IdentifierToken specified_token(attribute);
  EXPECT_EQ(specified_token.GetAttribute(), attribute);
}

TEST(IdentifierToken, DebugString) {
  const IdentifierToken token("Quoz");
  EXPECT_EQ(token.DebugString(), "kIdentifier:Quoz");
}

}  // namespace
}  // namespace truplc
