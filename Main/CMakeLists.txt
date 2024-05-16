SET(APP_NAME live2d)

# Set directory paths.
set(CORE_PATH ${PROJECT_ROOT}/Core)
set(FRAMEWORK_PATH ${PROJECT_ROOT}/Framework)
set(THIRD_PARTY_PATH ${PROJECT_ROOT}/thirdParty)
set(STB_PATH ${THIRD_PARTY_PATH}/stb)
set(GLEW_PATH ${THIRD_PARTY_PATH}/glew)
set(GLFW_PATH ${THIRD_PARTY_PATH}/glfw)
set(QT_INCLUDE_PATH ${THIRD_PARTY_PATH}/qt)
set(RES_PATH ${PROJECT_ROOT}/Resources)

# Set Qt Installation Path
set(CMAKE_PREFIX_PATH D:/cdk/qt/5.15.2/mingw81_64)
find_package(Qt5 REQUIRED Core Gui Widgets Quick Qml)

# Surpress GLEW and GLFW process.
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(BUILD_UTILS OFF CACHE BOOL "" FORCE)

# Specify version of compiler.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --Configure OpenGL--
# Add GLEW ,GLFW.
add_subdirectory(${GLEW_PATH}/build/cmake ${CMAKE_BINARY_DIR}/glew_s)
add_subdirectory(${GLFW_PATH} ${CMAKE_BINARY_DIR}/glfw)

# --Configure Framework--
# Specify Cubism Framework rendering.
set(FRAMEWORK_SOURCE OpenGL)
# Add Cubism Native Framework.
add_subdirectory(${FRAMEWORK_PATH} ${CMAKE_BINARY_DIR}/Framework)
# Add rendering definition to framework.
target_compile_definitions(Framework PUBLIC CSM_TARGET_WIN_GL)
# Add include path of GLEW to framework.
target_include_directories(Framework PUBLIC ${GLEW_PATH}/include)
# If current compiler is mingw, add some options
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  target_compile_options(Framework PRIVATE -fpermissive -Wconversion-null)
endif()  
# Link libraries to framework.
add_library(Live2DCubismCore STATIC IMPORTED)

# --CubismCoreLib--
# Import CubismCoreLib
set_target_properties(Live2DCubismCore
  PROPERTIES
    IMPORTED_LOCATION
      ${CORE_PATH}/dll/Live2DCubismCore.lib
    INTERFACE_INCLUDE_DIRECTORIES
      ${CORE_PATH}/include
)
target_compile_definitions(Live2DCubismCore
  INTERFACE
  __linux__# Windows 平台上使用 mingw 也需要使用该宏，应该是没有做 mingw 的适配
  CSM_TARGET_WIN_GL 
)

target_link_libraries(Framework Live2DCubismCore glew_s)

# Find opengl libraries.
find_package(OpenGL REQUIRED)

# Make executable app.
add_executable(${APP_NAME} 
  main.cpp
  AppConfig.cpp
)

# Add source files.
add_subdirectory(live2d)
add_subdirectory(model)

# Link libraries to app.
target_link_libraries(${APP_NAME}
  Framework
  glfw
  ${OPENGL_LIBRARIES}
  Qt5::Core
  Qt5::Gui
  Qt5::Widgets
  Qt5::Quick
  Qt5::Qml
)

# Specify include directories.
target_include_directories(${APP_NAME} PRIVATE ${STB_PATH} ${QT_INCLUDE_PATH}/include live2d .)

# Post build commands
add_custom_command(
  TARGET ${APP_NAME}
  POST_BUILD
  COMMAND
    ${CMAKE_COMMAND} -E
      copy_directory ${RES_PATH} $<TARGET_FILE_DIR:${APP_NAME}>/Resources
  COMMAND
    ${CMAKE_COMMAND} -E
      copy ${CORE_PATH}/dll/Live2DCubismCore.dll $<TARGET_FILE_DIR:${APP_NAME}>
  COMMAND
    ${CMAKE_PREFIX_PATH}/bin/windeployqt $<TARGET_FILE_DIR:${APP_NAME}>/${APP_NAME}.exe
)
