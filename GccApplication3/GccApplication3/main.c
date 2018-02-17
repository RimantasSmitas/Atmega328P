#include <avr/io.h>
#include <avr/interrupt.h>
#include<util/delay.h>
char buffer[5];
int ReadADC(uint8_t ch)
{
	ADMUX=ch;
	ADCSRA |= (1<<ADSC);
	while(!(ADCSRA&(1<<ADIF)));
	ADCSRA|=(1<<ADIF);
	return(ADC);
}

void initADC()
{
	ADMUX=(1<<REFS0);
	ADCSRA=(1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1);//|(0<<ADPS0);
}
int main()
{
	initADC();
	int analogVal;
	DDRD=0b0000000;
	DDRC = 0b11111111; // outputs
	
	while(1)
	{
		analogVal=ReadADC(0);
		analogVal=analogVal/2;
		
		//bLINKING
		PORTC = 0b00000001;
		_delay_ms(20);
	}
	return 0;
}