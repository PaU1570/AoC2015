//
//  main.cpp
//  Day 20
//
//  Created by Paul Uriarte Vicandi on 09/06/2020.
//  Copyright © 2020 Paul Uriarte Vicandi. All rights reserved.
//

#include "utilities.hpp"
#include <iostream>
#include <vector>

using namespace std;

unsigned int input = 34000000;

unsigned int howManyPresents(int houseNum)
{
    unsigned int count = 0;
    for (int i = 1; i*i <= houseNum; i++)
    {
        if (houseNum % i == 0)
        {
            count += i;
            count += houseNum/i;
        }
    }
    return count * 10;
}

unsigned int howManyPresents2(int houseNum)
{
    unsigned int count = 0;
    for (int i = 1; i*i <= houseNum; i++)
    {
        if (houseNum % i == 0)
        {
            if (50*i >= houseNum)
                count += i;
            if (50 >= i)
                count += houseNum/i;
        }
    }
    return count * 11;
}

int main ()
{
    int houseNum = 1;
    int presents;
    
    while (true)
    {
        presents = howManyPresents(houseNum);
        //cout << "House " << houseNum << " got " << presents << " presents (" << (int(input) - presents) << " fewer than puzzle input)." << endl;
        if (presents >= input)
            break;
        houseNum++;
    }
    cout << "Part 1: " << houseNum << endl;
    
    houseNum = 1;
    while (true)
    {
        presents = howManyPresents2(houseNum);
        //cout << "House " << houseNum << " got " << presents << " presents (" << (int(input) - presents) << " fewer than puzzle input)." << endl;
        if (presents >= input)
            break;
        houseNum++;
    }
    cout << "Part 2: " << houseNum << endl;
    
    return 0;
}
