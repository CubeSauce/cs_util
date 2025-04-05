#include <cstdio>
#include <cstdlib>

#include "cs/containers/dynamic_array.hpp"

struct Test
{
    uint64 i;

    Test() = default;
    Test(uint64 in): i(in) {
       // printf("Construct %lld\n", i);
    }

    ~Test()
    {
        //printf("Deconstruct %lld\n", i);
    }
};

int main(int argc, char** argv)
{
    if (argc == 1)
    {
        return -1;
    }

    const int64 e = atoll(argv[1]);
    const uint64 N = 1 << e;
    const uint64 N2 = N / 2;

    Dynamic_Array<Test> da;
    da.reserve(N);

    for (uint64 i = 0; i < N; ++i)
    {
        da.push_back(i);
    }

    da.clear();

    for (uint64 i = 0; i < N; ++i)
    {
        if (i % 2 == 0)
        {
            da.push_back(2);
        }
        else
        {
            da.push_back(i);
        }
    }

    int64 n_erases = da.erase_all_if([](const Test& value){
        return value.i == 2;
    });

    if (n_erases != N2)
    {
        printf("Expected %lld erases, got %lld\n", N2, n_erases);
        return -2;
    }

    return 0;
}