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

using namespace std;

bool freqCount(int* a, int length, const char* file);
void setArray(int* a, int length);
FILE* openInFile(const char* fileNmae);
FILE* openOutFile(const char* fileName);
void printArray(int* a, int length);
void charDescription(unsigned char c);


int traceEnabled = 0;


int main(int argc, char* argv[]){
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
    freqArray = new int[256];
    if (!freqCount(freqArray, arrayLength, A)){
        printf(" File read returned NULL\n");
        return 1;
    }
    printArray(freqArray, arrayLength);

    printDescription(0);
    
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


void printArray(int* a, int length){
    int counter=0;
    if (traceEnabled == 0){
        return;
    }
    for (int i = 0; i < length; i++){
        if (a[i] > 0){    
            printf(" [%i] = %i ", i , a[i]);
            counter++;
            if (counter % 3 == 0){
                
                printf("\n");
                counter = 0;
            }
        }
    }
}


