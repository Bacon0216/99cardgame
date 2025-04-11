#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <iostream>
#include <vector>
#include "card.h"
#include "deck.h"

using namespace std;

class Player
{
public:
    Player();
    void reset();
    int order;
    Card odcard;
    int hand;
    int tier;

    // Get Function
    int GetScore();
    Card GetCard(int);
    int GetCardRank(int);
    string GetCardSuit(int);
    int GetID();
    int GetRanking();

    // Set Function
    void SetScore(int);
    void SetID(int);
    void SetCard(int, Card);
    void SetRanking(int);

    void PrintHandCard(int);
    void PrintACard(Card);
    void DrawCard(Deck*, int, int);
    bool IsSpCard(Card, vector<int>);
    void Discard(int);
    bool IsPlayable(int, vector<int>);
    bool IsPlayableCard(int sum, int, vector<int>);

private:
    vector<Card> card;
    int score;
    int id;
    int ranking;
};

#endif