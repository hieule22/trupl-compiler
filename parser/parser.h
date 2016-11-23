// Parser verifies if the tokens generated by Scanner forms a syntactically
// and semantically valid program. Syntax analysis checks if the tokens agrees
// with the production rules of TruPL grammar. Semantic analysis performs basic
// type and declaration checks. A parsing error might be accompanied by an
// intelligible error message.
// Copyright 2016 Hieu Le.

#ifndef TRUPLC_PARSER_PARSER_H__
#define TRUPLC_PARSER_PARSER_H__

#include <memory>

#include "scanner/scanner.h"

namespace truplc {

class Parser {
 public:
  // Constructs a Parser for a specified Scanner.
  // Ownership of the Scanner is acquired by this Parser instance.
  explicit Parser(std::unique_ptr<Scanner> scanner);

  // Attemps to parse the program generated by tokens from Scanner.
  // Returns true if the parse succeeds, i.e. the program is valid, and false
  // if there is a syntax error. Parsing is terminated as soon as a semantic
  // error is encountered.
  bool ParseProgram();

  // Checks if all the tokens produced by Scanner have been exhausted.
  bool HasNextToken() const;
};

}  // namespace truplc

#endif  // TRUPLC_PARSER_PARSER_H__
