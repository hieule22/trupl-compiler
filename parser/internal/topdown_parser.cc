// Implementation for TopdownParser.
// Copyright 2016 Hieu Le.

#include "parser/internal/topdown_parser.h"

#include <utility>

#include "tokens/add_operator_token.h"
#include "tokens/identifier_token.h"
#include "tokens/keyword_token.h"
#include "tokens/mul_operator_token.h"
#include "tokens/number_token.h"
#include "tokens/punctuation_token.h"
#include "tokens/rel_operator_token.h"
#include "util/string_util.h"

namespace truplc {
namespace internal {

namespace {

// Default value for undefined environment.
static const char kDefaultEnvName[] = "__UNDEFINED";

}  // namespace

TopdownParser::TopdownParser(std::unique_ptr<Scanner> scanner)
    : scanner_(std::move(scanner)),
      word_(scanner_->NextToken()),
      current_env_(kDefaultEnvName),
      main_env_(kDefaultEnvName),
      procedure_name_(kDefaultEnvName),
      parsing_formal_parm_list_(false) {}

bool TopdownParser::HasNextToken() const {
  // If we have parsed the entire program, then word should be EOF.
  return word_->GetTokenType() == TokenType::kEOF;
}

void TopdownParser::Advance() {
  word_ = scanner_->NextToken();
}

namespace {

// Logs an error message to console and crashes if specified.
void PrintError(const std::string& message, bool crash) {
  std::cerr << message << std::endl;
  if (crash) {
    exit(EXIT_FAILURE);
  }
}

}  // namespace

void TopdownParser::ReportSyntaxError(const std::string& expected,
                                      const Token& actual) const {
  PrintError(Format("Syntax error: Expected: %s Actual: %s.",
                    expected.c_str(), actual.DebugString().c_str()), false);
}

void TopdownParser::ReportMultiplyDefinedIdentifier(
    const std::string& identifier) const {
  PrintError(Format("Semantic error: The identifier '%s' has been declared.",
                    identifier.c_str()), true);
}

void TopdownParser::ReportUndeclaredIdentifier(
    const std::string& identifier) const {
  PrintError(Format("Semantic error: The identifier '%s' has already been "
                    "declared.", identifier.c_str()), true);
}

void TopdownParser::ReportTypeError(const ExpressionType expected,
                                    const ExpressionType actual) const {
  PrintError(Format("Type error: Expected: %s Actual: %s.",
                    DebugString(expected).c_str(),
                    DebugString(actual).c_str()), true);
}

void TopdownParser::ReportTypeError(ExpressionType expected0,
                                    ExpressionType expected1,
                                    ExpressionType actual) const {
  PrintError(Format("Type error: Expected: %s or %s Actual: %s.",
                    DebugString(expected0).c_str(),
                    DebugString(expected1).c_str(),
                    DebugString(actual).c_str()), true);
}

namespace {

// Functions for querying the type of a token.

// Checks if a given token is an identifier.
inline bool IsIdentifier(const Token& token) {
  return token.GetTokenType() == TokenType::kIdentifier;
}

// Checks if a given token is a keyword with the specified attribute.
inline bool IsKeyword(const Token& token, const KeywordAttribute attr) {
  return token.GetTokenType() == TokenType::kKeyword
      && static_cast<const KeywordToken&>(token).GetAttribute() == attr;
}

// Checks if a given token is a punctuation with the specified attribute.
inline bool IsPunctuation(const Token& token, const PunctuationAttribute attr) {
  return token.GetTokenType() == TokenType::kPunctuation
      && static_cast<const PunctuationToken&>(token).GetAttribute() == attr;
}

// Checks if a given token is an additive operator.
inline bool IsAddop(const Token& token) {
  return token.GetTokenType() == TokenType::kAddOperator;
}

// Checks if a given token is an addop with the specified attribute.
inline bool IsAddop(const Token& token, const AddOperatorAttribute attr) {
  return IsAddop(token) &&
      static_cast<const AddOperatorToken&>(token).GetAttribute() == attr;
}

// Checks if a given token is a multiplicative operator.
inline bool IsMulop(const Token& token) {
  return token.GetTokenType() == TokenType::kMulOperator;
}

// Checks if a given token is a relational operator.
inline bool IsRelop(const Token& token) {
  return token.GetTokenType() == TokenType::kRelOperator;
}

// Checks if a given token is a number.
inline bool IsNumber(const Token& token) {
  return token.GetTokenType() == TokenType::kNumber;
}

}  // namespace

bool TopdownParser::ParseProgram() {
  // PROGRAM -> program identifier ; DECL_LIST BLOCK ;
  if (IsKeyword(*word_, KeywordAttribute::kProgram)) {
    Advance();
    if (IsIdentifier(*word_)) {
      const std::string& id_name =
          static_cast<const IdentifierToken&>(*word_).GetAttribute();
      const std::string global_env_name = "_EXTERNAL";
      symtable_.Install(id_name, global_env_name, ExpressionType::kProgram);
      current_env_ = id_name;
      main_env_ = id_name;
      Advance();
      if (IsPunctuation(*word_, PunctuationAttribute::kSemicolon)) {
        Advance();
        if (ParseDeclList()) {
          // Dump the content of symbol table.
          symtable_.Dump();
          if (ParseBlock()) {
            if (IsPunctuation(*word_, PunctuationAttribute::kSemicolon)) {
              Advance();
              return true;
            } else {
              ReportSyntaxError("';'", *word_);
              return false;
            }
          } else {
            return false;
          }
        } else {
          return false;
        }
      } else {
        ReportSyntaxError("';'", *word_);
        return false;
      }
    } else {
      ReportSyntaxError("identifier", *word_);
      return false;
    }
  } else {
    ReportSyntaxError("keyword 'program'", *word_);
    return false;
  }
  return false;
}

bool TopdownParser::ParseDeclList() {
  /* DECL_LIST -> VARIABLE_DECL_LIST PROCEDURE_DECL_LIST */
  return ParseVariableDeclList() && ParseProcedureDeclList();
}

bool TopdownParser::ParseVariableDeclList() {
  /* VARIABLE_DECL_LIST -> VARIABLE_DECL ; VARIABLE_DECL_LIST */
  if (IsIdentifier(*word_)) {
    if (ParseVariableDecl()) {
      if (IsPunctuation(*word_, PunctuationAttribute::kSemicolon)) {
        Advance();
        return ParseVariableDeclList();
      } else {
        ReportSyntaxError("';'", *word_);
        return false;
      }
    } else {
      return false;
    }
  } else {
    return true;
  }

  return false;
}

bool TopdownParser::ParseVariableDecl() {
  /* VARIABLE_DECL -> IDENTIFIER_LIST : STANDARD_TYPE */
  if (IsIdentifier(*word_)) {
    if (ParseIdentifierList()) {
      if (IsPunctuation(*word_, PunctuationAttribute::kColon)) {
        ExpressionType standard_type_type = ExpressionType::kGarbage;
        Advance();
        if (ParseStandardType(&standard_type_type)) {
          symtable_.UpdateType(standard_type_type);
          return true;
        } else {
          return false;
        }
      } else {
        ReportSyntaxError("':'", *word_);
        return false;
      }
    } else {
      return false;
    }
  } else {
    ReportSyntaxError("identifier", *word_);
    return false;
  }

  return false;
}

bool TopdownParser::ParseProcedureDeclList() {
  /* PROCEDURE_DECL_LIST -> PROCEDURE_DECL ; PROCEDURE_DECL_LIST */
  if (IsKeyword(*word_, KeywordAttribute::kProcedure)) {
    if (ParseProcedureDecl()) {
      if (IsPunctuation(*word_, PunctuationAttribute::kSemicolon)) {
        Advance();
        return ParseProcedureDeclList();
      } else {
        ReportSyntaxError("';'", *word_);
        return false;
      }
    } else {
      return false;
    }
    /* PROCEDURE_DECL_LIST -> lambda */
  } else {
    return true;
  }

  return false;
}

bool TopdownParser::ParseIdentifierList() {
  /* IDENTIFIER_LIST -> identifier IDENTIFIER_LIST_PRM */
  if (IsIdentifier(*word_)) {
    const std::string& identifier_attr =
        static_cast<const IdentifierToken&>(*word_).GetAttribute();
    if (symtable_.IsDeclared(identifier_attr, current_env_)) {
      ReportMultiplyDefinedIdentifier(identifier_attr);
    } else {
      symtable_.Install(identifier_attr, current_env_,
                        ExpressionType::kUnknown);
    }
    Advance();
    return ParseIdentifierListPrm();
  } else {
    ReportSyntaxError("identifier", *word_);
    return false;
  }

  return false;
}

bool TopdownParser::ParseIdentifierListPrm() {
  /* IDENTIFIER_LIST_PRM = , identifier IDENTIFIER_LIST_PRM */
  if (IsPunctuation(*word_, PunctuationAttribute::kComma)) {
    Advance();
    if (IsIdentifier(*word_)) {
      const std::string& identifier_attr =
          static_cast<const IdentifierToken&>(*word_).GetAttribute();
      if (symtable_.IsDeclared(identifier_attr, current_env_)) {
        ReportMultiplyDefinedIdentifier(identifier_attr);
      } else {
        if (parsing_formal_parm_list_) {
          symtable_.Install(identifier_attr, current_env_,
                            ExpressionType::kUnknown, formal_parm_position_);
          ++formal_parm_position_;
        } else {
          symtable_.Install(identifier_attr, current_env_,
                            ExpressionType::kUnknown);
        }
      }
      Advance();
      return ParseIdentifierListPrm();
    } else {
      ReportSyntaxError("identifier", *word_);
      return false;
    }
    /* IDENTIFIER_LIST_PRM = lambda */
  } else {
    return true;
  }

  return false;
}

bool TopdownParser::ParseStandardType(ExpressionType* standard_type_type) {
  /* STANDARD_TYPE -> int */
  if (IsKeyword(*word_, KeywordAttribute::kInt)) {
    *standard_type_type = ExpressionType::kInt;
    Advance();
    return true;
    /* STANDARD_TYPE -> bool */
  } else if (IsKeyword(*word_, KeywordAttribute::kBool)) {
    *standard_type_type = ExpressionType::kBool;
    Advance();
    return true;
  }

  return false;
}

bool TopdownParser::ParseBlock() {
  /* BLOCK -> begin STMT_LIST end */
  if (IsKeyword(*word_, KeywordAttribute::kBegin)) {
    Advance();
    if (ParseStmtList()) {
      if (IsKeyword(*word_, KeywordAttribute::kEnd)) {
        Advance();
        return true;
      } else {
        ReportSyntaxError("keyword 'end'", *word_);
        return false;
      }
    } else {
      return false;
    }
  } else {
    ReportSyntaxError("keyword 'begin'", *word_);
    return false;
  }

  return false;
}

bool TopdownParser::ParseProcedureDecl() {
  /* PROCEDURE_DECL ->
     procedure identifier ( PROCEDURE_ARGS ) VARIABLE_DECL_LIST BLOCK */
  if (IsKeyword(*word_, KeywordAttribute::kProcedure)) {
    Advance();
    if (IsIdentifier(*word_)) {
      const std::string& identifier_attr =
          static_cast<const IdentifierToken&>(*word_).GetAttribute();
      if (symtable_.IsDeclared(identifier_attr, current_env_)) {
        ReportMultiplyDefinedIdentifier(identifier_attr);
      } else {
        symtable_.Install(identifier_attr, current_env_,
                          ExpressionType::kProcedure);
        current_env_ = identifier_attr;
        formal_parm_position_ = 0;
      }
      Advance();
      if (IsPunctuation(*word_, PunctuationAttribute::kOpenBracket)) {
        Advance();
        if (ParseProcedureArgs()) {
          if (IsPunctuation(*word_, PunctuationAttribute::kCloseBracket)) {
            Advance();
            if (ParseVariableDeclList() && ParseBlock()) {
              current_env_ = main_env_;
              return true;
            } else {
              return false;
            }
          } else {
            ReportSyntaxError("')'", *word_);
            return false;
          }
        } else {
          return false;
        }
      } else {
        ReportSyntaxError("'('", *word_);
        return false;
      }
    } else {
      ReportSyntaxError("identifier", *word_);
      return false;
    }
  } else {
    ReportSyntaxError("keyword 'procedure'", *word_);
    return false;
  }

  return false;
}

bool TopdownParser::ParseProcedureArgs() {
  /* PROCEDURE_ARGS -> FORMAL_PARM_LIST */
  if (IsIdentifier(*word_)) {
    parsing_formal_parm_list_ = true;
    if (ParseFormalParmList()) {
      parsing_formal_parm_list_ = false;
      return true;
    } else {
      return false;
    }
    /* PROCEDURE_ARGS -> lambda */
  } else {
    return true;
  }

  return false;
}

bool TopdownParser::ParseFormalParmList() {
  /* FORMAL_PARM_LIST ->
     identifier IDENTIFIER_LIST_PRM : STANDARD_TYPE FORMAL_PARM_LIST_HAT */
  if (IsIdentifier(*word_)) {
    const std::string& identifier_attr =
        static_cast<const IdentifierToken&>(*word_).GetAttribute();
    if (symtable_.IsDeclared(identifier_attr, current_env_)) {
      ReportMultiplyDefinedIdentifier(identifier_attr);
    } else {
      symtable_.Install(identifier_attr, current_env_, ExpressionType::kUnknown,
                   formal_parm_position_);
      ++formal_parm_position_;
    }
    Advance();
    if (ParseIdentifierListPrm()) {
      if (IsPunctuation(*word_, PunctuationAttribute::kColon)) {
        ExpressionType standard_type_type = ExpressionType::kGarbage;
        Advance();
        if (ParseStandardType(&standard_type_type)) {
          symtable_.UpdateType(standard_type_type);
          return ParseFormalParmListHat();
        } else {
          return false;
        }
      } else {
        ReportSyntaxError("':'", *word_);
        return false;
      }
    } else {
      return false;
    }
  } else {
    ReportSyntaxError("identifier", *word_);
    return false;
  }

  return false;
}

bool TopdownParser::ParseFormalParmListHat() {
  /* FORMAL_PARM_LIST_HAT -> ; FORMAL_PARM_LIST */
  if (IsPunctuation(*word_, PunctuationAttribute::kSemicolon)) {
    Advance();
    return ParseFormalParmList();
    /* FORMAL_PARM_LIST_HAT = lambda */
  } else {
    return true;
  }

  return false;
}

bool TopdownParser::ParseStmtList() {
  /* STMT_LIST -> STMT ; STMT_LIST_PRM */
  if (IsIdentifier(*word_)
      || IsKeyword(*word_, KeywordAttribute::kIf)
      || IsKeyword(*word_, KeywordAttribute::kWhile)
      || IsKeyword(*word_, KeywordAttribute::kPrint)) {
    if (ParseStmt()) {
      if (IsPunctuation(*word_, PunctuationAttribute::kSemicolon)) {
        Advance();
        return ParseStmtListPrm();
      } else {
        ReportSyntaxError("';'", *word_);
        return false;
      }
    } else {
      return false;
    }
    /* STMT_LIST -> ; STMT_LIST_PRM */
  } else if (IsPunctuation(*word_, PunctuationAttribute::kSemicolon)) {
    Advance();
    return ParseStmtListPrm();
  }

  return false;
}

bool TopdownParser::ParseStmtListPrm() {
  /* STMT_LIST_PRM -> STMT ; STMT_LIST_PRM */
  if (IsIdentifier(*word_)
      || IsKeyword(*word_, KeywordAttribute::kIf)
      || IsKeyword(*word_, KeywordAttribute::kWhile)
      || IsKeyword(*word_, KeywordAttribute::kPrint)) {
    if (ParseStmt()) {
      if (IsPunctuation(*word_, PunctuationAttribute::kSemicolon)) {
        Advance();
        return ParseStmtListPrm();
      } else {
        ReportSyntaxError("';'", *word_);
        return false;
      }
    } else {
      return false;
    }
    /* STMT_LIST_PRM -> lambda */
  } else {
    return true;
  }

  return false;
}

bool TopdownParser::ParseStmt() {
  /* STMT -> IF_STMT */
  if (IsKeyword(*word_, KeywordAttribute::kIf)) {
    return ParseIfStmt();
    /* STMT -> WHILE_STMT */
  } else if (IsKeyword(*word_, KeywordAttribute::kWhile)) {
    return ParseWhileStmt();
    /* STMT -> PRINT_STMT */
  } else if (IsKeyword(*word_, KeywordAttribute::kPrint)) {
    return ParsePrintStmt();
    /* STMT -> identifier ADHOC_AS_PC_TAIL */
  } else if (IsIdentifier(*word_)) {
    const std::string& identifier_attr =
        static_cast<const IdentifierToken&>(*word_).GetAttribute();
    if (!symtable_.IsDeclared(identifier_attr, current_env_)) {
      ReportUndeclaredIdentifier(identifier_attr);
    } else {
      procedure_name_ = identifier_attr;
    }
    Advance();
    ExpressionType adhoc_as_pc_tail_type = ExpressionType::kGarbage;
    if (ParseAdhocAsPcTail(&adhoc_as_pc_tail_type)) {
      ExpressionType identifier_type =
          symtable_.GetType(identifier_attr, current_env_);
      if (adhoc_as_pc_tail_type != identifier_type) {
        ReportTypeError(identifier_type, adhoc_as_pc_tail_type);
      }
      return true;
    } else {
      return false;
    }
  }

  return false;
}

bool TopdownParser::ParseAdhocAsPcTail(ExpressionType* adhoc_as_pc_tail_type) {
  /* ADHOC_AS_PC_TAIL -> := EXPR */
  if (IsPunctuation(*word_, PunctuationAttribute::kAssignment)) {
    ExpressionType expr_type_result = ExpressionType::kGarbage;
    Advance();
    if (ParseExpr(&expr_type_result)) {
      *adhoc_as_pc_tail_type = expr_type_result;
      return true;
    } else {
      return false;
    }
  /* ADHOC_AS_PC_TAIL -> ( EXPR_LIST ) */
  } else if (IsPunctuation(*word_, PunctuationAttribute::kOpenBracket)) {
    ExpressionType procedure_type =
        symtable_.GetType(procedure_name_, main_env_);
    if (procedure_type != ExpressionType::kProcedure) {
      ReportTypeError(ExpressionType::kProcedure, procedure_type);
    }
    actual_parm_position_ = 0;
    Advance();
    if (ParseExprList()) {
      if (IsPunctuation(*word_, PunctuationAttribute::kCloseBracket)) {
        *adhoc_as_pc_tail_type = ExpressionType::kProcedure;
        Advance();
        return true;
      } else {
        ReportSyntaxError("')'", *word_);
        return false;
      }
    } else {
      return false;
    }
  }

  return false;
}

bool TopdownParser::ParseIfStmt() {
  /* IF_STMT -> if EXPR then BLOCK IF_STMT_HAT */
  if (IsKeyword(*word_, KeywordAttribute::kIf)) {
    Advance();
    ExpressionType expr_type_result = ExpressionType::kGarbage;
    if (ParseExpr(&expr_type_result)) {
      if (expr_type_result != ExpressionType::kBool) {
        ReportTypeError(ExpressionType::kBool, expr_type_result);
      }
      if (IsKeyword(*word_, KeywordAttribute::kThen)) {
        Advance();
        return ParseBlock() && ParseIfStmtHat();
      } else {
        ReportSyntaxError("keyword 'then'", *word_);
        return false;
      }
    } else {
      return false;
    }
  } else {
    ReportSyntaxError("keyword 'if'", *word_);
    return false;
  }

  return false;
}

bool TopdownParser::ParseIfStmtHat() {
  /* IF_STMT_HAT -> else BLOCK */
  if (IsKeyword(*word_, KeywordAttribute::kElse)) {
    Advance();
    return ParseBlock();
    /* IF_STMT_HAT -> lambda */
  } else {
    return true;
  }

  return false;
}

bool TopdownParser::ParseWhileStmt() {
  /* WHILE_STMT -> while EXPR loop BLOCK */
  if (IsKeyword(*word_, KeywordAttribute::kWhile)) {
    Advance();
    ExpressionType expr_type_result = ExpressionType::kGarbage;
    if (ParseExpr(&expr_type_result)) {
      if (expr_type_result != ExpressionType::kBool) {
        ReportTypeError(ExpressionType::kBool, expr_type_result);
      }
      if (IsKeyword(*word_, KeywordAttribute::kLoop)) {
        Advance();
        return ParseBlock();
      } else {
        ReportSyntaxError("keyword 'loop'", *word_);
        return false;
      }
    } else {
      return false;
    }
  } else {
    ReportSyntaxError("keyword 'while'", *word_);
    return false;
  }

  return false;
}

bool TopdownParser::ParsePrintStmt() {
  /* PRINT_STMT -> print EXPR */
  if (IsKeyword(*word_, KeywordAttribute::kPrint)) {
    Advance();
    ExpressionType expr_type_result = ExpressionType::kGarbage;
    if (ParseExpr(&expr_type_result)) {
      if (expr_type_result != ExpressionType::kInt
          && expr_type_result != ExpressionType::kBool) {
        ReportTypeError(ExpressionType::kInt, ExpressionType::kBool,
                        expr_type_result);
      }
      return true;
    } else {
      return false;
    }
  } else {
    ReportSyntaxError("keyword 'print'", *word_);
    return false;
  }

  return false;
}

bool TopdownParser::ParseExprList() {
  /* EXPR_LIST -> ACTUAL_PARM_LIST */
  if (IsIdentifier(*word_)
      || IsNumber(*word_)
      || IsPunctuation(*word_, PunctuationAttribute::kOpenBracket)
      || IsAddop(*word_, AddOperatorAttribute::kAdd)
      || IsAddop(*word_, AddOperatorAttribute::kSubtract)
      || IsKeyword(*word_, KeywordAttribute::kNot)) {
    return ParseActualParmList();
    /* EXPR_LIST -> lambda */
  } else {
    return true;
  }

  return false;
}

bool TopdownParser::ParseActualParmList() {
  /* ACTUAL_PARM_LIST -> EXPR ACTUAL_PARM_LIST_HAT */
  ExpressionType expr_type_result = ExpressionType::kGarbage;
  if (ParseExpr(&expr_type_result)) {
    ExpressionType expected_type =
        symtable_.GetType(procedure_name_, actual_parm_position_);
    if (expr_type_result != expected_type) {
      ReportTypeError(expected_type, expr_type_result);
    }
    ++actual_parm_position_;
    return ParseActualParmListHat();
  }

  return false;
}

bool TopdownParser::ParseActualParmListHat() {
  /* ACTUAL_PARM_LIST_HAT -> , ACTUAL_PARM_LIST */
  if (IsPunctuation(*word_, PunctuationAttribute::kComma)) {
    Advance();
    return ParseActualParmList();
    /* ACTUAL_PARM_LIST_HAT -> lambda */
  } else {
    return true;
  }

  return false;
}

bool TopdownParser::ParseExpr(ExpressionType* expr_type_result) {
  /* EXPR -> SIMPLE_EXPR EXPR_HAT */
  ExpressionType simple_expr_type = ExpressionType::kGarbage;
  ExpressionType expr_hat_type = ExpressionType::kGarbage;
  if (ParseSimpleExpr(&simple_expr_type) && ParseExprHat(&expr_hat_type)) {
    if (expr_hat_type == ExpressionType::kNo) {
      *expr_type_result = simple_expr_type;
    } else if (simple_expr_type == ExpressionType::kInt
               && expr_hat_type == ExpressionType::kInt) {
      *expr_type_result = ExpressionType::kBool;
    } else {
      ReportTypeError(ExpressionType::kInt, simple_expr_type, expr_hat_type);
    }

    return true;
  }

  return false;
}

bool TopdownParser::ParseExprHat(ExpressionType* expr_hat_type) {
  /* EXPR_HAT -> relop SIMPLE_EXPR */
  if (IsRelop(*word_)) {
    Advance();
    ExpressionType simple_expr_type = ExpressionType::kGarbage;
    if (ParseSimpleExpr(&simple_expr_type)) {
      if (simple_expr_type == ExpressionType::kInt) {
        *expr_hat_type = ExpressionType::kInt;
      } else {
        ReportTypeError(ExpressionType::kInt, simple_expr_type);
      }
      return true;
    } else {
      return false;
    }
    /* EXPR_HAT -> lambda */
  } else {
    *expr_hat_type = ExpressionType::kNo;
    return true;
  }

  return false;
}

bool TopdownParser::ParseSimpleExpr(ExpressionType* simple_expr_type) {
  /* SIMPLE_EXPR -> TERM SIMPLE_EXPR_PRM */
  ExpressionType term_type = ExpressionType::kGarbage;
  ExpressionType simple_expr_prm_type = ExpressionType::kGarbage;
  if (ParseTerm(&term_type) && ParseSimpleExprPrm(&simple_expr_prm_type)) {
    if (simple_expr_prm_type == ExpressionType::kNo) {
      *simple_expr_type = term_type;
    } else if (term_type == simple_expr_prm_type) {
      *simple_expr_type = term_type;
    } else {
      ReportTypeError(term_type, simple_expr_prm_type);
    }
    return true;
  }

  return false;
}

bool TopdownParser::ParseSimpleExprPrm(ExpressionType* simple_expr_prm0_type) {
  /* SIMPLE_EXPR_PRM -> addop TERM SIMPLE_EXPR_PRM */
  if (IsAddop(*word_)) {
    ExpressionType addop_type = ExpressionType::kGarbage;
    AddOperatorAttribute addop_attr =
        static_cast<const AddOperatorToken&>(*word_).GetAttribute();
    if (addop_attr == AddOperatorAttribute::kAdd
        || addop_attr == AddOperatorAttribute::kSubtract) {
      addop_type = ExpressionType::kInt;
    } else {
      addop_type = ExpressionType::kBool;
    }
    ExpressionType term_type = ExpressionType::kGarbage;
    ExpressionType simple_expr_prm1_type = ExpressionType::kGarbage;
    Advance();
    if (ParseTerm(&term_type) && ParseSimpleExprPrm(&simple_expr_prm1_type)) {
      if (simple_expr_prm1_type == ExpressionType::kNo) {
        if (addop_type == term_type) {
          *simple_expr_prm0_type = addop_type;
        } else {
          ReportTypeError(addop_type, term_type);
        }
      } else if (addop_type == term_type &&
                 term_type == simple_expr_prm1_type) {
        *simple_expr_prm0_type = addop_type;
      } else {
        ReportTypeError(addop_type, term_type, simple_expr_prm1_type);
      }
      return true;
    } else {
      return false;
    }
    /* SIMPLE_EXPR_PRM -> lambda */
  } else {
    *simple_expr_prm0_type = ExpressionType::kNo;
    return true;
  }

  return false;
}

bool TopdownParser::ParseTerm(ExpressionType* term_type) {
  /* TERM -> FACTOR TERM_PRM */
  ExpressionType factor_type = ExpressionType::kGarbage;
  ExpressionType term_prm_type = ExpressionType::kGarbage;
  if (ParseFactor(&factor_type)) {
    if (ParseTermPrm(&term_prm_type)) {
      if (term_prm_type == ExpressionType::kNo) {
        *term_type = factor_type;
      } else if (factor_type == term_prm_type) {
        *term_type = factor_type;
      } else {
        ReportTypeError(factor_type, term_prm_type);
      }
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }

  return false;
}

bool TopdownParser::ParseTermPrm(ExpressionType* term_prm0_type) {
  /* TERM_PRM -> mulop FACTOR TERM_PRM */
  if (IsMulop(*word_)) {
    ExpressionType mulop_type = ExpressionType::kGarbage;
    MulOperatorAttribute mulop_attr = MulOperatorAttribute::kUnspecified;
    mulop_attr = static_cast<const MulOperatorToken&>(*word_).GetAttribute();
    if (mulop_attr == MulOperatorAttribute::kMultiply
        || mulop_attr == MulOperatorAttribute::kDivide) {
      mulop_type = ExpressionType::kInt;
    } else {
      mulop_type = ExpressionType::kBool;
    }
    ExpressionType factor_type = ExpressionType::kGarbage;
    ExpressionType term_prm1_type = ExpressionType::kGarbage;
    Advance();
    if (ParseFactor(&factor_type) && ParseTermPrm(&term_prm1_type)) {
      if (term_prm1_type == ExpressionType::kNo && mulop_type == factor_type) {
        *term_prm0_type = mulop_type;
      } else if (mulop_type == factor_type && factor_type == term_prm1_type) {
        *term_prm0_type = mulop_type;
      } else if (term_prm1_type == ExpressionType::kNo) {
        ReportTypeError(mulop_type, factor_type);
      } else {
        ReportTypeError(mulop_type, factor_type, term_prm1_type);
      }
      return true;
    } else {
      return false;
    }
    /* TERM_PRM -> lambda */
  } else {
    *term_prm0_type = ExpressionType::kNo;
    return true;
  }

  return false;
}

bool TopdownParser::ParseFactor(ExpressionType* factor0_type) {
  /* FACTOR -> identifier */
  if (IsIdentifier(*word_)) {
    const std::string& identifier_attr =
        static_cast<const IdentifierToken&>(*word_).GetAttribute();
    if (!symtable_.IsDeclared(identifier_attr, current_env_)) {
      ReportUndeclaredIdentifier(identifier_attr);
    } else {
      *factor0_type = symtable_.GetType(identifier_attr, current_env_);
    }
    Advance();
    return true;
    /* FACTOR -> num */
  } else if (IsNumber(*word_)) {
    *factor0_type = ExpressionType::kInt;
    Advance();
    return true;
    /* FACTOR -> ( EXPR ) */
  } else if (IsPunctuation(*word_, PunctuationAttribute::kOpenBracket)) {
    Advance();
    ExpressionType expr_type_result = ExpressionType::kGarbage;
    if (ParseExpr(&expr_type_result)) {
      if (IsPunctuation(*word_, PunctuationAttribute::kCloseBracket)) {
        *factor0_type = expr_type_result;
        Advance();
        return true;
      } else {
        ReportSyntaxError("')'", *word_);
        return false;
      }
    } else {
      return false;
    }
    /* FACTOR -> SIGN FACTOR */
  } else if (IsAddop(*word_, AddOperatorAttribute::kAdd)
             || IsAddop(*word_, AddOperatorAttribute::kSubtract)
             || IsKeyword(*word_, KeywordAttribute::kNot)) {
    ExpressionType sign_type = ExpressionType::kGarbage;
    ExpressionType factor1_type = ExpressionType::kGarbage;
    if (ParseSign(&sign_type) && ParseFactor(&factor1_type)) {
      if (sign_type != factor1_type) {
        ReportTypeError(sign_type, factor1_type);
      } else {
        *factor0_type = factor1_type;
      }
      return true;
    } else {
      return false;
    }
  }

  return false;
}

bool TopdownParser::ParseSign(ExpressionType* sign_type) {
  /* SIGN -> + */
  if (IsAddop(*word_, AddOperatorAttribute::kAdd)) {
    *sign_type = ExpressionType::kInt;
    Advance();
    return true;
    /* SIGN -> - */
  } else if (IsAddop(*word_, AddOperatorAttribute::kSubtract)) {
    *sign_type = ExpressionType::kInt;
    Advance();
    return true;
    /* SIGN -> not */
  } else if (IsKeyword(*word_, KeywordAttribute::kNot)) {
    *sign_type = ExpressionType::kBool;
    Advance();
    return true;
  }

  return false;
}

}  // namespace internal
}  // namespace truplc
