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
  StreamBuffer buffer(&ss);
  for (const char c : expected) {
    EXPECT_EQ(buffer.NextChar(), c);
  }
}

TEST(StreamBufferTest, NextCharBasic) {
  TestNextChar("bool", {'b', 'o', 'o', 'l', kEOFMarker});
  TestNextChar("int a;", {'i', 'n', 't', kSpace, 'a', ';', kEOFMarker});
  TestNextChar("a = 3;", {'a', kSpace, '=', kSpace, '3', ';', kEOFMarker});
  TestNextChar("if(a )", {'i', 'f', '(', 'a', kSpace, ')', kEOFMarker});
  TestNextChar(";:(),=<>+-",
               {';', ':', '(', ')', ',', '=', '<', '>', '+', '-', kEOFMarker});
  TestNextChar("", {kEOFMarker});
  TestNextChar("a", {'a', kEOFMarker, kEOFMarker, kEOFMarker});
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
  TestNextChar("abc #!@#$%^&*\n", {'a', 'b', 'c', kSpace, kEOFMarker});
  TestNextChar("a#$$$\nb", {'a', kSpace, 'b', kEOFMarker});
  TestNextChar("#$$$", {kEOFMarker});
}


TEST(StreamBufferTest, NextCharWithMixingWhitespaceAndComments) {
  TestNextChar("a #foo bar\n b", {'a', kSpace, 'b', kEOFMarker});
  TestNextChar("#foo bar\n\n\t  a b", {'a', kSpace, 'b', kEOFMarker});
  TestNextChar(" a #foo bar \n \t   b #foo\n\t c#foo bar",
               {'a', kSpace, 'b', kSpace, 'c', kSpace, kEOFMarker});
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
  StreamBuffer buffer(&ss);
  char result = buffer.NextChar();
  EXPECT_EQ(result, 'a');
  EXPECT_EQ(buffer.NextChar(), kEOFMarker);
  buffer.UnreadChar(result);
  EXPECT_EQ(buffer.NextChar(), result);
}

TEST(StreamBufferDeathTest, NextCharIllegalInput) {
  {
    std::istringstream ss("FOO");
    StreamBuffer buffer(&ss);
    ASSERT_EXIT(buffer.NextChar(),
                 ::testing::ExitedWithCode(EXIT_FAILURE),
                 "c*Invalid character: Fc*");
  }
  {
    std::istringstream ss("%^&");
    StreamBuffer buffer(&ss);
    ASSERT_EXIT(buffer.NextChar(),
                ::testing::ExitedWithCode(EXIT_FAILURE),
                "c*Invalid character: %c*");
  }
  {
    std::istringstream ss("$");
    StreamBuffer buffer(&ss);
    ASSERT_EXIT(buffer.NextChar(),
                ::testing::ExitedWithCode(EXIT_FAILURE),
                "c*Invalid character: \\$c*");
  }
}

TEST(StreamBufferDeathTest, UnreadIllegalChar) {
  std::istringstream ss("");
  StreamBuffer buffer(&ss);
  EXPECT_EQ(buffer.NextChar(), kEOFMarker);
  buffer.UnreadChar('a');
  EXPECT_EQ(buffer.NextChar(), 'a');
  buffer.UnreadChar('$');
  ASSERT_EXIT(buffer.NextChar(),
              ::testing::ExitedWithCode(EXIT_FAILURE),
              "c*Invalid character: \\$c*");
}

}  // namespace
}  // namespace truplc
