/*
Nom: 
Maxime Laroche
Marie-Claire Taché
Eduardo Falluh
Ahmed Gafsi
Nemro Yapmi Nji Monluh

Date de remise: 17 mars 2021
Nom du fichier: Hbridge.h
Description:
Ce fichier est la déclaration de la classe Hbridge. Cette classe permet la manipulation de pont en H.
*/

#include "Timer.h"
#include "IO.h"
#ifndef HBRIDGE_H
#define HBRIDGE_H



class Hbridge
{
private:
    uint8_t left_direction_pin;
    uint8_t right_direction_pin;
    volatile uint8_t *port;
    Timer *timer;

public:
    void foward(uint8_t speed);
    void backward(uint8_t speed);
    void move(bool leftFoward, uint8_t leftSpeed,
              bool rightFoward, uint8_t rightSpeed);

    Hbridge(volatile uint8_t& port,
            const uint8_t right_direction_pin,
            const uint8_t left_direction_pin, 
            Timer &timer);

    ~Hbridge()=default;
    
};

#endif