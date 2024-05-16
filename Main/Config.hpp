#pragma once

#include <QtCore/qjsonobject.h>

class Config
{
private:
    QJsonObject *_json;
    Config();
    ~Config();

public:
    static void Initialize();
    static Config *GetInstance();
    static void ReleaseInstance();
    const char *GetResourceDir();
    int GetSceneWidth();
    int GetSceneHeight();
};