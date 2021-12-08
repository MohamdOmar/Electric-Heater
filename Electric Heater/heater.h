/*
 * IncFile1.h
 *
 * Created: 11/26/2021 4:15:17 PM
 *  Author: Mohamed
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

#include "ATmega32_Cfg.h"
#include "Dio.h"
#include "SSD.h"
#include "Sw.h"
#include "Led.h"
#include "Twi.h"
#include "Relay.h"
#include "TempSensor.h"
#include "Ext_Eeprom.h"
#include "Gpt.h"

#define ONE_SECOND_GPT_OVF_NUM   (244U)
#define FIVE_SECOND_GPT_OVF_NUM  (1220U)


#define HEATER_COOLER_DIR_REG  (PORTC_DIR_REG)
#define HEATER_COOLER_OUT_REG  (PORTC_OUT_REG)

#define HEATER_PIN   (DIO_PIN3)
#define COOLER_PIN   (DIO_PIN4)

 uint8 u8LocalRecData;
 

typedef enum
{
	HEATER_OFF,
	HEATER_ON
}HeaterModeSelect;
	
typedef enum
{
	COOLER_OFF,
	COOLER_ON
}CoolerModeSelect;


void Heater_Cooler_Init();

void Heater_Mode(HeaterModeSelect Mode);

void Cooler_Mode(CoolerModeSelect Mode);

void Set_mode(void);

uint8 TempSensor_ValueGet_100ms(void);

void SSD_Blink(uint8 Number);


#endif /* INCFILE1_H_ */