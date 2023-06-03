//-----------------------------------------------------------------------------
// Liam Murray, lijamurr
// Pa7
// Dictionary.cpp
// Source Code for Dictionary ADT 
//---------------------------------------------------------------------

#include <iostream>
#include <string>
#include "Dictionary.h"

using namespace std;

// Node Methods and constructors
Dictionary::Node::Node(keyType k, valType v){
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}
//constructors -----------------------------------------
Dictionary::Dictionary(){
    nil = new Node("NIL NIL NIL", -999);
    root = nil;
    current = nil;
    num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D){
    nil = new Node("NIL NIL NIL", -999);
    root = nil;
    current = nil;
    num_pairs = 0;
    preOrderCopy(D.root, D.nil);
    num_pairs = D.num_pairs;
}

//destructor
Dictionary::~Dictionary(){
    clear();
    delete nil;
    nil = nullptr;
    root = nil;
    current = nil;
}

//helper functions ---------------------------------------------------------
Dictionary::Node* Dictionary::search(Dictionary::Node* R, keyType k) const {
    if(R == nil) {
        return nil;
    }
    if (R->key == k) {
        return R;
    }
    Node * Rl = search(R->left, k);
    if (Rl != nil ) {
        return Rl;
    }
    Node * Rr = search(R->right, k);
    if (Rr != nil ) {
        return Rr;
    }
    return nil;
}

void Dictionary::inOrderString(std::string& s, Node* R) const{
    if(R == nil) {
        return;
    }
    inOrderString(s, R->left);
    s += R->key;
    s += " : ";
    valType v = R->val;
    s += std::to_string(v);
    s += "\n";
    inOrderString(s, R->right);
    return;
}

void Dictionary::preOrderString(std::string& s, Node* R) const{
    if(R == nil) {
        return;
    }
    s += R->key;
    s += "\n";
    preOrderString(s, R->left);
    preOrderString(s, R->right);
    return;
}

void Dictionary::preOrderCopy(Node* R, Node* N) {
    if(R == N) {
        return;
    }
    setValue(R->key, R->val);
    preOrderCopy(R->left, N);
    preOrderCopy(R->right, N);
    return;
}

void Dictionary::postOrderDelete(Node* R) {
    if (R == nil) {
        return;
    }
    postOrderDelete(R->left);
    postOrderDelete(R->right);
    delete R;
    R = nullptr;
    return;
}

Dictionary::Node* Dictionary::findMin(Dictionary::Node* R){
    if (R == nil) {
        return nil;
    }
    if (R->left == nil) {
        return R;
    }
    Node * n = findMin(R->left);
    return n;
}

Dictionary::Node* Dictionary::findMax(Dictionary::Node* R) {
    if (R == nil) {
        return nil;
    }
    if (R->right == nil) {
        return R;
    }
    Node * n = findMax(R->right);
    return n;
}

Dictionary::Node* Dictionary::findNext(Dictionary::Node* N) {
    if (N == nil || N == findMax(root)) {
        return nil;
    }
    if (N->right != nil) {
        return findMin(N->right);
    }
    else {
        return N->parent;
    }
}

Dictionary::Node* Dictionary::findPrev(Dictionary::Node* N) {
    if (N == nil || N == findMin(root)) {
        return nil;
    }
    if (N->left != nil) {
        return findMax(N->left);
    }
    else {
        return N->parent;
    }
}

//access functions
int Dictionary::size() const{
    return num_pairs;
}

bool Dictionary::contains(keyType k) const {
    if (search(root, k) == nil) {
        return false;
    }
    else {
        return true;
    }
}

valType& Dictionary::getValue(keyType k) const {
    Node* n = search(root, k);
    if (n == nil) {
        throw std::logic_error("ERROR: in getValue(); Dictionary does not contain key\n");
    }
    return n->val;
}

keyType Dictionary::currentKey() const {
    if (hasCurrent() == false) {
        throw std::logic_error("ERROR: in currentKey(); current undefined\n");
    }
    return current->key;
}

valType& Dictionary::currentVal() const{
    if (hasCurrent() == false) {
        throw std::logic_error("ERROR: in currentVal(); current undefined\n");
    }
    return current->val;
}

bool Dictionary::hasCurrent() const {
    if (current == nil) {
        return false;
    }
    return true;
}

// Manipulation procedures -------------------------------------------------
void Dictionary::setValue(keyType k, valType v){
    if (num_pairs == 0) {
        root = (new Node(k, v));
        root->parent = nil;
        root->left = nil;
        root->right = nil;
        num_pairs += 1;
    }
    Node* R = root;
    while(R->left != nil || R->right != nil){
        if (k == R->key) {
            R->val = v;
            return;
        }
        if(k < R->key && R->left != nil) {
            R = R->left;
            continue;
        }
        else if(k < R->key && R->left == nil) {
            R->left = new Node(k, v);
            R->left->parent = R;
            R->left->left = nil;
            R->left->right = nil;
            num_pairs += 1;
            return;
        }
        if(k > R->key && R->right != nil) {
            R = R->right;
            continue;
        }
        else if (k > R->key && R->right == nil) {
            R->right = new Node(k, v);
            R->right->parent = R;
            R->right->left = nil;
            R->right->right = nil;
            num_pairs += 1;
            return;
        }
    }
    if (k == R->key) {
            R->val = v;
            return;
        }
    if (k < R->key) {
        R->left = new Node(k, v);
        R->left->parent = R;
        R->left->left = nil;
        R->left->right = nil;
        num_pairs += 1;
        return;
    }
    if (k > R->key) {
        R->right = new Node(k, v);
        R->right->parent = R;
        R->right->left = nil;
        R->right->right = nil;
        num_pairs += 1;
        return;
    }
    return;
}

