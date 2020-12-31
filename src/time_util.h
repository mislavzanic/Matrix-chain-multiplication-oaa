#ifndef MATRIX_CHAIN_MULTIPLICATION_TIME_UTIL_H
#define MATRIX_CHAIN_MULTIPLICATION_TIME_UTIL_H

#include <time.h>
#include "defines.h"

double time_function(mat (*func)(int, int, mat*, ll*, ll**), void (*free_mat)(mat, ll), int start, int end, mat* args1, ll* args2, ll** args3)
{
    clock_t time1, time2;
    time1 = clock();
    mat A = func(start, end, args1, args2, args3);
    time2 = clock();
    free_mat(A, args2[start - 1]);

    return ((double)(time2 - time1)) / CLOCKS_PER_SEC;
}


#endif //MATRIX_CHAIN_MULTIPLICATION_TIME_UTIL_H
