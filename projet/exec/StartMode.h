#ifndef STARTMODE_H
#define STARTMODE_H

#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Time.h"
#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include "UART.h"
#include "Hbridge.h"

const uint16_t SECOND = 1000;
const uint16_t TWO_SECOND = 2000;

class StartMode
{
public:
   // Display the baud rate on the serieal communication terminal via RS-232
   void displayTerminal();

   // Display respectively the letters A, B, C and D on the four 7-segment display
   void display7segement(const uint8_t FIRST_SEGMENT, const uint8_t SECOND_SEGMENT, const uint8_t THIRD_SECOND, const uint8_t FORTH_SEGMENT);

   // both wheels turn full power clockwise for 1 second, then counterclockwise for 1 second.
   void forward_backward();

   StartMode();
   ~StartMode();

private:
   Hbridge motor{PORTD, PD6, PD3};
   UART uart = UART();
   const uint16_t FULL_SPEED = 65535;
   uint16_t speed = 99 * (FULL_SPEED / 100);
};

#endif
