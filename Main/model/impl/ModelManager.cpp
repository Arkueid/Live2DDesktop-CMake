#include "ModelManager.hpp"
#include <Config.hpp>
#include <assert.h>

#include <CubismFramework.hpp>
#include <utils/log/Log.hpp>
#include <Default.hpp>

using namespace Csm;

ModelManager::ModelManager(): _currentModel(nullptr)
{
}

ModelManager::~ModelManager()
{
    if (_currentModel != nullptr)
    {
        _currentModel->DeleteRenderer();
        delete _currentModel;
        _currentModel = nullptr;
    }
}

LAppModel *ModelManager::GetModel()
{
    assert(_currentModel != nullptr);

    return _currentModel;
}

void ModelManager::SetModel(const char *modelDir)
{
    if (_currentModel != nullptr)
    {
        delete _currentModel;
        _currentModel = nullptr;
    }

    _currentModel = new LAppModel();

    std::string modelPath(Config::GetResourceDir());
    modelPath += modelDir;
    modelPath.append("/");

    std::string modelJsonName(modelDir);
    modelJsonName += ".model3.json";

    _currentModel->LoadAssets(modelPath.c_str(), modelJsonName.c_str());
}

void ModelManager::UpdateModel(int winWidth, int winHeight)
{
    Csm::CubismMatrix44 projection;
    // 念のため単位行列に初期化
    projection.LoadIdentity();

    if (_currentModel->GetModel()->GetCanvasWidth() > 1.0f && winWidth < winHeight)
    {
        // 横に長いモデルを縦長ウィンドウに表示する際モデルの横サイズでscaleを算出する
        _currentModel->GetModelMatrix()->SetWidth(2.0f);
        projection.Scale(1.0f, static_cast<float>(winWidth) / static_cast<float>(winHeight));
    }
    else
    {
        projection.Scale(static_cast<float>(winHeight) / static_cast<float>(winWidth), 1.0f);
    }

    _currentModel->Update();
    _currentModel->Draw(projection);
}

void ModelManager::OnTouch(float x, float y)
{
    csmString hitArea = _currentModel->HitTest(x, y);
    if (strlen(hitArea.GetRawString()) != 0)
    {
        Info("hit area: [%s]", hitArea.GetRawString());
        if (strcmp(hitArea.GetRawString(), HIT_AREA_HEAD) == 0) _currentModel->SetRandomExpression();
        _currentModel->StartRandomMotion(hitArea.GetRawString(), MOTION_PRIORITY_FORCE);
        return;
    }
}

void ModelManager::OnDrag(float x, float y)
{
    _currentModel->SetDragging(x, y);
}
