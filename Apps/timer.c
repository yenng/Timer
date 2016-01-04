#include "timer.h"
#include <stdint.h>

void configTIM(TIM_t* timer){
	timerUnresetEnableClock();

	timer->CR1 = RESET;
	timer->CR1 = CNT_ENABLE | URS_ENABLE | UDIS_DISABLE | NO_BUFFERED | COUNTUP | EDGE | NO_ONE_PULSE | DIV_1;

	//RESET CR2
	timer->CR2 = RESET;

	timer->DIER = 31;		//enable all interrupt enable
}

void configInputCapture(TIM_t* timer, int CH){
	timer->CCMR1 &= ICM_MASK<<(8*(CH-1));
	timer->CCMR1 |= ICM_TI1<<(8*(CH-1));
	timer->CCMR1 &= ICF_MASK<<(12-(8*(CH%2)));
	timer->CCMR1 |= 3<<(12-(8*(CH%2)));
	timer->CCER  = RESET;
	timer->CCER	 |= (EDGE_RISE<<(1+4*(CH-1)))|(CCE_EN<<4*(CH-1));
	
}

void configOutputCompare(TIM_t* timer){
	timer->CCMR1 = RESET;
	timer->CCMR2 = RESET;
	timer->CCER = RESET;
	timer->CCER |= EN_OC1 | EN_OC2| EN_OC3| EN_OC4;			//enable OC1 OC2 OC3 OC4
	timer->CCMR1 |= OCM1;
	timer->CCMR1 |= OCM2;
	timer->CCMR2 |= OCM3;
	timer->CCMR2 |= OCM4;
	timer->CCMR1 |= 7<<4;	//channel 1 is in PWM mode 2.
}

void resetStatusRegisterFlag(TIM_t* timer){
	timer->SR = RESET;
}

void writeValueToCCR( uint32_t value,TIM_t* timer){
	timer->CCR1 = value;
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


