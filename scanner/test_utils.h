// Collection of helper macros and functions that can be used to test
// different phases of the lexical analyzer.
// Copyright Hieu Le 2016.

#ifndef TRUPLC_SCANNER_TEST_UTILS_H__
#define TRUPLC_SCANNER_TEST_UTILS_H__

#include "tokens/add_operator_token.h"
#include "tokens/eof_token.h"
#include "tokens/identifier_token.h"
#include "tokens/keyword_token.h"
#include "tokens/mul_operator_token.h"
#include "tokens/number_token.h"
#include "tokens/punctuation_token.h"
#include "tokens/rel_operator_token.h"
#include "tokens/token.h"

// Keywords.
#define PROGRAM   KeywordToken(KeywordAttribute::kProgram)
#define PROCEDURE KeywordToken(KeywordAttribute::kProcedure)
#define INT       KeywordToken(KeywordAttribute::kInt)
#define BOOL      KeywordToken(KeywordAttribute::kBool)
#define BEGIN     KeywordToken(KeywordAttribute::kBegin)
#define END       KeywordToken(KeywordAttribute::kEnd)
#define IF        KeywordToken(KeywordAttribute::kIf)
#define THEN      KeywordToken(KeywordAttribute::kThen)
#define ELSE      KeywordToken(KeywordAttribute::kElse)
#define WHILE     KeywordToken(KeywordAttribute::kWhile)
#define LOOP      KeywordToken(KeywordAttribute::kLoop)
#define PRINT     KeywordToken(KeywordAttribute::kPrint)
#define NOT       KeywordToken(KeywordAttribute::kNot)

// Punctuations.
#define SEMICOLON    PunctuationToken(PunctuationAttribute::kSemicolon)
#define COLON        PunctuationToken(PunctuationAttribute::kColon)
#define COMMA        PunctuationToken(PunctuationAttribute::kComma)
#define ASSIGNMENT   PunctuationToken(PunctuationAttribute::kAssignment)
#define OPENBRACKET  PunctuationToken(PunctuationAttribute::kOpenBracket)
#define CLOSEBRACKET PunctuationToken(PunctuationAttribute::kCloseBracket)

// Relational operators.
#define EQUAL          RelOperatorToken(RelOperatorAttribute::kEqual)
#define NOTEQUAL       RelOperatorToken(RelOperatorAttribute::kNotEqual)
#define GREATERTHAN    RelOperatorToken(RelOperatorAttribute::kGreaterThan)
#define GREATEROREQUAL RelOperatorToken(RelOperatorAttribute::kGreaterOrEqual)
#define LESSTHAN       RelOperatorToken(RelOperatorAttribute::kLessThan)
#define LESSOREQUAL    RelOperatorToken(RelOperatorAttribute::kLessOrEqual)

// Additive operators.
#define ADD      AddOperatorToken(AddOperatorAttribute::kAdd)
#define SUBTRACT AddOperatorToken(AddOperatorAttribute::kSubtract)
#define OR       AddOperatorToken(AddOperatorAttribute::kOr)

// Multiplicative operators.
#define MULTIPLY MulOperatorToken(MulOperatorAttribute::kMultiply)
#define DIVIDE   MulOperatorToken(MulOperatorAttribute::kDivide)
#define AND      MulOperatorToken(MulOperatorAttribute::kAnd)

// Identifiers and numbers.
#define IDENTIFIER(id) IdentifierToken(id)
#define NUMBER(num)    NumberToken(num)

// EOF
#define ENDOFFILE EOFToken()

#endif  // TRUPLC_SCANNER_TEST_UTILS_H__
