/*
 *  @file  : apds9660.h
 *	
 *  @brief : Header file to interface an apds9960
 *
 *  @author: Francesco Varani
 *  @date  : 13 nov 2020
 */

#ifndef INC_APDS9660_H_
#define INC_APDS9660_H_

typedef enum
{
	e_apds_sleep,
	e_apds_idle,
	e_apds_prox,
	e_apds_gesture,
	e_apds_wait,
	e_apds_color,
	e_apds_max
}t_apds_status;

extern void apds_init(void);


#endif /* INC_APDS9660_H_ */
