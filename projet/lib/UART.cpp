#include "UART.h"

bool UART::initialised=false;

UART::UART()
{
    initialise();
}


UART::~UART()
{

}

void UART::byte(const uint8_t data){
    UARTTransmission(data);
}
void UART::word(const char message[]){
    /*Prints the bytes in message[] untill a '\0' caracter is found*/
    uint8_t i=0;
    while(message[i]!='\0'){
        UARTTransmission(message[i++]);
    }
}

void UART::word(const char message[],uint8_t size){
    /*prints the array message[] for size bytes. No null character needed at end of string to stop*/
    for(uint8_t i=0; i<size; i++){
        UARTTransmission(message[i]);
    }
}

void UART::initialise(){
    if(!UART::initialised){
        UART::initialised=true;
        UARTInitialization();
    }
}

void UART::UARTInitialization(){
 
    UBRR0H = 0;
    UBRR0L = 52;
    // permettre la réception et la transmission par le UART0
    UCSR0A = 0x00 ;
   // UCSR0B = (1 << TXCIE0 /*tx complete interrupt*/) | (1 << TXEN0 /*Transmitter enable*/) | (1 << RXEN0 /*Receiver enable*/); 
     UCSR0B = (1 << TXEN0 /*Transmitter enable*/) | (1 << RXEN0 );
    // Format des trames: 8 bits, 1 stop bits, none parity
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void UART::UARTTransmission(const uint8_t data){
    
    while(!(UCSR0A & (1<<UDRE0))){
    }
   UDR0 = data;
}

void UART::readUntil(uint8_t *startAddress, uint8_t endValue){
    char temp = eeprom_read_byte(startAddress);
    uint8_t *address = startAddress;
    while(temp != endValue){
        UARTTransmission(temp);
        address++;
        temp = eeprom_read_byte(address);
    }
}

uint8_t UART::UARTReceive(){
    /* Wait for data to be received */
    while ( !(UCSR0A & (1<<RXC0))){}
    /* Get and return received data from buffer */
    return UDR0;
}