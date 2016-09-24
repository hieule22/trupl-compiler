// Token class for keywords from TruPL which consist of the following:
// program, procedure, int, bool, begin, end,
// if, then, else, while, loop. print, not.
// Copyright 2016 Hieu Le.

#ifndef TRUPLC_SCANNER_KEYWORD_TOKEN_H__
#define TRUPLC_SCANNER_KEYWORD_TOKEN_H__

#include "scanner/token.h"

namespace truplc {

// Attributes for keyword tokens from TruPL.
enum class KeywordAttribute : int {
    kProgram     = 100,
    kProcedure   = 101,
    kInt         = 102,
    kBool        = 103,
    kBegin       = 104,
    kEnd         = 105,
    kIf          = 106,
    kThen        = 107,
    kElse        = 108,
    kWhile       = 109,
    kLoop        = 110,
    kPrint       = 111,
    kNot         = 112,
    kUnspecified = 199,
};

class KeywordToken : public Token {
 public:
  // Constructs a keyword token from specified keyword attribute.
  // If no attribute is provided, defaults to unspecified.
  explicit KeywordToken(
      KeywordAttribute Attributes = KeywordAttribute::kUnspecified);

  // Returns the attribute of this keyword token.
  KeywordAttribute GetAttribute() const;

  // Returns a debug string consisting of the token type and its' attribute.
  // The form of the output is kKeyword:KeywordAttribute.
  std::string DebugString() const override;

 private:
  // The attribute of this keyword token.
  KeywordAttribute attribute_;
};

}  // namespace truplc

#endif  // TRUPLC_SCANNER_KEYWORD_TOKEN_H__
