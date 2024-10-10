#include <JITRegistry.hpp>

namespace _jit {

auto DeclMarkedForJIT() -> std::map<unsigned, clang::Decl *> & {
  static std::map<unsigned, clang::Decl *> Decls = {};
  return Decls;
}

auto StmtMarkedForJIT() -> std::map<unsigned, clang::Stmt *> & {
  static std::map<unsigned, clang::Stmt *> Stmts = {};
  return Stmts;
}

auto FunctionsMarkedToJIT() -> std::map<unsigned, clang::FunctionDecl *> & {
  static std::map<unsigned, clang::FunctionDecl *> Functions = {};
  return Functions;
}

auto CallerExprsMarkedToJIT() -> std::map<unsigned, clang::CallExpr *> & {
  static std::map<unsigned, clang::CallExpr *> CallerExprs = {};
  return CallerExprs;
}

auto FunctionsToJIT() -> std::map<unsigned, clang::FunctionDecl *> & {
  static std::map<unsigned, clang::FunctionDecl *> Functions = {};
  return Functions;
}
auto CallerExprsToJIT() -> std::map<unsigned, clang::CallExpr *> & {
  static std::map<unsigned, clang::CallExpr *> CallerExprs = {};
  return CallerExprs;
}

} // namespace _jit