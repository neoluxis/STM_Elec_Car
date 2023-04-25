/**
 * @file main.c
 * @author Neolux Lee (neolux.lee@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-04-20
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "stm32f10x.h"
#include "hcsr04.h"
#include "oled.h"
#include "delay.h"
#include "usart.h"
#include "motor.h"
#include "main.h"

/**
 * @brief Motor object, front, left, right
 *
 */
HCSR04_Structure front, left, right;
/**
 * @brief Motor object, left, right 
 *
 */
MOTOR_Structure motor_l, motor_r;
/**
 * @brief Distance, front, left, right
 *
 */
int d_f = 0, d_l = 0, d_r = 0;

/**
 * @brief Initialise the direction control
 *
 */
void HCSR_Dir_Init(void);

/**
 * @brief Initialise the motor
 *
 */
void MOTOR_Dir_Init(void);

/**
 * @brief Direction control
 *
 * @note The direction control is based on the distance of the front, left and right
 *
 * @note 1. While the front distance is less than 20cm, the car will stop, then turn left or right.
 * @note 2. While the front distance is less than 40cm, the car will slow down and turn left or right.
 * @note 3. While the front distance is more than 40cm, the car will go straight.
 * @note 4. Measure the distance of left and right(done), which side is closer, turn to the other side.
 * @note 5. If the left and right distance are the same, turn left.
 * @note 6. If the left or right distance is more than 50cm, turn to the other side. Avoid going out from the entrance.
 *
 */
void Dir_Ctrl(void);

int main(void)
{
	// Initialise
	{
		delay_init();
		uart_init(1152000);
		OLED_Init();
		HCSR_Dir_Init();
		MOTOR_Dir_Init();
	}
	// Main loop
	while (1)
	{
		d_f = HCSR04_GetDistance(&front);
		delay_ms(5);
		d_l = HCSR04_GetDistance(&left);
		delay_ms(5);
		d_r = HCSR04_GetDistance(&right);
		delay_ms(5);
		info("%d, %d, %d", d_l, d_r, d_f);
		Dir_Ctrl();
	}
	// return 0;
}

void HCSR_Dir_Init(void)
{
	// front
	{
		front.RCC_APBxPeriph_GPIOx_Trigger = RCC_APB2Periph_GPIOB;
		front.RCC_APBxPeriph_GPIOx_Echo = RCC_APB2Periph_GPIOB;
		front.RCC_APBxPeriph_TIMx = RCC_APB1Periph_TIM4;
		front.TIMx = TIM4;
		front.TriggerPort = GPIOB;
		front.TriggerPin = GPIO_Pin_0;
		front.EchoPort = GPIOB;
		front.EchoPin = GPIO_Pin_1;
		front.N = 0;
		front.distance = 0;
		front.count = 0;
		front.RCC_APBxPeriphClockCmd_Trigger = RCC_APB2PeriphClockCmd;
		front.RCC_APBxPeriphClockCmd_Echo = RCC_APB2PeriphClockCmd;
		front.RCC_APBxPeriphClockCmd_TIMx = RCC_APB1PeriphClockCmd;
		front.NVIC_IRQ_Channel = TIM4_IRQn;
		HCSR04_Init(&front);
	}
	// left
	{
		left.RCC_APBxPeriph_GPIOx_Trigger = RCC_APB2Periph_GPIOB;
		left.RCC_APBxPeriph_GPIOx_Echo = RCC_APB2Periph_GPIOB;
		left.RCC_APBxPeriph_TIMx = RCC_APB1Periph_TIM5;
		left.TIMx = TIM5;
		left.TriggerPort = GPIOB;
		left.TriggerPin = GPIO_Pin_10;
		left.EchoPort = GPIOB;
		left.EchoPin = GPIO_Pin_11;
		left.N = 0;
		left.distance = 0;
		left.count = 0;
		left.RCC_APBxPeriphClockCmd_Trigger = RCC_APB2PeriphClockCmd;
		left.RCC_APBxPeriphClockCmd_Echo = RCC_APB2PeriphClockCmd;
		left.RCC_APBxPeriphClockCmd_TIMx = RCC_APB1PeriphClockCmd;
		left.NVIC_IRQ_Channel = TIM5_IRQn;
		HCSR04_Init(&left);
	}
	// right
	{
		right.RCC_APBxPeriph_GPIOx_Trigger = RCC_APB2Periph_GPIOC;
		right.RCC_APBxPeriph_GPIOx_Echo = RCC_APB2Periph_GPIOC;
		right.RCC_APBxPeriph_TIMx = RCC_APB1Periph_TIM6;
		right.TIMx = TIM6;
		right.TriggerPort = GPIOC;
		right.TriggerPin = GPIO_Pin_4;
		right.EchoPort = GPIOC;
		right.EchoPin = GPIO_Pin_5;
		right.N = 0;
		right.distance = 0;
		right.count = 0;
		right.RCC_APBxPeriphClockCmd_Trigger = RCC_APB2PeriphClockCmd;
		right.RCC_APBxPeriphClockCmd_Echo = RCC_APB2PeriphClockCmd;
		right.RCC_APBxPeriphClockCmd_TIMx = RCC_APB1PeriphClockCmd;
		right.NVIC_IRQ_Channel = TIM6_IRQn;
		HCSR04_Init(&right);
	}
}

