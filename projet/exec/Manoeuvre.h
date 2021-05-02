#pragma once
#ifndef _Manoeuvre_H
#define _Manoeuvre_H

#include "Hbridge.h"
#include "UART.h"
#include "Detection.h"

uint8_t convertirNNen0xNN(uint8_t num);
void afficherVitesse(uint8_t vitesseRoueGauche, uint8_t vitesseRoueDroite);
void afficheurDynamique(uint8_t vitesseRoueGauche, uint8_t vitesseRoueDroite, int nombre);
class Manoeuvre;
void desactiverAffichage(Manoeuvre &);


//cette classe permet de gérer les manoeuvres. chaque méthode manoeuvre implemente la manoeuvre concernée.
class Manoeuvre
{
private:
    Hbridge motor{PORTD, PD6, PD3};
    UART uart = UART();
    int pariteDecimale = 0;

public:
    friend void desactiverAffichage(Manoeuvre &);
    void incrementePariteDecimale()
    {
        pariteDecimale++;
    }
    void manoeuvre1();
    void manoeuvre2();
    void manoeuvre3();
    void manoeuvre4();
    void manoeuvre5();
};

#endif
