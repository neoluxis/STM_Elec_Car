#include "motor.h"
#include "stm32f10x.h"                  // Device header

void MOTOR_Init(int arr, int psc){
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	//ʹ��GPIOA����ģ��ʱ��  
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   
 
	//��������Ϊ�����������,���TIM2 CH1-4��PWM���岨��	GPIOA.0-3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3; //TIM2 CH1-4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
 
	//ʹ�ܶ�ʱ��2ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	
    //��ʼ��TIM2
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	//��ʼ��TIM2 Channe1234 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�,�ߵ�ƽ��Ч
	
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM2 OC1
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM2 OC2
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM2 OC3
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM2 OC4

	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);  //ʹ��TIM2��CCR1�ϵ�Ԥװ�ؼĴ���
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);  //ʹ��TIM2��CCR2�ϵ�Ԥװ�ؼĴ���
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);  //ʹ��TIM2��CCR3�ϵ�Ԥװ�ؼĴ���
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);  //ʹ��TIM2��CCR4�ϵ�Ԥװ�ؼĴ���
 
	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIM2
}

void MOTOR_Adjust(int LeftPWM, int RightPWM){

}

