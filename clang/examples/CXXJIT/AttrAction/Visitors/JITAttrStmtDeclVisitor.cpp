#include "JITRegistry.hpp"
#include <AttrAction/Visitors/JITAttrStmtDeclVisitor.hpp>

#include <helpers.hpp>

JITAttrStmtDeclVisitor::JITAttrStmtDeclVisitor(clang::CompilerInstance &CI,
                                               clang::ASTContext &Context)
    : CI{CI}, Context{Context} {}

bool JITAttrStmtDeclVisitor::VisitVarDecl(const clang::VarDecl *VD) {
  if (_jit::DeclMarkedForJIT().contains(VD->getID())) {
    auto &os = _jit::log_debug()
               << "JITAttrStmtDeclVisitor::VisitVarDecl TRUE <"
               << VD->getNameAsString() << ">\n";

    if (!VD->hasInit()) {
      os << "Ignoring as there is no init body...";
    }

    auto *initStmt = VD->getInit();
    auto callexprs = _jit::extract_templated_callexpr_to_jit_in_stmt(initStmt);
    if (!callexprs.empty()) {
      for (auto *callexpr : callexprs) {
        os << "CallerExpr marked for JIT";
        _jit::pretty_print_stmt(callexpr, os);

        _jit::CallerExprsMarkedToJIT().emplace(callexpr->getID(Context),
                                               nullptr);
      }
    }
  }

  return true;
}

bool JITAttrStmtDeclVisitor::VisitDeclStmt(const clang::DeclStmt *DS) {
  if (_jit::DeclMarkedForJIT().contains(DS->getID(Context))) {
    auto &os = _jit::log_debug()
               << "[JIT PLUGIN] JITAttrStmtDeclVisitor::VisitDeclStmt TRUE <";
    _jit::pretty_print_stmt(DS, os);
    os << ">\n";
  }

  return true;
}

bool JITAttrStmtDeclVisitor::VisitAttributedStmt(
    const clang::AttributedStmt *AS) {
  if (_jit::DeclMarkedForJIT().contains(AS->getID(Context))) {
    auto &os =
        _jit::log_debug()
        << "[JIT PLUGIN] JITAttrStmtDeclVisitor::VisitAttributedStmt TRUE <";
    _jit::pretty_print_stmt(AS, os);
    os << ">\n";
  }

  return true;
}
