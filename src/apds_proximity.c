/*
 *  @file  : apds_proximity.c
 *	
 *  @brief : Proximity engine handling. See datasheet pag 11
 *
 *  @author: Francesco Varani
 *  @date  : 13 nov 2020
 */
#include "apds_proximity.h"
#include "apds_flag.h"
#include "apds_register.h"

#include <stdint.h>


/*
 * The Proximity detection feature provides distance measurement
 * Detect/release events are interrupt driven, and occur whenever proximity result crosses
 * upper and/or lower threshold settings.
 */
void apds_start_proximity_engine(void)
{
	/*
	 * TODO check if in SLEEP or IDLE !
	 */

	/*
	 * Start ENABLE REGISTER:
	 * - ENABLE_REGISTER_PON = 1
	 * - ENABLE_REGISTER_PEN = 1
	 */
	apds_write_generic_(e_register_ENABLE, ENABLE_REGISTER_PON | ENABLE_REGISTER_PEN);
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

void apds_read_result(void)
{
	uint8_t	read_data;
	uint8_t byte_read;

	/* read STATUS REGISTER 0x93 and check if PVALID is set */
	byte_read = apds_read_generic(e_register_STATUS,&read_data);

	if (byte_read != 0)
	{
		if ((read_data & STATUS_REGISTER_PVALID) == STATUS_REGISTER_PVALID)	/* check if PVALID is set*/
		{
			/* read PDATA 0x95 */
			byte_read = apds_read_generic(e_register_PDATA,&read_data);

			if (byte_read != 0)
			{

			}
		}
	}
	else
	{

	}


}
