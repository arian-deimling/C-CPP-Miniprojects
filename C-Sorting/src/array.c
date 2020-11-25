#include "array.h"
 
void printArray(uint32_t arr[], uint32_t arrSize) {

    // opening bracket at the beginning of the array
    printf("%s", "[");

    for (uint32_t i = 1; i < arrSize; i++) {

        // print each value in the array with 4 spaces of padding
        printf("%4d, ", arr[i - 1]);

        // if the current element is the tenth in the current line
        // and is not the final element in the array, print newline
        if ((i % 10 == 0) && (i != arrSize - 1)) {
            printf("%s", "\n ");
        }
    }

    // print the final value of the array as well as a newline character
    printf("%4d]\n", arr[arrSize - 1]);
}

double cpuTimeSort(void (*sortFunction)(uint32_t*, uint32_t),
                   uint32_t arr[], 
                   uint32_t size) {

    // stores the time before and after the function call
    clock_t start, end;

    // record start time (cpu time)
    start = clock();

    // call the sort function
    (*sortFunction)(arr, size);

    // record end time
    end = clock();

    // return the time taken to perform the sort
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

double clockTimeSort(void (*sortFunction)(uint32_t*, uint32_t),
                     uint32_t arr[], 
                     uint32_t size) {

    // stores the time before and after the function call
    struct timespec start, end;

    // record start time (clock time)
    clock_gettime(CLOCK_REALTIME, &start);

    // call the sort function
    (*sortFunction)(arr, size);

    // record end time
    clock_gettime(CLOCK_REALTIME, &end);

    // return the time taken to perform the sort
    return (end.tv_sec - start.tv_sec) + ((end.tv_nsec - start.tv_nsec) / 1e9);
}
