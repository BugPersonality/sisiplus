#pragma once

struct GameConfiguration {
    int population;
    int wheat;
    int land;
    int round;

    int currenLandPrice;
    int wheatDestroyedByRats;
    int wheatGatheredFromOneLandInEachRound[10];
    int wheatGathered;
    int wheatForEat;
    int landsForCultivation;
    int deadPopulationInEachRound[10];
    int arrivedPopulationInEachRound[10];

    bool didThePlagueHappen;
};