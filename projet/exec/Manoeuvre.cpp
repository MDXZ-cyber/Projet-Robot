#include "Manoeuvre.h"

const uint16_t FULL_SPEED = 65535;

void Manoeuvre::manoeuvre1()
{
    
    uart.word("Manoeuvre 1 \n");
    uint16_t speed = 35 * (FULL_SPEED/100);
    afficheurDynamique(35, 35, pariteDecimale);

    motor.move(false, speed, true, speed);
    _delay_ms(1500);

    motor.move(true, speed, true, speed);
    _delay_ms(2000);

    motor.move(true, speed, false, speed);
    _delay_ms(1500);

    for (uint16_t i = 35; i <= 95; i += 5)
    {
        speed = i * (FULL_SPEED/100);
        afficheurDynamique(i, i, pariteDecimale);
        motor.move(true, speed, true, speed);
        _delay_ms(125);
    }
    _delay_ms(2000);
}

void Manoeuvre::manoeuvre2()
{
    
    uart.word("Manoeuvre 2 \n");
    uint16_t speed = 35 * (FULL_SPEED/100);
    afficheurDynamique(35, 35, pariteDecimale);

    motor.move(true, speed, false, speed);
    _delay_ms(1500);

    motor.move(true, speed, true, speed);
    _delay_ms(2000);

    motor.move(false, speed, true, speed);
    _delay_ms(1500);

    for (uint8_t i = 35; i <= 95; i += 5)
    {
        speed = i * (FULL_SPEED/100);
        afficheurDynamique(i, i, pariteDecimale);
        motor.move(true, speed, true, speed);
        _delay_ms(125);
    }
    _delay_ms(2000);
}

void Manoeuvre::manoeuvre3()
{
    uart.word("Manoeuvre 3 \n");
    uint16_t speed = 50 * (FULL_SPEED/100);
    afficheurDynamique(50, 50, pariteDecimale);

    motor.move(false, speed, false, speed);
    _delay_ms(1000);

    speed = 70 * (FULL_SPEED/100);
    afficheurDynamique(70, 70, pariteDecimale);
    motor.move(false, speed, true, speed);
    _delay_ms(1500);

    for (uint8_t i = 0; i <= 99; i += 3)
    {
        speed = i * (FULL_SPEED/100);
        afficheurDynamique(i, i, pariteDecimale);
        motor.move(true, speed, true, speed);
        _delay_ms(50);
    }

    for (uint8_t i = 99; i >= 74; i -= 5)
    {
        speed = i * (FULL_SPEED/100);
        afficheurDynamique(i, i, pariteDecimale);
        motor.move(true, speed, true, speed);
        _delay_ms(500);
    }
    _delay_ms(2000);
}

void Manoeuvre::manoeuvre4()
{
    uart.word("Manoeuvre 4 \n");
    uint16_t speed = 78 * (FULL_SPEED/100);
    motor.move(true, speed, true, speed);
    for (uint8_t i = 78; i >= 48; i -= 2)
    {
        speed = i * (FULL_SPEED/100);
        afficheurDynamique(i, 78, pariteDecimale);
        motor.move(true, speed, true, 78 * (FULL_SPEED/100));
        _delay_ms(250);
    }
    _delay_ms(1500);

    for (uint8_t i = 48; i <= 78; i += 2)
    {
        speed = i * (FULL_SPEED/100);
        afficheurDynamique(i, 78, pariteDecimale);
        motor.move(true, speed, true, 78 * (FULL_SPEED/100));
        _delay_ms(250);
    }
    _delay_ms(2000);
}

void Manoeuvre::manoeuvre5()
{
    uart.word("Manoeuvre 5 \n");
    uint16_t speed = 78 * (FULL_SPEED/100);
    motor.move(true, speed, true, speed);
    for (uint8_t i = 78; i >= 48; i -= 2)
    {
        speed = i * (FULL_SPEED/100);
        afficheurDynamique(78, i, pariteDecimale);
        motor.move(true, 78 * (FULL_SPEED/100), true, speed);
        _delay_ms(250);
    }
    _delay_ms(1500);

    for (uint8_t i = 48; i <= 78; i += 2)
    {
        speed = i * (FULL_SPEED/100);
        afficheurDynamique(78, i, pariteDecimale);
        motor.move(true, 78 * (FULL_SPEED/100), true, speed);
        _delay_ms(250);
    }
    _delay_ms(2000);
}


//fonction permettant d'écrire de transformer un nombre NN en 0xNN  ex:  12 => 0x12 
uint8_t convertirNNen0xNN(uint8_t num)
{
    unsigned int a = num / 10;
    unsigned int b = num % 10;
    num = a << 4;
    num |= b;
    return num;
}

//fonction permettant d'afficher les vitesses des roues sur l'afficheur 7-segment.
void afficherVitesse(uint8_t vitesseRoueGauche, uint8_t vitesseRoueDroite)
{
   DDRA |= (1 << PD4 | 1 << PD5 | 1 << PD6 | 1 << PD7);
   DDRB |= (1 << PB5 | 1 << PB6 | 1 << PB7);
   DDRC |= (1 << PC0 | 1 << PC1);
   DDRD |= (1 << PD7);

   PORTA = vitesseRoueDroite << 4; 
   PORTC |= 1 << PC1;
   PORTD = 1 << PD7;
   PORTD = 0x00;

   PORTC &= ~(1<<PC1); 
   PORTA = (vitesseRoueDroite & 0xf0);  
   PORTC |= 1 << PC0;
   PORTD = 0x00;
   PORTC &= ~(1<<PC0);  

   PORTA = (vitesseRoueGauche << 4); 
   PORTB = 1 << PB6;
   PORTB = 1 << PB7;
   PORTB &= ~(1<<PB6);
   PORTB &= ~(1<<PB7);
   PORTA = vitesseRoueGauche & 0xf0; 
   PORTB = 1 << PB5;

}
//fonction permettant d'afficher les vitesses selon le mode d'affichage décimal ou hexadécimal
void afficheurDynamique(uint8_t vitesseRoueGauche, uint8_t vitesseRoueDroite, int nombre)
{
    if (nombre % 2 == 0)
        afficherVitesse(convertirNNen0xNN(vitesseRoueGauche), convertirNNen0xNN(vitesseRoueDroite));
    else
        afficherVitesse(vitesseRoueGauche, vitesseRoueDroite);
}

//fonction permettant de désactiver l'afficheur 7-segment.
void desactiverAffichage(Manoeuvre &manoeuvre)
{
    PORTD = 1 << PD7;
    PORTB = 1 << PB7;
    manoeuvre.motor.move(true, 0, true, 0);
}
