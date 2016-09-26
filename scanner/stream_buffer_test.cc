// Unit tests for InputBuffer class.
// Copyright 2016 Hieu Le.

#include "scanner/stream_buffer.h"

#include <sstream>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace truplc {
namespace {

void TestNextChar(const std::string& input,
                 const std::vector<char> expected) {
  std::istringstream ss(input);
  std::unique_ptr<Buffer> buffer = std::make_unique<StreamBuffer>(&ss);
  for (const char c : expected) {
    EXPECT_EQ(buffer->NextChar(), c);
  }
}

TEST(StreamBufferTest, NextCharBasic) {
  TestNextChar("foo", {'f', 'o', 'o', kEOFMarker});
}

TEST(StreamBufferTest, NextCharWithWhitespace) {
  TestNextChar("a b", {'a', kSpace, 'b', kEOFMarker});
}

TEST(StreamBufferTest, NextCharWithMultipleWhitespaces) {
  TestNextChar("a\n\nb", {'a', kSpace, 'b', kEOFMarker});
}

TEST(StreamBufferTest, NextCharWithPrecedingWhitespaces) {
  TestNextChar("\n\n\t a", {'a', kEOFMarker});
}

TEST(StreamBufferTest, NextCharWithInterveningWhitespaces) {
  TestNextChar("a\n\nb", {'a', kSpace, 'b', kEOFMarker});
}

TEST(StreamBufferTest, NextCharWithTrailingWhitespaces) {
  TestNextChar("a \n\t ", {'a', kSpace, kEOFMarker});
}

TEST(StreamBufferTest, NextCharWithOnlyWhitespaces) {
  TestNextChar("  \n\n\t\t  ", {kEOFMarker});
}

TEST(StreamBufferTest, NextCharWithComments) {
  TestNextChar("f#abc def ghi\nb", {'f', kSpace, 'b', kEOFMarker});
}

TEST(StreamBufferTest, NextCharWithMultilineComments) {
  TestNextChar("a#foo quoz bar \n#bar\nb", {'a', kSpace, 'b', kEOFMarker});
}

TEST(StreamBufferTest, NextCharWithPrecedingComments) {
  TestNextChar("#this is a comment\na", {'a', kEOFMarker});
}

TEST(StreamBufferTest, NextCharWithTrailingComments) {
  TestNextChar("a#this is a comment", {'a', kSpace, kEOFMarker});
}

TEST(StreamBufferTEST, NextCharWithOnlyComments) {
  TestNextChar("#this is a comment", {kEOFMarker});
}

TEST(StreamBufferTest, NextCharWithMixingWhitespaceAndComments) {
  TestNextChar("a #foo bar\n b", {'a', kSpace, 'b', kEOFMarker});
}

TEST(StreamBufferTest, NextCharWithEmptyStream) {
  TestNextChar("", {kEOFMarker});
}

TEST(StreamBufferTest, NextCharAfterEndOfFile) {
  TestNextChar("a", {'a', kEOFMarker, kEOFMarker, kEOFMarker});
}

TEST(StreamBufferTest, NextCharWithLongInputStream) {
  std::string input;
  for (int i = 0; i < 20000; ++i) {
    input.push_back('a');
  }
  std::vector<char> expected(input.begin(), input.end());
  expected.push_back(kEOFMarker);
  TestNextChar(input, expected);
}

}  // namespace
}  // namespace truplc
