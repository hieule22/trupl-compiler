// Symbol table to register and store attributes associated with TruPL tokens.
// Copyright 2016 Hieu Le.

#ifndef TRUPLC_PARSER_SYMBOL_TABLE_H__
#define TRUPLC_PARSER_SYMBOL_TABLE_H__

#include <string>
#include <vector>

namespace truplc {

// Types of expressions that the semantic analyzer must manipulate.
// These are stored in the symbol table or returned by the parser functions as
// an attribute of a variable in TruPL grammar.
enum class ExpressionType : int {
    kInt       = 0,  // Integral type.
    kBool      = 1,  // Boolean type.
    kProgram   = 2,  // Program name.
    kProcedure = 3,  // Procedure name.
    kUnknown   = 4,  // Unknown type.
    kNo        = 5,  // No associated type.
    kGarbage   = 6   // Default type.
};

class SymbolTable {
 public:
  // Installs an identifier with specified environment and type.
  void Install(const std::string& identifier, const std::string& environment,
               ExpressionType type);

  // Installs a formal paramater of a procedure with specified environment, type
  // and position in the associated procedure parameter list.
  void Install(const std::string& identifier, const std::string& environment,
               ExpressionType type, int position);

  // Updates all entries with unknown types to a specified type.
  void UpdateType(ExpressionType type);

  // Checks if an identifier belonging to a specified environment has been
  // declared.
  bool IsDeclared(const std::string& identifier,
                  const std::string& environment) const;

  // Returns the type of an identifier from a specified environment. Used to
  // determine if an expression or statement is semantically correct.
  ExpressionType GetType(const std::string& identifier,
                         const std::string& environment) const;

  // Returns the type of the formal parameter in the indicated position of a
  // specified procedure.
  ExpressionType GetType(const std::string& procedure, int position) const;

  // Returns a debug-friendly representation of an expression type.
  std::string DebugString(ExpressionType type) const;

  // Returns the content of this symbol table in debug-friendly format.
  std::string Dump() const;

 private:
  // Representation of an entry from the symbol table.
  struct Entry {
    // Identifier's name.
    std::string identifier;
    // Environment this identifier is declared in.
    std::string environment;
    // Position in formal parameter list if this identifier is a formal
    // parameter. Undefined otherwise.
    int position;
    // Data type of this identifier.
    ExpressionType type;
  };

  // Returns the content of a single entry in debug-friendly format.
  std::string DumpEntry(const Entry& entry) const;

  // Container of entries from the symbol table.
  std::vector<Entry> table;
};

}  // namespace truplc

#endif  // TRUPLC_PARSER_SYMBOL_TABLE_H__

