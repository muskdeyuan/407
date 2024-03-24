#include "stm32f4xx.h"                  // Device header
#include "BitBand.h"
#include "stdio.h"
#include "delay.h"

void exti_key_init()
{
	//ʱ������
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	
	//��GPIO��������
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3|GPIO_Pin_2;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_High_Speed;
	
	GPIO_Init(GPIOE,&GPIO_InitStruct);
	//��GPIOE��ĵ�2���������ӵ�EXTI2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource2);
	//��GPIOE��ĵ�3���������ӵ�EXTI3
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource3);
	
	//EXTI��������
	//����EXTI2��3�����������أ��͸�NVIC�����ж��ź�
	EXTI_InitTypeDef EXTI_InitStruct;
	
	EXTI_InitStruct.EXTI_Line=EXTI_Line2|EXTI_Line3;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Rising;
	
	EXTI_Init(&EXTI_InitStruct);
	
	//���鷽ʽ��2λ����ռ���ȼ���2λ����Ӧ���ȼ�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�Ӵ˴��жϺ�������������2��
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=EXTI2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	
	NVIC_Init(&NVIC_InitStruct);
	
	
	//���鷽ʽ��2λ����ռ���ȼ���2λ����Ӧ���ȼ�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);//�Ӵ˴��жϺ�������������2��
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	
	NVIC_Init(&NVIC_InitStruct);
	
}

//�жϷ����Ӻ�������EXTI2����
void EXTI2_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line2))
	{
		printf("key2 apple tree\n");
	}
	
	EXTI_ClearITPendingBit(EXTI_Line2);
}
	

//�жϷ����Ӻ�������EXTI3����
void EXTI3_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line3))
	{
		printf("key3 apple tree\n");
	}
	
	EXTI_ClearITPendingBit(EXTI_Line3);
}
	
