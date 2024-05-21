# Live2DDesktop-CMake

* 不使用 Visual Studio 过于庞大的配置
* 基于官方 CubismNativeSample Minimum Demo 修改
* Qt 与 Live2D 结合的最简模板

## 环境

* Qt 5.15.2 (MinGW-win64) （没有安装qt可以直接使用thirdParty中的静态库，但是运行需要使用 windeployqt）
* MinGW 8.1 (win64)
* glew 2.1+
* glfw 3.4+
* CMake 3.13+

### 直接使用 thirdParty/qt 文件夹下的静态库

以使用 Qt5Core.a 为例

```cmake
add_library(Qt5Core STATIC IMPORTED)
set_target_properties(Qt5Core 
    PROPERTIES
        IMPORTED_LOCATION
            ${PROJECT_ROOT}/thirdParty/qt/lib/Qt5Core.a
        INTERFACE_INCLUDE_DIRECTORIES
            ${PROJECT_ROOT}/thirdParty/qt/include
)

target_link_libraries(${APP_NAME} Qt5Core)
```

## 启动

* 安装 VS Code 插件 `CMake`，`CMake Tools`，`C/C++`
* Ctrl+Shift+P 并选择 `CMake: Configure`
* 将 Main/CMakeLists.txt 中 `set(CMAKE_PREFIX_PATH, ...)` 的 `...` 修改为 qt 的安装路径
* 选择 `live2d` 进行构建

