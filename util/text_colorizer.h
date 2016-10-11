// Utility class that allows dumping output to console in color.
// Copyright 2016 Hieu Le.

#ifndef TRUPLC_UTIL_TEXT_COLORIZER_H__
#define TRUPLC_UTIL_TEXT_COLORIZER_H__

#include <ostream>
#include <string>

namespace truplc {

class TextColorizer {
 public:
  // Choices for text colorization.
  static const TextColorizer kFGRedColorizer;
  static const TextColorizer kFGGreenColorizer;
  static const TextColorizer kFGBlueColorizer;
  static const TextColorizer kFGDefaultColorizer;

  // Prints output to targeted stream using the specified colorizer.
  static std::ostream& Print(std::ostream& os, const TextColorizer& colorizer,
                             const std::string& output);

 private:
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

  // Constructs a colorizer from given color.
  // Hides constructor to expose only immutable instances.
  explicit TextColorizer(TextColor color);

  // The text color associated with this instance.
  const TextColor color_;
};

}  // namespace truplc

#endif  // TRUPLC_UTIL_TEXT_COLORIZER_H__
