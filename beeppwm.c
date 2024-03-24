#include "stm32f4xx.h"                  // Device header
#include "Delay.h"
#include "BItBand.h"
//PC6 TIM8_ch1
void tim_beeppwm_init()
{
	//ʱ��ʹ�ܣ�GPIOC,TIM8
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM13,ENABLE);
	
	//GPIO�������ã�����
	 GPIO_InitTypeDef GPIO_InitStructure;
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
   GPIO_Init(GPIOF, &GPIO_InitStructure);

	//���ö�ʱ��
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM13);
	
	//��ʱ�����ã����߶�ʱ������ģʽ
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=(5000-1);
	TIM_TimeBaseInitStruct.TIM_Prescaler=(8400-1);
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM13,&TIM_TimeBaseInitStruct);	
	
	//�ö�ʱ����ʼ����-->cmd
	TIM_Cmd(TIM13,ENABLE);
	
	//ͨ����������
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCInitStruct.TIM_OCIdleState=TIM_OCIdleState_Set;    //����״̬
	
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;             //ȷ����һ������Ч��ƽ
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;     //��Ч��ƽ�����Ǹߵ�ƽ���ǵ͵�ƽ
	
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse=0;      //������           //ռ�ձ�
	TIM_OC1Init(TIM13,&TIM_OCInitStruct);

	//��ͨͨ��1
	TIM_OC1PreloadConfig(TIM13,TIM_OCPreload_Enable);
	
	//����PWM�����ʼ
	TIM_CtrlPWMOutputs(TIM13,ENABLE);
	
}

/*
void Beep_Once(uint32_t time,uint32_t fre)
{
	uint32_t fre_time = 500000/fre;
	while(time--)
	{
		PFout(8) = 1;
		delay_us(fre_time);
		PFout(8) = 0;
		delay_us(fre_time);
	}
}
*/

void tim_beeppwm_run()
{
		TIM_SetCompare1(TIM13,5);
		PFout(8) = 1;
		delay_ms(1000);
	
		TIM_SetCompare1(TIM13,10);
		PFout(8) = 0;
		delay_ms(100);
}

