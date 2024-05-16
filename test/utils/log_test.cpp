#include <utils/Log.hpp>


int main()
{
    Debug("debug msg");
    Info("info msg");
    Info("info msg", "info.log");
    Error("error msg");
    Error("error msg", "error.log");
    Debug2File("wow","WWO.log");
    return 0;
}