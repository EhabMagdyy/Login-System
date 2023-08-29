/*****************************************************
************    Author: Ehab Magdy		**************
************	SWC	  : adc.c    		**************
************	Data  : 28 Aug, 2023	**************
******************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>

#include "../../Library/STD_Types.h"
#include "../../Library/BIT_Math.h"
#include "../DIO/dio.h"
#include "adc.h"

void ADC_voidInit(void)
{
    /* Select Vref */
    SET_BIT(ADMUX, REFS0);
    CLEAR_BIT(ADMUX, REFS1);
    
    /* Select Adjustment */
    CLEAR_BIT(ADMUX, ADLAR);
    
    /* Disable auto trigger */
    CLEAR_BIT(ADCSRA, ADATE);
    
    /* Prescaler selection */
    CLEAR_BIT(ADCSRA, ADPS0);
    SET_BIT(ADCSRA, ADPS1);
    SET_BIT(ADCSRA, ADPS2);
    
    /* Enable ADC */
    SET_BIT(ADCSRA, ADEN);
}

u16 ADC_u16GetDigitalValue(u8 adc_channel)
{
    /* Select chanel */
    ADMUX &= 0xE0;
    ADMUX |= adc_channel;
    
    /* Start Conversion */
    SET_BIT(ADCSRA, ADSC);
    
    /* Wait for result */
    while(!READ_BIT(ADCSRA,ADIF));
    /* Clear flag by writing 1 */
    SET_BIT(ADCSRA, ADIF);
    
    /* Return result */
    return ADC_REG_VALUE;
}

