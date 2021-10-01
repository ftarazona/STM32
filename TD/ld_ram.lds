MEMORY	{
	flash (R) : ORIGIN = 0x08000000, LENGTH = 1M
	sram1 (WX) : ORIGIN = 0x20000000, LENGTH = 96K
	sram2 (W) : ORIGIN = 0x10000000, LENGTH = 32K
}

ENTRY(_start)

SECTIONS	{
	.text :	{
		_text = . ;
		*(.text)
		_etext = . ;
	} > sram1

	.rodata :	{
		_rodata = . ;
		*(.rodata)
		_erodata = . ;
	} > sram1

	.data : {
		_data = . ;
		*(.data)
		_edata = . ;
	} > sram1

	.bss :	{
		_bss = . ;
		*(.bss) *(COM*)
		_ebss = . ;
	} > sram1
}

_stack = ORIGIN(sram2) + LENGTH(sram2) ;

