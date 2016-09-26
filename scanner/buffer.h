// Buffer interface to read characters from an input source.
// Copyright 2016 Hieu Le.

#ifndef TRUPLC_SCANNER_BUFFER_H__
#define TRUPLC_SCANNER_BUFFER_H__

#include <string>

namespace truplc {

// Symbol denoting EOF.
const char kEOFMarker     = '$';

// Symbol denoting the start of a comment line.
const char kCommentMarker = '#';

// Whitespace symbols.
const char kSpace         = ' ';
const char kTab           = '\t';
const char kNewLine       = '\n';

class Buffer {
 public:
  virtual ~Buffer() {}

  // Removes and returns the next character from the buffer. Any preceding
  // region of whitespaces and comments will be ignored. Any intervening or
  // trailing region of whitespaces and comments will be compressed into a
  // single delimiting space. The EOF marker is returned when user attempts to
  // read past the end of input.
  virtual char NextChar() = 0;

  // Places a character back into the buffer. Should not be called more than
  // once without an intervening call to NextChar().
  virtual void UnreadChar(char c) = 0;

 protected:
  // Prints an error message and then exits. Intended when something
  // catastrophic happens in the buffer.
  void BufferFatalError(const std::string& message) const;
};

}  // namespace truplc

#endif  // TRUPLC_SCANNER_BUFFER_H__
