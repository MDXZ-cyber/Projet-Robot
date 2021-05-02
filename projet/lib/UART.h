
#ifndef UART_H
#define UART_H


#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/eeprom.h>
#include "string.h"


class UART
{
private:
    /* data */
    void initialise();
    void UARTTransmission(uint8_t data);
    void UARTInitialization();
    static bool initialised;
    
public:
    UART();

    //Prints a byte via RS-232
    void byte(const uint8_t data);

    /* Prints a word via RS-232. Word lenght is specified by size parameter*/
    void word(const char message[],uint8_t size);

    /*Prints a word via RS-232. word needs a null termnating character ('\0') to stop printing*/
    void word(const char message[]);

    /* Returns the next byte that is received by the RS-232*/
    uint8_t UARTReceive();

    /*Reads values in EEPROM, starting at startAddress and stops when it reaches a value equal to endValue*/
    void readUntil(uint8_t *startAddress, uint8_t endValue);
    
    
    ~UART();

};

#endif



