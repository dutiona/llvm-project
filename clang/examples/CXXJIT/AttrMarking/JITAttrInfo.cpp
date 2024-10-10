#include "clang/Basic/DiagnosticSema.h"
#include "clang/Sema/ParsedAttr.h"
#include <AttrMarking/JITAttrInfo.hpp>

#include <JITRegistry.hpp>
#include <helpers.hpp>

#include <clang/AST/Attr.h>
#include <clang/AST/Expr.h>
#include <clang/AST/Stmt.h>
#include <clang/Basic/DiagnosticFrontend.h>
#include <clang/Basic/ParsedAttrInfo.h>
#include <clang/Sema/Sema.h>
#include <llvm/Support/Casting.h>

namespace _jit {

JITAttrInfo::JITAttrInfo() : ParsedAttrInfo() {
  OptArgs = 0;
  // IsStmt = true;
  // AttrKind = clang::AttributeCommonInfo::NoSemaHandlerAttribute;

  static constexpr Spelling S[] = {{clang::ParsedAttr::AS_GNU, "jit"},
                                   {clang::ParsedAttr::AS_C23, "jit"},
                                   {clang::ParsedAttr::AS_CXX11, "jit"},
                                   {clang::ParsedAttr::AS_CXX11, "clang::jit"}};
  Spellings = S;
}

// Decl can be a function decl marked with JIT like
// template <int I> [[jit]] void foo(int a) { return a + I; }
// if (D->isFunctionOrFunctionTemplate()) {
// auto &os = _jit::log_debug()
//            << "Detecting function or function template...\n";
// D->print(os);
// os << "\n";

//_jit::FunctionsMarkedToJIT().emplace(D->getID(), nullptr);
//  return true;
//}

// return false;

// S.Diag(Attr.getLoc(), clang::diag::warn_attribute_wrong_decl_type)
//     << Attr << clang::ExpectedFunction
//     << " function template [JITAttrInfo::diagAppertainsToDecl]";

// else it can be a variable declaration, but it must be initialized at the
// same time
// if (!D->hasBody()) {
//  auto &os = _jit::log_debug()
//             << "Ignoring attr on a decl without a body...\n";
//  D->print(os);
//  os << "\n";
//
//  // S.Diag(Attr.getLoc(), clang::diag::warn_attribute_wrong_decl_type)
//  //     << Attr << clang::ExpectedVariableOrFunction
//  //     << ": no body for this declaration!";
//  return false;
//}

//_jit::log_debug() << "Top level...\n";
//_jit::pretty_print_stmt(D->getBody(), llvm::outs());

// We look for the callexpr inside the declaration that are related to JIT
// [[jit]] auto b = bar(f(42, test<I>(...))
// We're looking for test<I>(...) in particular
// auto callexprs_to_jit =
//    extract_templated_callexpr_to_jit_in_stmt(D->getBody());
// if (!callexprs_to_jit.empty()) {
//  for (auto *callexpr : callexprs_to_jit) {
//    _jit::CallerExprsMarkedToJIT().emplace(
//        callexpr->getID(D->getASTContext()), nullptr);
//  }
//  /*
//  for (auto *callexpr : callexpr_to_jit) {
//    auto *fdecl =
//        llvm::dyn_cast<clang::FunctionDecl>(callexpr->getCalleeDecl());
//    if (!fdecl) {
//      _jit::log_error() << "Wrong fdecl extracted from callexpr! Most likely
//      "
//                           "internal bug.";
//      _jit::pretty_print_stmt(callexpr, llvm::errs());
//    } else {
//      _jit::FunctionsMarkedToJIT().emplace(fdecl->getID(), nullptr);
//    }
//  }
//  */
//  return true;
//}

// S.Diag(Attr.getLoc(), clang::diag::warn_attribute_wrong_decl_type)
//     << Attr << clang::ExpectedVariableOrFunction;

// return false;

bool JITAttrInfo::diagAppertainsToDecl(clang::Sema &S,
                                       const clang::ParsedAttr &Attr,
                                       const clang::Decl *D) const {
  _jit::DeclMarkedForJIT().emplace(
      D->getID(), nullptr /* to be filled during AST traversal */);
  auto &os = _jit::log_debug() << "Decl marked for jit:";
  _jit::pretty_print_decl(D, os);
  return true;
}

bool JITAttrInfo::diagAppertainsToStmt(clang::Sema &S,
                                       const clang::ParsedAttr &Attr,
                                       const clang::Stmt *St) const {

  //_jit::StmtMarkedForJIT().emplace(
  //    St->getID(S.getASTContext()),
  //    nullptr /* to be filled during AST traversal */);
  // auto &os = _jit::log_debug() << "Stmt marked for jit:";
  //_jit::pretty_print_stmt(St, os);
  // return true;

  return false;
}

clang::ParsedAttrInfo::AttrHandling
JITAttrInfo::handleDeclAttribute(clang::Sema &S, clang::Decl *D,
                                 const clang::ParsedAttr &Attr) const {

  if (D->isFunctionOrFunctionTemplate()) {
    auto *FTDecl = clang::cast<clang::FunctionTemplateDecl>(D);
    clang::FunctionDecl *FDecl = FTDecl->getTemplatedDecl();

    _jit::log_debug() << "Function <" << FTDecl->getNameAsString() << ":"
                      << FTDecl->getID() << "/" << FTDecl << "/" << FDecl
                      << "> ("
                      << FTDecl->getLocation().printToString(
                             S.getSourceManager())
                      << "): " << "Marked with [[jit]] attribute.\n";
    _jit::FunctionsMarkedToJIT().emplace(FTDecl->getID(),
                                         FDecl /* can be filled here */);
    // no duplicate
    if (_jit::DeclMarkedForJIT().contains(FTDecl->getID())) {
      DeclMarkedForJIT().erase(FTDecl->getID());
    }
  }
  return AttributeApplied;
}

} // namespace _jit
