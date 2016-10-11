// Utility class that allows dumping output to console in color.
// Copyright 2016 Hieu Le.

#ifndef TRUPLC_UTIL_TEXT_COLORIZER_H__
#define TRUPLC_UTIL_TEXT_COLORIZER_H__

#include <ostream>

namespace truplc {

enum class TextColor : int {
    FG_RED     = 31,
    FG_GREEN   = 32,
    FG_BLUE    = 34,
    FG_DEFAULT = 39,
    BG_RED     = 41,
    BG_GREEN   = 42,
    BG_BLUE    = 44,
    BG_DEFAULT = 49
};

class TextColorizer {
 public:
  static const TextColorizer kFGRedColorizer;
  static const TextColorizer kFGGreenColorizer;
  static const TextColorizer kFGBlueColorizer;
  static const TextColorizer kFGDefaultColorizer;

  explicit TextColorizer(TextColor color);
  TextColor GetColor() const;

 private:
  const TextColor color_;
};

}  // namespace truplc

std::ostream& operator<<(std::ostream& os,
                         const truplc::TextColorizer& colorizer);

#endif  // TRUPLC_UTIL_TEXT_COLORIZER_H__
