#include <random>

#include "Random.hpp"

int ex::random(int x) {

    return rand() % (x + 1);
}

int ex::random(int x, int y) {

    return x + rand() % ((y + 1) - x);
}

float ex::random(float x) {

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> dis(0.f, x);

    return dis(gen);
}

float ex::random(float x, float y) {

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> dis(x, y);

    return dis(gen);
}