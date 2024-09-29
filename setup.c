#include "setup.h"

GPIO_TypeDef* gpio = 0;																				//pointer created to use the GPIO port as received from the user

void GPIO_setup(char port, uint16_t pinNo){
	
	if(port != 'H'){
		RCC->AHB1ENR |= 1 << (port-65);														//ENABLE port A,B,C,D,E
	}
	else
		RCC->AHB1ENR |= (1 << 7);																	//ENABLE port H
	
	switch(port){
		case 'A':
			gpio = GPIOA;
			break;
		case 'B':
			gpio = GPIOB;
			break;
		case 'C':
			gpio = GPIOC;
			break;
		case 'D':
			gpio = GPIOD;
			break;
		case 'E':
			gpio = GPIOE;
			break;
		case 'H':
			gpio = GPIOH;
			break;
	}
	
	gpio->MODER &= ~(0x3 << (pinNo * 2));												//SET the GPIO pin in output mode		
	gpio->MODER |= (0x1 << (pinNo * 2));												
	
	gpio->OTYPER &= ~(0x1 << pinNo);														//gpio pin in push pull config
	
	gpio->ODR &= ~(0x1 << pinNo);																//initially gpio pin in LOW state 
}

void GPIO_toggle (uint16_t pinNo){
	
	gpio->ODR ^= (1 << pinNo);																	//toggle the pin
}

void genDelay(TIM_TypeDef* t){
	
	t->CNT = 0;																								//Initial count is zero
	t->PSC = 41;																							//Prescaler value
	t->ARR = 65535;																						//Auto Reload Register value
	t->CR1 |= 0x9;																						//enable the timer and disabled once overflown
	while((t->CR1 & 1));																			//wait for the timer to overflow
}

void Timer_setup(uint16_t delay){
	
	TIM_TypeDef* tim;
	uint16_t of_num;
	
	if(delay <= 0.65){
		tim = TIM3;																						//use 16 bit timer if delay is less than 65 msec
		RCC->APB1ENR |= 2;																		//enable timer 3
		genDelay(tim);
	}
	else{
		tim = TIM2;																						//use 32 bit timer if delay is more than 65 msec
		RCC->APB1ENR |= 1;																		//enable timer 2
		of_num = (delay * 1000)/65;														//number of overflows required to generate the delay
		for(uint16_t i = 0; i < of_num; i++){
			genDelay(tim);
		}
	}
}
