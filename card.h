#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED
#include <iostream>
#include <vector>
#include "suit.h"

using namespace std;

class Card
{
public:
    Card();
    void PrintCard(Card, int);

    Suits suit;
    int rank;
    string rankp;
};

#endif