void MOTOR_Dir_Init(void)
{
	// left motor
	{
		motor_l.RCC_APBxPeriph_GPIOx_ENABLE = RCC_APB2Periph_GPIOA;
		motor_l.RCC_APBxPeriph_GPIOx_IN1 = RCC_APB2Periph_GPIOC;
		motor_l.RCC_APBxPeriph_GPIOx_IN2 = RCC_APB2Periph_GPIOC;
		motor_l.RCC_APBxPeriph_TIMx = RCC_APB1Periph_TIM2;
		motor_l.TIMx = TIM2;
		motor_l.IN1_Port = GPIOC;
		motor_l.IN1_Pin = GPIO_Pin_10;
		motor_l.IN2_Port = GPIOC;
		motor_l.IN2_Pin = GPIO_Pin_11;
		motor_l.OCx = TIM_OC1Init;
		motor_l.OCx_PreloadConfig = TIM_OC1PreloadConfig;
		motor_l.SetCompare = TIM_SetCompare1;
		motor_l.ENABLE_Port = GPIOA;
		motor_l.ENABLE_Pin = GPIO_Pin_0;

		MOTOR_SingleInit(&motor_l, 7199, 0);
	}

	// right motor
	{
		motor_r.RCC_APBxPeriph_GPIOx_ENABLE = RCC_APB2Periph_GPIOA;
		motor_r.RCC_APBxPeriph_GPIOx_IN1 = RCC_APB2Periph_GPIOC;
		motor_r.RCC_APBxPeriph_GPIOx_IN2 = RCC_APB2Periph_GPIOC;
		motor_r.RCC_APBxPeriph_TIMx = RCC_APB1Periph_TIM2;
		motor_r.TIMx = TIM2;
		motor_r.IN1_Port = GPIOB;
		motor_r.IN1_Pin = GPIO_Pin_5;
		motor_r.IN2_Port = GPIOB;
		motor_r.IN2_Pin = GPIO_Pin_6;
		motor_r.OCx = TIM_OC2Init;
		motor_r.OCx_PreloadConfig = TIM_OC2PreloadConfig;
		motor_r.SetCompare = TIM_SetCompare2;
		motor_r.ENABLE_Port = GPIOA;
		motor_r.ENABLE_Pin = GPIO_Pin_1;

		MOTOR_SingleInit(&motor_r, 7199, 0);
	}
}

void Dir_Ctrl(void)
{
	// If front distance is smaller than 20cm, stop and turn left or right
	if (d_f < 20)
	{
		// Stop
		MOTOR_SetDirection(&motor_l, MOTOR_NOWORK);
		MOTOR_SetDirection(&motor_r, MOTOR_NOWORK);
		// Speed slow down
		MOTOR_SetSpeed(&motor_l, 2000);
		MOTOR_SetSpeed(&motor_r, 2000);
		// Turn left or right
		// If left distance is smaller than right distance, turn right
		if (d_l < d_r || d_l > 50)
		{
			MOTOR_SetDirection(&motor_l, MOTOR_FORWARD);
			MOTOR_SetDirection(&motor_r, MOTOR_BACKWARD);
		}
		// If right distance is smaller than or equal to left distance, turn left
		else if (d_l >= d_r || d_r > 50)
		{
			MOTOR_SetDirection(&motor_l, MOTOR_BACKWARD);
			MOTOR_SetDirection(&motor_r, MOTOR_FORWARD);
		}
	}
	// If front distance is smaller than 40cm, slow down and
	else if (d_f < 40)
	{
		MOTOR_SetDirection(&motor_l, MOTOR_FORWARD);
		MOTOR_SetDirection(&motor_r, MOTOR_FORWARD);
		// Speed slow down
		MOTOR_SetSpeed(&motor_l, 2000);
		MOTOR_SetSpeed(&motor_r, 2000);
		// Turn left or right
		// If left distance is smaller than right distance, turn right
		if (d_l < d_r || d_l > 50)
		{
			MOTOR_SetSpeed(&motor_l, 4000);
			MOTOR_SetSpeed(&motor_r, 2000);
		}
		// If right distance is smaller than or equal to left distance, turn left
		else if (d_l >= d_r || d_r > 50)
		{
			MOTOR_SetSpeed(&motor_l, 2000);
			MOTOR_SetSpeed(&motor_r, 4000);
		}
	}
	// if the front distance is larger than 40cm, go straight
	else
	{
		// Go straight
		MOTOR_SetDirection(&motor_l, MOTOR_FORWARD);
		MOTOR_SetDirection(&motor_r, MOTOR_FORWARD);
		// Speed up
		MOTOR_SetSpeed(&motor_l, 6000);
		MOTOR_SetSpeed(&motor_r, 6000);
	}
}

void TIM4_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{
		front.N++;
	}
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
}

void TIM5_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
	{
		left.N++;
	}
	TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
}

void TIM6_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
	{
		right.N++;
	}
	TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
}
