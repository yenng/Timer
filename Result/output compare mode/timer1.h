#ifndef timer_H
#define timer_H
#include <stdint.h>

typedef struct TIM_Type TIM_t;
struct TIM_Type{
	uint32_t  CR1;
	uint32_t  CR2;
	uint32_t  SMCR;
	uint32_t  DIER;
	uint32_t  SR;
	uint32_t  EGR;
	uint32_t  CCMR1;
	uint32_t  CCMR2;
	uint32_t  CCER;
	uint32_t  CNT;
	uint32_t  PSC;
	uint32_t  ARR;
	uint32_t  RES1;
	uint32_t  CCR1;
	uint32_t  CCR2;
	uint32_t  CCR3;
	uint32_t  CCR4;
	uint32_t  RES2;
	uint32_t  DCR;
	uint32_t  DMAR;
	uint32_t  OR;
};

#define TIM2    	((TIM_t*)0x40000000)

#define CH1			0
#define CH2			1
#define CH3			2
#define CH4			3

#define RESET		0x0000
/*********BITS OF CONTROL REGISTER CR1************************/
#define URS_ENABLE		(1<<2)
#define CNT_ENABLE		1
#define UDIS_DISABLE	0
#define UDIS_ENABLE		(1<<1)

//CR1 Center-aligned mode selection
#define EDGE		(0<<5)
#define CENTER1		(1<<5)
#define CENTER2		(2<<5)
#define CENTER3		(3<<5)
#define CMS_MASK	(3<<5)

//BUFFER
#define NO_BUFFERED	0
#define BUFFERED	(1<<7)

//CR1 counter direction
#define COUNTUP		0
#define	COUNTDOWN	(1<<4)

//ONE PULSE MODE
#define NO_ONE_PULSE	0
#define ONE_PULSE		(1<<3)

//CLOCK DIVISION
#define	DIV_1		0<<8
#define	DIV_2		1<<8
#define	DIV_4		2<<8
#define RES_CLK_DIV		3<<8
/****************************************************************/
/************BITS OF capture/compare mode register 1*************/
#define OCM1		~3
#define OCM2		~(3<<8)
#define OCM3		~3
#define OCM4		~(3<<8)
#define OUT_KEEP_LVL_1	0<<4
#define OUT_LOW_1		2<<4
#define OUT_HIGH_1		1<<4
#define OUT_TOGGLE_1	3<<4
#define OUT_MASK_1		~(7<<4)
#define OUT_KEEP_LVL_2	0<<12
#define OUT_LOW_2		2<<12
#define OUT_HIGH_2		1<<12
#define OUT_TOGGLE_2	3<<12
#define OUT_MASK_2		~(7<<12)
#define ENABLE_PRELOAD1 1<<3
#define ENABLE_PRELOAD2 1<<11


void configTIM(TIM_t* timer);
void timerEnableDMA(TIM_t* timer);
void resetStatusRegisterFlag(TIM_t* timer);
void enableEventGeneration(TIM_t* timer);
void writeValueToCounter(uint32_t value, TIM_t* timer);
void setPrescaler(uint32_t prescaler, TIM_t* timer);
void writeValueToCCR( uint32_t value,TIM_t* timer);

#endif // timer_H
