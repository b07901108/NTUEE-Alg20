/****************************************************************************
  FileName     [ main.cpp ]
  PackageName  [ main ]
  Synopsis     [ Define main() ]
  Author       [ Chien-Kai Ma ]
  Copyright    [ Copyleft(c) 2020-present NTU, Taiwan  ]
****************************************************************************/

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include "../lib/tm_usage.h"
#include "cbSolver.h"

using namespace std;

bool CompareWeight(Edge e1, Edge e2) {
    return e1._weight > e2._weight;
};

void help_message() {
    cout << "usage: cb <input_file> <output_file>" << endl;
}

int main(int argc, char **argv)
{
	if(argc != 3) {
       help_message();
       return 0;
    }
    CommonNs::TmUsage tmusg;
    CommonNs::TmStat stat;
    tmusg.periodStart();
	string inputFile = argv[1];
    string outputFile = argv[2];
    CbSolver * cbSolver = new CbSolver();
    cbSolver->readInput(inputFile);
    cbSolver->solve();
    //cbSolver->checkSol();
    cbSolver->writeOutput(outputFile);
    tmusg.getPeriodUsage(stat);
    cout << "The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms\n";
    cout << "memory: " << stat.vmPeak << "KB\n"; // print peak memory
	return 0;
}
