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

void printTree(Tree head);

/***********************************************
 *              printDescription               *
 ***********************************************
 * Print the character value of integer i.     *
 * If char i has no print value print the      *
 * symbol at i or "\i".                        *
 ***********************************************/
void printDescription(int i){
    if (i == 32){
        printf("SPACE");
    }
    else if (i == 10){
        printf("\\n");
    }
    else if (isprint(i)){
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
 
void printArray(int* a, int length){
    if (traceEnabled == 0){
        return;
    }
    int counter=0;
    for (int i = 0; i < length; i++){
        if (a[i] > 0){
            printf(" ");
            printDescription( i);
            printf(" = %i " , a[i]);
            counter++;
            if (counter % 3 == 0){
                
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

void printTree(Tree head){
    if (head->kind == NodeKind(1)){
        if (head->left != NULL){
            printTree(head->left);
        }
        if (head->right != NULL){
            printTree(head->right);
        }
    } 
    if (head->kind == NodeKind(0)){
        printf(" Char = ");
        printDescription(head->ch);
        printf(" \n");
    }
}

/***********************************************
 *              tracePrintTree                 *
 ***********************************************
 * Check to see if traceing is enabled.        *
 * If it is then print the tree head.          *
 ***********************************************/
 
void tracePrintTree(Tree head){
    if (traceEnabled == 0){
        return;
    }
    printTree(head);
}

/***********************************************
 *              printCharArray                 *
 ***********************************************
 * Check to see if trace is enabled.           *
 * If trace is enabled print all strings in    *
 * the array Code from 0 to length.            *
 ***********************************************/

void printCharArray(const char* Code[], int length){
    if (traceEnabled == 0){
        return;
    }    
    for (int i = 0; i<length; i++){
        
        if (strcmp(Code[i], "\0") != 0){
            printDescription(i);
            printf("= %s\n",  Code[i]);
        }
    }
    
}
