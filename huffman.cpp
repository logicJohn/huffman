// CSCI 2530
// Assignment: 8
// Author:     Johnnie Hernandez
// File:       huffman.cpp
// Tab stops:  8

// Program 


#include <cstdio>
#include <cstring>
#include <cctype>
#include "trace.h"
#include "tree.h"
#include "pqueue.h"
#include "binary.h"

using namespace std;

bool freqCount(int* a, int length, const char* file);
void setArray(int* a, int length);
FILE* openInFile(const char* fileNmae);
FILE* openOutFile(const char* fileName);
Tree buildHuffmanTree( int* freqArray, int length);
void buildPriorityQueue(PriorityQueue& q, int* freqArray, int length);
void buildCode(Tree q, const char* Code[], int length);
void setCharArray(const char* Code[], int length);
void fillArray(Tree head,const char* Code[],const char* prefix);
void writeTreeBinary(BFILE* f, Tree head);
void writeCompressed( const char* readFile, BFILE* binaryFile, const char* Code[]);
void writeCodeBinary(BFILE* binaryFile, const char* code);


int main(int argc, char* argv[]) {
    
    if (!checkTrace(argc, argv)) {
        return 1;
    }
    
   
    int arrayLength = 256;
    int* freqArray;
    const char* codeBlock[arrayLength];
    freqArray = new int[arrayLength];
    const char* A;
    const char* B;
    A = argv[argc-2];
    B = argv[argc-1];
    Tree huffmanTree;
    
    
    if (!freqCount(freqArray, arrayLength, A)) {
        printf(" File read returned NULL\n");
        return 1;
    }
    printArray(freqArray, arrayLength);
    
    huffmanTree = buildHuffmanTree(freqArray, arrayLength);
    printf("test");
    tracePrintTree(huffmanTree);
    printf("broke");
    buildCode(huffmanTree, codeBlock, arrayLength);
    
    BFILE* binaryFile = openBinaryFileWrite(B);
    writeTreeBinary(binaryFile, huffmanTree);
    writeCompressed(A, binaryFile, codeBlock);
    closeBinaryFileWrite(binaryFile);

    delete huffmanTree;
    delete[] freqArray;
    return 0;
}   

/***********************************************
 *              freqCount                      *
 ***********************************************
 * Sets an array from 0 to length with the     *
 * total number of each chracter in file.      *
 * FreqCount returns true if the file is open. *
 * FreqCount returns false if the file is      *
 * unable to open.                             *
 ***********************************************/
 
bool freqCount(int* a, int length, const char* file) {
    setArray(a , length);
    FILE* f = openInFile(file);
    if (f == NULL) {
        return false;
    }
    int c = fgetc(f);
    while (c != EOF) {
        a[c]++;
        c = getc(f);
    }
    fclose(f);
    return true;
}

/***********************************************
 *               setarray                      *
 ***********************************************
 * setArray fills array a with the integer     *
 * 0 from a[0] to length.                      *
  ***********************************************/

void setArray(int* a, int length) {
    for (int i = 0; i <= length; i++) {
        a[i] = 0;
    }
    return;
}

/***********************************************
 *              openInFile                     *
 ***********************************************
 * Return an open FILE* for reading characters.*
 * If file does not open openInFile will print *
 * console message and return NULL.            *
 ***********************************************/

FILE* openInFile(const char* fileName) {
    FILE* infile = fopen(fileName, "r");
    if (infile == NULL) {
        printf("Cannot open file %s for reading\n", fileName);
        return NULL;
    }
    return infile;
}


/***********************************************
 *              openOutFile                    *
 ***********************************************
 * Return an open FILE* for writing characters.*
 * If file does not open openOutFile will print*
 * console message and return NULL.            *
 ***********************************************/

FILE* openOutFile(const char* fileName) {
    FILE* outfile = fopen(fileName, "w");
    if (outfile == NULL) {
        printf("cannnot open file %s for writing\n", fileName);
        return NULL;
    }
    return outfile;
}

