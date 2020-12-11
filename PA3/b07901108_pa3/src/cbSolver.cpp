/****************************************************************************
  FileName     [ cbSolver.cpp ]
  PackageName  [ cb ]
  Synopsis     [ Define cbSolver functions ]
  Author       [ Chien-Kai Ma ]
  Copyright    [ Copyleft(c) 2020-present NTU, Taiwan  ]
****************************************************************************/
#include <fstream>
#include <algorithm>
#include <cassert>
#include "cbSolver.h"

CbSolver::CbSolver() { this->_cb = 0; }

bool
CbSolver::readInput(const string& fileName)
{
	ifstream ifs(fileName.c_str());
    if (!ifs) {
        cerr << "Error: \"" << fileName << "\" does not exist!!" << endl;
        return false;
    }

	string bufferStr;
	uint bufferUint1, bufferUint2;
	int	bufferInt;
	ifs >> bufferStr;	// Graph type
	ifs >> bufferUint1; // Total vertices
	ifs >> bufferUint2; // Total edges
	if (bufferStr == "u") {
		_graph = new Graph(true, bufferUint1, bufferUint2);
	} else if (bufferStr == "d") {
		_graph = new Graph(false, bufferUint1, bufferUint2);
	} else {
		cout << "Invalid graph type!\n";
		return false;
	}
	_graph->build(ifs);

	#ifndef DEBUG
	_graph->printV(cout);
	#endif
	return true;
}

void
CbSolver::printSol(ostream& os) const
{
	os << _cb << "\n";
	for (auto& e : _ansEdges)
	{
		e.print(os);
		os << "\n";
	}
}

bool
CbSolver::writeOutput(const string& fileName)
{
	ofstream outfile;
	outfile.open(fileName, ios::out);
	if (!outfile) {
		cerr << "Output file open fail!" << endl;
		return false;
	}
	printSol(outfile);
	return true;
}

void
CbSolver::solve()
{
	cout << "Start solving..." << "\n";
	// TODO
}

ushort
CbSolver::cbSolve(int left, int right)
{
	// TODO
}

void
CbSolver::traceSolution(int left, int right)
{
	// TODO
}

void
CbSolver::printCycle() const
{
	// TODO
}
