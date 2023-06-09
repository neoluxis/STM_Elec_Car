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

#include "main.h"
#include "math.h"

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
double d_f = 0, d_l = 0, d_r = 0;

double dfr = 0, dfl = 0;

double getDiagonalDistance(double a, double b)
{
	double c = a * b / sqrt(a * a + b * b);
	return c;
}

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
 */
void Dir_Ctrl(void);

int main(void)
{
	// Initialise
	{
		delay_init();
		LED_Init();
		uart_init(9600);
		HCSR_Dir_Init();
		MOTOR_Dir_Init();
		printf("%s\n", NEOLUXLEE_SHADOW);
		printf("Neolux's Car\n");
	}
	// Main loop
	while (1)
	{
		info("%f,%f,%f", d_f, d_r, d_l);
		d_f = HCSR04_GetDistance(&front);
		delay_ms(10);
		d_l = HCSR04_GetDistance(&left);
		delay_ms(10);
		d_r = HCSR04_GetDistance(&right);
		delay_ms(10);
		Dir_Ctrl();
		// MOTOR_Set(&motor_l, MOTOR_BACKWARD, START);
		// MOTOR_Set(&motor_r, MOTOR_NOWORK, START);
		delay_ms(10);
		LED0_TOG();
		delay_ms(10);
	}
	// return 0;
}

