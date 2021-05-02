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

#ifndef HBRIDGE_H
#define HBRIDGE_H
#include "Timer.h"
#include "IO.h"

class Hbridge
{
private:
    uint8_t left_direction_pin;
    uint8_t right_direction_pin;
    volatile uint8_t *port;
    Timer1 *timer;

public:
    /*Makes both motors move foward at the specified speed*/
    void foward(uint16_t speed);
    /*Makes both motors move backward at the specified speed*/
    void backward(uint16_t speed);

    /*Make both motors move the way you want
    @param leftFoward: bool: whether or not to make the left moter move foward or backward
    @param left speed: uint16_t: the speed at witch the left motor will move. 0 to make it stop  (0%) and 65534 is 100%*/
    void move(bool leftFoward, uint16_t leftSpeed,
              bool rightFoward, uint16_t rightSpeed);

    /*Constructor of the Hbridge object. Uses the timer1 by default for PWM.
    @param port: address of the port where the directions are plugged to
    @param right_direction_pin: the pin that controls the direction of the right motor
    @param left_direction_pin: the pin that controls the direction of the left motor*/
    Hbridge(volatile uint8_t &port,
            const uint8_t right_direction_pin,
            const uint8_t left_direction_pin);

    ~Hbridge() = default;
};

#endif