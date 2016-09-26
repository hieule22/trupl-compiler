// Implementation for InputBuffer class.
// Copyright 2016 Hieu Le.

#include "scanner/input_buffer.h"

#include <sstream>
#include <utility>

namespace truplc {
namespace {

// Checks if given input stream is empty.
inline bool IsEmpty(std::istream& stream) {
  return stream.peek() == EOF;
}

// Checks if given character represents a whitespace symbol. Whitespaces consist
// of space (' '), tab ('\t') and new line ('\n') characters.
inline bool IsWhitespace(char c) {
  return c == kSpace || c == kTab || c == kNewLine;
}

// Fills buffer with characters from an input stream up to some specified limit.
void FillBuffer(std::istream* stream, std::list<char>* buffer,
                const size_t limit) {
  for (size_t i = 0; i < limit && !IsEmpty(*stream); ++i) {
    buffer->push_back(stream->get());
  }
}

}  // namespace

InputBuffer::InputBuffer(std::unique_ptr<std::istream> stream)
    : stream_(std::move(stream)) {
  // Remove any preceding whitespace or comment.
  RemoveSpaceAndComment();
}

InputBuffer::~InputBuffer() {}

char InputBuffer::Next() {
  // Refill buffer if empty.
  if (buffer_.empty()) {
    FillBuffer(stream_.get(), &buffer_, kMaxBufferSize);
  }
  // Signal EOF if buffer is still empty after refill attempt.
  if (buffer_.empty()) {
    return kEOFMarker;
  }

  char current = buffer_.front();
  buffer_.pop_front();
  return current;
}

void InputBuffer::SkipLine() {
  char current = Next();
  while (current != kNewLine && current != kEOFMarker) {
    current = Next();
  }
}

bool InputBuffer::RemoveSpaceAndComment() {
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
  if (current != kEOFMarker) {
    UnreadChar(current);
  }
  return hasWhitespaceOrComment;
}

char InputBuffer::NextChar() {
  // If there are tokens to process after the removed comments and whitespaces,
  // return a default space delimiter. Return EOF otherwise.
  if (RemoveSpaceAndComment()) {
    char current = Next();
    if (current == kEOFMarker) {
      return kEOFMarker;
    }
    UnreadChar(current);
    return kSpace;
  }

  return Next();
}

void InputBuffer::UnreadChar(char c) {
  buffer_.push_front(c);
}

}  // namespace truplc
