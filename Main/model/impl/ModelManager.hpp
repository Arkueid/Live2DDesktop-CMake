#include <model/IModelManager.hpp>

class ModelManager : public IModelManager
{
public:
    ModelManager();
    
    ~ModelManager();

    LAppModel *GetModel();

    void SetModel(const char *modelDir);

    void UpdateModel(int winWidth, int winHeight);

    void OnTouch(float x, float y);

    void OnDrag(float x, float y);
private:
    LAppModel *_currentModel;
};