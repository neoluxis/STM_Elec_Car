#include "stm32f10x.h" // Device header
#include "motor.h"

void MOTOR_SingleInit(MOTOR_Structure *motor,
					  int arr,
					  int psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	// 使能GPIO外设模块时钟, 用于PWM调速
	RCC_APB2PeriphClockCmd(motor->RCC_APBxPeriph_GPIOx_ENABLE, ENABLE);

	// 设置引脚为复用输出功能,输出TIMx的PWM脉冲波形
	GPIO_InitStructure.GPIO_Pin = motor->ENABLE_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(motor->ENABLE_Port, &GPIO_InitStructure); // 初始化GPIO

	// 使能GPIO外设模块时钟, 用于方向控制
	RCC_APB2PeriphClockCmd(motor->RCC_APBxPeriph_GPIOx_IN1, ENABLE);
	RCC_APB2PeriphClockCmd(motor->RCC_APBxPeriph_GPIOx_IN2, ENABLE);
	GPIO_InitStructure.GPIO_Pin = motor->IN1_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(motor->IN1_Port, &GPIO_InitStructure); // 初始化GPIO IN1
	GPIO_InitStructure.GPIO_Pin = motor->IN2_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(motor->IN2_Port, &GPIO_InitStructure); // 初始化GPIO IN2

	// 默认设置为停止状态
	GPIO_ResetBits(motor->IN1_Port, motor->IN1_Pin); // IN1 = 0
	GPIO_ResetBits(motor->IN2_Port, motor->IN2_Pin); // IN2 = 0

	// 使能定时器2时钟
	RCC_APB1PeriphClockCmd(motor->RCC_APBxPeriph_TIMx, ENABLE);
	// 初始化TIM2
	TIM_TimeBaseStructure.TIM_Period = arr;						// 设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = psc;					// 设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;				// 设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // TIM向上计数模式
	TIM_TimeBaseInit(motor->TIMx, &TIM_TimeBaseStructure);		// 根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	// 初始化TIM2 Channe1234 PWM模式
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;			  // 选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // 比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	  // 输出极性:TIM输出比较极性高,高电平有效

	motor->OCx(motor->TIMx, &TIM_OCInitStructure); // 根据T指定的参数初始化外设TIM2 OC1

	motor->OCx_PreloadConfig(motor->TIMx, TIM_OCPreload_Enable); // 使能TIM2在CCR1上的预装载寄存器

	TIM_Cmd(motor->TIMx, ENABLE); // 使能TIM2
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
