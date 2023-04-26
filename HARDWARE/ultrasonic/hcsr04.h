#ifndef __CSB_SR04_H__
#define __CSB_SR04_H__

#include "stm32f10x.h" // Device header

/**
 * @brief HCSR04 Structure definition
 *
 * @param RCC_APBxPeriph_GPIOx_Trigger RCC APBx Periph GPIOx Trigger
 * @param RCC_APBxPeriph_GPIOx_Echo RCC APBx Periph GPIOx Echo
 * @param RCC_APBxPeriph_TIMx RCC APBx Periph TIMx
 * @param TIMx TIMx
 * @param TriggerPort Trigger Port
 * @param TriggerPin Trigger Pin
 * @param EchoPort Echo Port
 * @param EchoPin Echo Pin
 * @param N N, set to 0 for default
 * @param distance distance, set to 0 for default
 * @param count count, set to 0 for default
 * @param RCC_APBxPeriphClockCmd_Trigger RCC APBx Periph Clock Cmd Trigger
 * @param RCC_APBxPeriphClockCmd_Echo RCC APBx Periph Clock Cmd Echo
 * @param RCC_APBxPeriphClockCmd_TIMx RCC APBx Periph Clock Cmd TIMx
 * @param NVIC_IRQ_Channel NVIC IRQ Channel
 *
 * @note You need to write a interrupt service function for TIMx like this
 * @note void TIMx_IRQHandler(void){
 * @note    if(TIM_GetITStatus(TIMx, TIM_IT_Update) != RESET){
 * @note       hcsr->N ++;
 * @note    }
 * @note    TIM_ClearITPendingBit(TIMx, TIM_IT_Update);
 * @note }
 *
 */
typedef struct
{
    uint32_t RCC_APBxPeriph_GPIOx_Trigger;
    uint32_t RCC_APBxPeriph_GPIOx_Echo;
    uint32_t RCC_APBxPeriph_TIMx;
    TIM_TypeDef *TIMx;
    GPIO_TypeDef *TriggerPort;
    uint16_t TriggerPin;
    GPIO_TypeDef *EchoPort;
    uint16_t EchoPin;
    uint16_t N;
    float distance;
    int count;

    void (*RCC_APBxPeriphClockCmd_Trigger)(uint32_t, FunctionalState);
    void (*RCC_APBxPeriphClockCmd_Echo)(uint32_t, FunctionalState);
    void (*RCC_APBxPeriphClockCmd_TIMx)(uint32_t, FunctionalState);
    uint8_t NVIC_IRQ_Channel;
} HCSR04_Structure;

/**
 * @brief HCSR04 Init, you need to write a interrupt service function for TIMx
 *
 * @param hcsr04 HCSR04 Structure
 */
void HCSR04_Init(HCSR04_Structure *hcsr04);

/**
 * @brief HCSR04 Get Distance, you need to write a interrupt service function for TIMx
 *
 * @param hcsr04 HCSR04 Structure
 * @return float distance
 */
double HCSR04_GetDistance(HCSR04_Structure *hcsr04);

#endif
