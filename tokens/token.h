// Base class for all tokens from TruPL.
// Copyright 2016 Hieu Le.

#ifndef TRUPLC_TOKENS_TOKEN_H__
#define TRUPLC_TOKENS_TOKEN_H__

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
  // If no type is provided, defaults to kUnspecified.
  explicit Token(TokenType token_type = TokenType::kUnspecified);

  // Virtual destructor for base class.
  virtual ~Token();

  // Returns the type of this token.
  TokenType GetTokenType() const;

  // Returns a debug string consisting of the token type and its' attribute.
  // Output should be of the form TOKEN_TYPE:Attribute.
  virtual std::string DebugString() const;

 private:
  // The type of this token.
  const TokenType type_;
};

}  // namespace truplc

#endif  // TRUPLC_TOKENS_TOKEN_H__
