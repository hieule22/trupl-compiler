// Unit tests for NumberToken class.
// Copyright 2016 Hieu Le.

#include "scanner/number_token.h"

#include <vector>

#include "gtest/gtest.h"

namespace truplc {
namespace {

TEST(NumberToken, GetTokenType) {
  const NumberToken token(std::to_string(12345));
  EXPECT_EQ(token.GetTokenType(), TokenType::kNumber);
}

TEST(NumberToken, GetAttribute) {
  const NumberToken default_token;
  EXPECT_TRUE(default_token.GetAttribute().empty());

  const std::string attribute = std::to_string(-2980);
  const NumberToken specified_token(attribute);
  EXPECT_EQ(specified_token.GetAttribute(), attribute);
}

TEST(NumberToken, DebugString) {
  const std::string prefix = "kNumber:";
  const std::vector<int> numbers = {0, 1, 17, -11, 9999, 1065};
  for (const int& number : numbers) {
    const std::string attribute = std::to_string(number);
    NumberToken token(attribute);
    EXPECT_EQ(token.DebugString(), prefix + attribute);
  }
}

}  // namespace
}  // namespace truplc
