//
//  main.cpp
//  Day 22
//
//  Created by Paul Uriarte Vicandi on 10/06/2020.
//  Copyright © 2020 Paul Uriarte Vicandi. All rights reserved.
//

#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

int initialBossHP = 55;
int initialBossDmg = 8;

class turn
{
public:
    turn() : playerHP(50), bossHP(initialBossHP), mana(500), manaSpent(0), armor(0), shieldTimer(0), poisonTimer(0), rechargeTimer(0) {}
    int playerHP;
    int bossHP;
    int mana;
    int manaSpent;
    int armor;
    
    // return true if spell was successful
    bool missile();
    bool drain();
    bool shield();
    bool poison();
    bool recharge();
    
    void bossTurn();
    void applyEffects();
    
    int shieldTimer;
    int poisonTimer;
    int rechargeTimer;
    
    vector<string> moves;
    
};

// 1. check if we have enough mana
// 2. apply effects of existing spells
// 3. cast spell

bool turn::missile()
{
    if (mana < 53)
        return false;
    mana -= 53;
    manaSpent += 53;
    applyEffects();
    bossHP -= 4;
    moves.push_back("missile");
    return true;
}

bool turn::drain()
{
    if (mana < 73)
        return false;
    mana -= 73;
    manaSpent += 73;
    applyEffects();
    bossHP -= 2;
    playerHP += 2;
    moves.push_back("drain");
    return true;
}

bool turn::shield()
{
    if (mana < 113)
        return false;
    if (shieldTimer > 1) // if timer is 1 we are allowed to start a new one
        return false;
    mana -= 113;
    manaSpent += 113;
    applyEffects();
    shieldTimer = 6;
    armor = 7;
    moves.push_back("shield");
    return true;
}

bool turn::poison()
{
    if (mana < 173)
        return false;
    if (poisonTimer > 1)
        return false;
    mana -= 173;
    manaSpent += 173;
    applyEffects();
    poisonTimer = 6;
    moves.push_back("poison");
    return true;
}

bool turn::recharge()
{
    if (mana < 229)
        return false;
    if (rechargeTimer > 1)
        return false;
    mana -= 229;
    manaSpent += 229;
    applyEffects();
    rechargeTimer = 5;
    moves.push_back("recharge");
    return true;
}

void turn::applyEffects()
{
    if (shieldTimer > 0)
    {
        shieldTimer--;
        if (shieldTimer == 0)
            armor = 0;
    }
    if (poisonTimer > 0)
    {
        poisonTimer--;
        bossHP -= 3;
    }
    if (rechargeTimer > 0)
    {
        rechargeTimer--;
        mana += 101;
    }
}

void turn::bossTurn()
{
    if (playerHP < 1)
        return;
    applyEffects();
    if (bossHP < 1)
        return;
    int dmg = initialBossDmg - armor;
    if (dmg < 1)
        dmg = 1;
    playerHP -= dmg;
}

// compare should return true if lhs is smaller than rhs
// priority queue will sort things such that the 'biggest' element goes on the front
// so we want the turn with lowest mana spent to be the 'biggest', so that we explore it first
class compareTurns
{
public:
    bool operator() (const turn &lhs, const turn &rhs) const
    {
        return lhs.manaSpent > rhs.manaSpent;
    }
};

int main()
{
    for (int i = 0; i < 2; i++)
    {
        priority_queue<turn, vector<turn>, compareTurns> q;
        
        // add initial turns
        turn t1; t1.playerHP -= i; t1.missile();
        q.push(t1);
        
        turn t2; t2.playerHP -= i; t2.drain();
        q.push(t2);
        
        turn t3; t3.playerHP -= i; t3.shield();
        q.push(t3);
        
        turn t4; t4.playerHP -= i; t4.poison();
        q.push(t4);
        
        turn t5; t5.playerHP -= i; t5.recharge();
        q.push(t5);
        
        int minMana = -1;
        int count = 0;
        while (!q.empty())
        {
            count++;
            turn current = q.top();
            q.pop();
            
            if (count == 72383)
            {
                
            }
            
            current.bossTurn();
            if (current.bossHP < 1)
            {
                count = count;
                minMana = current.manaSpent;
                // print moves
                cout << "Moves for Part " << i+1 << ": " << endl;
                for (int j = 0; j < current.moves.size(); j++)
                    cout << current.moves[j] << endl;
                break;
            }
            
            current.playerHP -= i;
            if (current.playerHP > 0)
            {
                // try all the possible moves and add them to queue
                turn copy = current;
                if (copy.missile())
                {
                    //copy.bossTurn();
                    q.push(copy);
                }
                copy = current;
                if (copy.drain())
                {
                    //copy.bossTurn();
                    q.push(copy);
                }
                copy = current;
                if (copy.shield())
                {
                    //copy.bossTurn();
                    q.push(copy);
                }
                copy = current;
                if (copy.poison())
                {
                    //copy.bossTurn();
                    q.push(copy);
                }
                copy = current;
                if (copy.recharge())
                {
                    //copy.bossTurn();
                    q.push(copy);
                }
            }
        }
        cout << "Part " << i+1 << ": " << minMana << endl << endl;
    }
    
    return 0;
}
