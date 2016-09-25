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
  // Initializes the buffer with specified input stream.
  // Ownership of the stream is transferred to this InputBuffer object.
  explicit InputBuffer(std::unique_ptr<std::istream> stream);

  virtual ~InputBuffer();

  // Removes and returns the next character from the buffer.
  char NextChar();

  // Places a character back into the buffer.
  void UnreadChar(char c);

 private:
  // Capacity of internal character buffer.
  static const int kMaxBufferSize = 1024;

  // Gets the next character and performs any necessary buffer refill.
  char Next();

  // Skips the current line of characters.
  void NextLine();

  // Skips all whitespaces and comments and points front of buffer to the
  // nearest character that is not a whitespace or part of a comment.
  void Compress();

  // Prints an error message and exits current process. Intended for
  // catastrophic events happening in the buffer.
  void BufferFatalError(const std::string& message);

  // Input stream to read characters from.
  std::unique_ptr<std::istream> stream_;

  // Internal character buffer.
  std::list<char> buffer_;
};

}  // namespace truplc

#endif  // TRUPLC_SCANNER_INPUT_BUFFER_H__
