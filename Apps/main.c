#include "stm32f4xx.h"
#include "timer.h"
#include "Rcc.h"
#include "Gpio.h"

uint32_t value = 0X0000;
uint32_t prescaler = 0X0002;
uint32_t preloadValue = 0x003F;

void showOutput(int pinNum, GPIO *port, int trigger){
	if(trigger)
		writeOne(pinNum, port);
	else
		writeZero(pinNum,port);
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
	configUSART(USART1);
	resetStatusRegisterFlag(TIM2);
	writeValueToCounter(value, TIM2);
	setPrescaler(prescaler, TIM2);
	writeValueToPreloadRegister(preloadValue, TIM2);
	configOutputCompare(TIM2);


	//config GPIO
	configureOutput(GPIO_SPEED_HIGH,PIN_15,PORTG);
	configureOutput(GPIO_SPEED_HIGH,PIN_13,PORTG);
	configureOutput(GPIO_SPEED_HIGH,PIN_11,PORTG);
	configureOutput(GPIO_SPEED_HIGH,PIN_9,PORTG);
	//configureAltFunc(PULL_UP,PIN_9,PORTA);
	TIM2->CCR1 = 0x2;
	//TIM2->CCR2 = 0x8;
	//TIM2->CCR3 = 0x10;
	//TIM2->CCR4 = 0x20;
	TIM2->SR = 0x0000;
	int output1 = (TIM2->SR & (1<<1)) >> 1;
	int output2 = (TIM2->SR & (1<<2)) >> 2;
	int output3 = (TIM2->SR & (1<<3)) >> 3;
	int output4 = (TIM2->SR & (1<<4)) >> 4;
	configureAltFunc(PULL_UP, PIN_0, PORTA);
	//configureAltFunc(PULL_UP, PIN_1, PORTA);
	//configureAltFunc(PULL_UP, PIN_2, PORTA);
	//configureAltFunc(PULL_UP, PIN_3, PORTA);

	while(1){
		uint32_t counterValue = TIM2->CNT;
		TIM2->CCMR1 |= OUT_LOW_1;
		TIM2->CCMR1 |= OUT_HIGH_1;
		//testARRchangesWithBuffer();
		output1 = (TIM2->SR & (1<<1)) >> 1;
		if(output1==1){
			writeOne(PIN_9,PORTG);
			TIM2->SR = 0x0000;
			output1 = 0;
		}
		else
			writeZero(PIN_9,PORTG);
	}
}
