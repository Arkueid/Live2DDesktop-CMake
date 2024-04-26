#pragma once
#include <live2d/LAppModel.hpp>


class IModelManager
{
public:
    /// @brief 获取当前已加载的模型，若模型不存在则报错
    /// @return 返回模型
    virtual LAppModel * GetCurrentModel() = 0;

    /// @brief 加载模型，自动释放之前已经加载的模型
    /// @param modelDir 
    virtual void LoadModel(const char *modelDir) = 0;

    /// @brief 释放模型
    virtual void ReleaseModel() = 0;
};