// Implementation of TextColorizer.
// Copyright 2016 Hieu Le.

#include "util/text_colorizer.h"

namespace truplc {

const TextColorizer TextColorizer::kFGRedColorizer(TextColor::FG_RED);
const TextColorizer TextColorizer::kFGGreenColorizer(TextColor::FG_GREEN);
const TextColorizer TextColorizer::kFGBlueColorizer(TextColor::FG_BLUE);
const TextColorizer TextColorizer::kFGDefaultColorizer(TextColor::FG_DEFAULT);

std::ostream& TextColorizer::Print(std::ostream& os,
                                   const TextColorizer& colorizer,
                                   const std::string& output) {
  return os << "\033[" << static_cast<int>(colorizer.color_) << "m"
            << output << "\033["
            << static_cast<int>(kFGDefaultColorizer.color_) << "m";
}

TextColorizer::TextColorizer(const TextColor color) : color_(color) {}

}  // namespace truplc
