// Unit tests for InputBuffer class.
// Copyright 2016 Hieu Le.

#include "scanner/input_buffer.h"

#include <sstream>
#include <utility>

#include "gtest/gtest.h"

namespace truplc {
namespace {

// Returns a mock input stream constructed from given string.
std::unique_ptr<std::istream> CreateStream(const std::string& s) {
  return std::make_unique<std::istringstream>(s);
}

TEST(InputBufferTest, NextCharBasic) {
  const std::string input = "FOO";
  InputBuffer scanner(CreateStream(input));
  for (char c : input) {
    EXPECT_EQ(scanner.NextChar(), c);
  }
  EXPECT_EQ(scanner.NextChar(), kEOFMarker);
}

TEST(InputBufferTest, NextCharWithWhitespace) {
  const std::string input = "FOO BAR";
  InputBuffer scanner(CreateStream(input));
  for (char c : input) {
    EXPECT_EQ(scanner.NextChar(), c);
  }
  EXPECT_EQ(scanner.NextChar(), kEOFMarker);
}

TEST(InputBufferTest, NextCharWithMultipleWhitespaces) {
  InputBuffer scanner(CreateStream("A  B"));
  EXPECT_EQ(scanner.NextChar(), 'A');
  EXPECT_EQ(scanner.NextChar(), kSpace);
  EXPECT_EQ(scanner.NextChar(), 'B');
  EXPECT_EQ(scanner.NextChar(), kEOFMarker);
}

TEST(InputBufferTest, NextCharWithPrecedingWhitespaces) {
  InputBuffer scanner(CreateStream("\n\n\t A"));
  EXPECT_EQ(scanner.NextChar(), 'A');
  EXPECT_EQ(scanner.NextChar(), kEOFMarker);
}

TEST(InputBufferTest, NextCharWithTrailingWhitespaces) {
  InputBuffer scanner(CreateStream("A \n\t "));
  EXPECT_EQ(scanner.NextChar(), 'A');
  EXPECT_EQ(scanner.NextChar(), kEOFMarker);
}

TEST(InputBufferTest, NextCharWithOnlyWhitespaces) {
  InputBuffer scanner(CreateStream("  \n\n\t\t  "));
  EXPECT_EQ(scanner.NextChar(), kEOFMarker);
}

TEST(InputBufferTest, NextCharWithComments) {
  InputBuffer scanner(CreateStream("F#ABC DEF GHI\nB"));
  EXPECT_EQ(scanner.NextChar(), 'F');
  EXPECT_EQ(scanner.NextChar(), kSpace);
  EXPECT_EQ(scanner.NextChar(), 'B');
  EXPECT_EQ(scanner.NextChar(), kEOFMarker);
}

TEST(InputBufferTest, NextCharWithMultilineComments) {
  InputBuffer scanner(CreateStream("A#FOO QUOZ BAR \n#BAR\nB"));
  EXPECT_EQ(scanner.NextChar(), 'A');
  EXPECT_EQ(scanner.NextChar(), kSpace);
  EXPECT_EQ(scanner.NextChar(), 'B');
  EXPECT_EQ(scanner.NextChar(), kEOFMarker);
}

TEST(InputBufferTest, NextCharWithPrecedingComments) {
  InputBuffer scanner(CreateStream("#THIS IS A COMMENT.\n  A"));
  EXPECT_EQ(scanner.NextChar(), 'A');
  EXPECT_EQ(scanner.NextChar(), kEOFMarker);
}

TEST(InputBufferTest, NextCharWithTrailingComments) {
  InputBuffer scanner(CreateStream("A#THIS IS A COMMENT."));
  EXPECT_EQ(scanner.NextChar(), 'A');
  EXPECT_EQ(scanner.NextChar(), kEOFMarker);
}

TEST(InputBufferTEST, NextCharWithOnlyComments) {
  InputBuffer scanner(CreateStream("#THIS IS A COMMENT."));
  EXPECT_EQ(scanner.NextChar(), kEOFMarker);
}

TEST(InputBufferTest, NextCharWithMixingWhitespaceAndComments) {
  InputBuffer scanner(CreateStream("A #FOO BAR\n B"));
  EXPECT_EQ(scanner.NextChar(), 'A');
  EXPECT_EQ(scanner.NextChar(), kSpace);
  EXPECT_EQ(scanner.NextChar(), 'B');
  EXPECT_EQ(scanner.NextChar(), kEOFMarker);
}

TEST(InputBufferTest, NextCharWithEmptyInput) {
  InputBuffer scanner(CreateStream(""));
  EXPECT_EQ(scanner.NextChar(), kEOFMarker);
}

TEST(InputBufferTest, NextCharAfterEndOfFile) {
  InputBuffer scanner(CreateStream("A"));
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
  InputBuffer scanner(std::make_unique<std::stringstream>(std::move(ss)));
  for (int i = 0; i < 20000; ++i) {
    EXPECT_EQ(scanner.NextChar(), 'a');
  }
  EXPECT_EQ(scanner.NextChar(), kEOFMarker);
}

}  // namespace
}  // namespace truplc
