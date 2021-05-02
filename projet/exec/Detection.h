/*
Nom: 
Maxime Laroche
Marie-Claire Taché
Eduardo Falluh
Ahmed Gafsi
Nemro Yapmi Nji Monluh

Date de remise: 21 avril 2021

Nom du fichier: Detection.h

Description: Ce fichier contient la déclaration de la classe Detection. Cette classe gère le mode détection.
*/

#ifndef DETECTION_H
#define DETECTION_H

#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Time.h"
#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include "UART.h"
#include "Can.h"

enum PrintMode
{
    R,
    V,
    C
};

enum CanEnum
{
    INT,
    EXT
};

struct Keyboard
{
    static PrintMode print;
    static uint8_t frequency;
};

enum DangerState
{
    OK,
    ATTENTION,
    DANGER
};

enum ManoeuvreEnum
{
    MANOEUVRE1,
    MANOEUVRE2,
    MANOEUVRE3,
    MANOEUVRE4,
    MANOEUVRE5,
    INVALIDE
};

enum Sensor
{
    LEFT,
    FRONT,
    RIGHT
};

class Detection
{
private:
    /* data */

    //Distance
    static float left_cm;
    static float front_cm;
    static float right_cm;

    Can can = Can();

    /*Method to transfort the uint8_t signals from the external can and puts the
    resulting distances in left_cm, front_cm et right_cm.*/
    void convertToDistanceEXT(uint8_t left, uint16_t front, uint8_t right);

    /*Method to transfort the uint8_t signals from the internal can and puts the
    resulting distances in left_cm, front_cm et right_cm.*/
    void convertToDistanceINT(uint16_t left, uint16_t front, uint16_t right);

    Keyboard keyboard;

    //Pour imprimer un float
    void floatToString(float i, char string[]);

    /*Méthode pour imprimer si la distance d'un capteur est DANGER, OK ou ATTENTION*/
    void printStatus(float distance);

    //Fréquence and time
    static uint8_t frequency;
    Time time = Time();
    UART uart = UART();

    /*This function return the manoeuvre string to print and assigns the ManoeuvreEnum value ou the parameter (used in Manoeuvre class to determin what to execute*/
    char classifyManoeuvre(ManoeuvreEnum &manoeuvre);

    /*Determins wheter or not the distance is within a certain range*/
    bool isInRange(float distance, DangerState state);

    //Choisir la source
    void readCanInt();
    void readCanExt();
    void chooseSensor(Sensor side);

    float convertEquationEXT(float valueCAN);
    float convertEquationINT(float valueCAN);

    uint8_t detect();

    /*Méthode pour imprimer le status (temps, distance, manoeuvre à exévuter*/
    void printStatus(ManoeuvreEnum &manoeuvre);

public:
    Detection(/* args */);
    ~Detection();

    //This is where we are in detection mode
    void DetectionMode(ManoeuvreEnum &manoeuvre);
};

#endif
