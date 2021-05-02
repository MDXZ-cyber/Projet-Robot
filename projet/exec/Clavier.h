/*
Nom: 
Maxime Laroche
Marie-Claire Taché
Eduardo Falluh
Ahmed Gafsi
Nemro Yapmi Nji Monluh

Date de remise: 21 avril 2021

Nom du fichier: Clavier.h

Description: Ce fichier contient initialise les fonction presentes dans le fichier clavier.h pour faire en sorte que celui-ci soit moins lourd/long. 
            Il permet le fonctionnement de clavier.cpp.
*/
#pragma once
#ifndef CLAVIER_H
#define CLAVIER_H

#include "UART.h"
#include "Detection.h"
#include <stdio.h>
#include <string.h>
#include "Manoeuvre.h"

#include <stdint.h>
#include <avr/io.h>

#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Time.h"
#include <avr/io.h>

ISR(PCINT2_vect);

//Pour imprimer

Manoeuvre &refererManoeuvre();
void manageButton();
void initialisationClavier(void);
void inverserClavier();
char toucheEnfonce(char charactere, uint8_t pos, Manoeuvre &obj);
uint8_t ligneDuClavier();
uint8_t colonneDuClavier();

#endif
