/*
 * LCD.c
 *
 *  Created on: Jul 10, 2023
 *      Author: Omar
 */

#include "LCD.h"

void delay_ms(uint32_t time) {
	uint32_t i, j;
	for (i = 0; i < time; i++)
		for (j = 0; j < 255; j++);
}


void LCD_KICK()
{
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_EN, GPIO_PIN_SET);
	delay_ms(50);
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_EN, GPIO_PIN_RESET);
}

//=================================================================================================
//                                           APIs Application
//=================================================================================================



/**================================================================
 * @Fn				-LCD_INIT
 * @brief 			-Initializes the LCD PINs according to the specified parameters in the PinConfig
 * @param [in] 		-none
 * @retval 			-none
 * Note				-none
 */

void LCD_INIT()
{
	//initialize the control pins
	PINCONFIG.GPIO_PinNumber = LCD_RS;
	PINCONFIG.GPIO_MODE = GPIO_MODE_OUTPT_PP;
	PINCONFIG.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &PINCONFIG);

	PINCONFIG.GPIO_PinNumber = LCD_RW;
	PINCONFIG.GPIO_MODE = GPIO_MODE_OUTPT_PP;
	PINCONFIG.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &PINCONFIG);

	PINCONFIG.GPIO_PinNumber = LCD_EN;
	PINCONFIG.GPIO_MODE = GPIO_MODE_OUTPT_PP;
	PINCONFIG.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &PINCONFIG);
	//=================================================================

	//initialize the DATA pins

	PINCONFIG.GPIO_PinNumber = GPIO_PIN_0;
	PINCONFIG.GPIO_MODE = GPIO_MODE_OUTPT_PP;
	PINCONFIG.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &PINCONFIG);

	PINCONFIG.GPIO_PinNumber = GPIO_PIN_1;
	PINCONFIG.GPIO_MODE = GPIO_MODE_OUTPT_PP;
	PINCONFIG.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &PINCONFIG);

	PINCONFIG.GPIO_PinNumber = GPIO_PIN_2;
	PINCONFIG.GPIO_MODE = GPIO_MODE_OUTPT_PP;
	PINCONFIG.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &PINCONFIG);

	PINCONFIG.GPIO_PinNumber = GPIO_PIN_3;
	PINCONFIG.GPIO_MODE = GPIO_MODE_OUTPT_PP;
	PINCONFIG.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &PINCONFIG);

	PINCONFIG.GPIO_PinNumber = GPIO_PIN_4;
	PINCONFIG.GPIO_MODE = GPIO_MODE_OUTPT_PP;
	PINCONFIG.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &PINCONFIG);

	PINCONFIG.GPIO_PinNumber = GPIO_PIN_5;
	PINCONFIG.GPIO_MODE = GPIO_MODE_OUTPT_PP;
	PINCONFIG.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &PINCONFIG);

	PINCONFIG.GPIO_PinNumber = GPIO_PIN_6;
	PINCONFIG.GPIO_MODE = GPIO_MODE_OUTPT_PP;
	PINCONFIG.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &PINCONFIG);

	PINCONFIG.GPIO_PinNumber = GPIO_PIN_7;
	PINCONFIG.GPIO_MODE = GPIO_MODE_OUTPT_PP;
	PINCONFIG.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &PINCONFIG);
	//=================================================================


	//Reset control pins
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_EN , GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RS , GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RW , GPIO_PIN_RESET);


	LCD_WRITE_COMMAND(LCD_FUNCTION_8BIT_2LINES);
	LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR_BLINK);

}




/**================================================================
 * @Fn				-LCD_WRITE_COMMAND
 * @brief 			-Write Command on LCD
 * @param [in] 		-command: the command that should be set
 * @retval 			-none
 * Note				-none
 */
void LCD_WRITE_COMMAND(unsigned char command)
{

	MCAL_GPIO_WritePort(LCD_CTRL_PORT, command);

	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RS, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RW, GPIO_PIN_RESET);


	delay_ms(1);
	LCD_KICK();
}



/**================================================================
 * @Fn				-LCD_WRITE_CHAR
 * @brief 			-Write Character on LCD
 * @param [in] 		-character: the character that should be written
 * @retval 			-none
 * Note				-none
 */


void LCD_WRITE_CHAR(unsigned char character)
{
	MCAL_GPIO_WritePort(LCD_CTRL_PORT, character);

	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RW, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RS, GPIO_PIN_SET);

	delay_ms(1);

	LCD_KICK();

}


/**================================================================
 * @Fn				-LCD_WRITE_STRING
 * @brief 			-Write String on LCD
 * @param [in] 		-string: the string that should be written on LCD
 * @retval 			-none
 * Note				-none
 */

void LCD_WRITE_STRING(char* string)
{
	int count=0;

	while(*string > 0)
	{
		count++;
		LCD_WRITE_CHAR(*string++);

		if (count == 16)
		{
			LCD_GOTO_XY(2, 0);
		}
		else if(count == 32)
		{
			LCD_clear_screen();
			LCD_GOTO_XY(1, 0);
			count = 0;
		}

	}
}


/**================================================================
 * @Fn				-LCD_check_lcd_isbusy
 * @brief 			-Check the LCD is busy or not
 * @param [in] 		-none
 * @retval 			-none
 * Note				-none
 */

void LCD_check_lcd_isbusy()
{
	//initialize the DATA pins

	PINCONFIG.GPIO_PinNumber = GPIO_PIN_0;
	PINCONFIG.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &PINCONFIG);

	PINCONFIG.GPIO_PinNumber = GPIO_PIN_1;
	PINCONFIG.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &PINCONFIG);

	PINCONFIG.GPIO_PinNumber = GPIO_PIN_2;
	PINCONFIG.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &PINCONFIG);

	PINCONFIG.GPIO_PinNumber = GPIO_PIN_3;
	PINCONFIG.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &PINCONFIG);

	PINCONFIG.GPIO_PinNumber = GPIO_PIN_4;
	PINCONFIG.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &PINCONFIG);

	PINCONFIG.GPIO_PinNumber = GPIO_PIN_5;
	PINCONFIG.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &PINCONFIG);

	PINCONFIG.GPIO_PinNumber = GPIO_PIN_6;
	PINCONFIG.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &PINCONFIG);

	PINCONFIG.GPIO_PinNumber = GPIO_PIN_7;
	PINCONFIG.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &PINCONFIG);
	//=================================================================

	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RS, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RW, GPIO_PIN_SET);


	LCD_KICK();

	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RW, GPIO_PIN_RESET);

}


/**================================================================
 * @Fn				-LCD_clear_screen
 * @brief 			-Clear the whole screen
 * @param [in] 		-none
 * @retval 			-none
 * Note				-none
 */

void LCD_clear_screen()
{
	LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN);
}

/**================================================================
 * @Fn				-LCD_GOTO_XY
 * @brief 			-detect the position on screen to write on
 * @param [in] 		-line: which line you want to write on (1 or 2)
 * @param [in] 		-position: which column you want to write on in the specified line
 * @retval 			-none
 * Note				-none
 */

void LCD_GOTO_XY(unsigned char line, unsigned char position)
{
	if (line == 1) {
		if (position < 16 && position >= 0) {
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW + position);
		}
	}
	if (line == 2) {
		if (position < 16 && position >= 0) {
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_SECOND_ROW + position);
		}
	}
}





