#pragma once

#include <model/IModelManager.hpp>

class IAppDelegate
{
public:
    virtual void Initialize() = 0;
    virtual void Release() = 0;
    virtual void Run() = 0;
    virtual IModelManager* GetModelManager() = 0;
};