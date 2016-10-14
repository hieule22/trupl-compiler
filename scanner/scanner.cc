// Implementation for Scanner class.
// Copyright 2016 Hieu Le.

#include "scanner/scanner.h"

#include <cctype>

#include <utility>
#include <vector>

#include "scanner/file_buffer.h"
#include "util/container_util.h"
#include "util/string_util.h"
#include "util/text_colorizer.h"

namespace truplc {
namespace {

// Set of states for the deterministic finite automata that recognizes all
// the valid lexemes of TruPL.
enum class State : int {
  START        = 0,
  DONE         = 999,
  IDENTIFIER   = 1,
  NUMBER       = 2,
  END_OF_FILE  = 3,

  A            = 4,
  AN           = 5,
  AND          = 6,
  B            = 7,
  BE           = 8,
  BEG          = 9,
  BEGI         = 10,
  BEGIN        = 11,
  BO           = 12,
  BOO          = 13,
  BOOL         = 14,
  E            = 15,
  EL           = 16,
  ELS          = 17,
  ELSE         = 18,
  EN           = 19,
  END          = 20,
  I            = 21,
  IF           = 22,
  IN           = 23,
  INT          = 24,
  L            = 25,
  LO           = 26,
  LOO          = 27,
  LOOP         = 28,
  N            = 29,
  NO           = 30,
  NOT          = 31,
  O            = 32,
  OR           = 33,
  P            = 34,
  PR           = 35,
  PRI          = 36,
  PRIN         = 37,
  PRINT        = 38,
  PRO          = 39,
  PROC         = 40,
  PROCE        = 41,
  PROCED       = 42,
  PROCEDU      = 43,
  PROCEDUR     = 44,
  PROCEDURE    = 45,
  PROG         = 46,
  PROGR        = 47,
  PROGRA       = 48,
  PROGRAM      = 49,
  T            = 50,
  TH           = 51,
  THE          = 52,
  THEN         = 53,
  W            = 54,
  WH           = 55,
  WHI          = 56,
  WHIL         = 57,
  WHILE        = 58,

