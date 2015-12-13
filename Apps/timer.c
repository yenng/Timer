#include "timer.h"
#include <stdint.h>

void configTIM(TIM_t* timer){
	timerUnresetEnableClock();

	timer->CR1 = RESET;
	timer->CR1 = CNT_ENABLE | URS_ENABLE | UDIS_DISABLE | NO_BUFFERED | COUNTUP | EDGE | NO_ONE_PULSE | DIV_1;

	//RESET CR2
	timer->CR2 = RESET;
}

void configInputCapture(TIM_t* timer){}

void configOutputCompare(TIM_t* timer){}

void timerEnableDMA(TIM_t* timer){

}

void resetStatusRegisterFlag(TIM_t* timer){
	timer->SR = RESET;
}

void enableEventGeneration(TIM_t* timer){
	timer->EGR = RESET;
}

void writeValueToCounter(uint32_t value, TIM_t* timer){
	timer->CNT = value;
}

void setPrescaler(uint32_t prescaler, TIM_t* timer){
	timer->PSC = prescaler;
}

void writeValueToPreloadRegister(uint32_t preloadValue, TIM_t* timer){
	timer->ARR = preloadValue;
}


