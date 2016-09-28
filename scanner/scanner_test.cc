// Unit tests for Scanner class.
// Copyright 2016 Hieu Le.

#include "scanner/scanner.h"

#include <sstream>
#include <unordered_map>
#include <utility>

#include "gtest/gtest.h"
#include "scanner/stream_buffer.h"

namespace truplc {
namespace {

class ScannerTest : public testing::Test {
 protected:
  ScannerTest() {
    table["int"] = std::make_unique<KeywordToken>(KeywordAttribute::kInt);
    table["a"] = std::make_unique<IdentifierToken>("a");
    table["="] = std::make_unique<RelOperatorToken>(
        RelOperatorAttribute::kEqual);
    table["1"] = std::make_unique<NumberToken>("1");
    table[";"] = std::make_unique<PunctuationToken>(
        PunctuationAttribute::kSemicolon);
    table["+"] = std::make_unique<AddOperatorToken>(AddOperatorAttribute::kAdd);
    table["$"] = std::make_unique<EOFToken>();
  }
  
  // Creates a character buffer from given input string.
  std::unique_ptr<Buffer> CreateBuffer(const std::string& input) {
    ss = std::make_unique<std::istringstream>(input);
    return std::make_unique<StreamBuffer>(ss.get());
  }

  // Gets the cached attributes for a given list of tokens.
  std::vector<Token*> GetAttributes(const std::vector<std::string>& tokens) {
    std::vector<Token*> attributes;
    for (const std::string& token : tokens) {
      attributes.push_back(table[token].get());
    }
    return attributes;
  }

  // Checks if the token represented in given string matches expected token.
  void TestSingleToken(const std::string& input, const Token& expected) {
    Scanner scanner(CreateBuffer(input));
    std::unique_ptr<Token> actual = scanner.NextToken();
    EXPECT_EQ(actual->DebugString(), expected.DebugString());
  }

  void TestMultipleTokens(const std::string& input,
                          const std::vector<Token*> tokens) {
    Scanner scanner(CreateBuffer(input));
    for (const Token* expected : tokens) {
      std::unique_ptr<Token> actual = scanner.NextToken();
      EXPECT_EQ(actual->DebugString(), expected->DebugString());
    }
  }

 private:
  std::unique_ptr<std::istringstream> ss;
  std::unordered_map<std::string, std::unique_ptr<Token>> table;
};

TEST_F(ScannerTest, NextTokenBasic) {
  TestSingleToken("program", KeywordToken(KeywordAttribute::kProgram));
  TestSingleToken("procedure", KeywordToken(KeywordAttribute::kProcedure));
  TestSingleToken("int", KeywordToken(KeywordAttribute::kInt));
  TestSingleToken("bool", KeywordToken(KeywordAttribute::kBool));
  TestSingleToken("begin", KeywordToken(KeywordAttribute::kBegin));
  TestSingleToken("end", KeywordToken(KeywordAttribute::kEnd));
  TestSingleToken("if", KeywordToken(KeywordAttribute::kIf));
  TestSingleToken("then", KeywordToken(KeywordAttribute::kThen));
  TestSingleToken("else", KeywordToken(KeywordAttribute::kElse));
  TestSingleToken("while", KeywordToken(KeywordAttribute::kWhile));
  TestSingleToken("loop", KeywordToken(KeywordAttribute::kLoop));
  TestSingleToken("print", KeywordToken(KeywordAttribute::kPrint));
  TestSingleToken("not", KeywordToken(KeywordAttribute::kNot));

  TestSingleToken(";", PunctuationToken(PunctuationAttribute::kSemicolon));
  TestSingleToken(":", PunctuationToken(PunctuationAttribute::kColon));
  TestSingleToken(",", PunctuationToken(PunctuationAttribute::kComma));
  TestSingleToken(":=", PunctuationToken(PunctuationAttribute::kAssignment));
  TestSingleToken("(", PunctuationToken(PunctuationAttribute::kOpenBracket));
  TestSingleToken(")", PunctuationToken(PunctuationAttribute::kCloseBracket));

  TestSingleToken("=", RelOperatorToken(RelOperatorAttribute::kEqual));
  TestSingleToken("<>", RelOperatorToken(RelOperatorAttribute::kNotEqual));
  TestSingleToken(">", RelOperatorToken(RelOperatorAttribute::kGreaterThan));
  TestSingleToken(">=", RelOperatorToken(RelOperatorAttribute::kGreaterOrEqual));
  TestSingleToken("<", RelOperatorToken(RelOperatorAttribute::kLessThan));
  TestSingleToken("<=", RelOperatorToken(RelOperatorAttribute::kLessOrEqual));

  TestSingleToken("+", AddOperatorToken(AddOperatorAttribute::kAdd));
  TestSingleToken("-", AddOperatorToken(AddOperatorAttribute::kSubtract));
  TestSingleToken("or", AddOperatorToken(AddOperatorAttribute::kOr));

  TestSingleToken("*", MulOperatorToken(MulOperatorAttribute::kMultiply));
  TestSingleToken("/", MulOperatorToken(MulOperatorAttribute::kDivide));
  TestSingleToken("and", MulOperatorToken(MulOperatorAttribute::kAnd));

  TestSingleToken("foobarquoz", IdentifierToken("foobarquoz"));
  TestSingleToken("a", IdentifierToken("a"));
  TestSingleToken("z", IdentifierToken("z"));
  TestSingleToken("ints", IdentifierToken("ints"));
  TestSingleToken("loo", IdentifierToken("loo"));
  TestSingleToken("elseif", IdentifierToken("elseif"));
  TestSingleToken("myprocedure", IdentifierToken("myprocedure"));
  TestSingleToken("andnota23", IdentifierToken("andnota23"));
  TestSingleToken("a1b2c3d4e5f6g7h8i9", IdentifierToken("a1b2c3d4e5f6g7h8i9"));
  TestSingleToken("a123456789", IdentifierToken("a123456789"));

  TestSingleToken("1", NumberToken("1"));
  TestSingleToken("9999999999999", NumberToken("9999999999999"));
  TestSingleToken("000000000000", NumberToken("000000000000"));
  TestSingleToken("123456789", NumberToken("123456789"));

  TestSingleToken("", EOFToken());
}

TEST_F(ScannerTest, MultipleNextTokens) {
  TestMultipleTokens("int a = 1;", GetAttributes({
        "int", "a", "=", "1", ";"}));
  TestMultipleTokens("int a = 1 + 1 + 1;", GetAttributes({
        "int", "a", "=", "1", "+", "1", "+", "1", ";"}));
}

}  // namespace
}  // namespace truplc
