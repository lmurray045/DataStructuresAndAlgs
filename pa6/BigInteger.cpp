//-----------------------------------------------------------------------------
// Liam Murray
// Lijamurr
// CSE 101, Spring 2023, Pa6
// BigInteger.cpp
// Source Code for BigInt ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<algorithm>
#include"List.h"
#include"BigInteger.h"
#include <cassert>
#include <set>
#include <cmath>
#include <iterator>

using namespace std;

ListElement base = 1000000000;
int power = 9;

//constructors -------------------------------------------------------------

BigInteger::BigInteger() {
    signum = 0;
}

BigInteger::BigInteger(long x) {
    if (x == 0) {
        return;
    } 
    string strint = std::to_string(x);
    if (strint[0] == '-') {
        signum = -1;
        strint.erase(0, 1);
    }
    else {
        signum = 1;
    }
    if (strint[0] == '+') {
        strint.erase(0, 1);
    }
    string substring = "";
    int counter = 1;
    for(int i = size(strint) - 1;  i >= 0; i--) {
        substring += strint[i];
        if(counter % power == 0 && i != 0) {
            reverse(substring.begin(), substring.end());
            digits.insertAfter(stol(substring));
            substring = "";
        }
        counter++;
    }
    reverse(substring.begin(), substring.end());
    if (stol(substring) == 0){
        return;
    }
    digits.insertAfter(stol(substring));
    return;   
}

BigInteger::BigInteger(std::string s) {
    if (s == "0") {
        return;
    } 
    string strint = s;
    if (strint[0] == '-') {
        signum = -1;
        strint.erase(0, 1);
    }
    else {
        signum = 1;
    }
    if (strint[0] == '+') {
        strint.erase(0, 1);
    }
    string substring = "";
    int counter = 1;
    for(int i = size(strint) - 1;  i >= 0; i--) {
        substring += strint[i];
        if(counter % power == 0 && i != 0) {
            reverse(substring.begin(), substring.end());
            digits.insertAfter(stol(substring));
            substring = "";
        }
        counter++;
    }
    reverse(substring.begin(), substring.end());
    if (stol(substring) == 0){
        return;
    }
    digits.insertAfter(stol(substring));
    return;   
}


BigInteger::BigInteger(const BigInteger& N) {
    signum = N.signum;
    List cD(N.digits);
    cD.moveFront();
    while(cD.position() != cD.length()) {
        digits.insertBefore(cD.moveNext());
    }
}


// Access functions --------------------------------------------------------

   // sign()
   // Returns -1, 1 or 0 according to whether this BigInteger is positive, 
   // negative or 0, respectively.
int BigInteger::sign() const {
    return signum;
}

   //compare()
   // Returns -1, 1 or 0 according to whether this BigInteger is less than N,
   // greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const{
    if (signum < N.signum) {
        return -1;
    }
    if (signum > N.signum) {
        return 1;
    }
    if (digits.equals(N.digits)) {
        return 0;
    }
    List cD(N.digits);
    List cS(digits);
    if (cS.length() < cD.length()) {
        return -1;
    }
    if (cS.length() > cD.length()) {
        return 1;
    }
    cD.moveFront();
    cS.moveFront();
    while(cD.position() != cD.length()) {
        ListElement sE = cS.moveNext();
        ListElement cE = cD.moveNext();
        if (sE < cE) {
            return -1;
        }
        if (sE > cE) {
            return 1;
        }
    }
    return 0;
}

// Manipulation procedures -------------------------------------------------

   // makeZero()
   // Re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {
    digits.clear();
    signum = 0;
}

   // negate()
   // If this BigInteger is zero, does nothing, otherwise reverses the sign of 
   // this BigInteger positive <--> negative. 
void BigInteger::negate() {
    if (signum == 0) {
        return;
    }
    if (signum == 1) {
        signum = -1;
        return;
    }
    if (signum == -1) {
        signum = 1;
        return;
    }
}

//helper functions ----------------------------------------------------------
// negate List();
void negateList(List& L) {
    L.moveFront();
    while(L.position() != L.length()) {
        ListElement elm = L.moveNext();
        L.setBefore(elm - (2 * elm));
    }
    return;
}

