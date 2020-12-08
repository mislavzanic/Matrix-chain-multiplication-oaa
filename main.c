#include <stdio.h>
#include <stdlib.h>

#define N 1000
#define INF -1

int zagrade[N][N];

int dinamika(int *niz_dimenzija, int start, int end)
{
    if (start == end) return zagrade[start][end];
    int min = INF;
    for (int k = start; k < end; ++k)
    {
        int temp = dinamika(niz_dimenzija, start, k) + dinamika(niz_dimenzija, k+1, end) + niz_dimenzija[start - 1] * niz_dimenzija[k] * niz_dimenzija[end];
        if (temp < min || min == INF)
        {
            min = temp;
        }
    }
    zagrade[start][end] = min;
    return zagrade[start][end];
}

int main()
{
    int niz_dimenzija[] = {1, 2, 3, 4};
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (i == j) zagrade[i][j] = 0;
            else zagrade[i][j] = INF;
        }
    }
    int opt_dim = dinamika(niz_dimenzija, 1, 3);
    printf("Optimalan broj mnozenja je %d", opt_dim);
    return 0;
}
