// Implementation of Token class.
// Copyright 2016 Hieu Le.

#include "tokens/token.h"

namespace truplc {

Token::Token(const TokenType token_type) : type_(token_type) {}

Token::~Token() {}

TokenType Token::GetTokenType() const {
  return type_;
}

std::string Token::DebugString() const {
  return "";
}

}  // namespace truplc
