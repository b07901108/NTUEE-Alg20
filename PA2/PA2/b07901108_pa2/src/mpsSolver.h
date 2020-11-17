/****************************************************************************
  FileName     [ mpsSolver.h ]
  PackageName  [ mps ]
  Synopsis     [ Define mpsSolver class ]
  Author       [ Chien-Kai Ma ]
  Copyright    [ Copyleft(c) 2020-present NTU, Taiwan  ]
****************************************************************************/

#include <iostream>
#include <vector>
#include <tuple>
#include <string>
using namespace std;

typedef pair<unsigned, unsigned> chord;

// A solver that solves
// maximum planar subset problem (mps)
class MpsSolver
{
public:
	MpsSolver();
    bool readInput(const string&);
    bool writeOutput(const string&);
    void solve();
    void printChord();
	void printSolution();
private:
    vector<int> _chords;
	vector<int> _chords2;
    int _mps;
    vector<int> _ansChords;
};

