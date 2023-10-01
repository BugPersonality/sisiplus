#include <random>
#include <chrono>

#include "Randomizer.h"

double Randomizer::randomValue(double min, double max) {
    unsigned int seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
    std::mt19937 rnd(seed);
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(rnd);
}

bool Randomizer::eventWithChance(int chance) {
    if (chance > 0 && chance < 100) {
        int value = randomValue(0, 100);
        return value <= chance;
    } else {
        return chance == 100;
    }
}