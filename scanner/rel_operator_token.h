// Token class for relational operators from TruPL.
// Copyright 2016 Hieu Le.

#ifndef TRUPLC_SCANNER_REL_OPERATOR_TOKEN_H__
#define TRUPLC_SCANNER_REL_OPERATOR_TOKEN_H__

#include <string>

#include "scanner/token.h"

namespace truplc {

// Attributes for relational operator tokens from TruPL.
enum class RelOperatorAttribute : int {
    kEqual          = 300,  // =
    kNotEqual       = 301,  // <>
    kGreaterThan    = 302,  // >
    kGreaterOrEqual = 303,  // >=
    kLessThan       = 304,  // <
    kLessOrEqual    = 305,  // <=
    kUnspecified    = 399,
};

class RelOperatorToken : public Token {
 public:
  // Constructs a relational operator token from specified attribute.
  // If no attribute is provided, defaults to kUnspecified.
  explicit RelOperatorToken(
      RelOperatorAttribute attribute = RelOperatorAttribute::kUnspecified);

  ~RelOperatorToken() override;

  // Returns the attribute of this relational operator token.
  RelOperatorAttribute GetAttribute() const;

  // Returns a debug string consisting of the token type and its' attribute.
  // Output will be of the form ""kRelOperator":<RelOperatorAttribute>.
  std::string DebugString() const override;

 private:
  // The attribute of this relational operator token.
  const RelOperatorAttribute attribute_;
};

}  // namespace truplc

#endif  // TRUPLC_SCANNER_REL_OPERATOR_TOKEN_H__
