// Token class for multiplicative operators from TruPL.
// Copyright 2016 Hieu Le.

#ifndef TRUPLC_TOKENS_MUL_OPERATOR_TOKEN_H__
#define TRUPLC_TOKENS_MUL_OPERATOR_TOKEN_H__

#include <string>

#include "tokens/token.h"

namespace truplc {

// Attributes for multiplicative operators from TruPL.
enum class MulOperatorAttribute : int {
    kMultiply    = 500,  // *
    kDivide      = 501,  // /
    kAnd         = 502,  // and
    kUnspecified = 599,
};

class MulOperatorToken : public Token {
 public:
  // Constructs a multiplicative operator token from specified attribute.
  // If no attribute is provided, defaults to kUnspecified.
  explicit MulOperatorToken(
      MulOperatorAttribute attribute = MulOperatorAttribute::kUnspecified);

  ~MulOperatorToken() override;

  // Returns the attribute of this multiplicative operator token.
  MulOperatorAttribute GetAttribute() const;

  // Returns a debug string consisting of the token type and its' attribute.
  // Output will be in the form "kMulOperator":<MulOperatorAttribute>.
  std::string DebugString() const override;

 private:
  // The attribute of this multiplicative operator token.
  const MulOperatorAttribute attribute_;
};

}  // namespace truplc

#endif  // TRUPLC_TOKENS_MUL_OPERATOR_TOKEN_H__
