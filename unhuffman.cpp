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
void writeBinaryText(Tree head, BFILE* read, FILE* write);
char searchTree(Tree head, BFILE* read, int temp);

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
    const char* B;
    A = argv[argc-2];    
    B = argv[argc-1];
    BFILE* f = openBinaryFileRead(A);
    FILE* outFile = fopen(B, "w");
    Tree huffmanTree;

    int temp = readBit(f);
    if( temp != EOF){
        huffmanTree = binaryToTree(f,  temp);
    }

    tracePrintTree(huffmanTree);
    
    writeBinaryText(huffmanTree, f, outFile);
    
    closeBinaryFileRead(f);
    fclose(outFile);
    

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
    
}

void writeBinaryText(Tree head, BFILE* read, FILE* write){
    int temp = readBit(read);
    Tree tempHead;
  
    while(temp != EOF){
        tempHead = head;
        putc(searchTree(tempHead, read, temp), write);
        temp = readBit(read);
        
    }
            
}

char searchTree( Tree head, BFILE* read, int temp){
        
    if (head->kind == NodeKind(1)){
        if (temp == 0){
            return searchTree(head->left, read, readBit(read));
        }
        if (temp == 1){
            return searchTree(head->right, read, readBit(read));
        }
    }
    else if (head->kind == NodeKind(0)){
        
        printf(" Char = ");
        printDescription(head->ch);
        printf(" \n");
        return head->ch;
    }

}