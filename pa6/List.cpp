//-----------------------------------------------------------------------------
// Liam Murray
// lijamurr
// CSE 101, Spring 2023, Pa6
// List.cpp
// Source Code for List ADT. List is a double ended queue with a vertical
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

//exported type

// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(ListElement x){
   data = x;
   next = nullptr;
   prev = nullptr;
}

// Class Constructors & Destructors -------------------------------------------

// Creates new List in the empty state.
List::List(){
   frontDummy = new Node(-1);
   backDummy = new Node(-1);
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   frontDummy->next = backDummy;
   backDummy->prev = frontDummy;
   pos_cursor = 0;
   num_elements = 0;
}

// Copy constructor.
List::List(const List& L){

   // make this an empty List
   frontDummy = new Node(-1);
   backDummy = new Node(-1);
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   frontDummy->next = backDummy;
   backDummy->prev = frontDummy;
   pos_cursor = 0;
   num_elements = 0;

   // if L is non-empty, load its elements into this
   if( L.num_elements!=0 ){
      Node* N = L.frontDummy->next;
      Node* M = new Node(N->data);
      frontDummy->next = M;
      backDummy->prev = M;
      while( N->next != L.backDummy ){
         N = N->next;
         M->next = new Node(N->data);
         M->next->prev = M;
         M = M->next;
         M->next = backDummy;
         backDummy->prev = M;
      }
      num_elements = L.num_elements;
   }
}

// Destructor
List::~List(){
   clear();
   delete frontDummy;
   delete backDummy;
}

// Access functions -----------------------------------------------------

// returns the number of elements in the list
int List::length() const {
    return(num_elements);
}

// returns the front data element from the list
ListElement List::front() const {
    if (num_elements == 0) {
        throw std::length_error("List: front(): empty list");
    }
    return(frontDummy->next->data);
}

// returns the back data element from the list
ListElement List::back() const {
    if (num_elements == 0) {
        throw std::length_error("List: back(): empty list");
    }
    return(backDummy->prev->data);
}

//returns the position of the cursor
int List::position() const {
    return(pos_cursor);
}

//returns the element to the back of the cursor
ListElement List::peekPrev() const {
    return(beforeCursor->data);
}

//returns the element to the front of the cursor
ListElement List::peekNext() const {
    return(afterCursor->data);
}

//Manipulation Procedures -------------------------------------------------
void List::moveFront() {
    pos_cursor = 0;    
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    return;
}

void List::moveBack() {
    pos_cursor = num_elements;
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;    
    return;
}

ListElement List::moveNext() {
    if(position() >= length()) {
        throw std::length_error("List: moveNext(): position is out of range");
    }
    pos_cursor += 1;
    beforeCursor = beforeCursor->next;
    afterCursor = afterCursor->next;   
    return(peekPrev());
}

ListElement List::movePrev() {
    if(pos_cursor == 0) {
        throw std::length_error("List: movePrev(): position is out of range");
    }
    beforeCursor = beforeCursor->prev;
    afterCursor = afterCursor->prev;
    pos_cursor -= 1;
    return(peekNext());
}

void List::insertAfter(ListElement x) {
    Node * nd = new Node(x);
    afterCursor->prev = nd;
    beforeCursor->next = nd;
    nd->next = afterCursor;
    nd->prev = beforeCursor;
    afterCursor = nd;
    num_elements += 1;
    return;
}

void List::insertBefore(ListElement x) {
    Node * nd = new Node(x);
    afterCursor->prev = nd;
    beforeCursor->next = nd;
    nd->next = afterCursor;
    nd->prev = beforeCursor;
    beforeCursor = nd;
    num_elements += 1;
    pos_cursor += 1;
    return;
}

void List::setAfter(ListElement x) {
    if (position() >= length()) {
        throw std::length_error("List: setAfter(): position is out of range");
    }
    afterCursor->data = x;
    return;
}

void List::setBefore(ListElement x) {
    if (position() <= 0) {
        throw std::length_error("List: setBefore(): position is out of range");
    }
    beforeCursor->data = x; 
    return;
}

