/*
Nom: 
Maxime Laroche
Marie-Claire Taché
Eduardo Falluh
Ahmed Gafsi
Nemro Yapmi Nji Monluh

Date de remise: 21 avril 2021

Nom du fichier: main.cpp

Description: Ce fichier est celui qui contient la fonction main du programme exécutant le livrable du projet final d'INF1900
             Robot qui détecte des obstacles et qui effectue des manœuvres d’évitement
             
PIND2 = ENTREE Bouton
PINB0 = SORTIE On/Off du démultiplexeur du Can Externe
PINB1 = ENTREE du démultiplexeur du CAN externe
PINB2 PINB3 PINB4 = SORTIE contrôlant le demultiplexeur
PIND3 PIND4 PIND5 PIND6 = SORTIE contrôllant les moteurs
PIND7 = SORTIE controllant (OE), sois maintenir l'état present de la LatchD ou la sortie recopie l'état
PINC0 PINC1 = SORTIE de l'unite de controle de la latchD 
PINC2 PINC3 PINC4 PINC5 PIND6 = Alterne entre ENTREE et SORTIE dépendament si on veut trouvé la ligne ou la colone de la touche appuyée sur le clavier
PINA0 = SORTIE controllant quel CAN recoit le signal des capteurs
PINA1 = ENTREE du CAN interne
PINA2 PINA3 =Sortie controllant le signal de quel capteur est acheminé au CAN
PINA4 PINA5 PINA6 PINA7 = SORTIE du décodeur BCD afin de commander le 7 Segment
PINB5 PINB6 = SORTIE de l'unite de controle de la latchD 
PINB7 = SORTIE controllant output de la Latch, sois maintenir l'état present de la bascule D ou la sortie recopie l'état


Can  interne PA1
CAN externe: PB0 PB2 PB3 PB4
gestion can: PA0
gestion sensor: PA2 PA3
Clavier: PC2 PC3 PC4 PC5 PC6 PC7
Bouton interruption declenche manoeuvre : PD2
7 SEGMENT : PA4 PA5 PA6 PA7 PB5 PB6 PB7  + PD7 pour enable
PONT EN H: PD3 PD4 PD5 PD6
*/

#include "Detection.h"
#include "Clavier.h"
#include "StartMode.h"
#include "Manoeuvre.h"

enum Mode
{
    DEMARRAGE,
    DETECTION,
    MANOEUVRE
} mode = Mode::DEMARRAGE;

// //Ne pas supprimer le prototype suivant. il est utilisé dans le code.
void exercuterManoeuvre(Manoeuvre &, ManoeuvreEnum);

StartMode startMode;
UART uart = UART();
const uint8_t FIRST_SEGMENT = 208;
const uint8_t SECOND_SEGMENT = 192;
const uint8_t THIRD_SEGMENT = 176;
const uint8_t FORTH_SEGMENT = 160;

// volatile Mode mode = Mode::DEMARRAGE;

ISR(INT0_vect)
{
    mode = Mode::MANOEUVRE;
    EIFR |= (1 << INTF0);
}

void initialisation(void)
{
    cli();
    DDRD &= ~(1 << PD2);
    EIMSK |= (1 << INT0);
    EICRA |= (0 << ISC01) | (1 << ISC00);
    sei();
}

int main()
{
    // cli();
    initialisation();

    // initialisation();
    initialisationClavier();
    Detection detection = Detection();
    // sei();

    Manoeuvre &manoeuvre = refererManoeuvre();
    ManoeuvreEnum manoeuvreEnum = ManoeuvreEnum::MANOEUVRE1;
    // Mode mode = DEMARRAGE;

    while (true)
    {
        initialisationClavier();
        switch (mode)
        {
        case Mode::DEMARRAGE:
            startMode.displayTerminal();
            startMode.display7segement(FIRST_SEGMENT, SECOND_SEGMENT, THIRD_SEGMENT, FORTH_SEGMENT);
            startMode.forward_backward();
            mode = Mode::DETECTION;
            break;

        case Mode::DETECTION:
            detection.DetectionMode(manoeuvreEnum);
            break;
        case Mode::MANOEUVRE:
            exercuterManoeuvre(manoeuvre, manoeuvreEnum);
            desactiverAffichage(manoeuvre);
            mode = Mode::DETECTION;
            break;
        default:
            break;
        }
    }
    return 0;
}

void exercuterManoeuvre(Manoeuvre &manoeuvre, ManoeuvreEnum manoeuvreEnum)
{
    DDRD &= ~(1 << PD2);
    if (manoeuvreEnum == ManoeuvreEnum::MANOEUVRE1)
        manoeuvre.manoeuvre1();
    else if (manoeuvreEnum == ManoeuvreEnum::MANOEUVRE2)
        manoeuvre.manoeuvre2();
    else if (manoeuvreEnum == ManoeuvreEnum::MANOEUVRE3)
        manoeuvre.manoeuvre3();
    else if (manoeuvreEnum == ManoeuvreEnum::MANOEUVRE4)
        manoeuvre.manoeuvre4();
    else if (manoeuvreEnum == ManoeuvreEnum::MANOEUVRE5)
        manoeuvre.manoeuvre5();
    else
        uart.word("Combinaison non evaluee\n");
}
