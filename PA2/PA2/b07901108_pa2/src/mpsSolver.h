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
    bool initMatrices(uint& size);
    void solve();
    uint mpsSolve(int left, int right);
    void traceSolution(int left, int right);
    void printChord();
	void printSolution();
    void printMatrices() const;
private:
    uint _pointCnt;
    vector<int> _chords;
	vector<int> _chords2;
    uint _mps;
    vector<int> _ansChords;
    vector<vector<int>> _solutions;
    vector<vector<int>> _traces;
};

