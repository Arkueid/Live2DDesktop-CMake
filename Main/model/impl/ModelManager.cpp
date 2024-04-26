#include "ModelManager.hpp"
#include <AppConfig.hpp>
#include <assert.h>

static LAppModel * _currentModel = nullptr;

ModelManager::ModelManager()
{
}

ModelManager::~ModelManager()
{
    ReleaseModel();
}

LAppModel *ModelManager::GetCurrentModel()
{
    assert(_currentModel != nullptr);

    return _currentModel;
}

void ModelManager::LoadModel(const char *modelDir)
{
    // モデルデータの新規生成
        _currentModel = new LAppModel();

        std::string modelPath(AppConfig::ResourceDir);
        modelPath += modelDir;
        modelPath.append("/");

        std::string modelJsonName(modelDir);
        modelJsonName += ".model3.json";

        _currentModel->LoadAssets(modelPath.c_str(), modelJsonName.c_str());
}

void ModelManager::ReleaseModel()
{
    if (_currentModel != nullptr)
    {
        _currentModel->DeleteRenderer();
        delete _currentModel;
    }
}
