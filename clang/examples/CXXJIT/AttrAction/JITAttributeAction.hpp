#pragma once

#include <AttrAction/Visitors/JITAttrStmtDeclVisitor.hpp>
#include <AttrAction/Visitors/JITFunctionCallVisitor.hpp>
#include <AttrAction/Visitors/JITFunctionDeclVisitor.hpp>

#include <clang/Frontend/FrontendAction.h>

#include <memory>

/// Custom attribute handler for [[jit]]
class JITASTConsumer : public clang::ASTConsumer {
public:
  explicit JITASTConsumer(clang::CompilerInstance &CI,
                          clang::ASTContext &Context);

  void HandleTranslationUnit(clang::ASTContext &Context) override;

private:
  JITAttrStmtDeclVisitor VisitorAttr;
  JITFunctionDeclVisitor VisitorDecl;
  JITFunctionCallVisitor VisitorCall;
};

class JITAttributeAction : public clang::PluginASTAction {
protected:
  // Register the custom attribute in the plugin action.
  bool ParseArgs(const clang::CompilerInstance &CI,
                 const std::vector<std::string> &args) override;

  std::unique_ptr<clang::ASTConsumer>
  CreateASTConsumer(clang::CompilerInstance &CI, llvm::StringRef) override;

  PluginASTAction::ActionType getActionType() override;
};
