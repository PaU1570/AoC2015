//
//  main.cpp
//  Day 21
//
//  Created by Paul Uriarte Vicandi on 10/06/2020.
//  Copyright © 2020 Paul Uriarte Vicandi. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const int bossHP = 104;
const int bossDmg = 8;
const int bossArm = 1;

int turnsToKill(int damageAttacker, int armorDefender, int hpDefender)
{
    int dmg = damageAttacker - armorDefender;
    if (dmg < 1)
        dmg = 1;
    
    double turns = ceil(double(hpDefender) / dmg);
    return turns;
}

int main()
{
    int weapons[5][2] = {{8,4},{10,5},{25,6},{40,7},{74,8}}; // {cost, damage}
    int armor[6][2] = {{0,0},{13,1},{31,2},{53,3},{75,4},{102,5}}; // {cost, armor}
    int rings[8][3] = {{0,0,0},{0,0,0},{25,1,0},{50,2,0},{100,3,0},{20,0,1},{40,0,2},{80,0,3}}; // {cost, damage, armor}
    
    int plyHP = 100;
    vector<int> winningCosts;
    vector<int> losingCosts;
    // for each weapon, choose an armor. for each armor, choose a ring. for each ring, choose another ring
    for (int w = 0; w < 5; w++)
    {
        for (int a = 0; a < 6; a++)
        {
            for (int r1 = 0; r1 < 8; r1++)
            {
                for (int r2 = r1; r2 < 8; r2++)
                {
                    if (r2 != r1)
                    {
                        int cost = weapons[w][0] + armor[a][0] + rings[r1][0] + rings[r2][0];
                        
                        int plyDmg = weapons[w][1] + rings[r1][1] + rings[r2][1];
                        int plyArm = armor[a][1] + rings[r1][2] + rings[r2][2];
                        int plyTurns = turnsToKill(plyDmg, bossArm, bossHP);
                        int bossTurns = turnsToKill(bossDmg, plyArm, plyHP);
                        
                        if (plyTurns <= bossTurns)
                            winningCosts.push_back(cost);
                        else
                            losingCosts.push_back(cost);
                    }
                }
            }
        }
    }
    
    int min = winningCosts[0];
    for (int i = 1; i < winningCosts.size(); i++)
    {
        if (winningCosts[i] < min)
            min = winningCosts[i];
    }
    
    int max = losingCosts[0];
    for (int i = 1; i < losingCosts.size(); i++)
    {
        if (losingCosts[i] > max)
            max = losingCosts[i];
    }
    
    cout << "Part 1: " << min << endl;
    cout << "Part 2: " << max << endl;
    
    
    return 0;
}
