//-----------------------------------------------------------------------------
// Liam Murray
// CSE 101, Spring 2023, Pa5
// Shuffle.cpp
// Shuffle client for the List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include"List.h"
#include <cassert>
#include <set>
#include <iterator>

using namespace std;

void shuffle(List& D) {
    int len = D.length();
    D.moveFront();
    int half = len / 2;
    List fr;
    List bk;
    for(int i = 0; i < half; i++) {
        fr.insertBefore(D.moveNext());
    }
    while(D.position() != D.length()) {
        bk.insertBefore(D.moveNext());
    }
    D.clear();
    fr.moveFront();
    bk.moveFront();
    while(fr.position() != fr.length() && bk.position() != bk.length()) {
        D.insertBefore(bk.moveNext());
        D.insertBefore(fr.moveNext());
    }
    if (bk.position() != bk.length()) {
        D.insertBefore(bk.moveNext());
    }
    D.moveFront();
    return;
}


int main(int argc, char * argv[]) {
    if (argc != 2) {
        fprintf(stderr, "ERROR: Invalid arguments passed. Please refer to guide for usage: \n\nRUN PROGRAM AS FOLLOWS: Shuffle <integer>\n");
        exit(1);
    }
    int shuffles = stoi(argv[1]);
    cout << "deck size       shuffle count" << endl;
    cout << "------------------------------" << endl;
    for (int j = 1; j <= shuffles; j++) {
        List L;
        for (int i = 0; i < j; i++) {
            L.insertBefore(i);
        }
        int counter = 1;
        List cL(L);
        shuffle(L);
        while ((cL == L) == false) {
            shuffle(L);
            counter += 1;
        }
        int lj = std::to_string(j).length();
        cout << " " << j;
        for (int num = 0; num < (16- lj); num++) {
            cout << " ";
        }
        cout << counter;
        cout << endl;
    }
    return 0;
}
