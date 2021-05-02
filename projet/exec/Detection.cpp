/*
Nom: 
Maxime Laroche
Marie-Claire Taché
Eduardo Falluh
Ahmed Gafsi
Nemro Yapmi Nji Monluh

Date de remise: 21 avril 2021

Nom du fichier: Detection.cpp

Description: Ce fichier contient l'implementation de la classe Detection. Cette classe gère le mode détection.
*/

#include "Detection.h"

//État du clavier
uint8_t Detection::frequency = 1;
PrintMode Keyboard::print = PrintMode::R;
uint8_t Keyboard::frequency = 1;

//Distance percu par les capteur
float Detection::left_cm = 0.0;
float Detection::front_cm = 0.0;
float Detection::right_cm = 0.0;

Detection::Detection(/* args */)
{
    //Can  interne et gestioon sensor
    DDRA |= (1 << PA0) | (1 << PA3) | (1 << PA4);
    DDRA &= ~(1 << PA1);

    //CAN externe
    DDRB |= (1 << PB0) | (1 << PB2) | (1 << PB3) | (1 << PB4);
    DDRB &= ~(1 << PB1);
}
Detection::~Detection()
{
}

uint8_t Detection::detect()
{
    if ((PORTA & (1 << PA0)))
    {
        readCanExt();
    }
    else
    {
        readCanInt();
    }

    return 0;
}

void Detection::printStatus(ManoeuvreEnum &manoeuvre)
{

    char buffer[15];
    char tempString[10];

    //Time
    time.toString(); //builds the string in time.timeString
    uart.word(time.timeString);


    //------Distance --left
    floatToString(left_cm, tempString);
    sprintf(buffer, " -G:%s", tempString);
    uart.word(buffer);

    //Front
    floatToString(front_cm, tempString);
    sprintf(buffer, " -C:%s", tempString);
    uart.word(buffer);

    //right
    floatToString(right_cm, tempString);
    sprintf(buffer, " -D:%s", tempString);
    uart.word(buffer);


    //-------Status
    uart.word(" - ");
    printStatus(left_cm);
    uart.word(" | ");
    printStatus(front_cm);
    uart.word(" | ");
    printStatus(right_cm);
    sprintf(buffer, "(%c)\n", classifyManoeuvre(manoeuvre));
    uart.word(buffer);
}

/*Puts a string equivalent to a float in string[]*/
void Detection::floatToString(float i, char string[])
{
    uint8_t integer = i;
    uint16_t decimalTemp = (i * 10.0);
    uint8_t decimal = decimalTemp % 10;

    sprintf(string, "%2d.%1d", integer, decimal);
}

void Detection::printStatus(float distance)
{
    char statusString[10];
    const float DANGER = 20;
    const float ATTENTION = 50;

    if (distance < DANGER)
    {
        sprintf(statusString, "%s", "DANGER");
    }
    else if (distance < ATTENTION)
    {
        sprintf(statusString, "%s", "ATTENTION");
    }
    else
    {
        sprintf(statusString, "%s", "OK");
    }
    uart.word(statusString);
}

void Detection::DetectionMode(ManoeuvreEnum &manoeuvre)
{

    ManoeuvreEnum previousManoeuvre = manoeuvre;
    float previousLeft = Detection::left_cm;
    float previousFront = Detection::front_cm;
    float previousRight = Detection::right_cm;
    time.waitTimeStep(keyboard.frequency);
    detect();
    classifyManoeuvre(manoeuvre);

    switch (keyboard.print)
    {
    case PrintMode::R:
        printStatus(manoeuvre);
        break;
    case PrintMode::V:
        if (previousLeft != Detection::left_cm ||
            previousFront != Detection::front_cm ||
            previousRight != Detection::right_cm)
        {
            printStatus(manoeuvre);
            previousLeft = Detection::left_cm;
            previousFront = Detection::front_cm;
            previousRight = Detection::right_cm;
        }
    case PrintMode::C:
        if (previousManoeuvre != manoeuvre)
        {
            printStatus(manoeuvre);
            previousManoeuvre = manoeuvre;
        }
        break;
    default:
        break;
    }
}

char Detection::classifyManoeuvre(ManoeuvreEnum &manoeuvre)
{
    const char MANOEUVRE1 = '1';
    const char MANOEUVRE2 = '2';
    const char MANOEUVRE3 = '3';
    const char MANOEUVRE4 = '4';
    const char MANOEUVRE5 = '5';
    const char INVALIDE = '-';

    if (isInRange(Detection::left_cm, DangerState::OK) &&
        isInRange(Detection::front_cm, DangerState::ATTENTION) &&
        isInRange(Detection::right_cm, DangerState::ATTENTION))
    {
        manoeuvre = ManoeuvreEnum::MANOEUVRE1;
        return MANOEUVRE1;
    }
    else if (isInRange(Detection::left_cm, DangerState::ATTENTION) &&
             isInRange(Detection::front_cm, DangerState::ATTENTION) &&
             isInRange(Detection::right_cm, DangerState::OK))
    {
        manoeuvre = ManoeuvreEnum::MANOEUVRE2;
        return MANOEUVRE2;
    }
    else if (isInRange(Detection::left_cm, DangerState::DANGER) &&
             isInRange(Detection::front_cm, DangerState::DANGER) &&
             isInRange(Detection::right_cm, DangerState::DANGER))
    {
        manoeuvre = ManoeuvreEnum::MANOEUVRE3;
        return MANOEUVRE3;
    }
    else if (isInRange(Detection::left_cm, DangerState::OK) &&
             isInRange(Detection::front_cm, DangerState::OK) &&
             isInRange(Detection::right_cm, DangerState::DANGER))
    {
        manoeuvre = ManoeuvreEnum::MANOEUVRE4;
        return MANOEUVRE4;
    }
    else if (isInRange(Detection::left_cm, DangerState::DANGER) &&
             isInRange(Detection::front_cm, DangerState::OK) &&
             isInRange(Detection::right_cm, DangerState::OK))
    {
        manoeuvre = ManoeuvreEnum::MANOEUVRE5;
        return MANOEUVRE5;
    }

    manoeuvre = ManoeuvreEnum::INVALIDE;
    return INVALIDE;
}

