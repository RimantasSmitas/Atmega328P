/*
 * ATmega16_DHT11_Project_File.c
 *
 * http://www.electronicwings.com
 */ 
#define F_CPU 16E6

#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h> 
#define DHT11_PIN 6
uint8_t c=0,I_RH,D_RH,I_Temp,D_Temp,CheckSum;

void init(){
	
TCCR1B |= (1 << CS12)| (0 << CS11) | (1 << CS10); // enabling the prescale to 1024
	
}


void Wait10ms(int y)

{	int x;
	for(x = 1; x <= y; x++){
		TCNT1 = 0; //set the timer to value 0
		while (TCNT1 <= 1562); // while loop that counts to 1562 which is equal to 1s
	}
	return;
}


void Request()				/* Microcontroller send start pulse/request */
{
	DDRD |= (1<<DHT11_PIN);
	PORTD &= ~(1<<DHT11_PIN);	/* set to low pin */
	Wait10ms(2);				/* wait for 20ms */
	PORTD |= (1<<DHT11_PIN);	/* set to high pin */
}

void Response()				/* receive response from DHT11 */
{
	DDRD &= ~(1<<DHT11_PIN);
	while(PIND & (1<<DHT11_PIN));
	while((PIND & (1<<DHT11_PIN))==0);
	while(PIND & (1<<DHT11_PIN));
}

uint8_t Receive_data()			/* receive data */
{	
	for (int q=0; q<8; q++)
	{
		while((PIND & (1<<DHT11_PIN)) == 0);  /* check received bit 0 or 1 */
		Wait10ms(3);
		if(PIND & (1<<DHT11_PIN))/* if high pulse is greater than 30ms */
		c = (c<<1)|(0x01);	/* then its logic HIGH */
		else			/* otherwise its logic LOW */
		c = (c<<1);
		while(PIND & (1<<DHT11_PIN));
	}
	return c;
}

int main(void)
{	init();
	char data[5];
	
    while(1)
	
	{
	
		Request();		/* send start pulse */
		Response();		/* receive response */
		I_RH=Receive_data();	/* store first eight bit in I_RH */
		D_RH=Receive_data();	/* store next eight bit in D_RH */
		I_Temp=Receive_data();	/* store next eight bit in I_Temp */
		D_Temp=Receive_data();	/* store next eight bit in D_Temp */
		CheckSum=Receive_data();/* store next eight bit in CheckSum */
		
		int temp,humid;
		temp = D_Temp;
		humid = I_Temp;
		
		if ((I_RH + D_RH + I_Temp + D_Temp) != CheckSum)
		{
			
		}
		
		else
		{	
			
		}
				
	Wait10ms(1);
	}	
	
	
}