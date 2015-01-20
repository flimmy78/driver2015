/*
================================================================================
* File Name                 :   dma.c
* Copyright                 :   2011-2013
* 
* CPU                       :   STM32F103
* RTOS                      :   FreeRTOS
*
* Create Date               :   2012/12/1
* Author/Company            :   Zhan Yubo/UESTC
* Abstract Description      :   Configuration and Applications of DMA.
*...............................................................................
* Revision History
* NO.     Date      Revised by      Item      Description
*	NO.1		2013/7/16	Zhan Yubo				Note			Added some necessary notes.
*
================================================================================
*/

#include "dma.h"
#include "includes.h"
//#include "hall.h"
//#include "current.h"
//#include "ad.h"
//#include "pwm.h"
//#include "memory.h"
//#include "canopen.h"
//#include "encoder.h"
//#include "foc.h"
//#include "led.h"
#include <math.h>
short ADC1_Value[5];
int adc1,adc2;
int adc;
#define ADC1_DR_Address    ((uint32_t)(&(ADC1->JDR1)))

/*
DMA2 CHANNEL STREAM 0
*/
void DMA_Configuration(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/*RCC*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE)	;
		
	/*NVIC*/
	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_SetPriority(DMA1_Stream2_IRQn,15);
	
	DMA_DeInit(DMA2_Stream0);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;//�����ַ
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)ADC1_Value;//�ڴ��ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;//dma���䷽����
	DMA_InitStructure.DMA_BufferSize = 4;//����DMA�ڴ���ʱ�������ĳ��� word
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;//����DMA���������ģʽ��һ������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//����DMA���ڴ����ģʽ��
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//���������ֳ�
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//�ڴ������ֳ�
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//����DMA�Ĵ���ģʽ���������ϵ�ѭ��ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;//����DMA�����ȼ���
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;//
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA2_Stream0, &DMA_InitStructure);
	DMA_ITConfig(DMA2_Stream0,DMA_IT_TC,ENABLE);
	DMA_Cmd(DMA2_Stream0,ENABLE);
}
void DMA2_Stream0_IRQHandler(void)
{
	
	if(DMA_GetITStatus(DMA2_Stream0,DMA_IT_TCIF0) == SET)
	{
		DMA_ClearITPendingBit(DMA2_Stream0,DMA_IT_TCIF0);
		adc1 = (int)(2048-ADC1_Value[0]);
		adc2 = (int)(2048-ADC1_Value[1]);	
	}
}
/*========================== END OF FILE =======================================*/
