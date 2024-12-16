/*
    Library for output.c
*/


#ifndef OUTPUT_HEADER
#define OUTPUT_HEADER

#include "basics.h"

void outputProcess(const char* stationType, const char* consumerType);
void createPath(const char* stationType, const char* consumerType, char* path);
void createOutputFile(const char* stationType, const char* consumerType);

#endif