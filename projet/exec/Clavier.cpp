/*
Nom: 
Maxime Laroche
Marie-Claire Taché
Eduardo Falluh
Ahmed Gafsi
Nemro Yapmi Nji Monluh

Date de remise: 21 avril 2021

Nom du fichier: Clavier.cpp

Description: Ce fichier contient les fonctions definies dans clavier.h necessaire pour que notre clavier fonctionne en implementant la fonction ISR.
*/
#include "Clavier.h"

Manoeuvre manoeuvre{};
UART print = UART();
Keyboard state{};

Manoeuvre &refererManoeuvre()
{
    return manoeuvre;
};

ISR(PCINT2_vect)
{

    manageButton();
}

void manageButton()
{

    PCMSK2 = 0;
    uint8_t colonne = 3;

    colonne = colonneDuClavier();

    if (colonne != 3)
    {
        inverserClavier();

        uint8_t ligne = 3;

        ligne = ligneDuClavier();
        if (colonne != 3)
        {
            char charactere = toucheEnfonce('z', ligne * 3 + colonne, manoeuvre); //permet de controller la boucle a l`infini que le code executait

            char message[30]; // = "Le bouton ", charactere, " a ete appuye.\n";
            sprintf(message, "Le bouton %c a ete appuye.\n", charactere);
            print.word(message);
        }
    }
    inverserClavier();

    PCMSK2 |= (1 << PCINT20) | (1 << PCINT19) | (1 << PCINT18);
}

void initialisationClavier(void)
{
    cli();
    PCMSK2 = 0;
    DDRC = 0xE0;
    PORTC = 0xE0;

    PCICR |= (1 << PCIE2);
    PCMSK2 |= (1 << PCINT20) | (1 << PCINT19) | (1 << PCINT18);
    sei();
}

void inverserClavier()
{

    DDRC ^= 0b11111100;
    PORTC ^= 0b11111100;
}

char toucheEnfonce(char charactere, uint8_t pos, Manoeuvre &obj)
{
    switch (pos)
    {
    case 0:
        charactere = '1';

        state.frequency = 1;
        break;
    case 1:
        charactere = '2';
        state.frequency = 2;
        break;
    case 2:
        charactere = '4';
        state.frequency = 4;
        break;
    case 3:
        charactere = 'R';
        state.print = PrintMode::R;
        break;
    case 4:
        charactere = 'V';
        state.print = PrintMode::V;
        break;
    case 5:
        charactere = 'C';
        state.print = PrintMode::C;
        break;
    case 6:
        charactere = 'I';
        // PORTA = 0x00;
        //state.canEnum = CanEnum::INT;
        // state.isINT = true;
        DDRA |= (1 << PA0);
        PORTA &= ~(1 << PA0);
        break;
    case 7:
        charactere = 'E';
        //PORTA = 0x01;
        //state.canEnum = CanEnum::EXT;
        //state.isINT = false;
        DDRA |= (1 << PA0);
        PORTA |= (1 << PA0);
        break;
    case 8:
        charactere = '#';
        obj.incrementePariteDecimale();
        break;
    }
    return charactere;
}

// Ces deux derniere boucle if permettent d eviter la boucle a linfini qui se produit lorsqu on appuie sur une touche
uint8_t ligneDuClavier()
{
    if (PINC & 0x20) //C5
    {
        return 0;
    }
    else if (PINC & 0x40) //C6
    {
        return 1;
    }
    else if (PINC & 0x80) //C7
    {
        return 2;
    }
    return 3;
}

uint8_t colonneDuClavier()
{
    if (PINC & 0x10)
    {
        return 0;
    }
    else if (PINC & 0x08)
    {
        return 1;
    }
    else if (PINC & 0x04)
    {
        return 2;
    }
    return 3;
}
