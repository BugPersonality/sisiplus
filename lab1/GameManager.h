#pragma once

#include "Randomizer.h"
#include "GameConfiguraion.h"
#include "Request.h"

class GameManager {
public:
    GameManager(GameConfiguration config);

    RequestResult nextRound();

    void updateData();
    void setNewConfig(GameConfiguration config);

    int currentRound();
    GameConfiguration getConfig();

    std::string getStatus();
    std::string getEndGameStatistics();

    RequestResult buyLands(int landsCount);
    RequestResult sellLands(int landsCount);
    RequestResult setCountOfWheatForEat(int wheatCount);
    RequestResult setCountOfLandsForCultivation(int landsCount);

private:
    GameConfiguration config;
    Randomizer randimizer;
};
