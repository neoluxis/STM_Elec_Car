#ifndef __LED_H
#define __LED_H

#define LED0_GPIO_Port GPIOA
#define LED0_GPIO_Pin GPIO_Pin_8
#define LED1_GPIO_Port GPIOD
#define LED1_GPIO_Pin GPIO_Pin_2

void LED_Init(void);

/**
 * @brief Turn on LED0 PA8
 *
 */
void LED0_ON(void);
/**
 * @brief Turn off LED0 PA8
 *
 */
void LED0_OFF(void);

/**
 * @brief Turn on LED1 PD2
 *
 */
void LED1_ON(void);
/**
 * @brief Turn off LED1 PD2
 *
 */
void LED1_OFF(void);

#endif
