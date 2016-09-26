// Implementation for Buffer interface.
// Copyright 2016 Hieu Le.

#include "scanner/buffer.h"

#include <cctype>

#include <algorithm>
#include <iostream>

namespace truplc {

void Buffer::BufferFatalError(const std::string& message) const {
  std::cerr << message << std::endl;
  std::cerr << "EXITING on BUFFER FATAL ERROR" << std::endl;
  exit(EXIT_FAILURE);
}

bool Buffer::Validate(const char c) {
  return std::islower(c) || std::isdigit(c) ||
      std::find(std::begin(kNonAlphanum), std::end(kNonAlphanum), c) !=
      std::end(kNonAlphanum);
}

}  // namespace truplc
