// Implementation for Buffer interface.
// Copyright 2016 Hieu Le.

#include "scanner/buffer.h"

#include <cctype>

#include <algorithm>
#include <iostream>

namespace truplc {
namespace {

template <typename Container, typename T>
bool Contains(const Container& container, const T& value) {
  return std::find(std::begin(container), std::end(container), value)
      != std::end(container);
}

}  // namespace

void Buffer::BufferFatalError(const std::string& message) const {
  std::cerr << message << std::endl;
  std::cerr << "EXITING on BUFFER FATAL ERROR" << std::endl;
  exit(EXIT_FAILURE);
}

bool Buffer::Validate(const char c) {
  return std::islower(c) || std::isdigit(c) || Contains(kNonAlphanum, c);
}

}  // namespace truplc
