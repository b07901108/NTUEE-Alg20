/****************************************************************************
  FileName     [ mpsSolver.cpp ]
  PackageName  [ mps ]
  Synopsis     [ Define mpsSolver functions ]
  Author       [ Chien-Kai Ma ]
  Copyright    [ Copyleft(c) 2020-present NTU, Taiwan  ]
****************************************************************************/
#include <fstream>
#include <algorithm>
#include <cassert>
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

	int chordCnt;
	int left, right;

	// Read points
	ifs >> _pointCnt;
	initMatrices(_pointCnt);

	chordCnt = _pointCnt / 2;
	_chords2.resize(_pointCnt);
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
	ofstream outfile;
	outfile.open(fileName, ios::out);
	if (!outfile) {
		cerr << "Output file open fail!" << endl;
		return false;
	}

	assert(_mps > 0);
	assert(~_ansChords.empty());
	outfile << _mps << "\n";
	for (auto& chord: _ansChords) {
		outfile << chord << " " << _chords2[chord] << "\n";
	}
	return true;
}

bool
MpsSolver::initMatrices(uint& pointCnt)
{
	_solutions.resize(pointCnt + 1);
	_traces.resize(pointCnt + 1);
	for (uint i=0; i<pointCnt; ++i) {
		_solutions[i].resize(pointCnt - i);
		_traces[i].resize(pointCnt - i);
	}
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
	cout << "Start solving..." << "\n";
	::sort(_chords.begin(), _chords.end());
	_mps = mpsSolve(0, _pointCnt-1);
	// Trace solutions
	traceSolution(0, _pointCnt-1);
}

uint
MpsSolver::mpsSolve(int left, int right)
{
	uint solution = 0;
	if (left >= right) { return 0; }
	int rev_right = _pointCnt - right - 1;
	// Memoize
	if (_solutions[left][rev_right] != 0) { return _solutions[left][rev_right]; }
	// Start solving
	int chord_right = _chords2[left];
	if (chord_right > right || chord_right == 0) {
		solution = mpsSolve(left+1, right);
		_solutions[left][rev_right] = solution;
		_traces[left][rev_right] = 1;
		return solution;
	} else if (chord_right < right) {
		// If chord in optimal solution
		int in_optimal = mpsSolve(left+1, chord_right-1) +
						mpsSolve(chord_right+1, right) + 1;
		int not_in_optimal = mpsSolve(left+1, right);
		solution = (in_optimal > not_in_optimal)
					? in_optimal : not_in_optimal;
		_solutions[left][rev_right] = solution;
		_traces[left][rev_right] = (in_optimal > not_in_optimal)
									? 2 : 1;
		return solution;
	} else {
		solution = mpsSolve(left+1, right-1) + 1;
		_solutions[left][rev_right] = solution;
		_traces[left][rev_right] = 3;
		return solution;
	}	
}

void
MpsSolver::traceSolution(int left, int right)
{
	if (left >= right) { return; }
	int rev_right = _pointCnt - right - 1;
	int chord_right = _chords2[left];
	int cond = _traces[left][rev_right];
	switch (cond)
	{
	case 1:
		traceSolution(left+1, right);
		break;
	case 2:
		_ansChords.push_back(left);
		traceSolution(left+1, chord_right-1);
		traceSolution(chord_right+1, right);
		break;
	case 3:
		_ansChords.push_back(left);
		traceSolution(left+1, right-1);
		break;
	default:
		break;
	}
}

void
MpsSolver::printSolution()
{
	cout << _mps << "\n";
	for (auto& chord: _ansChords) {
		cout << chord << " " << _chords2[chord] << "\n";
	}
}

void
MpsSolver::printMatrices() const
{
	for (auto& v : _solutions)
	{
		for (auto& w : v) {
			cout << w << " ";
		}
		cout << "\n";
	}
	for (auto& v : _traces)
	{
		for (auto& w : v) {
			cout << w << " ";
		}
		cout << "\n";
	}
}