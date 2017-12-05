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



int main(int argc, char** argv)
{
    if (!checkTrace(argc, argv)) {
        return 1;
    }

    const char* A;
    const char* B;
    A = argv[argc-2];    
    B = argv[argc-1];
    BFILE* f = openBinaryFileRead(A);
    FILE* outFile = fopen(B, "w");
    Tree huffmanTree;

    huffmanTree = binaryToTree(f,  readBit(f));
    tracePrintTree(huffmanTree);
    writeBinaryText(huffmanTree, f, outFile);
    
    closeBinaryFileRead(f);
    fclose(outFile);
    
    delete huffmanTree;
    return 0;
}

/***********************************************
 *              binaryToTree                   *
 ***********************************************
 * Returns a tree after reading f until a full *
 * and creating a the tree based off of x.     *
 ***********************************************/
 
Tree binaryToTree(BFILE* f,  int x) {
    if (x == 1) {
        Tree head = new Node(readByte(f));
        return head;
    } 
    if (x == 0) {
        Tree head = new Node(binaryToTree(f, readBit(f)) , binaryToTree(f, readBit(f)));
        return head;
    }
    
}

/***********************************************
 *              writeBinaryText                *
 ***********************************************
 * Writes the file write by reading a set of   *
 * characters in read and finding the matching *
 * location in head.                           *
 ***********************************************/
 
void writeBinaryText(Tree head, BFILE* read, FILE* write) {
    int temp = readBit(read);
    Tree tempHead = head;
    while(temp != EOF) {
        tempHead = head;
        putc(searchTree(tempHead, read, temp), write);
        temp = readBit(read);
    }
}

/***********************************************
 *              searchTree                     *
 ***********************************************
 * Traverse the tree head by reading a         *
 * set of paths in read and current location   *
 * temp.  Returns the tree value when found.   *
 ***********************************************/
 
char searchTree( Tree head, BFILE* read, int temp) {
    if (head->kind == NodeKind(1)) {
        if (temp == 0) {
            if(head->left->kind == 0) {
                return head->left->ch;
            }
            return searchTree(head->left, read, readBit(read));
        }
        else if (temp == 1) {
            if(head->right->kind == 0) {
                return head->right->ch;
            }
            return searchTree(head->right, read, readBit(read));
        }
    }
}