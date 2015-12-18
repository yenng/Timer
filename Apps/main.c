#include "stm32f4xx.h"
#include "timer.h"
#include "Rcc.h"
#include "Gpio.h"

uint32_t value = 0X0000;
uint32_t prescaler = 0X0002;
uint32_t preloadValue = 0x003F;

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
	configUSART(USART1);
	resetStatusRegisterFlag(TIM2);
	writeValueToCounter(value, TIM2);
	setPrescaler(prescaler, TIM2);
	writeValueToPreloadRegister(preloadValue, TIM2);


	//config GPIO
	configureOutput(GPIO_SPEED_HIGH,PIN_15,PORTG);
	configureAltFunc(PULL_UP,PIN_9,PORTA);
	while(1){
		//testARRchangesWithBuffer();
		USART1->DR |= 0x01;
	}
}
