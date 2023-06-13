#include <stdint.h>
#include <stdio.h>

#include "driver.h"
int threshold;
int main (){
	GPIO_INITIALIZATION();
	int current_pressure;
	threshold=20;
	Set_Alarm_actuator(0);

	while (1)
	{
		
		current_pressure = getPressureVal();
		if(current_pressure <= threshold);

		else{
			Set_Alarm_actuator(1);
			Delay(10000);
			Set_Alarm_actuator(0);

		}

	}

}
