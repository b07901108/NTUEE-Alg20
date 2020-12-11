/****************************************************************************
  FileName     [ cbSolver.h ]
  PackageName  [ cb ]
  Synopsis     [ Define cbSolver class ]
  Author       [ Chien-Kai Ma ]
  Copyright    [ Copyleft(c) 2020-present NTU, Taiwan  ]
****************************************************************************/

#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include "graphDef.h"
using namespace std;

typedef pair<unsigned, unsigned> chord;

// A solver that solves
// cycle breaking problem (cb)
class CbSolver
{
public:
	CbSolver();
    bool readInput(const string&);
    void printSol(ostream&) const;
    bool writeOutput(const string&);
    // TODO: Solution
    void solve();
    void identifyCycles();
    ushort cbSolve(int left, int right);
    void traceSolution(int left, int right);
    void printCycle()       const; // TODO
private:
    Graph *          _graph;
    uint             _cb; // Total weight of removed edges
    vector<Edge>     _ansEdges;
};

// TODO: Build disjoint sets?
