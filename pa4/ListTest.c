/************************************************
* Liam Murray, lijamurr
* CSE101 Spring 2023, Pa4
* ListTest.c
* Test Harness for the List ADT
************************************************/

#include "List.h"
#include <stdio.h>
#include <stdbool.h>

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
    moveFront(l);
    printf("cursor index 1: %d\n", index(l));
    set(l, ip6);
    printList(stdout, l, 0);
    printf("cursor index 2: %d\n", index(l));
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
    printf("cursor index 3: %d\n", index(l));
    moveFront(l);
    printf("cursor index 4: %d\n", index(l));
    moveBack(l);
    printf("cursor index 5: %d\n", index(l));
    movePrev(l);
    movePrev(l);
    movePrev(l);
    printf("cursor index 6: %d\n", index(l));
    moveNext(l);
    moveNext(l);
    printf("cursor index 7: %d\n", index(l));
    printf("list length: %d\n", length(l));
    printf("front of the list: %d\n", *(int *)front(l));
    printf("back of the list: %d\n", *(int *)back(l));

    freeList(&l);
    return 0;
}

