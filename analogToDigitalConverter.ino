#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define clk 5
#define  strt 2
#define EOC 3
#define  outEnb 4
int main(void){ /*Configure the input(PD2,PD4,PD5)/ output(PD3) registersand Timer 0 interrupt and prescaler*/
  DDRD |= 0b00110100;//
  DDRD = 0b11110111;//
  PORTD = 0b11001011;
  TIMSK0 = 0b00000001;
  TCCR0B |= 0b00000001;//no prescale
  SREG |= 0b10000000;
  TCNT0 = 240;
  while (1)
  { /*Generate the start signal and check the EOC signal then generate the output enable signal*/
    PORTD |= (1 << strt); //set start
    _delay_us(0.1);
    //  PORTD &= 0b00000100;//clear
    PORTD &= !(1 << strt); //clear
    while (PIND&(1<<EOC));
    //while (!(PIND&(1<<EOC)));
    while (!(PIND&(1<<EOC)));
    PORTD |= (1 << outEnb);
    _delay_us(100);
    PORTD &= !(1 << outEnb);}
}
ISR(TIMER0_OVF_vect) { /*Generate the clock signal on Timer 0 overflow*/
  TCNT0 = 240;
  TIFR0 |= 0b00000001;
  PORTD ^= (1 << clk);}
