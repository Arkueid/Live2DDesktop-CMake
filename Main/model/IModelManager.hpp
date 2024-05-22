#pragma once
#include <live2d/LAppModel.hpp>

class IModelManager
{
public:
    /// @brief 获取当前已加载的模型，若模型不存在则报错
    /// @return 返回模型
    virtual LAppModel * GetModel() = 0;

    /// @brief 加载模型，自动释放之前已经加载的模型
    /// @param modelDir 
    virtual void SetModel(const char *modelDir) = 0;

    virtual void UpdateModel(int winWidth, int winHeight) = 0;
    

    /// @brief 点击触碰
    /// @param x opengl 坐标系 x
    /// @param y opengl 坐标系 y
    virtual void OnTouch(float x, float y) = 0;

    /// @brief 视线拖动
    /// @param x opengl 坐标系 x
    /// @param y opengl 坐标系 y
    virtual void OnDrag(float x, float y) = 0;
};