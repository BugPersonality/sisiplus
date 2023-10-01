#include <iostream>
#include <vector>
#include <limits>

#include "GameCycle.h"

GameCycle::GameCycle(
    GameConfiguration config,
    std::string saveFileName
) : manager(config), fileManager(saveFileName) { }  

void GameCycle::start() {
    tryAskToLoadSavedGame();

    for (int round = manager.currentRound(); round <= 10; ++round) {
        manager.updateData();
        
        std::cout << manager.getStatus();

        if (requestSaveGame()) {
            std::cout << "Игра была сохранена" << std::endl;
            return;
        }

        requestUserInput();

        RequestResult nextRoundResult = manager.nextRound();
        if (!nextRoundResult.success) {
            std::cout << nextRoundResult.message << std::endl;
            return;
        }
    }
    
    std::cout << manager.getEndGameStatistics();
}

bool GameCycle::requestSaveGame() {
    char choice;
    std::cout << "Вы хотите сохранить текущий результат и закончить игру? (y/n): ";
    std::cin >> choice;

    if (choice == 'y' && fileManager.saveConfiguration(manager.getConfig())) { 
        return true;
    }

    // std::cin.clear();
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return false;
}

void GameCycle::tryAskToLoadSavedGame() {
    GameConfiguration loadedConfig;
    if (fileManager.loadConfiguration(loadedConfig)) {
        char choice;

        std::cout << "Вы хотите начать новую игру или загрузить сохранение? (y/n): ";
        std::cin >> choice;

        if (choice == 'y') { 
            manager.setNewConfig(loadedConfig);
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } 
}

void GameCycle::requestUserInput() {
    int landsToBuy, landsToSell, wheatForEat, landsForCultivation;

    std::vector<Request> requests = {
        {"Сколько акров 🏔️  повелеваешь купить? ", landsToBuy, [&](int value) { return manager.buyLands(value); }},
        {"Сколько акров 🏔️  повелеваешь продать? ", landsToSell, [&](int value) { return manager.sellLands(value); }},
        {"Сколько бушелей 🌾  повелеваешь съесть? ", wheatForEat, [&](int value) { return manager.setCountOfWheatForEat(value); }},
        {"Сколько акров 🏔️  повелеваешь засеять? ", landsForCultivation, [&](int value) { return manager.setCountOfLandsForCultivation(value); }}
    };

    std::cout << "Что пожелаешь, повелитель?" << std::endl;

    for (const Request& request : requests) {
        RequestResult result = {false, ""};

        do {
            std::cout << request.prompt;

            if (!(std::cin >> request.value)) {
                std::cout << "Пожалуйста, введите корректное целое число." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {
                result = request.action(request.value);
                std::cout << result.message;
            }

        } while (!result.success);
    }
}