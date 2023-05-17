//-----------------------------------------------------------------------------
// Liam Murray
// CSE 101, Spring 2023, Pa5
// ListTest.cpp
// Test Harness for List ADT. List is a double ended queue with a vertical
// cursor standing between elements. The cursor position is always defined
// to be an int in the range 0 (at front) to length of List (at back).
// An empty list consists of the vertical cursor only, with no elements.
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include"List.h"
#include <cassert>
#include <set>
#include <iterator>

using namespace std;

//Main
int main (void){
   int i;
   List L;
   List * pL = &L;
   assert(pL != nullptr);
   //List nL;
   cout << "Inserting Behind, 1-10... " << endl;
   for(i=1; i<=10; i++){
      L.insertAfter(i);
   }
   cout << "L = " << L << endl;
   cout << "Clearing List: " << endl;
   L.clear();
   cout << "current list: " << endl;
   cout << "L = " << L << endl;
   cout << "Inserting Before, 1-10... " << endl;
   for(i=1; i<=10; i++){
      L.insertBefore(i);
   }
   cout << "current list: " << endl;
   cout << "L = " << L << endl;
   cout << endl;
   cout << endl;
   L.moveFront();
   cout << "Erasing front two elements..." << endl << endl;
   L.eraseAfter();
   L.eraseAfter();
   L.moveBack();
   cout << "Erasing back two elements..." << endl << endl;
   L.eraseBefore();
   L.eraseBefore();
   cout << "current list: " << endl;
   cout << "L = " << L << endl;
   List cL(L);
   cout << "copied list: " << endl;
   cout << "cL = " << L << endl;
   cout << endl;
   cout << endl;
   cout << "Moving Back:" << endl;
   L.moveBack();
   cout << "Cursor Position: " << L.position() << endl;
   cout << "Moving Front:" << endl;
   L.moveFront();
   cout << "Cursor Position: " << L.position() << endl;
   cout << endl << endl;
   cout << "Moving Next by 3: " << endl;
   L.moveNext();
   L.moveNext();
   L.moveNext();
   cout << "Cursor Position: " << L.position() << endl;
   cout << "Cursor Element Behind: " << L.peekPrev() << endl;
   cout << "Cursor Element Ahead: " << L.peekNext() << endl;
   cout << endl << endl;
   cout << "Moving back by 2: " << endl;
   L.movePrev();
   L.movePrev();
   cout << "Cursor Position: " << L.position() << endl;
   cout << "Cursor Element Behind: " << L.peekPrev() << endl;
   cout << "Cursor Element Ahead: " << L.peekNext() << endl;
   cout << endl << endl;
   cout << "setting ahead element to 88... " << endl;
   L.setAfter(88);
   cout << "current list: " << endl;
   cout << "L = " << L << endl;
   cout << endl << endl;
   cout << "setting behind element to 77... " << endl;
   L.setBefore(77);
   cout << "current list: " << endl;
   cout << "L = " << L << endl << endl;
   int f = 8;
   int f2 = 77;
   L.moveFront();
   cout << "finding the next occurance of " << f << endl;
   cout << "found at pos " << L.findNext(f) << endl;

   L.moveBack();
   cout << "finding the previous occurance of " << f2 << endl;
   cout << "found at pos " << L.findPrev(f2) << endl;

   cout << endl << endl;
   cout << "Testing equals... (false)" << endl;
   cout << "does ( " << L << ") = ( " << cL << ") ?" << endl << L.equals(cL) << endl;

   List ccL(L);

   cout << endl << endl;
   cout << "Testing equals... (true)" << endl;
   cout << "does ( " << L << ") = ( " << ccL << ") ?" << endl << L.equals(ccL) << endl;

   cout << "Testing overloaded '==' operator..." << endl;
   assert(L == ccL);
   cout << "Test Passed.\n";

   cout << endl << endl;
   List nL  = L.concat(cL);
   cout << "Testing contcat: L + cL = " << nL << endl;
   
   cout << endl << endl;
   L = cL;
   cout << "Testing override: L = cL = " << L << endl;

   cout << endl << endl;
   cout << "Testing cleanup..." << endl;
   List C;
   C.insertAfter(1);
   C.insertAfter(0);
   C.insertAfter(4);
   C.insertAfter(4);
   C.insertAfter(5);
   C.insertAfter(9);
   C.insertAfter(1);
   cout << "Current List: " << C << endl;
   C.moveBack();
   C.movePrev();
   C.movePrev();
   C.movePrev();
   cout << "Cursor Positon: " << C.position() << endl;
   C.cleanup();
   cout << "Cleaned List: " << C << endl;
   cout << "Cursor Positon: " << C.position() << endl;
   
   cout << endl << endl;
   List nC;
   nC.insertAfter(1);
   nC.insertAfter(1);
   nC.insertAfter(1);
   nC.insertAfter(1);
   nC.insertAfter(1);
   nC.insertAfter(1);
   nC.insertAfter(1);
   cout << "Current List: " << nC << endl;
   nC.cleanup();
   cout << "Cleaned List: " << nC << endl;
   return 0;
}

