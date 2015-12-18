#ifndef __Rcc_H__
#define	__Rcc_H__

#include <stdint.h>

#define RCC_reg ((RCC_t*)0x40023800)


typedef struct RCC_Type RCC_t;
struct RCC_Type{
	volatile uint32_t CR;
	volatile uint32_t PLLCFGR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t AHB1RSTR;
	volatile uint32_t AHB2RSTR;
	volatile uint32_t AHB3RSTR;
	volatile uint32_t RESERVE_0;
	volatile uint32_t APB1RSTR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t RESERVE_1;
	volatile uint32_t RESERVE_2;
	volatile uint32_t AHB1ENR;
	volatile uint32_t AHB2ENR;
	volatile uint32_t RCC_AHB3ENR;
	volatile uint32_t RESERVE_3;
	volatile uint32_t APB1ENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t RESERVE_4;
	volatile uint32_t RESERVE_5;
	volatile uint32_t AHB1LPENR;
	volatile uint32_t AHB2LPENR;
	volatile uint32_t AHB3LPENR;
	volatile uint32_t RESERVE_6;
	volatile uint32_t APB1LPENR;
	volatile uint32_t APB2LPENR;
	volatile uint32_t RESERVE_7;
	volatile uint32_t RESERVE_8;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t RESERVE_9;
	volatile uint32_t RESERVE_10;
	volatile uint32_t SSCGR;
	volatile uint32_t PLLI2SCFGR;
	volatile uint32_t PLLSAICFGR;
	volatile uint32_t DCKCFGR;
};

#define GPIOx_ENABLE_CLOCK(x)	(0x00100000 | (1 << (x)))
#define GPIOx_RESET(x)			  (1 << (x))

void timerUnresetEnableClock();
void usartUnresetEnableClock();

#endif //__Rcc_H__
