 // CSCI 2530
// Assignment: 8
// Author:     Johnnie Hernandez
// File:       unhuffman.cpp
// Tab stops:  8

// **Say what this program does here.  (replace this comment)**



#include <cstdio>
#include <cstring>
#include <cctype>
#include "trace.h"
#include "tree.h"
#include "pqueue.h"
#include "binary.h"

using namespace std;

Tree binaryToTree(BFILE* f, int x);

int traceEnabled = 0;

int main(int argc, char** argv)
{
    if (argc > 2) {
        if ( strcmp(argv[1], "-t") == 0 ) {
            traceEnabled = 1;
        } else {
            printf("\n usage: huffman [-t] \n");
            return 1;
        }
    }

    const char* A;
    A = argv[argc-1];    
    BFILE* f = openBinaryFileRead(A);
    Tree huffmanTree;

    int temp = readBit(f);
    if( temp != EOF){
        huffmanTree = binaryToTree(f,  temp);
    }

    tracePrintTree(huffmanTree);

    return 0;
}


Tree binaryToTree(BFILE* f,  int x){
    if (x == 1){
        Tree head = new Node(readByte(f));
        return head;
    } 
    if (x == 0){
        Tree head = new Node(binaryToTree(f, readBit(f)) , binaryToTree(f, readBit(f)));
        return head;
    }
    if (x == EOF){
        return NULL;
    }
}