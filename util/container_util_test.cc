// Unit tests for container utilities.
// Copyright Hieu Le 2016.

#include "util/container_util.h"

#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace truplc {
namespace {

TEST(ContainTest, Basic) {
  std::vector<int> container = {1, 2, 3};
  EXPECT_TRUE(Contain(container, 3));
  EXPECT_FALSE(Contain(container, 0));
}

TEST(FindOrNullTest, Basic) {
  std::unordered_set<int> container = {1, 2, 3, 4};
  EXPECT_EQ(FindOrNull(container, 0), nullptr);
  auto element = FindOrNull(container, 1);
  ASSERT_TRUE(element != nullptr);
  EXPECT_EQ(*element, 1);
}

}  // namespace
}  // namespace truplc
