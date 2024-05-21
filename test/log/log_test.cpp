// test for log
#include <utils/Log.hpp>


int main()
{
    Debug("debug msg %d %d", 1111, 2222);
    Info("info msg %d %d", 1111, 2222);
    Error("error msg %d %d", 1111, 2222);
    return 0;
}