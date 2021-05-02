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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint8_t convertirNNen0xNN(uint8_t num)
{
  unsigned int a = num / 10;
  unsigned int b = num % 10;
  num = a << 4;
  num |= b;
  return num;
}

void afficherVitesse(uint8_t vitesseRoueGauche, uint8_t vitesseRoueDroite)
{
  DDRA = 0xff;
  DDRB = 0xff;
  DDRC = 0xff;
  DDRD = 1 << PD7;

  PORTA = (vitesseRoueDroite & 0xf0);
  //_delay_ms(1000);

  PORTC = 0x01;
  // _delay_ms(1000);

  PORTD = (1 << PD7);
  //_delay_ms(1000);

  PORTC = 0x02;
  PORTA = vitesseRoueDroite << 4;
  //_delay_ms(1000);
  PORTD = 0x00;

  PORTC = 0x00;
  PORTB = (1 << PD3);

  PORTB = 1 << PD5; //0b00100000; //0x20
  PORTA = (vitesseRoueGauche & 0xf0);
  // _delay_ms(1000);

  PORTB = 1 << PD6; //0b01000000; //0x40
  PORTA = (vitesseRoueGauche << 4);
  //_delay_ms(1000);

  // desactiver les afficheurs
}

int main()
{

  //afficherVitesse(convertirNNen0xNN(29), convertirNNen0xNN(92));

  DDRA = (1 << PD4 | 1 << PD5 | 1 << PD6 | 1 << PD7);
  DDRB = (1 << PB5 | 1 << PB6 | 1 << PB7);
  DDRC = (1 << PC0 | 1 << PD1);
  DDRD = (1 << PD7);

  PORTA = 0xD0 ; //first_segment; //0xC0 ; //192
  PORTC = 1 << PC1;
  PORTD = 1 << PD7;
  PORTD = 0x00;

  PORTC = 0x00;
  PORTA = 0xC0 ; //first_segment; //0xC0 ; //192
  PORTC = 1 << PC0;
  PORTD = 0x00;
  PORTC = 0x00;

  
  // B7 = D7
  //B6 = C1
  PORTA = 0xB0 ; //first_segment; //0xC0 ; //192
  PORTB = 1 << PB6;
  PORTB = 1 << PB7;
  PORTB = 0X00;
  PORTB = 0X00;
  PORTA = 0xA0 ; //first_segment; //0xC0 ; //192
  PORTB = 1 << PB5;
  _delay_ms(1000);
  PORTD = 1 << PD7;
  PORTB = 1 << PB7;





  // PORTC = 1 << PD2;
  // PORTA = 0xD0 ; //second_segment; //0xD0; //208
  // _delay_ms(1000);

  // PORTC = 0x00; // zero n'est pas un chiffre magique, 1 aussi dans certain cas
  // PORTB = (1 << PD3);

  // PORTB = 1 << PD6;      // 0b01000000;
  // PORTA = 0xB0; //third_segment; //0xB0; //176
  // _delay_ms(1000);

  // PORTB = 1 << PD5;      //0b00100000;
  // PORTA = 0xA0; //forth_segment; //0xA0; //160
  // _delay_ms(1000);

  // // desactiver les afficheurs
  // PORTD = 0x00;
  // PORTB = 0x00;

  return 0;
}

// #include "startMode.h"

//    void startMode::displayTerminal(){
//      // UART uart = UART();
//       uart.word("2400 bps  \n ");
//    };

//    void startMode::display7segement(uint8_t first_segment, uint8_t second_segment,uint8_t third_segment ,uint8_t forth_segment){
//    DDRA = 0xff;
//    DDRB = 0xff;
//    DDRC = 0xff;

//    PORTA = first_segment ;//0xC0; //192

//    PORTC = 0x01;
//    PORTD = (1 << PD7);

//    PORTC = 0x02;
//    PORTA = second_segment ; //0xD0; //208
//    _delay_ms(1000);

//    PORTC = 0x00;
//    PORTB = (1 << PD3);

//    PORTB = 1 << PD6; // 0b01000000;
//    PORTA = third_segment ; //0xB0; //176
//    _delay_ms(1000);

//    PORTB = 1 << PD5 ; //0b00100000;
//    PORTA = forth_segment ; //0xA0; //160
//    _delay_ms(1000);

//    // desactiver les afficheurs
//    PORTD = 0x00;
//    PORTB = 0x00;

// }

//    void startMode::forward_backward(){
//       uint16_t speed = 0.99 * 65536 ;
//       motor.foward(speed);
//       _delay_ms(1000);
//       motor.backward(speed);
//       _delay_ms(1000);
//    };