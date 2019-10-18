; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc < %s -mtriple=i686-- | FileCheck %s
; PR2835

@g_407 = internal global i32 0		; <i32*> [#uses=1]
@llvm.used = appending global [1 x i8*] [ i8* bitcast (i32 ()* @main to i8*) ], section "llvm.metadata"		; <[1 x i8*]*> [#uses=0]

define i32 @main() nounwind {
; CHECK-LABEL: main:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    movl g_407, %eax
; CHECK-NEXT:    movzbl %al, %eax
; CHECK-NEXT:    pushl %eax
; CHECK-NEXT:    calll func_45
; CHECK-NEXT:    addl $4, %esp
; CHECK-NEXT:    xorl %eax, %eax
; CHECK-NEXT:    retl
entry:
	%0 = load volatile i32, i32* @g_407, align 4		; <i32> [#uses=1]
	%1 = trunc i32 %0 to i8		; <i8> [#uses=1]
	%2 = tail call i32 @func_45(i8 zeroext %1) nounwind		; <i32> [#uses=0]
	ret i32 0
}

declare i32 @func_45(i8 zeroext) nounwind
