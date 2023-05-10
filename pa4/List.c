/************************************************
* Liam Murray, lijamurr
* CSE101 Spring 2023, Pa4
* List.c
* Functions and code for the List ADT
************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

//node structure definition

typedef struct NodeObj {
    struct NodeObj* left;
    void* data;
    struct NodeObj* right;
} NodeObj;

//this is saying that the type "Node" is now an alias for NodeObj Pointers
typedef NodeObj* Node;

//node contructor
Node node_create(void* value) {
    Node nd = (Node)malloc(sizeof(NodeObj));
    nd->data = value;
    nd->left = NULL;
    nd->right = NULL;
    return nd;
}

//node printer for DEBUG

void node_print(FILE* out, Node nd, int t) {
    if (nd == NULL) {
        fprintf(stderr, "ERROR: in node_print(): Node selected is set to NULL.\n");
        exit(1);
    }
    if (t == 0) {
        fprintf(out, "%d", *(int*)(nd->data));
    }
    if (t == 1) {
        fprintf(out, "%c", *(char*)(nd->data));
    }
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
    int vd = -1;
    l->length = 0;
    l->cursor = -1;
    l->head = node_create(&vd);
    l->tail = node_create(&vd);
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
void* front(List L){
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
void* back(List L) {
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
void* get(List L) {
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
void set(List L, void* x) {
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
void insertBefore(List L, void* x) {
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
void insertAfter(List L, void* x) {
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

void prepend(List L, void* x) {
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
    return;
}

// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, void* x){
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


//list printing
void printList(FILE* out, List L, int t) {
    if(L == NULL){
        fprintf(stderr, "ERROR: In list_print(): list input set to NULL.\n");
        exit(1);
    }
    Node current = L->head->right; 
    for (int i = 0; i < L->length; i++) {
        fprintf(out, " ");
        node_print(out, current, t);
        current = current->right;
    } 
    fprintf(out, "\n");
    return;
}
/*
int main(void){
    List l = newList();
    int i1 = 32;
    int i2 = 64;
    int i3 = 16;
    int i4 = 8;
    int i5 = 4;
    int i6 = 2;
    int i7 = 5;

    int * ip1 = &i1;
    int * ip2 = &i2;
    int * ip3 = &i3;
    int * ip4 = &i4;
    int * ip5 = &i5;
    int * ip6 = &i6;
    int * ip7 = &i7;

    prepend(l, ip1);
    prepend(l, ip2);
    append(l, ip3);
    append(l, ip4);
    printList(stdout, l, 0);

    clear(l);
    printList(stdout, l, 0);
    append(l, ip6);
    prepend(l, ip5);
    printList(stdout, l, 0);
    l->cursor = 1;
    printf("cursor index 1: %d\n", L_index(l));
    set(l, ip6);
    printList(stdout, l, 0);
    printf("cursor index 2: %d\n", L_index(l));
    set(l, ip7);
    printList(stdout, l, 0);
    printf("inserting elements before: \n");
    insertBefore(l, ip1);
    printList(stdout, l, 0);
    insertBefore(l, ip2);
    printList(stdout, l, 0);
    printf("inserting elements after: \n");
    insertAfter(l, ip3);
    insertAfter(l, ip4);
    printList(stdout, l, 0);
    printf("removing front and back elements:\n");
    deleteFront(l);
    printList(stdout, l, 0);
    deleteBack(l);
    printList(stdout, l, 0);
    printf("removing cursor element:\n");
    delete(l);
    printList(stdout, l, 0);
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
    printf("front of the list: %d\n", *(int *)front(l));
    printf("back of the list: %d\n", *(int *)back(l));

    freeList(&l);
    return 0;
}
*/
