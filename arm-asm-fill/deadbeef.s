/* r0 - r3 addresses
   r4 - r7 sizes
   r8 - r11 patterns
   */

.syntax unified
.arch armv7-m
.cpu cortex-m4
.thumb

.global _start

_start:
    ldr r0, =0x10000000
    ldr r1, =0x10000200
    ldr r2, =0x10000500
    ldr r3, =0x10000900
    ldr r4, =0x200
    ldr r5, =0x300
    ldr r6, =0x400
    ldr r7, =0x100
    ldr r8, =0xc01dcafe
    ldr r9, =0xdeadbeef
    ldr r10, =0x00000000
    ldr r11, =0xffffffff
    ldr r12, =0x0

main:
    bl fill
    mov r0, r1
    mov r4, r5
    mov r8, r9
    ldr r12, =0
    bl fill
    mov r0, r2
    mov r4, r6
    mov r8, r10
    ldr r12, =0
    bl fill
    mov r0, r3
    mov r4, r7
    mov r8, r11
    ldr r12, =0
    bl fill
    bl end
    
fill:
    str r8, [r0, r12]
    add r12, r12, #4
    cmp r12, r4
    bne fill
    bx lr

end: b end
