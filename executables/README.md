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

First of all we focus on "base dump" files (const char msg[])
By disassembling we can see that O0 uses the frame pointer whereas O1 or higher do not. O1 pushes more registers (r4, r5, r6, lr) in order to reduce the number of instructions required. O0 uses less registers to process, so it has more instructions to do in order to free some required registers.
O2 adds a text.startup subsection, but the content of the code remains identical to O1.
Os (speed optim) pushes even more registers, so that it doesn't have to decrement the stack pointer on instruction 1c.

Now we focus on "static dump" (static const char msg[])
For O0, it is identical to "base dump".
For O1, O2, Os, the section .rodata is removed when static is added. The static variable is visible only in this file. When non-static, maybe the compiler adds some information in .rodata so that when linking, other files can have access to the variable.
When indicating static, the compiler then know it doesn't have to add this section.

Now we focus on "pointer dump" (const char\* msg)
For O0, we notice that the size of .text and .data is increased by four octet. .rodata size is 10 less than "base dump". In .text, we notice that up to now, printf(mesg) was translated to puts(mesg). I suppose that it is done because mesg has a fixed size AND is terminated by '\n'.
Effectively, the second printf has a variable size string in argument (a number can be several digit long) and is translated by a printf. Moreover when removing '\n' from mesg, printf remains printf.
My guess is that when a pointer is used instead of an array, the compiler can not deduce these two conditions, so printf is not translated in puts.
Just before jumping to the first printf, the string is first stored in r3 then moved to r0.
With O1, the string is immediately stored in r0.

