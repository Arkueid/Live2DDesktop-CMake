#include <model/IModelManager.hpp>

class ModelManager: public IModelManager
{
public:
    static IModelManager* GetInstance();
    static void ReleaseInstance();

    LAppModel * GetModel();

    void SetModel(const char *modelDir);

    void UpdateModel(int winWidth, int winHeight);
private:
    ModelManager();
    ~ModelManager();
};