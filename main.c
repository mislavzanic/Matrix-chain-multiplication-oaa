#include <stdio.h>
#include <stdlib.h>

#include "mat_util.h"
#include "defines.h"


typedef int** mat;

long opt_solution(int *dim_array, int n, ull** P, ull** S)
{
    for (int l = 2; l < n; ++l)
    {
        for (int i = 1; i < n - l + 1; ++i)
        {
            int j = i + l - 1;
            for (int k = i; k < j; ++k)
            {
                ull q = P[i][k] + P[k + 1][j] + dim_array[i - 1] * dim_array[k] * dim_array[j];
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

void init(ull*** P, ull*** S)
{
    *P = (ull**)malloc(N * sizeof(ull*)); *S = (ull**)malloc(N * sizeof(ull*));
    for (int i = 0; i < N; ++i)
    {
        (*P)[i] = (ull*)malloc(N * sizeof(ull));
        (*S)[i] = (ull*)malloc(N * sizeof(ull));
        for (int j = 0; j < N; ++j)
        {
            if (i == j)
            {
                (*S)[i][j] = 1;
                (*P)[i][j] = 0;
            }
            else (*P)[i][j] = INF;
        }
    }
}

int* read_from_file(char* filepath)
{
    FILE *in;
    int* dim_array = NULL;
    int arr_len;
    in = fopen(filepath, "r");
    fscanf(in, "%d\n", &arr_len);
    dim_array = (int*)malloc(arr_len * sizeof(int));
    for (int i = 0; i < arr_len; ++i)
    {
        fscanf(in, "%d ", dim_array + i);
    }
    fclose(in);
    return dim_array;
}

int main(int argc, char** argv)
{
    if (argc < 2) printf("Call: ./program_name infile_path");
    char* filepath = argv[1];
    int* dim_array = read_from_file(filepath);
    ull **DP, **Par_placement; init(&DP, &Par_placement);

    ull opt_dim = opt_solution(dim_array, 14, DP, Par_placement);
    printf("Optimalan broj mnozenja je %u\n", opt_dim);
    time_matrix_multiplications(Par_placement, dim_array, 14);
    free(dim_array);
    return 0;
}
