#include "Config.hpp"
#include <assert.h>

#include <iostream>
#include <fstream>
#include <QtCore/qjsondocument.h>

#include <Default.hpp>

#include <utils/Log.hpp>

static Config* _instance = nullptr;

void Config::Initialize()
{
    _instance = new Config();
    std::ifstream file;
    file.open(APP_CONFIG_PATH);
    if (!file.is_open())
    {
        Error("config file read error");
    }
}

Config *Config::GetInstance()
{
    assert(_instance != nullptr);

    return _instance;
}

void Config::ReleaseInstance()
{
    if (_instance)
    {
        delete _instance;
    }
}

Config::Config()
{
}

Config::~Config()
{
}

const char *Config::GetResourceDir()
{
    return nullptr;
}

int Config::GetSceneWidth()
{
    return 0;
}

int Config::GetSceneHeight()
{
    return 0;
}
