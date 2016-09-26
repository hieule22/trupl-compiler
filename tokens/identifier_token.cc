// Implementation of IdentifierToken class.
// Copyright 2016 Hieu Le.

#include "tokens/identifier_token.h"

namespace truplc {

IdentifierToken::IdentifierToken(const std::string& attribute)
    : Token(TokenType::kIdentifier), attribute_(attribute) {}

IdentifierToken::~IdentifierToken() {}

const std::string& IdentifierToken::GetAttribute() const {
  return attribute_;
}

std::string IdentifierToken::DebugString() const {
  return "kIdentifier:" + attribute_;
}

}  // namespace truplc
