// Implementation of Token class.
// Copyright 2016 Hieu Le.

#include "scanner/token.h"

namespace truplc {

Token::Token(TokenType token_type) : type_(token_type) {}

TokenType Token::GetTokenType() const {
  return type_;
}

std::string Token::DebugString() const {
  return "";
}

}  // namespace truplc
