#include <avr/io.h>
#include <avr/interrupt.h>

#define Led0On	PORTC |=(1<<PORTC0)
#define Led1On	PORTC |=(1<<PORTC1)
#define Led2On	PORTC |=(1<<PORTC2)
#define  Led0Off PORTC &=~(1<<PORTC0);
#define  Led1Off PORTC &=~(1<<PORTC1);
#define  Led2Off PORTC &=~(1<<PORTC2);
int time = 0;
int delayint = 250; 

int main(void)
{
	PORTD = 0x00; // Initialize the I/O ports
	DDRD = 0xFF; // All Output
	DDRC = 0xDF; // PIN5 as Input (based on 0-7)
		
	// Set the Timer Mode to CTC
	TCCR0A |= (1 << WGM01);

	// Set the value that you want to count to
	OCR0A = 0xF9;

	TIMSK0 |= (1 << OCIE0A);    //Set the ISR COMPA vect

	sei();         //enable interrupts

	TCCR0B |= (1 << CS02);
	// set prescaler to 256 and start the timer
	while (1)
	{
		//main loop
	}
}


ISR (TIMER0_COMPA_vect)  // timer0 overflow interrupt overflow every 4 seconds
{
	time +=4; 
	if (time>delayint){
		time = 0;
	}
	LedDecider(time);
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
	}}