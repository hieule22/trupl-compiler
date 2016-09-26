// Implementation of MulOperatorToken class.
// Copyright 2016 Hieu Le.

#include "tokens/mul_operator_token.h"

#include <cassert>

namespace truplc {

MulOperatorToken::MulOperatorToken(const MulOperatorAttribute attribute)
    : Token(TokenType::kMulOperator), attribute_(attribute) {}

MulOperatorToken::~MulOperatorToken() {}

MulOperatorAttribute MulOperatorToken::GetAttribute() const {
  return attribute_;
}

std::string MulOperatorToken::DebugString() const {
  const std::string prefix = "kMulOperator:";

  switch (attribute_) {
    case MulOperatorAttribute::kMultiply: {
      return prefix + "kMultiply";
    }
    case MulOperatorAttribute::kDivide: {
      return prefix + "kDivide";
    }
    case MulOperatorAttribute::kAnd: {
      return prefix + "kAnd";
    }
    case MulOperatorAttribute::kUnspecified: {
      return prefix + "kUnspecified";
    }
    default: {
      assert(false);
    }
  }
}

}  // namespace truplc
