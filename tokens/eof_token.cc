// Implementation of EOFToken class.
// Copyright 2016 Hieu Le.

#include "tokens/eof_token.h"

namespace truplc {

EOFToken::EOFToken() : Token(TokenType::kEOF) {}

EOFToken::~EOFToken() {}

std::string EOFToken::DebugString() const {
  return "kEOF:EndOfFile";
}

}  // namespace truplc
