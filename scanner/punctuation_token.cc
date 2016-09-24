// Implementation of PunctuationToken class.
// Copyright 2016 Hieu Le.

#include "scanner/punctuation_token.h"

#include <cassert>

namespace truplc {

PunctuationToken::PunctuationToken(const PunctuationAttribute attribute)
    : Token(TokenType::kPunctuation), attribute_(attribute) {}

PunctuationAttribute PunctuationToken::GetAttribute() const {
  return attribute_;
}

std::string PunctuationToken::DebugString() const {
  const std::string prefix = "kPunctuation:";
  switch (attribute_) {
    case PunctuationAttribute::kSemicolon: {
      return prefix + "kSemicolon";
    }
    case PunctuationAttribute::kColon: {
      return prefix + "kColon";
    }
    case PunctuationAttribute::kComma: {
      return prefix + "kComma";
    }
    case PunctuationAttribute::kAssignment: {
      return prefix + "kAssignment";
    }
    case PunctuationAttribute::kOpenBracket: {
      return prefix + "kOpenBracket";
    }
    case PunctuationAttribute::kCloseBracket: {
      return prefix + "kCloseBracket";
    }
    case PunctuationAttribute::kUnspecified: {
      return prefix + "kUnspecified";
    }
    default: {
      assert(false);
    }
  }
}

}  // namespace truplc
