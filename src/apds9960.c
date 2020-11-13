/*
 *  @file  : apds9960.c
 *	
 *  @brief : Source code to interface an apds9960
 *
 *  @author: Francesco Varani
 *  @date  : 13 nov 2020
 */
#include "lib_i2c.h"
#include "apds9660.h"

#include "stm32f4xx.h"

/** ---------------------------------- DEFINE ------------------------ */
#define		I2C_OWN_ADDRESS	(0x00)

/* Turn on pin*/
#define APDS_INTERRUPT_PIN		GPIO_Pin_11
#define APDS_INTERRUPT_PORT		GPIOA
#define APDS_INTERRUPT_SOURCE	EXTI_PinSource11
#define APDS_EXT_LINE			EXTI_Line11

/** ---------------------------------- PUBLIC FUNCTIONS IMPLEMENTATION ------------------------ */
/**
 * @brief Initialize the communcation channel with the sensor and the input pin to receive interrupt on falling edge
 */
void apds_init(void)
{
	GPIO_InitTypeDef 			GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	/* Enable SYSCFG's APB interface clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_EXTIT, ENABLE);

	GPIO_StructInit(&GPIO_InitStructure);
	EXTI_StructInit(&EXTI_InitStructure);

	/* Init interrupt pin*/
	GPIO_InitStructure.GPIO_Pin = APDS_INTERRUPT_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(APDS_INTERRUPT_PORT, &GPIO_InitStructure);

	/* connect pin to ext */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, APDS_INTERRUPT_SOURCE);

	/* set ext  12 */
	EXTI_InitStructure.EXTI_Line = APDS_EXT_LINE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;		/* yeah rising or falling ? */
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* INTERRUPT Init */
	/* Enable the USARTx Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;	/* to check ! */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			/* to check ! */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* init i2c 1*/
	lib_I2C_init(e_i2c_1, I2C_OWN_ADDRESS);
}

/** ---------------------------------- IRQ HANDLER IMPLEMENTATION ------------------------ */
/**
 * @note From datasheet - INT pin Interrupt - open drain (active low)
 */
void EXTI15_10_IRQHandler(void)
{
	if (EXTI_GetITStatus(APDS_EXT_LINE) == SET)
	{
		EXTI_ClearITPendingBit(APDS_EXT_LINE);

		if (GPIO_ReadInputDataBit(APDS_INTERRUPT_PORT, APDS_INTERRUPT_PIN) == RESET)
		{
			/*
			 * what to do?
			 */
		}

	}
}
