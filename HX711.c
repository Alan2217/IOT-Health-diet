/************************************************************************************
						
*************************************************************************************/
#include "stm32f10x.h"  
#include "Delay.h"
#include "HX711.h"

uint32_t HX711_Buffer;
uint32_t Weight_Maopi;
int32_t Weight_Shiwu;
uint8_t Flag_Error = 0;
float Weight_real;
//校准参数
//因为不同的传感器特性曲线不是很一致，因此，每一个传感器需要矫正这里这个参数才能使测量值很准确。
//当发现测试出来的重量偏大时，增加该数值。
//如果测试出来的重量偏小时，减小改数值。
//该值可以为小数
#define GapValue 396.8125


void Init_HX711pin(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PF端口时钟

	//HX711_SCK
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				 // 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB
	
	//HX711_DOUT
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//输入上拉
    GPIO_Init(GPIOB, &GPIO_InitStructure);  
	
	GPIO_SetBits(GPIOA,GPIO_Pin_10);					//初始化设置为0
}



//****************************************************
//读取HX711
//****************************************************
uint32_t HX711_Read(uint8_t pin)	//增益128
{
	unsigned long count; 
	unsigned char i; 
  	PBin(pin) =1; 
		Delay_us(1);
  	HX711_SCK=0; 
  	count=0; 
  	while(PBin(pin)); 
  	for(i=0;i<24;i++)
	{ 
	  	HX711_SCK = 1; 
	  	count=count<<1; 
		Delay_us(1);
		HX711_SCK = 0; 
	  	if(PBin(pin))
			count++; 
		Delay_us(1);
	} 
 	HX711_SCK=1; 
    count=count^0x800000;//第25个脉冲下降沿来时，转换数据
	Delay_us(1);
	HX711_SCK=0;  
	return(count);
}

//****************************************************
//获取毛皮重量
//****************************************************
void Get_Maopi(uint8_t pin)
{
	Weight_Maopi = HX711_Read(pin);	
} 

//****************************************************
//称重
//****************************************************
float Get_Weight(uint8_t pin)
{
	HX711_Buffer = HX711_Read(pin);
	if(HX711_Buffer > Weight_Maopi)			
	{
		Weight_Shiwu = HX711_Buffer;
		Weight_Shiwu = Weight_Shiwu - Weight_Maopi;				//获取实物的AD采样数值。
	
		Weight_real = (float)Weight_Shiwu/GapValue; 	//计算实物的实际重量
																		//因为不同的传感器特性曲线不一样，因此，每一个传感器需要矫正这里的GapValue这个除数。
																		//当发现测试出来的重量偏大时，增加该数值。
																		//如果测试出来的重量偏小时，减小改数值
		return Weight_real; 
	}

	
}
