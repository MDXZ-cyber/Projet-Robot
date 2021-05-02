#include "IO.h"


/*
Nom: 
Maxime Laroche
Marie-Claire Taché
Eduardo Falluh
Ahmed Gafsi
Nemro Yapmi Nji Monluh

Date de remise: 17 mars 2021

Description:
Cette classe permet de choisir la PIN sur laquelle se connecter (setPin) et controler la LED (setLED) 
et activer une interruption setInputInterrupts() au rising edge.
*/

/*
const uint8_t LED_PIN[] = {PA0, PA1};
volatile uint16_t time_left;
const uint16_t TIME_STEP_MS = 100;
volatile uint8_t button_pressed;*/

void setPin(volatile uint8_t &port, const uint8_t pin, PinState state)
{
    if (state == PinState::HIGH)
    {
        port |= 1 << pin;
    }
    else if (state == PinState::LOW)
    {
        port &= ~(1 << pin);
    }
}

void setLED(volatile uint8_t &port, const uint8_t pins[], Color col)
{
    switch (col)
    {
    case OFF:
        setPin(port, pins[0], LOW);
        setPin(port, pins[1], LOW);
        break;
    case RED:
        setPin(port, pins[0], LOW);
        setPin(port, pins[1], HIGH);
        break;
    case GREEN:
        setPin(port, pins[0], HIGH);
        setPin(port, pins[1], LOW);
        break;
    default:
        break;
    }
}


void setInputInterrupts()
{
    DDRD &= ~(1<<PD2) & ~(1<<PD3);
    EIMSK |= (1 << INT0) | (1 << INT1);
    //On veut uniquement réagir au rising edge
    EICRA |= /*(1 << ISC01);// &*/ ~(1 << ISC00);
    // sei permet de recevoir à nouveau des interruptions.
}


   