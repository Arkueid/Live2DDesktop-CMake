#include "ModelManager.hpp"
#include <Config.hpp>
#include <assert.h>

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

