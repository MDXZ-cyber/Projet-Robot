/*
Nom: 
Maxime Laroche
Marie-Claire Taché
Eduardo Falluh
Ahmed Gafsi
Nemro Yapmi Nji Monluh

Date de remise: 21 avril 2021

Nom du fichier: Time.cpp

Description: Ce fichier contient l'implementation de la classe time. Cette classe gère les méthodes le comportement du timer0 pour bien compter le temps depuis le début de l'exécution du programme. Ce fichier contient aussi l'implementation de l'ISR nécessaire au bon fonctionnement de la minuterie.
*/

#include "Time.h"

volatile uint8_t Time::hundred = 0;
volatile uint8_t Time::second = 0;
volatile uint8_t Time::minute = 0;

uint8_t Time::previous_hundred = 0;
uint8_t Time::previous_second = 0;
uint8_t Time::previous_minute = 0;
volatile uint8_t Time::count = 0;
Timer0 Time::timer = Timer0();
bool Time::initialised = false;

Time::Time(/* args */)
{
    if (!Time::initialised)
    {
        initialise();
        Time::initialised = true;
    }
}

Time::~Time()
{
}

Time time = Time();
ISR(TIMER0_COMPA_vect)
{
    time.updateTime();
}

void Time::updateTime()
{
    Time::count = (Time::count + 1) % Time::FACTOR;
    if (Time::count == 0)
    {
        Time::hundred = (Time::hundred + 1) % 100;
        if (Time::hundred == 0)
        {
            Time::second = (Time::second + 1) % 60;
            if (Time::second == 0)
            {
                Time::minute++;
            }
        }
    }
}

void Time::initialise()
{
    const uint16_t PRESCALER = 1024;
    const uint8_t COMPARE_A_VALUE = 77 * 2; //(F_CPU/PRESCALER)/ INTERUPT_FREQUENCY;

    timer.setInterupts(true, false, false);

    timer.setCompareValue(COMPARE_A_VALUE, COMPARE_A_VALUE);
    timer.setWaveform(Waveform::CTC);
    timer.setPrescaler(PRESCALER);
}

char *Time::toString()
{
    /*returns a pointer to an array of chars containing the  current time in format MM:SS.CC */
    sprintf(timeString, "%2d:%2d.%2d ", Time::minute, Time::second, Time::hundred);

    return timeString;
}

uint8_t Time::getHundred()
{
    return Time::hundred;
}

uint8_t Time::getSecond()
{
    return Time::second;
}

void Time::waitTimeStep(uint8_t frequency)
{

    //Pour quand on entre dans le mode detection:
    bool passed = false;
    while (!passed)
    {
        //_delay_us(5);
        if (Time::second > Time::previous_second + 2)
        {
            Time::previous_hundred = Time::hundred;
            Time::previous_second = Time::second;
            Time::previous_minute = Time::minute;
            passed = true;
            break;
        }

        switch (frequency)
        {
        case 1:
            if (Time::second > Time::previous_second &&
                Time::hundred >= Time::previous_hundred)
            {
                Time::previous_hundred = Time::hundred;
                Time::previous_second = Time::second;
                passed = true;
                break;
            }
            else if (Time::minute > Time::previous_minute &&
                     Time::hundred >= Time::previous_hundred)
            {
                Time::previous_hundred = Time::hundred;
                Time::previous_second = Time::second;
                Time::previous_minute = Time::minute;
                passed = true;
                break;
            }
            break;
        case 2:
            if (Time::hundred > Time::previous_hundred + 50)
            { //Même seconde
                Time::previous_hundred = Time::hundred;
                passed = true;
                break;
            }
            else if (Time::second > Time::previous_second && //Même minute mais seconde diff
                     Time::hundred + 50 >= Time::previous_hundred)
            {
                Time::previous_hundred = Time::hundred;
                Time::previous_second = Time::second;
                passed = true;
                break;
            }
            else if (Time::minute > Time::previous_minute &&
                     Time::hundred + 50 >= Time::previous_hundred)
            {
                Time::previous_hundred = Time::hundred;
                Time::previous_second = Time::second;
                Time::previous_minute = Time::minute;
                passed = true;
                break;
            }
            break;
        case 4:
            if (Time::hundred >= Time::previous_hundred + 25)
            { //Même seconde
                Time::previous_hundred = Time::hundred;
                passed = true;
                break;
            }
            else if (Time::second > Time::previous_second && //Même minute mais seconde diff
                     Time::hundred + 75 >= Time::previous_hundred)
            {
                Time::previous_hundred = Time::hundred;
                Time::previous_second = Time::second;
                passed = true;
                break;
            }
            else if (Time::minute > Time::previous_minute &&
                     Time::hundred + 75 >= Time::previous_hundred)
            {
                Time::previous_hundred = Time::hundred;
                Time::previous_second = Time::second;
                Time::previous_minute = Time::minute;
                passed = true;
                break;
            }
            break;
        default:
            break;
        }
    }
}