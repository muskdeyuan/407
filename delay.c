#include "stm32f4xx.h"  

void delay_ms(uint32_t ms)
{
	while(ms--)
		{
	SysTick->CTRL=0;//ʹ�乤��
	SysTick->LOAD=(SystemCoreClock/1000);//һ����
	SysTick->VAL=0;//���
	SysTick->CTRL=5;//���ڲ�ʱ�ӿ�ʼ�ɻ�
	while((SysTick->CTRL & 0x00010000)==0);
	SysTick->CTRL=0;
		}
}

void delay_us(uint32_t us)
{
	while(us--)
		{
	SysTick->CTRL=0;//ʹ�乤��
	SysTick->LOAD=(SystemCoreClock/1000000);//һ΢��
	SysTick->VAL=0;//���
	SysTick->CTRL=5;//���ڲ�ʱ�ӿ�ʼ�ɻ�
	while((SysTick->CTRL & 0x00010000)==0);
	SysTick->CTRL=0;
		}
}


