/*
 * BlinkLED.c
 *
 * Created: 4/11/2018 9:19:02 AM
 * Author : riman
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#define Led0On	PORTC |=(1<<PORTC0)
#define  Led0Off PORTC &=~(1<<PORTC0);
#define Led1On	PORTC |=(1<<PORTC1)
#define  Led1Off PORTC |=(1<<PORTC1);
#define Led2On	PORTC |=(1<<PORTC2)
#define  Led2Off PORTC &=~(1<<PORTC2);

// TIMER0 overflow interrupt service routine
// called whenever TCNT0 overflows


ISR(TIMER0_OVF_vect)
{
	// keep a track of number of overflows
	PORTC ^= 0b00000100;
	
}

void timer0_init()
{
	TIMSK0=(1<<TOIE0) | (1<<TOIE1);
    // set timer0 counter initial value to 0
    TCNT0=0x00;
    // start timer0 with /1024 prescaler
    TCCR0B = (1<<CS02) | (1<<CS00);
	
	
}



void leder(){
	PORTC ^= 0b00000010;
	}
	
ISR(INT0_vect){
	leder();
}

void inittimer (){
	TCCR1B |= (1 << CS10) | (1 << CS12); // prescaler to 1024
	TCNT1 = 0;
}

int timer10ms(int tenMs){
	
	TCNT1 = 0;	// setting the counter to 0
	while (TCNT1 <= tenMs);	//When TCNT1 is equal to 1600 it will show 1 second
	return 0;
}

void blinker(){
		Led0On;
		timer10ms(16000);
		Led0Off;
		timer10ms(16000);
		
}

int main(void)
{
	
	DDRD = 0x00; // All Output
	DDRC = 0xFF;
	PORTD |= (1 << PORTD2); 
	inittimer();
	timer0_init();
	EICRA |= (1 << ISC00);    // set INT0 to trigger on ANY logic change
	EIMSK |= (1 << INT0);     // Turns on INT0
	EICRA |= 0b00000011;
	sei();

    /* Replace with your application code */
    while (1) 
    {
			blinker();	
    }
}

