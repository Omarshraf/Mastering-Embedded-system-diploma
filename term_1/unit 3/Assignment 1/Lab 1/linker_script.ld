ENTRY(reset)
MEMORY{
	mem (rwx) : ORIGIN = 0x00000000, LENGTH = 64M
}
SECTIONS
{
	. = 0X10000;
	.STARTUP . :
	{
		startup.o(.text)
	}> mem
	.text :
	{
		*(.text) *(.rodata)
	}> mem
	.data :
	{
		*(.data)
	}> mem
	.bss :
	{
		*(.bss) 
	}> mem
	. = . + 0x1000;
	stack_top = . ;

}

