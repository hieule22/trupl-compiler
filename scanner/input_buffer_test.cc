// Unit tests for InputBuffer class.
// Copyright 2016 Hieu Le.

#include "scanner/input_buffer.h"

#include <sstream>
#include <utility>

#include "gtest/gtest.h"

namespace truplc {
namespace {

TEST(InputBufferTest, NextCharBasic) {
  const std::string input = "FOO";
  std::istringstream ss(input);
  InputBuffer scanner(&ss);
  for (char c : input) {
    EXPECT_EQ(scanner.NextChar(), c);
  }
  EXPECT_EQ(scanner.NextChar(), kEOFMarker);
}

TEST(InputBufferTest, NextCharWithWhitespace) {
  const std::string input = "FOO BAR";
  std::istringstream ss(input);
  InputBuffer scanner(&ss);
  for (char c : input) {
    EXPECT_EQ(scanner.NextChar(), c);
  }
  EXPECT_EQ(scanner.NextChar(), kEOFMarker);
}

TEST(InputBufferTest, NextCharWithMultipleWhitespaces) {
  std::istringstream ss("A\n\tB");
  InputBuffer scanner(&ss);
  EXPECT_EQ(scanner.NextChar(), 'A');
  EXPECT_EQ(scanner.NextChar(), kSpace);
  EXPECT_EQ(scanner.NextChar(), 'B');
  EXPECT_EQ(scanner.NextChar(), kEOFMarker);
}

TEST(InputBufferTest, NextCharWithPrecedingWhitespaces) {
  std::istringstream ss("\n\n\t A");
  InputBuffer scanner(&ss);
  EXPECT_EQ(scanner.NextChar(), 'A');
  EXPECT_EQ(scanner.NextChar(), kEOFMarker);
}

TEST(InputBufferTest, NextCharWithTrailingWhitespaces) {
  std::istringstream ss("A \n\t ");
  InputBuffer scanner(&ss);
  EXPECT_EQ(scanner.NextChar(), 'A');
  EXPECT_EQ(scanner.NextChar(), kEOFMarker);
}

TEST(InputBufferTest, NextCharWithOnlyWhitespaces) {
  std::istringstream ss("  \n\n\t\t  ");
  InputBuffer scanner(&ss);
  EXPECT_EQ(scanner.NextChar(), kEOFMarker);
}

TEST(InputBufferTest, NextCharWithComments) {
  std::istringstream ss("F#ABC DEF GHI\nB");
  InputBuffer scanner(&ss);
  EXPECT_EQ(scanner.NextChar(), 'F');
  EXPECT_EQ(scanner.NextChar(), kSpace);
  EXPECT_EQ(scanner.NextChar(), 'B');
  EXPECT_EQ(scanner.NextChar(), kEOFMarker);
}

TEST(InputBufferTest, NextCharWithMultilineComments) {
  std::istringstream ss("A#FOO QUOZ BAR \n#BAR\nB");
  InputBuffer scanner(&ss);
  EXPECT_EQ(scanner.NextChar(), 'A');
  EXPECT_EQ(scanner.NextChar(), kSpace);
  EXPECT_EQ(scanner.NextChar(), 'B');
  EXPECT_EQ(scanner.NextChar(), kEOFMarker);
}

TEST(InputBufferTest, NextCharWithPrecedingComments) {
  std::istringstream ss("#THIS IS A COMMENT.\n  A");
  InputBuffer scanner(&ss);
  EXPECT_EQ(scanner.NextChar(), 'A');
  EXPECT_EQ(scanner.NextChar(), kEOFMarker);
}

TEST(InputBufferTest, NextCharWithTrailingComments) {
  std::istringstream ss("A#THIS IS A COMMENT.");
  InputBuffer scanner(&ss);
  EXPECT_EQ(scanner.NextChar(), 'A');
  EXPECT_EQ(scanner.NextChar(), kEOFMarker);
}

TEST(InputBufferTEST, NextCharWithOnlyComments) {
  std::istringstream ss("#THIS IS A COMMENT.");
  InputBuffer scanner(&ss);
  EXPECT_EQ(scanner.NextChar(), kEOFMarker);
}

TEST(InputBufferTest, NextCharWithMixingWhitespaceAndComments) {
  std::istringstream ss("A #FOO BAR\n B");
  InputBuffer scanner(&ss);
  EXPECT_EQ(scanner.NextChar(), 'A');
  EXPECT_EQ(scanner.NextChar(), kSpace);
  EXPECT_EQ(scanner.NextChar(), 'B');
  EXPECT_EQ(scanner.NextChar(), kEOFMarker);
}

TEST(InputBufferTest, NextCharWithEmptyInput) {
  std::istringstream ss("");
  InputBuffer scanner(&ss);
  EXPECT_EQ(scanner.NextChar(), kEOFMarker);
}

TEST(InputBufferTest, NextCharAfterEndOfFile) {
  std::istringstream ss("A");
  InputBuffer scanner(&ss);
  EXPECT_EQ(scanner.NextChar(), 'A');
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(scanner.NextChar(), kEOFMarker);
  }
}

TEST(InputBufferTest, NextCharWithLongInputStream) {
  std::stringstream ss;
  for (int i = 0; i < 20000; ++i) {
    ss << 'a';
  }
  InputBuffer scanner(&ss);
  for (int i = 0; i < 20000; ++i) {
    EXPECT_EQ(scanner.NextChar(), 'a');
  }
  EXPECT_EQ(scanner.NextChar(), kEOFMarker);
}

}  // namespace
}  // namespace truplc
