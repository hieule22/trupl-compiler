// End to end tests for TruPL lexical analyzer.
// Copyright 2016 Hieu Le.

#include <sstream>
#include <utility>
#include <vector>

#include "scanner/scanner.h"
#include "scanner/stream_buffer.h"
#include "scanner/test_utils.h"

#include "gtest/gtest.h"

namespace truplc {
namespace {

class LexicalAnalyzerTest : public testing::Test {
 protected:
  // Creates a character from given input string.
  std::unique_ptr<Buffer> CreateBuffer(const std::string& input) {
    ss = std::make_unique<std::istringstream>(input);
    return std::make_unique<StreamBuffer>(ss.get());
  }

  // Tests if the tokens from an input stream as read by the scanner
  // matches a list of expected tokens.
  void MatchTokens(const std::string& input, const std::vector<Token*>& token) {
    Scanner scanner(CreateBuffer(input));
    for (const auto& expected : token) {
      std::unique_ptr<Token> actual(scanner.NextToken());
      EXPECT_EQ(actual->DebugString(), expected->DebugString());
    }
  }

 private:
  std::unique_ptr<std::istringstream> ss;
};

// TODO(hieule22): Fix memory leaks.
TEST_F(LexicalAnalyzerTest, Basic) {
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

TEST_F(LexicalAnalyzerTest, CommentAndWhitespace) {
  MatchTokens("foo #abc def ghi\nbar", { new IDENTIFIER("foo"),
          new IDENTIFIER("bar"), new ENDOFFILE });

  MatchTokens(
      "#Hello world\n \
       program \
        i := 10; \
       end",
      { new PROGRAM, new IDENTIFIER("i"), new ASSIGNMENT, new NUMBER("10"),
            new SEMICOLON, new END, new ENDOFFILE });

  MatchTokens(
      "#$%^*())##\t\t\t\n \
       \t\t\n\n\n \
       if a = b then #This is a comment\n \
       \t\t print 1;\n ################\n \
       else \
       print 0;",
      { new IF, new IDENTIFIER("a"), new EQUAL, new IDENTIFIER("b"),
            new THEN, new PRINT, new NUMBER("1"), new SEMICOLON, new ELSE,
            new PRINT, new NUMBER("0"), new SEMICOLON });
}

}  // namespace
}  // namespace truplc
