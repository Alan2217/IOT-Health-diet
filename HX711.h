#ifndef __HX711_H
#define __HX711_H

#include "sys.h"

#define HX711_SCK PBout(10)// PB10
//#define HX711_DOUT PBin(0) 


extern void Init_HX711pin(void);
extern uint32_t HX711_Read(uint8_t pin);
extern void Get_Maopi(uint8_t pin);
extern float Get_Weight(uint8_t pin);

extern uint32_t HX711_Buffer;
extern uint32_t Weight_Maopi;
//extern int32_t Weight_Shiwu;
extern uint8_t Flag_Error;

#endif

