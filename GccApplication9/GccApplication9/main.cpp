#include <avr/io.h>
#include <avr/interrupt.h>

// global variable to count the number of overflows
volatile uint8_t tot_overflow;
int clocker = 1;

#define clkUp PORTC |=(1<<PORTC0) 
#define csUp PORTC |=(1<<PORTC1) 
#define  clkDown PORTC &=~(1<<PORTC0); 
#define  csDown PORTC &=~(1<<PORTC1);

// initialize timer, interrupt and variable
void timer1_init()
{
	// set up timer with prescaler = 8
	TCCR1B |= (1 << CS11);
	
	// initialize counter
	TCNT1 = 0;
	
	// enable overflow interrupt
	TIMSK0 |= (1 << TOIE1);
	
	// enable global interrupts
	sei();
	
	// initialize overflow counter variable
	tot_overflow = 0;
}

int Clock(){
	if (clocker%2==0){
	clkUp;}
	else{clkDown;}
	if(clocker == 39){
	csUp;}
	if(clocker == 40){
		csDown;
		clocker = 1;
	}
	clocker = clocker + 1;
	return 0;
}

// TIMER1 overflow interrupt service routine
// called whenever TCNT1 overflows
ISR(TIMER1_OVF_vect)
{
	// keep a track of number of overflows
	tot_overflow++;
	
	// check for number of overflows here itself
	// 61 overflows = 2 seconds delay (approx.)
	if (tot_overflow >= 3) // NOTE: '>=' used instead of '=='
	{
		Clock();
		// no timer reset required here as the timer
		// is reset every time it overflows
		
		tot_overflow = 0;   // reset overflow counter
	}
}


int main(void)
{
	// connect led to pin PC0
	DDRC = 0xFF;
	// initialize timer
	timer1_init();
	
	// loop forever
	while(1)
	{
		// do nothing
		// comparison is done in the ISR itself
	}
}