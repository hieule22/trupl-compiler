// Unit tests for PunctuationToken class.
// Copyright 2016 Hieu Le.

#include "scanner/punctuation_token.h"

#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace truplc {
namespace {

TEST(PunctuationToken, GetTokenType) {
  const PunctuationToken token(PunctuationAttribute::kSemicolon);
  EXPECT_EQ(token.GetTokenType(), TokenType::kPunctuation);
}

TEST(PunctuationToken, GetAttribute) {
  const PunctuationToken default_token;
  EXPECT_EQ(default_token.GetAttribute(), PunctuationAttribute::kUnspecified);

  const PunctuationAttribute attribute = PunctuationAttribute::kComma;
  const PunctuationToken specified_token(attribute);
  EXPECT_EQ(specified_token.GetAttribute(), attribute);
}

TEST(PunctuationToken, DebugString) {
  const std::string prefix = "kPunctuation:";
  const std::vector<std::pair<PunctuationAttribute, std::string>> attributes =
      {{PunctuationAttribute::kSemicolon,    prefix + "kSemicolon"},
       {PunctuationAttribute::kColon,        prefix + "kColon"},
       {PunctuationAttribute::kComma,        prefix + "kComma"},
       {PunctuationAttribute::kAssignment,   prefix + "kAssignment"},
       {PunctuationAttribute::kOpenBracket,  prefix + "kOpenBracket"},
       {PunctuationAttribute::kCloseBracket, prefix + "kCloseBracket"},
       {PunctuationAttribute::kUnspecified,  prefix + "kUnspecified"}
      };

  for (const auto& attribute : attributes) {
    PunctuationToken token(attribute.first);
    EXPECT_EQ(token.DebugString(), attribute.second);
  }
}

}  // namespace
}  // namespace truplc
