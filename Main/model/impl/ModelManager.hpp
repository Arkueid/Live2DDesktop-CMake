#include <model/IModelManager.hpp>

class ModelManager: public IModelManager
{
public:
    ModelManager();
    ~ModelManager();

    LAppModel * GetCurrentModel();

    void LoadModel(const char *modelDir);

    void ReleaseModel();
};