.syntax unified
.arch armv7-m
.cpu cortex-m4
.thumb

.thumb_func 
.global _start

/* _start is the entry point (cf. ld_ram.lds).
   It initializes the stack pointer, then zero out .bss.
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
