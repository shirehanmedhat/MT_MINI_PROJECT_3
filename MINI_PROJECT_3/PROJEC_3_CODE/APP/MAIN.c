/******************************************************************************
 *
 * Module: MAIN For Mini project 3
 *
 * File Name: MAIN.c
 *
 * Description: Source file for the Application Layer
 *
 * Author: Shirehan Medhat
 *
 *******************************************************************************/

#include "../HAL/LCD/LCD.h"
#include "../HAL/LM35/lm35_sensor.h"
#include "../HAL/DC_MOTOR/DC_MOTOR.h"
#include "MAIN.h"
int main (void)
{
	ALL_INIT();
	while(1)
	{

		uint16 LOC_TEMP_READING = LM35_getTemperature ();
		DISPLAY (LOC_TEMP_READING);


	}

}

/*
 * Function To Display the Temperature By LCDS
 * */
void DISPLAY (uint16 TEMP_READING)
{

	/*1- The First Line Content*/
	LCD_moveCursor (0,4);
	if (TEMP_READING <30)
	{
		LCD_displayStringRowColumn (0,3,"FAN IS OFF");
		DcMotor_Rotate (CW ,ZERO );
	}
	else if ((TEMP_READING >=30) && (TEMP_READING <60))
	{
		LCD_displayStringRowColumn (0,3,"FAN IS ON");
		LCD_displayCharacter (' ');
		DcMotor_Rotate (CW ,QUARTER_PERCENT );
	}
	else if ((TEMP_READING >=60) && (TEMP_READING <90))
	{
		LCD_displayStringRowColumn (0,3,"FAN IS ON");
		LCD_displayCharacter (' ');
		DcMotor_Rotate (CW ,HALF_PERCENT );
	}
	else if ((TEMP_READING >=90) && (TEMP_READING <120))
	{
		LCD_displayStringRowColumn (0,3,"FAN IS ON");
		DcMotor_Rotate (CW ,THREE_QUARTER_PERCENT );
	}
	else if ((TEMP_READING >=120) )
	{
		LCD_displayStringRowColumn (0,3,"FAN IS ON");
		LCD_displayCharacter (' ');
		DcMotor_Rotate (CW ,HUNDRED_PERCENT );
	}

	/*2- Move To The Second Line To Display The Content*/
	LCD_displayStringRowColumn (1,3,"TEMP =");
	LCD_intgerToString (TEMP_READING);
	/*3- If the Temperature Is Less Than 100 the third cell for number will be cleaned by space */
	if (TEMP_READING < HUNDRED_PERCENT)
	{
		LCD_displayCharacter (' ');
	}
	/*4- Print C at the end of the Second Line*/
	 LCD_displayCharacter ('C');

}
/*
 * Function To initialize all the devices needed
 * */

void ALL_INIT(void)
{
	LM35_INIT ();
	LCD_init ();
	DcMotor_Init();

}

