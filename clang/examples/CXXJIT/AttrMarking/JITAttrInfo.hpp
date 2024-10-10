#pragma once

#include <clang/Sema/ParsedAttr.h>

namespace _jit {

struct JITAttrInfo : public clang::ParsedAttrInfo {
  JITAttrInfo();

  bool diagAppertainsToDecl(clang::Sema &S, const clang::ParsedAttr &Attr,
                            const clang::Decl *D) const override;

  bool diagAppertainsToStmt(clang::Sema &S, const clang::ParsedAttr &Attr,
                            const clang::Stmt *D) const override;

  AttrHandling
  handleDeclAttribute(clang::Sema &S, clang::Decl *D,
                      const clang::ParsedAttr &Attr) const override;

  // FIXME: not supported by clang internals yet
  // clang::Attr *
  // handleStmtAttribute(clang::Sema &S, clang::Stmt *St,
  //                    const clang::ParsedAttr &Attr) const override;
};

} // namespace _jit