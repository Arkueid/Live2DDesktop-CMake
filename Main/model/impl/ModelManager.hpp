#include <model/IModelManager.hpp>

class ModelManager : public IModelManager
{
public:
    ModelManager();
    
    ~ModelManager();

    LAppModel *GetModel();

    void SetModel(const char *modelDir);

    void UpdateModel(int winWidth, int winHeight);

private:
    LAppModel *_currentModel;
};