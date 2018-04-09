char dat[10];                                // buffer for receving/sending messages
char i,j;

sbit  rs485_rxtx_pin  at PORTD2_bit;         // set transcieve pin
sbit  rs485_rxtx_pin_direction at DDD2_bit;  // set transcieve pin direction

// Interrupt routine
void interrupt() org IVT_ADDR_USART_RXC {
  RS485Master_Receive(dat);
}

void main(){

  long cnt = 0;
  
  PORTA  = 0;                          // clear PORTA
  PORTB  = 0;                          // clear PORTB
  PORTC  = 0;                          // clear PORTC

  DDRA   = 0xFF;                       // set PORTA as output
  DDRB   = 0xFF;                       // set PORTB as output
  DDRC   = 0xFF;                       // set PORTB as output
  
  UART1_Init(9600);                    // initialize UART1 module
  Delay_ms(100);

  RS485Master_Init();                  // initialize MCU as Master
  dat[0] = 0xAA;
  dat[1] = 0xF0;
  dat[2] = 0x0F;
  dat[4] = 0;                          // ensure that message received flag is 0
  dat[5] = 0;                          // ensure that error flag is 0
  dat[6] = 0;

  RS485Master_Send(dat,1,160);

  SREG_I_bit  = 1;                     // enable global interrupt
  RXCIE_bit   = 1;                     // enable interrupt on UART receive

  while (1){
                                       // upon completed valid message receiving
                                       //   data[4] is set to 255
    cnt++;
    if (dat[5])  {                     // if an error detected, signal it
      PORTC = dat[5];                  //   by setting PORTC
    }
    if (dat[4]) {                      // if message received successfully
      cnt = 0;
      dat[4] = 0;                      // clear message received flag
      j = dat[3];
      for (i = 1; i <= dat[3]; i++) {  // show data on PORTB
        PORTB = dat[i-1];
      }                                // increment received dat[0]
      dat[0] = dat[0]+1;               // send back to slave
      Delay_ms(1);
      RS485Master_Send(dat,1,160);

    }

    if (cnt > 100000) {                // if in 100000 poll-cycles the answer
      PORTA++;                         //   was not detected, signal
      cnt = 0;                         //   failure of send-message
      RS485Master_Send(dat,1,160);
      if (PORTA > 10){                 // if sending failed 10 times
        PORTA = 0;
        RS485Master_Send(dat,1,50);    //   send message on broadcast address
      }
    }
  }
}