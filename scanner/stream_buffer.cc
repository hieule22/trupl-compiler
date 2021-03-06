// Implementation for StreamBuffer class.
// Copyright 2016 Hieu Le.

#include "scanner/stream_buffer.h"

#include <sstream>
#include <utility>

namespace truplc {
namespace {

// Checks if given input stream is empty.
inline bool IsEmptyStream(std::istream* stream) {
  return stream->peek() == EOF;
}

// Checks if given character represents a whitespace symbol. Whitespaces consist
// of space (' '), tab ('\t') and new line ('\n') characters.
inline bool IsWhitespace(char c) {
  return c == kSpace || c == kTab || c == kNewLine;
}

// Fills buffer with characters from an input stream up to some specified limit.
void FillBuffer(std::istream* stream, std::list<char>* buffer,
                const size_t limit) {
  for (size_t i = 0; i < limit && !IsEmptyStream(stream); ++i) {
    buffer->push_back(stream->get());
  }
}

}  // namespace

StreamBuffer::StreamBuffer(std::istream* stream)
    : stream_(stream), exhausted(false) {
  // Remove any preceding whitespace or comment.
  RemoveSpaceAndComment();
}

char StreamBuffer::Next() {
  // Refill buffer if empty.
  if (buffer_.empty()) {
    FillBuffer(stream_, &buffer_, kMaxBufferSize);
  }
  // Signal EOF if buffer is still empty after refill attempt.
  if (buffer_.empty()) {
    exhausted = true;
    return kEOFMarker;
  }

  char current = buffer_.front();
  buffer_.pop_front();
  return current;
}

void StreamBuffer::SkipLine() {
  char current = Next();
  while (current != kNewLine && !exhausted) {
    current = Next();
  }
}

bool StreamBuffer::RemoveSpaceAndComment() {
  char current = Next();
  bool hasWhitespaceOrComment = false;
  while (IsWhitespace(current) || current == kCommentMarker) {
    hasWhitespaceOrComment = true;
    while (IsWhitespace(current)) {  // Remove whitespaces.
      current = Next();
    }
    if (current == kCommentMarker) {  // Remove comments.
      SkipLine();
      current = Next();
    }
  }

  // current now stores the nearest character that is neither a whitespace
  // nor part of a comment. If current is not EOF, places it back at the front
  // of buffer.
  if (!exhausted) {
    buffer_.push_front(current);
  }
  return hasWhitespaceOrComment;
}

char StreamBuffer::NextChar() {
  // Removes any subsequent region of whitespaces and comments and returns the
  // default space delimiter.
  if (RemoveSpaceAndComment()) {
    return kSpace;
  }

  char current = Next();
  // Flags error if current does not belong to the TruPL alphabet.
  if (!Validate(current)) {
    if (!(current == kEOFMarker && exhausted)) {
      BufferFatalError(std::string("Invalid character: ") + current);
    }
  }
  return current;
}

void StreamBuffer::UnreadChar(const char c) {
  if (c != kEOFMarker) {
    exhausted = false;
    buffer_.push_front(c);
  }
}

}  // namespace truplc
