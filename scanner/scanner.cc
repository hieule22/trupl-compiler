// Implementation for Scanner class.
// Copyright 2016 Hieu Le.

#include "scanner/scanner.h"

#include <cctype>

#include <utility>
#include <vector>

#include "scanner/file_buffer.h"

namespace truplc {
namespace {

// Set of states for the deterministic finite automata that recognizes all
// the valid lexemes of TruPL.

const int START = 0;
const int DONE = 999;
const int IDENTIFIER = 1;
const int NUMBER = 24;
const int END_OF_FILE = 25;

const int A = 2;
const int AN = 40;
const int AND = 41;
const int B = 3;
const int BE = 42;
const int BEG = 44;
const int BEGI = 45;
const int BEGIN = 46;
const int BO = 43;
const int BOO = 47;
const int BOOL = 48;
const int E = 4;
const int EL = 49;
const int ELS = 50;
const int ELSE = 51;
const int EN = 52;
const int END = 53;
const int I = 5;
const int IF = 54;
const int IN = 55;
const int INT = 56;
const int L = 6;
const int LO = 57;
const int LOO = 58;
const int LOOP = 59;
const int N = 7;
const int NO = 60;
const int NOT = 61;
const int O = 8;
const int OR = 62;
const int P = 9;
const int PR = 63;
const int PRI = 64;
const int PRIN = 65;
const int PRINT = 66;
const int PRO = 67;
const int PROC = 68;
const int PROCE = 69;
const int PROCED = 70;
const int PROCEDU = 71;
const int PROCEDUR = 72;
const int PROCEDURE = 73;
const int PROG = 74;
const int PROGR = 75;
const int PROGRA = 76;
const int PROGRAM = 77;
const int T = 10;
const int TH = 78;
const int THE = 79;
const int THEN = 80;
const int W = 11;
const int WH = 81;
const int WHI = 82;
const int WHIL = 83;
const int WHILE = 84;

const int SEMICOLON = 12;
const int COLON = 13;
const int COMMA = 14;
const int OPENBRACKET = 15;
const int CLOSEBRACKET = 16;
const int EQUAL = 17;
const int LESS = 18;
const int LESSEQUAL = 34;
const int NOTEQUAL = 35;
const int GREATER = 19;
const int GREATEREQUAL = 36;
const int ADD = 20;
const int SUBTRACT = 21;
const int MULTIPLY = 22;
const int DIVIDE = 32;
const int ASSIGN = 33;

// Checks if a target character is a member of a given set of characters.
bool IsMemberOf(const char target, const std::vector<char>& collection) {
  for (const char c : collection) {
    if (target == c) {
      return true;
    }
  }
  return false;
}

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
  std::cerr << "Exiting on Scanner Fatal Error: " << message << std::endl;
  exit(EXIT_FAILURE);
}

std::unique_ptr<Token> Scanner::NextToken() {
  int state = START;
  std::string attribute;
  Token* token = NULL;

  while (state != DONE) {
    // Always read a char from buffer before each transition.
    char c = buffer_->NextChar();
    // std::cerr << "State: " << state << std::endl;
    // std::cerr << "Symbol: " << c << std::endl;

    switch (state) {
      case START:
        if (IsAlpha(c) && !IsMemberOf(c, {
              'a', 'b', 'e', 'i', 'l', 'n', 'o', 'p', 't', 'w'})) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else if (c == 'a') {
          state = A;
          attribute.push_back(c);
        } else if (c == 'b') {
          state = B;
          attribute.push_back(c);
        } else if (c == 'e') {
          state = E;
          attribute.push_back(c);
        } else if (c == 'i') {
          state = I;
          attribute.push_back(c);
        } else if (c == 'l') {
          state = L;
          attribute.push_back(c);
        } else if (c == 'n') {
          state = N;
          attribute.push_back(c);
        } else if (c == 'o') {
          state = O;
          attribute.push_back(c);
        } else if (c == 'p') {
          state = P;
          attribute.push_back(c);
        } else if (c == 't') {
          state = T;
          attribute.push_back(c);
        } else if (c == 'w') {
          state = W;
          attribute.push_back(c);
        } else if (c == ';') {
          state = SEMICOLON;
        } else if (c == ':') {
          state = COLON;
        } else if (c == ',') {
          state = COMMA;
        } else if (c == '(') {
          state = OPENBRACKET;
        } else if (c == ')') {
          state = CLOSEBRACKET;
        } else if (c == '=') {
          state = EQUAL;
        } else if (c == '<') {
          state = LESS;
        } else if (c == '>') {
          state = GREATER;
        } else if (c == '+') {
          state = ADD;
        } else if (c == '-') {
          state = SUBTRACT;
        } else if (c == '*') {
          state = MULTIPLY;
        } else if (c == '/') {
          state = DIVIDE;
        } else if (IsDigit(c)) {
          state = NUMBER;
          attribute.push_back(c);
        } else if (c == kEOFMarker) {
          state = END_OF_FILE;
        } else {
          ScannerFatalError(std::string("Illegal character: ") + c);
        }
        break;

      case IDENTIFIER:
        if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case A:
        if (c == 'n') {
          state = AN;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case AN:
        if (c == 'd') {
          state = AND;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case AND:
        if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new MulOperatorToken(MulOperatorAttribute::kAnd);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case B:
        if (c == 'e') {
          state = BE;
          attribute.push_back(c);
        } else if (c == 'o') {
          state = BO;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case BE:
        if (c == 'g') {
          state = BEG;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case BEG:
        if (c == 'i') {
          state = BEGI;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case BEGI:
        if (c == 'n') {
          state = BEGIN;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case BEGIN:
        if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new KeywordToken(KeywordAttribute::kBegin);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case BO:
        if (c == 'o') {
          state = BOO;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case BOO:
        if (c == 'l') {
          state = BOOL;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case BOOL:
        if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new KeywordToken(KeywordAttribute::kBool);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case E:
        if (c == 'l') {
          state = EL;
          attribute.push_back(c);
        } else if (c == 'n') {
          state = EN;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case EL:
        if (c == 's') {
          state = ELS;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case ELS:
        if (c == 'e') {
          state = ELSE;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case ELSE:
        if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new KeywordToken(KeywordAttribute::kElse);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case EN:
        if (c == 'd') {
          state = END;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case END:
        if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new KeywordToken(KeywordAttribute::kEnd);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case I:
        if (c == 'f') {
          state = IF;
          attribute.push_back(c);
        } else if (c == 'n') {
          state = IN;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case IF:
        if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new KeywordToken(KeywordAttribute::kIf);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case IN:
        if (c == 't') {
          state = INT;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case INT:
        if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new KeywordToken(KeywordAttribute::kInt);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case L:
        if (c == 'o') {
          state = LO;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case LO:
        if (c == 'o') {
          state = LOO;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case LOO:
        if (c == 'p') {
          state = LOOP;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case LOOP:
        if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new KeywordToken(KeywordAttribute::kLoop);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case N:
        if (c == 'o') {
          state = NO;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case NO:
        if (c == 't') {
          state = NOT;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case NOT:
        if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new KeywordToken(KeywordAttribute::kNot);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case O:
        if (c == 'r') {
          state = OR;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case OR:
        if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new AddOperatorToken(AddOperatorAttribute::kOr);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case P:
        if (c == 'r') {
          state = PR;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case PR:
        if (c == 'i') {
          state = PRI;
          attribute.push_back(c);
        } else if (c == 'o') {
          state = PRO;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case PRI:
        if (c == 'n') {
          state = PRIN;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case PRIN:
        if (c == 't') {
          state = PRINT;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case PRINT:
        if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new KeywordToken(KeywordAttribute::kPrint);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case PRO:
        if (c == 'c') {
          state = PROC;
          attribute.push_back(c);
        } else if (c == 'g') {
          state = PROG;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case PROC:
        if (c == 'e') {
          state = PROCE;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case PROCE:
        if (c == 'd') {
          state = PROCED;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case PROCED:
        if (c == 'u') {
          state = PROCEDU;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case PROCEDU:
        if (c == 'r') {
          state = PROCEDUR;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case PROCEDUR:
        if (c == 'e') {
          state = PROCEDURE;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case PROCEDURE:
        if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new KeywordToken(KeywordAttribute::kProcedure);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case PROG:
        if (c == 'r') {
          state = PROGR;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case PROGR:
        if (c == 'a') {
          state = PROGRA;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case PROGRA:
        if (c == 'm') {
          state = PROGRAM;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case PROGRAM:
        if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new KeywordToken(KeywordAttribute::kProgram);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case T:
        if (c == 'h') {
          state = TH;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case TH:
        if (c == 'e') {
          state = THE;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case THE:
        if (c == 'n') {
          state = THEN;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case THEN:
        if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new KeywordToken(KeywordAttribute::kThen);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case W:
        if (c == 'h') {
          state = WH;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case WH:
        if (c == 'i') {
          state = WHI;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case WHI:
        if (c == 'l') {
          state = WHIL;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case WHIL:
        if (c == 'e') {
          state = WHILE;
          attribute.push_back(c);
        } else if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new IdentifierToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case WHILE:
        if (IsAlphanumeric(c)) {
          state = IDENTIFIER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new KeywordToken(KeywordAttribute::kWhile);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case SEMICOLON:
        state = DONE;
        token = new PunctuationToken(PunctuationAttribute::kSemicolon);
        if (!IsSpace(c)) {
          buffer_->UnreadChar(c);
        }
        break;

      case COLON:
        if (c == '=') {
          state = ASSIGN;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new PunctuationToken(PunctuationAttribute::kColon);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case ASSIGN:
        state = DONE;
        token = new PunctuationToken(PunctuationAttribute::kAssignment);
        if (!IsSpace(c)) {
          buffer_->UnreadChar(c);
        }
        break;

      case COMMA:
        state = DONE;
        token = new PunctuationToken(PunctuationAttribute::kComma);
        if (!IsSpace(c)) {
          buffer_->UnreadChar(c);
        }
        break;

      case OPENBRACKET:
        state = DONE;
        token = new PunctuationToken(PunctuationAttribute::kOpenBracket);
        if (!IsSpace(c)) {
          buffer_->UnreadChar(c);
        }
        break;

      case CLOSEBRACKET:
        state = DONE;
        token = new PunctuationToken(PunctuationAttribute::kCloseBracket);
        if (!IsSpace(c)) {
          buffer_->UnreadChar(c);
        }
        break;

      case EQUAL:
        state = DONE;
        token = new RelOperatorToken(RelOperatorAttribute::kEqual);
        if (!IsSpace(c)) {
          buffer_->UnreadChar(c);
        }
        break;

      case LESS:
        if (c == '=') {
          state = LESSEQUAL;
          attribute.push_back(c);
        } else if (c == '>') {
          state = NOTEQUAL;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new RelOperatorToken(RelOperatorAttribute::kLessThan);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case LESSEQUAL:
        state = DONE;
        token = new RelOperatorToken(RelOperatorAttribute::kLessOrEqual);
        if (!IsSpace(c)) {
          buffer_->UnreadChar(c);
        }
        break;

      case NOTEQUAL:
        state = DONE;
        token = new RelOperatorToken(RelOperatorAttribute::kNotEqual);
        if (!IsSpace(c)) {
          buffer_->UnreadChar(c);
        }
        break;

      case GREATER:
        if (c == '=') {
          state = GREATEREQUAL;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new RelOperatorToken(RelOperatorAttribute::kGreaterThan);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case GREATEREQUAL:
        state = DONE;
        token = new RelOperatorToken(RelOperatorAttribute::kGreaterOrEqual);
        if (!IsSpace(c)) {
          buffer_->UnreadChar(c);
        }
        break;

      case ADD:
        state = DONE;
        token = new AddOperatorToken(AddOperatorAttribute::kAdd);
        if (!IsSpace(c)) {
          buffer_->UnreadChar(c);
        }
        break;

      case SUBTRACT:
        state = DONE;
        token = new AddOperatorToken(AddOperatorAttribute::kSubtract);
        if (!IsSpace(c)) {
          buffer_->UnreadChar(c);
        }
        break;

      case MULTIPLY:
        state = DONE;
        token = new MulOperatorToken(MulOperatorAttribute::kMultiply);
        if (!IsSpace(c)) {
          buffer_->UnreadChar(c);
        }
        break;

      case DIVIDE:
        state = DONE;
        token = new MulOperatorToken(MulOperatorAttribute::kDivide);
        if (!IsSpace(c)) {
          buffer_->UnreadChar(c);
        }
        break;

      case NUMBER:
        if (IsDigit(c)) {
          state = NUMBER;
          attribute.push_back(c);
        } else {
          state = DONE;
          token = new NumberToken(attribute);
          if (!IsSpace(c)) {
            buffer_->UnreadChar(c);
          }
        }
        break;

      case END_OF_FILE:
        state = DONE;
        token = new EOFToken();
        break;

      default:
        break;
    }
  }

  return std::unique_ptr<Token>(token);
}

}  // namespace truplc
