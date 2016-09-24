// Token class for identifiers from TruPL.
// Copyright 2016 Hieu Le.

#ifndef TRUPLC_SCANNER_IDENTIFIER_TOKEN_H__
#define TRUPLC_SCANNER_IDENTIFIER_TOKEN_H__

#include <string>

#include "scanner/token.h"

namespace truplc {

class IdentifierToken : public Token {
 public:
  // Constructs an identifier token from specified attribute which is the string
  // literal representing the identifier name. If no attribute is provided,
  // defaults to empty string.
  explicit IdentifierToken(const std::string& attribute = "");

  ~IdentifierToken() override;

  // Returns the string literal representing this identifier token.
  const std::string& GetAttribute() const;

  // Returns a debug string consisting of the token type and its' attribute.
  // Output will be of the form "kIdentifier":<StringLiteral>.
  std::string DebugString() const override;

 private:
  // The string literal representing this identifier's name.
  const std::string attribute_;
};

}  // namespace truplc

#endif  // TRUPLC_SCANNER_IDENTIFIER_TOKEN_H__
