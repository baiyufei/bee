#include <iostream>
#include <random>
#include "TDOA.h"
int main()
{
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(-200, 200);
    int i = 100;
    TDOA t;
    while (i--) {
        int x = distribution(generator);
        int y = distribution(generator);
        int z = distribution(generator);
        t.simulate(x, y, z);
    }
    return 0;
}
