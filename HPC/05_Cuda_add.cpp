#include <iostream>
#define N 10

void add(int *a, int *b, int *c)
{
    for (int tid = 0; tid < N; tid++)
    {
        c[tid] = a[tid] + b[tid];
    }
}

int main()
{
    int a[N], b[N], c[N];

    // Fill the arrays 'a' and 'b'
    for (int i = 0; i < N; i++)
    {
        a[i] = -i;
        b[i] = i * i;
    }

    add(a, b, c);

    // Display the results
    for (int i = 0; i < N; i++)
    {
        std::cout << a[i] << " + " << b[i] << " = " << c[i] << std::endl;
    }

    return 0;
}
//g++ -o 05_cuda 05_cuda_add.cpp
//./05_cuda_add