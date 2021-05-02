#include "StartMode.h"

StartMode::StartMode()
{
}
StartMode::~StartMode()
{
}

void StartMode::displayTerminal()
{
   uart.word("9600 bps  \n ");
};

void StartMode::display7segement(const uint8_t FIRST_SEGMENT, const uint8_t SECOND_SEGMENT, const uint8_t THIRD_SEGMENT, const uint8_t FORTH_SEGMENT)
{

   DDRA |= (1 << PD4 | 1 << PD5 | 1 << PD6 | 1 << PD7);
   DDRB |= (1 << PB5 | 1 << PB6 | 1 << PB7);
   DDRC |= (1 << PC0 | 1 << PC1);
   DDRD |= (1 << PD7);

   PORTA = FIRST_SEGMENT;
   PORTC |= 1 << PC1;
   PORTD |= 1 << PD7;
   PORTD &= ~(1 << PD7);

   PORTC &= ~(1 << PC1);
   PORTA = SECOND_SEGMENT;
   PORTC |= 1 << PC0;
   PORTC &= ~(1 << PC0);

   PORTA = THIRD_SEGMENT;
   PORTB |= 1 << PB6;
   PORTB |= 1 << PB7;
   PORTB &= ~(1 << PD7);
   PORTB &= ~(1 << PD6);
   PORTA = FORTH_SEGMENT;
   PORTB |= 1 << PB5;
   _delay_ms(TWO_SECOND); // This remains visible for 2 seconds then the displays deactivate
   PORTD |= 1 << PD7;
   PORTB |= 1 << PB7;
}

void StartMode::forward_backward()
{
   DDRD |= (1 << PD4) | (1 << PD5) | 1 << PD7;
   motor.foward(speed);
   _delay_ms(SECOND);
   motor.backward(speed);
   _delay_ms(SECOND);
   motor.backward(0);
};