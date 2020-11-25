/**
 * @file sort.h
 * @brief Declare sort functions.
 * 
 * Declares functions that implement a variety of algorithms and methods to
 * sort an array.
 * 
 * @author Arian Deimling
 * @date November 24, 2020
 */

#ifndef _SORT_H_
#define _SORT_H_

#include <stdint.h>
#include <stdlib.h>

/**
 * @brief Bubble sorts the array that is passed to the function - O(n²).
 * 
 * The sort iterates over the array examining two elements at a time and 
 * swapping them if they are out of order. With each iteration (I), beginning
 * at 0, the last I elements must be sorted, so they are ignored. If an
 * iteration over the list results in no swaps of out-of-place values (i.e. the
 * the list is sorted), the iterations terminate and the function returns.
 * 
 * @param array pointer to the first element of an array
 * @param size the number of values in the array
 * 
 * @return void
 */
void bubbleSortArray(uint32_t array[], uint32_t size);

/**
 * @brief Merge sorts the array that is passed to the function - O(n*log(n))
 * 
 * The sort divides the provided array into two halves (in place) and calls the
 * merge sort function recursively on each half. Once the function is called on
 * a list of length 1, it returns immediately. After the recursive calls to the
 * merge sort function return, they have been sorted, so each half is merged
 * together to create a single, sorted array and the function returns.
 * 
 * @param array pointer to the first element of an array
 * @param size the number of values in the array
 * 
 * @return void
 */
void mergeSortArray (uint32_t array[], uint32_t size);

#endif // _SORT_H_