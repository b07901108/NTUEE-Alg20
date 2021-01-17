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

	#ifdef DEBUG
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
	if (_graph->_graphType) { kruskal(); }
	else {
		align();
		//kruskal();
		//posSelect();
	}
}

void
CbSolver::kruskal()
{
	cout << "Maximum spanning tree" << "\n";
	// TODO
	// Test_dfs
	DisjointSets A(_graph->getVCnt());
	//sorted edges
	_graph->sortByWeight();
	for (auto &e: _graph->_E) {
		if (!A.same(e._start, e._end)) {
			A.unite(e._start, e._end);
		} else {
			_ansEdges.push_back(e);
			_cb += e._weight;
		}
	}
}

void
CbSolver::posSelect()
{
	cout << "Positive edge selection" << "\n";
	// TODO
	// Test_dfs
	// TODO: modify data structure to minheap and maxheap?
	// TODO: check other cycles created by connection
	DisjointSets forward(_graph->getVCnt()); // from small vertex to large one
	DisjointSets backward(_graph->getVCnt()); // from large vertex to small one
	//sorted edges
	//_graph->sortByWeight();
	for (auto &e: _graph->_E) {
		auto search_result = ::find(_ansEdges.begin(), _ansEdges.end(), e);
		if (search_result == _ansEdges.end()) {
			if (e._start < e._end) {
				forward.unite(e._start, e._end);
			} else if (e._start > e._end) {
				backward.unite(e._start, e._end);
			}
		} else if (e._weight > 0) {
			/*
			// Naive implementation and is wrong
			if (e._start < e._end) {
				if (!backward.same(e._start, e._end)) {
					// We can add this edge without generating a cycle!
					_ansEdges.push_back(e);
					forward.unite(e._start, e._end);
					_cb -= e._weight;
				}
			} else if (e._start > e._end) {
				if (!forward.same(e._start, e._end)) {
					_ansEdges.push_back(e);
					backward.unite(e._start, e._end);
					_cb -= e._weight;
				}
			}
			*/
			if (e._start < e._end) {
				if (!backward.same(e._start, e._end)) {
					// We can add this edge without generating a cycle!
					_ansEdges.push_back(e);
					forward.unite(e._start, e._end);
					_cb -= e._weight;
				}
			} else if (e._start > e._end) {
				if (!forward.same(e._start, e._end)) {
					_ansEdges.push_back(e);
					backward.unite(e._start, e._end);
					_cb -= e._weight;
				}
			}
		}
	}
	//printAns(cout);
	//_graph->dfs();
	//_graph->printDfs(cout);
}

void
CbSolver::align()
{
	cout << "Maximum spanning tree" << "\n";
	vector<Edge> tempTree;
	DisjointSets A(_graph->getVCnt());
	//sorted edges
	_graph->sortByWeight();
	vector<uint> startV;
	for (auto &e: _graph->_E) {
		if (!A.same(e._start, e._end)) {
			A.unite(e._start, e._end);
			tempTree.push_back(e);
		}
	}
	// Search for source node
	for (auto &v: _graph->_V) {
		v._adjEdges.clear();
	}
	for (auto &e: tempTree) {
		_graph->_V[e._end]._adjEdges.push_back(e);
	}
	for (uint i=0; i<_graph->_verticeCnt; ++i) {
		if (_graph->_V[i]._adjEdges.empty()) { startV.push_back(i); }
		_graph->_V[i]._adjEdges.clear();
	}
	// DFS for vertex depth
	for (auto &e: tempTree) {
		_graph->_V[e._start]._adjEdges.push_back(e);
	}
	for (auto &idx: startV) {
		_graph->_dfsList.push_back(idx);
		_graph->dfsVisit((_graph->_V[idx]), 1);
	}
	
	cout << "Positive edge selection" << "\n";
	for (auto &e: _graph->_E) {
		auto search_result = ::find(tempTree.begin(), tempTree.end(), e);
		if (search_result == tempTree.end()) {
			if (e._weight > 0) {
				if (_graph->_V[e._start]._depth > _graph->_V[e._end]._depth) {
					_ansEdges.push_back(e);
					_cb += e._weight;
				}
			} else {
				// Negative edges
				_ansEdges.push_back(e);
				_cb += e._weight;
			}
		}
	}
}

void
CbSolver::checkSol()
{
	DisjointSets forward(_graph->getVCnt()); // from small vertex to large one
	DisjointSets backward(_graph->getVCnt()); // from large vertex to small one
	for (auto &e: _graph->_E) {
		if (::find(_ansEdges.begin(), _ansEdges.end(), e) == _ansEdges.end()) {
			if (e._start < e._end) {
				forward.unite(e._start, e._end);
			} else if (e._start > e._end) {
				backward.unite(e._start, e._end);
			}
		} 
	}
	for (uint i=0; i<_graph->_verticeCnt; ++i) {
		for (uint j=i+1; j<_graph->_verticeCnt; ++j) {
			if (forward.same(i, j) && backward.same(i, j)) {
				cout << "Cycle(" << i << ", " << j << ")\n";
			}
		}
	}
}

void
CbSolver::printCycle() const
{
	// TODO
}
