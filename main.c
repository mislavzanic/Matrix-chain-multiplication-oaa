#include <stdio.h>
#include <stdlib.h>
#include "helper.h"

#define N 1000
#define INF -1

typedef int** mat;

int opt_solution(int *dim_array, int n, int** P, int** S)
{
    for (int l = 2; l < n; ++l)
    {
        for (int i = 1; i < n - l + 1; ++i)
        {
            int j = i + l - 1;
            for (int k = i; k < j; ++k)
            {
                int q = P[i][k] + P[k + 1][j] + dim_array[i - 1] * dim_array[k] * dim_array[j];
                if (q < P[i][j] || P[i][j] == INF)
                {
                    P[i][j] = q;
                    S[i][j] = k;
                }
            }
        }
    }
    return P[1][n - 1];
}

void init(int** P, int** S)
{
    P = (int**)malloc(N * sizeof(int*)); S = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; ++i)
    {
        P[i] = (int*)malloc(N * sizeof(int));
        S[i] = (int*)malloc(N * sizeof(int));
        for (int j = 0; j < N; ++j)
        {
            if (i == j)
            {
                S[i][j] = 1;
                P[i][j] = 0;
            }
            else P[i][j] = INF;
        }
    }
}

int main(int argc, char** argv)
{
//    if (argc < 2) printf("Call: ./program_name infile_path");
    char* filepath = argv[1];
    int dim_array[] = {30, 35, 15, 5, 10, 20, 25};
    int* index = (int*)malloc(6 * sizeof(int));
    int **P, **S; init(P, S);

    int opt_dim = opt_solution(dim_array, 7, P, S);
    printf("Optimalan broj mnozenja je %d\n", opt_dim);
    time_matrix_multiplications(P, S, N);
    return 0;
}
