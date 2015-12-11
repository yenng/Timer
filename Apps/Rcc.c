#include "Rcc.h"
#include "Gpio.h"

//TIMER2 IS USED IN THIS EXPERIMENT.
void timerUnresetEnableClock(){
	RCC_reg->APB1RSTR &= ~(1);
	RCC_reg->APB1ENR |= 1;
}


void gpioUnresetEnableClock(GPIO* port){
	int valToShift = ((int)port - (0x40020000))/(0x400);

	RCC_reg->AHB1RSTR	&= ~GPIOx_RESET(valToShift);
	RCC_reg->AHB1ENR	|= GPIOx_ENABLE_CLOCK(valToShift);
}
