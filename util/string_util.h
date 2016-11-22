// Utility functions to manipulate strings.
// Copyright 2016 Hieu Le.

#ifndef TRUPLC_UTIL_STRING_UTIL_H__
#define TRUPLC_UTIL_STRING_UTIL_H__

#include <string>

namespace truplc {

// Returns the concatenation of two strings.
std::string StrCat(const std::string& s0, const std::string& s1);

// Returns the concatenation of three strings.
std::string StrCat(const std::string& s0, const std::string& s1,
                   const std::string& s2);

// Returns a string constructed from format specifiers and arguments.
std::string Format(const std::string fmt, ...);

}  // namespace truplc

#endif  // #ifndef TRUPLC_UTIL_STRING_UTIL_H__
