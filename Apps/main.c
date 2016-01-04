#include "stm32f4xx.h"
#include "timer.h"
#include "Rcc.h"
#include "Gpio.h"

uint32_t counterValue = 0X0000;
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
//function used to trigger output pin
int triggerOutputPin(int counterTrig){
	counterTrig = !counterTrig;
	if(counterTrig == 1)
		writeOne(PIN_15,PORTG);
	else
		writeZero(PIN_15,PORTG);
	return counterTrig;
}

//this function used to investigate the counter,
// by triggering the output pin manually
int testCounter(){
	//setting of TIM->CR1
	int counterTrig = 0;
	uint32_t counterValue;
	uint32_t ARRValue = preloadValue;
	while(1){
		if(TIM2->CNT == preloadValue)
			counterTrig = triggerOutputPin(counterTrig);
	}
}

int getInputCaptureValue(){
	int CCR2 = TIM2->CCR2;
}

int main(void){
	//config timer
	configTIM(TIM2);
	resetStatusRegisterFlag(TIM2);
	writeValueToCounter(counterValue, TIM2);
	setPrescaler(prescaler, TIM2);
	writeValueToPreloadRegister(preloadValue, TIM2);
	writeValueToCCR(0x50,TIM2);
	configOutputCompare(TIM2);
	configInputCapture(TIM2, CH2);


	//config GPIO
	configureOutput(GPIO_SPEED_HIGH,PIN_15,PORTG);
	configureOutput(GPIO_SPEED_HIGH,PIN_13,PORTG);
	configureOutput(GPIO_SPEED_HIGH,PIN_11,PORTG);
	configureOutput(GPIO_SPEED_HIGH,PIN_9,PORTG);
	configureAltFunc(PULL_UP, PIN_0, PORTA, AF1);
	configureAltFunc(PULL_UP, PIN_3, PORTB, AF1);
	configureAltFunc(PULL_UP, PIN_10, PORTB, AF1);
	configureAltFunc(PULL_UP, PIN_3, PORTA, AF1);
	TIM2->SR = 0x0000;
	while(1){
		getInputCaptureValue();
	}
		//testARRchangesWithBuffer();
		//TIM2->CCMR1 |= OUT_HIGH_1;
		//testOCMmanually();

}
