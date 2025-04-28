#ifndef __SERIAL_USART_H
#define __SERIAL_USART_H

#include <stdio.h>
extern char Serial_Rx[];

extern uint8_t Serial_TxPacket[];
extern uint8_t Serial_RxPacket[];
void Serial_init(void);
void Serial_SendByte(uint8_t msg);
void Serial_SendByte(uint8_t msg);
void Serial_SendString(char *String);

uint32_t Serial_Pow(uint32_t X, uint32_t Y);
void Serial_SendNUM(uint32_t Number, uint8_t Length);
void Serial_Printf(char *format, ...);
uint8_t Serial_GetRxFlag(void);
uint8_t Serial_GetRxData(void);
void Serial_SendPacket(void);


//uint8_t Serial_GetRxData(void);


#endif