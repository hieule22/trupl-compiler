// Implementation of TextColorizer.
// Copyright 2016 Hieu Le.

#include "util/text_colorizer.h"

namespace truplc {

const TextColorizer TextColorizer::kFGRedColorizer(TextColor::FG_RED);
const TextColorizer TextColorizer::kFGGreenColorizer(TextColor::FG_GREEN);
const TextColorizer TextColorizer::kFGBlueColorizer(TextColor::FG_BLUE);
const TextColorizer TextColorizer::kFGDefaultColorizer(TextColor::FG_DEFAULT);

std::ostream& TextColorizer::Print(std::ostream& os, const std::string& output,
                                   const TextColorizer& colorizer) {
  return os << colorizer << output << kFGDefaultColorizer;
}

TextColorizer::TextColorizer(const TextColor color) : color_(color) {}

TextColor TextColorizer::GetColor() const {
  return color_;
}

}  // namespace truplc

std::ostream& operator<<(std::ostream& os,
                         const truplc::TextColorizer& colorizer) {
  return os << "\033[" << static_cast<int>(colorizer.GetColor()) << "m";
}
