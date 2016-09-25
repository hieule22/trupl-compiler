// Unit tests for InputBuffer class.
// Copyright 2016 Hieu Le.

#include "scanner/input_buffer.h"

#include <sstream>
#include <utility>

#include "gtest/gtest.h"

namespace truplc {
namespace {

std::unique_ptr<std::istream> CreateStream(const std::string& s) {
  return std::make_unique<std::istringstream>(s);
}

TEST(InputBufferTest, NextCharBasic) {
  const std::string input = "Foo$";
  InputBuffer scanner(CreateStream(input));
  for (char c : input) {
    EXPECT_EQ(scanner.NextChar(), c);
  }
}

TEST(InputBufferTest, NextCharWithWhitespace) {
  const std::string input = "Foo Bar$";
  InputBuffer scanner(CreateStream(input));
  for (char c : input) {
    EXPECT_EQ(scanner.NextChar(), c);
  }
}

TEST(InputBufferTest, NextCharWithMultipleWhitespaces) {
  {
    InputBuffer scanner(CreateStream("F  $"));
    EXPECT_EQ(scanner.NextChar(), 'F');
    EXPECT_EQ(scanner.NextChar(), kSpace);
  }
  {
    InputBuffer scanner(CreateStream("F\n\t $"));
    EXPECT_EQ(scanner.NextChar(), 'F');
    EXPECT_EQ(scanner.NextChar(), kSpace);
  }
}

TEST(InputBufferTest, NextCharWithPrecedingWhitespaces) {
  InputBuffer scanner(CreateStream("\n\n\t H$"));
  EXPECT_EQ(scanner.NextChar(), 'H');
}

TEST(InputBufferTest, NextCharWithComment) {
  InputBuffer scanner(CreateStream("F#abc bar quoz \nB$"));
  EXPECT_EQ(scanner.NextChar(), 'F');
  EXPECT_EQ(scanner.NextChar(), kSpace);
  EXPECT_EQ(scanner.NextChar(), 'B');
}

TEST(InputBufferTest, NextCharWithMultilineComment) {
  InputBuffer scanner(CreateStream("A#foo quoz bar \n#bar\nB"));
  EXPECT_EQ(scanner.NextChar(), 'A');
  EXPECT_EQ(scanner.NextChar(), kSpace);
  EXPECT_EQ(scanner.NextChar(), 'B');
}

TEST(InputBufferTest, NextCharWithPrecedingComment) {
  InputBuffer scanner(CreateStream("#This is a comment\n  A$"));
  EXPECT_EQ(scanner.NextChar(), 'A');
}

TEST(InputBufferTest, NextCharWithMixingWhitespaceAndComment) {
  InputBuffer scanner(CreateStream("A #foo bar\n B"));
  EXPECT_EQ(scanner.NextChar(), 'A');
  EXPECT_EQ(scanner.NextChar(), kSpace);
  EXPECT_EQ(scanner.NextChar(), 'B');
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
}

}  // namespace
}  // namespace truplc
