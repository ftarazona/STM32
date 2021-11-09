#include "timer.h"
#include "matrix.h"

static int i;
static int displayTriggered;
static int accelerometerTriggered;
static int refreshTriggered;

static int displayFreq;
static int accelerometerFreq;
static int refreshFreq;

/* timer init initializes the timer TIM2 and links a IRQ */
void timer_init(int max_us, int display, int accelerometer, int refresh)	{
	displayFreq = display;
	accelerometerFreq = accelerometer;
	refreshFreq = refresh;

	//Enabling TIM2 on APB1
	SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM2EN);

	//Reseting the timer
	TIM2->CNT = 0;
	TIM2->PSC = 80;
	TIM2->ARR = max_us;
	SET_BIT(TIM2->DIER, TIM_DIER_UIE);
	SET_BIT(TIM2->CR1, TIM_CR1_CEN);

	//Enabling the IRQ in NVIC
	NVIC_EnableIRQ(TIM2_IRQn);
}

int timer_triggered_display(void)	{
	if(displayTriggered)	{
		displayTriggered = 0;
		return 1;
	} else	{
		return 0;
	}
}

int timer_triggered_accelerometer(void)	{
	if(accelerometerTriggered)	{
		accelerometerTriggered = 0;
		return 1;
	} else	{
		return 0;
	}
}

int timer_triggered_refresh(void)	{
	if(refreshTriggered)	{
		refreshTriggered = 0;
		return 1;
	} else	{
		return 0;
	}
}

/* IRQ Handler called at every overflow of the timer. */
void TIM2_IRQHandler(void)	{
	CLEAR_BIT(TIM2->SR, TIM_SR_UIF);
	i++;
	if(i % displayFreq == 0)	{
		displayTriggered = 1;
	}
	if(i % accelerometerFreq == 0)	{
		accelerometerTriggered = 1;
	}
	if(i % refreshFreq == 0)	{
		refreshTriggered = 1;
		i = 0;
	}
}

/* nop loop */
void active_wait(int n_ticks)	{
	for(int i = 0; i < n_ticks; ++i)	{
		asm volatile("nop");
	}
}
