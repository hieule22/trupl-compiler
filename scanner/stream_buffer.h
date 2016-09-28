// Buffer class to read characters from an input stream.
// Copyright 2016 Hieu Le.

#ifndef TRUPLC_SCANNER_STREAM_BUFFER_H__
#define TRUPLC_SCANNER_STREAM_BUFFER_H__

#include <iostream>
#include <list>
#include <memory>
#include <string>

#include "scanner/buffer.h"

namespace truplc {

class StreamBuffer : public Buffer {
 public:
  // Initializes the buffer with specified input stream. The associated stream
  // shall not be destroyed or modified during the lifetime of this object.
  explicit StreamBuffer(std::istream* stream);

  // Removes and returns the next character from the buffer. Returns EOF if
  // there is no more character to read from the buffer.
  char NextChar() override;

  // Places a character back into the buffer.
  void UnreadChar(char c) override;

 private:
  // Capacity of internal character buffer.
  static const size_t kMaxBufferSize = 1024;

  // Gets the next character and performs any necessary buffer refill.
  char Next();

  // Skips the current line of characters.
  void SkipLine();

  // Removes any subsequent whitespace and comment. If there is any remaining
  // token to process, the first character of that token would be stored in
  // the buffer's front.
  // Returns true if any removal takes place; false otherwise.
  bool RemoveSpaceAndComment();

  // Input stream to read characters from.
  std::istream* stream_;

  // Internal character buffer.
  std::list<char> buffer_;

  // Flags indicating if EOF has been reached.
  // TODO(hieule): Remove this.
  bool exhausted;
};

}  // namespace truplc

#endif  // TRUPLC_SCANNER_STREAM_BUFFER_H__
