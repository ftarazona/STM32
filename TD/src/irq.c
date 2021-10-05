#include "irq.h"

void *vector_table[] =	{
	//Stack and reset
	&_stack,
	_start,

	//Internal exceptions
	NMI_Handler,
	HardFault_Handler,
	MemManage_Handler,
	BusFault_Handler,
	UsageFault_Handler,
	0,
	0,
	0,
	0,
	SVC_Handler,
	0,
	0,
	PendSV_Handler,
	SysTick_Handler,

	//External IRQs
	WWDG_IRQHandler,
	PVD_PVM_IRQHandler,
	CSS_LSE_IRQHandler,
	RTC_WKUP_IRQHandler,
	FLASH_IRQHandler,
	RCC_IRQHandler,
	EXTI0_IRQHandler,
	EXTI1_IRQHandler,
	EXTI2_IRQHandler,
	EXTI3_IRQHandler,
	EXTI4_IRQHandler,
	DMA1_CH1_IRQHandler,
	DMA1_CH2_IRQHandler,
	DMA1_CH3_IRQHandler,
	DMA1_CH4_IRQHandler,
	DMA1_CH5_IRQHandler,
	DMA1_CH6_IRQHandler,
	DMA1_CH7_IRQHandler,
	ADC1_2_IRQHandler,
	CAN1_TX_IRQHandler,
	CAN1_RX0_IRQHandler,
	CAN1_RX1_IRQHandler,
	CAN1_SCE_IRQHandler,
	EXTI9_5_IRQHandler,
	TIM_BRK_IRQHandler,
	TIM1_UP_IRQHandler,
	TIM1_TRG_COM_IRQHandler,
	TIM1_CC_IRQHandler,
	TIM2_IRQHandler,
	TIM3_IRQHandler,
	TIM4_IRQHandler,
	I2C1_EV_IRQHandler,
	I2C1_ER_IRQHandler,
	I2C2_EV_IRQHandler,
	I2C2_ER_IRQHandler,
	SPI1_IRQHandler,
	SPI2_IRQHandler,
	USART1_IRQHandler,
	USART2_IRQHandler,
	USART3_IRQHandler,
	EXTI15_10_IRQHandler,
	RTC_ALARM_IRQHandler,
	DFSDM1_FLT3_IRQHandler,
	TIM8_BRK_IRQHandler,
	TIM8_UP_IRQHandler,
	TIM8_TRG_COM_IRQHandler,
	TIM8_CC_IRQHandler,
	ADC3_IRQHandler,
	FMC_IRQHandler,
	SDMMC1_IRQHandler,
	TIM5_IRQHandler,
	SPI3_IRQHandler,
	UART4_IRQHandler,
	UART5_IRQHandler,
	TIM6_DACUNDER_IRQHandler,
	TIM7_IRQHandler,
	DMA2_CH1_IRQHandler,
	DMA2_CH2_IRQHandler,
	DMA2_CH3_IRQHandler,
	DMA2_CH4_IRQHandler,
	DMA2_CH5_IRQHandler,
	DFSDM1_FLT0_IRQHandler,
	DFSDM1_FLT1_IRQHandler,
	DFSDM1_FLT2_IRQHandler,
	COMP_IRQHandler,
	LPTIM1_IRQHandler,
	LPTIM2_IRQHandler,
	OTG_FS_IRQHandler,
	DMA2_CH6_IRQHandler,
	DMA2_CH7_IRQHandler,
	LPUART1_IRQHandler,
	QUADSPI_IRQHandler,
	I2C3_EV_IRQHandler,
	I2C3_ER_IRQHandler,
	SAI1_IRQHandler,
	SAI2_IRQHandler,
	SWPMI1_IRQHandler,
	TSC_IRQHandler,
	LCD_IRQHandler,
	AES_IRQHandler,
	RNG_IRQHandler,
	FPU_IRQHandler
}
