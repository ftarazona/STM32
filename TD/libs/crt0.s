.syntax unified
.arch armv7-m
.cpu cortex-m4
.thumb

.thumb_func 
.global _start

/* _start initializes the stack pointer, then zero out .bss.
   It then jumps to main.
   Finally, in case main returns, an endless loop assures our controller
    don't go dumb. */
_start:
	//Careful here, use bl for returning
	bl init_nvic
	bl init_bss
	bl init_data

	bl main

_exit:
	b _exit

.section .xiptext, "x"
.thumb_func
.global _textcpy

/* _textcpy is the entry point.
   It copies .text in RAM and then jump to _start, which is the
   beginning of the program. */
_textcpy:
	bl init_text
	/* No need to save context, as we never come back to _textcpy
	   A b instruction could not reach _start which is more than
	   0x10000000 further than _textcpy. */
	ldr r0, =_start
	mov pc, r0
