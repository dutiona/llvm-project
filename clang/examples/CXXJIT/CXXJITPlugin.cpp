#include <AttrAction/JITAttributeAction.hpp>
#include <AttrMarking/JITAttrInfo.hpp>

#include <clang/Basic/ParsedAttrInfo.h>
#include <clang/Frontend/FrontendPluginRegistry.h>

static clang::ParsedAttrInfoRegistry::Add<_jit::JITAttrInfo>
    X1("cxxjit-attr-plugin", "Enable [[jit]] parsing for function template.");

static clang::FrontendPluginRegistry::Add<::JITAttributeAction>
    X2("cxxjit-ast-plugin", "Enable JITing function template.");
