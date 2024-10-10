#pragma once

#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/CompilerInstance.h>

class JITFunctionCallVisitor
    : public clang::RecursiveASTVisitor<JITFunctionCallVisitor> {
public:
  explicit JITFunctionCallVisitor(clang::CompilerInstance &CI,
                                  clang::ASTContext &Context);

  bool VisitCallExpr(clang::CallExpr *Call);

private:
  // Helper function to adjust the arguments of the call for the new JitFunction
  void replaceCallArguments(clang::CallExpr *Call, clang::FunctionDecl *OldFunc,
                            clang::FunctionDecl *NewFunc);

private:
  clang::ASTContext &Context;
  clang::CompilerInstance &CI;
};