void List::eraseAfter() {
    if (position() >= length()) {
        throw std::length_error("List: eraseAfter(): position is out of range");
    }
    if (length() == 1) {
        delete afterCursor;
        frontDummy->next = backDummy;
        backDummy->prev = frontDummy;
        afterCursor = backDummy;
        beforeCursor = frontDummy;
    }
    else {
        beforeCursor->next = beforeCursor->next->next;
        beforeCursor->next->prev = beforeCursor;
        Node * tN = afterCursor;
        afterCursor = beforeCursor->next;
        delete tN;
    }
    num_elements -= 1;
    return;
}

void List::eraseBefore() {
    if (position() <= 0) {
        throw std::length_error("List: eraseBefore(): position is out of range");
    }
    afterCursor->prev = afterCursor->prev->prev;
    afterCursor->prev->next = afterCursor;
    Node * tN = beforeCursor;
    beforeCursor = afterCursor->prev;
    delete tN;
    num_elements -= 1;
    pos_cursor -= 1;
}

void List::clear() {
    moveFront();
    int tnum = num_elements;
    for (int i = 0; i < tnum; i++) {
        eraseAfter();
    }
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
}

//Other Operations--------------------------------------------------------------

int List::findNext(ListElement x) {
    int r;
    for (int i = pos_cursor; i < num_elements; i++) {
        r = moveNext();
        if (r == x) {
            return pos_cursor;
        }
    }
    return -1;
}

int List::findPrev(ListElement x) {
    int r;
    for (int i = pos_cursor; i != 0; i--) {
        r = movePrev();
        if (r == x) {
            return pos_cursor;
        }
    }
    return -1;
}

std::string List::to_string() const{
   Node* N = nullptr;
   std::string s = "";
   for(N=frontDummy->next; N!=backDummy; N=N->next){
      s += std::to_string(N->data)+" ";
   }
   return s;
}

bool List::equals(const List& R) const {
    if (length() != R.length()) {
        return false;
    }
    Node * N = frontDummy->next;
    Node * rN = R.frontDummy->next;
    for (int i = 0; i < length(); i++) {
        if (N->data != rN->data) {
            return false;
        }
        N = N->next;
        rN = rN->next;
    }
    return true;
}

List List::concat(const List& L) const {
    List nL;
    if (length() == 0 && L.length() == 0) {
        return nL;
    }
    Node* N = frontDummy->next;
    while( N != backDummy ){
        nL.insertBefore(N->data);
        N = N->next;
    }
    N = L.frontDummy->next;
    while( N != L.backDummy ){
        nL.insertBefore(N->data);
        N = N->next;
    }
    nL.moveFront();
    return nL;
}

void List::cleanup() {
    set<ListElement> elm;
    set<ListElement> :: iterator s;
    Node * N = frontDummy->next;
    while(N != backDummy) {
        elm.insert(N->data);
        N = N->next;
    }
    for (s = elm.begin(); s != elm.end(); s++) {
        N = frontDummy->next;
        int first = 0;
        int counter = 1;
        while (N != backDummy) {
            if (N->data != *s) {
                N = N->next;
                counter++;
                continue;
            }
            if (first == 0) {
                first = 1;
                N = N->next;
                counter++;
                continue;
            }
            Node * temp = N;
            N = N->next;
            temp->prev->next = N;
            N->prev = temp->prev;
            delete temp;
            num_elements -= 1;
            if (counter <= pos_cursor) {
                pos_cursor -= 1;
            }
        }
    }
    N = frontDummy;
    for(int i = 1; i <= pos_cursor; i++) {
        N = N->next;
    }
    beforeCursor = N;
    afterCursor = N->next;
    return;
}

//Overridden Operators ---------------------------------------------------------
std::ostream& operator<< ( std::ostream& stream, const List& L ) {
   return stream << L.List::to_string();
}

bool operator==( const List& A, const List& B ){
    return(A.equals(B));
}

List& List::operator=( const List& L ) {
    clear();
    Node * N = L.frontDummy->next;
    while( N != L.backDummy ){
        insertBefore(N->data);
        N = N->next;
    }
    pos_cursor = L.pos_cursor;
    num_elements = L.num_elements;
    beforeCursor = L.beforeCursor;
    afterCursor = L.afterCursor;
    return *this;
}

//Main
/*
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
*/
