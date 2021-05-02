/*
Nom: 
Maxime Laroche
Marie-Claire Taché
Eduardo Falluh
Ahmed Gafsi
Nemro Yapmi Nji Monluh

Date de remise: 21 avril 2021

Nom du fichier: Time.h

Description: Ce fichier contient la déclaration de la classe time. Cette classe gère les méthodes le comportement du timer0 pour bien compter le temps depuis le début de l'exécution du programme. Ce fichier contient aussi la déclaration de l'ISR nécessaire au bon fonctionnement de la minuterie.
*/


#ifndef TIME_H
#define TIME_H
#include "Timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class Time
{
private:
    /* data */
    static Timer0 timer;
    static bool initialised;
    volatile static uint8_t hundred;
    volatile static uint8_t second;
    volatile static uint8_t minute;

    static uint8_t previous_hundred;
    static uint8_t previous_second;
    static uint8_t previous_minute;

    static const uint8_t FACTOR = 2; //Mis par observation: le compteur allait 2 fois trop vite que ce qui est prévu par nos calculs
    volatile static uint8_t count;  //Nombre de fois qu'on aura une interruption avant d'aumenter le tmeps de 0.01 sec

    void initialise();

public:
    Time();
    ~Time();

    //returns the two decimal points after seconds
    uint8_t getHundred();
    // returns the current second
    uint8_t getSecond();

    //Update the current time. Called by ISR
    void updateTime();

    /*Generates a string to print the current time*/
    char *toString();
    //String containing the current time
    char timeString[10];

    //Waits until the next timestep
    void waitTimeStep(uint8_t frequency);
};

ISR(TIMER0_COMPA_vect);

#endif
