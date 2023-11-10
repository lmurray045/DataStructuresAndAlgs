//-----------------------------------------------------------------------------
// Liam Murray, lijamurr
// Pa7
// Order.cpp
// Client Program for Dictionary ADT 
//---------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include "Dictionary.h"

using namespace std;

int main(int argc, char * argv[]) {
    if (argc != 3) {
        fprintf(stderr, "ERROR: Invalid arguments passed. Please refer to guide for usage: \n\nRUN PROGRAM AS FOLLOWS: Order <infile> <outfile>\n");
        exit(1);
    }
    fstream infile;
    infile.open(argv[1], ios::in);
    fstream outfile;
    outfile.open(argv[2], ios::out);
    string s = "";
    Dictionary D;
    int counter = 1;
    while (getline(infile, s, '\n')) {
        D.setValue(s, counter);
        counter++;
    }
    infile.close();
    string inO = D.to_string();
    string preO = D.pre_string();
    outfile << inO << endl;
    outfile << preO;
    outfile.close();
    return 0;
}
