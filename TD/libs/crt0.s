.syntax unified
.arch armv7-m
.cpu cortex-m4
.thumb

.global _start

_start:
	ldr r0, =_stack
	mov sp, r0

	b main

_exit:
	b _exit
