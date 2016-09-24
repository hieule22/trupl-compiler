// Token class for punctuation symbols from TruPL.
// Copyright 2016 Hieu Le.

#ifndef TRUPLC_SCANNER_PUNCTUATION_TOKEN_H__
#define TRUPLC_SCANNER_PUNCTUATION_TOKEN_H__

#include <string>

#include "scanner/token.h"

namespace truplc {

// Attributes for punctuation tokens from TruPL.
enum class PunctuationAttribute : int {
    kSemicolon    = 200,  // ;
    kColon        = 201,  // :
    kComma        = 202,  // ,
    kAssignment   = 203,  // :=
    kOpenBracket  = 204,  // (
    kCloseBracket = 205,  // )
    kUnspecified  = 299,
};

class PunctuationToken : public Token {
 public:
  // Constructs a punctuation token from specified punctuation attribute.
  // If no attribute is provided, defaults to kUnspecified.
  explicit PunctuationToken(
      PunctuationAttribute attribute = PunctuationAttribute::kUnspecified);

  ~PunctuationToken() override;

  // Returns the attribute of this punctuation token.
  PunctuationAttribute GetAttribute() const;

  // Returns a debug string consisting of the token type and its' attribute.
  // Output will be in the form "kPunctuation":<PunctuationAttribute>.
  std::string DebugString() const override;

 private:
  // The attribute of this punctuation token.
  const PunctuationAttribute attribute_;
};

}  // namespace truplc

#endif  // TRUPLC_SCANNER_PUNCTUATION_TOKEN_H__
