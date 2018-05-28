/**
 * \file
 *
 * \brief megaAVR STK600 AVR libc setbaud Example
 *
 * Copyright (c) 2011-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */

#define _ASSERT_ENABLE_
#include "compiler.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define TIMEOUT 250

// Set the correct BAUD and F_CPU defines before including setbaud.h
#include "conf_clock.h"
#include "conf_uart.h"
#include <util/setbaud.h>

void init(void)
{							//ADC Init
	ADMUX = (1<<REFS0);     //select AVCC as reference
	ADCSRA = (1<<ADEN) | 7;
	
//	TCCR1B |= (1 << CS12)| (0 << CS11) | (1 << CS10); //timer 
													// enabling the prescale to 1024	
}

int readAdc()
{
	ADMUX = (1<<REFS0) | (101 & 0x0f);  //select input and ref
	ADCSRA |= (1<<ADSC);                 //start the conversion
	while (ADCSRA & (1<<ADSC));          //wait for end of conversion
	return ADCW;
}


void Wait10ms(int y)
{	/*int x;
	for(x = 1; x <= y; x++){
		TCNT1 = 0; //set the timer to value 0
		while (TCNT1 <= 1562); // while loop that counts to 1562 which is equal to 1s
	}
	return;*/
}


void sendString(char *s); 
static uint8_t uart_getchar(void);
char checkOk(void);
/**
 * \brief Initialize the uart with correct baud rate settings
 *
 * This function will initialize the UART baud rate registers with the correct
 * values using the AVR libc setbaud utility. In addition set the UART to 8-bit,
 * 1 stop and no parity.
 */
static void uart_init(void)
{
#if defined UBRR0H
	/* These values are calculated by the setbaud tool based on the values
	defined in conf_clock.h and conf_uart.h. The only thing that the application
	need to do is to load these values into the correct registers.*/
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
#else
#error "Device is not supported by the driver"
#endif

	/* Check if the setbaud tool require that the 2x speed bit has to be set in
	order to reach the specified baudrate. */
#if USE_2X
	UCSR0A |= (1 << U2X0);
#endif

	// Enable RX and TX and set up port
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	// Set the TX pin as output
	UART_PORT_DDR |= (1 << UART_TX_PIN);
	// Set the RX pin as input
	UART_PORT_DDR &= ~(1 << UART_RX_PIN);

	// 8-bit, 1 stop bit, no parity, asynchronous UART
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00) | (0 << USBS0) |
			(0 << UPM01) | (0 << UPM00) | (0 << UMSEL01) |
			(0 << UMSEL00);
}

/**
 * \brief Function for sending a char over the UART
 *
 * \param data the data to send over UART
 */
static void uart_putchar(uint8_t data)
{
	// Make sure that the UART buffer is empty
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

/**
 * \brief Function for getting a char from the UART
 *
 * \note This function is blocking and will expect to receive something
 * on the UART.
 *
 * \retval uint8_t the data received from the UART
 * \retval 0       if timeout
 */
static uint8_t uart_getchar(void)
{
	uint8_t timeout = TIMEOUT;
	// Wait for RX to complete
	while ((!(UCSR0A & (1 << RXC0))) && timeout) {
		timeout--;
	}
	if (timeout) {
		return UDR0;
	} else {
		// No data, timeout
		return 0;
	}
}

/**
 * \brief Example application on how to use the libc setbaud utility.
 *
 * This application shows how to use the avr libc setbaud utility to get the
 * correct values for the baud rate registers. It also performs a test where
 * it sends a character on the UART and check if the same char is received
 * back.
 *
 * \note This application assumes that the TX and RX pins have been externally
 * shorted to create a loop back.
 */



char checkOk(void)
{
	char ch=0;
	char message[100];
	char index=0;

	while(uart_getchar()!='o');
	while(uart_getchar()!='k');
	while(uart_getchar()!='\r');
	while(uart_getchar()!='\n');
	
	return 1;	
	
}
char checkmctxok(void)
{
	char ch=0;
	char message[100];
	char index=0;

	while(uart_getchar()!='m');
	while(uart_getchar()!='a');
	while(uart_getchar()!='c');
	while(uart_getchar()!='_');
	while(uart_getchar()!='t');
	while(uart_getchar()!='x');
	while(uart_getchar()!='_');
	while(uart_getchar()!='o');
	while(uart_getchar()!='k');
	while(uart_getchar()!='\r');
	while(uart_getchar()!='\n');
	
	return 1;	
	
}

char checkaccecepted(void)
{
	char ch=0;
	char message[100];
	char index=0;

	while(uart_getchar()!='a');
	while(uart_getchar()!='c');
	while(uart_getchar()!='c');
	while(uart_getchar()!='e');
	while(uart_getchar()!='p');
	while(uart_getchar()!='t');
	while(uart_getchar()!='e');
	while(uart_getchar()!='d');
	while(uart_getchar()!='\r');
	while(uart_getchar()!='\n');
	
	return 1;
	
}
// this function takes a string and puts out chars until no more characters are available
void sendString(char *s){
   char *ptr = s;
   while(*ptr)
   {
      char ch = (*ptr);
	  	uart_putchar(ch);
      (*ptr) = ch;
      ++ptr;
   }
	
}
	
	
	
int main(void)
{
	// Set up baud rate registers
		init();
		Wait10ms(10);
	    uart_init();
		
		//Wait10ms(50);
		sendString("mac get status\r\n");
		sendString("mac get sync\r\n");

	/*	Setup; 
		sendString("mac set appeui 70B3D57ED000EDDB\r\n");
		sendString("mac set deveui 0004A30B001A6546\r\n");	
		sendString("mac set appkey 28E9F75BF2494007752ED4AC31E5760D\r\n");
		sendString("mac save\r\n");
	*/
		Wait10ms(10);
		sendString("mac join otaa\r\n");
		
		while(!checkOk());
		while(!checkaccecepted());
		
		//sendString("sys sleep 500\r\n");
		
	//	while(!checkOk());
	//	sendString("mac resume\r\n");
		

		DDRC &= ~(1<<5);
		
		int adcReading = 0;
		while (1)
		{
			adcReading = readAdc();
			char c = (char)adcReading;
			char message = ("radio tx %d\r\n",c); 	
			char message2 = ("mac tx uncnf 1 %d\r\n",c);
			
			//sendString("mac get status\r\n");
			sendString("mac tx uncnf 1 100\r\n");			
			
			//while(!checkmctxok());
			sendString(message2);
			
			
		}
	
	
}
