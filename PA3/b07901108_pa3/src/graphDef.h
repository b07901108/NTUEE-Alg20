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
using namespace std;

class Edge
{
public:
    friend class Vertice;
    friend class Graph;
    Edge() : _deleted(false) {}
    void read(ifstream &ifs) { ifs >> _start >> _end >> _weight; }
    void print(ostream &os) const { os << _start << " " << _end << " " << _weight << "\n"; }
private:
    bool    _deleted;
    uint    _start;
    uint    _end;
    int     _weight;
};

class Vertice
{
public:
    friend class Edge;
    friend class Graph;
    // TODO: Solution
    // Debug
    void print(ostream &os) const
    {
        for (auto &e : _adjEdges)
        {
            e->print(os);
        }
        os << "\n";
    }
private:
    Vertice *       _predecessor;
    // TODO: Some other properties
    vector<Edge *>  _adjEdges;
};

class Graph
{
public:
    // Build graph
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
            _V[e._start]._adjEdges.push_back(&e);
            if (_graphType)
            {
                _V[e._end]._adjEdges.push_back(&e);
            }
        }
    }
    void build(ifstream &ifs)
    {
        readE(ifs);
        connect();
    }
    // TODO: Solution
    bool dfs();
    bool dfsVisit();
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
private:
    bool _graphType; // true: undirected
    uint _verticeCnt;
    uint _edgeCnt;
    vector<Vertice> _V;
    vector<Edge>    _E;
};
