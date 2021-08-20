#include <avr/io.h>
void init_adc() {
  // set pre-scaler to 128
  ADCSRA |= 0b00000111;
  // disable digital input on Analog input channels
  DIDR0 |= 0b11111111;
  // enable the ADC module
  ADCSRA |= 0b10000000;
}

uint16_t read_adc(uint8_t ADC_channel) {
  // select the ADC channel using a safety mask
  // so as not mess up any other bits in ADMUX
  ADMUX = (ADMUX & 0xF0) | (ADC_channel & 0x0F);
  // single conversion mode
  // start conversion
  ADCSRA |= 0b01000000;
  // wait until conversion ends (ADSC is LOW)
  while(!(ADCSRA & 0b00010000)) ;
  
  return ADC;
}

#define button1 2
#define button2 3
uint8_t channel;
//potentiometer connected to ADC0
int main (void) {

  DDRD &= 0b11110011;
  DDRD |= 0b01110000;
    PORTD &=0b10001111;
//DDRC &= 0b11111110;

  init_adc();//INITIALIZE ADC
  TCCR0A = 0b10000001;
  TCCR0B = 0b00000010;
while(1){
//channel = PIND;
  if(!(1<<button1)&PIND){
PORTD |= 0b00100000;
PORTD &= 0b11011111;

  }
  else{
  if(!(1<<button2)&PIND){
PORTD |= 0b00010000;
PORTD &= 0b11101111;
}
  }
OCR0A = read_adc(0)/4;
}
}
