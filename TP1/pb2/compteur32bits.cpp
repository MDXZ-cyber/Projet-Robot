/*
 * Nom: compteur 32 bits
 * Copyright (C) 2005 Matthew Khouzam
 * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
 * Description: Ceci est un exemple simple de programme 
 * Version: 1.1
 */
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>

const uint8_t FERME = 0x00;
const uint8_t RED = 0x02;
const uint8_t GREEN = 0x01;

enum COULEUR
{
  ETEINT,
  ROUGE,
  VERT
};
enum ETAT
{
  ETAT1,
  ETAT2,
  ETAT3
};

void setDEL(COULEUR color)
{
  switch (color)
  {
  case ETEINT:
    PORTA = FERME;
    break;
  case ROUGE:
    PORTA = RED;
    break;
  case VERT:
    PORTA = GREEN;
    break;
  default:
    break;
  }
}

bool pressed (){
  return (PIND == 0x04);
}

int main()
{
  DDRA = 0x03;
  DDRD = 0x00;
  ETAT ETAT_COURANT = ETAT1;
  while (1) // boucle sans fin
  {
    switch (ETAT_COURANT)
    {
    case ETAT1:
    while (pressed()){
      setDEL(ROUGE);
      _delay_ms(1000);
      ETAT_COURANT = ETAT2;
    }
      break;
    case ETAT2:
      setDEL(ETEINT);
      _delay_ms(1000);
      ETAT_COURANT = ETAT3;
      break;
    case ETAT3:
      setDEL(VERT);
      _delay_ms(1000);
      ETAT_COURANT = ETAT1;
      break;
    }
  }
  return 0;
}
