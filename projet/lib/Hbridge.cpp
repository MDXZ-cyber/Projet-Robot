/*
Nom: 
Maxime Laroche
Marie-Claire Taché
Eduardo Falluh
Ahmed Gafsi
Nemro Yapmi Nji Monluh

Date de remise: 17 mars 2021

Nom du fichier: Hbridge.cpp
Description:
Ce fichier est l'implémentation de la classe Hbridge. Cette classe permet la manipulation de pont en H.
*/
#include "Hbridge.h"

void Hbridge::foward(uint16_t speed)
{
    setPin(*port, left_direction_pin, HIGH);
    setPin(*port, right_direction_pin, HIGH);

    OCR1A = speed;
    OCR1B = speed;
}
void Hbridge::backward(uint16_t speed)
{
    setPin(*port, left_direction_pin, LOW);
    setPin(*port, right_direction_pin, LOW);

    OCR1A = speed;
    OCR1B = speed;
}

Hbridge::Hbridge(volatile uint8_t &port,
                 const uint8_t right_direction_pin,
                 const uint8_t left_direction_pin)
{
    //Set pin as outputs
    port |= (1 << left_direction_pin) | (1 << right_direction_pin);
    //Set PWM pins as output
    port |= (1 << PD4) | (1 << PD5);

    this->port = &port;
    this->right_direction_pin = right_direction_pin;
    this->left_direction_pin = left_direction_pin;
    Timer1 t;
    this->timer = &t;
    this->timer->setPrescaler(1);
    this->timer->setWaveform(PWM_PHASE_CORRECT);
    this->timer->setCompareOutput(CLEAR);
}

void Hbridge::move(bool leftFoward, uint16_t leftSpeed,
                   bool rightFoward, uint16_t rightSpeed)
{
    if (leftFoward)
    {
        setPin(*port, left_direction_pin, HIGH);
    }
    else
    {
        setPin(*port, left_direction_pin, LOW);
    }

    if (rightFoward)
    {
        setPin(*port, right_direction_pin, HIGH);
    }
    else
    {
        setPin(*port, right_direction_pin, LOW);
    }
    OCR1A = rightSpeed;
    OCR1B = leftSpeed;
}