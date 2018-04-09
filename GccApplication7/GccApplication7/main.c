#include <avr/io.h>
#include <avr/interrupt.h>


#define Led0On	PORTC |=(1<<PORTC0)
#define Led1On	PORTC |=(1<<PORTC1)
#define Led2On	PORTC |=(1<<PORTC2)
#define  Led0Off PORTC &=~(1<<PORTC0);
#define  Led1Off PORTC &=~(1<<PORTC1);
#define  Led2Off PORTC &=~(1<<PORTC2);
int GlobalTimeIn4msIncriments = 0;
int delayint = 100;

int main(void)
{
	PORTD = 0x00; // Initialize the I/O ports
	DDRD = 0xFF; // All Output
	DDRC = 0xDF; // PIN5 as Input (based on 0-7)
	
	adc_init();
	timerinit();
	
	int x = 0;
	
	while (1)
	{
		LedDecider(x);
		timer(25);
		readAdc()
		x +=5;
	}
	
}


void timerinit(){
	// Set the Timer Mode to CTC
	TCCR0A |= (1 << WGM01);

	// Set the value that you want to count to
	OCR0A = 0xF9;

	TIMSK0 |= (1 << OCIE0A);    //Set the ISR COMPA vect

	sei();         //enable interrupts

	TCCR0B |= (1 << CS02);
	// set prescaler to 256 and start the timer
	
}

ISR (TIMER0_COMPA_vect)  // timer0 overflow interrupt overflow every 4 miliseconds
{
	GlobalTimeIn4msIncriments +=4 ;
	
}


void timer(int delayInMS)
{
	while(delayInMS<GlobalTimeIn4msIncriments)
	{
	}
	GlobalTimeIn4msIncriments = 0;
}

void adc_init(void)
{
	ADMUX = (1<<REFS0);     //select AVCC as reference
	ADCSRA = (1<<ADEN) | 8;
}

int readAdc()
{
	ADMUX = (1<<REFS0) | (101 & 0x0f);  //select input and ref
	ADCSRA |= (1<<ADSC);                 //start the conversion
	while (ADCSRA & (1<<ADSC));          //wait for end of conversion
	//return ADCW;
	LedDecider(ADCW);
}

int LedDecider(int x)
{
switch(x) {
		case (5):
			Led0On;
			Led2Off;
			Led1Off;
		break;
		case (10):
			Led0Off;
			Led1On;
			Led2Off
		break;
		case (15):
			Led0Off;
			Led1Off;
			Led2On;
		break;
		case (20):
			Led0On;
			Led1On;
			Led2Off;
		break;
		case (25):
			Led0On;
			Led1Off;
			Led2On;
		break;
		case (30):
			Led0Off;
			Led1On;
			Led2On;
		break;
		case (35):
			Led0On;
			Led1On;
			Led2On;
		break;
	}
}