#include "managers/ConfigManager.hpp"

#include <filesystem>
#include <fstream>


ConfigManager::ConfigManager()
{
    load();
}

ConfigManager::~ConfigManager()
{
    save();
}


ConfigManager &ConfigManager::getInstance()
{
    static ConfigManager instance;
    return instance;
}

void ConfigManager::save()
{
    std::filesystem::create_directory("res/conf");

    std::ofstream configFile("res/conf/setting.conf");
    configFile << musicStatus << std::endl;
    configFile << musicVolume << std::endl;
    configFile << soundStatus << std::endl;
    configFile << soundVolume << std::endl;
    configFile.close();
}


void ConfigManager::load()
{
    if (std::filesystem::exists("res/conf"))
    {
        std::ifstream configFile("res/conf/setting.conf");
        configFile >> musicStatus;
        configFile >> musicVolume;
        configFile >> soundStatus;
        configFile >> soundVolume;
        configFile.close();
    }
}
