#ifndef MATRIX_CHAIN_MULTIPLICATION_MAT_UTIL_H
#define MATRIX_CHAIN_MULTIPLICATION_MAT_UTIL_H

#include "time_util.h"
#include "defines.h"
#include <stdlib.h>
#include <assert.h>


mat create_mat(int n, int m)
{
    mat A = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i)
    {
        A[i] = (int*)malloc(m * sizeof(int));
        for (int j = 0; j < m; ++j)
        {
            A[i][j] = (i == j);
        }
    }

    return A;
}

mat multiply(const mat A, const mat B, int n, int k, int m)
{
    mat C = create_mat(n, m);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            C[i][j] = 0;
            for (int l = 0; l < k; ++l)
            {
                C[i][j] += A[i][l] * B[l][j];
            }
        }
    }

    return C;
}

void Free(mat A, int n)
{
    for (int i = 0; i < n; ++i)
    {
        free(A[i]);
    }

    free(A);
}

mat multiply_array(int start, int end, const mat* mat_array, const int* dim_array, const int** S)
{
    if (start == end)
    {
        return mat_array[start];
    }
    else
    {
        mat A, B, C;
        A = multiply_array(start, S[start][end], mat_array, dim_array, S);
        B = multiply_array(S[start][end] + 1, end, mat_array, dim_array, S);
        C = multiply(A, B, dim_array[start - 1], dim_array[S[start][end]], dim_array[end]);
        Free(A, dim_array[start - 1]);
        Free(B, dim_array[S[start][end]]);
        return C;
    }
}

mat* generate_mat_array(const int* dim_array, int n)
{
    mat *array = (mat*)malloc((n - 1) * sizeof(mat));
    for (int i = 0; i < n - 1; ++i)
    {
        array[i] = create_mat(dim_array[i], dim_array[i+1]);
    }

    return array;
}

void time_matrix_multiplications(const int** PP, const int* dim_array, int n)
{
    mat* mat_array = generate_mat_array(dim_array, n);
    mat result;
    double result1, result2;
    result1 = time_matr_multipl(multiply_array, Free, 1, 6, mat_array, dim_array, PP);
    result2 = time_matr_multipl(multiply_array, Free, 1, 6, mat_array, dim_array, PP);
    printf("%f %f", result1, result2);
}

#endif //MATRIX_CHAIN_MULTIPLICATION_MAT_UTIL_H
