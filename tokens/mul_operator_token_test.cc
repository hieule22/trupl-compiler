// Unit tests for MulOperatorToken class.
// Copyright 2016 Hieu Le.

#include "tokens/mul_operator_token.h"

#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace truplc {
namespace {

TEST(MulOperatorToken, GetTokenType) {
  const MulOperatorToken token(MulOperatorAttribute::kAnd);
  EXPECT_EQ(token.GetTokenType(), TokenType::kMulOperator);
}

TEST(MulOperatorToken, GetAttribute) {
  const MulOperatorToken default_token;
  EXPECT_EQ(default_token.GetAttribute(), MulOperatorAttribute::kUnspecified);

  const MulOperatorAttribute attribute = MulOperatorAttribute::kMultiply;
  const MulOperatorToken specified_token(attribute);
  EXPECT_EQ(specified_token.GetAttribute(), attribute);
}

TEST(MulOperatorToken, DebugString) {
  const std::string prefix = "kMulOperator:";
  const std::vector<std::pair<MulOperatorAttribute, std::string>> attributes = {
    {MulOperatorAttribute::kMultiply,    prefix + "kMultiply"},
    {MulOperatorAttribute::kDivide,      prefix + "kDivide"},
    {MulOperatorAttribute::kAnd,         prefix + "kAnd"},
    {MulOperatorAttribute::kUnspecified, prefix + "kUnspecified"}
  };

  for (const auto& attribute : attributes) {
    MulOperatorToken token(attribute.first);
    EXPECT_EQ(token.DebugString(), attribute.second);
  }
}

}  // namespace
}  // namespace truplc
