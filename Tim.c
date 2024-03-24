#include "stm32f4xx.h"                  // Device header
#include "stdio.h"

//��ʱ���ĳ�ʼ��
void Time_Init()
{
	//ʱ��ʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//1
	//�������ã�84M 84 000 000
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;//3
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;//4
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=(5000-1);//��������·�̣���ÿһ��ִ��һ���ж�
	TIM_TimeBaseInitStruct.TIM_Prescaler=(8400-1);//84M����8400=10 000�������ٶȣ�10 000/s��
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);//2
	
	//�ö�ʱ����ʼ����
	
	TIM_Cmd(TIM2,ENABLE);
	
	//��ʱ�������ж�,����TIM_Period������ͷ����NVIC˵һ��
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	//�жϷ���
	//���鷽ʽ��2λ����ռ���ȼ���2λ����Ӧ���ȼ�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�Ӵ˴��жϺ�������������2��
	
	//NVIC��������
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	
	NVIC_Init(&NVIC_InitStruct);
	
}
void TIM2_IRQHandler()
{
	//�ź��жϣ��жϽ�һ��ȷ��
	if(TIM_GetITStatus(TIM2,TIM_IT_Update))
	{
		printf("not apple tree!\n");
	}
	//�ж��ź����
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
}













