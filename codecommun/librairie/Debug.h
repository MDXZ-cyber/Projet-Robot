
#ifndef DEBUG_H
#define DEBUG_H

#include "UART.h"
#include "string.h"


class Debug
{
private:
    /* data */
    void initialise();
    static bool initialised;
    
public:
    Debug();
    void print(const uint8_t data);
    void print(const char message[],uint8_t size);
    
    
    ~Debug();

};

#endif



