#include "stm32f10x.h"
#include "hcsr04.h"
#include "oled.h"
#include "delay.h"
#include "usart.h"
//#include "motor.h"

//HCSR04_InitStruct front, left, right;

void HCSR_Dir_Init(void){
//	// front
//	front.TriggerPin = GPIO_Pin_0;
//	front.EchoPin = GPIO_Pin_1;
//	front.TriggerPort = GPIOA;
//	front.EchoPort= GPIOA;
//	front.HCSR_Timer = TIM3;
//	front.RCC_APB1Periph_TIM = RCC_APB1Periph_TIM3;
//	front.NVIC_IRQChannel = TIM3_IRQn;
//	HCSR_Init(&front);
}

int main(void)
{	
	int distance1=0,distance2=0,distance3=0;
	delay_init();
	uart_init(9600);
	OLED_Init();
	
	
	while(1){
		
		printf("%d, %d, %d\n",distance1, distance2, distance3);
		
	}
}

// front
//void TIM3_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM3,TIM_IT_Update) != RESET)
//	{
//		front.N += 1;
//	}
//	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //清除中断标志位
//}
