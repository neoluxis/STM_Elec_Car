#ifndef __KEY_H
#define __KEY_H
#include "stm32f10x.h"                  // Device header

// #define __USE_WK_UP

#define NONE_PRES 0
#define KEY0_PRES 1
#define KEY1_PRES 2
#define WKUP_PRES 3

#define KEY0 PCin(1)   //PC1
#define KEY1 PCin(13)	//PC13 
#define WK_UP PAin(0)	//PA0  WK_UP

/**
 * @brief Initialize the keys
 * 
 */
void Key_Init(void);
/**
 * @brief Scan the keys to get a key value
 * 
 * @param mode 0: no repeat 1: repeat
 * @return uint8_t 
 */
uint8_t KEY_Scan(int mode);

#endif
