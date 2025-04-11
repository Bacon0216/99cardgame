#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include "ninenine.h"

void Order(Player* player , CPU* cpu, int people, Deck deck)
{
    int x = time(0);
    srand(x);
    int PlayerR, CPUR[4] , k = 0;
    int PlayerID = 1, CPUID[4] = {1, 1, 1, 1};
    
    PlayerR = 1 + rand() % 52;
    player -> odcard = deck.GetDeck(PlayerR);                   //玩家抽取順序卡
    deck.Erase(PlayerR);

    for (int i = 0; i < people -1; i++)
    {
        CPUR[k] = 1 + rand() % 52;
        cpu[i].odcard = deck.GetDeck(CPUR[k]);                  //電腦抽取順序卡
        deck.Erase(CPUR[k++]);
    }
    
    for (int i = 0; i < people - 1; i++)                        //決定先後順序
    {   
        if (player ->odcard.rank < cpu[i].odcard.rank)
        {
            PlayerID++;
        }
        else if (player ->odcard.rank > cpu[i].odcard.rank)
        {
            CPUID[i]++;
        }
        else if (player ->odcard.rank == cpu[i].odcard.rank)
        {
            if (PlayerR/13 > CPUR[i]/13)
            {
                PlayerID++;
            }
            else
            {
                CPUID[i]++;
            }
        }

        for (int j = 0; j < people - 1; j++)
        {
            if (cpu[i].odcard.rank < cpu[j].odcard.rank && i != j)
            {
                CPUID[i]++;
            }
            else if (cpu[i].odcard.rank == cpu[j].odcard.rank && i != j)
            {
                if (CPUR[i]/13 > CPUR[j]/13)
                {
                    CPUID[i]++;
                }
            }
        }
    }
    player->order = PlayerID;
    cout << "Player ID : " << player->order << endl;             //印出先後順序
    for (int i = 0; i < people-1; i++)
    {
        cpu[i].order = CPUID[i];
        cout << "CPU " << i + 1 << " ID : " << cpu[i].order << " ";
        cout << endl;
    }
    
}

void Initial(Player* player, CPU* cpu, int people, Deck* deck, int* left, int* sum)
{
    *sum = 0;
    *left = 52;
    player ->reset();
    int k = time(0);
    srand(k);
    int RandCardID;
    for (int i = 0; i < 5; i++)
    {
        RandCardID = rand() % *left;
        player ->SetCard(i, deck -> GetDeck(RandCardID));           //建立玩家手牌
        deck ->Erase(RandCardID);
        *left -= 1;
    }

    for (int i = 0; i < people - 1; i++)
    {
        cpu[i].reset();
        for (int j = 0; j < 5; j++)
        {
            RandCardID = rand() % *left;

            cpu[i].SetCard(j, deck -> GetDeck(RandCardID));         //建立電腦手牌
            deck ->Erase(RandCardID);
            *left -= 1;
        }
    }
}

void PrintHandCard(Player player, int people)
{
    cout << "Player card : " << endl;
    player.PrintHandCard(player.hand);      //印出玩家手牌
}

