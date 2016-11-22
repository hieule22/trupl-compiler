// Unit tests for SymbolTable class.
// Copyright 2016 Hieu Le.
// TODO(hieule): Fix failing unit tests.

#include "parser/symbol_table.h"

#include "gtest/gtest.h"

namespace truplc {
namespace {

TEST(SymbolTableTest, InstallIdentifier) {
  const std::string identifier = "foo";
  const std::string environment = "main";
  const ExpressionType type = ExpressionType::kInt;
  SymbolTable table;
  table.Install(identifier, environment, type);

  EXPECT_TRUE(table.IsDeclared(identifier, environment));
  EXPECT_EQ(table.GetType(identifier, environment), type);
}

TEST(SymbolTableTest, InstallFormalParameter) {
  const std::string identifier = "foo";
  const std::string environment = "main::bar";
  const ExpressionType type = ExpressionType::kBool;
  const int position = 1;
  SymbolTable table;
  table.Install(identifier, environment, type, position);

  EXPECT_TRUE(table.IsDeclared(identifier, environment));
  EXPECT_EQ(table.GetType(environment, position), type);
}

TEST(SymbolTableTest, UpdateType) {
  const std::string identifier = "foo";
  const std::string environment = "main";
  const ExpressionType type = ExpressionType::kInt;
  SymbolTable table;
  table.Install(identifier, environment, ExpressionType::kUnknown);
  table.UpdateType(type);

  EXPECT_TRUE(table.IsDeclared(identifier, environment));
  EXPECT_EQ(table.GetType(identifier, environment), type);
}

TEST(SymbolTableTest, IsDeclared) {
  const std::string identifier = "foo";
  const std::string environment = "main::bar";
  SymbolTable table;
  table.Install(identifier, environment, ExpressionType::kBool);

  EXPECT_TRUE(table.IsDeclared(identifier, environment));
  EXPECT_FALSE(table.IsDeclared("baz", "quoz"));
}

TEST(SymbolTableTest, GetIdentifierType) {
  const std::string identifier = "foo";
  const std::string environment = "main";
  const ExpressionType type = ExpressionType::kProcedure;
  SymbolTable table;
  table.Install(identifier, environment, type);

  EXPECT_EQ(table.GetType(identifier, environment), type);
  EXPECT_EQ(table.GetType("bar", "quoz"), ExpressionType::kGarbage);
}

TEST(SymbolTableTest, GetFormalParamType) {
  const std::string procedure = "main::foo";
  const ExpressionType type = ExpressionType::kInt;
  const int position = 2;
  SymbolTable table;
  table.Install("bar", procedure, type, position);

  EXPECT_EQ(table.GetType(procedure, position), type);
  EXPECT_EQ(table.GetType(procedure, 1), ExpressionType::kGarbage);
}

TEST(SymbolTableTest, DebugString) {
  SymbolTable table;
  EXPECT_EQ(table.DebugString(ExpressionType::kInt), "kInt");
  EXPECT_EQ(table.DebugString(ExpressionType::kBool), "kBool");
  EXPECT_EQ(table.DebugString(ExpressionType::kProcedure), "kProcedure");
  EXPECT_EQ(table.DebugString(ExpressionType::kProgram), "kProgram");
  EXPECT_EQ(table.DebugString(ExpressionType::kNo), "kNo");
  EXPECT_EQ(table.DebugString(ExpressionType::kUnknown), "kUnknown");
  EXPECT_EQ(table.DebugString(ExpressionType::kGarbage), "kGarbage");
}

}  // namespace
}  // namespace truplc
