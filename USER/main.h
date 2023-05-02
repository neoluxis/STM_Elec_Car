#ifndef __MAIN_H__
#define __MAIN_H__

#include "stm32f10x.h"
#include "hcsr04.h"
#include "led.h"
#include "oled.h"
#include "delay.h"
#include "usart.h"
#include "motor.h"
#include "neolux.h"

#define info(format, ...) printf(format "\r\n", __VA_ARGS__)

#define BRAKE_DISTANCE 20
#define ALERT_DISTANCE 45
#define OUT_DISTANCE 130

#define TURN 860

#define START 4500

#endif
