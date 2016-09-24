// Unit tests for RelOperatorToken class.
// Copyright 2016 Hieu Le.

#include "scanner/rel_operator_token.h"

#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace truplc {
namespace {

TEST(RelOperatorToken, GetTokenType) {
  const RelOperatorToken token(RelOperatorAttribute::kGreaterThan);
  EXPECT_EQ(token.GetTokenType(), TokenType::kRelOperator);
}

TEST(RelOperatorToken, GetAttribute) {
  const RelOperatorToken default_token;
  EXPECT_EQ(default_token.GetAttribute(), RelOperatorAttribute::kUnspecified);

  const RelOperatorAttribute attribute = RelOperatorAttribute::kLessOrEqual;
  const RelOperatorToken specified_token(attribute);
  EXPECT_EQ(specified_token.GetAttribute(), attribute);
}

TEST(RelOperatorToken, DebugString) {
  const std::string prefix = "kRelOperator:";
  const std::vector<std::pair<RelOperatorAttribute, std::string>> attributes =
      {{RelOperatorAttribute::kEqual,          prefix + "kEqual"},
       {RelOperatorAttribute::kNotEqual,       prefix + "kNotEqual"},
       {RelOperatorAttribute::kGreaterThan,    prefix + "kGreaterThan"},
       {RelOperatorAttribute::kGreaterOrEqual, prefix + "kGreaterOrEqual"},
       {RelOperatorAttribute::kLessThan,       prefix + "kLessThan"},
       {RelOperatorAttribute::kLessOrEqual,    prefix + "kLessOrEqual"},
       {RelOperatorAttribute::kUnspecified,    prefix + "kUnspecified"}
      };

  for (const auto& attribute : attributes) {
    RelOperatorToken token(attribute.first);
    EXPECT_EQ(token.DebugString(), attribute.second);
  }
}

}  // namespace
}  // namespace truplc
