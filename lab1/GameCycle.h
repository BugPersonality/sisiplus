#pragma once

#include "GameManager.h"
#include "FileManager.h"
#include "Request.h"

class GameCycle {
public:
    GameCycle(GameConfiguration config, std::string saveFileName); 
    
    void start();
    void requestUserInput();
    void tryAskToLoadSavedGame();
    bool requestSaveGame();

private:
    GameManager manager;
    FileManager fileManager;
};