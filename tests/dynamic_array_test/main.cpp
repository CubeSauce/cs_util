#include <cstdio>
#include <cstdlib>

#include "cs/containers/dynamic_array.hpp"
#include "cs/time/low_level_timer.hpp"

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

    uint64 elapsed_avg = 0, count = 0;
    uint64 largest = 0, shortest = UINT64_MAX;
    for (uint64 i = 0; i < N; ++i)
    {
        uint64 ticks = get_ticks();

        da.push_back(i);

        uint64 elapsed = get_ticks() - ticks;
        elapsed_avg += elapsed;

        if (elapsed > largest)
        {
            largest = elapsed;
        }

        if (elapsed < shortest)
        {
            shortest = elapsed;
            count = 0;
        }
        else if (shortest == elapsed)
        {
            count++;
        }
    }

    elapsed_avg /= N;
    printf("Average push_back time: %llu ns\n", convert_ticks_to_ns(elapsed_avg));
    printf("Shortest push_back time: %llu ns - %llu times\n", convert_ticks_to_ns(shortest), count);
    printf("Largest push_back time: %llu ns\n", convert_ticks_to_ns(largest));

    elapsed_avg = 0; count = 0;
    largest = 0, shortest = UINT64_MAX;
    for (uint64 i = 0; i < N; ++i)
    {
        uint64 ticks = get_ticks();

        assert(da.find_if([i](const Test& value){
            return value.i == i;
        }) != -1);

        uint64 elapsed = get_ticks() - ticks;
        elapsed_avg += elapsed;

        if (elapsed > largest)
        {
            largest = elapsed;
        }

        if (elapsed < shortest)
        {
            shortest = elapsed;
            count = 0;
        }
        else if (shortest == elapsed)
        {
            count++;
        }
    }

    elapsed_avg /= N;
    printf("Average find time: %llu ns\n", convert_ticks_to_ns(elapsed_avg));
    printf("Shortest find time: %llu ns - %llu times\n", convert_ticks_to_ns(shortest), count);
    printf("Largest find time: %llu ns\n", convert_ticks_to_ns(largest));

    da.clear();

    elapsed_avg = 0; count = 0;
    largest = 0, shortest = UINT64_MAX;
    for (uint64 i = 0; i < N; ++i)
    {
        uint64 ticks = get_ticks();

        da.push_back(i);

        uint64 elapsed = get_ticks() - ticks;
        elapsed_avg += elapsed;

        if (elapsed > largest)
        {
            largest = elapsed;
        }

        if (elapsed < shortest)
        {
            shortest = elapsed;
            count = 0;
        }
        else if (shortest == elapsed)
        {
            count++;
        }
    }

    elapsed_avg /= N;
    printf("Average reserved push_back time: %llu ns\n", convert_ticks_to_ns(elapsed_avg));
    printf("Shortest reserved push_back time: %llu ns - %llu times\n", convert_ticks_to_ns(shortest), count);
    printf("Largest reserved push_back time: %llu ns\n", convert_ticks_to_ns(largest));

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

    if (N2 != 1 && n_erases != (N2 + 1))
    {
        printf("Expected %lld erases, got %lld\n", N2 + 1, n_erases);
        return -2;
    }

    return 0;
}