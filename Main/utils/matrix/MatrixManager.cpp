#include "MatrixManager.hpp"

#include <AppDelegate.hpp>

#include <Config.hpp>

void MatrixManager::Initialize()
{
}

// call when scene is resized
void MatrixManager::AdaptToSceneSize()
{
    int width = Config::GetSceneWidth();
    int height = Config::GetSceneHeight();

    float ratio = static_cast<float>(width) / static_cast<float>(height);
    float left = -ratio;
    float right = ratio;
    float bottom = -1.0f;
    float top = 1.0f;

    _screenToScene.LoadIdentity(); // サイズが変わった際などリセット必須
    if (width > height)
    {
        float screenW = fabsf(right - left);
        _screenToScene.ScaleRelative(screenW / width, -screenW / width);
    }
    else
    {
        float screenH = fabsf(top - bottom);
        _screenToScene.ScaleRelative(screenH / height, -screenH / height);
    }
    _screenToScene.TranslateRelative(-width * 0.5f, -height * 0.5f);
}

void MatrixManager::ScreenToScene(float *x, float *y)
{
    *x = _screenToScene.TransformX(*x);
    *y = _screenToScene.TransformY(*y);
}
