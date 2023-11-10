//-----------------------------------------------------------------------------
// Liam Murray, lijamurr
// Pa7
// DictionaryTest.cpp
// Test Harness for Dictionary ADT 
//---------------------------------------------------------------------

#include <iostream>
#include <string>
#include "Dictionary.h"

using namespace std;

int main() {
    Dictionary D;
    printf("D insert start\n");
    D.setValue("B", 1);
    D.setValue("A", 2);
    D.setValue("C", 3);
    D.setValue("D", 4);
    D.setValue("C", 99);
    printf("D insert end\n");

    Dictionary C;
    printf("C insert start\n");
    C.setValue("A", 2);
    C.setValue("D", 4);
    C.setValue("B", 1);
    C.setValue("C", 3);
    C.setValue("C", 99);
    printf("C insert end\n");
    cout << D << endl << endl;
    cout << "Size: " << D.size() << endl;
    cout << "D contains 'Hello': " << D.contains("A") << endl;
    cout << "D contains 'Womp Womp': " << D.contains("Womp Womp") << endl << endl;
    cout << "Value of 'Whats Up': " << D.getValue("C") << endl;
    //cout << "Value of 'Womp Womp': " << D.getValue("Womp Womp") << endl;
    cout << endl << endl;
    std::string s = "";
    cout << "Pre Order of Dictionary D: " << endl << D.pre_string() << endl << endl;


    cout << "Dictionary C: \n" << C << endl;
    cout << "Dictionary D: \n" << D << endl;

    cout << "Comparing Dictionary C and D : " << D.equals(C) << endl << endl;

    Dictionary E(D);
    cout << "Copying D into E via Constructor...\n";
    cout << "Dictionary E: \n" << E << endl;

    
    Dictionary B;
    B = D;
    cout << "Copying D into B via Overload...\n";
    cout << "Dictionary B: \n" << B << endl;


    D.begin();
    cout << "Min value of D: (" << D.currentKey()  << " : " << D.currentVal()  << ") "<< endl;
    D.next();
    cout << "Next Cursor value: (" << D.currentKey()  << " : " << D.currentVal()  << ") "<< endl;
    D.next();
    cout << "Next Cursor value: (" << D.currentKey()  << " : " << D.currentVal()  << ") "<< endl << endl;
    D.end();
    cout << "Max value of D: (" << D.currentKey()  << " : " << D.currentVal()  << ") "<< endl << endl;
    D.prev();
    cout << "Prev Cursor value: (" << D.currentKey()  << " : " << D.currentVal()  << ") "<< endl;
    D.prev();
    cout << "Prev Cursor value: (" << D.currentKey()  << " : " << D.currentVal()  << ") "<< endl << endl;
    D.remove("A");
    cout << "Removing 'A': \n" << D.pre_string() << endl;
    D.remove("B");
    cout << "Removing 'B': \n" << D.pre_string() << endl;

    D.clear();
    cout << "D after being cleared: " << D << endl << endl;
    
    return 0;
}
