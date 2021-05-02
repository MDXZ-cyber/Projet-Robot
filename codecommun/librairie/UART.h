/*
Nom: 
Maxime Laroche
Marie-Claire Taché
Eduardo Falluh
Ahmed Gafsi
Nemro Yapmi Nji Monluh

Date de remise: 17 mars 2021

Description:
Ces fonctions permettent d'implémenter les registres nécessaires pour permettre l’initialisation et la transmission pour le UART.
*/
#ifndef UART_H
#define UART_H
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/eeprom.h>

void UARTInitialization();
void UARTTransmission(uint8_t data);
void readUntil(uint8_t *startAddress, uint8_t endValue);
void UARTTranmitWord(char message[],uint8_t size);
uint8_t UARTReceive();

#endif