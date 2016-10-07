// Implementation of TextColorizer.
// Copyright 2016 Hieu Le.

#include "util/text_colorizer.h"

namespace truplc {

TextColorizer::TextColorizer(const TextColor color) : color_(color) {}

TextColor TextColorizer::GetColor() const {
  return color_;
}

}  // namespace truplc

std::ostream& operator<<(std::ostream& os,
                         const truplc::TextColorizer& colorizer) {
  return os << "\033[" << static_cast<int>(colorizer.GetColor()) << "m";
}
