// Unit tests for Scanner class.
// Copyright 2016 Hieu Le.

#include "scanner/scanner.h"

#include <list>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <vector>

#include "test/scanner/test_utils.h"

#include "gtest/gtest.h"

namespace truplc {
namespace {

// Mock class that mimicks the behaviors of a Buffer class.
class MockBuffer : public Buffer {
 public:
  // Input string must be in the proper format ready for processing by Scanner.
  explicit MockBuffer(const std::string& input)
      : buffer_(input.begin(), input.end()) {}

  char NextChar() override {
    if (buffer_.empty()) {
      return kEOFMarker;
    }
    const char head = buffer_.front();
    buffer_.pop_front();
    return head;
  }

  void UnreadChar(const char c) override {
    if (c != kEOFMarker) {
      buffer_.push_front(c);
    }
  }

 private:
  std::list<char> buffer_;
};

// Creates a character buffer from given input string.
std::unique_ptr<Buffer> CreateBuffer(const std::string& input) {
  return std::make_unique<MockBuffer>(input);
}

// Checks if the token represented in input string matches expected token.
void MatchSingleToken(const std::string& input, const Token& expected) {
  Scanner scanner(CreateBuffer(input));
  std::unique_ptr<Token> actual = scanner.NextToken();
  EXPECT_EQ(actual->DebugString(), expected.DebugString());
  EXPECT_EQ(scanner.NextToken()->DebugString(), ENDOFFILE.DebugString());
}

// Tests if the tokens represented in input string matches a list of
// expected tokens.
void MatchTokens(const std::string& input, const std::vector<Token*>& tokens) {
  Scanner scanner(CreateBuffer(input));
  for (const auto& token : tokens) {
    std::unique_ptr<Token> actual = scanner.NextToken();
    std::unique_ptr<Token> expected(token);
    EXPECT_EQ(actual->DebugString(), expected->DebugString());
  }
}

TEST(ScannerTest, NextTokenBasic) {
  MatchSingleToken("p", IDENTIFIER("p"));
  MatchSingleToken("pr", IDENTIFIER("pr"));
  MatchSingleToken("pro", IDENTIFIER("pro"));
  MatchSingleToken("prog", IDENTIFIER("prog"));
  MatchSingleToken("progr", IDENTIFIER("progr"));
  MatchSingleToken("progra", IDENTIFIER("progra"));
  MatchSingleToken("program", PROGRAM);
  MatchSingleToken("programs", IDENTIFIER("programs"));

  MatchSingleToken("proc", IDENTIFIER("proc"));
  MatchSingleToken("proce", IDENTIFIER("proce"));
  MatchSingleToken("proced", IDENTIFIER("proced"));
  MatchSingleToken("procedu", IDENTIFIER("procedu"));
  MatchSingleToken("procedur", IDENTIFIER("procedur"));
  MatchSingleToken("procedure", PROCEDURE);
  MatchSingleToken("procedures", IDENTIFIER("procedures"));

  MatchSingleToken("i", IDENTIFIER("i"));
  MatchSingleToken("in", IDENTIFIER("in"));
  MatchSingleToken("int", INT);
  MatchSingleToken("ints", IDENTIFIER("ints"));

  MatchSingleToken("b", IDENTIFIER("b"));
  MatchSingleToken("bo", IDENTIFIER("bo"));
  MatchSingleToken("boo", IDENTIFIER("boo"));
  MatchSingleToken("bool", BOOL);
  MatchSingleToken("boolean", IDENTIFIER("boolean"));

  MatchSingleToken("be", IDENTIFIER("be"));
  MatchSingleToken("beg", IDENTIFIER("beg"));
  MatchSingleToken("begi", IDENTIFIER("begi"));
  MatchSingleToken("begin", BEGIN);
  MatchSingleToken("beginning", IDENTIFIER("beginning"));

  MatchSingleToken("e", IDENTIFIER("e"));
  MatchSingleToken("en", IDENTIFIER("en"));
  MatchSingleToken("end", END);
  MatchSingleToken("end123", IDENTIFIER("end123"));

  MatchSingleToken("if", IF);
  MatchSingleToken("iffy", IDENTIFIER("iffy"));

  MatchSingleToken("t", IDENTIFIER("t"));
  MatchSingleToken("th", IDENTIFIER("th"));
  MatchSingleToken("the", IDENTIFIER("the"));
  MatchSingleToken("then", THEN);
  MatchSingleToken("thenprogram", IDENTIFIER("thenprogram"));

  MatchSingleToken("e", IDENTIFIER("e"));
  MatchSingleToken("el", IDENTIFIER("el"));
  MatchSingleToken("els", IDENTIFIER("els"));
  MatchSingleToken("else", ELSE);
  MatchSingleToken("elseif", IDENTIFIER("elseif"));

  MatchSingleToken("w", IDENTIFIER("w"));
  MatchSingleToken("wh", IDENTIFIER("wh"));
  MatchSingleToken("whi", IDENTIFIER("whi"));
  MatchSingleToken("whil", IDENTIFIER("whil"));
  MatchSingleToken("while", WHILE);
  MatchSingleToken("whilelse", IDENTIFIER("whilelse"));

  MatchSingleToken("l", IDENTIFIER("l"));
  MatchSingleToken("lo", IDENTIFIER("lo"));
  MatchSingleToken("loo", IDENTIFIER("loo"));
  MatchSingleToken("loop", LOOP);
  MatchSingleToken("looprint", IDENTIFIER("looprint"));

  MatchSingleToken("pri", IDENTIFIER("pri"));
  MatchSingleToken("prin", IDENTIFIER("prin"));
  MatchSingleToken("print", PRINT);
  MatchSingleToken("printend", IDENTIFIER("printend"));

  MatchSingleToken("n", IDENTIFIER("n"));
  MatchSingleToken("no", IDENTIFIER("no"));
  MatchSingleToken("not", NOT);
  MatchSingleToken("not123", IDENTIFIER("not123"));

  MatchSingleToken("o", IDENTIFIER("o"));
  MatchSingleToken("or", OR);
  MatchSingleToken("orr", IDENTIFIER("orr"));

  MatchSingleToken("a", IDENTIFIER("a"));
  MatchSingleToken("an", IDENTIFIER("an"));
  MatchSingleToken("and", AND);
  MatchSingleToken("andd", IDENTIFIER("andd"));

  MatchSingleToken(";", SEMICOLON);
  MatchSingleToken(":", COLON);
  MatchSingleToken(",", COMMA);
  MatchSingleToken(":=", ASSIGNMENT);
  MatchSingleToken("(", OPENBRACKET);
  MatchSingleToken(")", CLOSEBRACKET);

  MatchSingleToken("=", EQUAL);
  MatchSingleToken("<>", NOTEQUAL);
  MatchSingleToken(">", GREATERTHAN);
  MatchSingleToken(">=", GREATEROREQUAL);
  MatchSingleToken("<", LESSTHAN);
  MatchSingleToken("<=", LESSOREQUAL);

  MatchSingleToken("+", ADD);
  MatchSingleToken("-", SUBTRACT);

  MatchSingleToken("*", MULTIPLY);
  MatchSingleToken("/", DIVIDE);

  MatchSingleToken("foobarquoz", IDENTIFIER("foobarquoz"));
  MatchSingleToken("a", IDENTIFIER("a"));
  MatchSingleToken("z", IDENTIFIER("z"));
  MatchSingleToken("ints", IDENTIFIER("ints"));
  MatchSingleToken("loo", IDENTIFIER("loo"));
  MatchSingleToken("elseif", IDENTIFIER("elseif"));
  MatchSingleToken("myprocedure", IDENTIFIER("myprocedure"));
  MatchSingleToken("andnota23", IDENTIFIER("andnota23"));
  MatchSingleToken("a1b2c3d4e5f6g7h8i9", IDENTIFIER("a1b2c3d4e5f6g7h8i9"));
  MatchSingleToken("a123456789", IDENTIFIER("a123456789"));

  MatchSingleToken("1", NUMBER("1"));
  MatchSingleToken("9999999999999", NUMBER("9999999999999"));
  MatchSingleToken("000000000000", NUMBER("000000000000"));
  MatchSingleToken("123456789", NUMBER("123456789"));

  MatchSingleToken("", ENDOFFILE);
}

TEST(ScannerTest, MultipleNextTokens) {
  MatchTokens("int a = 1;", { new INT, new IDENTIFIER("a"), new EQUAL,
          new NUMBER("1"), new SEMICOLON, new ENDOFFILE });
  MatchTokens("int a = 1 + 1 + 1;", { new INT, new IDENTIFIER("a"),
          new EQUAL, new NUMBER("1"), new ADD, new NUMBER("1"), new ADD,
          new NUMBER("1"), new SEMICOLON, new ENDOFFILE });
  MatchTokens("while else int", { new WHILE, new ELSE, new INT,
          new ENDOFFILE });
  MatchTokens("foo bar baz", { new IDENTIFIER("foo"),
          new IDENTIFIER("bar"), new IDENTIFIER("baz"), new ENDOFFILE });
  MatchTokens("and nota2", { new AND, new IDENTIFIER("nota2"), new ENDOFFILE});
  MatchTokens("and not a23", { new AND, new NOT, new IDENTIFIER("a23"),
          new ENDOFFILE });
  MatchTokens("123abc", { new NUMBER("123"), new IDENTIFIER("abc"),
          new ENDOFFILE });
  MatchTokens("integer >= 2", { new IDENTIFIER("integer"), new GREATEROREQUAL,
          new NUMBER("2"), new ENDOFFILE });
  MatchTokens("integer > = 2", { new IDENTIFIER("integer"), new GREATERTHAN,
          new EQUAL, new NUMBER("2"), new ENDOFFILE });
  MatchTokens("if(a+1)*2=2then", { new IF, new OPENBRACKET, new IDENTIFIER("a"),
          new ADD, new NUMBER("1"), new CLOSEBRACKET, new MULTIPLY,
          new NUMBER("2"), new EQUAL, new NUMBER("2"), new THEN,
          new ENDOFFILE });
  MatchTokens("a1+b2<>c3", { new IDENTIFIER("a1"), new ADD,
          new IDENTIFIER("b2"), new NOTEQUAL, new IDENTIFIER("c3"),
          new ENDOFFILE });
}

TEST(ScannerTest, StressTest) {
  std::string input;
  std::vector<Token*> expected;
  for (int i = 0; i < 20000; ++i) {
    input.append("foo = 1 and bar <> 2");
    expected.push_back(new IDENTIFIER("foo"));
    expected.push_back(new EQUAL);
    expected.push_back(new NUMBER("1"));
    expected.push_back(new AND);
    expected.push_back(new IDENTIFIER("bar"));
    expected.push_back(new NOTEQUAL);
    expected.push_back(new NUMBER("2"));
  }
  expected.push_back(new ENDOFFILE);
  MatchTokens(input, expected);
}

TEST(ScannerDeathTest, ScanIllegalCharacter) {
  {
    Scanner scanner(CreateBuffer("%"));
    ASSERT_EXIT(scanner.NextToken(),
                ::testing::ExitedWithCode(EXIT_FAILURE),
                "c*Illegal character: \\%c*");
  }
  {
    Scanner scanner(CreateBuffer("abcdH"));
    scanner.NextToken();
    ASSERT_EXIT(scanner.NextToken(),
                ::testing::ExitedWithCode(EXIT_FAILURE),
                "c*Illegal character: H*");
  }
  {
    Scanner scanner(CreateBuffer("abcd H"));
    scanner.NextToken();
    ASSERT_EXIT(scanner.NextToken(),
                ::testing::ExitedWithCode(EXIT_FAILURE),
                "c*Illegal character: H*");
  }
}

}  // namespace
}  // namespace truplc
