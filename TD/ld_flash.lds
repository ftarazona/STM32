/* We have two zones : the flash and the sram, which is divided in two
   parts. */
MEMORY	{
	flash (R) : ORIGIN = 0x08000000, LENGTH = 1M
	sram1 (WX) : ORIGIN = 0x20000000, LENGTH = 96K
	sram2 (W) : ORIGIN = 0x10000000, LENGTH = 32K
}

/* _start makes some necessary initializations before executing main. */
ENTRY(_textcpy)

SECTIONS	{
	.nvic	:	{
		_nvic = . ;
		*(.nvic)
		_envic = . ;
	} > sram1 AT> flash

	.xiptext :	{
		_xiptext = . ;
		*(.xiptext)
		_exiptext = . ;
	} > flash

	.text :	{
		_text = . ;
		*(.text)
		_etext = . ;
	} > sram1 AT> flash

	.rodata :	{
		_rodata = . ;
		*(.rodata)
		_erodata = . ;
	} > flash

	.data :	{
		_data = . ;
		*(.data)
		_edata = . ;
	} > sram1 AT> flash

	.bss :	{
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
