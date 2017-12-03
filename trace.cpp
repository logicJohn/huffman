// CSCI 2530
// Assignment: 8
// Author:     Johnnie Hernandez
// File:       trace.cpp
// Tab stops:  8

// Program 


#include <cstdio>
#include <cstring>
#include <cctype>
#include "trace.h"
#include "tree.h"

#include <cstdio>
using namespace std;

void printTree(Tree head);

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

void tracePrintTree(Tree head){
    if (traceEnabled == 0){
        return;
    }
    printTree(head);
}









