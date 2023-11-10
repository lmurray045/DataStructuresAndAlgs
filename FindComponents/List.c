/************************************************
 * * Liam Murray, lijamurr
 * * CSE101 Spring 2023, Pa1
 * * List.c
 * * Functions and Code for list ADT
 * ************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

//node structure definition

typedef struct NodeObj {
    struct NodeObj* left;
    uint64_t data;
    struct NodeObj* right;
} NodeObj;

//this is saying that the type "Node" is now an alias for NodeObj Pointers
typedef NodeObj* Node;

//node contructor
Node node_create(uint32_t value) {
    Node nd = (Node)malloc(sizeof(NodeObj));
    nd->data = value;
    nd->left = NULL;
    nd->right = NULL;
    return nd;
}

//node printer for DEBUG

void node_print(FILE* out, Node nd) {
    if (nd == NULL) {
        fprintf(stderr, "ERROR: in node_print(): Node selected is set to NULL.\n");
        exit(1);
    }
    fprintf(out, "%lu", nd->data);
    return;
}

//node delete function 
void node_delete(Node *n) {
    if(n != NULL && *n != NULL){
	free(*n);
    	*n = NULL;
    }
    return;
}

//list structure definition

typedef struct ListObj {
    uint32_t length;
    uint32_t cursor;
    Node head; //the front of the list sentinel Node
    Node tail; //the back of the list sentinel Node
} ListObj;

//this is aliasing the type "List" to ListObj
typedef ListObj* List;

//list constructor

List newList(void) {
    List l = (List)malloc(sizeof(ListObj));
    if (l == NULL) {
        fprintf(stderr, "ERROR: new list is NULL: Malloc failed.\n");
        exit(1);
    }
    l->length = 0;
    l->cursor = -1;
    l->head = node_create(-1);
    l->tail = node_create(-1);
    l->head->right = l->tail;
    l->tail->left = l->head;
    return l;
}

//list deconstructor

void freeList(List* pL){
    if (pL == NULL) {
        fprintf(stderr, "ERROR: In freeList()- passed pointer is NULL.\n");
        exit(1);
    }
    Node first = (*pL)->head; 
    Node next = (*pL)->head->right;
    for (int i = 0; i < (*pL)->length; i++) {
        first = next;
        next = next->right;
	node_delete(&first);
    }
    node_delete(&((*pL)->head));
    node_delete(&((*pL)->tail));
    free(*pL);
    *pL = NULL;
    return;
}

//Access Functions-----------------------------------------------------

// Returns the number of elements in L.
int length(List L){
    if (L == NULL) {
        printf("ERROR: in Length(): list selected is set to NULL.\n");
        exit(1);
    }
    return L->length;
}

// Returns index of cursor element if defined, -1 otherwise.
int index(List L) {
    if (L == NULL) {
        printf("ERROR: in index(): list selected is set to NULL.\n");
        exit(1);
    }
    return L->cursor;
}

// Returns front element of L. Pre: length()>0
int front(List L){
    if (L == NULL) {
        printf("ERROR: in front(): list selected is set to NULL.\n");
        exit(1);
    }
    if (L->length <= 0) {
        fprintf(stderr, "ERROR: in front(): List length is zero");
        exit(1);    
    }
    return L->head->right->data;
}

// Returns back element of L. Pre: length()>0
int back(List L) {
    if (L == NULL) {
        printf("ERROR: in back(): list selected is set to NULL.\n");
        exit(1);
    }
    if (L->length <= 0) {
        fprintf(stderr, "ERROR: in back(): List length is zero");
        exit(1);    
    }
    return L->tail->left->data;
}

// Returns cursor element of L. Pre: length()>0, index()>=0
int get(List L) {
    if (L == NULL) {
        printf("ERROR: in get(): list selected is set to NULL.\n");
        exit(1);
    }
    if (L->cursor < 0){
        fprintf(stderr, "ERROR: in get(): List cursor is undefined.\n");
        exit(1);
    }
    if (L->length <= 0) {
        fprintf(stderr, "ERROR: in get(): List length is zero.\n");
        exit(1);    
    }
    Node next = L->head->right;
    for (int i = 0; i < L->cursor; i++) {
        next = next->right;
    }
    return next->data;
}

// Returns true iff Lists A and B are in same
// state, and returns false otherwise.
bool equals(List A, List B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "ERROR: in equals(): either A or B are set to NULL.\n");
        exit(1);
    }
    if (A->length != B->length) {
        return false;
    }
    Node A_next = A->head->right;
    Node B_next = B->head->right;
    for (int i = 0; i < A->length; i++){
        if (A_next->data != B_next->data) {
            return false;
        }
        A_next = A_next->right;
        B_next = B_next->right;
    }
    return true;
}

//Maniplation Functions----------------------------------------------------------

// Resets L to its original empty state.
void clear(List L) {
    if (L == NULL) {
        fprintf(stderr, "ERROR: in clear(): List argument is NULL.\n");
        exit(1);
    }
    Node start = L->head;
    Node next = L->head->right;
    for (int i = 0; i < L->length; i++) {
        start = next;
        next = next->right;
        node_delete(&start);
    }
    L->head->right = L->tail;
    L->tail->left = L->head;
    L->length = 0;
    L->cursor = -1;
    return;
}

// Overwrites the cursor element’s data with x.
// Pre: length()>0, index()>=0
void set(List L, int x) {
    if (L == NULL) {
        fprintf(stderr, "ERROR: in set(): List argument is NULL.\n");
        exit(1);
    }
    if (L->length == 0) {
        fprintf(stderr, "ERROR: in clear(): List Length is zero.\n");
        exit(1);
    }
    if (index(L) < 0) {
        fprintf(stderr, "ERROR: in set(): index is less than zero.\n");
        exit(1);
    }
    Node next = L->head;
    for (int i = 0; i <= L->cursor; i++) {
        next = next->right;
    }
    next->data = x;
    return;
}

// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L) {
    if (L == NULL) {
        fprintf(stderr, "ERROR: in moveFront(): List argument is NULL.\n");
        exit(1);
    }
    if (L->length == 0) {
        return;
    }
    L->cursor = 0;
}

// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L) {
    if (L == NULL) {
        fprintf(stderr, "ERROR: in moveBack(): List argument is NULL.\n");
        exit(1);
    }
    if (L->length == 0) {
        return;
    }
    L->cursor = (L->length) - 1;
    return;
}

// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L) {
    if (L == NULL) {
        fprintf(stderr, "ERROR: in movePrev(): List argument is NULL.\n");
        exit(1);
    }
    if (L->length == 0) {
        return;
    }
    if (L->cursor == -1) {
        return;
    }
    L->cursor -= 1;
    return;
}

// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L) {
    if (L == NULL) {
        fprintf(stderr, "ERROR: in moveNext(): List argument is NULL.\n");
        exit(1);
    }
    if (L->length == 0) {
        return;
    }
    if (L->cursor == -1) {
        return;
    }
    if (L->cursor == (L->length) - 1) {
        L->cursor = -1;
        return;
    }
    L->cursor += 1;
    return;
}

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int x) {
    if (L == NULL) {
        fprintf(stderr, "ERROR: in insertBefore(): List argument is NULL.\n");
        exit(1);
    }
    if (L->length <= 0) {
        fprintf(stderr, "ERROR: in insertBefore(): Length is less than zero.\n");
        exit(1);
    }
    if (L->cursor < 0) {
        fprintf(stderr, "ERROR: in insertBefore(): cursor is NULL.\n");
        exit(1);
    }
    Node next = L->head;
    for (int i = 0; i <= L->cursor; i++) {
        next = next->right;
    }
    Node N = node_create(x);
    next->left->right = N;
    N->left = next->left;
    next->left = N;
    N->right = next;
    L->length += 1;
    L->cursor += 1;
    return;
}

// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int x) {
    if (L == NULL) {
        fprintf(stderr, "ERROR: in insertAfter(): List argument is NULL.\n");
        exit(1);
    }
    if (L->length <= 0) {
        fprintf(stderr, "ERROR: in insertAfter(): Length is less than zero.\n");
        exit(1);
    }
    if (L->cursor < 0) {
        fprintf(stderr, "ERROR: in insertAfter(): cursor is NULL.\n");
        exit(1);
    }
    Node next = L->head;
    for (int i = 0; i <= L->cursor; i++) {
        next = next->right;
    }
    Node N = node_create(x);
    next->right->left = N;
    N->right = next->right;
    next->right = N;
    N->left = next;
    L->length += 1;
    return;
}

// Delete the front element. Pre: length()>0
void deleteFront(List L) {
    if (L == NULL) {
        fprintf(stderr, "ERROR: in deleteFront(): List argument is NULL.\n");
        exit(1);
    }
    if (L->length <= 0) {
        fprintf(stderr, "ERROR: in deleteFront(): Length is less than zero.\n");
        exit(1);
    }
    Node deleter = L->head->right;
    L->head->right = L->head->right->right;
    L->head->right->left = L->head;
    node_delete(&(deleter));
    L->length -= 1;
    L->cursor -= 1;
    return;
}

// Delete the back element. Pre: length()>0
void deleteBack(List L) {
    if (L == NULL) {
        fprintf(stderr, "ERROR: in deleteBack(): List argument is NULL.\n");
        exit(1);
    }
    if (L->length <= 0) {
        fprintf(stderr, "ERROR: in deleteBack(): Length is less than zero.\n");
        exit(1);
    }
    Node deleter = L->tail->left;
    L->tail->left = L->tail->left->left;
    L->tail->left->right = L->tail;
    node_delete(&(deleter));
    if (L->cursor == L->length - 1) {
         L->cursor = -1;
    }
    L->length -= 1;
    return;
}

// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L) {
    if (L == NULL) {
        fprintf(stderr, "ERROR: in delete(): List argument is NULL.\n");
        exit(1);
    }
    if (L->length <= 0) {
        fprintf(stderr, "ERROR: in delete(): Length is less than zero.\n");
        exit(1);
    }
    if (L->cursor < 0) {
        fprintf(stderr, "ERROR: in delete(): cursor is NULL.\n");
        exit(1);
    }
    Node next = L->head;
    for (int i = 0; i <= L->cursor; i++) {
        next = next->right;
    }
    next->left->right = next->right;
    next->right->left = next->left;
    node_delete(&next);
    L->cursor = -1;
    L->length -= 1;
    return;
}

//list prepend: Insert new element into L. If L is non-empty,
// insertion takes place before front element. Pre: None

void prepend(List L, int x) {
    if (L == NULL) {
        fprintf(stderr, "ERROR: In prepend(): list input set to NULL.\n");
        exit(1);
    }
    Node n = node_create(x);
    n->right = L->head->right;
    L->head->right->left = n;
    L->head->right = n;
    n->left = L->head;
    L->length += 1;
    L->cursor += 1;
    return;
}

// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, int x){
    if (L == NULL) {
        fprintf(stderr, "ERROR: In append(): list input set to NULL.\n");
        exit(1);
    }
    Node n = node_create(x);
    n->left = L->tail->left;
    L->tail->left->right = n;
    L->tail->left = n;
    n->right = L->tail;
    L->length += 1;
    return;
}

//list copy

List copyList(List L) {
    if (L == NULL) {
        fprintf(stderr, "ERROR in copyList(): List input is NULL.\n");
        exit(1);
    }
    List new_list = newList();
    Node L_next = L->head->right; 
    for (int i = 0; i < L->length; i++) {
        append(new_list, L_next->data);
        L_next = L_next->right;
    }
    new_list->length = L->length;
    return new_list;
}

//list printing
void printList(FILE* out, List L) {
    if(L == NULL){
        fprintf(stderr, "ERROR: In list_print(): list input set to NULL.\n");
        exit(1);
    }
    Node current = L->head->right; 
    for (int i = 0; i < L->length; i++) {
        fprintf(out, " ");
        node_print(out, current);
        current = current->right;
    } 
    fprintf(out, "\n");
    return;
}
/*
int main(void){
    List l = newList();
    prepend(l, 32);
    prepend(l, 64);
    append(l, 16);
    append(l, 8);
    printList(stdout, l);

    List new_list = copyList(l);
    printf("Old List: ");
    printList(stdout, l);
    printf("New List: ");
    printList(stdout, new_list);
    return 0;

    clear(l);
    list_print(l);
    append(l, 2);
    prepend(l, 4);
    list_print(l);
    l->cursor = 1;
    printf("cursor index 1: %d\n", L_index(l));
    set(l, 2);
    list_print(l);
    printf("cursor index 2: %d\n", L_index(l));
    set(l, 5);
    list_print(l);
    printf("inserting elements before: \n");
    insertBefore(l, 22);
    list_print(l);
    insertBefore(l, 44);
    list_print(l);
    printf("inserting elements after: \n");
    insertAfter(l, 77);
    insertAfter(l, 99);
    list_print(l);
    printf("removing front and back elements:\n");
    deleteFront(l);
    list_print(l);
    deleteBack(l);
    list_print(l);
    printf("removing cursor element:\n");
    delete(l);
    list_print(l);
    printf("cursor index 3: %d\n", L_index(l));
    moveFront(l);
    printf("cursor index 4: %d\n", L_index(l));
    moveBack(l);
    printf("cursor index 5: %d\n", L_index(l));
    movePrev(l);
    movePrev(l);
    movePrev(l);
    printf("cursor index 6: %d\n", L_index(l));
    moveNext(l);
    moveNext(l);
    printf("cursor index 7: %d\n", L_index(l));
    printf("list length: %d\n", length(l));
    printf("front of the list: %d\n", front(l));
    printf("back of the list: %d\n", back(l));
    List A = newList();
    prepend(A, 32);
    prepend(A, 64);
    append(A, 16);
    append(A, 8);
    list_print(A);

    List B = newList();
    prepend(B, 3);
    prepend(B, 6);
    append(B, 16);
    append(B, 8);
    list_print(B);

    if (equals(A, l)){
        printf("True \n");
    }
    else {
        printf("False \n");
    }

    if (equals(A, B)){
        printf("True \n");
    }
    else {
        printf("False \n");
    }

    freeList(&l);
    freeList(&A);
    freeList(&B);
    return 0;
}
*/

