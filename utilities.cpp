//
//  utilities.cpp
//  Advent of Code 2015
//
//  Created by Paul Uriarte Vicandi on 08/06/2020.
//  Copyright © 2020 Paul Uriarte Vicandi. All rights reserved.
//

#include "utilities.hpp"

bool readFile(string filename, string &output)
{
    ifstream inputFile(filename);
    if (!inputFile.is_open())
        return false;
    
    // read file line by line
    string line;
    output = "";
    while (getline(inputFile, line))
    {
        output += line + '\n';
    }
    inputFile.close();
    
    return true;
}