void SpCalculate(Player* player, CPU* cpu, int* sum, Card card, int people, int* k, char identity)
{
    int x = time(0);
    srand(x);
    if (card.rank == 1 && card.suit.suit == "Spade")
    {
        *sum = 0;
    }
    else if (card.rank == 4)
    {
        *k = people + 1 - *k;
        player->order = people + 1 - player->order;

        for (int i = 0; i < people - 1; i++)
        {
            cpu[i].order = people + 1 - cpu[i].order;
        }
    }
    else if (card.rank == 5)
    {
        if (identity == 'p')
        {
            cout << "The order now is : \n";
            for (int j = 1; j < people + 1; j++)
            {
                if (player->order == j)
                {
                    cout << "Player ID " << player->order;
                }
                else
                {
                    for (int n = 0; n < people - 1; n++)
                    {
                        if (cpu[n].order == j)
                        {
                            cout << "CPU" << n + 1 << " ID " << cpu[n].order;
                        }
                    }
                }
                cout << " ---> ";
            }
            cout << endl << "Chose next player (Enter the id) : ";
            int id ;
            cin >> id;
            if (id == player ->order)
            {
                cout << "Next is change to player " << endl;
                *k = player->order - 1;
            }
            else
            {
                for (int j = 0; j < people - 1; j++)
                {
                    if (id == cpu[j].order)
                    {
                        cout << "Next is change to ID " << cpu[j].order << endl;
                        *k = cpu[j].order - 1;
                    }
                }
            }
        }
        else if (identity == 'c')
        {
            int cp = rand() % people;
            if (cp == player ->GetID())
            {
                cout << "Next is change to player " << endl;
                *k = player->order - 1;
            }
            else
            {
                for (int j = 0; j < people - 1; j++)
                {
                    if (cp == cpu[j].GetID())
                    {
                        cout << "Next is change to ID " << cpu[j].GetID() << endl;
                        *k = cpu[j].order - 1;
                    }
                }
            }
        }
    }
    else if (card.rank == 10)
    {
        if (identity == 'p')
        {
            if (*sum + 10 > 99)
            {
                cout << "You can't +10\n";
                *sum -= 10;
            }
            else
            {
                cout << "+10 or -10 ? (enter '+' or '-'): ";
                char c;
                cin >> c;
                
                while(true)
                {
                    if ( c != '+' && c != '-')
                    {
                        cout << "Wrong input!" << endl << "Please enter again : ";
                        cin >> c;
                    }
                    else
                    {
                        break;
                    }
                }

                if (c == '+')
                {
                    *sum += 10;
                }
                else if (c == '-')
                {
                    *sum -= 10;
                    if (*sum < 0)
                    {
                        *sum = 0;
                    }
                }
            }
        }
        else if (identity == 'c')
        {
            int cp = 1 + rand() % 2;
            if (*sum + 10 > 99)
            {
                *sum -= 10;
            }
            else if (cp == 1)
            {
                *sum += 10;
            }
            else if (cp == 2)
            {
                *sum -= 10;
                if (*sum < 0)
                {
                    *sum = 0;
                }
            }
        }
    }
    else if (card.rank == 11)
    {
        cout << "Pass\n";
    }
    else if (card.rank == 12)
    {
        if (identity == 'p')
        {
            if (*sum + 20 > 99)
            {
                cout << "You can't +20\n";
                *sum -= 20;
            }
            else 
            {
                cout << "+20 or -20 ? (enter '+' or '-'): ";
                char c;
                cin >> c;
                
                while(true)
                {
                    if ( c != '+' && c != '-')
                    {
                        cout << "Wrong input!" << endl << "Please enter again : ";
                        cin >> c;
                    }
                    else
                    {
                        break;
                    }
                }

                if (c == '+')
                {
                    *sum += 20;
                }
                else if (c == '-')
                {
                    *sum -= 20;
                }
            }
        }
        else if (identity == 'c')
        {
            int cp = 1 + rand() % 2;
            if (*sum + 20 > 99)
            {
                *sum -= 20;
            }
            else if (cp == 1)
            {
                *sum += 20;
            }
            else if (cp == 2)
            {
                *sum -= 20;
                if (*sum < 0)
                {
                    *sum = 0;
                }
            }
        }
    }
    else if (card.rank == 13)
    {
        *sum = 99;
    }
}

