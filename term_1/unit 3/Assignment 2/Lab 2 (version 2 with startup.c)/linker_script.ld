MEMORY{
	flash(RX) : ORIGIN = 0X08000000, LENGTH = 128K
	sram(RWX) : ORIGIN = 0X20000000, LENGTH = 20K
}
SECTIONS{
	.text :
	{
		*(.vectors*)
		main.o(.text*)
		startup.o(.text*)
		*(.rodata)
		_E_text = . ;
	} > flash
	.data :
	{
		_S_data = . ;
		*(.data)
		_E_data = . ;
	}> sram AT> flash

	.bss :
	{
		_S_bss = . ;
		*(.bss)
		. = ALIGN(4) ;
		_E_bss = .;

		. = ALIGN(4);
		. = . + 0x1000 ;
		stack_top = . ;
	} > sram


}