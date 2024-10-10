#include <AttrAction/JITAttributeAction.hpp>

#include <helpers.hpp>

#include <clang/AST/ASTConsumer.h>
#include <clang/Frontend/CompilerInstance.h>

JITASTConsumer::JITASTConsumer(clang::CompilerInstance &CI,
                               clang::ASTContext &Context)
    : VisitorAttr{CI, Context}, VisitorDecl{CI, Context},
      VisitorCall{CI, Context} {}

void JITASTConsumer::HandleTranslationUnit(clang::ASTContext &Context) {
  _jit::log_debug() << "Entering JITASTConsumer::HandleTranslationUnit.\n";
  VisitorAttr.TraverseDecl(Context.getTranslationUnitDecl());
  // VisitorDecl.TraverseDecl(Context.getTranslationUnitDecl());
  // VisitorCall.TraverseDecl(Context.getTranslationUnitDecl());
  _jit::log_debug() << "Exiting JITASTConsumer::HandleTranslationUnit.\n";
}

// Register the custom attribute in the plugin action.
bool JITAttributeAction::ParseArgs(const clang::CompilerInstance &CI,
                                   const std::vector<std::string> &args) {
  _jit::log_debug() << "PluginASTAction correctly registered\n";
  return true;
}

std::unique_ptr<clang::ASTConsumer>
JITAttributeAction::CreateASTConsumer(clang::CompilerInstance &CI,
                                      llvm::StringRef) {
  return std::make_unique<JITASTConsumer>(CI, CI.getASTContext());
}

clang::PluginASTAction::ActionType JITAttributeAction::getActionType() {
  return AddBeforeMainAction;
}
