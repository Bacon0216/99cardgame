#ifndef DECK_H_INCLUDED
#define DECK_H_INCLUDED
#include <iostream>
#include <vector>
#include "card.h"

using namespace std;

class Deck
{
public:
    Deck();
    Card GetDeck(int);
    int GetDeckRank(int);
    void SetDeckRank(int);
    void Erase(int);
private:
    vector<Card> deck2;
};

#endif