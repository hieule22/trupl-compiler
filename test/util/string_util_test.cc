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

TEST(FormatTest, Basic) {
  EXPECT_EQ(Format("%d %s", 1, "foo"), "1 foo");
  EXPECT_EQ(Format("%.1f", 3.1415), "3.1");
}

}  // namespace
}  // namespace truplc
