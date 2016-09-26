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
  Compress();
}

InputBuffer::~InputBuffer() {}

void InputBuffer::BufferFatalError(const std::string& message) const {
  std::cerr << message << std::endl;
  std::cerr << "EXITING on BUFFER FATAL ERROR" << std::endl;
  exit(EXIT_FAILURE);
}

char InputBuffer::Next() {
  // Refill buffer if empty.
  if (buffer_.empty()) {
    FillBuffer(stream_.get(), &buffer_, kMaxBufferSize);
  }

  // Error if buffer is still empty after refill attempt.
  if (buffer_.empty()) {
    BufferFatalError("Buffer underflow");
  }

  char output = buffer_.front();
  buffer_.pop_front();
  return output;
}

void InputBuffer::SkipLine() {
  char current = Next();
  while (current != kNewLine) {
    current = Next();
  }
}

void InputBuffer::Compress() {
  char current = Next();
  while (IsWhitespace(current) || current == kCommentMarker) {
    // Remove white spaces.
    while (IsWhitespace(current)) {
      current = Next();
    }
    // Remove comments.
    if (current == kCommentMarker) {
      SkipLine();
      current = Next();
    }
  }
  // current now stores the nearest character that is neither a whitespace
  // nor part of a comment. Places it back at the front of buffer_.
  UnreadChar(current);
}

char InputBuffer::NextChar() {
  char current = Next();

  // All whitespaces and comments are compressed to a single space delimiter.
  if (current == kCommentMarker || IsWhitespace(current)) {
    UnreadChar(current);
    Compress();
    return kSpace;
  }

  return current;
}

void InputBuffer::UnreadChar(char c) {
  buffer_.push_front(c);
}

}  // namespace truplc
