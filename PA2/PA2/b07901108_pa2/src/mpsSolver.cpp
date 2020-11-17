/****************************************************************************
  FileName     [ mpsSolver.cpp ]
  PackageName  [ mps ]
  Synopsis     [ Define mpsSolver functions ]
  Author       [ Chien-Kai Ma ]
  Copyright    [ Copyleft(c) 2020-present NTU, Taiwan  ]
****************************************************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include "mpsSolver.h"

MpsSolver::MpsSolver() { this->_mps = 0; }

bool
MpsSolver::readInput(const string& fileName)
{
	ifstream ifs(fileName.c_str());
    if (!ifs) {
        cerr << "Error: \"" << fileName << "\" does not exist!!" << endl;
        return false;
    }

	int pointCnt, chordCnt;
	int left, right;

	// Read points
	ifs >> pointCnt;
	#ifdef DEBUG
	cout << pointCnt << "\n";
	#endif

	chordCnt = pointCnt / 2;
	_chords2.resize(pointCnt);
	for (int i=0; i<chordCnt; ++i) {
		// Read endpoints
		ifs >> left >> right;
		_chords.push_back(left);
		_chords2[left] = right;
	}
	return true;
}

bool
MpsSolver::writeOutput(const string& fileName)
{
	return true;
}

void
MpsSolver::printChord()
{
	for (auto chord: this->_chords) {
		cout << chord << " " << _chords2[chord] << "\n";
	}
}

void
MpsSolver::solve()
{
	cout << "Starting solving..." << "\n";
}

void
MpsSolver::printSolution()
{
	for (auto chord: this->_ansChords) {
		cout << chord << "\n";
	}
}