// Implementation of KeywordToken class.
// Copyright 2016 Hieu Le.

#include "scanner/keyword_token.h"

#include <cassert>

namespace truplc {

KeywordToken::KeywordToken(KeywordAttribute attribute)
    : Token(TokenType::kKeyword), attribute_(attribute) {}

KeywordAttribute KeywordToken::GetAttribute() const {
  return attribute_;
}

std::string KeywordToken::DebugString() const {
  const std::string prefix = "kKeyword:";
  switch (attribute_) {
    case KeywordAttribute::kProgram: {
      return prefix + "kProgram";
    }
    case KeywordAttribute::kProcedure: {
      return prefix + "kProcedure";
    }
    case KeywordAttribute::kInt: {
      return prefix + "kInt";
    }
    case KeywordAttribute::kBool: {
      return prefix + "kBool";
    }
    case KeywordAttribute::kBegin: {
      return prefix + "kBegin";
    }
    case KeywordAttribute::kEnd: {
      return prefix + "kEnd";
    }
    case KeywordAttribute::kIf: {
      return prefix + "kIf";
    }
    case KeywordAttribute::kThen: {
      return prefix + "kThen";
    }
    case KeywordAttribute::kElse: {
      return prefix + "kElse";
    }
    case KeywordAttribute::kWhile: {
      return prefix + "kWhile";
    }
    case KeywordAttribute::kLoop: {
      return prefix + "kLoop";
    }
    case KeywordAttribute::kPrint: {
      return prefix + "kPrint";
    }
    case KeywordAttribute::kNot: {
      return prefix + "kNot";
    }
    case KeywordAttribute::kUnspecified: {
      return prefix + "kUnspecifed";
    }
    default: {
      assert(false);
    }
  }
}

}  // namespace truplc
