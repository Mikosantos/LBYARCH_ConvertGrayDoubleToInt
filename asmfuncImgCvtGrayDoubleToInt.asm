section .data
var1 dq 255.0

section .text
bits 64
default rel

global asmImgCvtGrayDoubleToInt
extern printf

asmImgCvtGrayDoubleToInt:
	movsd xmm1, [var1]
	mulsd xmm0, xmm1
	xor rax, rax
	cvtsd2si rax, xmm0
	movsd xmm0, xmm0
	ret
	