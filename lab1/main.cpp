#include <iostream>

#include "Request.h"
#include "GameConfiguraion.h"
#include "GameCycle.h"

#include <fstream>

using namespace std; // g++ -std=c++17 *.cpp -o app

static GameConfiguration defaultGameConfig {
    100,                                                 // population
    2800,                                                // wheat
    1000,                                                // land
    1,                                                   // round
    static_cast<int>(Randomizer().randomValue(1, 6)),    // currenLandPrice
    0,                                                   // wheatDestroyedByRats
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},                      // wheatGatheredFromOneLandInEachRound
    0,                                                   // wheatGathered
    0,                                                   // wheatForEat
    0,                                                   // landsForCultivation
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},                      // deadPopulationInEachRound
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},                      // arrivedPopulationInEachRound
    false                                                // didThePlagueHappen
};

int main() {
    GameCycle cycle = GameCycle(defaultGameConfig, "SaveConfig.bin");
    cycle.start();

    return 0;
}