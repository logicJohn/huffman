// CSCI 2530
// Assignment: 8
// Author:     Johnnie Hernandez
// File:       trace.cpp
// Tab stops:  8

/*
Trace.cpp holds a list of functions used by huffman.cpp and unhuffman.cpp.
Functions under trace will only display information if the user has enabled
trace by using the argument "-t" 
Example ./huffman -t file1.txt file2.txt
*/

#include <cstdio>
#include <cstring>
#include <cctype>
#include "trace.h"
#include "tree.h"

#include <cstdio>
using namespace std;

int traceEnabled = 0;

void printTree(Tree head);

/***********************************************
 *              printDescription               *
 ***********************************************
 * Print the character value of integer i.     *
 * If char i has no print value print the      *
 * symbol at i or "\i".                        *
 ***********************************************/
void printDescription(int i) {
    if (i == 32) {
        printf("SPACE");
    }
    else if (i == 10) {
        printf("\\n");
    }
    else if (isprint(i)) {
        printf("%c", i);
    }
    else {
        printf("\\%d", i);
    }
}

/***********************************************
 *              printArray                     *
 ***********************************************
 * If traceEnabled is equal to true then       *
 * search array a fromt 0 to length  for       *
 * any non Null values and print the values    *
 * as chracters to the screen                  *
 ***********************************************/
 
void printArray(int* a, int length) {
    if (traceEnabled == 0) {
        return;
    }
    printf("\n The character Frequenceis are:\n");
    int counter=0;
    for (int i = 0; i < length; i++) {
        if (a[i] > 0) {
            printf(" ");
            printDescription( i);
            printf(" = %i " , a[i]);
            counter++;
            if (counter % 3 == 0) {
                
                printf("\n");
                counter = 0;
            }
        }
    }
    printf("\n\n");
}

/***********************************************
 *              printTree                      *
 ***********************************************
 * Print all characters in the tree head.      *
 ***********************************************/

void printTree(Tree head) {
    if (head->kind == NodeKind(1)) {
        printTree(head->left);
        printTree(head->right);
    } 
    else if (head->kind == NodeKind(0)) {
        printf(" Char = ");
        unsigned char temp = head->ch;
        printDescription(temp);
        printf(" \n");
    }
}

/***********************************************
 *              tracePrintTree                 *
 ***********************************************
 * Check to see if traceing is enabled.        *
 * If it is then print the tree head.          *
 ***********************************************/
 
void tracePrintTree(Tree head) {
    if (traceEnabled == 0) {
        return;
    }
    printTree(head);
    tracePrintTreeRoute(head, "");
}

/***********************************************
 *              printCharArray                 *
 ***********************************************
 * Check to see if trace is enabled.           *
 * If trace is enabled print all strings in    *
 * the array Code from 0 to length.            *
 ***********************************************/

void printCharArray(const char* Code[], int length) {
    if (traceEnabled == 0) {
        return;
    }    
    for (int i = 0; i<length; i++) {
        
        if (strcmp(Code[i], "\0") != 0) {
            printDescription(i);
            printf("= %s\n",  Code[i]);
        }
    }
    
}

/***********************************************
 *              checkTrace                     *
 ***********************************************
 * looks through the the argv to see if "-t"   *
 * is included.  If it enabled tracing.        *
 ***********************************************/
 
bool checkTrace(int argc, char* argv[]) {
    if (argc > 3) {
        if ( strcmp(argv[1], "-t") == 0 ) {
            traceEnabled = 1;
            return true;
        } else {
            printf("\n usage: huffman [-t] \n");
            return false;
        }
    }
    else return true;
}

/***********************************************
 *              tracePrintTreeRoute            *
 ***********************************************
 * Prints the location of each chracter in     *
 * The tree as a path of 0's and 1's.          *
 * 0's mean move right and 1's mean move left  *
 ***********************************************/
 
void tracePrintTreeRoute(Tree head, const char* path) {
    printf("line  165  \n");
    if(head -> kind == NodeKind(0)) {
        printf("line  167  \n");
        printf("%s =", path );
        printf(" %c \n", head->ch);
        printf("line  170  \n");
    }
    else if (head->kind == NodeKind(1)) {
        printf("line  173  \n");
        char* left = new char[strlen(path)+1];
        left = strcpy(left,path);
        left = strcat(left, "0");
        tracePrintTreeRoute(head->left, left);
        printf("line  178  \n");
        
        printf("line  179  \n");
        char* right = new char[strlen(path)+1];
        right = strcpy(right,path);
        right = strcat(right,"1");
        tracePrintTreeRoute(head->right, right);
        printf("line  184  \n");
    }
}
