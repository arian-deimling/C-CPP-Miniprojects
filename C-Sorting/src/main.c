#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "sort.h"
#include "array.h"

// SIZE is provided via compiler flag
const uint32_t size = SIZE;

int main(int argc, char* argv[]) {

    // set the psuedo-random number generator seed 
    srand(0);

    // allocate memory in heap for an array
    uint32_t* array = malloc(sizeof(uint32_t) * size);
    
    // fill the array with random numbers
    for (uint32_t i = 0; i < size; i++) {
        array[i] = rand();
    }

    // calculate the time taken to run the sort function on the array
    double t = clockTimeSort(tMergeSortArray, array, size);
    printf("%lf\n", t);
}

