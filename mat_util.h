#ifndef MATRIX_CHAIN_MULTIPLICATION_MAT_UTIL_H
#define MATRIX_CHAIN_MULTIPLICATION_MAT_UTIL_H

#include "time_util.h"
#include "defines.h"
#include <stdlib.h>
#include <assert.h>


mat create_mat(int n, int m)
{
    mat A = (mat)malloc(n * sizeof(ll*));
    for (int i = 0; i < n; ++i)
    {
        A[i] = (ll*)malloc(m * sizeof(ll));
        for (int j = 0; j < m; ++j)
        {
            A[i][j] = (i == j);
        }
    }

    return A;
}

mat multiply_mat(const mat A, const mat B, int n, int k, int m)
{
    mat C = create_mat(n, m);
    double time1 = clock();
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
    time1 = (clock() - time1) / CLOCKS_PER_SEC;
    printf("Multiplied %d x %d with %d x %d in %f\n", n, k, k, m, time1);
    return C;
}

void free_mat(mat A, ll n)
{
    for (int i = 0; i < n; ++i)
    {
        free(A[i]);
    }

    free(A);
}

mat multiply_array(int start, int end, mat* mat_array, ll* dim_array, ll** S)
{
    if (start == end)
    {
        return mat_array[start - 1];
    }
    else
    {
        mat A, B, C;
        A = multiply_array(start, S[start][end], mat_array, dim_array, S);
        B = multiply_array(S[start][end] + 1, end, mat_array, dim_array, S);
        C = multiply_mat(A, B, dim_array[start - 1], dim_array[S[start][end]], dim_array[end]);
        free_mat(A, dim_array[start - 1]);
        free_mat(B, dim_array[S[start][end]]);
        return C;
    }
}

mat multiply_in_order(int start, int end, mat* mat_array, ll* dim_array, ll** extra)
{
    mat A;
    for (int i = start; i < end; ++i)
    {
        A = multiply_mat(mat_array[i - 1], mat_array[i], dim_array[i - 1], dim_array[i], dim_array[i + 1]);
        free_mat(mat_array[i - 1], dim_array[i - 1]);
        free_mat(mat_array[i], dim_array[i]);
        mat_array[i] = A;
        dim_array[i] = dim_array[i - 1];
    }
    return A;
}

mat* generate_mat_array(const ll* dim_array, int n)
{
    mat *array = (mat*)malloc((n - 1) * sizeof(mat));
    for (int i = 0; i < n - 1; ++i)
    {
        array[i] = create_mat(dim_array[i], dim_array[i+1]);
    }

    return array;
}

void time_matrix_multiplications(ll** PP, ll* dim_array, int n)
{
    mat* mat_array = generate_mat_array(dim_array, n);
    double result1, result2;
    result1 = time_function(multiply_array, free_mat, 1, n - 1, mat_array, dim_array, PP);
    printf("Optimal: %f\n", result1);
    mat_array = generate_mat_array(dim_array, n);
    free_mat(PP, N);
    result2 = time_function(multiply_in_order, free_mat, 1, n - 1, mat_array, dim_array, NULL);
    printf("In order: %f\n", result2);
}

#endif //MATRIX_CHAIN_MULTIPLICATION_MAT_UTIL_H
