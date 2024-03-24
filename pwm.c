#include "stm32f4xx.h"                  // Device header
#include "delay.h"
//PC6 TIM8_ch1
void tim_pwm_init()
{
	//ʱ��ʹ�ܣ�GPIOC,TIM8
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);
	
	//GPIO�������ã�����
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;//���ã�
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;//����
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6;//PC6
	//GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_High_Speed;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	
	//���ö�ʱ��
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM8);
	
	//��ʱ�����ã����߶�ʱ������ģʽ
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=(5000-1);
	TIM_TimeBaseInitStruct.TIM_Prescaler=(8400-1);
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM8,&TIM_TimeBaseInitStruct);	
	
	//�ö�ʱ����ʼ����-->cmd
	TIM_Cmd(TIM8,ENABLE);
	
	//ͨ����������
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCInitStruct.TIM_OCIdleState=TIM_OCIdleState_Set;    //����״̬
	
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;             //ȷ����һ������Ч��ƽ
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;     //��Ч��ƽ�����Ǹߵ�ƽ���ǵ͵�ƽ
	
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse=0;      //������           //ռ�ձ�
	TIM_OC1Init(TIM8,&TIM_OCInitStruct);

	//��ͨͨ��1
	TIM_OC1PreloadConfig(TIM8,TIM_OCPreload_Enable);
	
	//����PWM�����ʼ
	TIM_CtrlPWMOutputs(TIM8,ENABLE);
	
}
void tim_pwm_run()
{
	
	TIM_SetCompare1(TIM8,5);
	delay_ms(1000);
	
	
	TIM_SetCompare1(TIM8,50);
	delay_ms(1000);
}

