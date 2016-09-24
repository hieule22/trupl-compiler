// Token class for numbers from TruPL.
// Copyright 2016 Hieu Le.

#ifndef TRUPLC_SCANNER_NUMBER_TOKEN_H__
#define TRUPLC_SCANNER_NUMBER_TOKEN_H__

#include <string>

#include "scanner/token.h"

namespace truplc {

class NumberToken : public Token {
 public:
  // Constructs a number token from specified attribute which is the string
  // literal representing the number. If no attribute is provided, defaults
  // to empty string.
  explicit NumberToken(const std::string& attribute = "");

  // Return the string literal representing this number token.
  const std::string& GetAttribute() const;

  // Returns a debug string consisting of the token type and its' attribute.
  // Output will be in the form kNumberToken:StringLiteral.
  std::string DebugString() const override;

 private:
  const std::string attribute_;
};

}  // namespace truplc

#endif  // TRUPLC_SCANNER_NUMBER_TOKEN_H__
