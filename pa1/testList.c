#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

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


    clear(l);
    printList(stdout, l);
    append(l, 2);
    prepend(l, 4);
    printList(stdout, l);
    moveFront(l);
    moveNext(l);
    printf("cursor index 1: %d\n", index(l));
    set(l, 2);
    printList(stdout, l);
    printf("cursor index 2: %d\n", index(l));
    set(l, 5);
    printList(stdout, l);
    printf("inserting elements before: \n");
    insertBefore(l, 22);
    printList(stdout, l);
    insertBefore(l, 44);
    printList(stdout, l);
    printf("inserting elements after: \n");
    insertAfter(l, 77);
    insertAfter(l, 99);
    printList(stdout, l);
    printf("removing front and back elements:\n");
    deleteFront(l);
    printList(stdout, l);
    deleteBack(l);
    printList(stdout, l);
    printf("removing cursor element:\n");
    delete(l);
    printList(stdout, l);
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
    printf("front of the list: %d\n", front(l));
    printf("back of the list: %d\n", back(l));
    List A = newList();
    prepend(A, 32);
    prepend(A, 64);
    append(A, 16);
    append(A, 8);
    printList(stdout, A);

    List B = newList();
    prepend(B, 3);
    prepend(B, 6);
    append(B, 16);
    append(B, 8);
    printList(stdout, B);

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
    freeList(&new_list);
    return 0;
}