  SEMICOLON    = 59,
  COLON        = 60,
  COMMA        = 61,
  OPENBRACKET  = 62,
  CLOSEBRACKET = 63,
  EQUAL        = 64,
  LESS         = 65,
  LESSEQUAL    = 66,
  NOTEQUAL     = 67,
  GREATER      = 68,
  GREATEREQUAL = 69,
  ADD          = 70,
  SUBTRACT     = 71,
  MULTIPLY     = 72,
  DIVIDE       = 73,
  ASSIGN       = 74,
};

// Checks if a given character represents a lowercase letter.
bool IsAlpha(const char c) {
  return std::islower(c);
}

// Checks if a given character represents a digit.
bool IsDigit(const char c) {
  return std::isdigit(c);
}

// Checks if a given character represents a space.
bool IsSpace(const char c) {
  return c == kSpace;
}

// Checks if a given character represents a lowercase letter or a digit.
bool IsAlphanumeric(const char c) {
  return IsAlpha(c) || IsDigit(c);
}

}  // namespace

Scanner::Scanner(const std::string& filename)
    : buffer_(new FileBuffer(filename)) {}

Scanner::Scanner(std::unique_ptr<Buffer> buffer)
    : buffer_(std::move(buffer)) {}

void Scanner::ScannerFatalError(const std::string& message) const {
  TextColorizer::Print(std::cerr, TextColorizer::kFGRedColorizer,
                       StrCat("Exiting on Scanner Fatal Error: ",
                              message, "\n"));
  exit(EXIT_FAILURE);
}

std::unique_ptr<Token> Scanner::NextToken() {
  State state = State::START;
  std::string attribute;
  Token* token = NULL;

  while (state != State::DONE) {
    // Always read a char from buffer before each transition.
    char c = buffer_->NextChar();

    switch (state) {
      case State::START:
        if (IsAlpha(c) && !Contain<std::vector<int>, int>( {
              'a', 'b', 'e', 'i', 'l', 'n', 'o', 'p', 't', 'w'}, c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else if (c == 'a') {
          state = State::A;
          attribute.push_back(c);
        } else if (c == 'b') {
          state = State::B;
          attribute.push_back(c);
        } else if (c == 'e') {
          state = State::E;
          attribute.push_back(c);
        } else if (c == 'i') {
          state = State::I;
          attribute.push_back(c);
        } else if (c == 'l') {
          state = State::L;
          attribute.push_back(c);
        } else if (c == 'n') {
          state = State::N;
          attribute.push_back(c);
        } else if (c == 'o') {
          state = State::O;
          attribute.push_back(c);
        } else if (c == 'p') {
          state = State::P;
          attribute.push_back(c);
        } else if (c == 't') {
          state = State::T;
          attribute.push_back(c);
        } else if (c == 'w') {
          state = State::W;
          attribute.push_back(c);
        } else if (c == ';') {
          state = State::SEMICOLON;
        } else if (c == ':') {
          state = State::COLON;
        } else if (c == ',') {
          state = State::COMMA;
        } else if (c == '(') {
          state = State::OPENBRACKET;
        } else if (c == ')') {
          state = State::CLOSEBRACKET;
        } else if (c == '=') {
          state = State::EQUAL;
        } else if (c == '<') {
          state = State::LESS;
        } else if (c == '>') {
          state = State::GREATER;
        } else if (c == '+') {
          state = State::ADD;
        } else if (c == '-') {
          state = State::SUBTRACT;
        } else if (c == '*') {
          state = State::MULTIPLY;
        } else if (c == '/') {
          state = State::DIVIDE;
        } else if (IsDigit(c)) {
          state = State::NUMBER;
          attribute.push_back(c);
        } else if (c == kEOFMarker) {
          state = State::END_OF_FILE;
        } else {
          ScannerFatalError(StrCat("Illegal character: ", std::string(1, c)));
        }
        break;

      case State::IDENTIFIER:
        if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::A:
        if (c == 'n') {
          state = State::AN;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::AN:
        if (c == 'd') {
          state = State::AND;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::AND:
        if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new MulOperatorToken(MulOperatorAttribute::kAnd);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::B:
        if (c == 'e') {
          state = State::BE;
          attribute.push_back(c);
        } else if (c == 'o') {
          state = State::BO;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::BE:
        if (c == 'g') {
          state = State::BEG;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::BEG:
        if (c == 'i') {
          state = State::BEGI;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::BEGI:
        if (c == 'n') {
          state = State::BEGIN;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::BEGIN:
        if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new KeywordToken(KeywordAttribute::kBegin);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::BO:
        if (c == 'o') {
          state = State::BOO;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::BOO:
        if (c == 'l') {
          state = State::BOOL;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::BOOL:
        if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new KeywordToken(KeywordAttribute::kBool);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::E:
        if (c == 'l') {
          state = State::EL;
          attribute.push_back(c);
        } else if (c == 'n') {
          state = State::EN;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::EL:
        if (c == 's') {
          state = State::ELS;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::ELS:
        if (c == 'e') {
          state = State::ELSE;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::ELSE:
        if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new KeywordToken(KeywordAttribute::kElse);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::EN:
        if (c == 'd') {
          state = State::END;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::END:
        if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new KeywordToken(KeywordAttribute::kEnd);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::I:
        if (c == 'f') {
          state = State::IF;
          attribute.push_back(c);
        } else if (c == 'n') {
          state = State::IN;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::IF:
        if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new KeywordToken(KeywordAttribute::kIf);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::IN:
        if (c == 't') {
          state = State::INT;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::INT:
        if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new KeywordToken(KeywordAttribute::kInt);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::L:
        if (c == 'o') {
          state = State::LO;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::LO:
        if (c == 'o') {
          state = State::LOO;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::LOO:
        if (c == 'p') {
          state = State::LOOP;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::LOOP:
        if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new KeywordToken(KeywordAttribute::kLoop);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::N:
        if (c == 'o') {
          state = State::NO;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::NO:
        if (c == 't') {
          state = State::NOT;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::NOT:
        if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new KeywordToken(KeywordAttribute::kNot);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::O:
        if (c == 'r') {
          state = State::OR;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::OR:
        if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new AddOperatorToken(AddOperatorAttribute::kOr);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::P:
        if (c == 'r') {
          state = State::PR;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::PR:
        if (c == 'i') {
          state = State::PRI;
          attribute.push_back(c);
        } else if (c == 'o') {
          state = State::PRO;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::PRI:
        if (c == 'n') {
          state = State::PRIN;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::PRIN:
        if (c == 't') {
          state = State::PRINT;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::PRINT:
        if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new KeywordToken(KeywordAttribute::kPrint);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::PRO:
        if (c == 'c') {
          state = State::PROC;
          attribute.push_back(c);
        } else if (c == 'g') {
          state = State::PROG;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::PROC:
        if (c == 'e') {
          state = State::PROCE;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::PROCE:
        if (c == 'd') {
          state = State::PROCED;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::PROCED:
        if (c == 'u') {
          state = State::PROCEDU;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::PROCEDU:
        if (c == 'r') {
          state = State::PROCEDUR;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::PROCEDUR:
        if (c == 'e') {
          state = State::PROCEDURE;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::PROCEDURE:
        if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new KeywordToken(KeywordAttribute::kProcedure);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::PROG:
        if (c == 'r') {
          state = State::PROGR;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::PROGR:
        if (c == 'a') {
          state = State::PROGRA;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::PROGRA:
        if (c == 'm') {
          state = State::PROGRAM;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::PROGRAM:
        if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new KeywordToken(KeywordAttribute::kProgram);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::T:
        if (c == 'h') {
          state = State::TH;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::TH:
        if (c == 'e') {
          state = State::THE;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::THE:
        if (c == 'n') {
          state = State::THEN;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::THEN:
        if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new KeywordToken(KeywordAttribute::kThen);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::W:
        if (c == 'h') {
          state = State::WH;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::WH:
        if (c == 'i') {
          state = State::WHI;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::WHI:
        if (c == 'l') {
          state = State::WHIL;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::WHIL:
        if (c == 'e') {
          state = State::WHILE;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::WHILE:
        if (IsAlphanumeric(c)) {
          state = State::IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new KeywordToken(KeywordAttribute::kWhile);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::SEMICOLON:
        state = State::DONE;
        token = new PunctuationToken(PunctuationAttribute::kSemicolon);
        if (!IsSpace(c)) {
          buffer_->UnreadChar(c);
        }
        break;

      case State::COLON:
        if (c == '=') {
          state = State::ASSIGN;
        } else {
          state = State::DONE;
          token = new PunctuationToken(PunctuationAttribute::kColon);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::ASSIGN:
        state = State::DONE;
        token = new PunctuationToken(PunctuationAttribute::kAssignment);
        if (!IsSpace(c)) {
          buffer_->UnreadChar(c);
        }
        break;

      case State::COMMA:
        state = State::DONE;
        token = new PunctuationToken(PunctuationAttribute::kComma);
        if (!IsSpace(c)) {
          buffer_->UnreadChar(c);
        }
        break;

      case State::OPENBRACKET:
        state = State::DONE;
        token = new PunctuationToken(PunctuationAttribute::kOpenBracket);
        if (!IsSpace(c)) {
          buffer_->UnreadChar(c);
        }
        break;

      case State::CLOSEBRACKET:
        state = State::DONE;
        token = new PunctuationToken(PunctuationAttribute::kCloseBracket);
        if (!IsSpace(c)) {
          buffer_->UnreadChar(c);
        }
        break;

      case State::EQUAL:
        state = State::DONE;
        token = new RelOperatorToken(RelOperatorAttribute::kEqual);
        if (!IsSpace(c)) {
          buffer_->UnreadChar(c);
        }
        break;

      case State::LESS:
        if (c == '=') {
          state = State::LESSEQUAL;
        } else if (c == '>') {
          state = State::NOTEQUAL;
        } else {
          state = State::DONE;
          token = new RelOperatorToken(RelOperatorAttribute::kLessThan);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::LESSEQUAL:
        state = State::DONE;
        token = new RelOperatorToken(RelOperatorAttribute::kLessOrEqual);
        if (!IsSpace(c)) {
          buffer_->UnreadChar(c);
        }
        break;

      case State::NOTEQUAL:
        state = State::DONE;
        token = new RelOperatorToken(RelOperatorAttribute::kNotEqual);
        if (!IsSpace(c)) {
          buffer_->UnreadChar(c);
        }
        break;

      case State::GREATER:
        if (c == '=') {
          state = State::GREATEREQUAL;
        } else {
          state = State::DONE;
          token = new RelOperatorToken(RelOperatorAttribute::kGreaterThan);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::GREATEREQUAL:
        state = State::DONE;
        token = new RelOperatorToken(RelOperatorAttribute::kGreaterOrEqual);
        if (!IsSpace(c)) {
          buffer_->UnreadChar(c);
        }
        break;

      case State::ADD:
        state = State::DONE;
        token = new AddOperatorToken(AddOperatorAttribute::kAdd);
        if (!IsSpace(c)) {
          buffer_->UnreadChar(c);
        }
        break;

      case State::SUBTRACT:
        state = State::DONE;
        token = new AddOperatorToken(AddOperatorAttribute::kSubtract);
        if (!IsSpace(c)) {
          buffer_->UnreadChar(c);
        }
        break;

      case State::MULTIPLY:
        state = State::DONE;
        token = new MulOperatorToken(MulOperatorAttribute::kMultiply);
        if (!IsSpace(c)) {
          buffer_->UnreadChar(c);
        }
        break;

      case State::DIVIDE:
        state = State::DONE;
        token = new MulOperatorToken(MulOperatorAttribute::kDivide);
        if (!IsSpace(c)) {
          buffer_->UnreadChar(c);
        }
        break;

      case State::NUMBER:
        if (IsDigit(c)) {
          state = State::NUMBER;
          attribute.push_back(c);
        } else {
          state = State::DONE;
          token = new NumberToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case State::END_OF_FILE:
        state = State::DONE;
        token = new EOFToken();
        break;

      default:
        break;
    }
  }

  return std::unique_ptr<Token>(token);
}

}  // namespace truplc
