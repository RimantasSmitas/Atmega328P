#include <avr/io.h>
#include <avr/interrupt.h>

int clocker = 1;

#define clkUp PORTB |=(1<<PORTB1);
#define slowUp PORTB |=(1<<PORTB2);

#define clkDown PORTB &=~(1<<PORTB1);
#define slowDown PORTB &=~(1<<PORTB2);




void inittimer (){

TCCR1B |= (1 << CS10) | (1 << CS12); // prescaler to 1024
TCNT1 = 0;

}


int sleeper1ms(int timer){
timer = timer *16; 
TCNT1 = 0;	// setting the counter to 0
while (TCNT1 <= 1600);	//When TCNT1 is equal to 1600 it will show 1 second
return 0;

}


int main(void)
{
	DDRC = 0xFF;
	DDRB = 0xFF;
	DDRD = 0X00;

	// initialize timer
	inittimer();
	
	
	// loop forever
	while(1)
	{
	int i; 
	for(i=1;i<20;i++)
	{clkUp;
	sleeper1ms(10);
	clkDown;
	sleeper1ms(10);
		}
		slowUp;
		sleeper1ms(10);
		slowDown;
		sleeper1ms(10);
			}
	}


int Clock(){
	clocker = clocker + 1;
	return 0;
}