/****************************************************************************
  FileName     [ graphDef.h ]
  PackageName  [ cb ]
  Synopsis     [ Define graph class ]
  Author       [ Chien-Kai Ma ]
  Copyright    [ Copyleft(c) 2020-present NTU, Taiwan  ]
****************************************************************************/
#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <cassert>
#include <fstream>
#include <algorithm>
#include "dset.h"
using namespace std;

class Edge
{
public:
    friend class Vertice;
    friend class Graph;
    //friend class UGraph;
    //friend class DGraph;
    Edge() : _deleted(false) {}
    void read(ifstream &ifs) { ifs >> _start >> _end >> _weight; }
    void print(ostream &os) const { os << _start << " " << _end << " " << _weight << "\n"; }
    bool operator==(const Edge e) {
        return (this->_start == e._start) && (this->_end == e._end);
    }
//private:
    bool    _deleted;
    uint    _start;
    uint    _end;
    int     _weight;
};

bool CompareWeight(Edge e1, Edge e2);

class Vertice
{
public:
    friend class Edge;
    friend class Graph;
    //friend class UGraph;
    //friend class DGraph;
    // TODO: Solution
    // Debug
    void print(ostream &os) const
    {
        for (auto &e : _adjEdges)
        {
            e.print(os);
        }
        os << "\n";
    }
//private:
    bool            _visited = false;
    Vertice *       _pred   = 0;
    // TODO: Some other properties
    uint            _depth  = 0;
    vector<Edge>  _adjEdges;
};

class Graph
{
public:
    // Build graph
    Graph() {}
    Graph(bool gType, uint &vCnt, uint &eCnt)
        : _graphType(gType), _verticeCnt(vCnt), _edgeCnt(eCnt)
    {
        _V.resize(_verticeCnt);
        _E.resize(_edgeCnt);
    };
    void readE(ifstream &ifs)
    {
        assert(_verticeCnt);
        assert(_edgeCnt);
        for (uint i; i < _edgeCnt; ++i)
            _E[i].read(ifs);
    }
    void connect()
    {
        for (auto &e : _E)
        {
            _V[e._start]._adjEdges.push_back(e);
        }
    }
    void build(ifstream &ifs)
    {
        readE(ifs);
        connect();
    }
    // TODO: Solution
    //virtual bool dfs();
    void sortByWeight() {
        ::sort(_E.begin(), _E.end(), CompareWeight);
    }
    void deleteEdge(Edge *e);
    // Print
    void printV(ostream &os) const
    {
        for (uint i; i < _verticeCnt; ++i)
        {
            os << i << ": \n";
            _V[i].print(os);
        }
    }
    void printE(ostream &os) const
    {
        for (auto &e : _E)
            e.print(os);
    }
    void printDfs(ostream &os) const
    {
        for (auto &v : _dfsList)
            cout << v << "\n";
    }
    bool dfs() {
        for (uint i=0; i<_V.size(); ++i) {
            if (!_V[i]._visited) {
                _V[i]._pred = &_V[i];
                _dfsList.push_back(i);
                dfsVisit(_V[i], i);
            }
        }
        for (auto& v : _V) {
            v._visited = false;
        }
        return true;
    }
    /*
    bool dfsVisit(Vertice& v, uint idx) {
        assert(!v._visited);
        v._visited = true;
        cout << idx << "\n";
        for (auto adjE : v._adjEdges) {
            uint adjIdx = (idx == adjE._start)
                            ? adjE._end : adjE._start;
            if (_V[adjIdx]._pred == 0) {
                _V[adjIdx]._pred = &v;
                _dfsList.push_back(&_V[adjIdx]);
                dfsVisit(_V[adjIdx], adjIdx);
            } else if (_V[adjIdx]._pred != &v) {
                cout << "Cycle detected!\n";
            }
        }
        return true;
    }
    */
    bool dfsVisit(Vertice& v, uint depth) {
        if (depth > v._depth) {
            v._depth = depth;
            // Update
            for (auto adjE : v._adjEdges) {
                //uint adjIdx = (idx == adjE._start)
                                //? adjE._end : adjE._start;
                uint adjIdx = adjE._end;
                _dfsList.push_back(adjIdx);
                dfsVisit(_V[adjIdx], depth+1);
            }
        }
        return true;
    }
    uint getECnt() const { return _edgeCnt; }
    uint getVCnt() const { return _verticeCnt; }
    vector<Vertice>* getV() { return &_V; }
    vector<Edge>* getE() { return &_E; }
//protected:
    bool _graphType; // true: undirected
    bool _weighted;
    uint _verticeCnt;
    uint _edgeCnt;
    vector<Edge>    _E;
    vector<Vertice> _V;
    vector<uint> _dfsList;
};

/*
class UGraph: public Graph
{
friend class Graph;
public:
    UGraph(bool gType, uint &vCnt, uint &eCnt)
    {
        _graphType = gType;
        _verticeCnt = vCnt;
        _edgeCnt = eCnt;
        _V.resize(_verticeCnt);
        _E.resize(_edgeCnt);
    };
    //~UGraph() { }
    bool dfs() override {
        for (uint i=0; i<_V.size(); ++i) {
            if (!_V[i]._visited) {
                _V[i]._pred = &_V[i];
                _dfsList.push_back(&_V[i]);
                dfsVisit(_V[i], i);
            }
        }
        for (auto& v : _V) {
            v._visited = false;
        }
        return true;
    }
    bool dfsVisit(Vertice& v, uint idx) {
        assert(!v._visited);
        v._visited = true;
        cout << idx << "\n";
        for (auto adjE : v._adjEdges) {
            uint adjIdx = (idx == adjE->_start)
                            ? adjE->_end : adjE->_start;
            if (_V[adjIdx]._pred == 0) {
                _V[adjIdx]._pred = &v;
                _dfsList.push_back(&_V[adjIdx]);
                dfsVisit(_V[adjIdx], adjIdx);
            } else if (_V[adjIdx]._pred != &v) {
                cout << "Cycle detected!\n";
            }
        }
        return true;
    }
private:

};

class DGraph: public Graph
{
public:
    DGraph(bool gType, uint &vCnt, uint &eCnt)
    {
        _graphType = gType;
        _verticeCnt = vCnt;
        _edgeCnt = eCnt;
        _V.resize(_verticeCnt);
        _E.resize(_edgeCnt);
    };
    //~DGraph() { }
    bool dfs() override { return true; }
};
*/