// Implementation of string utilities.
// Copyright 2016 Hieu Le.

#include "util/string_util.h"

#include <cstdarg>

#include <initializer_list>
#include <memory>
#include <sstream>

namespace truplc {
namespace {

// Returns the concatenation of an initializer list of strings.
std::string StrCat(std::initializer_list<std::string> args) {
  std::ostringstream os;
  for (auto str = args.begin(); str != args.end(); ++str) {
    os << *str;
  }
  return os.str();
}

}  // namespace

std::string StrCat(const std::string& s0, const std::string& s1) {
  return StrCat({s0, s1});
}

std::string StrCat(const std::string& s0, const std::string& s1,
                   const std::string& s2) {
  return StrCat({s0, s1, s2});
}

std::string Format(const std::string fmt, ...) {
  int finalLength;
  // Reserve twice the length of fmt.
  int capacity = static_cast<int>(fmt.size()) * 2;
  std::string str;
  std::unique_ptr<char[]> formatted;
  va_list ap;
  while (true) {
    // Wrap the plain char array inside a unique pointer.
    formatted.reset(new char[capacity]);
    strcpy(&formatted[0], fmt.c_str());
    va_start(ap, fmt);
    finalLength = vsnprintf(&formatted[0], capacity, fmt.c_str(), ap);
    va_end(ap);
    if (finalLength < 0 || finalLength >= capacity) {
      capacity += abs(finalLength - capacity + 1);
    } else {
      break;
    }
  }

  return std::string(formatted.get());
}

}  // namespace truplc
