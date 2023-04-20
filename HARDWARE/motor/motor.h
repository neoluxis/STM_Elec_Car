#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f10x.h"

#define MOTOR_FORWARD 1  // 0b0001, 向前
#define MOTOR_BACKWARD 0 // 0b0000, 向后
#define MOTOR_NOWORK 2   // 0b0010, 不工作
#define MOTOR_BRAKE 3    // 0b0011, 刹车

/**
 * @brief Motor object
 *
 * @param RCC_APBxPeriph_GPIOx_ENABLE  GPIO clock for enable pin
 * @param RCC_APBxPeriph_GPIOx_IN1     GPIO clock for IN1 pin
 * @param RCC_APBxPeriph_GPIOx_IN2     GPIO clock for IN2 pin
 * @param RCC_APBxPeriph_TIMx   Timer clock
 * @param TIMx                  Timer
 * @param OCx                   Timer output channel, function
 * @param OCx_PreloadConfig     Timer output channel preload, function
 * @param SetCompare            Timer output channel compare value, function
 * @param ENABLE_Port                 GPIO Port for enable pin
 * @param ENABLE_Pin              GPIO Pin for enable pin
 * @param IN1_Port               GPIO Port for IN1 pin
 * @param IN1_Pin                GPIO Pin for IN1 pin
 * @param IN2_Port               GPIO Port for IN2 pin
 * @param IN2_Pin                GPIO Pin for IN2 pin
 */
typedef struct
{
    uint32_t RCC_APBxPeriph_GPIOx_ENABLE;
    uint32_t RCC_APBxPeriph_GPIOx_IN1;
    uint32_t RCC_APBxPeriph_GPIOx_IN2;
    uint32_t RCC_APBxPeriph_TIMx;
    TIM_TypeDef *TIMx;
    GPIO_TypeDef *IN1_Port;
    uint16_t IN1_Pin;
    GPIO_TypeDef *IN2_Port;
    uint16_t IN2_Pin;
    void (*OCx)(TIM_TypeDef *,
                TIM_OCInitTypeDef *);
    void (*OCx_PreloadConfig)(TIM_TypeDef *,
                              uint16_t);
    void (*SetCompare)(TIM_TypeDef *,
                       uint16_t);
    GPIO_TypeDef *ENABLE_Port;
    uint16_t ENABLE_Pin;

} MOTOR_Structure;

/**
 * @brief Initialise a motor object
 *
 * @param motor    The motor to be initialised
 * @param arr   Timer auto reload register
 * @param psc   Timer prescaler
 */
void MOTOR_SingleInit(MOTOR_Structure *motor,
                      int arr,
                      int psc);
/**
 * @brief Adjust the motor speed
 *
 * @param motor     The motor to be adjusted
 */
void MOTOR_SetSpeed(MOTOR_Structure *motor, uint16_t cmp);

/**
 * @brief Set the motor direction
 *
 * @param motor   The motor to be adjusted
 * @param dir    The direction to be set, Available values are: MOTOR_FORWARD, MOTOR_BACKWARD, MOTOR_NOWORK, MOTOR_BRAKE
 */
void MOTOR_SetDirection(MOTOR_Structure *motor, uint8_t dir);

#endif