/***********************************************
 *              buildHuffmanTree               *
 ***********************************************
 * Build a huffman tree using freqArray.       *
 * huffman tree will contain all chracters     *
 * in freqArray from 0 to 1                    *
 ***********************************************/

Tree buildHuffmanTree(int* freqArray, int length) {
    PriorityQueue  q;
    ItemType r, s;
    PriorityType l,m;
  
    buildPriorityQueue(q, freqArray, length);
    while (!isEmpty(q)) {
        remove(q, r, l);
        if (isEmpty(q)) {
            Tree temp = r;
            return temp;
        }
        remove(q, s, m);
        Tree t = new Node(r, s);
        l = m+ l;
        insert(q, t, l); 
    }

}

/***********************************************
 *              buildPriorityQueue             *
 ***********************************************
 * Build a PriorityQueue with freqArray from   *
 * 0 to length.                                *
 ***********************************************/

void buildPriorityQueue(PriorityQueue& q, int* freqArray, int length) {
    Tree t;
    for (int i = 0;i < length; i++) {
        if (freqArray[i] > 0) {
            t = new Node(i);
            insert(q, t, freqArray[i]);
        }
    }
   
}

/***********************************************
 *              setCharArray                   *
 ***********************************************
 * Set all values in Code[] from 0 to length   *
 * to equal "\0"                               *
 ***********************************************/
 
void setCharArray(const char* Code[], int length) {
    for (int i = 0; i <= length; i++) {
        Code[i] = "\0";
    }
    return;    
}

/***********************************************
 *              fillArray                      *
 ***********************************************
 * fillArray sets Code to prefix at the        *
 * position of each chracter in the three      *
 * head.                                       *
 ***********************************************/
 
void fillArray(Tree head, const char* Code[], const char* prefix) {
    if (head->kind == NodeKind(0)) {
        Code[head->ch] = prefix;
    }
    else if (head->kind == NodeKind(1)) {
        char* left = new char[strlen(prefix)+1];
        left = strcpy(left,prefix);
        left = strcat(left, "0");
        fillArray(head->left, Code, left);        
        char* right = new char[strlen(prefix)+1];
        right = strcpy(right,prefix);
        right = strcat(right,"1");
        fillArray(head->right, Code, right);
    }
}

/***********************************************
 *              buildCode                      *
 ***********************************************
 * Fill the array Code from 0 to length with   *
 * a string representing each chracter in tree.*
 ***********************************************/
 
void buildCode(Tree head, const char* Code[], int length) {
    setCharArray(Code, length);
    fillArray(head, Code, "");
    printCharArray(Code, length);
}

/***********************************************
 *              writeTreeBinary                *
 ***********************************************
 * Writes a binary File f with the tree head   *
 * writing the binary path to each chracter    *
 * in tree to the file f.                      *
 ***********************************************/

void writeTreeBinary(BFILE* f,Tree head) {
    if (head->kind == NodeKind(0)) {
        writeBit(f, 1);
        writeByte(f, head->ch);
    }
    else if (head->kind == NodeKind(1)) {
        writeBit(f, 0);
        writeTreeBinary(f, head->left);
        writeTreeBinary(f, head->right);    
    }
}

/***********************************************
 *              writeCodeBinary                *
 ***********************************************
 * Writes the string code into the binaryFile  *
 * not including the "\0"                      *
 ***********************************************/

void writeCodeBinary(BFILE* binaryFile, const char* code) {
    for (int i = 0; i < strlen(code); i++) {
        if (code[i] == '0') {
            writeBit(binaryFile, 0);
        }
        else if (code[i] == '1') {
            writeBit(binaryFile, 1);
        }
    }
}

/***********************************************
 *              writeCompressed                *
 ***********************************************
 * Writes binaryFile by reading each character *
 * in readFile and finding the associated      *
 * string in Code[] then writes the string to  *
 * binaryFile.                                 *
 ***********************************************/

void writeCompressed(const char* readFile ,BFILE* binaryFile, const char* Code[]) {
    FILE*  read  = openInFile(readFile);
    
    int temp = getc(read);
    while (temp != EOF) {
        writeCodeBinary(binaryFile, Code[temp]);
        temp = getc(read);
    }
}