void PlayCard(Player* player, CPU* cpu, int people, int* sum, Deck* deck, int* left)
{
    int number = 0, leftpeople = people, origine;
    string pause;
    vector<int> special = {1, 4 ,5, 10, 11, 12, 13};
    vector<int> W_ranking, L_ranking;

    if (people < 4)
    {
        special.erase(special.begin() + 1);
    }
    
    for (int i = 1; i < people + 1; i++)
    {         
        bool end = false;    
        origine = *sum;
        if (i == player -> order)
        {
            if (player -> hand == 0)
            {
                if (i == people)
                {
                    i = 0;
                }
                continue; //跳過此玩家的回合
            }            
            else if (leftpeople == 1)
            {
                W_ranking.push_back(player ->GetID());
                break;
            }
            else if (!player->IsPlayable(*sum, special) == true)
            {
                PrintHandCard(*player, people);
                cout << "You are'able to play any card!" << endl;
                player -> hand = 0;
                L_ranking.insert(L_ranking.begin(),player ->GetID());
                leftpeople--;
                if (i == people)
                {
                    i = 0;
                }
                continue; //跳過此玩家的回合
            }
            cout << "\nEnter anything to continue : ";
            cin >> pause;           //讓玩家確認

            cout << "Deck has " << *left << " left" << endl;    //顯示牌組剩餘卡牌數量
            PrintHandCard(*player, people);                     //印出玩家手牌
            cout << "         01         " << "         02         "
                 << "         03         " << "         04         " 
                 << "         05         " << endl;

            cout << "Enter the card number of the card you want : ";
            
            cin >>  number;
            number -= 1;
            
            while (true)
            {   
                if (number > player -> hand - 1 || number  < 0)
                {
                    cout << "You can't play this card" << endl << "Enter another card number of the card you want : ";
                    cin >> number;
                    number -= 1;
                } 
                else if (player->IsSpCard(player->GetCard(number),special) == true)
                {
                    SpCalculate(player, cpu, sum, player->GetCard(number), people, &i, 'p');
                    break;
                }
                else if (*sum + player->GetCardRank(number) > 99 || number + 1 > player -> hand)
                {
                    cout << "You can't play this card" << endl << "Enter another card number of the card you want : ";
                    cin >> number;
                    number -= 1;
                }
                
                else 
                {
                    *sum += player->GetCardRank(number);
                    break;
                }
            }
            player ->PrintACard(player -> GetCard(number));
            cout << "Current point : " << origine << " -> " << *sum << endl;
            if (*left == 0)
            {
                player->hand--;
                player->Discard(number); //出牌
            }
            else
            {
                player ->DrawCard(deck, number, *left); //出並且抽牌
                *left -= 1;
            }

            if (player->hand == 0)
            {
                W_ranking.push_back(player ->GetID());
                cout << "Player win!" << endl;
                leftpeople--;
            }
        }
        else
        {
            for (int j = 0; j < people - 1; j++)
            {
                if (i == cpu[j].order)
                {                
                    if (cpu[j].hand == 0)
                    {
                        if (i == people)
                        {
                            i = 0;
                        }
                        break;         //跳過此玩家的回合
                    }                    
                    else if (leftpeople == 1)
                    {
                        W_ranking.push_back(cpu[j].GetID());
                        end = true;
                        break;
                    }
                    else if (!cpu[j].IsPlayable(*sum, special) == true)
                    {
                        leftpeople--;
                        cout << "CPU" << cpu[j].GetID() << " is out!" << endl;
                        cpu[j].hand = 0;
                        L_ranking.insert(L_ranking.begin(),cpu[j].GetID());
                        if (i == people)
                        {
                            i = 0;
                        }
                        break; //跳過此玩家的回合
                    }

                    cout << "\nEnter anything to continue : ";
                    cin >> pause;       //讓玩家確認

                    cout << "Deck has " << *left << " left" << endl;
                    cout << "CPU " << cpu[j].GetID() << " turn!\n\n";
                    
                    int x = time(0);
                    srand(x);
                    int num = rand();
                    while(true)
                    {
                        num %= cpu[j].hand;
                        if (cpu[j].IsPlayableCard(*sum ,num , special))
                        {
                            break;
                        }
                        else
                        {
                            num++;
                        }
                    }

                    //cpu[j].PrintHandCard(cpu[j].hand);     可/不可看到電腦手牌

                    cout << "CPU " << cpu[j].GetID() << " play the card :" << endl;
                    cpu[j].PrintACard(cpu[j].GetCard(num));

                    if (cpu[j].IsSpCard(cpu[j].GetCard(num), special))
                    {
                        SpCalculate(player, cpu, sum, cpu[j].GetCard(num), people, &i, 'c');
                    }
                    else
                    {
                        *sum += cpu[j].GetCardRank(num);
                    }
                    cout << "Current point : " << origine << " -> " << *sum << endl;
                    if (*left == 0)
                    {
                        cpu[j].hand--;
                        cpu[j].Discard(num);    //出牌
                    }
                    else
                    {
                        cpu[j].DrawCard(deck, num, *left);  //出並且抽牌
                        *left -= 1;
                    }
                    if (cpu[j].hand == 0)
                    {
                        W_ranking.push_back(cpu[j].GetID());
                        leftpeople--;
                        cout << "CPU" << cpu[j].GetID() << " Win!" << endl;
                    }
                    break;
                }
            }
        }
        if (end == true)
        {
            break;
        }
        if (i == people)
        {
            i = 0;
        }
    }

    W_ranking.reserve(W_ranking.size() + L_ranking.size());
    W_ranking.insert(W_ranking.end(), L_ranking.begin(), L_ranking.end());  //排名順序

    for (int i = 0; i < people; i++)
    {
        if (W_ranking[i] == player ->GetID())
        {
            player ->SetRanking(i + 1);
        }
        else
        {
            for (int j = 0; j < people - 1; j++)
            {
                if (W_ranking[i] == cpu[j].GetID())
                {
                    cpu[j].SetRanking(i + 1);
                }
            }
        }
    }
    cout << "Game Over!" << endl;
}

