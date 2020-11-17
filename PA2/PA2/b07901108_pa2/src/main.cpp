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
#include "mpsSolver.h"

using namespace std;

void help_message() {
    cout << "usage: mps <input_file> <output_file>" << endl;
}

int main(int argc, char **argv)
{
	if(argc != 3) {
       help_message();
       return 0;
    }
	string inputFile = argv[1];
    string outputFile = argv[2];
    MpsSolver mpsSolver;
    mpsSolver.readInput(inputFile);
    #ifndef DEBUG
    mpsSolver.printChord();
    #endif
    mpsSolver.solve();
    mpsSolver.writeOutput(outputFile);
	return 0;
}
