#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "ERROR: Invalid arguments passed. Please refer to guide for usage: \n\nRUN PROGRAM AS FOLLOWS: Lex <input file> <output file>\n");
        exit(1);
    }
    int CHAR_NUM = 1000;
    FILE * infile = fopen(argv[1], "r");
    int counter = 0;
    char buf [CHAR_NUM];
    char * pbuf = buf;
    while (fgets(pbuf, CHAR_NUM, infile) != NULL) {
        counter += 1;
    }
    char ** str_arr = (char **)calloc(counter, sizeof(char *));
    for (int i = 0; i < counter; i++){
        str_arr[i] = calloc(CHAR_NUM, sizeof(char));
    }
    rewind(infile);
    int j = 0; 
    while (fgets(str_arr[j], CHAR_NUM, infile) != NULL) {
        j++;
    }
    List l = newList();
    for (int i = 0; i < counter; i++) {
        if (length(l) == 0) {
            prepend(l, i);
            continue;
        }
        moveFront(l);
        for (int j = 0; j < length(l); j++) {
            if (strcmp(str_arr[i], str_arr[get(l)]) < 0) {
                insertBefore(l, i);
                break;
            }
            else if (strcmp(str_arr[i], str_arr[get(l)]) == 0) {
                insertAfter(l, i);
                break;
            }
            else {
                moveNext(l);
                if (index(l) < 0) {
                    append(l, i);
                    break;
                }          
                continue;
            }
        }
    }
    FILE * outfile = fopen(argv[2], "w");
    moveFront(l);
    while (index(l) >= 0) {
        int x = get(l);
        fprintf(outfile, "%s", str_arr[x]);
       /* if (x == counter - 1) {
            if (index(l) != length(l) - 1){
                fprintf(outfile, "\n");
            }
        }
	*/
        moveNext(l);
    }
    fclose(infile);
    fclose(outfile);
    //for (int i = 0; i < counter; i++) {
      //  free(&(str_arr[i]));
    //}
    return 0;
}
