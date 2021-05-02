
/*
Nom: 
Maxime Laroche
Marie-Claire Taché
Eduardo Falluh
Ahmed Gafsi
Nemro Yapmi Nji Monluh

Date de remise: 30 mars 2021 8h30 AM

Nom du fichier: Main.cpp.cpp
Description:
Ce fichier est l'implementation de l'interpréteur du language fourni dans l'énoncé, ainsi que le lecteur pour importer le code dans le EEPROM


Composant Matériels
PD0...PD3: Afficheur 7 segments
PD4...PD7: afficheur 7 segments

PB1: Sens de rotation moteur droit
PB4: Vitesse Moteur droit

PB2: Sens de rotation Moteur gauche
PB3: Vitesse Moteur gauche

PB6-PB7: DEL bicolore

PA0...PA3: C3...C0 de la Matrice 4x4
PA4...PA7: R3...R0 de la matrice 4x4

PC2...PC4: C2...C0 de la bousole
PC5...PC7: R0...R2 de la bousole
*/

#include "IO.h"
#include "UART.h"
#include "Hbridge.h"
#include "Timer.h"
#include "can.h"
#include "Debug.h"
//#define DEBUG

#ifdef DEBUG
Debug debug = Debug();
#define PRINT(x) debug.print(x)
#define PRINT_WORD(x, y) debug.print(x, y)
#else
#define PRINT(x) \
    do           \
    {            \
    } while (0)
#define PRINT_WORD(x, y) \
    do                   \
    {                    \
    } while (0)
#endif

enum OPCode
{
    DBT = 0x01,
    ATT = 0b00000010,
    DAL = 0b01000100,
    DET = 0b01000101,
    MON = 0b00011000,
    MOF = 0b00011001,
    MAR = 0b01100000,
    MARR = 0b01100001, //Nom différent, mais c'est aussi MAR
    MAV = 0b01100010,
    MRE = 0b01100011,
    TRD = 0b01100100,
    TRG = 0b01100101,
    DBC = 0b11000000,
    FBC = 0b11000001,
    FIN = 0b11111111
};

enum Direction{
    NORD,
    EST,
    SUD,
    OUEST
};
enum Tourner{
    DROITE,
    GAUCHE
};
Direction updateDirection(Direction current, Tourner way){
    Direction nextDir=current;
    if(current==Direction::NORD){
        if(way==Tourner::DROITE){
            nextDir = Direction::EST;
        }else{
            nextDir = Direction::OUEST;
        }
    }else if (current==Direction::EST)
    {
        if(way==Tourner::DROITE){
            nextDir = Direction::SUD;
        }else{
            nextDir = Direction::NORD;
        }
    }else if(current==Direction::SUD){
        if(way==Tourner::DROITE){
            nextDir = Direction::OUEST;
        }else{
            nextDir = Direction::EST;
        }
    }else if (current==Direction::OUEST)
    {
        if(way==Tourner::DROITE){
            nextDir = Direction::NORD;
        }else{
            nextDir = Direction::SUD;
        }
    }
    return nextDir;
    
}
void updateBousole(Direction direction){
    const uint8_t FRONT = PC7;
    const uint8_t MIDDLE_FRONT_BACK = PC6;
    const uint8_t BACK = PC5;

    const uint8_t LEFT = PC4;
    const uint8_t MIDDLE_LEFT_RIGHT = PC3;
    const uint8_t RIGHT = PC2;
    PORTC=0x00;
    switch (direction)
    {
    case Direction::NORD:
        PORTC |= (1<<FRONT) | (1<<LEFT) |(1<<RIGHT);
        break;
    case Direction::SUD:
        PORTC |= (1<<BACK) | (1<<LEFT) |(1<<RIGHT);
        break;
    case Direction::EST:
        PORTC |= (1<<MIDDLE_FRONT_BACK) | (1<<MIDDLE_LEFT_RIGHT) | (1<<LEFT);
        break;
    case Direction::OUEST:
        PORTC |= (1<<MIDDLE_FRONT_BACK) | (1<<MIDDLE_LEFT_RIGHT) | (1<<RIGHT);
        break;
    default:
        break;
    }
}


