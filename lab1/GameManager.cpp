#include <string>
#include <algorithm>

#include "GameManager.h"

GameManager::GameManager(GameConfiguration config) {
    this->config = config;
    this->randimizer = Randomizer();
}

RequestResult GameManager::nextRound() {
    RequestResult result;

    // Сбор пшеницы
    config.wheatGathered = config.population * 10 > config.landsForCultivation
        ? config.landsForCultivation * config.wheatGatheredFromOneLandInEachRound[config.round]
        : config.population * 10 * config.wheatGatheredFromOneLandInEachRound[config.round];
    config.wheat += config.wheatGathered;

    // Крысы
    config.wheatDestroyedByRats = randimizer.randomValue(0, 0.07 * config.wheat);
    config.wheat -= config.wheatDestroyedByRats;

    // ешь умри молись
    int deadPopulation = std::max(0, static_cast<int>(std::ceil((20 * config.population - config.wheatForEat) / 20)));

    if (deadPopulation / config.population >= 0.45) {
        result.success = false;
        result.message = "Проиграл, за прошедший год умерло больше 45% населения";
        return result;
    }

    config.wheat -= std::min(config.wheat * 20, config.wheatForEat);
    config.population -= deadPopulation;
    config.deadPopulationInEachRound[config.round] = deadPopulation;

    // Новые менчики
    int arrivedPopulation = std::clamp(
        deadPopulation / 2 + (5 - config.wheatGatheredFromOneLandInEachRound[config.round]) * config.wheat / 600 + 1,
        0, 
        50
    );
    config.population += arrivedPopulation;
    config.arrivedPopulationInEachRound[config.round] = arrivedPopulation;

    // Чума
    config.didThePlagueHappen = randimizer.eventWithChance(15);
    if (config.didThePlagueHappen) {
        config.population -= std::floor(config.population / 2);
    }

    config.round += 1;
    result.success = true;
    return result;
}

void GameManager::updateData() {
    config.currenLandPrice = randimizer.randomValue(17, 26);
    config.wheatGatheredFromOneLandInEachRound[config.round] = randimizer.randomValue(1, 6);
}

std::string GameManager::getStatus() {
    std::string status;
    status += "\n";
    status += "Мой повелитель, соизволь поведать тебе \n";
    status += "\t в году " + std::to_string(config.round) + " твоего высочайшего правления \n";

    int deadPopulation = config.deadPopulationInEachRound[config.round - 1];
    int arrivedPopulation = config.arrivedPopulationInEachRound[config.round - 1];

    if (deadPopulation > 0 || arrivedPopulation > 0) {
        status += "\t " + std::to_string(deadPopulation) + " человек умерли с голоду, и ";
        status += std::to_string(arrivedPopulation) + " человек прибыли в наш великий город \n";
    }
    
    if (config.didThePlagueHappen) {
        status += "\t ☠️ Чума уничтожила половину населения ☠️ \n";
    }

    status += "\t Население города сейчас составляет " + std::to_string(config.population) + " человек \n";

    if (config.wheatGathered > 0 || config.landsForCultivation > 0) {
        status += "\t Мы собрали " + std::to_string(config.wheatGathered) + " 🌾, по " + std::to_string(config.wheatGatheredFromOneLandInEachRound[config.round - 1]) + " бушеля 🌾 с акра \n";
    }
    
    if (config.wheatDestroyedByRats > 0) {
        status += "\t Крысы истребили " + std::to_string(config.wheatDestroyedByRats) + " 🌾, оставив " + std::to_string(config.wheat) + " бушеля 🌾 в амбарах \n";
    } else {
        status += "\t Сейчас в ваших амбарах " + std::to_string(config.wheat) + " бушеля 🌾 \n";
    }
    
    status += "\t Город сейчас занимает " + std::to_string(config.land) + " акров 🏔️ \n";
    status += "\t 1 акр 🏔️ стоит сейчас " + std::to_string(config.currenLandPrice) + " бушеля 🌾 \n";

    return status;
}

