#include "uart.h"
#define UART0DR *((volatile unsigned char *)((unsigned char *)(0x101f1000)))
void uart_send_string(unsigned char *text){
	while(*text!='\0'){
		UART0DR=(unsigned char)(*text);
		text++;
	}
}