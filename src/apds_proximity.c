/*
 *  @file  : apds_proximity.c
 *	
 *  @brief : Proximity engine handling. See datasheet pag 11
 *
 *  @author: Francesco Varani
 *  @date  : 13 nov 2020
 */
#include "apds_proximity.h"
#include "apds9660.h"
#include "apds_flag.h"
#include "apds_register.h"

#include "stm32f4xx.h"

volatile static uint8_t _p_saturation;
volatile static t_proximity_error _p_error;

/*
 * The Proximity detection feature provides distance measurement
 * Detect/release events are interrupt driven, and occur whenever proximity result crosses
 * upper and/or lower threshold settings.
 */
void apds_start_proximity_engine(void)
{
	_p_saturation = RESET;
	_p_error = e_proximity_error_none;
	/*
	 * TODO check if in SLEEP or IDLE !
	 */

	/*
	 * Start ENABLE REGISTER:
	 * - ENABLE_REGISTER_PON = 1
	 * - ENABLE_REGISTER_PEN = 1
	 */
	apds_write_generic(e_register_ENABLE, ENABLE_REGISTER_PON | ENABLE_REGISTER_PEN);
	/*
	Optically, the IR emission appears as a pulse train. The
	number of pulses is set by the PPULSE bits and the period
	of each pulse is adjustable using the PPLEN bits.
	*/


	/*
	The intensity of the IR emission is selectable using the LDRIVE
	control bits; corresponding to four, factory calibrated,
	current levels. If a higher intensity is required (E.g. longer
	detection distance or device placement beneath dark
	glass) then the LEDBOOST bit can be used to boost current
	up to an additional 300%.
	 */
}

void apds_read_result(uint8_t from_interrupt)
{
	uint8_t can_read = ERROR;
	uint8_t	read_data;
	uint8_t byte_read;

	/* read STATUS REGISTER 0x93 and check if PVALID is set */
	byte_read = apds_read_generic(e_register_STATUS,&read_data);

	if (byte_read != 0)
	{
		if (from_interrupt == APDS_READ_FROM_INTERRUPT)
		{
			if ((read_data & STATUS_REGISTER_PVALID) == STATUS_REGISTER_PINT)	/* check if PINT is set - we have received an interrupt */
			{
				can_read = SUCCESS;
			}
		}
		else
		{
			can_read = SUCCESS;
		}


		if ( (can_read == SUCCESS)
			&&	(read_data & STATUS_REGISTER_PVALID) == STATUS_REGISTER_PVALID)	/* check if PVALID is set*/
		{
			/* read PDATA 0x95 */
			byte_read = apds_read_generic(e_register_PDATA,&read_data);

			if (byte_read != 0)
			{

			}
		}

		if ((read_data & STATUS_REGISTER_PVALID) == STATUS_REGISTER_PGSAT)	/* check if PGSATT is set - Proximity saturation */
		{
			_p_saturation = SET;
			_p_error = e_proximity_error_saturation;
		}
		else
		{
			_p_saturation = RESET;
			_p_error = e_proximity_error_none;
		}
	}
	else
	{
		_p_error = e_proximity_error_data_not_valid;
	}


}
