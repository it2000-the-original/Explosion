#include <random>

#include "Random.hpp"

int ex::random(int x) {

    return rand() % (x + 1);
}

int ex::random(int x, int y) {

    return x + rand() % ((y + 1) - x);
}