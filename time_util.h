#ifndef MATRIX_CHAIN_MULTIPLICATION_TIME_UTIL_H
#define MATRIX_CHAIN_MULTIPLICATION_TIME_UTIL_H

#include <time.h>
#include "defines.h"

double time_matr_multipl(mat (*func)(), void (*Free)(), int start, int end, const mat* args1, const int* args2, const int** args3)
{
    clock_t time1, time2;
    time1 = clock();
    mat A = func(start, end, args1, args2, args3);
    time2 = clock();
    Free(A, args2[start - 1]);

    return ((double)(time2 - time1)) / CLOCKS_PER_SEC;
}


#endif //MATRIX_CHAIN_MULTIPLICATION_TIME_UTIL_H
