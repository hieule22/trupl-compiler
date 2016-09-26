// Implementation for Buffer interface.
// Copyright 2016 Hieu Le.

#include "scanner/buffer.h"

#include <iostream>

namespace truplc {

void Buffer::BufferFatalError(const std::string& message) const {
  std::cerr << message << std::endl;
  std::cerr << "EXITING on BUFFER FATAL ERROR" << std::endl;
  exit(EXIT_FAILURE);
}

}  // namespace truplc