void sumList(List& S, List A, List B, int sgn) {
    A.moveFront();
    B.moveFront();
    int compare = 0;
    if (A.length() < B.length()){
        compare = -1;
    }
    else if (A.length() > B.length()){
        compare = 1;
    }
    else {
        while(A.position() != A.length()) {
            ListElement sE = A.moveNext();
            ListElement cE = B.moveNext();
            if (sE < cE) {
                compare = -1;
            }
            if (sE > cE) {
                compare = 1;
            }
        }
    }
    List Y;
    List X;
    if (A.length() <= 1){
        if (A.length() == 0) {
            Y.insertAfter(0);
        }
        else {
            Y.insertAfter(A.front());
        }
    }
    else {
        Y = A;
    }
    if (B.length() <= 1){ 
        if (B.length() == 0) {
            X.insertAfter(0);
        }
        else {
            X.insertAfter(B.front());
        }
    }
    else {
        X = B;
    }
    int switched = 0;
    if ((compare = -1)){
        switched = 1;
    }
    X.moveFront();
    Y.moveFront();
    while((X.length() < Y.length())) {
        X.insertAfter(0);
    }
    while((X.length() > Y.length())) {
        Y.insertAfter(0);
    }
    S.clear();
    X.moveBack();
    Y.moveBack();
    int carry = 0;
    while(X.position() != 0) {
        ListElement a = X.movePrev();
        ListElement b = Y.movePrev();
        a -= carry;
        if(sgn == -1) {
            if (a < b && A.position() != 0) {
                a += base;
                carry = 1;
            }
            else {
                carry = 0;
            }
            S.insertAfter(a - b);
        }
        else if(sgn == 0) {
            S.insertAfter(a);
        }
        else {
            S.insertAfter(a + b);
        }
    }
    if (switched == 1 && sgn == -1 && S.length() != 0) {
        S.moveFront();
        ListElement l = S.peekNext();
        S.setAfter(l - (2 * l));
    }
}

// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m) {
    L.moveFront();
    while(L.position() != L.length()){
        ListElement elm = L.moveNext();
        L.setBefore(elm * m);
    }
}

int normalizeList_to_one(List& L) {
    L.moveFront();
    string snum = "";
    while(L.position() != L.length()){
        int n = L.moveNext();
        snum += std::to_string(n);
    }
    L.clear();
    for(unsigned long i = 0; i < std::size(snum); i++){
        string t = "";
        t += snum[i];
        L.insertBefore(stol(t));
    }
    return 0;
}

int normalizeList(List& L) {
    if (L.length() == 0) {
        return 0;
    }
    L.moveBack();
    int carry = 0;
    while(L.position() != 0){
        int num = L.movePrev();
        L.setAfter(num + carry);
        num = num + carry;
        string snum = std::to_string(num);
        int over = std::size(snum) - power;
        if (over > 0) {
            if (snum[0] == '-' && over == 1) {
                break;
            }
            string sub = "";
            for(int i = 0; i < over; i++){
                sub += snum[0];
                snum.erase(0, 1);
            }
            carry = stoi(sub);
            L.setAfter(stol(snum));
        }
        else {
            carry = 0;
        }
    }
    if (carry >= 1) {
        L.insertBefore(carry);
    }
    if (L.front() == 0) {
        return 0;
    }
    if (L.front() < 0) {
        return -1;
    }
    if (L.front() > 0) {
        return 1;
    }
    return 0;
}

// BigInteger Arithmetic operations ----------------------------------------
// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const {
    BigInteger A;
    A.signum = 1;
    if((signum == -1 || N.signum == -1) && signum != N.signum) {
        sumList(A.digits, digits, N.digits, -1);
    }
    else {
        sumList(A.digits, digits, N.digits, 1);
    }
    if (A.digits.length() == 0) {
        A.signum = 0;
        return A;
    }
    if(signum == -1 && A.digits.length() != 0) {
        A.digits.moveFront();
        ListElement elm = A.digits.peekNext();
        A.digits.setAfter(elm - (2 * elm));
    }
    if (A.digits.front() < 0 && A.digits.length() != 0) {
        A.signum = -1;
        A.digits.moveFront();
        ListElement elm = A.digits.peekNext();
        A.digits.setAfter(elm - (2 * elm));
    }
    normalizeList(A.digits);
    return A;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const {
    BigInteger cN(N);
    cN.signum *= -1;
    return add(cN);
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const {
    BigInteger A(N);
    A.digits.clear();
    A.signum = 1;
    List cT;
    cT = digits;
    normalizeList_to_one(cT);
    cT.moveBack();
    for (int i = 0; i < (cT.length()); i++) {
        BigInteger addL(N);
        addL.signum = 1;
        int elm = cT.movePrev();
        int scale = 1;
        scale = pow(10, i);
        scalarMultList(addL.digits, (elm * scale)); 
        normalizeList(addL.digits);
        addL.digits.moveFront();
        while (addL.digits.position() != addL.digits.length()) {
            ListElement elm = addL.digits.moveNext();
            addL.digits.setBefore(abs(elm));
        }
        BigInteger temp = A.add(addL);
        A.digits = temp.digits;
    }
    normalizeList(A.digits);
    A.signum = (signum * N.signum);
    return A;
}

//other functions -----------------------------------------------------------

std::string BigInteger::to_string() {
    if (signum == 0) {
        return "0";
    }
    string sub = "";
    if (signum == -1) {
        sub += "-";
    }
    digits.moveFront();
    while(digits.position() != digits.length()) {
        string temp = std::to_string(digits.moveNext());
        int ts = temp.size();
        if (ts < power && digits.position() != 1) {
            for(int i = 0; i < power - ts; i ++) {
                sub += "0";
            }
        }
        sub += temp;
    }
    return sub;
}



//overridden operators ---------------------------------------------------

// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
    return stream << N.to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) != 0) {
        return false;
    }
    return true;
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) != -1) {
        return false;
    }
    return true;
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
    if (A.compare(B) == 1) {
        return false;
    }
    return true;
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
    if (A.compare(B) != 1) {
        return false;
    }
    return true;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
    if (A.compare(B) == -1) {
        return false;
    }
    return true;
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
    return A.add(B);
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
    BigInteger temp = A.add(B);
    A.signum = temp.signum;
    A.digits = temp.digits;
    return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
    return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
    BigInteger temp = A.sub(B);
    A.signum = temp.signum;
    A.digits = temp.digits;
    return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
    return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
    BigInteger temp = A.mult(B);
    A.signum = temp.signum;
    A.digits = temp.digits;
    return A;
}

