// Implementation for SymbolTable class.
// Copyright 2016 Hieu Le.

#include "parser/symbol_table.h"

namespace truplc {

void SymbolTable::Install(const std::string& identifier,
                          const std::string& environment,
                          const ExpressionType type) {
  // TODO(hieule): Unimplemented method.
}

void SymbolTable::Install(const std::string& identifier,
                          const std::string& environment,
                          const ExpressionType type,
                          const int position) {
  // TODO(hieule): Unimplemented method.
}

void SymbolTable::UpdateType(const ExpressionType type) {
  // TODO(hieule): Unimplemented method.
}

bool SymbolTable::IsDeclared(const std::string& identifier,
                             const std::string& environment) const {
  // TODO(hieule): Unimplemented method.
  return false;
}

ExpressionType SymbolTable::GetType(const std::string& identifier,
                                    const std::string& environment) const {
  // TODO(hieule): Unimplemented method.
  return ExpressionType::kGarbage;
}

ExpressionType SymbolTable::GetType(const std::string& procedure,
                                    const int position) const {
  // TODO(hieule): Unimplemented method.
  return ExpressionType::kGarbage;
}

std::string SymbolTable::DebugString(const ExpressionType type) const {
  // TODO(hieule): Unimplemented method.
  return "";
}

std::string SymbolTable::Dump() const {
  // TODO(hieule): Unimplemented method.
  return "";
}

std::string SymbolTable::DumpEntry(const Entry& entry) const {
  // TODO(hieule): Unimplemented method.
  return "";
}

}  // namespace truplc
