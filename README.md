# Live2DDesktop-CMake
特色: 
* PC 端桌面 Live2D
* 基于 Qt 的跨平台支持

## 功能
* 模型
    - [x] 加载模型
    - [ ] 切换模型
    - [ ] 修补动作参数
    - [ ] 修改模型参数
* 界面
    - [x] 角色绘制
        - [x] 动作
        - [x] 口型同步
        - [ ] 文本显示
    - [x] 系统托盘
        - [x] 角色显示
        - [x] 视线追踪
        - [x] 锁定
        - [x] 置顶
        - [x] 设置
        - [x] 退出
        - [x] 双击显示
    - [ ] 设置窗口
    - [ ] 右键菜单
    - [ ] 输入窗口
    - [ ] 聊天记录
* 其他
    - [x] 跨平台
        - [x] linux
        - [x] windows
    - [ ] 插件
    
## 开发环境
### 依赖
Windows:  
* Qt 5.15.2 (MinGW-win64) 
* MinGW 8.1 (x86_64)

Linux(以 Archlinux 为例):  
* gcc/g++ (x86_64)
* Qt5: `sudo pacman -S qt5-base`
* glu: `sudo pacman -S glu`
* 其他依赖由于使用者图形化界面配置不同需可能需要额外安装

共用:  
* glew 2.1+
* glfw 3.4+
* CMake 3.13+

### 推荐配置
* 安装 VS Code 插件 `CMake`，`CMake Tools`，`C/C++`
* `Ctrl+Shift+P` 并选择 `CMake: Configure`
* Windows 平台需要将 `Main/CMakeLists.txt` 中 `set(CMAKE_PREFIX_PATH, ...)` 的 `...` 修改为 Qt 的安装路径
* 选择 `live2d` 进行构建