#include <stdio.h>
#include <stdlib.h>

#include "mat_util.h"
#include "defines.h"



long opt_solution(const ll *dim_array, int n, ll** P, ll** S)
{
    for (int l = 2; l < n; ++l)
    {
        for (int i = 1; i < n - l + 1; ++i)
        {
            int j = i + l - 1;
            for (int k = i; k < j; ++k)
            {
                ll q = P[i][k] + P[k + 1][j] + dim_array[i - 1] * dim_array[k] * dim_array[j];
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

void init(ll*** P, ll*** S)
{
    *P = (ll**)malloc(N * sizeof(ll*)); *S = (ll**)malloc(N * sizeof(ll*));
    for (int i = 0; i < N; ++i)
    {
        (*P)[i] = (ll*)malloc(N * sizeof(ll));
        (*S)[i] = (ll*)malloc(N * sizeof(ll));
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

ll* read_from_file(char* filepath, int *n)
{
    FILE *in;
    ll* dim_array = NULL;
    in = fopen(filepath, "r");
    fscanf(in, "%d\n", n);
    dim_array = (ll*)malloc(*n * sizeof(ll));
    for (int i = 0; i < *n; ++i)
    {
        fscanf(in, "%llu ", dim_array + i);
    }
    fclose(in);
    return dim_array;
}

int main(int argc, char** argv)
{
    if (argc < 2) printf("Call: ./program_name infile_path");
    char* filepath = argv[1];
    int arr_len;
    ll sum = 0;
    ll* dim_array = read_from_file(filepath, &arr_len);
    ll **DP, **Par_placement; init(&DP, &Par_placement);

    ll opt_dim = opt_solution(dim_array, arr_len, DP, Par_placement);
    printf("Optimalan broj mnozenja je %lld\n", opt_dim);

    for (int i = 1; i < arr_len; i++) sum += dim_array[i] * dim_array[i+1];
    printf("Broj mnozenja po redu je %lld\n", sum * dim_array[0]);

    time_matrix_multiplications(Par_placement, dim_array, arr_len);
    free(dim_array);
    return 0;
}