void Score(Player* player, CPU* cpu, int people)
{
    player -> SetScore(people + 1 - player -> GetRanking());
    cout << "player's scroe : " << player -> GetScore() << endl;                        //顯示玩家前分數

    for (int i = 0; i < people - 1; i++)
    {
        cpu[i].SetScore(people + 1 - cpu[i].GetRanking());
        cout << "CPU" << cpu[i].GetID() << " score : " << cpu[i].GetScore() << endl;    //顯示電腦當前分數
    }
}

void Scoresettlement(Player* player, CPU *cpu, int people)
{
    player -> tier = people;
    for (int j = 0; j < people - 1; j++)
    {
        cpu[j].tier = people;
    }

    for (int i = 0; i < people - 1; i++)
    {
        if (player->GetScore() > cpu[i].GetScore())
        {
            player ->tier--;
        }
        else if (player->GetScore() < cpu[i].GetScore())
        {
            cpu[i].tier--;
        }
        else if (player->GetScore() == cpu[i].GetScore())
        {
            cpu[i].tier--;
            player ->tier--;
        }
        for (int j = i + 1; j < people - 1; j++)
        {
            if (cpu[i].GetScore() > cpu[j].GetScore())
            {
                cpu[i].tier--;
            }
            else if (cpu[i].GetScore() < cpu[j].GetScore() )
            {
                cpu[j].tier--;
            }
            else if (cpu[j].GetScore() == cpu[i].GetScore())
            {
                cpu[i].tier--;
                cpu[j].tier--;
            }
        }
    }

    for (int i = 1; i < people + 1; i++)        //印出排行榜
    {
        if (i == 2)
        {
            cout << "                   Second Place : ";   
        }
        else if (i == 3)
        {
            cout << "                    Third Place : ";
        }
        else if (i == 4)
        {
            cout << "                    Forth Place : ";
        }
        else if (i == 5)
        {
            cout << "                    Fifth Place : ";
        }

        if (i == player->tier)
        {
            if (i == 1)
            {
                cout << endl << "               !!!   The Winer is Player !!!                  " << endl << endl;
                cout << "--------------------------------------------------------------" << endl;
            }
            else
            {
                cout << "Player "; 
            }
        }
        for (int j = 0; j < people - 1; j++)
        {
            if (i == cpu[j].tier)
            {
                if (i == 1)
                {
                    cout << endl << "               !!!   The Winer is CPU "<<  cpu[j].GetID() << "   !!!                  " << endl << endl;
                    cout << "--------------------------------------------------------------" << endl;
                }
                else 
                {
                    cout << "CPU" << cpu[j].GetID() << " ";
                }
            }
        }
        cout << endl;
    }
    cout << endl << "--------------------------------------------------------------";
}


Card::Card(){}
// << Player function >>

Player::Player(){score = 0; card.resize(5); hand = 5; id = 0;}

void Player::reset()
{
    card.resize(5);
    hand = 5;

}
//Getfunction
int Player::GetID()
{
    return id;
}

int Player::GetScore()
{
    return score;
}

Card Player::GetCard(int i)
{
    return card[i];
}

