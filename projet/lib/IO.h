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

#ifndef IO_H
#define IO_H

#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>

enum PinState
{
    LOW,
    HIGH
};

enum Color
{
    OFF,
    RED,
    GREEN
};



void setPin(volatile uint8_t &port, const uint8_t pin, PinState state);
void setLED(volatile uint8_t &port, const uint8_t pins[], Color col);
void setInputInterrupts();

#endif