// Implementation of NumberToken class.
// Copyright 2016 Hieu Le.

#include "tokens/number_token.h"

namespace truplc {

NumberToken::NumberToken(const std::string& attribute)
    : Token(TokenType::kNumber), attribute_(attribute) {}

NumberToken::~NumberToken() {}

const std::string& NumberToken::GetAttribute() const {
  return attribute_;
}

std::string NumberToken::DebugString() const {
  return "kNumber:" + attribute_;
}

}  // namespace truplc
