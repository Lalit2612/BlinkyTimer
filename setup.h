#include "stm32f4xx.h"

void GPIO_setup(char, uint16_t);																	//function to setup the GPIO port and pin
void Timer_setup(uint16_t);																				//function to setup the timer according to delay received
void GPIO_toggle(uint16_t);																				//function to toggle the GPIO pin
void genDelay(TIM_TypeDef*);																			//function to generate the required delay