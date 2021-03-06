// Unit tests for SymbolTable class.
// Copyright 2016 Hieu Le.

#include "parser/symbol_table.h"

#include "gtest/gtest.h"

namespace truplc {
namespace {

TEST(DebugStringTest, Basic) {
  EXPECT_EQ(DebugString(ExpressionType::kInt), "kInt");
  EXPECT_EQ(DebugString(ExpressionType::kBool), "kBool");
  EXPECT_EQ(DebugString(ExpressionType::kProcedure), "kProcedure");
  EXPECT_EQ(DebugString(ExpressionType::kProgram), "kProgram");
  EXPECT_EQ(DebugString(ExpressionType::kNo), "kNo");
  EXPECT_EQ(DebugString(ExpressionType::kUnknown), "kUnknown");
  EXPECT_EQ(DebugString(ExpressionType::kGarbage), "kGarbage");
}

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

TEST(SymbolTableTest, Dump) {
  SymbolTable table;
  EXPECT_EQ(table.Dump(), "Content of symbol table:");

  table.Install("bar", "main::foo", ExpressionType::kInt, 1);
  EXPECT_EQ(table.Dump(),
            "Content of symbol table:\n"
            "ID: bar ENV: main::foo TYPE: kInt POS: 1");

  table.Install("quoz", "main", ExpressionType::kBool);
  EXPECT_EQ(table.Dump(),
            "Content of symbol table:\n"
            "ID: bar ENV: main::foo TYPE: kInt POS: 1\n"
            "ID: quoz ENV: main TYPE: kBool POS: -1");
}

}  // namespace
}  // namespace truplc
