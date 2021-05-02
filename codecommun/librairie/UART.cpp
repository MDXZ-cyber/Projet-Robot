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

#include "UART.h"


void UARTInitialization(){
 
    UBRR0H = 0;
    UBRR0L = 0xCF;
    // permettre la réception et la transmission par le UART0
    UCSR0A = 0x00 ;
   // UCSR0B = (1 << TXCIE0 /*tx complete interrupt*/) | (1 << TXEN0 /*Transmitter enable*/) | (1 << RXEN0 /*Receiver enable*/); 
     UCSR0B = (1 << TXEN0 /*Transmitter enable*/) | (1 << RXEN0 );
    // Format des trames: 8 bits, 1 stop bits, none parity
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void UARTTransmission(const uint8_t data){
    
    while(!(UCSR0A & (1<<UDRE0))){
    }
   UDR0 = data;
}

void UARTTranmitWord(const char message[],uint8_t size){
    for(uint8_t i=0; i<size; i++){
        UARTTransmission(message[i]);
    }
}

void readUntil(uint8_t *startAddress, uint8_t endValue){
    char temp = eeprom_read_byte(startAddress);
    uint8_t *address = startAddress;
    while(temp != endValue){
        UARTTransmission(temp);
        address++;
        temp = eeprom_read_byte(address);
    }
}

uint8_t UARTReceive(){
    /* Wait for data to be received */
    while ( !(UCSR0A & (1<<RXC0))){}
    /* Get and return received data from buffer */
    return UDR0;
}
