// Driver program for Scanner class.
// Prints all TruPL tokens and their attributes from a source file.
// Copyright 2016 Hieu Le.

#include <cstdlib>

#include <iostream>

#include "scanner/scanner.h"
#include "util/text_colorizer.h"

int main(int argc, char** argv) {
  char *filename;
  if (argc != 2) {
    std::cerr <<
        truplc::TextColorizer(truplc::TextColor::FG_RED) <<
        "Usage: " << argv[0] << " <input file name>" <<
        truplc::TextColorizer(truplc::TextColor::FG_DEFAULT) << std::endl;
    exit(EXIT_FAILURE);
  }

  filename = argv[1];

  // Declare a scanner object and a pointer to a Token object.
  truplc::Scanner scanner(filename);
  std::unique_ptr<truplc::Token> token;

  do {
    token = scanner.NextToken();
    if (token->GetTokenType() == truplc::TokenType::kUnspecified) {
      std::cerr <<
          truplc::TextColorizer(truplc::TextColor::FG_RED) <<
          "Error: NextToken() returned typeless token." <<
          truplc::TextColorizer(truplc::TextColor::FG_DEFAULT) << std::endl;
    } else {
      std::cout << token->DebugString() << std::endl;
    }
  } while (token->GetTokenType() != truplc::TokenType::kEOF);

  return 0;
}
