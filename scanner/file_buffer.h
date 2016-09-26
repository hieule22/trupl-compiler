// Buffer class to read characters from an input file.
// Copyright 2016 Hieu Le.

#ifndef TRUPLC_SCANNER_FILE_BUFFER_H__
#define TRUPLC_SCANNER_FILE_BUFFER_H__

#include <fstream>
#include <string>
#include <memory>

#include "scanner/buffer.h"

namespace truplc {

class FileBuffer : public Buffer {
 public:
  // Opens input program file and initializes the buffer.
  explicit FileBuffer(const std::string& filename);

  // Closes the file and performs any needed clean-up.
  ~FileBuffer();

  // Removes and returns the next character from the buffer.n
  char NextChar() override;

  // Places a character back into the buffer.
  void UnreadChar(char c) override;

 private:
  // The stream object for the source file.
  std::ifstream source_file_;

  // The composed stream buffer.
  std::unique_ptr<Buffer> buffer_;
};

}  // namespace truplc

#endif  // TRUPLC_SCANNER_FILE_BUFFER_H__
