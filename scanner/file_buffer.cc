// Implementation for FileBuffer class.
// Copyright 2016 Hieu Le.

#include "scanner/file_buffer.h"

#include <utility>

#include "scanner/stream_buffer.h"

namespace truplc {

FileBuffer::FileBuffer(const std::string& filename) {
  // Open the file and fill the buffer.
  source_file_.open(filename);
  if (source_file_.fail()) {  // Fail to open source file.
    BufferFatalError("Error opening source file: " + filename);
  }
  buffer_ = std::make_unique<StreamBuffer>(&source_file_);
}

FileBuffer::~FileBuffer() {
  source_file_.close();
}

char FileBuffer::NextChar() {
  return buffer_->NextChar();
}

void FileBuffer::UnreadChar(const char c) {
  return buffer_->UnreadChar(c);
}

}  // namespace truplc
