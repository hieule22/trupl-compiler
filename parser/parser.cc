// Implementation for Parser class.
// Copyright 2016 Hieu Le.

#include "parser/parser.h"

#include <utility>

namespace truplc {

Parser::Parser(std::unique_ptr<Scanner> scanner)
    : internal_parser_(std::move(scanner)) {}

bool Parser::ParseProgram() {
  return internal_parser_.ParseProgram();
}

bool Parser::HasNextToken() const {
  return internal_parser_.HasNextToken();
}

}  // namespace truplc
