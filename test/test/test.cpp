#include <iostream>
using namespace std;

#include <model/model_dir/ModelDir.hpp>

int main()
{
    printf("%d\n", ModelDirectory::IsModelDir("/Resources/"));
    printf("%d\n", ModelDirectory::IsModelDir("C:\\Resources/model"));
    printf("%d\n", ModelDirectory::IsModelDir("/Resources/find/yes/"));
    printf("%d\n", ModelDirectory::IsModelDir("C:/"));
    printf("%d\n", ModelDirectory::IsModelDir("/Resources\\"));
    printf("%d\n", ModelDirectory::IsModelDir("Resources/Haru"));
    printf("%d\n", ModelDirectory::IsModelDir("D:\\forDesktop\\DesktopLive2d-Cmake\\build\\bin\\Debug"));
    printf("%d\n", ModelDirectory::IsModelDir("D:\\forDesktop\\DesktopLive2d-Cmake\\build\\bin\\Debug/Resources/Haru"));

    return 0;
}