int Player::GetCardRank(int i)
{
    return card[i].rank;
}

string Player::GetCardSuit(int i)
{
    return card[i].suit.suit;
}

int Player::GetRanking()
{
    return ranking;
}

//Set function
void Player::SetScore(int i)
{
    score += i;
}

void Player::SetID(int i)
{
    id = i;
}

void Player::SetCard(int i , Card k)
{
    card[i] = k;
}

void Player::SetRanking(int i)
{
    ranking = i;
}


//other function
void Player::PrintHandCard(int sum)
{
    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < sum; j++)
        {
            if (card[j].suit.suit == "Spade")
            {
                if (i == 0 || i == 13)
                {
                    cout << "--------------------";
                }
                else if (i == 1)
                {
                    cout << "|                  |";
                }
                else if (i == 2)
                {
                    cout << "|        **        |";
                }
                else if (i == 3)
                {
                    cout << "|       ****       |";
                }
                else if (i == 4)
                {
                    cout << "|      ******      |";
                }
                else if (i == 5)
                {
                    cout << "|     ********     |";
                }
                else if (i == 6)
                {
                    cout << "|    **********    |";
                }
                else if (i == 7)
                {
                    cout << "|     ** ** **     |";
                }
                else if (i == 8)
                {
                    cout << "|        **        |";
                }
                else if (i == 9)
                {
                    cout << "|       ****       |";
                }
                else if (i == 10)
                {
                    cout << "|                  |";
                }
                else if (i == 11)
                {
                    cout << "|        S" << left << setw(2) << card[j].rankp << "       |";
                }
                else if (i == 12)
                {
                    cout << "|                  |";
                }
            }
            else if (card[j].suit.suit == "Heart")
            {
                if (i == 0 || i == 13)
                {
                    cout << "--------------------";
                }
                else if (i == 1)
                {
                    cout << "|                  |";
                }
                else if (i == 2)
                {
                    cout << "|    ***    ***    |";
                }
                else if (i == 3)
                {
                    cout << "|   *****  *****   |";
                }
                else if (i == 4)
                {
                    cout << "|    **********    |";
                }
                else if (i == 5)
                {
                    cout << "|     ********     |";
                }
                else if (i == 6)
                {
                    cout << "|      ******      |";
                }
                else if (i == 7)
                {
                    cout << "|       ****       |";
                }
                else if (i == 8)
                {
                    cout << "|        **        |";
                }
                else if (i == 9 || i == 10 || i == 12)
                {
                    cout << "|                  |";
                }
                else if (i == 11)
                {
                    cout << "|        H" << left << setw(2) << card[j].rankp << "       |";
                }
            }
            else if (card[j].suit.suit == "Diamond")
            {
                if (i == 0 || i == 13)
                {
                    cout << "--------------------";
                }
                else if (i == 1)
                {
                    cout << "|                  |";
                }
                else if (i == 2)
                {
                    cout << "|        **        |";
                }
                else if (i == 3)
                {
                    cout << "|       ****       |";
                }
                else if (i == 4)
                {
                    cout << "|      ******      |";
                }
                else if (i == 5)
                {
                    cout << "|     ********     |";
                }
                else if (i == 6)
                {
                    cout << "|      ******      |";
                }
                else if (i == 7)
                {
                    cout << "|       ****       |";
                }
                else if (i == 8)
                {
                    cout << "|        **        |";
                }
                else if (i == 9 || i == 10 ||i == 12)
                {
                    cout << "|                  |";
                }
                else if (i == 11)
                {
                    cout << "|        D" << left << setw(2) << card[j].rankp << "       |";
                }
            }
            else if (card[j].suit.suit == "Club")
            {
                if (i == 0 || i == 13)
                {
                    cout << "--------------------";
                }
                else if (i == 1)
                {
                    cout << "|                  |";
                }
                else if (i == 2)
                {
                    cout << "|        **        |";
                }
                else if (i == 3)
                {
                    cout << "|       ****       |";
                }
                else if (i == 4)
                {
                    cout << "|       ****       |";
                }
                else if (i == 5)
                {
                    cout << "|    **  **  **    |";
                }
                else if (i == 6)
                {
                    cout << "|   ************   |";
                }
                else if (i == 7)
                {
                    cout << "|   ************   |";
                }
                else if (i == 8)
                {
                    cout << "|    **  **  **    |";
                }
                else if (i == 9)
                {
                    cout << "|        **        |";
                }
                else if (i == 10)
                {
                    cout << "|                  |";
                }
                else if (i == 11)
                {
                    cout << "|        C" << left << setw(2) << card[j].rankp << "       |";
                }
                else if (i == 12)
                {
                    cout << "|                  |";
                }
            }
        }
        cout << endl;
    }
}

