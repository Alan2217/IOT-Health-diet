#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "sys.h"
#include "HX711.h"
#include "Serial_USART.h"
#include <stdio.h>
#include <string.h>

#define GapValue 396.8125
float Weight_0;
float Weight_1;
char RxData;

int main(void)
{
	OLED_Init();
	Init_HX711pin();
	NVIC_Configuration();
	Serial_init();
	
	

	
	Get_Maopi(0);		
	Get_Maopi(1);				
	Delay_ms(1000);
	Delay_ms(1000);
	Get_Maopi(0);
	Get_Maopi(1);
	
	//OLED_ShowNum(3,1,Weight_Maopi,10);
	
	while(1)
	{
		
		
		//Get pin0  
		Weight_0 = Get_Weight(0)-149.8;
		
		OLED_ShowString(1,1,"Weight pin 0");
		OLED_ShowNum(2,1,Weight_0,4);
		uint16_t Weight_0p = (uint16_t)(Weight_0 * 100)%100;
		OLED_ShowString(2,5,".");
		OLED_ShowNum(2,6,Weight_0p,2);
		OLED_ShowString(2,8,"g");
		
		//Get pin1   #define GapValue 396.8125
		Weight_1 = Get_Weight(1);
		
		OLED_ShowString(3,1,"Weight pin 1");
		OLED_ShowNum(4,1,Weight_1,4);
		uint16_t Weight_1p = (uint16_t)(Weight_1 * 100)%100;
		OLED_ShowString(4,5,".");
		OLED_ShowNum(4,6,Weight_1p,2);
		OLED_ShowString(4,8,"g");
		
		//Send weight to computer
		//Serial_TxPacket[0] = (uint16_t)(Weight_0);
		//Serial_TxPacket[1] =(uint16_t)(Weight_1);
		//Serial_SendPacket();
		char str[5];
		
		if(Serial_GetRxFlag() == 1)
		{
			//RxData = Serial_GetRxData();
			if(strcmp(Serial_Rx,"1")==0)
			{
				//snprintf(str, sizeof(str), "%d", (uint8_t)(Weight_0+Weight_1));
				//Serial_SendString("Weight :");
				Serial_SendByte((uint8_t)(Weight_0+Weight_1));
				
				OLED_ShowNum(4,12,5,1);
				Delay_s(1);
				OLED_ShowNum(4,12,4,1);
				Delay_s(1);
				OLED_ShowNum(4,12,3,1);
				Delay_s(1);
				OLED_ShowNum(4,12,2,1);
				Delay_s(1);
				OLED_ShowNum(4,12,1,1);
				Delay_s(1);
				//Serial_SendString("g\r\n");
			}
//			else if(strcmp(Serial_Rx,"2")==0)
//			{
//				snprintf(str, sizeof(str), "%d", (uint16_t)(Weight_1));
//				Serial_SendString("Weight 2:");
//				Serial_SendString(str);
//				Serial_SendString("g\r\n");
//			}
		}
		
		
		
		Delay_ms(1000);
		
	}
		
}