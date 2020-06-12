//
//  main.cpp
//  Day 23
//
//  Created by Paul Uriarte Vicandi on 10/06/2020.
//  Copyright © 2020 Paul Uriarte Vicandi. All rights reserved.
//

#include "utilities.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string filename = "/Users/pauluv/Documents/Code/Advent of Code 2015/Inputs/Day23.txt";

struct Pair
{
    Pair(int one, int two) : a(one), b(two) {}
    int a;
    int b;
};

struct Instruction
{
    Instruction(string n, int v, char r = '0') : name(n), value(v), reg(r) {}
    string name;
    int value;
    char reg;
    void print()
    {
        cout << name << " " << reg << " " << value << endl;
    }
};

void parseInput(string input, vector<Instruction> &instructions)
{
    size_t ipos = 0;
    size_t fpos = 0;
    while (ipos < input.size())
    {
        fpos = input.find('\n', ipos); // find position of next line end
        string token = input.substr(ipos, fpos - ipos); // get substring (line)
        ipos = fpos + 1;
        
        int i = 0;
        string tmp("");
        string tmpval("0");
        int sign = 1;
        char reg = '0';
        while (i < token.size())
        {
            // look for instruction
            if (i < 3)
            {
                tmp += token[i];
            }
            // look for register
            else if (token[i] == 'a' || token[i] == 'b')
            {
                reg = token[i];
            }
            // look for number
            else if (token[i] == '-')
            {
                sign = -1;
            }
            else if (token[i] != '+' && token[i] != ' ' && token[i] != ',')
            {
                tmpval += token[i];
            }
            i++;
        }
        int val = stoi(tmpval) * sign;
        Instruction nInst(tmp, val, reg);
        instructions.push_back(nInst);
    }
}

void runInstructions(vector<Instruction> &inst, Pair &regs, int pos = 0)
{
    if (pos > inst.size() || pos < 0)
        return;
    
    Instruction i = inst[pos];
    if (i.name == "hlf")
    {
        if (i.reg == 'a')
            regs.a *= 0.5;
        else
            regs.b *= 0.5;
        runInstructions(inst, regs, pos + 1);
    }
    else if (i.name == "tpl")
    {
        if (i.reg == 'a')
            regs.a *= 3;
        else
            regs.b *= 3;
        runInstructions(inst, regs, pos + 1);
    }
    else if (i.name == "inc")
    {
        if (i.reg == 'a')
            regs.a++;
        else
            regs.b++;
        runInstructions(inst, regs, pos + 1);
    }
    else if (i.name == "jmp")
    {
        runInstructions(inst, regs, pos + i.value);
    }
    else if (i.name == "jie")
    {
        if ((i.reg == 'a' && regs.a % 2 == 0) || (i.reg == 'b' && regs.b % 2 == 0))
            runInstructions(inst, regs, pos + i.value);
        else
            runInstructions(inst, regs, pos + 1);
    }
    else if (i.name == "jio")
    {
        if ((i.reg == 'a' && regs.a == 1) || (i.reg == 'b' && regs.b == 1))
            runInstructions(inst, regs, pos + i.value);
        else
            runInstructions(inst, regs, pos + 1);
    }
}

int main()
{
    string input;
    readFile(filename, input);
    
    vector<Instruction> inst;
    parseInput(input, inst);

    Pair regs1(0,0);
    Pair regs2(1,0);
    
    runInstructions(inst, regs1);
    runInstructions(inst, regs2);

    cout << "Part 1: " << regs1.b << endl;
    cout << "Part 2: " << regs2.b << endl;

    
    return 0;
}
