/* first asm code */
     .syntax	unified
	.cpu cortex-m0

     .text


     .thumb
     .thumb_func
     .align 2
     .globl   delay_asm
     .type    delay_asm, %function

delay_asm:
     loop:
     nop
     subs r0, 1
     bne loop
     bx lr

	.end

