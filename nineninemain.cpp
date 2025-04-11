#include <iostream>
#include "ninenine.h"
#include "player.h"

using namespace std;

int main()
{
    int people, rounds, sum = 0, left = 52;
    cout << "Welcome to 99 card game!" << endl;
    Player reference;
    Player*player = &reference;
    CPU cpu[4];
    for (int i = 0; i < 4; i++)
    {
        cpu[i].SetID(i + 1);
    }
    
    cout << endl << "How many people do you want in the game (please input between 3 ~ 5 people) :";
    cin >> people;

    while (people > 5 || people < 3)
    {
        cout << "please input between 3 ~ 5 people : ";
        cin >> people;
    }

    cout << endl << "How many rounds do you want :";
    cin >> rounds;
    int now = 1 ;
    string pause;
    while (rounds != 0)
    {
        Deck deck;
        cout << endl << "----------Round" << now++ << "----------" <<  endl;
        Order(player, cpu, people, deck);                  //排出牌順序
        Initial(player, cpu, people, &deck, &left, &sum);  //初始化玩家並建立初始手牌及可出的牌
        PrintHandCard(*player, people);                    //印出玩家初始手牌
        PlayCard(player, cpu, people, &sum, &deck, &left); //電腦和玩家出牌 排排名
        Score(player, cpu, people);                        //計算並輸出分數
        cout << "Enter anything to continue~";
        cin >> pause;                                      //讓玩家確認
        
        rounds--;
    }
    Scoresettlement(player, cpu, people);                  //結算畫面
}
