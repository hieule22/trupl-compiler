// Implementation of AddOperatorToken class.
// Copyright 2016 Hieu Le.

#include "scanner/add_operator_token.h"

#include <cassert>

namespace truplc {

AddOperatorToken::AddOperatorToken(const AddOperatorAttribute attribute)
    : Token(TokenType::kAddOperator), attribute_(attribute) {}

AddOperatorToken::~AddOperatorToken() {}

AddOperatorAttribute AddOperatorToken::GetAttribute() const {
  return attribute_;
}

std::string AddOperatorToken::DebugString() const {
  const std::string prefix = "kAddOperator:";

  switch (attribute_) {
    case AddOperatorAttribute::kAdd: {
      return prefix + "kAdd";
    }
    case AddOperatorAttribute::kSubtract: {
      return prefix + "kSubtract";
    }
    case AddOperatorAttribute::kOr: {
      return prefix + "kOr";
    }
    case AddOperatorAttribute::kUnspecified: {
      return prefix + "kUnspecified";
    }
    default: {
      assert(false);
    }
  }
}

}  // namespace truplc
