// Unit tests for FileBuffer class.
// Copyright 2016 Hieu Le.

#include "scanner/file_buffer.h"

#include <iostream>

#include "gtest/gtest.h"

namespace truplc {
namespace {

TEST(FileBufferTest, NextCharBasic) {
  const std::string filename = "";
  FileBuffer buffer(filename);
  char current = buffer.NextChar();
  while (current != kEOFMarker) {
    std::cout << current;
    current = buffer.NextChar();
  }
  std::cout << std::endl;
}

}  // namespace
}  // namespace truplc