void Player::PrintACard(Card card)
{
    for (int i = 0; i < 14; i++)
    {
        if (card.suit.suit == "Spade")
        {
            if (i == 0 || i == 13)
            {
                cout << "--------------------";
            }
            else if (i == 1)
            {
                cout << "|                  |";                
            }
            else if (i == 2)
            {
                cout << "|        **        |";
            }
            else if (i == 3)
            {
                cout << "|       ****       |";
            }
            else if (i == 4)
            {
                cout << "|      ******      |";
            }
            else if (i == 5)
            {
                cout << "|     ********     |";
            }
            else if (i == 6)
            {
                cout << "|    **********    |";
            }
            else if (i == 7)
            {
                cout << "|     ** ** **     |";
            }
            else if (i == 8)
            {
                cout << "|        **        |";
            }
            else if (i == 9)
            {
                cout << "|       ****       |";
            }
            else if (i == 10)
            {
                cout << "|                  |";
            }
            else if (i == 11)
            {
                cout << "|        S" << setw(2) << card.rankp << "       |";
            }
            else if (i == 12)
            {
                cout << "|                  |";
            }
        }
        else if (card.suit.suit == "Heart")
        {
            if (i == 0 || i == 13)
            {
                cout << "--------------------";
            }
            else if (i == 1)
            {
                cout << "|                  |";
            }
            else if (i == 2)
            {
                cout << "|    ***    ***    |";
            }
            else if (i == 3)
            {
                cout << "|   *****  *****   |";
            }
            else if (i == 4)
            {
                cout << "|    **********    |";
            }
            else if (i == 5)
            {
                cout << "|     ********     |";
            }
            else if (i == 6)
            {
                cout << "|      ******      |";
            }
            else if (i == 7)
            {
                cout << "|       ****       |";
            }
            else if (i == 8)
            {
                cout << "|        **        |";
            }
            else if (i == 9 || i == 10 || i == 12)
            {
                cout << "|                  |";
            }
            else if (i == 11)
            {
                cout << "|        H" << setw(2) << card.rankp << "       |";
            }
        }
        else if (card.suit.suit == "Diamond")
        {
            if (i == 0 || i == 13)
            {
                cout << "--------------------";
            }
            else if (i == 1)
            {
                cout << "|                  |";
            }
            else if (i == 2)
            {
                cout << "|        **        |";
            }
            else if (i == 3)
            {
                cout << "|       ****       |";
            }
            else if (i == 4)
            {
                cout << "|      ******      |";
            }
            else if (i == 5)
            {
                cout << "|     ********     |";
            }
            else if (i == 6)
            {
                cout << "|      ******      |";
            }
            else if (i == 7)
            {
                cout << "|       ****       |";
            }
            else if (i == 8)
            {
                cout << "|        **        |";
            }
            else if (i == 9 || i == 10 ||i == 12)
            {
                cout << "|                  |";
            }
            else if (i == 11)
            {
                cout << "|        D" << setw(2) << card.rankp << "       |";
            }
        }
        else if (card.suit.suit == "Club")
        {
            if (i == 0 || i == 13)
            {
                cout << "--------------------";
            }
            else if (i == 1)
            {
                cout << "|                  |";
            }
            else if (i == 2)
            {
                cout << "|        **        |";
            }
            else if (i == 3)
            {
                cout << "|       ****       |";
            }
            else if (i == 4)
            {
                cout << "|       ****       |";
            }
            else if (i == 5)
            {
                cout << "|    **  **  **    |";
            }
            else if (i == 6)
            {
                cout << "|   ************   |";
            }
            else if (i == 7)
            {
                cout << "|   ************   |";
            }
            else if (i == 8)
            {
                cout << "|    **  **  **    |";
            }
            else if (i == 9)
            {
                cout << "|        **        |";
            }
            else if (i == 10)
            {
                cout << "|                  |";
            }
            else if (i == 11)
            {
                cout << "|        C" << setw(2) << card.rankp << "       |";
            }
            else if (i == 12)
            {
                cout << "|                  |";
            }
        }
        cout << endl;
    }
}

