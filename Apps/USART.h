#ifndef USART_H
#define USART_H
#include <stdint.h>

typedef struct USART_Type USART_t;
struct USART_Type{
	uint32_t  SR;
	uint32_t  DR;
	uint32_t  BRR;
	uint32_t  CR1;
	uint32_t  CR2;
	uint32_t  CR3;
	uint32_t  GTPR;
};

#define USART1    	((USART_t*)0x40011000)

#define UE_ENABLE		(1<<13)
#define PARITY_ENABLE	(1<<10)
#define TE_ENABLE		(1<<3)

#endif // USART_H
