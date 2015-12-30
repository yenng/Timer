#include "stm32f4xx.h"
#include "timer.h"
#include "Rcc.h"
#include "Gpio.h"

uint32_t value = 0X0000;
uint32_t prescaler = 0X0002;
uint32_t preloadValue = 0x0200;

void testOCMmanually(){
	uint32_t counterValue = TIM2->CNT;
	int output1 = (TIM2->SR & (1<<1)) >> 1;
	if(output1==1){
		TIM2->CCMR1 |= OUT_HIGH_1;
		TIM2->SR = 0x0000;
	}
	//else
		//TIM2->CCMR1 |= OUT_LOW_1;
}
int triggerOutputPin(int counterTrig){
	counterTrig = !counterTrig;
	if(counterTrig == 1)
		writeOne(PIN_15,PORTG);
	else
		writeZero(PIN_15,PORTG);
	return counterTrig;
}

int testARRchangesWithBuffer(){
	//setting of TIM->CR1
	//timer->CR1 = CNT_ENABLE | URS_ENABLE | UDIS_DISABLE | NO_BUFFERED | COUNTUP | EDGE | NO_ONE_PULSE | DIV_1;
	int counterTrig = 0;
	uint32_t counterValue;
	uint32_t ARRValue = preloadValue;
	while(1){
		while(ARRValue == 63){
			while(TIM2->CNT < 63){
				if(TIM2->CNT == 50)
					ARRValue = 0x00FF;
				counterValue = TIM2->CNT;
			}
			counterTrig = triggerOutputPin(counterTrig);
		}
		writeValueToPreloadRegister(ARRValue, TIM2);
		if(ARRValue == 255){
			while(TIM2->CNT < 255){
				counterValue = TIM2->CNT;}
			counterTrig = triggerOutputPin(counterTrig);
		}
	}
}

int main(void){
	//config timer
	configTIM(TIM2);
	resetStatusRegisterFlag(TIM2);
	writeValueToCounter(value, TIM2);
	setPrescaler(prescaler, TIM2);
	writeValueToPreloadRegister(preloadValue, TIM2);
	writeValueToCCR(0x50,TIM2);
	configOutputCompare(TIM2);
	int x =TIM2->CCMR1;


	//config GPIO
	configureOutput(GPIO_SPEED_HIGH,PIN_15,PORTG);
	configureOutput(GPIO_SPEED_HIGH,PIN_13,PORTG);
	configureOutput(GPIO_SPEED_HIGH,PIN_11,PORTG);
	configureOutput(GPIO_SPEED_HIGH,PIN_9,PORTG);
	configureAltFunc(PULL_UP, PIN_0, PORTA, AF1);
	configureAltFunc(PULL_UP, PIN_3, PORTB, AF1);
	configureAltFunc(PULL_UP, PIN_10, PORTB, AF1);
	configureAltFunc(PULL_UP, PIN_3, PORTA, AF1);
	TIM2->CCMR1 = 0b00001110000;
	TIM2->CCMR1 |= OUT_HIGH_2;
	TIM2->CCMR2 |= OUT_HIGH_2;
	TIM2->CCMR2 |= OUT_HIGH_1;
	x =TIM2->CCMR1;
	TIM2->SR = 0x0000;
//	while(1){
//		while(TIM2->CNT > 0x10){
//			TIM2->CCMR1 |= OUT_LOW_1;
//		}
//		TIM2->CCMR1 |= OUT_HIGH_1;
//	}
		//testARRchangesWithBuffer();
		//TIM2->CCMR1 |= OUT_HIGH_1;
		//testOCMmanually();

}
