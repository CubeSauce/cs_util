#include <cstdio>
#include <cstdlib>

#include "cs/containers/hash_map.hpp"
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

    Hash_Map<uint64, Test> map;

    uint64 elapsed_avg = 0, count = 0;
    uint64 largest = 0, shortest = UINT64_MAX;
    for (uint64 i = 0; i < N; ++i)
    {
        uint64 ticks = get_ticks();
        map.insert(i, i % 2 == 0 ? 2 : i);
        uint64 elapsed = get_ticks() - ticks;
        elapsed_avg += elapsed;

        if (elapsed > largest)
        {
            largest = elapsed;
        }

        if (elapsed < shortest)
        {
            shortest = elapsed;
        }
    }

    elapsed_avg /= N;
    printf("Average reserved insertion time: %llu ns\n", convert_ticks_to_ns(elapsed_avg));
    printf("Shortest reserved insertion time: %llu ns - %llu times\n", convert_ticks_to_ns(shortest), count);
    printf("Largest reserved insertion time: %llu ns\n", convert_ticks_to_ns(largest));

    elapsed_avg = 0; count = 0;
    largest = 0, shortest = UINT64_MAX;
    for (uint64 i = 0; i < N; ++i)
    {
        uint64 ticks = get_ticks();
        assert(map.find(i));
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


    Test* found = map.find(N2);
    assert(found);
    Test* not_found = map.find(N);
    assert(!not_found);

    return 0;
}