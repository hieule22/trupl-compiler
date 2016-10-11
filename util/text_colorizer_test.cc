// Unit tests for TextColorizer.
// Copyright 2016 Hieu Le.

#include "util/text_colorizer.h"

#include <iostream>

#include "gtest/gtest.h"

namespace truplc {
namespace {

TEST(TextColorizer, GetColor) {
  const TextColorizer colorizer(TextColor::FG_RED);
  EXPECT_EQ(colorizer.GetColor(), TextColor::FG_RED);
  const TextColorizer undoer(TextColor::FG_DEFAULT);
  EXPECT_EQ(undoer.GetColor(), TextColor::FG_DEFAULT);
  std::cout << colorizer << "Hello world" << undoer << std::endl;
}

TEST(TextColorizer, Constants) {
  EXPECT_EQ(TextColorizer::kFGRedColorizer.GetColor(), TextColor::FG_RED);
  EXPECT_EQ(TextColorizer::kFGGreenColorizer.GetColor(), TextColor::FG_GREEN);
  EXPECT_EQ(TextColorizer::kFGBlueColorizer.GetColor(), TextColor::FG_BLUE);
  EXPECT_EQ(TextColorizer::kFGDefaultColorizer.GetColor(),
            TextColor::FG_DEFAULT);
}

}  // namespace
}  // namespace truplc
