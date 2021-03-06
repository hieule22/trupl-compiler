// Collection of utility modules for working with C++ containers.
// Copyright 2016 Hieu Le.

#ifndef TRUPLC_UTIL_CONTAINER_UTIL_H__
#define TRUPLC_UTIL_CONTAINER_UTIL_H__

#include <algorithm>

namespace truplc {

// Checks if a given value is a member of the specified container.
template <typename Container, typename T>
bool Contain(const Container& container, const T& value) {
  return std::find(std::begin(container), std::end(container), value)
      != std::end(container);
}

// Searches for a given value inside a specified container.
// Returns a pointer to the element if found; NULL otherwise.
template <typename Container, typename T>
const T* FindOrNull(const Container& container, const T& value) {
  auto pointer = std::find(std::begin(container), std::end(container), value);
  return pointer != std::end(container) ? &(*pointer) : nullptr;
}

}  // namespace truplc

#endif  // TRUPLC_UTIL_CONTAINER_UTIL_H__

