/*
 * global.c
 *
 *  Created on: Nov 28, 2024
 *      Author: DUC TIN
 */
#include "global.h"

void LEDREDBINKY(){
	HAL_GPIO_TogglePin(GPIOA, LED_RED_Pin);
}
void LEDGREENBINKY(){
	HAL_GPIO_TogglePin(GPIOA, LED_GREEN_Pin);
}
void LEDYELLOWBINKY(){
	HAL_GPIO_TogglePin(GPIOA, LED_YELLOW_Pin);
}
void LEDBLUEBINKY(){
	HAL_GPIO_TogglePin(GPIOA, LED_BLUE_Pin);
}

void LEDPURPLEBINKY(){
	HAL_GPIO_TogglePin(GPIOA, LED_PURPLE_Pin);
}
