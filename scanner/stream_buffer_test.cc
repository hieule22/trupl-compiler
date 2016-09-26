// Unit tests for InputBuffer class.
// Copyright 2016 Hieu Le.

#include "scanner/stream_buffer.h"

#include <sstream>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace truplc {
namespace {

// Test if StreamBuffer generates on specified input an expected sequence of
// characters.
void TestNextChar(const std::string& input,
                  const std::vector<char>& expected) {
  std::istringstream ss(input);
  std::unique_ptr<Buffer> buffer = std::make_unique<StreamBuffer>(&ss);
  for (const char c : expected) {
    EXPECT_EQ(buffer->NextChar(), c);
  }
}

TEST(StreamBufferTest, NextCharBasic) {
  TestNextChar("bool", {'b', 'o', 'o', 'l', kEOFMarker});
  TestNextChar("int a;", {'i', 'n', 't', kSpace, 'a', ';', kEOFMarker});
  TestNextChar("a = 3;", {'a', kSpace, '=', kSpace, '3', ';', kEOFMarker});
  TestNextChar("if(a )", {'i', 'f', '(', 'a', kSpace, ')', kEOFMarker});
  TestNextChar(";:(),=<>+-",
               {';', ':', '(', ')', ',', '=', '<', '>', '+', '-', kEOFMarker});
}

TEST(StreamBufferTest, NextCharWithWhitespace) {
  TestNextChar("a b", {'a', kSpace, 'b', kEOFMarker});
  TestNextChar("a\n\nb", {'a', kSpace, 'b', kEOFMarker});
  TestNextChar("\n\n\t a", {'a', kEOFMarker});
  TestNextChar("a \n\t ", {'a', kSpace, kEOFMarker});
  TestNextChar("  \n\n\t\t  ", {kEOFMarker});
}

TEST(StreamBufferTest, NextCharWithComments) {
  TestNextChar("f#abc def ghi\nb", {'f', kSpace, 'b', kEOFMarker});
  TestNextChar("a#foo quoz bar \n#bar\nb", {'a', kSpace, 'b', kEOFMarker});
  TestNextChar("#this #is #comment\na#abcxyz", {'a', kSpace, kEOFMarker});
  TestNextChar("a#this\t\tis a\t\tcomment\nb", {'a', kSpace, 'b', kEOFMarker});
  TestNextChar("#this is a comment\na", {'a', kEOFMarker});
  TestNextChar("a#this is a comment", {'a', kSpace, kEOFMarker});
  TestNextChar("#this is a comment", {kEOFMarker});
}


TEST(StreamBufferTest, NextCharWithMixingWhitespaceAndComments) {
  TestNextChar("a #foo bar\n b", {'a', kSpace, 'b', kEOFMarker});
  TestNextChar("#foo bar\n\n\t  a b", {'a', kSpace, 'b', kEOFMarker});
  TestNextChar(" a #foo bar \n \t   b #foo\n\t c#foo bar",
               {'a', kSpace, 'b', kSpace, 'c', kSpace, kEOFMarker});
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

TEST(StreamBufferTest, UnreadCharBasic) {
  std::istringstream ss("a");
  std::unique_ptr<Buffer> buffer = std::make_unique<StreamBuffer>(&ss);
  char result = buffer->NextChar();
  EXPECT_EQ(result, 'a');
  EXPECT_EQ(buffer->NextChar(), kEOFMarker);
  buffer->UnreadChar(result);
  EXPECT_EQ(buffer->NextChar(), result);
}

}  // namespace
}  // namespace truplc
