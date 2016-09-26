// Implementation for Buffer class.
// Copyright 2016 Hieu Le.

#include "scanner/file_buffer.h"

#include <utility>

#include "scanner/input_buffer.h"

namespace truplc {

FileBuffer::FileBuffer(const std::string& filename) {
  // Open the file and fill the buffer.
  source_file_.open(filename);
  if (source_file_.fail()) {  // Fail to open source file.
    BufferFatalError("Error opening source file: " + filename);
  }
  input_buffer_ = std::make_unique<InputBuffer>(&source_file_);
}

FileBuffer::~FileBuffer() {
  source_file_.close();
}

char FileBuffer::NextChar() {
  return input_buffer_->NextChar();
}

void FileBuffer::UnreadChar(char c) {
  return input_buffer_->UnreadChar(c);
}

}  // namespace truplc
