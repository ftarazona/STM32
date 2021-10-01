# Cross compilation exercises

These exercises test compilation toolchain knowledge.

## Exercise 1 : COMMON section

The purpose is to understand how the linker will treat variables in COMMON section.
When adding another variable y1 (size 2o), the address of y1 is 2. Same with a char.
It seems the address is actually the size of the variable.
The manpage tells us the first symbol is not the actual address but the symbol's value.

The second numeric column actually indicates the alignment : every 4o-integer will be align on a 4o-border. Same for 2o or 1o.

## Exercise 2 : Linux Stack & Sections

In order to examine the order of sections on a Linux, we'll use objdump to see the headers. We'll use the first program as the example.
The order is .text, .data, .bss, .rodata, .comment etc.

In order to examine the stack, we print the address of local variables. The stack grows to the bottom.

## Exercise 3 : GCC optimisations

First thing to notice : optimization separates rodata in subsections, one for each literal string.
The data segment seems not to be affected.
Os and O2 move a large part of the text section after string sections.
