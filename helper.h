#ifndef MATRIX_CHAIN_MULTIPLICATION_HELPER_H
#define MATRIX_CHAIN_MULTIPLICATION_HELPER_H

#include <stdlib.h>

typedef int** mat;

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

#endif //MATRIX_CHAIN_MULTIPLICATION_HELPER_H
