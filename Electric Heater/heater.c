/*
 * heater.c
 *
 * Created: 11/26/2021 4:15:46 PM
 *  Author: Mohamed
 */ 

#include "heater.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Twi.h"

extern volatile uint16 gu8GptCounter;




 

void Heater_Cooler_Init()
{
	Dio_ChannelDirectionSet(HEATER_COOLER_DIR_REG , HEATER_PIN , DIO_OUTPUT);
	Dio_ChannelDirectionSet(HEATER_COOLER_DIR_REG , COOLER_PIN , DIO_OUTPUT);
	
	SSD_Init();
	Sw_init(SW0_DIR_REG, SW0);
	Sw_init(SW1_2_DIR_REG, SW1);
	Sw_init(SW1_2_DIR_REG, SW2);
	Led_Init(LED0_1_DIR_REG,LED0);
	Led_Init(LED0_1_DIR_REG,LED1);
	Led_Init(LED2_DIR_REG,LED2);

	TempSensor_Init();
	Eeprom_Init();
	
}
void Heater_Mode(HeaterModeSelect Mode)
{
	switch (Mode)
	{
		case HEATER_ON:
		Dio_ChannelWrite(HEATER_COOLER_OUT_REG,HEATER_PIN,HEATER_ON);
		Dio_ChannelWrite(HEATER_COOLER_OUT_REG,COOLER_PIN,COOLER_OFF);
		Led_StateSet(LED2_OUT_REG,LED2,LED_OFF);
		Led_StateSet(LED0_1_OUT_REG,LED1,LED_ON); /*inducing a blink every 1 second when heater is on*/                            
		_delay_ms(1000);
		Led_StateSet(LED0_1_OUT_REG,LED1,LED_OFF);
		_delay_ms(200);
		
		break;
		case HEATER_OFF:
		Dio_ChannelWrite(HEATER_COOLER_OUT_REG,HEATER_PIN,HEATER_OFF);
		Led_StateSet(LED0_1_OUT_REG,LED1,LED_OFF);
		break;
		default:
		break;
	}
}
void Cooler_Mode(CoolerModeSelect Mode)
{
	switch (Mode)
	{
		case COOLER_ON:
		Dio_ChannelWrite(HEATER_COOLER_OUT_REG,COOLER_PIN,COOLER_ON);
		Dio_ChannelWrite(HEATER_COOLER_OUT_REG,HEATER_PIN,HEATER_OFF);
		Led_StateSet(LED2_OUT_REG,LED2,LED_ON);
		break;
		case COOLER_OFF:
		Dio_ChannelWrite(HEATER_COOLER_OUT_REG,COOLER_PIN,COOLER_OFF);
		Led_StateSet(LED2_OUT_REG,LED2,LED_OFF);
		break;
		default:
		break;
	}
}
void Set_mode(void)
{
	uint16 ONE_SECOND=244;
	Gpt_Init(&gaStrGpt_Configuration[GPT_TIMER0]);
	
	/*uint8 u8_1_seconds_counter=0;
	uint8 one_seconds=244U;  like in main.c file
	uint16 u16_5_seconds_counter=0;
	uint16 five_seconds=1220U;  244x5 
	setting 1 second timer for blinking and 5 seconds for exit*/
	while (gu8GptCounter < FIVE_SECOND_GPT_OVF_NUM)
	{
	/*u8_1_seconds_counter++;		
	u16_5_seconds_counter++;*/	
	 /*to save temp change and get temp from eeprom*/
	 
	Eeprom_ReadByte(0x00, &u8LocalRecData);
	SSD_NumSet(u8LocalRecData);
	Sw_StateEnum_t  Sw_State_1 = Sw_StateGet(SW1_2_INP_REG,SW1);
	Sw_StateEnum_t  Sw_State_2 = Sw_StateGet(SW1_2_INP_REG,SW2);
	if(Sw_State_1)/*if switch 1 is pressed increase temp and save it and displays it and resets 5 seconds counter*/
	{
		if(u8LocalRecData<=70)
		{
		u8LocalRecData+=5;
		SSD_NumSet(u8LocalRecData);
		gu8GptCounter=0;
		}
	}
	else if (Sw_State_2)
	{
		if(u8LocalRecData>=40)
		{
			
		u8LocalRecData-=5;
		SSD_NumSet(u8LocalRecData);
		gu8GptCounter=0;
		}
	}
	if (gu8GptCounter==ONE_SECOND) /*induces a delay for blinking*/ 
	{
		Eeprom_ReadByte(0x00, &u8LocalRecData);
		SSD_Blink(u8LocalRecData);
		ONE_SECOND+=244;
	}
		
	}
	Eeprom_WriteByte(0x00, u8LocalRecData);
	_delay_ms(1000);// You must allow sufficient delay for the EEPROM to complete its write cycle
	gu8GptCounter=0;
}
	
	uint8 TempSensor_ValueGet_100ms(void)
	{
		uint8 i=0;
		uint8 measurement=0;
		for(i=1;i<=10;i++) /* we do a loop for 10 measurements separated by 100ms delay as requested*/
		{
			measurement+=TempSensor_ValueGet();
			_delay_ms(100); //100/
		}
		uint8 Temp_Read= (measurement/10);
		return Temp_Read;
	}
	
	void SSD_Blink(uint8 Number)
	{
		SSD_NumberDisplay(gau8SSD_arr[(Number%100)/10],SSD2_EN);
		_delay_ms(10);
		SSD_NumberDisplay(gau8SSD_arr[(Number%10)],SSD1_EN);
		_delay_ms(10);
		SSD_NumberDisplay(gau8SSD_arr[(Number%10)],3);
		_delay_ms(10);
	}
