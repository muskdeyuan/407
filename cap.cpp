#include "stm32f4xx.h"   // Device header
#include "stdio.h"

//PA0  TIM5_CH1
void cap_init()
{
	//ʱ��ʹ��
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM5,ENABLE);
	//��������
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_DOWN;
	GPIO_InitStruct.GPIO_Speed=GPIO_High_Speed;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//����ģ��
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM5);
	//��ʱ��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = (5000-1);
	TIM_TimeBaseInitStruct.TIM_Prescaler = (8400-1);
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStruct);
	
	//��ʱ����ʼ����
	TIM_Cmd(TIM5, ENABLE);
	
	
	TIM_ICInitTypeDef TIM_ICInitStruct;
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_1;
	//TIM_ICInitStruct.TIM_ICFilter=0;
	TIM_ICInitStruct.TIM_ICPolarity=TIM_ICPolarity_BothEdge;//�������½���
	TIM_ICInitStruct.TIM_ICPrescaler=TIM_ICPSC_DIV1;//Ԥ��Ƶ��
	TIM_ICInitStruct.TIM_ICSelection=TIM_ICSelection_DirectTI;//ֱ��
	TIM_ICInit(TIM5,&TIM_ICInitStruct);
	
	//�����ж�
	TIM_ITConfig(TIM5, TIM_IT_CC1|TIM_IT_Update, ENABLE);
	//    nvic�ڲ��ж�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIM5_IRQn;//ץ�ж�Դ
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
}	

static uint32_t flag = 0;
static uint32_t val = 0;
static uint32_t cir = 0;
//�жϷ����Ӻ���
void TIM5_IRQHandler()
{
	if(TIM_GetITStatus(TIM5,TIM_IT_CC1))
	{
		if(flag == 0)
		{
			TIM5->CCR1=0;
			TIM_Cmd(TIM5, ENABLE);
			flag = 1;
		}
		else
		{
			TIM_Cmd(TIM5, DISABLE);
			val=TIM_GetCapture1(TIM5);//�൱��value    �ó�CCR����ֵ
			
			val = val + cir*5000;
			printf("val = %d\n",val);
			flag=0;
			cir =0;
		}
		 TIM_ClearITPendingBit(TIM5,TIM_IT_CC1);

	}
	if(TIM_GetITStatus(TIM5,TIM_IT_Update))
	{
	   cir++; 
		//����жϱ��
     TIM_ClearITPendingBit(TIM5,TIM_IT_Update);
	}
}
