/*

Nom: 
Maxime Laroche
Marie-Claire Taché
Eduardo Falluh
Ahmed Gafsi
Nemro Yapmi Nji Monluh

Date de remise: 17 mars 2021

Description: ce fichier est l'implémentation des fonctions permettant d'utiliser les timers

*/

#include "Timer.h"

void Timer::setWaveform(Waveform mode)
{
    /* Calls the right function to set the desired waveform*/
    //cli();
    switch (mode)
    {
    case WNORMAL:
        setNormal();
        break;
    case PWM_PHASE_CORRECT:
        setPWMPhaseCorrect();

        break;
    case CTC:
        setCTC();
        break;
    case PWM_FAST_PWM:
        setFastPWM();

        break;
    default:
        break;
    }
    //sei();
}

void Timer::setCompareOutput(CompareOutput mode)
{
    /*Sets the compare Output Mode*/
    // cli();
    switch (mode)
    {
    case CNORMAL:
        setCompareNormal();
        break;
    case TOGGLE:
        setCompareToggle();
        break;
    case CLEAR:
        setCompareClear();
        break;
    case SET:
        setCompareSet();
        break;
    default:
        break;
    }
    ////sei();
}
// void Timer::setCompareValuePercent(uint8_t percentA, uint8_t percentB)
// {
//     uint8_t hundred = 100;
//     uint8_t bits = 255;

//     uint8_t valueA = 100;
//     uint8_t valueB = 100;

//     setCompareValue(valueA, valueB);
// };

//----------------------------------------------
//Timer0

Timer0::Timer0(/* args */)
{

    setInterupts(false, false, false);
}

Timer0::~Timer0()
{
}

void Timer0::setNormal()
{
    TCCR0A &= ~(1 << WGM01) & ~(1 << WGM00);
    TCCR0B &= ~(1 << WGM02);
}
void Timer0::setPWMPhaseCorrect()
{
    TCCR0A &= ~(1 << WGM01);
    TCCR0A |= (1 << WGM00);
    TCCR0B &= ~(1 << WGM02);
}
void Timer0::setCTC()
{
    TCCR0A |= (1 << WGM01);
    TCCR0A &= ~(1 << WGM00);
    TCCR0B &= ~(1 << WGM02);
}
void Timer0::setFastPWM()
{
    TCCR0A |= (1 << WGM01) | (1 << WGM00);
    TCCR0B &= ~(1 << WGM02);
}
void Timer0::setCompareNormal()
{
    TCCR0A &= ~(1 << COM0A1) & ~(1 << COM0A0);
    TCCR0A &= ~(1 << COM0B1) & ~(1 << COM0B0);
}
void Timer0::setCompareToggle()
{
    TCCR0A &= ~(1 << COM0A1);
    TCCR0A |= (1 << COM0A0);

    TCCR0A &= ~(1 << COM0B1);
    TCCR0A |= (1 << COM0B0);
}
void Timer0::setCompareClear()
{
    TCCR0A |= (1 << COM0A1);
    TCCR0A &= ~(1 << COM0A0);

    TCCR0A |= (1 << COM0B1);
    TCCR0A &= ~(1 << COM0B0);
}
void Timer0::setCompareSet()
{
    TCCR0A |= (1 << COM0A1) | (1 << COM0A0);

    TCCR0A |= (1 << COM0B1) | (1 << COM0B0);
}
void Timer0::setPrescaler(uint16_t value)
{
    switch (value)
    {
    case 0:
        TCCR0B &= ~(1 << CS02) & ~(1 << CS01) & ~(1 << CS00);
        break;
    case 1:
        TCCR0B &= ~(1 << CS02) & ~(1 << CS01);
        TCCR0B |= (1 << CS00);
        break;
    case 8:
        TCCR0B &= ~(1 << CS02) & ~(1 << CS00);
        TCCR0B |= (1 << CS01);
        break;
    case 64:
        TCCR0B &= ~(1 << CS02);
        TCCR0B |= (1 << CS01) | (1 << CS00);
        break;
    case 256:
        TCCR0B &= ~(1 << CS01) & ~(1 << CS00);
        TCCR0B |= (1 << CS02);
        break;
    case 1024:
        TCCR0B |= (1 << CS02) | (1 << CS02);
        TCCR0B &= ~(1 << CS01);
        break;
    default:
        break;
    }
}

void Timer0::setTimerValue(uint8_t value)
{
    TCNT0 = value;
}
void Timer0::setCompareValue(uint8_t A, uint8_t B)
{
    OCR0A = A;
    OCR0B = B;
}

void Timer0::setTimerStartValue(uint8_t percent)
{
    uint8_t hundred = 100;
    uint8_t bits = 255;
    int value = (percent * bits) / hundred;
    percent = value;
    setTimerValue(percent);
}

