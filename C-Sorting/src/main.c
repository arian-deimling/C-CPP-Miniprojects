#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "sort.h"
#include "array.h"

#define SIZE 100000000

int main(int argc, char* argv[]) {

    uint32_t* array = malloc(sizeof(uint32_t) * SIZE);
    srand(time(NULL));

    for (uint32_t i = 0; i < SIZE; i++) {
        array[i] = rand() % 100;
    }

    double t = clockTimeSort(tMergeSortArray, array, SIZE);
    printf("%lf\n", t);
}

