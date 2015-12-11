#include "stm32f4xx.h"
#include "timer.h"

int main(void)
{
	uint32_t value = 0X0010;
	uint32_t prescaler = 0X0002;
	uint32_t preloadValue = 0X00FF;
	uint32_t counterValue;
	configTIM(TIM2);
	resetStatusRegisterFlag(TIM2);
	writeValueToCounter(value, TIM2);
	setPrescaler(prescaler, TIM2);
	writeValueToPreloadRegister(preloadValue, TIM2);

    while(1){
    	counterValue = TIM2->CNT;
    }
}
