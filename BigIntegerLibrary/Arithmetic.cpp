//-----------------------------------------------------------------------------
// Liam Murray
// lijamurr
// CSE 101, Spring 2023, Pa6
// Arithmetic.cpp
// Source Code for Arithmetic Client
//-----------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "List.h"
#include "BigInteger.h"
#include <cassert>
#include <set>
#include <cmath>
#include <iterator>

using namespace std;

int main(int argc, char * argv[]) {
    if (argc != 3) {
        fprintf(stderr, "ERROR: Invalid arguments passed. Please refer to guide for usage: \n\nRUN PROGRAM AS FOLLOWS: Arithmetic <infile> <outfile>\n");
        exit(1);
    }
    fstream infile;
    infile.open(argv[1], ios::in);
    fstream outfile;
    outfile.open(argv[2], ios::out);
    string nl;
    string aString = "";
    string bString = "";
    getline(infile, aString, '\n');
    getline(infile, nl, '\n');
    getline(infile, bString, '\n');
    BigInteger A(aString);
    BigInteger B(bString);
    infile.close();
    outfile << A << endl << endl;
    outfile << B << endl << endl;
    outfile << (A + B) << endl << endl;
    outfile << (A - B) << endl << endl;
    outfile << (A - A) << endl << endl;

    BigInteger mA(3);
    BigInteger mB(2);
    outfile << (mA * A) - (mB * B) << endl << endl;
    //cout << "A times B ----------------------------------------------------\n";
    outfile << A * B << endl << endl;
    //cout << "A times A ----------------------------------------------------\n";
    outfile << A * A << endl << endl;
    //cout << "B times B ----------------------------------------------------\n";
    outfile << B * B << endl << endl;

    //cout << "Massive Calc ----------------------------------------------------\n";
    BigInteger nA(9);
    BigInteger nB(16);
    BigInteger cA(A);
    BigInteger cB(B);

    for(int i = 0; i < 4; i++){
        cA *= A;
        cB *= B;
    }
    cB *= B;
    outfile << (nA * cA) + (nB * cB) << endl;
    outfile.close();
    return 0;
}
