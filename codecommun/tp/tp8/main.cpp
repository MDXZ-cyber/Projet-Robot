#include "IO.h"
#include "UART.h"
#include "Hbridge.h"
#include "Timer.h"
#include "can.h"
#include "Debug.h"
#define DEBUG

#ifdef DEBUG
    Debug debug = Debug();
#define PRINT(x) debug.print(x)
#define PRINT_WORD(x,y) debug.print(x,y)
#else
#define PRINT(x) do {} while (0)
#define PRINT_WORD(x,y) do {} while(0)
#endif

enum Etat
{
    INIT,
    ETAT1,
    ETAT2
};



volatile uint16_t countA=1;
ISR(TIMER1_COMPA_vect){
//    _delay_ms(1);
    countA++;
    //PRINT(('a'));
    TIFR1 |= (1 << OCF1A);
}
volatile uint16_t countB=1;


int main()
{

    UARTInitialization();
    DDRD=0xFF;
    DDRA=0xFF;
    DDRB=0xFF;
    PRINT(('X'));
    PRINT(('Y'));
    volatile uint8_t speed=125;
    
    


    // Moteur
    Timer0 t;
    Hbridge h(PORTA, PA0,PA1, t);
    bool leftFoward = true;
    bool rightFoward = false;
    uint8_t leftSpeed = 254;
    uint8_t rightSpeed =50;
    h.move(leftFoward, leftSpeed,rightFoward, rightSpeed);
    _delay_ms(10000);



    //Minuterie avec interuption (sans rapport au moteur
    Timer1 t1;
    t1.setInterupts(true, false, false);
    cli();
    Timer *timer = & t1;
    timer->setWaveform(CTC);
    timer->setPrescaler(1024);
    timer->setCompareOutput(CNORMAL);
    timer->setCompareValue(250,250);
    sei();
    
    _delay_ms(2000);
    while (true)
    {
        /* code */
        // if(value==0){
        //     UARTTransmission('A');
        // }
        _delay_ms(20);
        
            speed+=1;
            // timer->setCompareValue(speed,speed);
            h.foward(speed);
        
        countA++;
        countA--;
        if(countA%10==0){
            PRINT(('A'));
        }
        if(countB==0){
            PRINT(('B'));
        }


    }
    
    return 0;
}