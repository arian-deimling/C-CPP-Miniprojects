#include "sort.h"

typedef struct Array {
    uint32_t* data;
    uint32_t size;
} Array;

uint8_t threadCount;

void* threadedMergeSortArrayImpl(void* arrayPtr);

void bubbleSortArray(uint32_t array[], uint32_t size) {

    // boolean value that stores whether the list is sorted
    uint8_t sorted = 0;
    uint32_t temp; 

    while (!sorted) {

        // assume the list is completely sorted
        sorted = 1;

        // the first for-loop must iterate over each value in the array except
        // for the last; each subsequent loop may ignore one more value at the
        // end of the list because those have been sorted
        size--;

        // iterate over `N - 1` unsorted values in the array
        for (uint32_t i = 0; i < size; i++) {

            // if the current and next number are out of place, swap their 
            // places
            if (array[i] > array[i + 1]) {

                temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;

                // if any numbers are out of place, the list is not sorted
                sorted = 0;
            }
        }
    }
}

void mergeSortArray(uint32_t array[], uint32_t size) {

    // no sorting to be done if the array length is 0 or 1
    if (size == 1) { return; }

    // create references to each of the two halves of the array
    uint32_t *arrLeft = &array[0];
    uint32_t arrLeftSize = size / 2;
    uint32_t *arrRight = &array[size / 2];
    uint32_t arrRightSize = (size + 1) / 2;

    // merge sort the two halves of the array
    mergeSortArray(arrLeft, arrLeftSize);
    mergeSortArray(arrRight, arrRightSize);

    // once the halves are sorted, they will be merged into a temp array
    uint32_t *tempSorted = malloc(sizeof(uint32_t) * size);

    uint16_t idxLeft = 0;
    uint16_t idxRight = 0;
    for (uint32_t i = 0; i < size; i++) {

        // if there is no more data in Left, merge values from Right
        if (idxLeft == arrLeftSize) {
            tempSorted[i] = arrRight[idxRight++];
        
        // if there is no more data in Right, merge values from Left
        } else if (idxRight == arrRightSize) {
            tempSorted[i] = arrLeft[idxLeft++];

        // if the current value in Right is smaller than the current value in
        // Left, merge in the value from Right
        } else if (arrRight[idxRight] < arrLeft[idxLeft]) {
            tempSorted[i] = arrRight[idxRight++];

        // if none of the above is true, merge in the current value from Left
        } else {
            tempSorted[i] = arrLeft[idxLeft++];
        }
    }

    // place the sorted values from temp into the array
    for (uint32_t i = 0; i < size; i++) {
        array[i] = tempSorted[i];
    }

    free(tempSorted);
}

void tMergeSortArray(uint32_t array[], uint32_t size) {

    // turn the array information into a struct, so it can be passed to thread
    // creation function which limits functions to a single parameter
    Array arrayStruct;
    arrayStruct.data = array;
    arrayStruct.size = size;

    // call the threaded merge sort function on the array
    threadedMergeSortArrayImpl((void*) &arrayStruct);

    // no more threads exist after merge sort is complete
    threadCount = 0;
}

void* threadedMergeSortArrayImpl(void* arrayPtr) {

    // cast arrayPtr back into Array type
    Array array = *((Array*)arrayPtr);

    // no sorting to be done if the array length is 0 or 1
    if (array.size == 1) { return NULL; }

    // TODO - handle short arrays differently (i.e. len 2, 3?, 4?)

    // identifier for thread created for left half of the given array
    pthread_t leftThreadID;

    // boolean variables to store whether thread was created
    uint8_t leftThreadCreated = 0;

    // create references to each of the two halves of the array
    Array arrLeft;
    arrLeft.data = &array.data[0];
    arrLeft.size = array.size / 2;

    Array arrRight;
    arrRight.data = &array.data[array.size / 2];
    arrRight.size = (array.size + 1) / 2;

    // if another thread can be created, do so; subtract one from MAX_THREADS
    // because by default the program already occupies one thread
    if (threadCount < MAX_THREADS - 1) {

        // increment global thread count variable
        threadCount++;

        leftThreadCreated = 1;

        // create a thread that will sort the left half of the array
        pthread_create(&leftThreadID, NULL, 
                       threadedMergeSortArrayImpl, (void*) &arrLeft);

    } else { // if no more threads are available
        
        // call merge sort in the current thread
        threadedMergeSortArrayImpl((void*) &arrLeft);
    }

    // merge sort the right half of the array in the current thread
    threadedMergeSortArrayImpl((void*) &arrRight);

    // wait until the left half thread terminate if it was created
    if (leftThreadCreated) {
        pthread_join(leftThreadID, NULL);

        // it would make sense to decrement threadCount here but it is not, so
        // only large list sizes are sorted in separate threads; using
        // threading to sort small lists slows down the sort
    }

    // once the halves are sorted, they will be merged into a temp array
    uint32_t *tempSorted = malloc(sizeof(uint32_t) * array.size);

    uint16_t idxLeft = 0;
    uint16_t idxRight = 0;
    for (uint32_t i = 0; i < array.size; i++) {

        // if there is no more data in Left, merge values from Right
        if (idxLeft == arrLeft.size) {
            tempSorted[i] = arrRight.data[idxRight++];
        
        // if there is no more data in Right, merge values from Left
        } else if (idxRight == arrRight.size) {
            tempSorted[i] = arrLeft.data[idxLeft++];

        // if the current value in Right is smaller than the current value in
        // Left, merge in the value from Right
        } else if (arrRight.data[idxRight] < arrLeft.data[idxLeft]) {
            tempSorted[i] = arrRight.data[idxRight++];

        // if none of the above is true, merge in the current value from Left
        } else {
            tempSorted[i] = arrLeft.data[idxLeft++];
        }
    }

    // place the sorted values from temp into the array
    for (uint32_t i = 0; i < array.size; i++) {
        array.data[i] = tempSorted[i];
    }

    free(tempSorted);

    return NULL;
}