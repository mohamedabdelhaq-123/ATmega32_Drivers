
#include "StdTypes.h"
#include "MemMap.h"
#include "ADC_Int.h"

void ADC_Init(ADC_VolRef_t vref,ADC_Prescaler_t scaler)
{
	//modes of Volt refrence
	switch(vref){
		case VREF_AREF:         // Input volt to AREF pin to measure according to it
		clear_bit(ADMUX,REFS0);
		clear_bit(ADMUX,REFS1);
		break;
		case VREF_AVCC:        // volt of Mc is the ref but,put capacitor on AVCC pin
		set_bit(ADMUX,REFS0);
		clear_bit(ADMUX,REFS1);
		break;
		case VREF_256:         // Vref=2.56
		set_bit(ADMUX,REFS0);
		set_bit(ADMUX,REFS1);
		break;
		
	}
	
	//prescaler ADC clk Setup  ,F.adc btw (50k-200k) 
	ADCSRA=ADCSRA&0xF8;//0b11111000
	scaler=scaler&0x07;//0b00000111
	ADCSRA=ADCSRA|scaler;
	
	set_bit(ADCSRA,ADEN);  	//ADC enable
	
}

u16 ADC_Read(ADC_Channel_t ch)  // Start conversion mode (just one reading)
{
	// select channel using mux
	ADMUX=ADMUX&0xe0;//0b11100000
	ADMUX=ADMUX|ch;
	set_bit(ADCSRA,ADSC); 	//start conversion mode
	while(get_bit(ADCSRA,ADSC));  // wait till bit is cleared that means the value of volt is ready
	return ADC; // get reading from reg but there is no reg called adc but collection btw ADCL & ADCH that has values of readings and reg adlar =0
}

u16 ADC_ReadVolt(ADC_Channel_t ch) 
{
	u16 volt;
	u16 adc=ADC_Read(ch);
	volt=(adc*(u32)5000)/1024;  // Vin= [(Vref*adc reading)/ max no. of steps] "2^10" --> 10 bits of adc regs.
	return volt;
	
}




