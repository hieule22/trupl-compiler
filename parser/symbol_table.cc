// Implementation for SymbolTable class.
// Copyright 2016 Hieu Le.

#include "parser/symbol_table.h"

#include "util/string_util.h"

namespace truplc {

std::string DebugString(const ExpressionType type) {
  std::string debug_str;

  switch (type) {
    case ExpressionType::kInt:
      debug_str = "kInt";
      break;

    case ExpressionType::kBool:
      debug_str = "kBool";
      break;

    case ExpressionType::kProgram:
      debug_str = "kProgram";
      break;

    case ExpressionType::kProcedure:
      debug_str = "kProcedure";
      break;

    case ExpressionType::kUnknown:
      debug_str = "kUnknown";
      break;

    case ExpressionType::kNo:
      debug_str = "kNo";
      break;

    default:
      debug_str = "kGarbage";
      break;
  }

  return debug_str;;
}

void SymbolTable::Install(const std::string& identifier,
                          const std::string& environment,
                          const ExpressionType type) {
  Install(identifier, environment, type, -1);
}

void SymbolTable::Install(const std::string& identifier,
                          const std::string& environment,
                          const ExpressionType type,
                          const int position) {
  table_.push_back(Entry(identifier, environment, type, position));
}

void SymbolTable::UpdateType(const ExpressionType type) {
  for (Entry& entry : table_) {
    if (entry.type == ExpressionType::kUnknown) {
      entry.type = type;
    }
  }
}

bool SymbolTable::IsDeclared(const std::string& identifier,
                             const std::string& environment) const {
  for (const Entry& entry : table_) {
    if (entry.identifier == identifier && entry.environment == environment) {
      return true;
    }
  }
  return false;
}

ExpressionType SymbolTable::GetType(const std::string& identifier,
                                    const std::string& environment) const {
  for (const Entry& entry : table_) {
    if (entry.identifier == identifier && entry.environment == environment) {
      return entry.type;
    }
  }
  return ExpressionType::kGarbage;
}

ExpressionType SymbolTable::GetType(const std::string& procedure,
                                    const int position) const {
  for (const Entry& entry : table_) {
    if (entry.environment == procedure && entry.position == position) {
      return entry.type;
    }
  }
  return ExpressionType::kGarbage;
}

std::string SymbolTable::Dump() const {
  std::string debug_str = "Content of symbol table:";
  for (const Entry& entry : table_) {
    debug_str.push_back('\n');
    debug_str.append(DumpEntry(entry));
  }
  return debug_str;
}

std::string SymbolTable::DumpEntry(const Entry& entry) const {
  return Format("ID: %s ENV: %s TYPE: %s POS: %d",
                entry.identifier.c_str(), entry.environment.c_str(),
                DebugString(entry.type).c_str(), entry.position);
}

}  // namespace truplc
