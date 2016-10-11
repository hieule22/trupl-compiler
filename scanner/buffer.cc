// Implementation for Buffer interface.
// Copyright 2016 Hieu Le.

#include "scanner/buffer.h"

#include <cctype>

#include <algorithm>
#include <iostream>

#include "util/container_util.h"
#include "util/string_util.h"
#include "util/text_colorizer.h"

namespace truplc {

void Buffer::BufferFatalError(const std::string& message) const {
  TextColorizer::Print(std::cerr, TextColorizer::kFGRedColorizer,
                       StrCat(message, "\nEXITING on BUFFER FATAL ERROR\n"));
  exit(EXIT_FAILURE);
}

bool Buffer::Validate(const char c) {
  return std::islower(c) || std::isdigit(c) || Contain(kNonAlphanum, c);
}

}  // namespace truplc