RequestResult GameManager::buyLands(int landsCount) {
    RequestResult result;
    
    if (landsCount * config.currenLandPrice > config.wheat) {
        result.success = false;
        result.message = "Не хватает " + std::to_string(landsCount * config.currenLandPrice - config.wheat) + " 🌾 для покупки земли 📸🤡 \n";
    } else {
        config.wheat -= landsCount * config.currenLandPrice;
        config.land += landsCount;  
        
        result.success = true;
        if (landsCount > 0) {
            result.message = "🏔️ успешно куплена \n";
            result.message += std::to_string(config.wheat) + "  🌾 осталось в запасах \n";
            result.message += "теперь у вас " + std::to_string(config.land) + "  🏔️ \n";
        }
    }
    
    return result;
}

RequestResult GameManager::sellLands(int landsCount) {
    RequestResult result;

    if (landsCount > config.land) {
        result.success = false;
        result.message = "Не хватает " + std::to_string(landsCount - config.land) + "  🏔️ для продажи 📸🤡 \n";
    } else {
        config.land -= landsCount;
        config.wheat += landsCount * config.currenLandPrice;

        result.success = true;

        if (landsCount > 0) {
            result.message = "🏔️ успешно продана \n";
            result.message = std::to_string(config.land) + "  🏔️ осталось \n";
            result.message += "теперь у вас " + std::to_string(config.wheat) + "  🌾 в запасах \n";
        }
    }

    return result;
}

RequestResult GameManager::setCountOfWheatForEat(int wheatCount) {
    RequestResult result;

    if (wheatCount > config.wheat) {
        result.success = false;
        result.message = "Не хватает " + std::to_string(wheatCount - config.wheat) + "  🌾 для пропитания \n";
    } else {
        config.wheatForEat = wheatCount;
        
        result.success = true;
        if (wheatCount > 0) { 
            result.message = std::to_string(wheatCount) + "  🌾 было потрачено на пропитания \n";
        }
    }

    return result;
}

RequestResult GameManager::setCountOfLandsForCultivation(int landsCount) {
    RequestResult result;

    if (landsCount > config.wheat * 2) {
        result.success = false;
        result.message = "Не хватает " + std::to_string(landsCount - config.wheat * 2) + "  🌾 для посева \n";
    } else {
        config.wheat -= landsCount / 2; 
        config.landsForCultivation = landsCount;
        
        result.success = true;
        if (landsCount > 0) { 
            result.message = std::to_string(landsCount) + "  🏔️ было засеяно \n";
        }
    }

    return result;
}

std::string GameManager::getEndGameStatistics() {
    float p = 0.0;
    for (int i = 0; i < 10; i++) {
        p += config.deadPopulationInEachRound[i];
    }
    p /= 10;
    float l = config.land / config.population;

    if (p > 0.33 && l < 7) {
        return "\n Из-за вашей некомпетентности в управлении, народ устроил бунт, и изгнал вас их города. Теперь вы вынуждены влачить жалкое существование в изгнании \n";
    } else if (p > 0.1 && l < 9) {
        return "\n Вы правили железной рукой, подобно Нерону и Ивану Грозному. Народ вздохнул с облегчением, и никто больше не желает видеть вас правителем \n";
    } else if (p > 0.03 && l < 10) {
        return "\n Вы справились вполне неплохо, у вас, конечно, есть недоброжелатели, но многие хотели бы увидеть вас во главе города снова \n";
    } else {
        return "\n Фантастика! Карл Великий, Дизраэли и Джефферсон вместе не справились бы лучше \n";
    }
}

 void GameManager::setNewConfig(GameConfiguration config) {
    this->config = config;
}

int GameManager::currentRound() {
    return config.round;
}

GameConfiguration GameManager::getConfig() {
    return this->config;
}