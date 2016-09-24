// Base class for all token classes.
// Copyright 2016 Hieu Le.

#ifndef TRUPLC_SCANNER_TOKEN_H__
#define TRUPLC_SCANNER_TOKEN_H__

#include <string>

namespace truplc {

// Types of tokens from TruPL.
enum class TokenType : int {
    kKeyword     = 0,
    kPunctuation = 1,
    kRelOperator = 2,
    kAddOperator = 3,
    kMulOperator = 4,
    kIdentifier  = 5,
    kNumber      = 6,
    kEOF         = 7,
    kUnspecified = 99,
};

class Token {
 public:
  // Constructs a token from given token type.
  explicit Token(TokenType token_type);

  // Virtual destructor for base class.
  virtual ~Token();

  // Returns the type of this token.
  TokenType GetTokenType() const;

  // Returns a string consisting of the token type and its' attribute.
  // Intended for debugging. The form of the output is TOKEN_TYPE:Attribute.
  virtual std::string DebugString() const;

 private:
  // The type of this token.
  const TokenType type_;
};

}  // namespace truplc

#endif  // TRUPLC_SCANNER_TOKEN_H__
