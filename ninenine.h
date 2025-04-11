#ifndef NINENINE_H_INCLUDED
#define NINENINE_H_INCLUDED
#include <iostream>
#include <vector>
#include "player.h"
#include "cpu.h"

using namespace std;


void Order(Player* , CPU*, int, Deck);
void Initial(Player* , CPU* , int , Deck* , int*, int* );
void PrintHandCard(Player, int);
void SpCalculate(Player*, CPU*, int*, Card, int, int*, char);
void PlayCard(Player*, CPU*, int, int*, Deck*, int*);
void Score(Player* , CPU*, int);
void Scoresettlement(Player*, CPU *, int);
#endif
