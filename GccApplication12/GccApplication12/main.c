#include <avr/io.h>
#include <avr/interrupt.h>

#define clkUp PORTB |=(1<<PORTB1);
#define slowUp PORTB |=(1<<PORTB2);

#define clkDown PORTB &=~(1<<PORTB1);
#define slowDown PORTB &=~(1<<PORTB2);

uint16_t data;

void initTimer (){
TCCR1B |= (1 << CS10) | (1 << CS12); // prescaler to 1024
TCNT1 = 0;
}

int sleep10MS(int timer){
timer = timer *16; //since the chip is running at 16
TCNT1 = 0;	// setting the counter to 0
while (TCNT1 <= timer);	//When TCNT1 is equal to 1600 it will show 1 second
return 0;
}

void clocker(){
clkUp;
sleep10MS(4);
clkDown;
}

int readStuff2(){
	int bit; 
	data <<= 1 ;
	if(!(PIND & (1<<PORTD7))){
		bit = 0;
	}
	else{ bit = 1;}
	data |= (bit);
}

int main(void)
{
DDRC = 0xFF;
DDRB = 0xFF;
DDRD = 0X00;

// initialize timer
initTimer();
int finalData = 0;
// loop forever
while(1)
{
data = 0;
// at these oscilations the data gathering will take 13 * 2 * 100ms = 2600ms
// since it takes 26 sleep functions 1/26= 0.038s
// one sleep should be 38ms
//then you can send data on case 13
//thats incorect cause it would still run 40 sleeps in the total of the loop
// 1/40=0.025s
//  for one sleep 25 ms
//hoewer if you reduse the difrence in frequencies 13 to 1
// the first solution should work
// running the frequencies at 13 to 1
// having 4ms sleeps 1000/4=25
// just before the last sleep
// case 13 is perfect

slowDown;
int i = 0;
clocker();
sleep10MS(4);
clocker();
sleep10MS(4);
clocker();
sleep10MS(4);
for ( i=0; i<9; i++){
clocker();
readStuff2();
sleep10MS(4);
}
finalData = data;
slowUp;
sleep10MS(4);
}
}



