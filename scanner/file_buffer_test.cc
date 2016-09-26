// Unit tests for FileBuffer class.
// Copyright 2016 Hieu Le.

#include "scanner/file_buffer.h"

#include <iostream>
#include <utility>

#include "gtest/gtest.h"

namespace truplc {
namespace {

TEST(FileBufferTest, NextCharBasic) {
  const std::string filename = "";
  std::unique_ptr<Buffer> buffer = std::make_unique<FileBuffer>(filename);
  char current = buffer->NextChar();
  while (current != kEOFMarker) {
    std::cout << current;
    current = buffer->NextChar();
  }
  std::cout << std::endl;
}

}  // namespace
}  // namespace truplc
