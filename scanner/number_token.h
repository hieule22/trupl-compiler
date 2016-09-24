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
  // literal representing that number. If no attribute is provided, defaults
  // to an empty string.
  explicit NumberToken(const std::string& attribute = "");

  ~NumberToken() override;

  // Returns the string literal representing this number token.
  const std::string& GetAttribute() const;

  // Returns a debug string consisting of the token type and its' attribute.
  // Output will be of the form "kNumber":<StringLiteral>.
  std::string DebugString() const override;

 private:
  // The string literal representing this number's value.
  const std::string attribute_;
};

}  // namespace truplc

#endif  // TRUPLC_SCANNER_NUMBER_TOKEN_H__
