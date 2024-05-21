# Live2DDesktop-CMake
* 基于Cubism官方示例Cubism Native Sample Minimum Demo修改
* 基于 Qt 的跨平台支持

## 功能
* 模型
    - [x] 加载模型
    - [ ] 切换模型
    - [ ] 修补动作参数
    - [ ] 修改模型参数
* 界面
    - [x] 角色绘制
    - [x] 系统托盘
    - [ ] 设置窗口
    - [ ] 右键菜单
    - [ ] 输入窗口
    - [ ] 聊天记录
* 其他
    - [x] 跨平台：linux/windows
    - [ ] 插件
    
## 环境
Windows:  
* Qt 5.15.2 (MinGW-win64) （没有安装qt可以直接使用thirdParty中的静态库，但是运行需要使用 windeployqt）
* MinGW 8.1 (x86_64)

Linux(以Archlinux为例):  
* gcc/g++ (x86_64)
* Qt5: `sudo pacman -S qt5-base`
* glu: `sudo pacman -S glu`
* 其他依赖由于使用者图形化界面配置不同需可能需要额外安装

共用:  
* glew 2.1+
* glfw 3.4+
* CMake 3.13+

## 推荐配置
* 安装 VS Code 插件 `CMake`，`CMake Tools`，`C/C++`
* `Ctrl+Shift+P` 并选择 `CMake: Configure`
* Windows平台需要将 `Main/CMakeLists.txt` 中 `set(CMAKE_PREFIX_PATH, ...)` 的 `...` 修改为 qt 的安装路径
* 选择 `live2d` 进行构建

