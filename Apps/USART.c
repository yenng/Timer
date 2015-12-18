#include "USART.h"

void configUSART(USART_t* usart){
	usartUnresetEnableClock();
	usart->CR1 = UE_ENABLE|TE_ENABLE|PARITY_ENABLE;
	usart->BRR = 'x';

}
