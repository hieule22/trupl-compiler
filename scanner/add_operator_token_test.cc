// Unit tests for AddOperatorToken class.
// Copyright 2016 Hieu Le.

#include "scanner/add_operator_token.h"

#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace truplc {
namespace {

TEST(AddOperatorToken, GetTokenType) {
  const AddOperatorToken token(AddOperatorAttribute::kSubtract);
  EXPECT_EQ(token.GetTokenType(), TokenType::kAddOperator);
}

TEST(AddOperatorToken, GetAttribute) {
  const AddOperatorToken default_token;
  EXPECT_EQ(default_token.GetAttribute(), AddOperatorAttribute::kUnspecified);

  const AddOperatorAttribute attribute = AddOperatorAttribute::kAdd;
  const AddOperatorToken specified_token(attribute);
  EXPECT_EQ(specified_token.GetAttribute(), attribute);
}

TEST(AddOperatorToken, DebugString) {
  const std::string prefix = "kAddOperator:";
  const std::vector<std::pair<AddOperatorAttribute, std::string>> attributes = {
    {AddOperatorAttribute::kAdd, prefix + "kAdd"},
    {AddOperatorAttribute::kSubtract, prefix + "kSubtract"},
    {AddOperatorAttribute::kOr, prefix + "kOr"},
    {AddOperatorAttribute::kUnspecified, prefix + "kUnspecified"}
  };

  for (const auto& attribute : attributes) {
    AddOperatorToken token(attribute.first);
    EXPECT_EQ(token.DebugString(), attribute.second);
  }
}

}  // namespace
}  // namespace truplc
