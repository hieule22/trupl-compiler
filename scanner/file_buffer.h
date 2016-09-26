// Buffer class to read characters from input file.
// Copyright 2016 Hieu Le.

#ifndef TRUPLC_SCANNER_FILE_BUFFER_H__
#define TRUPLC_SCANNER_FILE_BUFFER_H__

#include <fstream>
#include <string>
#include <memory>

#include "scanner/input_buffer.h"

namespace truplc {

class FileBuffer {
 public:
  // Opens input program file and initializes the buffer.
  explicit FileBuffer(const std::string& filename);

  // Closes the file and performs any needed clean-up.
  ~FileBuffer();

  // Removes and returns the next character from the buffer.
  char NextChar();

  // Places a character back at the front of the buffer.
  void UnreadChar(char c);

 private:
  // Prints an error message and then exits. Intended when something
  // catastrophic happens in the buffer.
  void BufferFatalError() const;

  // The stream object for the source file.
  std::ifstream source_file_;

  // The contained input buffer.
  std::unique_ptr<InputBuffer> input_buffer_;
};

}  // namespace truplc

#endif  // TRUPLC_SCANNER_FILE_BUFFER_H__
