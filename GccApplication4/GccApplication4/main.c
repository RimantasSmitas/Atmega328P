/*
 * GccApplication4.c
 *
 * Created: 2/17/2018 4:32:36 PM
 * Author : riman
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#define Led0On	PORTC |=(1<<PORTC0);
#define  Led0Off PORTC &=~(1<<PORTC0);

//PC5 for temp input 
//PC0 lights

void adc_init(void)
{
    ADMUX = (1<<REFS0);     //select AVCC as reference
    ADCSRA = (1<<ADEN) | 7;  
}

int readAdc()
{
    ADMUX = (1<<REFS0) | (101 & 0x0f);  //select input and ref
    ADCSRA |= (1<<ADSC);                 //start the conversion
    while (ADCSRA & (1<<ADSC));          //wait for end of conversion
    return ADCW;
}


int main(void)
{	
	PORTD = 0x00; // Initialize the I/O ports
	DDRD = 0xFF; // All Output
	
	//DDRC = 0xDF; // PIN5 as Input (based on 0-7)
	DDRC &= ~(1<<5);
	adc_init();
	int adcReading = 0;
    while (1) 
	{
	adcReading = readAdc();
    
	if (adcReading >400)
		{
		Led0On;
		}	
	else
	{
		Led0Off;
	}
		}
	}

