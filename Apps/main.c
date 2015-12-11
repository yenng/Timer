#include "stm32f4xx.h"
#include "timer.h"
#include "Rcc.h"
#include "Gpio.h"

void delay(int count){
	while(count>0)
		count--;
}

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
	configureOutput(GPIO_SPEED_HIGH,PIN_15,PORTG);
	configureOutput(GPIO_SPEED_HIGH,PIN_13,PORTG);
/*	while(1){
		writeOne(PIN_15,PORTG);
		writeOne(PIN_13,PORTG);
		delay(1000000);
		writeZero(PIN_15,PORTG);
		writeZero(PIN_13,PORTG);
		delay(10000000);
	}*/

    while(1){
    	while(TIM2->CNT < 255){
        	counterValue = TIM2->CNT;
    	}
    	counterTrig = !counterTrig;
    	if(counterTrig == 1)
    		writeOne(PIN_15,PORTG);
    	else
    		writeZero(PIN_15,PORTG);
    }

}
