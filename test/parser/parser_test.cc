// Unit tests for Parser class.
// Copyright 2016 Hieu Le.

#include "parser/parser.h"

#include <sstream>
#include <utility>

#include "gtest/gtest.h"
#include "scanner/buffer.h"
#include "scanner/stream_buffer.h"

namespace truplc {
namespace {

class ParserTest : public testing::Test {
 protected:
  // Creates a Parser for a program represented by an input string.
  Parser CreateParser(const std::string& input) {
    stream_ = std::make_unique<std::istringstream>(input);
    auto buffer = std::make_unique<StreamBuffer>(stream_.get());
    auto scanner = std::make_unique<Scanner>(std::move(buffer));
    return Parser(std::move(scanner));
  }

 private:
  std::unique_ptr<std::istringstream> stream_;
};

TEST_F(ParserTest, ParseValidProgram) {
  EXPECT_TRUE(CreateParser(
      "program foo0; "
      "begin "
        "print 10; "
      "end;").ParseProgram());

  EXPECT_TRUE(CreateParser(
      "program foo1; "
        "i: int; "
      "begin "
        "print i; "
      "end;").ParseProgram());

  EXPECT_TRUE(CreateParser(
      "program foo2; "
        "procedure add(a: int; b: int) "
        "begin "
          "print(a + b); "
        "end; "
      "begin "
        "add(1, 2); "
      "end;").ParseProgram());

  EXPECT_TRUE(CreateParser(
      "program foo3; "
        "a, b: int; "
      "begin "
        "a := 1; "
        "b := a + 1; "
        "print(a + b); "
      "end;").ParseProgram());

  EXPECT_TRUE(CreateParser(
      "program foo; "
        "a, b, c, d: int; "
      "begin "
        "print(a + b + c + d); "
      "end;").ParseProgram());

  EXPECT_TRUE(CreateParser(
      "program foo; "
        "a, b, c, d: int; "
      "begin "
        "a := (-a + (b * c) - (a / -b)) + (((a - b))) + (-10 / (c * (d + 1))); "
      "end;").ParseProgram());

  EXPECT_TRUE(CreateParser(
      "program foo; "
        "a, b, c, d: bool; "
      "begin "
        "a := (b and not c) or (not d and not a) and ((10 = 12) and "
              "(not(not c))); "
      "end;").ParseProgram());

  EXPECT_TRUE(CreateParser(
      "program foo; "
        "a, b: int; "
        "m, n: bool; "
      "begin "
        "a := b; "
        "m := n; "
      "end;").ParseProgram());

  EXPECT_TRUE(CreateParser(
      "program foo; "
        "a, b: int; "
        "c: bool; "
      "begin "
        "c := (a = b) or (a <= b); "
        "c := (a > b) and not (a < b); "
      "end;").ParseProgram());

  EXPECT_TRUE(CreateParser(
      "program foo4; "
        "a, b: int; "

        "procedure max(a, b: int) "
        "begin "
          "if (a > b) then begin "
            "print a; "
          "end "
          "else begin "
            "print b; "
          "end; "
        "end; "

      "begin "
        "a := 1; "
        "b := 2; "
        "max(a, b); "
      "end; ").ParseProgram());

  EXPECT_TRUE(CreateParser(
      "program foo; "
        "procedure bar(a, b, c, d: int) "
        "begin "
          "print(a + b + c + d); "
        "end; "
      "begin "
        "bar(1, 2, 3, 4); "
      "end;").ParseProgram());

  EXPECT_TRUE(CreateParser(
      "program foo; "
        "procedure bar(a, b, c: int; d: int; m, n, p: int) "
        "begin "
          "print(a + b + c + d + m + n + p); "
        "end; "
      "begin "
        "bar(1, 2, 3, 4, 5, 6, 7); "
      "end;").ParseProgram());

  EXPECT_TRUE(CreateParser(
      "program foo; "
        "procedure bar(a, b: int; c, d: bool) "
        "begin print 1; end; "
      "begin "
        "bar(0, 1, 1 = 1, 2 = 2); "
      "end;").ParseProgram());

  EXPECT_TRUE(CreateParser(
      "program foo5; "
        "a, c: int; "

        "procedure increment(a: int) "
          "c: int; "
        "begin "
          "c := 1; "
          "a := a + c; "
          "print a; "
        "end; "

      "begin "
        "a := 0; "
        "increment(a); "
        "c := 1; "
        "increment(c); "
      "end; ").ParseProgram());

  EXPECT_TRUE(CreateParser(
      "program foo; "
        "procedure bar(a, b, c: int) "
          "m, n, p: int; "
        "begin "
          "print(a + b + c + m + n + p); "
        "end; "
      "begin "
        "bar(0, 0, 0); "
      "end;").ParseProgram());

  EXPECT_TRUE(CreateParser(
      "program foo6; "
        "a: bool; "
        "b: int; "
      "begin "
        "while (a) loop begin "
          "print a; "
        "end; "

        "while (b = 1) loop begin "
          "print b; "
        "end; "

        "if (not a) then begin "
          "print a; "
        "end; "

        "if (b < 1) then begin "
          "print b; "
        "end; "
      "end;").ParseProgram());

  EXPECT_TRUE(CreateParser(
      "program foo7; "
        "a: bool; "
        "b: int; "
      "begin "
        "while (a or (b > 1)) loop begin "
          "if not a then begin "
            "print(b > 1); "
          "end "
          "else begin "
            "if b = 0 then begin "
              "print a; "
            "end; "
          "end; "
        "end; "
      "end; ").ParseProgram());

  EXPECT_TRUE(CreateParser(
      "program foo8; "
        "a, b, c, d: int; "
        "m, n, p, q: bool; "

        "procedure bar() "
          "a, b, c, d: int; "
          "m, n, p, q: bool; "
        "begin "
          "print(a + b + c + d); "
          "print(m and n and not p or q); "
        "end; "

      "begin "
        "bar(); "
      "end; ").ParseProgram());

  EXPECT_TRUE(CreateParser(
      "program foo; "
        "procedure bar(foo: int) "
        "begin "
          "print foo; "
        "end; "
      "begin "
        "bar(10); "
      "end;").ParseProgram());

  EXPECT_TRUE(CreateParser(
      "program foo; "
        "procedure bar(quoz: int) "
        "begin "
          "print quoz; "
        "end; "

        "procedure quoz(bar: int) "
        "begin "
          "print bar; "
        "end;"
      "begin "
        "bar(0); quoz(1); "
      "end;").ParseProgram());

  EXPECT_TRUE(CreateParser(
      "program foo; "
        "procedure foo(bar: int) "
        "begin "
          "print bar; "
        "end; "
      "begin "
        "foo(10); "
      "end;").ParseProgram());

  EXPECT_TRUE(CreateParser(
      "program foo; "
        "procedure bar(foo: int) "
        "begin "
          "print foo; "
        "end; "
      "begin "
        "bar(10); "
      "end;").ParseProgram());

  EXPECT_TRUE(CreateParser(
      "program looper; "
        "a: int; "
        "b: bool; "
      "begin "
        "a := 0; "
        "b := 0 = 0; "
        "while b loop begin "
          "if a <= 2 then begin "
            "a := (a + 1) * 3; "
          "end "
          "else begin "
            "a := (a - 1) * 2; "
          "end; "
          "b := a > 1; "
          "print a; "
        "end; "
      "end;").ParseProgram());

  EXPECT_TRUE(CreateParser(
      "program minimal; "
      "begin "
        "; "
      "end;").ParseProgram());

  EXPECT_TRUE(CreateParser(
      "program redundant; "
      "begin "
        "print 10; "
      "end; foobarquoz").ParseProgram());
}

TEST_F(ParserTest, MultiplyDefinedIdentifierError) {
  ASSERT_EXIT(CreateParser(
      "program foo; "
        "a: int; "
        "a: bool; "
      "begin "
        "print(a); "
      "end;").ParseProgram(),
              ::testing::ExitedWithCode(EXIT_FAILURE),
              "The identifier a has already been declared.");

  ASSERT_EXIT(CreateParser(
      "program foo; "
        "a: int; "
        "procedure a() "
        "begin print 1; end; "
      "begin "
        "print(a); "
      "end;").ParseProgram(),
              ::testing::ExitedWithCode(EXIT_FAILURE),
              "The identifier a has already been declared.");

  ASSERT_EXIT(CreateParser(
      "program foo; "
        "procedure bar(a: int) "
          "a: int; "
        "begin print a; end; "
      "begin print 1; end;").ParseProgram(),
              ::testing::ExitedWithCode(EXIT_FAILURE),
              "The identifier a has already been declared.");

  ASSERT_EXIT(CreateParser(
      "program foo; "
        "procedure bar(a, b, c, d, e, a: int) "
        "begin print 0; end; "
      "begin print 0; end;").ParseProgram(),
              ::testing::ExitedWithCode(EXIT_FAILURE),
              "The identifier a has already been declared.");
}

TEST_F(ParserTest, UndeclaredIdentifierError) {
  ASSERT_EXIT(CreateParser(
      "program foo; "
      "begin "
        "print(a); "
      "end;").ParseProgram(),
              ::testing::ExitedWithCode(EXIT_FAILURE),
              "The identifier a has not been declared.");

  ASSERT_EXIT(CreateParser(
      "program foo; "
        "a: int; "
        "procedure bar() "
        "begin print(a); end; "
      "begin "
        "bar(); "
      "end;").ParseProgram(),
              ::testing::ExitedWithCode(EXIT_FAILURE),
              "The identifier a has not been declared.");

  ASSERT_EXIT(CreateParser(
      "program foo; "
        "procedure bar(a: int) begin print a; end; "
      "begin a := 10; end; ").ParseProgram(),
              ::testing::ExitedWithCode(EXIT_FAILURE),
              "The identifier a has not been declared.");

  ASSERT_EXIT(CreateParser(
      "program foo; "
        "procedure bar() "
          "a: int; "
        "begin print a; end; "
      "begin print a; end;").ParseProgram(),
              ::testing::ExitedWithCode(EXIT_FAILURE),
              "The identifier a has not been declared.");

  ASSERT_EXIT(CreateParser(
      "program foo; "
        "procedure bar(a: int) begin print a; end; "
        "procedure quoz() begin print a; end; "
      "begin bar(10); end;").ParseProgram(),
              ::testing::ExitedWithCode(EXIT_FAILURE),
              "The identifier a has not been declared.");

  ASSERT_EXIT(CreateParser(
      "program foo; "
        "procedure bar(a: int) begin print a; end; "
        "procedure quoz(a: int) begin bar(a); end; "
      "begin quoz(10); end;").ParseProgram(),
              ::testing::ExitedWithCode(EXIT_FAILURE),
              "The identifier bar has not been declared.");

  ASSERT_EXIT(CreateParser(
      "program norecursion; "
        "procedure foo(a: int) begin foo(10); end; "
      "begin foo(10); end;").ParseProgram(),
              ::testing::ExitedWithCode(EXIT_FAILURE),
              "The identifier foo has not been declared.");
}

TEST_F(ParserTest, TypeError) {
  ASSERT_EXIT(CreateParser(
      "program foo; "
        "a: int; b: bool; "
      "begin "
        "a := (a + 1) * (a - 1) + b; "
      "end;").ParseProgram(),
              ::testing::ExitedWithCode(EXIT_FAILURE),
              "Type error: expected INT_T found BOOL_T.");

  ASSERT_EXIT(CreateParser(
      "program foo; "
        "a: int; b: bool; "
      "begin "
        "b := not b and b or a; "
      "end;").ParseProgram(),
              ::testing::ExitedWithCode(EXIT_FAILURE),
              "Type error: expected BOOL_T found INT_T.");

  ASSERT_EXIT(CreateParser(
      "program foo; "
        "a: int; "
      "begin "
        "a := (a + 1) * (a - 10) and (a + 1); "
      "end;").ParseProgram(),
              ::testing::ExitedWithCode(EXIT_FAILURE),
              "Type error: expected BOOL_T found INT_T");

  ASSERT_EXIT(CreateParser(
      "program foo; "
      "begin "
        "if 1 then begin print(1); end; "
      "end;").ParseProgram(),
              ::testing::ExitedWithCode(EXIT_FAILURE),
              "Type error: expected BOOL_T found INT_T.");

  ASSERT_EXIT(CreateParser(
      "program foo; "
      "begin "
        "while 1 loop begin print(1); end; "
      "end;").ParseProgram(),
              ::testing::ExitedWithCode(EXIT_FAILURE),
              "Type error: expected BOOL_T found INT_T.");

  ASSERT_EXIT(CreateParser(
      "program foo; "
      "begin "
        "print((1 + (1 = 1))); end; "
      "end;").ParseProgram(),
              ::testing::ExitedWithCode(EXIT_FAILURE),
              "Type error: expected INT_T found BOOL_T.");

  ASSERT_EXIT(CreateParser(
      "program foo; "
      "begin "
        "print(((1 = 1) and 1)); end; "
      "end;").ParseProgram(),
              ::testing::ExitedWithCode(EXIT_FAILURE),
              "Type error: expected BOOL_T found INT_T.");

  ASSERT_EXIT(CreateParser(
      "program foo; "
      "begin "
        "print(1 and 2); "
      "end;").ParseProgram(),
              ::testing::ExitedWithCode(EXIT_FAILURE),
              "Type error: expected BOOL_T found INT_T.");

  ASSERT_EXIT(CreateParser(
      "program foo; "
      "begin "
        "if ((1 = 1) and 2) then begin "
          "print(1); "
        "end; "
      "end;").ParseProgram(),
              ::testing::ExitedWithCode(EXIT_FAILURE),
              "Type error: expected BOOL_T found INT_T.");

  ASSERT_EXIT(CreateParser(
      "program foo; "
        "a: int; "
        "b: bool; "
      "begin "
        "a := b; "
      "end;").ParseProgram(),
              ::testing::ExitedWithCode(EXIT_FAILURE),
              "Type error: expected INT_T found BOOL_T.");

  ASSERT_EXIT(CreateParser(
      "program foo; "
        "procedure increment(a: int) "
        "begin "
          "print(a + 1); "
        "end; "
      "begin "
        "increment(1 = 2); "
      "end;").ParseProgram(),
              ::testing::ExitedWithCode(EXIT_FAILURE),
              "Type error: expected INT_T found BOOL_T.");

  ASSERT_EXIT(CreateParser(
      "program foo; "
        "procedure add(a, b: int) "
        "begin print(a + b); end; "
      "begin add(1, 1 = 1); end; ").ParseProgram(),
              ::testing::ExitedWithCode(EXIT_FAILURE),
              "Type error: expected INT_T found BOOL_T.");

  ASSERT_EXIT(CreateParser(
      "program foo; "
        "procedure bar() "
        "begin "
          "print 1; "
        "end; "
      "begin "
        "print(bar); "
      "end;").ParseProgram(),
              ::testing::ExitedWithCode(EXIT_FAILURE),
              "Type error: expected INT_T or BOOL_T, found PROCEDURE_T.");

  ASSERT_EXIT(CreateParser(
      "program foo; "
        "procedure bar() "
        "begin print 1; end; "
      "begin bar := 1; end;").ParseProgram(),
              ::testing::ExitedWithCode(EXIT_FAILURE),
              "Type error: expected PROCEDURE_T found INT_T.");

  ASSERT_EXIT(CreateParser(
      "program foo; "
        "a: int; "
        "procedure bar() "
        "begin print 1; end; "
      "begin a := bar; end;").ParseProgram(),
              ::testing::ExitedWithCode(EXIT_FAILURE),
              "Type error: expected INT_T found PROCEDURE_T.");
}

}  // namespace
}  // namespace truplc
