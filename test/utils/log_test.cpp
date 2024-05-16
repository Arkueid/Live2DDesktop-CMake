#include <utils/Log.hpp>


int main()
{
    Debug("debug msg %d %d", 1111, 2222);
    _DebugF("debug.log", "debug msg %d %d", __BASE_FILE__, __LINE__, 1111, 2222);
    Info("info msg %d %d", 1111, 2222);
    InfoF("info.log", "info msg %d %d", 1111, 2222);
    Error("error msg %d %d", 1111, 2222);
    ErrorF("error.log", "error msg %d %d", 1111, 2222);
    return 0;
}