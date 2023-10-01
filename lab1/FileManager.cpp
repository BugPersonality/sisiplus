
#include <iostream>
#include <fstream>

#include "FileManager.h"

FileManager::FileManager(const std::string fileName) : fileName(fileName) {}

bool FileManager::fileExists() const {
    std::ifstream file(fileName);
    return file.good();
}

bool FileManager::saveConfiguration(const GameConfiguration& config) {
    std::ofstream file(fileName, std::ios::binary | std::ios::trunc);
    
    if (!fileExists()) {
        std::cerr << "Нет файла для сохранения :(" << std::endl;
        return false;
    }

    if (!file.is_open()) {
        std::cerr << "Не смог открыть файлик?!?!?!" << std::endl;
        return false;
    }
    file.write(reinterpret_cast<const char*>(&config), sizeof(GameConfiguration));
    file.close();
    return true;
}

bool FileManager::loadConfiguration(GameConfiguration& config) {
    if (!fileExists()) {
        std::cerr << "Нет файла для сохранения :(" << std::endl;
        return false;
    }

    std::ifstream file(fileName, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Упс кто-то уже открыл файлик для сохранения :(" << std::endl;
        return false;
    }

    file.read(reinterpret_cast<char*>(&config), sizeof(GameConfiguration));
    file.close();
    return true;
}