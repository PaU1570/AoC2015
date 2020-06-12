//
//  main.cpp
//  Day 24
//
//  Created by Paul Uriarte Vicandi on 11/06/2020.
//  Copyright © 2020 Paul Uriarte Vicandi. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include "utilities.hpp"

string filename = "/Users/pauluv/Documents/Code/Advent of Code 2015/Inputs/Day24.txt";

class Node
{
public:
    Node() : m_terms(), m_sum(0) {}
    int sum() const {return m_sum;}
    size_t numberOfTerms () const {return m_terms.size();}
    bool add(int val)
    {
        if (hasTerm(val))
            return false;
        m_terms.push_back(val);
        sort(m_terms.begin(), m_terms.end());
        m_sum += val;
        return true;
    }
    bool hasTerm(int val)
    {
        for (int i = 0; i < m_terms.size(); i++)
        {
            if (m_terms[i] == val)
                return true;
        }
        return false;
    }
    bool sameTerms(const Node &other) const
    {
        if (m_terms.size() != other.m_terms.size())
            return false;
        for (int i = 0; i < m_terms.size(); i++)
        {
            if (m_terms[i] != other.m_terms[i])
                return false;
        }
        return true;
    }
    unsigned long int quantum() const
    {
        if (m_terms.empty())
            return 0;
        unsigned long int prod = m_terms[0];
        for (int i = 1; i < m_terms.size(); i++)
            prod *= m_terms[i];
        return prod;
    }
    bool operator<(const Node &other) const
    {
        if (m_sum != other.m_sum)
            return m_sum < other.m_sum;
        if (m_terms.size() != other.m_terms.size())
            return m_terms.size() < other.m_terms.size();
        return quantum() < other.quantum();
    }
private:
    vector<int> m_terms;
    int m_sum;
};

// we want the Node with the fewest terms but the largest sum to be the 'biggest'
class compareNodes
{
public:
    bool operator() (const Node &lhs, const Node &rhs) const
    {
        if (lhs.numberOfTerms() != rhs.numberOfTerms())
            return lhs.numberOfTerms() < rhs.numberOfTerms();
        return lhs.sum() < rhs.sum();
    }
};

int parseInput(string input, vector<int> &weights)
{
    size_t ipos = 0;
    size_t fpos = 0;
    int sum = 0;
    while (ipos < input.size())
    {
        fpos = input.find('\n', ipos); // find position of next line end
        string token = input.substr(ipos, fpos - ipos); // get substring (line)
        ipos = fpos + 1;
        weights.push_back(stoi(token));
        sum += stoi(token);
    }
    return sum;
}

bool contains(vector<Node> &exploredSums, Node sum)
{
    for (int i = 0; i < exploredSums.size(); i++)
    {
        if (exploredSums[i].sameTerms(sum))
            return true;
    }
    return false;
}

void findGroups(priority_queue<Node, vector<Node>, compareNodes> &nodeq, set<Node> &validNodes, vector<int> weights, int groupSize, int sumsToExplore)
{
    vector<Node> exploredSums;
    size_t minpackages = weights.size();
    while (!nodeq.empty())
    {
        Node current = nodeq.top();
        nodeq.pop();
        exploredSums.push_back(current);
        
        //cout << "Queue size: " << nodeq.size();
        //cout << "; current sum: " << current.sum() << endl;
        
        if (current.sum() == groupSize)
        {
            // only add if it has fewer or equal terms as the already found ones
            if (current.numberOfTerms() <= minpackages)
            {
                minpackages = current.numberOfTerms();
                validNodes.insert(current);
            }
            
            if (validNodes.size() >= sumsToExplore)
                break;
        }
        else if (current.sum() < groupSize && current.numberOfTerms() < minpackages)
        {
            for (int i = 0; i < weights.size(); i++)
            {
                Node copy = current;
                if (copy.add(weights[i]) && !contains(exploredSums, copy))
                {
                    nodeq.push(copy);
                }
            }
        }
    }
}

int main()
{
    string input;
    readFile(filename, input);
    vector<int> weights;
    int totalWeight = parseInput(input, weights);
    
    // part 1
    int groupSize = totalWeight / 3;
    priority_queue<Node, vector<Node>, compareNodes> nodeq;
    set<Node> validNodes;
    
    Node initial;
    nodeq.push(initial);
    
    findGroups(nodeq, validNodes, weights, groupSize, 5);
    cout << "Part 1 - first few options for first group (not guaranteed that these are compatible with the other two groups):" << endl;
    for (set<Node>::iterator p = validNodes.begin(); p != validNodes.end(); p++)
    {
        cout << "Total weight = " << p->sum() << "; packages = " << p->numberOfTerms() << "; quantum = " << p->quantum() << endl;
    }
    
    // part 2
    int groupSize2 = totalWeight / 4;
    priority_queue<Node, vector<Node>, compareNodes> nodeq2;
    set<Node> validNodes2;
    
    nodeq2.push(initial);
    
    findGroups(nodeq2, validNodes2, weights, groupSize2, 5);
    cout << "Part 2 - first few options for first group (not guaranteed that these are compatible with the other three groups):" << endl;
    for (set<Node>::iterator p = validNodes2.begin(); p != validNodes2.end(); p++)
    {
        cout << "Total weight = " << p->sum() << "; packages = " << p->numberOfTerms() << "; quantum = " << p->quantum() << endl;
    }
    
    return 0;
}
