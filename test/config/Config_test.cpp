#include <Config.hpp>
#include <utils/Log.hpp>
#include <QtWidgets/qapplication.h>

int main(int argc, char *argv[])
{
    
    if (!Config::Initialize())
    {
        Error("config file read error!!!");
        return -1;
    }

    Info("%s: %s", KEY_RESOURCE_DIR, Config::GetResourceDir().c_str());
    Info("%s: %d", KEY_SCENE_WIDTH, Config::GetSceneWidth());
    Info("%s: %d", KEY_SCENE_HEIGHT, Config::GetSceneHeight());
    Info("%s: %s", KEY_MODEL_NAME, Config::GetModelName().c_str());

    if (!Config::SaveConfig())
    {
        Error("config file save error!!!");
        return -1;
    }

    Info("config file saved successfully!!!");
    return 0;
}