// The lexical analyzer for the TruPL compiler.
// Copyright 2016 Hieu Le.

#ifndef TRUPLC_SCANNER_SCANNER_H__
#define TRUPLC_SCANNER_SCANNER_H__

#include <iostream>
#include <memory>
#include <string>

#include "scanner/buffer.h"
#include "tokens/add_operator_token.h"
#include "tokens/eof_token.h"
#include "tokens/identifier_token.h"
#include "tokens/keyword_token.h"
#include "tokens/mul_operator_token.h"
#include "tokens/number_token.h"
#include "tokens/punctuation_token.h"
#include "tokens/rel_operator_token.h"
#include "tokens/token.h"

namespace truplc {

class Scanner {
 public:
  // Constructs a Scanner for a given file.
  explicit Scanner(const std::string& filename);

  // Constructs a Scanner on a given buffer.
  explicit Scanner(std::unique_ptr<Buffer> buffer);

  ~Scanner();

  // Returns the next token in this file.
  std::unique_ptr<Token> NextToken();

 private:
  // If a lexical error OR an internal scanner error occurs, call this method.
  // It will print the message and exit.
  void ScannerFatalError(const std::string& message) const;

  // The character buffer.
  std::unique_ptr<Buffer> buffer_;
};

}  // namespace truplc

#endif  // TRUPLC_SCANNER_SCANNER_H__
