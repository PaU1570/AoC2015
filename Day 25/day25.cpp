//
//  main.cpp
//  Day 25
//
//  Created by Paul Uriarte Vicandi on 11/06/2020.
//  Copyright © 2020 Paul Uriarte Vicandi. All rights reserved.
//

#include <iostream>
using namespace std;

const int inputRow = 3010;
const int inputColumn = 3019;

int sum(int n)
{
    if (n < 1)
        return 0;
    return (n*(n+1))/2;
}

// adds the first n numbers starting from m
int sum(int m, int n)
{
    return sum(m+n-1) - sum(m-1);
}

int getIndex(int row, int col)
{
    return sum(col) + sum(col, row - 1);
}

unsigned long int getCode(unsigned long int prevCode)
{
    return (prevCode*252533U) % 33554393U;
}

int main()
{
    int endIndex = getIndex(inputRow, inputColumn);
    
    unsigned long int currentCode = 20151125U;
    int i;
    for (i = 1; i < endIndex; i++)
    {
        currentCode = getCode(currentCode);
    }
    cout << "Code " << i << ": " << currentCode << endl;
    
    
    return 0;
}
