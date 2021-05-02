

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