#include "utilities.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

bool printDebug = true;
string filename = "/Users/pauluv/Documents/Code/Advent of Code 2015/Inputs/Day19.txt";

struct Replacement
{
    Replacement(string f, string t) : from(f), to(t) {}
    string from;
    string to;
};

struct GraphNode
{
    GraphNode(string mol, int rep = 0) : molecule(mol), replacements(rep) {}
    string molecule;
    int replacements;
};

// compare should return true if lhs is smaller than rhs
// priority queue will sort things such that the 'biggest' element goes on the front
// so we want the shortest molecule to be the 'biggest'
class compareNodes
{
public:
    bool operator() (const GraphNode &lhs, const GraphNode &rhs) const
    {
      return lhs.molecule.size() > rhs.molecule.size();
    }
};

void parseInput(string &input, vector<Replacement> &replacementList, string &medicine)
{
    string tmp("");
    Replacement tmpRep("", "");
    
    int i;
    for (i = 0; i < input.size(); i++)
    {
        // if there is a space, put preceding string into 'from'
        if (input[i] == ' ')
        {
            tmpRep.from = tmp;
            tmp = "";
            i += 3;
        }
        // if there is a new line, put preceding string into 'to' and push to vector
        else if (input[i] == '\n')
        {
            tmpRep.to = tmp;
            tmp = "";
            replacementList.push_back(tmpRep);
            // two consecutive line breaks indicate end of replacements
            if (input[i+1] == '\n')
                break;
        }
        // for normal characters, add into tmp
        else
        {
            tmp += input[i];
        }
    }
    // deal with medicine molecule
    medicine = "";
    for (i += 2; i < input.size() - 1; i++)
    {
        medicine += input[i];
    }
}

// stores into positions the starting index of each instance of substr found in the input string
void findAll(string &input, string &substr, vector<int> &positions)
{
    positions.clear();
    
    size_t pos = 0;
    pos = input.find(substr, pos);
    while (pos != string::npos)
    {
        positions.push_back(int(pos));
        pos = input.find(substr, pos+1);
    }
}

// performs every possible reverse replacement (from 'from' to 'to') on the molecule and adds each result to the queue
void revReplaceAll(priority_queue<GraphNode, vector<GraphNode>, compareNodes> &nodeq, Replacement &rep, string &molecule, int replacementNum)
{
    // get indeces of all the occurrences of the 'to' molecule
    vector<int> positions;
    findAll(molecule, rep.to, positions);
    
    // for every insance, replace with the 'from' molecule and add to queue
    for (int i = 0; i < positions.size(); i++)
    {
        string copy(molecule);
        copy.replace(positions[i], rep.to.length(), rep.from);
        GraphNode newNode(copy, replacementNum);
        nodeq.push(newNode);
    }
}

int findPath(priority_queue<GraphNode, vector<GraphNode>, compareNodes> &nodeq, string &goal, vector<Replacement> &repList)
{
    while (!nodeq.empty())
    {
        GraphNode current = nodeq.top();
        nodeq.pop();
                
        if (current.molecule == goal)
            return current.replacements;
        
        for (int i = 0; i < repList.size(); i++)
        {
            revReplaceAll(nodeq, repList[i], current.molecule, current.replacements+1);
        }
    }
    return -1;
}

int main ()
{
    string input("");
    if (!readFile(filename, input))
    {
        cout << "Could not open file: '" << filename << "'" << endl;
        return 2;
    }
    
    string medicine;
    vector<Replacement> repList;
    parseInput(input, repList, medicine);
    
    if (printDebug)
    {
        cout << "Input file:" << endl;
        cout << "----------------------" << endl;
        for (int i = 0; i < repList.size() ; i++)
        {
            cout << repList[i].from << " => " << repList[i].to << endl;
        }
        cout << endl;
        cout << medicine << endl;
        cout << "----------------------" << endl;
    }
    
    priority_queue<GraphNode, vector<GraphNode>, compareNodes> nodeq;
    GraphNode start(medicine, 0);
    nodeq.push(start);
    string electron("e");
    
    int reps = findPath(nodeq, electron, repList);
    cout << "Replacements needed to make medicine: " << reps << endl;
    
    return 0;
}