void Timer0::setInterupts(bool compareA, bool compareB, bool compareOF)
{
    //cli();
    if (compareA)
    {
        TIMSK0 |= (1 << OCIE0A);
    }
    else
    {
        TIMSK0 &= ~(1 << OCIE0A);
    }

    if (compareB)
    {
        TIMSK0 |= (1 << OCIE0B);
    }
    else
    {
        TIMSK0 &= ~(1 << OCIE0B);
    }

    if (compareOF)
    {
        TIMSK0 |= (1 << TOIE0);
    }
    else
    {
        TIMSK0 &= ~(1 << TOIE0);
    }
    //sei();
}

//----------------------------------------------
//Timer1

Timer1::Timer1(/* args */)
{
    setInterupts(false, false, false);
}

Timer1::~Timer1()
{
}

void Timer1::setNormal()
{
    TCCR1A &= ~(1 << WGM11) & ~(1 << WGM10);
    TCCR1B &= ~(1 << WGM12) & ~(1 << WGM13);
}
void Timer1::setPWMPhaseCorrect()
{
    TCCR1B |= WGM13 << 1;
    TCCR1B &= ~(1 << WGM12);

    TCCR1A |= WGM10 << 1;
    TCCR1A &= ~(1 << WGM11);
}
void Timer1::setCTC()
{
    TCCR1A |= (1 << WGM11);
    TCCR1A &= ~(1 << WGM10);
    TCCR1B &= ~(1 << WGM12);
}
void Timer1::setFastPWM()
{
    TCCR1A |= (1 << WGM10);
    TCCR1A &= ~(1 << WGM11);
    TCCR1B |= ~(1 << WGM12);
    TCCR1B = ~(1 << WGM13);
}
void Timer1::setCompareNormal()
{
    TCCR1A &= ~(1 << COM1A1) & ~(1 << COM1A0);
    TCCR1A &= ~(1 << COM1B1) & ~(1 << COM1B0);
}
void Timer1::setCompareToggle()
{
    TCCR1A &= ~(1 << COM1A1);
    TCCR1A |= (1 << COM1A0);

    TCCR1A &= ~(1 << COM1B1);
    TCCR1A |= (1 << COM1B0);
}
void Timer1::setCompareClear()
{
    TCCR1A |= (1 << COM1A1);
    TCCR1A &= ~(1 << COM1A0);

    TCCR1A |= (1 << COM1B1);
    TCCR1A &= ~(1 << COM1B0);
}
void Timer1::setCompareSet()
{
    TCCR1A |= (1 << COM1A1) | (1 << COM1A0);

    TCCR1A |= (1 << COM1B1) | (1 << COM1B0);
}
void Timer1::setPrescaler(uint16_t value)
{
    switch (value)
    {
    case 0:
        TCCR1B &= ~(1 << CS12) & ~(1 << CS11) & ~(1 << CS10);
        break;
    case 1:
        TCCR1B &= ~(1 << CS12) & ~(1 << CS01);
        TCCR1B |= (1 << CS10);
        break;
    case 8:
        TCCR1B &= ~(1 << CS12) & ~(1 << CS10);
        TCCR1B |= (1 << CS11);
        break;
    case 64:
        TCCR1B &= ~(1 << CS12);
        TCCR1B |= (1 << CS11) | (1 << CS10);
        break;
    case 256:
        TCCR1B &= ~(1 << CS11) & ~(1 << CS10);
        TCCR1B |= (1 << CS12);
        break;
    case 1024:
        TCCR1B |= (1 << CS12) | (1 << CS12);
        TCCR1B &= ~(1 << CS11);
        break;
    default:
        break;
    }
}

void Timer1::setTimerValue(uint16_t value)
{
    TCNT1 = value;
}
void Timer1::setCompareValue1(uint16_t A, uint16_t B)
{
    OCR1A = A;
    OCR1B = B;
}
void Timer1::setCompareValue(uint8_t A, uint8_t B)
{
    OCR1A = A;
    OCR1B = B;
}

void Timer1::setTimerStartValue(uint8_t percent)
{
    uint16_t hundred = 100;
    uint16_t bits = 65534;
    uint16_t speed = percent * (bits / hundred);

    setTimerValue(speed);
}
// void Timer1::setCompareValuePercent(uint8_t percentA, uint8_t percentB)
// {
//     uint16_t hundred = 100;
//     uint16_t bits = 65534;
//     uint16_t valueA = percentA * (bits / hundred);

//     uint16_t valueB = percentB * (bits / hundred);

//     setCompareValue(200, 200);
// };

