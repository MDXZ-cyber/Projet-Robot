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
#include "UART.h"

void Hbridge::foward(uint8_t speed)
{
    setPin(*port, left_direction_pin, HIGH);
    setPin(*port, right_direction_pin, HIGH);

    timer->setCompareValue(speed,speed);
}
void Hbridge::backward(uint8_t speed)
{
    setPin(*port, left_direction_pin, LOW);
    setPin(*port, right_direction_pin, LOW);

    timer->setCompareValue(speed, speed);
}

Hbridge::Hbridge(volatile uint8_t &port,
                 const uint8_t right_direction_pin,
                 const uint8_t left_direction_pin,
                 Timer &timer)
{
    this->port = &port;
    this->right_direction_pin = right_direction_pin;
    this->left_direction_pin = left_direction_pin;
    this->timer = &timer;
    this->timer->setPrescaler(256);
    this->timer->setWaveform(PWM_FAST_PWM);
    this->timer->setCompareOutput(CLEAR);
}

void Hbridge::move(bool leftFoward, uint8_t leftSpeed,
                   bool rightFoward, uint8_t rightSpeed)
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
    timer->setCompareValue(leftSpeed, rightSpeed);
}
