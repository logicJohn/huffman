// CSCI 2530
// Assignment: 8
// Author:     Johnnie Hernandez
// File:       trace.h
// Tab stops:  8

// 
#ifndef TRACE_H
#define TRACE_H

#include <cstdio>
#include "tree.h"

using namespace std;

extern int traceEnabled;

void printDescription(int x);
void printArray(int* a, int length);
void tracePrintTree(Tree head);



#endif