void Timer1::setInterupts(bool compareA, bool compareB, bool compareOF)
{
    //cli();
    if (compareA)
    {
        TIMSK1 |= (1 << OCIE1A);
    }
    else
    {
        TIMSK1 &= ~(1 << OCIE1A);
    }

    if (compareB)
    {
        TIMSK1 |= (1 << OCIE1B);
    }
    else
    {
        TIMSK1 &= ~(1 << OCIE1B);
    }

    if (compareOF)
    {
        TIMSK1 |= (1 << TOIE1);
    }
    else
    {
        TIMSK1 &= ~(1 << TOIE1);
    }
    //sei();
}

//----------------------------------------------
//Timer2

Timer2::Timer2(/* args */)
{
    setInterupts(false, false, false);
}

Timer2::~Timer2()
{
}

void Timer2::setNormal()
{
    TCCR2A &= ~(1 << WGM21) & ~(1 << WGM20);
    TCCR2B &= ~(1 << WGM22);
}
void Timer2::setPWMPhaseCorrect()
{
    TCCR2A &= ~(1 << WGM21);
    TCCR2A |= (1 << WGM20);
    TCCR2B &= ~(1 << WGM22);
}
void Timer2::setCTC()
{
    TCCR2A |= (1 << WGM21);
    TCCR2A &= ~(1 << WGM20);
    TCCR2B &= ~(1 << WGM22);
}
void Timer2::setFastPWM()
{
    TCCR2A |= (1 << WGM21) | (1 << WGM20);
    TCCR2B &= ~(1 << WGM22);
}
void Timer2::setCompareNormal()
{
    TCCR2A &= ~(1 << COM2A1) & ~(1 << COM2A0);

    TCCR2A &= ~(1 << COM2B1) & ~(1 << COM2B0);
}
void Timer2::setCompareToggle()
{
    TCCR2A &= ~(1 << COM2A1);
    TCCR2A |= (1 << COM2A0);

    TCCR2A &= ~(1 << COM2B1);
    TCCR2A |= (1 << COM2B0);
}
void Timer2::setCompareClear()
{
    TCCR2A |= (1 << COM2A1);
    TCCR2A &= ~(1 << COM2A0);

    TCCR2A &= ~(1 << COM2B1);
    TCCR2A |= (1 << COM2B0);
}
void Timer2::setCompareSet()
{
    TCCR2A |= (1 << COM2A1) | (1 << COM2A0);
    TCCR2A |= (1 << COM2B1) | (1 << COM2B0);
}
void Timer2::setPrescaler(uint16_t value)
{
    switch (value)
    {
    case 0:
        TCCR2B &= ~(1 << CS22) & ~(1 << CS21) & ~(1 << CS20);
        break;
    case 1:
        TCCR2B &= ~(1 << CS22) & ~(1 << CS21);
        TCCR2B |= (1 << CS20);
        break;
    case 8:
        TCCR2B &= ~(1 << CS22) & ~(1 << CS20);
        TCCR2B |= (1 << CS21);
        break;
    case 64:
        TCCR2B &= ~(1 << CS22);
        TCCR2B |= (1 << CS21) | (1 << CS20);
        break;
    case 256:
        TCCR2B &= ~(1 << CS21) & ~(1 << CS20);
        TCCR2B |= (1 << CS22);
        break;
    case 1024:
        TCCR2B |= (1 << CS22) | (1 << CS22);
        TCCR2B &= ~(1 << CS21);
        break;
    default:
        break;
    }
}

void Timer2::setTimerValue(uint8_t value)
{
    TCNT2 = value;
}
void Timer2::setCompareValue(uint8_t A, uint8_t B)
{
    OCR2A = A;
    OCR2B = B;
}

void Timer2::setTimerStartValue(uint8_t percent)
{
    uint8_t hundred = 100;
    uint8_t bits = 255;
    int value = (percent * bits) / hundred;
    percent = value;
    setTimerValue(percent);
}
// void Timer2::setCompareValuePercent(uint8_t percentA, uint8_t percentB)
// {
//     uint8_t hundred = 100;
//     uint8_t bits = 255;
//     int valueA = (percentA * bits) / hundred;
//     percentA = valueA;
//     int valueB = (percentB * bits) / hundred;
//     percentB = valueB;
//     setCompareValue(percentA, percentB);
// };

void Timer2::setInterupts(bool compareA, bool compareB, bool compareOF)
{
    //cli();
    if (compareA)
    {
        TIMSK2 |= (1 << OCIE2A);
    }
    else
    {
        TIMSK2 &= ~(1 << OCIE2A);
    }

    if (compareB)
    {
        TIMSK2 |= (1 << OCIE2B);
    }
    else
    {
        TIMSK2 &= ~(1 << OCIE2B);
    }

    if (compareOF)
    {
        TIMSK2 |= (1 << TOIE2);
    }
    else
    {
        TIMSK2 &= ~(1 << TOIE2);
    }
    //sei();
}