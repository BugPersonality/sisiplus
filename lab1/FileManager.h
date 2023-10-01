#pragma once

#include <string>

#include "GameConfiguraion.h"

class FileManager {
public:
    FileManager(const std::string fileName);

    bool saveConfiguration(const GameConfiguration& config);
    bool loadConfiguration(GameConfiguration& config);

private:
    std::string fileName;

    bool fileExists() const;
};