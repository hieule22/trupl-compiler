// Implementation of container utilities.
// Copyright 2016 Hieu Le.

#include "util/container_util.h"

namespace truplc {

template <typename Container, typename T>
bool Contain(const Container& container, const T& value) {
  return std::find(std::begin(container), std::end(container), value)
      != std::end(container);
}

template <typename Container, typename T>
T* FindOrNull(const Container& container, const T& value) {
  auto pointer = std::find(std::begin(container), std::end(container), value);
  return pointer != std::end(container) ? *pointer : nullptr;
}

}  // namespace truplc
