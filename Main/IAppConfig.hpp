#pragma once

class IAppConfig
{
public:
    const char* GetResourceDir();
    int GetSceneWidth();
    int GetSceneHeight();
};