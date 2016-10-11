// Utility class that allows dumping output to console in color.
// Copyright 2016 Hieu Le.

#ifndef TRUPLC_UTIL_TEXT_COLORIZER_H__
#define TRUPLC_UTIL_TEXT_COLORIZER_H__

#include <ostream>

namespace truplc {

// Color options to prettify output to UNIX terminal.
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
  // Default immutable instances for text colorization.
  static const TextColorizer kFGRedColorizer;
  static const TextColorizer kFGGreenColorizer;
  static const TextColorizer kFGBlueColorizer;
  static const TextColorizer kFGDefaultColorizer;

  // Constructs a colorizer from given text color.
  explicit TextColorizer(TextColor color);

  // Returns the text color associated with this instance.
  TextColor GetColor() const;

 private:
  // The text color associated with this instance.
  const TextColor color_;
};

}  // namespace truplc

// Override << operator to print output in color.
std::ostream& operator<<(std::ostream& os,
                         const truplc::TextColorizer& colorizer);

#endif  // TRUPLC_UTIL_TEXT_COLORIZER_H__