bool Detection::isInRange(float distance, DangerState state)
{
    const float OK = 50.0;        //50cm
    const float ATTENTION = 20.0; //20cm
    const float DANGER = 10.0;

    switch (state)
    {
    case DangerState::OK:
        if (distance >= OK)
        {
            return true;
        }
        break;
    case DangerState::ATTENTION:
        if (distance < OK && distance > ATTENTION)
        {
            return true;
        }
        break;
    case DangerState::DANGER:
        if (distance < ATTENTION && distance > DANGER)
        {
            return true;
        }
        break;
    default:
        break;
    }
    return false;
}

void Detection::chooseSensor(Sensor side)
{
    switch (side)
    {
    case Sensor::LEFT:
        PORTA &= ~(1 << PA2) & ~(1 << PA3);
        break;
    case Sensor::FRONT:
        PORTA |= 1 << PA2;
        PORTA &= ~(1 << PA3);
        break;
    case Sensor::RIGHT:
        PORTA |= 1 << PA3;
        PORTA &= ~(1 << PA2);
        break;
    default:
        break;
    }
}

void Detection::readCanExt()
{
    //Enable MUX
    PORTB &= ~(1 << PB0);

    uint8_t result[3];

    uint8_t bit;
    for (uint8_t i = 0; i < sizeof(result); i++)
    {
        uint8_t position = 0;
        result[i] = 0;
        switch (i)
        {
        case 0:
            chooseSensor(Sensor::LEFT);
            break;
        case 1:
            chooseSensor(Sensor::FRONT);
            break;
        case 2:
            chooseSensor(Sensor::RIGHT);
            break;

        default:
            break;
        }

        const uint8_t BITS_IN_BYTE = 8;
        while (position < BITS_IN_BYTE)
        {
            bit = PINB;
            bit &= (1 << PB1);

            PORTB &= ~(1 << PB2) & ~(1 << PB3) & ~(1 << PB4);
            PORTB |= position << 2;
            
            result[i] += (bit << (BITS_IN_BYTE - 1 - position));
            position++;
        }
    }

    convertToDistanceEXT(result[0], result[1], result[2]);
}
void Detection::readCanInt()
{
    uint16_t left;
    uint16_t front;
    uint16_t right;

    chooseSensor(Sensor::LEFT);
    left = can.lecture(PA1);
    _delay_us(2000);
    chooseSensor(Sensor::RIGHT);
    right = can.lecture(PA1);
    _delay_us(2000);
    chooseSensor(Sensor::FRONT);
    front = can.lecture(PA1);

    convertToDistanceINT(left, front, right);
}

void Detection::convertToDistanceEXT(uint8_t left, uint16_t front, uint8_t right)
{
    float leftFloat = left;
    //capteur left
    Detection::left_cm = Detection::convertEquationEXT(leftFloat);

    //capteur droite
    float rightFloat = right;
    Detection::right_cm = Detection::convertEquationEXT(rightFloat);

    //capteur front
    float frontFloat = front;
    Detection::front_cm = Detection::convertEquationEXT(frontFloat);
}

void Detection::convertToDistanceINT(uint16_t left, uint16_t front, uint16_t right)
{
    //capteur left
    float leftFloat = left;
    Detection::left_cm = convertEquationINT(leftFloat);

    //capteur droite
    float rightFloat = right;
    Detection::right_cm = convertEquationINT(rightFloat);

    //capteur front
    float frontFloat = front;
    Detection::front_cm = convertEquationINT(frontFloat);
}
float Detection::convertEquationEXT(float valueCAN)
{
    const float RESOLUTION_CAN_EXT = 256;
    const float AREF_EXT = 2.48F;
    float distance = ((26.0F * RESOLUTION_CAN_EXT) / ((AREF_EXT * valueCAN) - (0.1F * RESOLUTION_CAN_EXT)))- 0.42F;
    return distance;
}

float Detection::convertEquationINT(float valueCAN)
{
    const float RESOLUTION_CAN_INT = 1024;
    const float AREF_INT = 5;
    float distance = ((26.0F * RESOLUTION_CAN_INT) / ((AREF_INT * valueCAN) - (0.1F * RESOLUTION_CAN_INT))) - 0.42F;
    return distance;
}
