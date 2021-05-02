
#define F_CPU 8000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

const uint8_t ROUGE = 0x02;
const uint8_t VERT = 0x01;
const uint8_t ETEINT = 0x00;

volatile uint8_t etat_courant = 0;

enum Etat
{
    ETAT1,
    ETAT2,
    ETAT3
};

void changeState(uint8_t etat)
{
    switch (etat_courant)
    {
    case ETAT1:
        etat_courant = ETAT2;
        break;

    case ETAT2:
        etat_courant = ETAT3;
        break;

    case ETAT3:
        etat_courant = ETAT1;
        break;
    }
}

ISR(INT0_vect)
{

    _delay_ms(30);
    changeState(etat_courant);
    EIFR |= (1 << INTF0);
}

ISR(INT1_vect)
{
    _delay_ms(30);
    changeState(etat_courant);
    EIFR |= (1 << INTF1);
}

void initialisation(void)
{
    cli();
    DDRA = 0xff;
    DDRD = 0x00;
    EIMSK |= (1 << INT0) | (1 << INT1);
    EICRA |= (1 << ISC01) | (1 << ISC00) | (1 << ISC11) | (1 << ISC10);
    sei();
}

int main()
{
    initialisation();
    while (true)
    {
        switch (etat_courant)
        {
        case ETAT1:
            PORTA = ETEINT;
            break;
        case ETAT2:
            PORTA = VERT;
            break;
        case ETAT3:
            PORTA = ROUGE;
            break;
        }
    }

    return 0;
}