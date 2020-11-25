#include "sort.h"

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

void mergeSortArray (uint32_t array[], uint32_t size) {

    // no sorting to be done if the array length is 0 or 1
    if (size == 1) { return; }

    if (size < 3) {
        bubbleSortArray(array, size);
        return;
    }

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
