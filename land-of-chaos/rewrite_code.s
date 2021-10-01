.syntax unified
.arch armv7-m
.cpu cortex-m4
.thumb

.global _start

_start:
	ldr r1, =0x4
	ldr r2, =0x5
	ldr r4, =0xeb010402
	mov r0, pc
	add r0, r0, #8
	str r4, [r0]
	nop
	nop
addition:
	add r3, r1, r2
end:
	b end
