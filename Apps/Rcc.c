#include "Rcc.h"

//TIMER2 IS USED IN THIS EXPERIMENT.
void timerUnresetEnableClock(){
	RCC_reg->APB1RSTR &= ~(1);
	RCC_reg->APB1ENR |= 1;
}
