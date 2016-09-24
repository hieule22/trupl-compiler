// Test class for KeywordToken class.
// Copyright 2016 Hieu Le.

#include "scanner/keyword_token.h"

#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace truplc {
namespace {

TEST(KeywordToken, GetAttribute) {
  const KeywordToken default_token;
  EXPECT_EQ(default_token.GetAttribute(), KeywordAttribute::kUnspecified);

  const KeywordAttribute attribute = KeywordAttribute::kPrint;
  const KeywordToken specified_token(attribute);
  EXPECT_EQ(default_token.GetAttribute(), attribute);
}

TEST(KeywordToken, DebugString) {
  const std::string prefix = "kKeyword:";
  std::vector<std::pair<KeywordAttribute, std::string>> attribute_debug_str =
      {{KeywordAttribute::kProgram,    prefix + "kProgram"},
       {KeywordAttribute::kProcedure,  prefix + "kProcedure"},
       {KeywordAttribute::kInt,        prefix + "kInt"},
       {KeywordAttribute::kBool,       prefix + "kBool"},
       {KeywordAttribute::kBegin,      prefix + "kBegin"},
       {KeywordAttribute::kEnd,        prefix + "kEnd"},
       {KeywordAttribute::kIf,         prefix + "kIf"},
       {KeywordAttribute::kThen,       prefix + "kThen"},
       {KeywordAttribute::kElse,       prefix + "kElse"},
       {KeywordAttribute::kWhile,      prefix + "kWhile"},
       {KeywordAttribute::kLoop,       prefix + "kLoop"},
       {KeywordAttribute::kPrint,      prefix + "kPrint"},
       {KeywordAttribute::kNot,        prefix + "kNot"},
       {KeywordAttribute::kUnspecified, prefix + "kUnspecified"}
      };

  for (const auto& attribute : attribute_debug_str) {
    KeywordToken token(attribute.first);
    EXPECT_EQ(token.DebugString(), attribute.second);
  }
}

}  // namespace
}  // namespace truplc
