/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include "lib_uart.h"
#include "delay.h"
#include "apds9660.h"

#include "stm32f4xx.h"
#include "string.h"

			

int main(void)
{
	Delay_init();
	UART_lib_config(e_UART_2, DISABLE, 0, 0);
	apds_init();

	UART_lib_sendData("START\n", strlen("START\n"));

	while(1)
	{

	}
}
