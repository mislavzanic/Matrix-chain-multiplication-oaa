#ifndef MATRIX_CHAIN_MULTIPLICATION_HELPER_H
#define MATRIX_CHAIN_MULTIPLICATION_HELPER_H

#include <stdlib.h>
#include <assert.h>
#include <time.h>

typedef int** mat;

double time_matr_multipl(mat (*func)(), void (*Free)(), int start, int end, mat* args1, int* args2, int** args3)
{
    clock_t time1, time2;
    time1 = clock();
        mat A = func(start, end, args1, args2, args3);
    time2 = clock();
    Free(A, args2[start - 1]);

    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

mat create_mat(int n, int m)
{
    mat A = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i)
    {
        A[i] = (int*)malloc(m * sizeof(int));
    }

    return A;
}

mat multiply(mat A, mat B, int n, int k, int m)
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

mat multiply_array(int start, int end, mat* mat_array, int* dim_array, int** S)
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

void time_matrix_multiplications(int** P, int** S, int N)
{
    //mat* mat_array = generate_mat_array();
    mat result;
    double result1, result2;
    result1 = time_matr_multipl(multiply_array, Free, 1, 6, mat_array, dim_array, S);
    result2 = time_matr_multipl(multiply_array, Free, 1, 6, mat_array, dim_array, S);
    printf("%f %f", result1, result2);
}

#endif //MATRIX_CHAIN_MULTIPLICATION_HELPER_H
