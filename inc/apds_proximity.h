/*
 *  @file  : apds_proximity.h
 *	
 *  @brief	
 *
 *  @author: Francesco Varani
 *  @date  : 13 nov 2020
 */

#ifndef INC_APDS_PROXIMITY_H_
#define INC_APDS_PROXIMITY_H_

#include <stdint.h>

typedef enum
{
	e_proximity_error_none,
	e_proximity_error_saturation,
	e_proximity_error_data_not_valid,
	e_proximity_error_max
}t_proximity_error;

extern void apds_start_proximity_engine(void);
extern void apds_proximity_read_result(uint8_t from_interrupt);

#endif /* INC_APDS_PROXIMITY_H_ */