void Player::DrawCard(Deck* deck, int i, int left)
{
    int x = time(0);
    int random;
    srand(x);
    random = rand() % left;
    card[i] = deck->GetDeck(random);
    deck->Erase(random);
}

bool Player::IsSpCard(Card card, vector<int> sp)
{
    for (int i = 0; i < sp.size(); i++)
    {
        if (card.rank == sp[i])
        {
            if (card.rank == 1 && card.suit.suit == "Spade")
            {
                return true;
            }
            else if(card.rank != 1) 
            {
                return true;
            }
        }
    }

    return false;
}

void Player::Discard(int i)
{
    card.erase(card.begin() + i);
}

bool Player::IsPlayable(int sum, vector<int> sp)
{
    for (int i = 0; i < hand; i++)
    {
        if (card[i].rank + sum < 100 || IsSpCard(card[i], sp))
        {
            return true;
        }
    }
    return false;
}

bool Player::IsPlayableCard(int sum, int x, vector<int> sp )
{
    if (card[x].rank + sum > 99 && !IsSpCard(card[x], sp))
    {
        return false;
    }
    return true;
}

Suits::Suits(){}

// << Deck function >>
Deck::Deck()
{
    deck2.resize(52);
    for (int i = 0; i < 52; i++)
    {
        Card sample;
        if (i / 13 == 0)
        {
            sample.suit.suit = "Spade";
            sample.rank = i % 13 + 1;
            switch(i % 13 + 1)
            {
                case 1:
                sample.rankp = "A";
                break;
                
                case 11:
                sample.rankp = "J";
                break;
                
                case 12:
                sample.rankp = "Q";
                break;

                case 13:
                sample.rankp = "K";
                break;

                default:
                sample.rankp = to_string(i % 13 + 1);
                break;
            }
        }
        else if (i / 13 == 1)
        {
            sample.suit.suit = "Heart"; 
            sample.rank = i % 13 + 1;
            switch(i % 13 + 1)
            {
                case 1:
                sample.rankp = "A";
                break;
                
                case 11:
                sample.rankp = "J";
                break;

                case 12:
                sample.rankp = "Q";
                break;

                case 13:
                sample.rankp = "K";
                break;

                default:
                sample.rankp = to_string(i % 13 + 1);
                break;
            }
        }
        else if (i / 13 == 2)
        {
            sample.suit.suit = "Diamond";
            sample.rank = i % 13 + 1;
            switch(i % 13 + 1)
            {
                case 1:
                sample.rankp = "A";
                break;

                case 11:
                sample.rankp = "J";
                break;

                case 12:
                sample.rankp = "Q";
                break;

                case 13:
                sample.rankp = "K";
                break;
                
                default:
                sample.rankp = to_string(i % 13 + 1);
                break;
            }
        }
        else if (i / 13 == 3)
        {
            sample.suit.suit = "Club";
            sample.rank = i % 13 + 1;
            switch(i % 13 + 1)
            {
                case 1:
                sample.rankp = "A";
                break;

                case 11:
                sample.rankp = "J";
                break;

                case 12:
                sample.rankp = "Q";
                break;

                case 13:
                sample.rankp = "K";
                break;

                default:
                sample.rankp = to_string(i % 13+ 1);
                break;
            }
        }
        deck2[i] = sample;
    }
}

Card Deck::GetDeck(int i)
{
    return deck2[i];
}

int Deck::GetDeckRank(int i)
{
    return deck2[i].rank;
}

void Deck::SetDeckRank(int i)
{
    deck2[i].rank = 0;
}

void Deck::Erase(int i)
{
    deck2.erase(deck2.begin() + i);
}

