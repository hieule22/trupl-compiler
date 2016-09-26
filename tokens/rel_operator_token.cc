// Implementation of RelOperatorToken class.
// Copyright 2016 Hieu Le.

#include "tokens/rel_operator_token.h"

#include <cassert>

namespace truplc {

RelOperatorToken::RelOperatorToken(const RelOperatorAttribute attribute)
    : Token(TokenType::kRelOperator), attribute_(attribute) {}

RelOperatorToken::~RelOperatorToken() {}

RelOperatorAttribute RelOperatorToken::GetAttribute() const {
  return attribute_;
}

std::string RelOperatorToken::DebugString() const {
  const std::string prefix = "kRelOperator:";

  switch (attribute_) {
    case RelOperatorAttribute::kEqual: {
      return prefix + "kEqual";
    }
    case RelOperatorAttribute::kNotEqual: {
      return prefix + "kNotEqual";
    }
    case RelOperatorAttribute::kGreaterThan: {
      return prefix + "kGreaterThan";
    }
    case RelOperatorAttribute::kGreaterOrEqual: {
      return prefix + "kGreaterOrEqual";
    }
    case RelOperatorAttribute::kLessThan: {
      return prefix + "kLessThan";
    }
    case RelOperatorAttribute::kLessOrEqual: {
      return prefix + "kLessOrEqual";
    }
    case RelOperatorAttribute::kUnspecified: {
      return prefix + "kUnspecified";
    }
    default: {
      assert(false);
    }
  }
}

}  // namespace truplc
