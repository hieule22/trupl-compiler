// Driver program for Scanner class.
// Prints all TruPL tokens and their attributes from a source file.
// Copyright 2016 Hieu Le.

#include <cstdlib>

#include <iostream>

#include "scanner/scanner.h"
#include "util/string_util.h"
#include "util/text_colorizer.h"

int main(int argc, char** argv) {
  char *filename;
  if (argc != 2) {
    truplc::TextColorizer::Print(
        std::cerr, truplc::TextColorizer::kFGRedColorizer,
        truplc::StrCat("Usage: ", argv[0], " <input file name>\n"));
    exit(EXIT_FAILURE);
  }

  filename = argv[1];

  // Declare a scanner object and a pointer to a Token object.
  truplc::Scanner scanner(filename);
  std::unique_ptr<truplc::Token> token;

  do {
    token = scanner.NextToken();
    if (token->GetTokenType() == truplc::TokenType::kUnspecified) {
      truplc::TextColorizer::Print(
          std::cerr, truplc::TextColorizer::kFGRedColorizer,
          "Error: NextToken() returned typeless token.\n");
    } else {
      truplc::TextColorizer::Print(
          std::cout, truplc::TextColorizer::kFGGreenColorizer,
          truplc::StrCat(token->DebugString(), "\n"));
    }
  } while (token->GetTokenType() != truplc::TokenType::kEOF);

  return 0;
}
