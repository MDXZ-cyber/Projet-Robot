#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>

const uint8_t FERME = 0x00;
const uint8_t RED = 0x02;
const uint8_t GREEN = 0x01;
const uint8_t MODE_ENTREE = 0x00;
const uint8_t MODE_SORTIE = 0x03;

enum ETAT
{
  ETAT1,
  ETAT2,
  ETAT3
};

volatile uint8_t ETAT_COURANT = ETAT1;

bool isPressed(){
    if (PIND & (1 << PD2)){
      while(PIND & (1 << PD2)){}
      return true;
    }else if(PIND & (1 << PD3)){
      return true;
    }
    return false;
}

ISR(INT0_vect)
{
  _delay_ms(30);
  if (isPressed())
  {
    ETAT_COURANT = ETAT2;
  }
  EIFR |= (1 << INTF0);
}

ISR(INT1_vect)
{
  _delay_ms(30);
  if (isPressed())
  {
    ETAT_COURANT = ETAT3;
  }
  EIFR |= (1 << INTF1);
}

void setDEL(ETAT state)
{
  switch (ETAT_COURANT)
  {
  case ETAT1:
    PORTA = FERME;
    _delay_ms(1000);
    ETAT_COURANT = ETAT1;
    break;
  case ETAT2:
    PORTA = RED;
    _delay_ms(1000);
    ETAT_COURANT = ETAT2;
    break;
  case ETAT3:
    PORTA = GREEN;
    _delay_ms(1000);
    ETAT_COURANT = ETAT1;
    break;
  }
}

void initialisation(void)
{
  cli();
  DDRA = MODE_SORTIE;
  DDRD = MODE_ENTREE;
  EIMSK |= (1 << INT0) | (1 << INT1);
  EICRA |= (1 << ISC01) | (1 << ISC00) | (1 << ISC11) | (1 << ISC10);
  sei();
}

int main()
{
  while (true)
  {
    setDEL(ETAT1);
    _delay_ms(1000);
    setDEL(ETAT2);
    _delay_ms(1000);
    setDEL(ETAT3);
    _delay_ms(1000);
  }

  return 0;
}
