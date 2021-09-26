.syntax unified
.arch armv7-m
.cpu cortex-m4
.thumb

.global _start

_start:
	ldr r0, =0x10000200
	ldr r1, =[mem]

main:
	bl strcpy
	b end

/* strcpy takes two arguments :
    r0 is the destination address
	r1 is the pattern address
	it modifies both by increasing until r1 points to '\0'.
	it uses r2 in order to store values temporarily.
	it takes 
*/
strcpy:
	ldr r2, [r1]
	str r2, [r0]
	add r0, r0, #4
	add r1, r1, #4
	and r2, r2, 0xff000000
	cmp r2, #0
	bne strcpy
	bx lr

end:
	b end

.balign 4
mem:
	.asciz "Hello World"
	
