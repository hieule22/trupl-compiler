// Token class for the End of File symbol from TruPL.
// Copyright 2016 Hieu Le.

#ifndef TRUPLC_TOKENS_EOF_TOKEN_H__
#define TRUPLC_TOKENS_EOF_TOKEN_H__

#include <string>

#include "tokens/token.h"

namespace truplc {

// EOF token has no attribute.

class EOFToken : public Token {
 public:
  EOFToken();

  ~EOFToken() override;

  std::string DebugString() const override;
};

}  // namespace truplc

#endif  // TRUPLC_TOKENS_EOF_TOKEN_H__