void Dictionary::clear(){
    postOrderDelete(root);
    root = nil;
    num_pairs = 0;
    current = nil;
    return;
}

void Dictionary::begin() {
    if (num_pairs ==  0) {
        return;
    }
    current = findMin(root); 
}

void Dictionary::end() {
    if (num_pairs ==  0) {
        return;
    }
    current = findMax(root); 
}

void Dictionary::next() {
    if (hasCurrent() == false) {
        throw std::logic_error("ERROR: in next(); current undefined\n");
    }
    current = (findNext(current));
}

void Dictionary::prev() {
    if (hasCurrent() == false) {
        throw std::logic_error("ERROR: in prev(); current undefined\n");
    }
    current = (findPrev(current));
}

void Dictionary::remove(keyType k) {
    if (contains(k) == false) {
        throw std::logic_error("ERROR: in remove(); key is not present\n");
    }
    if (hasCurrent() && currentKey() == k){
        current = nil;
    }
    Node * n = search(root, k);
    if (n->parent == nil) {
        if (n->right == nil) {
            root = n->left;
            delete n;
            n = nil;
            num_pairs -= 1;
            return;
        }
        Node * s = findMin(n->right);
        if (s == nil) {
            n->key = n->right->key;
            n->val = n->right->val;
            delete n->right;
            n->right = nil;
            num_pairs -= 1;
            return;
        }
        keyType k = s->key;
        valType v = s->val;
        remove(s->key);
        n->key = k;
        n->val = v;
        return;
    }
    if (n->parent->left == n) {
        if (n->right != nil) {
            Node * s = findMin(n->right);
            if (s == nil) {
                n->key = n->right->key;
                n->val = n->right->val;
                delete n->right;
                n->right = nil;
                num_pairs -= 1;
                return;
            }
            keyType k = s->key;
            valType v = s->val;
            remove(s->key);
            n->key = k;
            n->val = v;
            return;
        }
        if (n->left != nil) {
            n->parent->left = n->left;
            delete n;
            n = nil;
            num_pairs -= 1;
            return;
        }
        if (n->right == nil && n->left == nil) {
            n->parent->left = nil;
            delete n;
            n = nil;
            num_pairs -= 1;
            return;
        }
    }
    if (n->parent->right == n) {
        if (n->right != nil) {
            Node * s = findMin(n->right);
            if (s == nil) {
                n->key = n->right->key;
                n->val = n->right->val;
                delete n->right;
                num_pairs -= 1;
                return;
            }
            keyType k = s->key;
            valType v = s->val;
            remove(s->key);
            n->key = k;
            n->val = v;
            return;
        }
        if (n->left != nil) {
            n->parent->right = n->left;
            delete n;
            n = nil;
            num_pairs -= 1;
            return;
        }
        if (n->right == nil && n->left == nil) {
            n->parent->right = nil;
            delete n;
            n = nil;
            num_pairs -= 1;
            return;
        }
    }
}  

//other functions----------------------------------------------------------------
std::string Dictionary::to_string() const{
    std::string s = "";
    inOrderString(s, root);
    return s;
}

std::string Dictionary::pre_string() const{
    std::string s = "";
    preOrderString(s, root);
    return s;
}

bool Dictionary::equals(const Dictionary& D) const {
    std::string s1 = to_string();
    std::string s2 = D.to_string();
    if (s1 == s2) {
        return true;
    }
    else {
        return false;
    }
}

//operator overrides-------------------------------------------------------------
std::ostream& operator<<( std::ostream& stream, Dictionary& D ) {
    return stream << D.Dictionary::to_string();
}

bool operator==( const Dictionary& A, const Dictionary& B ) {
    if (A.equals(B) == true) {
        return true;
    }
    return false;
}


Dictionary& Dictionary::operator=( const Dictionary& D ){
    clear();
    preOrderCopy(D.root, D.nil);
    num_pairs = D.num_pairs;
    return *this;
}
/*
int main() {
    Dictionary D;
    D.setValue("B", 1);
    D.setValue("A", 2);
    D.setValue("C", 3);
    D.setValue("D", 4);
    D.setValue("C", 99);

    Dictionary C;
    C.setValue("A", 2);
    C.setValue("D", 4);
    C.setValue("B", 1);
    C.setValue("C", 3);
    C.setValue("C", 99);
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
*/
