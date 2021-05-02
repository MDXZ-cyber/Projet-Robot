

#ifndef DEBUG_H
#define DEBUG_H

#define DEBUG
#include "UART.h"

#ifdef DEBUG
UART debug = UART();
#define PRINT(x) debug.byte(x)
//#define PRINT_WORD(x) debug.word(x)
#define PRINT_WORD(x, y) debug.word(x, y)
#else
#define PRINT(x) \
    do           \
    {            \
    } while (0)
#define PRINT_WORD(x, y) \
    do                   \
    {                    \
    } while (0)
//#define PRINT_WORD(x) do{} while(0)
#endif // Déplacer dans Debug.cpp

#endif