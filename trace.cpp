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

void printDescription(int x){
    for (int i = 0; i<256; i++){
        printf("%d %c \n", i, i);
    }
}