int main()
{
    //LED
    DDRB = 0xFF;
    const uint8_t LED[] = {PB6, PB7};
    DDRD = 0xFF;
    DDRA=0xFF;

    //Bousole
    DDRC = 0xFF;
    Direction direction = Direction::NORD;
    updateBousole(direction);

    /*
    Ajouter la partie pour upload le fichier dans le EEPROM*/
    uint8_t opCode = 0;
    uint8_t arg = 0;
    uint8_t *address = 0x00;

    //Partie pour les moteurs
    Timer0 timer;
    Hbridge h(PORTB, PB1, PB2, timer);
    const uint16_t ANGLE_DROIT_MS = 2000;
    const uint8_t MAX_SPEED = 253;
    
    

    //Partie pour les boucles
    uint8_t nbBoucle = -1;
    uint8_t nbBoucle2 = -1;
    uint8_t *actualAddress = 0x00;
    bool alreadyInLoop = false;
    uint8_t *actualAddress2 = 0x00;

    bool recording = false;
    bool done = false;
    UARTInitialization();
    
    while (done == false)
    {
        opCode = UARTReceive();
        PRINT((opCode));
        if (opCode == OPCode::DBT)
        {
            recording = true;
        }
        if (recording == true)
        {
            eeprom_write_byte(address++, opCode);
            if (opCode == OPCode::FIN)
            {
                done = true;
            }
            arg = UARTReceive();
            eeprom_write_byte(address++, arg);
            PRINT((arg));
        }
    }

    //uint8_t startAddress = 0x00;

    done = false;
    address = 0x00;

    while (done == false)
    {

        // Lire eeprom et afficher l'opCode
        opCode = eeprom_read_byte(address++);
        arg = eeprom_read_byte(address++);
        PORTD = opCode;

        // les instructions sont aux adresses paires en mémoire alors que les opérandes (significatifs ou non) sont aux adresses impaires.

        switch (opCode)
        {
        case OPCode::DBT:
            /* code */
            break;
        case OPCode::ATT: //TEST POUR GIT
            /* code */

            for (uint8_t i = 0; i < arg; i++)
            {
                _delay_ms(25);
            }

            break;
        case OPCode::DAL:
            /* code */
            // setPin = 0x44;
            if (arg < 127)
            {
                setLED(PORTB, LED, GREEN);
            }
            else
            {

                setLED(PORTB, LED, RED);
            }
            break;
        case OPCode::DET:
            /* code */
            setLED(PORTA, LED, OFF);

            break;
        case OPCode::MON:
            /* code */
            PORTA=arg;
            break;
        case OPCode::MOF:
            PORTA=0x00;
            break;

        case OPCode::MARR:
        case OPCode::MAR: // arreter moteur : A FAIRE
            /* code */
            arg = 0;
            h.foward(arg);
            break;
        case OPCode::MAV:
            // trouver comment allumner moteur
            //arg = arg / 255;
            if(arg>MAX_SPEED){
                arg=MAX_SPEED;
            }
            h.foward(arg); // decider la vitesse qu'on veut

            break;
        case OPCode::MRE:
            /* code */
            //arg = arg / 255;
            if(arg>MAX_SPEED){
                arg=MAX_SPEED;
            }
            h.backward(arg); // decider de la vitesse
            break;
        case OPCode::TRD: // tourner droite
            
            h.move(true, MAX_SPEED, true, 0);

            _delay_ms(ANGLE_DROIT_MS);
            h.move(true,0,true,0);
            direction = updateDirection(direction, DROITE);
            updateBousole(direction);
            break;
        case OPCode::TRG: // tourner a gauche
            h.move(true, 0, true, MAX_SPEED);
            _delay_ms(ANGLE_DROIT_MS);
            h.move(true,0,true,0);
            direction = updateDirection(direction,GAUCHE);
            updateBousole(direction);
            break;

        case OPCode::DBC:

            if (alreadyInLoop == true)
            {
                actualAddress2 = address;
                nbBoucle2 = arg;
            }
            else
            {
                actualAddress = address;
                nbBoucle = arg;
            }
            alreadyInLoop = true;

            // uint8_t instrucion = DBC;
            // do
            // {
            //     if (instruction == OPCode::FBC)
            //     {
            //         --nbBoucle;
            //         instruction = DBC;
            //     }
            //     (*address) += 2;
            //     instruction = eeprom_read_byte((uint8_t *)address);
            // } while (instruction != FBC && nbBoucle != -1);
            break;

        case OPCode::FBC:
            //boucle( nbBoucle,  *position, eeproom)

            if (alreadyInLoop)
            {
                nbBoucle2--;
            }
            else
            {
                nbBoucle--;
            }
            if (nbBoucle2 < 0)
            {
                alreadyInLoop = false;
                if (nbBoucle > 0)
                {
                    address = actualAddress;
                }
            }
            else if (nbBoucle2 > 0)
            {
                address = actualAddress2;
            }

            break;
        case OPCode::FIN:
            /* code */
            done = true;
            break;
        default:
            break;
        }
    }

    return 0;
}