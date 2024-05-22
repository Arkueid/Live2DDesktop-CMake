#pragma once

#include <CubismFramework.hpp>
#include <Math/CubismViewMatrix.hpp>

class MatrixManager
{
public:
    void Initialize();
    void AdaptToSceneSize();
    void ScreenToScene(float *x, float *y);
private:
    Csm::CubismMatrix44 _screenToScene;
};