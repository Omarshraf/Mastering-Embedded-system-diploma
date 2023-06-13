#include "driver.h"

int getPressureVal(){
	return (GPIOA_IDR & 0xFF);
}