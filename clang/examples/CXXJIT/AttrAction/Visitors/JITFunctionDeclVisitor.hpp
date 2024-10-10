#pragma once

#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/CompilerInstance.h>

/// Visitor that detects and processes functions marked with [[jit]].
class JITFunctionDeclVisitor
    : public clang::RecursiveASTVisitor<JITFunctionDeclVisitor> {
public:
  explicit JITFunctionDeclVisitor(clang::CompilerInstance &CI,
                                  clang::ASTContext &Context);

  bool VisitFunctionDecl(clang::FunctionDecl *FD);

private:
  clang::ASTContext &Context;
  clang::CompilerInstance &CI;
};
