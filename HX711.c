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
//У׼����
//��Ϊ��ͬ�Ĵ������������߲��Ǻ�һ�£���ˣ�ÿһ����������Ҫ�������������������ʹ����ֵ��׼ȷ��
//�����ֲ��Գ���������ƫ��ʱ�����Ӹ���ֵ��
//������Գ���������ƫСʱ����С����ֵ��
//��ֵ����ΪС��
#define GapValue 396.8125


void Init_HX711pin(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PF�˿�ʱ��

	//HX711_SCK
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				 // �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB
	
	//HX711_DOUT
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
    GPIO_Init(GPIOB, &GPIO_InitStructure);  
	
	GPIO_SetBits(GPIOA,GPIO_Pin_10);					//��ʼ������Ϊ0
}



//****************************************************
//��ȡHX711
//****************************************************
uint32_t HX711_Read(uint8_t pin)	//����128
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
    count=count^0x800000;//��25�������½�����ʱ��ת������
	Delay_us(1);
	HX711_SCK=0;  
	return(count);
}

//****************************************************
//��ȡëƤ����
//****************************************************
void Get_Maopi(uint8_t pin)
{
	Weight_Maopi = HX711_Read(pin);	
} 

//****************************************************
//����
//****************************************************
float Get_Weight(uint8_t pin)
{
	HX711_Buffer = HX711_Read(pin);
	if(HX711_Buffer > Weight_Maopi)			
	{
		Weight_Shiwu = HX711_Buffer;
		Weight_Shiwu = Weight_Shiwu - Weight_Maopi;				//��ȡʵ���AD������ֵ��
	
		Weight_real = (float)Weight_Shiwu/GapValue; 	//����ʵ���ʵ������
																		//��Ϊ��ͬ�Ĵ������������߲�һ������ˣ�ÿһ����������Ҫ���������GapValue���������
																		//�����ֲ��Գ���������ƫ��ʱ�����Ӹ���ֵ��
																		//������Գ���������ƫСʱ����С����ֵ
		return Weight_real; 
	}

	
}
