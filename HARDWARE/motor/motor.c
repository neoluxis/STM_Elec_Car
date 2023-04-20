#include "stm32f10x.h" // Device header
#include "motor.h"

void MOTOR_SingleInit(MOTOR_Structure *motor,
					  int arr,
					  int psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	// ʹ��GPIO����ģ��ʱ��, ����PWM����
	RCC_APB2PeriphClockCmd(motor->RCC_APBxPeriph_GPIOx_ENABLE, ENABLE);

	// ��������Ϊ�����������,���TIMx��PWM���岨��
	GPIO_InitStructure.GPIO_Pin = motor->ENABLE_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // �����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(motor->ENABLE_Port, &GPIO_InitStructure); // ��ʼ��GPIO

	// ʹ��GPIO����ģ��ʱ��, ���ڷ������
	RCC_APB2PeriphClockCmd(motor->RCC_APBxPeriph_GPIOx_IN1, ENABLE);
	RCC_APB2PeriphClockCmd(motor->RCC_APBxPeriph_GPIOx_IN2, ENABLE);
	GPIO_InitStructure.GPIO_Pin = motor->IN1_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // �������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(motor->IN1_Port, &GPIO_InitStructure); // ��ʼ��GPIO IN1
	GPIO_InitStructure.GPIO_Pin = motor->IN2_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // �������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(motor->IN2_Port, &GPIO_InitStructure); // ��ʼ��GPIO IN2

	// Ĭ������Ϊֹͣ״̬
	GPIO_ResetBits(motor->IN1_Port, motor->IN1_Pin); // IN1 = 0
	GPIO_ResetBits(motor->IN2_Port, motor->IN2_Pin); // IN2 = 0

	// ʹ�ܶ�ʱ��2ʱ��
	RCC_APB1PeriphClockCmd(motor->RCC_APBxPeriph_TIMx, ENABLE);
	// ��ʼ��TIM2
	TIM_TimeBaseStructure.TIM_Period = arr;						// ��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = psc;					// ����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;				// ����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // TIM���ϼ���ģʽ
	TIM_TimeBaseInit(motor->TIMx, &TIM_TimeBaseStructure);		// ����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	// ��ʼ��TIM2 Channe1234 PWMģʽ
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;			  // ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // �Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	  // �������:TIM����Ƚϼ��Ը�,�ߵ�ƽ��Ч

	motor->OCx(motor->TIMx, &TIM_OCInitStructure); // ����Tָ���Ĳ�����ʼ������TIM2 OC1

	motor->OCx_PreloadConfig(motor->TIMx, TIM_OCPreload_Enable); // ʹ��TIM2��CCR1�ϵ�Ԥװ�ؼĴ���

	TIM_Cmd(motor->TIMx, ENABLE); // ʹ��TIM2
}

void MOTOR_SetSpeed(MOTOR_Structure *motor, uint16_t cmp)
{
	motor->SetCompare(motor->TIMx, cmp);
}

void MOTOR_SetDirection(MOTOR_Structure *motor, uint8_t dir)
{
	switch (dir)
	{
	case MOTOR_FORWARD:
		GPIO_ResetBits(motor->IN1_Port, motor->IN1_Pin); // IN1 = 0
		GPIO_SetBits(motor->IN2_Port, motor->IN2_Pin);	 // IN2 = 1
		break;
	case MOTOR_BACKWARD:
		GPIO_SetBits(motor->IN1_Port, motor->IN1_Pin);	 // IN1 = 1
		GPIO_ResetBits(motor->IN2_Port, motor->IN2_Pin); // IN2 = 0
		break;
	case MOTOR_NOWORK:
		GPIO_ResetBits(motor->IN1_Port, motor->IN1_Pin); // IN1 = 0
		GPIO_ResetBits(motor->IN2_Port, motor->IN2_Pin); // IN2 = 0
		break;
	case MOTOR_BRAKE:
		GPIO_SetBits(motor->IN1_Port, motor->IN1_Pin); // IN1 = 1
		GPIO_SetBits(motor->IN2_Port, motor->IN2_Pin); // IN2 = 1
		break;

	default:
		break;
	}
}
