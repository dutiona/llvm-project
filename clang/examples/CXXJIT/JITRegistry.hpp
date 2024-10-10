#pragma once

#include <clang/AST/Decl.h>
#include <clang/AST/Expr.h>
#include <clang/AST/Stmt.h>

#include <map>

namespace _jit {

auto DeclMarkedForJIT() -> std::map<unsigned, clang::Decl *> &;
auto StmtMarkedForJIT() -> std::map<unsigned, clang::Stmt *> &;

auto FunctionsMarkedToJIT() -> std::map<unsigned, clang::FunctionDecl *> &;
auto CallerExprsMarkedToJIT() -> std::map<unsigned, clang::CallExpr *> &;

auto FunctionsToJIT() -> std::map<unsigned, clang::FunctionDecl *> &;
auto CallerExprsToJIT() -> std::map<unsigned, clang::CallExpr *> &;

} // namespace _jit
