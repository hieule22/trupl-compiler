// Token class for additive operators from TruPL.
// Copyright 2016 Hieu Le.

#ifndef TRUPLC_SCANNER_ADD_OPERATOR_TOKEN_H__
#define TRUPLC_SCANNER_ADD_OPERATOR_TOKEN_H__

#include <string>

#include "scanner/token.h"

namespace truplc {

// Attributes for additive operators from TruPL.
enum class AddOperatorAttribute : int {
    kAdd         = 400,  // +
    kSubtract    = 401,  // -
    kOr          = 402,  // or
    kUnspecified = 499,
};

class AddOperatorToken : public Token {
 public:
  // Constructs an additive operator token from specified attribute.
  // If no attribute is provided, defaults to unspecified.
  explicit AddOperatorToken(
      AddOperatorAttribute attribute = AddOperatorAttribute::kUnspecified);

  ~AddOperatorToken() override;

  // Returns the attribute of this additive operator token.
  AddOperatorAttribute GetAttribute() const;

  // Returns a debug string consisting of the token type and its' attribute.
  // Output will be in the form "kAddOperator":<AddOperatorAttribute>.
  std::string DebugString() const override;

 private:
  // The attribute of this additive operator token.
  const AddOperatorAttribute attribute_;
};

}  // namespace truplc

#endif  // TRUPLC_SCANNER_ADD_OPERATOR_TOKEN_H__
