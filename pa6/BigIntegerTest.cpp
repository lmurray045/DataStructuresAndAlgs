//-----------------------------------------------------------------------------
// Liam Murray
// lijamurr
// CSE 101, Spring 2023, Pa6
// BigIntegerTest.cpp
// Test Harness for BigInt ADT
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

    cout << "Big Integer Function Tests------------------------------------------------------" << endl << endl;

    BigInteger B("-988887");
    BigInteger C("654318");
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