void HCSR_Dir_Init(void)
{
	// front
	{
		front.RCC_APBxPeriph_GPIOx_Trigger = RCC_APB2Periph_GPIOB;
		front.RCC_APBxPeriph_GPIOx_Echo = RCC_APB2Periph_GPIOB;
		front.RCC_APBxPeriph_TIMx = RCC_APB1Periph_TIM7;
		front.TIMx = TIM7;
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
		front.NVIC_IRQ_Channel = TIM7_IRQn;
		HCSR04_Init(&front);
	}
	// right
	{
		right.RCC_APBxPeriph_GPIOx_Trigger = RCC_APB2Periph_GPIOB;
		right.RCC_APBxPeriph_GPIOx_Echo = RCC_APB2Periph_GPIOB;
		right.RCC_APBxPeriph_TIMx = RCC_APB1Periph_TIM5;
		right.TIMx = TIM5;
		right.TriggerPort = GPIOB;
		right.TriggerPin = GPIO_Pin_10;
		right.EchoPort = GPIOB;
		right.EchoPin = GPIO_Pin_11;
		right.N = 0;
		right.distance = 0;
		right.count = 0;
		right.RCC_APBxPeriphClockCmd_Trigger = RCC_APB2PeriphClockCmd;
		right.RCC_APBxPeriphClockCmd_Echo = RCC_APB2PeriphClockCmd;
		right.RCC_APBxPeriphClockCmd_TIMx = RCC_APB1PeriphClockCmd;
		right.NVIC_IRQ_Channel = TIM5_IRQn;
		HCSR04_Init(&right);
	}
	// left
	{
		left.RCC_APBxPeriph_GPIOx_Trigger = RCC_APB2Periph_GPIOC;
		left.RCC_APBxPeriph_GPIOx_Echo = RCC_APB2Periph_GPIOC;
		left.RCC_APBxPeriph_TIMx = RCC_APB1Periph_TIM6;
		left.TIMx = TIM6;
		left.TriggerPort = GPIOC;
		left.TriggerPin = GPIO_Pin_4;
		left.EchoPort = GPIOC;
		left.EchoPin = GPIO_Pin_5;
		left.N = 0;
		left.distance = 0;
		left.count = 0;
		left.RCC_APBxPeriphClockCmd_Trigger = RCC_APB2PeriphClockCmd;
		left.RCC_APBxPeriphClockCmd_Echo = RCC_APB2PeriphClockCmd;
		left.RCC_APBxPeriphClockCmd_TIMx = RCC_APB1PeriphClockCmd;
		left.NVIC_IRQ_Channel = TIM6_IRQn;
		HCSR04_Init(&left);
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
		motor_l.IN1_Pin = GPIO_Pin_0;
		motor_l.IN2_Port = GPIOC;
		motor_l.IN2_Pin = GPIO_Pin_1;
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
		motor_r.IN1_Port = GPIOC;
		motor_r.IN1_Pin = GPIO_Pin_2;
		motor_r.IN2_Port = GPIOC;
		motor_r.IN2_Pin = GPIO_Pin_3;
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
	// if (d_f == 0 || d_r == 0 || d_l == 0)
	// {
	// 	MOTOR_SetDirection(&motor_l,
	// 					   MOTOR_BRAKE);
	// 	MOTOR_SetDirection(&motor_r,
	// 					   MOTOR_BRAKE);
	// 	MOTOR_Set(&motor_l,
	// 			  MOTOR_BACKWARD,
	// 			  START);
	// 	MOTOR_Set(&motor_r,
	// 			  MOTOR_BACKWARD,
	// 			  START);
	// 	// if (d_f == 0)
	// 	// {
	// 	// 	MOTOR_Set(&motor_l,
	// 	// 			  MOTOR_BACKWARD,
	// 	// 			  START);
	// 	// 	MOTOR_Set(&motor_r,
	// 	// 			  MOTOR_BACKWARD,
	// 	// 			  START);
	// 	// }
	// 	// else if (d_r == 0)
	// 	// {
	// 	// 	MOTOR_Set(&motor_l,
	// 	// 			  MOTOR_BACKWARD,
	// 	// 			  START - TURN);
	// 	// 	MOTOR_Set(&motor_r,
	// 	// 			  MOTOR_FORWARD,
	// 	// 			  START + TURN);
	// 	// }
	// 	// else if (d_l == 0)
	// 	// {
	// 	// 	MOTOR_Set(&motor_l,
	// 	// 			  MOTOR_FORWARD,
	// 	// 			  START + TURN);
	// 	// 	MOTOR_Set(&motor_r,
	// 	// 			  MOTOR_BACKWARD,
	// 	// 			  START - TURN);
	// 	// }
	// 	return;
	// }
	if (d_f < BRAKE_DISTANCE)
	{
		MOTOR_SetDirection(&motor_l,
						   MOTOR_BRAKE);
		MOTOR_SetDirection(&motor_r,
						   MOTOR_BRAKE);
		if (d_l - d_r > 8 ||
			d_r > OUT_DISTANCE)
		{
			MOTOR_Set(&motor_l,
					  MOTOR_BACKWARD,
					  START);
		}
		else if (d_r - d_l > 8 ||
				 d_l > OUT_DISTANCE)
		{
			MOTOR_Set(&motor_r,
					  MOTOR_BACKWARD,
					  START);
		}
		else
		{
			MOTOR_Set(&motor_l,
					  MOTOR_BACKWARD,
					  START + 520);
		}
	}
	else if (d_f < ALERT_DISTANCE)
	{
		if (d_l - d_r > 8 ||
			d_r > OUT_DISTANCE)
		{
			MOTOR_Set(&motor_l,
					  MOTOR_FORWARD,
					  START - TURN);
			MOTOR_Set(&motor_r,
					  MOTOR_FORWARD,
					  START + TURN);
		}
		else if (d_r - d_l > 8 ||
				 d_l > OUT_DISTANCE)
		{
			MOTOR_Set(&motor_l,
					  MOTOR_FORWARD,
					  START + TURN);
			MOTOR_Set(&motor_r,
					  MOTOR_FORWARD,
					  START - TURN);
		}
		else
		{
			MOTOR_Set(&motor_l,
					  MOTOR_BACKWARD,
					  START + 500);
		}
	}
	else // go straight
	{
		MOTOR_Set(&motor_l,
				  MOTOR_FORWARD,
				  START + 525);
		MOTOR_Set(&motor_r,
				  MOTOR_FORWARD,
				  START);
	}
}

void TIM7_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
	{
		front.N++;
	}
	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
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
