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
#include "lib_systick.h"

#include "stm32f4xx.h"
#include "string.h"

			

int main(void)
{
	UART_lib_config(e_UART_2, DISABLE, 0, 0);

	libsystick_set_systick(1000);

	UART_lib_sendData("START\n", strlen("START\n"));

	while(1)
	{

	}
}