/*
int main() {
    cout << "Empty Number assignment: ";
    BigInteger N;
    cout << N << endl;
    cout << endl << endl;

    long num = 5430027343;
    BigInteger sN(num);
    cout << "Assigned from Number: " << sN << endl;


    cout << endl << endl;
    string s = "560430027343";
    BigInteger stN(s);
    cout << "Assigned from string: " << stN << endl;


    cout << endl << endl;
    BigInteger cN(sN);
    cout << "Copy of Num Assignment: ";
    cout << cN << endl;


    cout << endl << endl;
    cout << "Comparing (" << cN << ") and (" << stN << "): " << cN.compare(stN) << endl;  
    

    cout << endl << endl;
    BigInteger zN(sN);
    cout << "Making " << zN << " zero: ";
    zN.makeZero();
    cout << zN << endl;


    cout << endl << endl;
    BigInteger nN(sN);
    cout << "Negating " << nN;
    nN.negate();
    cout << nN << endl;

    cout << endl << endl;
    cout << "Helper function tests --------------------------------------------------" << endl << endl;
    List L;
    List nL;
    for(int i = 1; i <= 10; i++) {
        L.insertBefore(i);
        if (i % 2 == 0) {
            nL.insertAfter(i);
        }
    }
    cout << "List L: " << L << endl << endl;
    List cL(L);
    negateList(cL);
    cout << "Negated L: " << cL << endl << endl;
    negateList(cL);
    cout << "Twice Negated L: " << cL << endl << endl;

    List aL;
    sumList(aL, L, nL, 1);
    cout << "Adding (" << L << ") and (" << nL << "): " << aL << endl << endl;

    List sL;
    sL.insertAfter(1043);
    sL.insertAfter(1303);
    sL.insertAfter(999);
    sL.insertAfter(998);
    sL.insertAfter(123);
    cout << "Normalizing (" << sL << "): ";
    normalizeList(sL);
    cout << sL << endl << endl;

    ListElement sc = 4;
    cout << "Scaling (" << aL << ") by " << sc << ": ";
    scalarMultList(aL, sc);
    cout << aL << endl << endl;

    cout << "Big Integer Function Tests------------------------------------------------------" << endl << endl;

    BigInteger B = -988887;
    BigInteger C = 654321;
    BigInteger A = B.add(C);
    BigInteger S = B.sub(C);
    BigInteger M = B.mult(C);

    cout << "Adding (" << B << ") and (" << C << "): " << A << endl << endl;

    cout << "Subtracting (" << B << ") and (" << C << "): " << S << endl << endl;

    cout << "Multipling (" << B << ") and (" << C << "): " << M << endl << endl;

    cout << "Override Tests ------------------------------------------------------" << endl << endl;

    BigInteger I1 = 12345678;
    BigInteger I2 = 87654321;

    bool pr;

    cout << "Comparisons: " << endl;
    pr = (I1 == I1);
    cout << "I1 == I1: " << pr << endl;
    pr = (I1 == I2);
    cout << "I1 == I2: " << pr << endl << endl;

    pr = (I1 < I1);
    cout << "I1 < I1: " << pr << endl;
    pr = (I1 < I2);
    cout << "I1 < I2: " << pr << endl << endl;

    pr = (I1 <= I1);
    cout << "I1 <= I1: " << pr << endl;
    pr = (I1 <= I2);
    cout << "I1 <= I2: " << pr << endl << endl;

    pr = (I1 > I1);
    cout << "I1 > I1: " << pr << endl;
    pr = (I1 > I2);
    cout << "I1 > I2: " << pr << endl << endl;

    pr = (I1 >= I1);
    cout << "I1 >= I1: " << pr << endl;
    pr = (I1 >= I2);
    cout << "I1 >= I2: " << pr << endl << endl;

    cout << "Adding via '+': (" << I1 << ") + (" << I2 << "): " << I1 + I2 << endl;
    BigInteger pI(I1);
    pI += I2;
    cout << "Adding via '+=': (" << I1 << ") += (" << I2 << "): " << pI << endl << endl;

    cout << "Subtracting via '-': (" << I1 << ") - (" << I2 << "): " << I1 - I2 << endl;
    BigInteger sI(I1);
    sI -= I2;
    cout << "Subtracting via '-=': (" << I1 << ") -= (" << I2 << "): " << sI << endl << endl;

    cout << "Multiplying via '*': (" << I1 << ") * (" << I2 << "): " << I1 * I2 << endl;
    BigInteger mI(I1);
    mI *= I2;
    cout << "Multiplying via '*=': (" << I1 << ") *= (" << I2 << "): " << mI << endl << endl;

    return 0;
}
*/
