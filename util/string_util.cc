// Implementation of string utilities.
// Copyright 2016 Hieu Le.

#include "util/string_util.h"

#include <initializer_list>
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

}  // namespace truplc
