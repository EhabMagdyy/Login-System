/*****************************************************
************    Author: Ehab Magdy		**************
************	SWC	  : adc.h    		**************
************	Data  : 28 Aug, 2023	**************
******************************************************/


#ifndef ADC_H
#define	ADC_H

/********************  Includes **********************/
#include "../../Library/STD_Types.h"

/************** Macro definitions ********************/
/* To write at ADRL and ADRH both ___ (ADRL -> 0x24),(ADRH -> 0x25) */
#define ADC_REG_VALUE         *((volatile u16*) 0x24)

#define ADC_CHANNEL_0			0x00

/************** Functions Decelerations **************/
void ADC_voidInit(void);
u16 ADC_u16GetDigitalValue(u8 adc_channel);

#endif	/* ADC_H */

