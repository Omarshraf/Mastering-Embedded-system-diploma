#include "uart.h"
#include "stdio.h"
unsigned char text [100]="learn-in-depth:<Omar Ashraf>";
int main()
{
	uart_send_string(text);

}