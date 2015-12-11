#include "stm32f4xx.h"
#include "timer.h"
#include "Rcc.h"
#include "Gpio.h"

int main(void)
{
	uint32_t value = 0X0010;
	uint32_t prescaler = 0XFFFF;
	uint32_t preloadValue = 0X00FF;
	uint32_t counterValue;
	int counterTrig = 0;


	//config timer
	configTIM(TIM2);
	resetStatusRegisterFlag(TIM2);
	writeValueToCounter(value, TIM2);
	setPrescaler(prescaler, TIM2);
	writeValueToPreloadRegister(preloadValue, TIM2);


	//config GPIO
	configureOutput(GPIO_SPEED_HIGH,PIN_4,PORTA);
	while(1){
		writeOne(PIN_4,PORTA);
		writeZero(PIN_4,PORTA);
	}
/*
    while(1){
    	while(TIM2->CNT < 255){
        	counterValue = TIM2->CNT;
    	}
    	counterTrig = !counterTrig;
    	if(counterTrig == 1)
    		writeOne(PIN_4,PORTA);
    	else
    		writeZero(PIN_4,PORTA);
    }
    */
}
