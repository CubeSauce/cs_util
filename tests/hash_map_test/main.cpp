#include <cstdio>
#include <cstdlib>

#include "cs/containers/hash_map.hpp"

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

    for (uint64 i = 0; i < N; ++i)
    {
        map.insert(i, i % 2 == 0 ? 2 : i);
    }

    Test* found = map.find(N2);
    assert(found);
    Test* not_found = map.find(N);
    assert(!not_found);

    return 0;
}