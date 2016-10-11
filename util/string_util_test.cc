// Unit tests for string utilities.
// Copyright 2016 Hieu Le.

#include "util/string_util.h"

#include "gtest/gtest.h"

namespace truplc {
namespace {

TEST(StrCatTest, Basic) {
  EXPECT_EQ(StrCat("Foo", "Bar"), "FooBar");
  EXPECT_EQ(StrCat("Foo", "Bar", "Quoz"), "FooBarQuoz");
}

}  // namespace
}  // namespace truplc
