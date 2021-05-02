#include "Debug.h"

bool Debug::initialised=false;

Debug::Debug()
{
    initialise();
    
}


Debug::~Debug()
{

}

void Debug::print(const uint8_t data){
    UARTTransmission(data);
}
void Debug::print(const char message[],uint8_t size){
    for(uint8_t i=0; i<size; i++){
        UARTTransmission(message[i]);
    }
}

void Debug::initialise(){
    if(!Debug::initialised){
        Debug::initialised=true;
        UARTInitialization();
    }
}