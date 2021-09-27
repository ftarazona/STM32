.syntax unified
.arch armv7-m
.cpu cortex-m4
.thumb

.global _start

.equ GPIOB, 0x48000400

_start:
	ldr r0, =GPIOB
	ldr r1, [r0]
	orr r1, r1, #0x100000000
	str r1, [r0]
end:
	bl switch_led
	b end

switch_led:
	ldr r1, [r0, #0x14]
	and r2, r1, #0x00004000
	cmp r2, #0
	bne turn_off /* if turned on */
turn_on:
	orr r1, r1, #0x00004000
	b refresh_led
turn_off:
	and r1, r1, #0xffffbfff
refresh_led:
	str r1, [r0, #0x14]
	bx lr
