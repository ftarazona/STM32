/* We have two zones : the flash and the sram, which is divided in two
   parts. */
MEMORY	{
	flash (R) : ORIGIN = 0x08000000, LENGTH = 1M
	sram1 (WX) : ORIGIN = 0x20000000, LENGTH = 96K
	sram2 (W) : ORIGIN = 0x10000000, LENGTH = 32K
}

/* _start makes some necessary initializations before executing main. */
ENTRY(_start)

SECTIONS	{
	.nvic ORIGIN(sram1)	: AT(ORIGIN(flash))	{
		_nvic = . ;
		*(.nvic)
		_envic = . ;
	} > sram1

	.xiptext (LOADADDR(.nvic) + SIZEOF(.nvic)) : AT(LOADADDR(.nvic) + SIZEOF(.nvic))	{
		_xiptext = . ;
		*(.xiptext)
		_exiptext = . ;
	} > flash

	.text (ADDR(.nvic) + SIZEOF(.nvic)) : AT(LOADADDR(.text) + SIZEOF(.text))	{
		_text = . ;
		*(.text)
		_etext = . ;
	} > sram1

	.rodata (LOADADDR(.xiptext) + SIZEOF(.xiptext)) : AT(LOADADDR(.text) + SIZEOF(.text))	{
		_rodata = . ;
		*(.rodata)
		_erodata = . ;
	} > flash

	.data (ADDR(.text) + SIZEOF(.text)) : AT(LOADADDR(.rodata) + SIZEOF(.rodata)) {
		_data = . ;
		*(.data)
		_edata = . ;
	} > sram1

	.bss (ADDR(.data) + SIZEOF(.data)) : AT(ADDR(.data) + SIZEOF(.data)) 	{
		_bss = . ;
		*(.bss) *(COM*)
		_ebss = . ;
	} > sram1
}

/* The stack begins at the END of sram2 for the stack grows descending */
_stack = ORIGIN(sram2) + LENGTH(sram2) ;
_data_flash = LOADADDR(.data) ;
_nvic_flash = LOADADDR(.nvic) ;
_text_flash = LOADADDR(.text) ;
