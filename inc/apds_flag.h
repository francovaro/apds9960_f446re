/*
 *  @file  : apds_flag.h
 *	
 *  @brief	
 *
 *  @author: franc
 *  @date  : 13 nov 2020
 */

#ifndef INC_APDS_FLAG_H_
#define INC_APDS_FLAG_H_

/* Enable register */
#define ENABLE_REGISTER_GEN		(1<<6)	/* Gesture Enable */
#define ENABLE_REGISTER_PIEN	(1<<5)	/* Proximity Interrupt Enable. */
#define ENABLE_REGISTER_AIEN	(1<<4)	/* ALS Interrupt Enable.  */
#define ENABLE_REGISTER_WEN		(1<<3)	/* Wait Enable.  */
#define ENABLE_REGISTER_PEN		(1<<2)	/* Proximity Detect Enable.  */
#define ENABLE_REGISTER_AEN		(1<<1)	/* ALS Enable. */
#define ENABLE_REGISTER_PON		(1<<0)	/* Power ON */

/* Status Register 0x93 */
#define STATUS_REGISTER_CPSAT	(1<<7)
#define STATUS_REGISTER_PGSAT	(1<<6)
#define STATUS_REGISTER_PINT	(1<<5)
#define STATUS_REGISTER_AINT	(1<<4)
#define STATUS_REGISTER_GINT	(1<<2)
#define STATUS_REGISTER_PVALID	(1<<1)
#define STATUS_REGISTER_AVALID	(1<<0)


#endif /* INC_APDS_FLAG_H_ */
