#pragma once

class Randomizer {
public:
    Randomizer() {}

    double randomValue(double min, double max);

    bool eventWithChance(int chance);
};