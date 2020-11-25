#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <stdint.h>
#include <stdio.h>
#include <time.h>

void printArray(uint32_t arr[], uint32_t arrSize);

double cpuTimeSort(void (*sortFunction)(uint32_t*, uint32_t),
                   uint32_t arr[], 
                   uint32_t size);

double clockTimeSort(void (*sortFunction)(uint32_t*, uint32_t),
                     uint32_t arr[], 
                     uint32_t size);

#endif // _ARRAY_H_