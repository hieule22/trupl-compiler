// Token class for keywords from TruPL.
// Copyright 2016 Hieu Le.

#ifndef TRUPLC_TOKENS_KEYWORD_TOKEN_H__
#define TRUPLC_TOKENS_KEYWORD_TOKEN_H__

#include <string>

#include "tokens/token.h"

namespace truplc {

// Attributes for keyword tokens from TruPL.
enum class KeywordAttribute : int {
    kProgram     = 100,  // program
    kProcedure   = 101,  // procedure
    kInt         = 102,  // int
    kBool        = 103,  // bool
    kBegin       = 104,  // begin
    kEnd         = 105,  // end
    kIf          = 106,  // if
    kThen        = 107,  // then
    kElse        = 108,  // else
    kWhile       = 109,  // while
    kLoop        = 110,  // loop
    kPrint       = 111,  // print
    kNot         = 112,  // not
    kUnspecified = 199,
};

class KeywordToken : public Token {
 public:
  // Constructs a keyword token from specified keyword attribute.
  // If no attribute is provided, defaults to kUnspecified.
  explicit KeywordToken(
      KeywordAttribute attribute = KeywordAttribute::kUnspecified);

  ~KeywordToken() override;

  // Returns the attribute of this keyword token.
  KeywordAttribute GetAttribute() const;

  // Returns a debug string consisting of the token type and its' attribute.
  // Output will be of the form "kKeyword":<KeywordAttribute>.
  std::string DebugString() const override;

 private:
  // The attribute of this keyword token.
  const KeywordAttribute attribute_;
};

}  // namespace truplc

#endif  // TRUPLC_TOKENS_KEYWORD_TOKEN_H__
