// Buffer interface to read characters from an input source.
// Copyright 2016 Hieu Le.

#ifndef TRUPLC_SCANNER_BUFFER_H__
#define TRUPLC_SCANNER_BUFFER_H__

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
  
  // Removes and returns the next character from the buffer. Subclass seeking
  // to override this method should remove any preceding regions of whitespaces
  // and comments. Intervening / trailing regions of whitespaces and comments
  // must be compressed into a single delimiting space.
  // Should not crash when user attempts to read past the end of input and
  // return an EOF marker instead.
  virtual char NextChar() = 0;

  // Places a character back into the buffer. Should not be called more than
  // once without an intervening call to NextChar().
  virtual void UnreadChar(char c) = 0;
};

}  // namespace truplc

#endif  // TRUPLC_SCANNER_BUFFER_H__
