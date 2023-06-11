//-----------------------------------------------------------------------------
// Liam Murray, lijamurr
// Pa*
// Dictionary.cpp
// Source Code for Dictionary ADT 
//---------------------------------------------------------------------

#include <iostream>
#include <string>
#include "Dictionary.h"

#define RED 1
#define BLACK 0

using namespace std;

// Node Methods and constructors
Dictionary::Node::Node(keyType k, valType v){
    key = k;
    val = v;
    color = BLACK; //0 = blk, 1 = redx
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

// RBT Helper Functions (Optional) -----------------------------------------
   
   // LeftRotate()
void Dictionary::LeftRotate(Node* N) {
    //printf("Left Rotate\n");
    Node * Y = N->right;
    N->right = Y->left;
    if (Y->left != nil) {
        Y->left->parent = N;
    }
    Y->parent = N->parent;
    if (N->parent == nil) {
        root = Y;
    }
    else if(N == N->parent->left) {
        N->parent->left = Y;
    }
    else {
        N->parent->right = Y;
    }
    Y->left = N;
    N->parent = Y;
}

   // RightRotate()
void Dictionary::RightRotate(Node* N) {
    //printf("Right Rotate\n");
    Node * Y = N->left;
    N->left = Y->right;
    if (Y->right != nil) {
        Y->right->parent = N;
    }
    Y->parent = N->parent;
    if (N->parent == nil) {
        root = Y;
    }
    else if(N == N->parent->right) {
        N->parent->right = Y;
    }
    else {
        N->parent->left = Y;
    }
    Y->right = N;
    N->parent = Y;
}
   // RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* N) {
    //printf("Insert Fix up\n");
    //cout << "Insert Fix on " << N->key << ": Parent = " << N->parent->key << endl;
    while (N->parent->color == RED) {
        if (N->parent == N->parent->parent->left) {
            Node * y = N->parent->parent->right;
            if (y->color == RED) {
                //printf("Case 1\n");
                N->parent->color = BLACK;
                y->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            }
            else {
                if (N == N->parent->right) {
                    //printf("Case 2\n");
                    N = N->parent;
                    LeftRotate(N);
                }
                //printf("Case 3\n");
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                //cout << "Calling RR on " << N->parent->parent->key << endl;
                RightRotate(N->parent->parent);
            }
        }
        else {
            Node * y = N->parent->parent->left;
            if (y->color ==  RED) {
                //printf("Case 4\n");
                N->parent->color = BLACK;
                y->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            }
            else {
                if (N == N->parent->left) {
                    N = N->parent;
                    //cout << "1 Calling RR on " << N->key << endl;
                    RightRotate(N);
                    //printf("Case 5\n");
                }
                //printf("Case 6\n");
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                LeftRotate(N->parent->parent);
            }
        }
    }
    root->color = BLACK;
    return;
}

   // RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v) {
    //printf("Transplant\n");
    if (u->parent == nil){
        //cout << "making " << v->key << " root2" << endl;
        root = v;
    }
    else if (u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* N) {
    //cout << "Delete Fix on: " << N->key << endl;
    Node * w;
    while (N != root && N->color == BLACK) {
        if (N == N->parent->left) {
            w = N->parent->right;
            if (w->color == RED) {
                w->color = BLACK;                        // case 1
                N->parent->color = RED;                   // case 1
                LeftRotate(N->parent);                // case 1
                w = N->parent->right;     
            }                
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;                          // case 2
                N = N->parent;            
            }             
            else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;                // case 3
                    w->color = RED;                       // case 3
                    //cout << " 2 Calling RR on " << w->key << endl;
                    RightRotate(w);                   // case 3
                    w = N->parent->right; 
                }                
                w->color = N->parent->color;               // case 4
                N->parent->color = BLACK;                 // case 4
                w->right->color = BLACK;                  // case 4
                LeftRotate(N->parent);                // case 4
                N = root;
            }
        }                           
        else {
            w = N->parent->left;
            if (w->color == RED) {
                w->color = BLACK;                        // case 5
                N->parent->color = RED;                   // case 5
                //cout << " 3 Calling RR on " << N->parent->key << endl;
                RightRotate(N->parent);               // case 5
                w = N->parent->left;    
            }                  
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;                          // case 6
                N = N->parent;      
            }                    
            else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;               // case 7
                    w->color = RED;                       // case 7
                    LeftRotate(w);                    // case 7
                    w = N->parent->left; 
                }                  
                w->color = N->parent->color;               // case 8
                N->parent->color = BLACK;                 // case 8
                w->left->color = BLACK;                   // case 8
                //cout << " 4 Calling RR on " << N->parent->key << endl;
                RightRotate(N->parent);               // case 8
                N = root; 
            }
        }                            
    }
    N->color = BLACK;
}

// RB_Delete()
void Dictionary::RB_Delete(Node* N) {
    //printf("Delete\n");
    Node * y = N;
    Node * x;
    int yog = y->color;
    if (N->left == nil){
        x = N->right;
        RB_Transplant(N, N->right);
    }
    else if (N->right == nil) {
        x = N->left;
        RB_Transplant(N, N->left);
    }
    else {
        y = findMin(N->right);
        yog = y->color;
        x = y->right;
        if (y->parent == N) {
            x->parent = y;
        }
        else {
            RB_Transplant(y, y->right);
            y->right = N->right;
            y->right->parent = y;
        }
        RB_Transplant(N, y);
        y->left = N->left;
        y->left->parent = y;
        y->color = N->color;
    }
    delete N;
    if (yog == BLACK) {
        RB_DeleteFixUp(x);
    }
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
    if (R->color == RED){
        s += " (RED)";
    }
    s += "\n";
    preOrderString(s, R->left);
    preOrderString(s, R->right);
    return;
}

void Dictionary::BST_insert(Dictionary::Node* M) {
    Node * z = new Node(M->key, M->val);
    z->color = M->color;
    Node * y = nil;
    Node * x = root;
    while (x != nil) {
        y = x;
        if (z->key == x->key) {
            return;
        }
        else if (z->key < x->key) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == nil) {
        root = z;
    }
    else if (z->key < y->key) {
        y->left = z;
    }
    else {
        y->right = z;
    }
    z->left = nil;
    z->right = nil;
    return;
}


void Dictionary::preOrderCopy(Node* R, Node* N) {
    if(R == N) {
        return;
    }
    BST_insert(R);
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
    Node * z = new Node(k, v);
    Node * y = nil;
    Node * x = root;
    while (x != nil) {
        y = x;
        if (x->key == k) {
            delete z;
            x->val = v;
            return;
        }
        else if (z->key < x->key) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == nil) {
        root = z;
        z->color = BLACK;
    }
    else if (z->key < y->key) {
        y->left = z;
    }
    else {
        y->right = z;
    }
    z->left = nil;
    z->right = nil;
    z->color = RED;
    num_pairs += 1;
    RB_InsertFixUp(z);
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
    Node * n = search(root, k);
    if (n == nil) {
        throw std::logic_error("ERROR: in remove(); key is not present\n");
    }
    if (hasCurrent() && currentKey() == k){
        current = nil;
    }
    RB_Delete(n);
    num_pairs -= 1;
    return;
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

}
*/
