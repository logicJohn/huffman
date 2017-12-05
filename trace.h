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

bool checkTrace(int argc, char* argv[]);
void printDescription(int x);
void printArray(int* a, int length);
void tracePrintTree(Tree head);
void printCharArray(const char* Code[], int length);
void tracePrintTreeRoute(Tree head, const char* path);



#endif
