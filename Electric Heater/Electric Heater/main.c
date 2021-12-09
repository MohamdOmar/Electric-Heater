/*
 * Electric Heater.c
 *
 * Created: 11/23/2021 6:41:13 PM
 * Author : DELL
 */ 

#include "SSD.h"
#include "Macros.h"
#include <util/delay.h>
#include "Sw.h"
#include "Relay.h"
#include "Led.h"
#include "heater.h"
#include <avr/interrupt.h>
#include "Ext_Interrupts.h"

volatile uint16 five_sconds_counter=0;
volatile uint8 One_second_Counter=0;

ISR(TIMER0_OVF_vect)
{
	five_sconds_counter++;
	One_second_Counter++;
}

 


int main(void)
{
	uint8 u8TempReading;
	Heater_Cooler_Init();

	Global_Interrupts_StateSet(GLOBAL_INT_ENABLE);
	u8LocalRecData = 50 ;
	Eeprom_WriteByte(0x00,u8LocalRecData);
	_delay_ms(1000);
   

    /* Replace with your application code */
    while (1) 
    { 
		
		if(Sw_StateGet(SW0_INP_REG,SW0))
		{
			Led_StateSet(LED0_1_OUT_REG,LED0,LED_TOGGLE);
			_delay_ms(100);
		}
		else{
			//do nothing
		}
		
		if(Dio_ChannelRead(LED0_1_OUT_REG,LED0)) /*on and off*/
		{
			if(Sw_StateGet(SW1_2_INP_REG,SW1)||Sw_StateGet(SW1_2_INP_REG,SW2))
			{
				Set_mode();
			}
			
			u8TempReading =  TempSensor_ValueGet_100ms();
			SSD_NumSet(u8TempReading);
			
			Eeprom_ReadByte(0x00, &u8LocalRecData);
			if (u8TempReading<(u8LocalRecData-5))
			{
				Heater_Mode(HEATER_ON);
			}
			else{
				// DO Nothing
			}
			if (u8TempReading>(u8LocalRecData+5))
			{
				Cooler_Mode(COOLER_ON);
			} 
			else{
				// DO Nothing
			}
				
		}
		else
		{
			Heater_Mode(HEATER_OFF);
			Cooler_Mode(COOLER_OFF);
			SSD_NumberDisplay(gau8SSD_arr[0],3);
		}
    
	}
}

	


