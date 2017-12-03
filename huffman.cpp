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
void printCharArray(const char* Code[], int length);

int traceEnabled = 0;


int main(int argc, char* argv[]){
    //make the -t filename 1 and filename 2 a helper function
    //use a loop to check the whole input for the correct info
    if (argc > 3) {
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

    int arrayLength = 256;
    int* freqArray;
    const char* codeBlock[arrayLength];
    freqArray = new int[arrayLength];
    if (!freqCount(freqArray, arrayLength, A)){
        printf(" File read returned NULL\n");
        return 1;
    }
    printArray(freqArray, arrayLength);
    Tree huffmanTree;
    huffmanTree = buildHuffmanTree(freqArray, arrayLength);
    tracePrintTree( huffmanTree );
    

    buildCode(huffmanTree, codeBlock, arrayLength);
    printf("finished\n");
    
    delete huffmanTree;
    delete[] freqArray;
    return 0;
}   

void charDescription(unsigned char c){
    isprint(c);
}



bool freqCount(int* a, int length, const char* file ){
    setArray(a , length);
    FILE* f = openInFile(file);
    if (f == NULL){
        return false;
    }
    int c = fgetc(f);
    while (c != EOF){
        a[c]++;
        c = getc(f);
    }
    fclose(f);
    return true;
}



void setArray(int* a, int length){
    for (int i = 0; i <= length; i++){
        a[i] = 0;
    }
    return;
}



FILE* openInFile(const char* fileName){
    FILE* infile = fopen(fileName, "r");
    if (infile == NULL){
        printf("Cannot open file %s for reading\n", fileName);
        return NULL;
    }
    return infile;
}



FILE* openOutFile(const char* fileName){
    FILE* outfile = fopen(fileName, "w");
    if (outfile == NULL){
        printf("cannnot open file %s for writing\n", fileName);
        return NULL;
    }
    return outfile;
}

Tree buildHuffmanTree(int* freqArray, int length){
    PriorityQueue  q;
    ItemType r, s;
    PriorityType l,m;
  
    buildPriorityQueue(q, freqArray, length);
    while (!isEmpty(q)){
        remove(q, r, l);
        if( isEmpty(q) ){
            Tree temp = r;
            return temp;
        }
        remove(q, s, m);
        Tree t = new Node(r, s);
        l += m;
        insert(q, t, l); 
    }

}

void buildPriorityQueue(PriorityQueue& q, int* freqArray, int length){
    Tree t;
    for (int i = 0; i < length; i++){
        if (freqArray[i] > 0){
            t = new Node(i);
            insert(q, t, freqArray[i]);
        }
    }
   
}

void setCharArray(const char* Code[], int length){
    for (int i = 0; i <= length; i++){
        Code[i] = "\0";
    }
    return;    
}

void fillArray(Tree head,const char* Code[],const char* prefix){
    printf("line 163 \n");
    printf(" prefix: %s",prefix );
    char* temp;
    temp = strcpy(temp,prefix);
    printf(" temp: %s", temp );
    if (head->kind == NodeKind(1)){
        if (head->right != NULL){
            fillArray(head->right, Code, strcat(temp,"0"));
        }
        if (head->left != NULL){
            fillArray(head->left, Code, strcat(temp,"0"));
        }
    }
    if (head->kind == NodeKind(0)){
       printf("line 175 \n");
       Code[head->ch] = prefix;
       
    }
}

void buildCode(Tree head,const char* Code[], int length){
    printf("line 179 \n");
    setCharArray(Code, length);
    printf("line 181 \n");
    fillArray(head, Code, "0");
    printf("line 183 \n");
    printCharArray(Code, length);
}

void printCharArray(const char* Code[], int length){
    for (int i = 0; i<length; i++){
        
        if (strcmp(Code[i], "\0") != 0){
            printf("%d\n", Code[i]);
        }
    }
    
}
