// Buffer class to read characters from an input stream.
// Copyright 2016 Hieu Le.

#ifndef TRUPLC_SCANNER_INPUT_BUFFER_H__
#define TRUPLC_SCANNER_INPUT_BUFFER_H__

#include <iostream>
#include <list>
#include <memory>
#include <string>

namespace truplc {

// The dollar sign marks the end of file in the buffer.
static const char kEOFMarker     = '$';
static const char kCommentMarker = '#';
static const char kSpace         = ' ';
static const char kTab           = '\t';
static const char kNewLine       = '\n';

class InputBuffer {
 public:
  // Initializes the buffer with specified input stream. Ownership of the stream
  // is acquired this InputBuffer object.
  explicit InputBuffer(std::unique_ptr<std::istream> stream);

  virtual ~InputBuffer();

  // Removes and returns the next character from the buffer. Returns kEOFMarker
  // if there is no more character to read from the buffer.
  char NextChar();

  // Places a character back into the buffer.
  void UnreadChar(char c);

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
  std::unique_ptr<std::istream> stream_;

  // Internal character buffer.
  std::list<char> buffer_;
};

}  // namespace truplc

#endif  // TRUPLC_SCANNER_INPUT_BUFFER_H__
